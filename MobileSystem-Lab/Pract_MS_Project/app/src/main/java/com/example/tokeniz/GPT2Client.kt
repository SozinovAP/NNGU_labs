package com.example.tokeniz

import android.app.Application
import android.text.Spannable
import android.text.SpannableStringBuilder
import android.util.JsonReader
import android.widget.TextView
import androidx.core.content.res.ResourcesCompat
import androidx.databinding.BindingAdapter
import androidx.lifecycle.*
import com.example.textquest.R
import kotlinx.coroutines.*
import org.tensorflow.lite.Interpreter
import java.io.BufferedReader
import java.io.FileInputStream
import java.io.InputStreamReader
import java.nio.channels.FileChannel
import kotlin.math.exp
import kotlin.random.Random

private const val SEQUENCE_LENGTH  = 64
private const val VOCAB_SIZE       = 50257
private const val NUM_LITE_THREADS = 4
private const val MODEL_PATH       = "model.tflite"
private const val VOCAB_PATH       = "gpt2-vocab.json"
private const val MERGES_PATH      = "gpt2-merges.txt"

private typealias Predictions = Array<Array<FloatArray>>

enum class GPT2StrategyEnum { GREEDY, TOPK }
data class GPT2Strategy(val strategy: GPT2StrategyEnum, val value: Int = 0)

class GPT2Client(application: Application) : AndroidViewModel(application) {
    private val initJob: Job;
    private var autocompleteJob: Job? = null;
    private lateinit var tokenizer: GPT2Tokenizer;
    private lateinit var tflite: Interpreter;

    private var prompts = "Go";
    private var countWords = 100;

    private var _prompt = MutableLiveData(prompts);
    var prompt: LiveData<String> = _prompt;

    private val _completion = MutableLiveData("");
    val completion: LiveData<String> = _completion;

    var strategy = GPT2Strategy(GPT2StrategyEnum.TOPK, 40);

    init {
        initJob = viewModelScope.launch {
            val encoder  = LoadEncoder();
            val decoder  = encoder.entries.associateBy({ it.value }, { it.key });
            val bpeRanks = loadBpeRanks();

            val encDec = EncoderDecoder(encoder, decoder);
            tokenizer = GPT2Tokenizer(encDec, bpeRanks)
            tflite    = LoadModel()
        }
    }

    override fun onCleared() {
        super.onCleared()
        tflite.close()
    }

    fun ChangePrompts(text: String) {
        prompts = text;
        _prompt = MutableLiveData(prompts);
        prompt = _prompt;
    }

    fun SetCountWords(count: Int) {
        countWords = count;
    }

    fun LaunchAutoComplete() {
        autocompleteJob = viewModelScope.launch {
            initJob.join()
            autocompleteJob?.cancelAndJoin()
            _completion.value = ""
            Generate(_prompt.value!!)
        }
    }

    fun RefreshPrompt() {
        autocompleteJob?.cancel();
    }

    private suspend fun Generate(text: String, nbTokens: Int = 100) = withContext(Dispatchers.Default) {
        val tokens = tokenizer.Encode(text)
        repeat (countWords) {
            val maxTokens    = tokens.takeLast(SEQUENCE_LENGTH).toIntArray()
            val paddedTokens = maxTokens + IntArray(SEQUENCE_LENGTH - maxTokens.size)
            val inputIds     = Array(1) { paddedTokens }

            val predictions: Predictions = Array(1) { Array(SEQUENCE_LENGTH) { FloatArray(VOCAB_SIZE) } }
            val outputs = mutableMapOf<Int, Any>(0 to predictions)

            tflite.runForMultipleInputsOutputs(arrayOf(inputIds), outputs)
            val outputLogits = predictions[0][maxTokens.size-1]

            val nextToken: Int = when (strategy.strategy) {
                GPT2StrategyEnum.TOPK -> {
                    val filteredLogitsWithIndexes = outputLogits
                            .mapIndexed { index, fl -> (index to fl) }
                            .sortedByDescending { it.second }
                            .take(strategy.value)

                    // Softmax computation on filtered logits
                    val filteredLogits = filteredLogitsWithIndexes.map { it.second }
                    val maxLogitValue  = filteredLogits.maxOrNull()
                    val logitsExp      = filteredLogits.map { exp(it - maxLogitValue!!) }
                    val sumExp         = logitsExp.sum()
                    val probs          = logitsExp.map { it.div(sumExp) }

                    val logitsIndexes = filteredLogitsWithIndexes.map { it.first }
                    Sample(logitsIndexes, probs)
                }
                else -> outputLogits.argmax()
            }

            tokens.add(nextToken)
            val decodedToken = tokenizer.Decode(listOf(nextToken))
            _completion.postValue(_completion.value + decodedToken)

            yield()
        }
    }

    private suspend fun LoadModel(): Interpreter = withContext(Dispatchers.IO) {
        val assetFileDescriptor = getApplication<Application>().assets.openFd(MODEL_PATH)
        assetFileDescriptor.use {
            val fileChannel = FileInputStream(assetFileDescriptor.fileDescriptor).channel
            val modelBuffer = fileChannel.map(FileChannel.MapMode.READ_ONLY, it.startOffset, it.declaredLength)

            val opts = Interpreter.Options()
            opts.setNumThreads(NUM_LITE_THREADS)
            return@use Interpreter(modelBuffer, opts)
        }
    }

    private suspend fun LoadEncoder(): Map<String, Int> = withContext(Dispatchers.IO) {
        hashMapOf<String, Int>().apply {
            val vocabStream = getApplication<Application>().assets.open(VOCAB_PATH)
            vocabStream.use {
                val vocabReader = JsonReader(InputStreamReader(it, "UTF-8"))
                vocabReader.beginObject()
                while (vocabReader.hasNext()) {
                    val key = vocabReader.nextName()
                    val value = vocabReader.nextInt()
                    put(key, value)
                }
                vocabReader.close()
            }
        }
    }

    private suspend fun loadBpeRanks():Map<Pair<String, String>, Int> = withContext(Dispatchers.IO) {
        hashMapOf<Pair<String, String>, Int>().apply {
            val mergesStream = getApplication<Application>().assets.open(MERGES_PATH)
            mergesStream.use { stream ->
                val mergesReader = BufferedReader(InputStreamReader(stream))
                mergesReader.useLines { seq ->
                    seq.drop(1).forEachIndexed { i, s ->
                        val list = s.split(" ")
                        val keyTuple = list[0] to list[1]
                        put(keyTuple, i)
                    }
                }
            }
        }
    }
}

private fun RandomIndex(probs: List<Float>): Int {
    val rnd = probs.sum() * Random.nextFloat()
    var acc = 0f

    probs.forEachIndexed { i, fl ->
        acc += fl
        if (rnd < acc) {
            return i
        }
    }

    return probs.size - 1
}

private fun Sample(indexes: List<Int>, probs: List<Float>): Int {
    val i = RandomIndex(probs)
    return indexes[i]
}

private fun FloatArray.argmax(): Int {
    var bestIndex = 0
    repeat(size) {
        if (this[it] > this[bestIndex]) {
            bestIndex = it
        }
    }

    return bestIndex
}

@BindingAdapter("prompt", "completion")
fun TextView.formatCompletion(prompt: String, completion: String): Unit {
    text = when {
        completion.isEmpty() -> prompt
        else -> {
            val str = SpannableStringBuilder(prompt + completion)
            val bgCompletionColor = ResourcesCompat.getColor(resources, R.color.colorPrimary, context.theme)
            str.setSpan(android.text.style.BackgroundColorSpan(bgCompletionColor), prompt.length, str.length, Spannable.SPAN_EXCLUSIVE_EXCLUSIVE)

            str
        }
    }
}
