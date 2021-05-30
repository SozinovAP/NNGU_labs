package com.example.textquest

import android.content.pm.ActivityInfo
import android.os.Bundle
import android.text.method.ScrollingMovementMethod
import android.view.View
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast
import androidx.activity.viewModels
import androidx.appcompat.app.AppCompatActivity
import androidx.databinding.DataBindingUtil
import com.example.tokeniz.GPT2Client
import java.io.*
import com.example.textquest.databinding.ActivityGameBinding

class GameActivity : AppCompatActivity() {
    private var loadedFrom: Int = 0;
    private lateinit var worldName: String;
    private lateinit var characterName: String;
    private lateinit var fileName: String;
    private val gpt2: GPT2Client by viewModels();
    private lateinit var activityGameBinding: ActivityGameBinding;
    override fun onCreate(savedInstanceState: Bundle?) {
        requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_PORTRAIT;
        super.onCreate(savedInstanceState);
        activityGameBinding = DataBindingUtil
                .setContentView(this, R.layout.activity_game);

        var text: String? = intent.getStringExtra("begin");
        if (text == null) {
            text = "Go";
        }
        gpt2.ChangePrompts(text);
        gpt2.SetCountWords(intent.getIntExtra("count", 100));

        activityGameBinding.vm = gpt2
        activityGameBinding.lifecycleOwner = this
        val tv = findViewById<TextView>(R.id.historyView);
        tv.movementMethod = ScrollingMovementMethod();
        tv.text = text;
    }

    // Save game to database
    fun PrevActivity(view: View) {
        gpt2.SetCountWords(0);
        gpt2.RefreshPrompt();
        this.finish();
    }

}