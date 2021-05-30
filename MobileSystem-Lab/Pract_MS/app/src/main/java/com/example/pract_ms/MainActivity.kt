package com.example.pract_ms

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.TextView

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }

    fun Increment(view: View) {
        val textView = findViewById<TextView>(resources.getIdentifier("text_count", "id", packageName));
        textView.text = (Integer.parseInt(textView.text.toString()) + 1).toString();
    }

    fun Decrement(view: View) {
        val textView = findViewById<TextView>(resources.getIdentifier("text_count", "id", packageName));
        textView.text = (Integer.parseInt(textView.text.toString()) - 1).toString();
    }
}