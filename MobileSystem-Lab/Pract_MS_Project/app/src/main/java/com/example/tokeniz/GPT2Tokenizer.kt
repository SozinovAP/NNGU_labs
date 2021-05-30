package com.example.tokeniz

class GPT2Tokenizer(
        private val encDec: EncoderDecoder,
        private val bpeRanks: Map<Pair<String, String>, Int>) {
    private val encodeRegex = Regex("""'s|'t|'re|'ve|'m|'ll|'d| ?\p{L}+| ?\p{N}+| ?[^\s\p{L}\p{N}]+|\s+(?!\S)|\s+""")

    fun Decode(tokens: List<Int>): String {
        val text = tokens.joinToString("") { encDec.Decode(it, ""); }
        val utfCodePoints = text.map { byteDecoder[it.toString()]!! };
        return String(utfCodePoints.toIntArray(), 0, utfCodePoints.size);
    }

    fun Encode(text: String): MutableList<Int> {
        val tokens = encodeRegex.findAll(text).map { result ->
            result.value.codePoints()
                    .boxed()
                    .map { byteEncoder[it]!! }
                    .toArray()
                    .joinToString("")
        }

        return tokens
                .map { Bpe(it) }
                .flatten()
                .map { encDec.GetEncodeByKey(it) }
                .toMutableList();
    }

    private fun Bpe(token: String): List<String> {
        if (token.length <= 1) return listOf(token)

        var word = token.map { it.toString() }
        var pairs = GetPairs(word)

        while (true) {
            if (!pairs.any { bpeRanks.containsKey(it) }) break
            val (first, second) = pairs.minByOrNull { bpeRanks.getOrDefault(it, Int.MAX_VALUE) } ?: break

            var i = 0
            val newWord = mutableListOf<String>()
            while (i < word.size) {
                val j = word.withIndex().indexOfFirst { it.index >= i && it.value == first }
                if (j != -1) {
                    newWord.addAll(word.subList(i, j))
                    i = j
                } else {
                    newWord.addAll(word.subList(i, word.size))
                    break
                }

                if (word[i] == first && i < word.size-1 && word[i+1] == second) {
                    newWord.add(first+second)
                    i += 2
                } else {
                    newWord.add(word[i])
                    i += 1
                }
            }

            word = newWord
            if (word.size == 1) {
                break
            } else {
                pairs = GetPairs(word)
            }
        }

        return word
    }

    private fun GetPairs(word: List<String>): Set<Pair<String, String>> {
        return mutableSetOf<Pair<String, String>>().apply {
            for (i in 0 until word.size-1) {
                add(word[i] to word[i+1])
            }
        }
    }
}
