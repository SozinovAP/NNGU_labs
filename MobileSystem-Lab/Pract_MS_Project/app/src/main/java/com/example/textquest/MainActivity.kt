package com.example.textquest

import android.content.Intent
import android.content.pm.ActivityInfo
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.EditText

// Main activity
class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_PORTRAIT;
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    // Go to GameActivity
    fun Next(view: View) {
        val activity = Intent(this, GameActivity::class.java);
        val editText = findViewById<EditText>(R.id.text_input);
        val editTextCount = findViewById<EditText>(R.id.editTextNumber);
        if (editText.text.isNotEmpty()) {
            activity.putExtra("begin", editText.text.toString());
        }

        if (editTextCount.text.isNotEmpty()) {
            activity.putExtra("count", editTextCount.text.toString().toInt());
        }
        startActivity(activity);
    }
}