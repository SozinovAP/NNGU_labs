package com.example.pract_ms_3

import android.annotation.SuppressLint
import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.view.MotionEvent
import android.view.View
import android.widget.Button
import android.widget.TextView

class MainActivity : AppCompatActivity() {
    private var isPressed = false;
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        ChangeText();
        StateButton();
    }

    fun Counter(view: View) {
        val textView = findViewById<TextView>(R.id.count_click);
        textView.text = (Integer.parseInt(textView.text.toString()) + 1).toString();
    }

    @SuppressLint("ClickableViewAccessibility")
    fun ChangeText()
    {
        val textView = findViewById<TextView>(R.id.textView);
        val but = findViewById<Button>(R.id.button_text);

        but.setOnTouchListener { _, event ->
            when(event.action){

                MotionEvent.ACTION_DOWN -> {
                    textView.text = getString(R.string.text_pressed);
                    but.text = getString(R.string.text_pressed);
                }

                MotionEvent.ACTION_UP -> {
                    textView.text = getString(R.string.text_released);
                    but.text = getString(R.string.text_released);
                }

                else ->{

                }
            }
            return@setOnTouchListener true;
        }
    }

    @SuppressLint("ClickableViewAccessibility")
    fun StateButton()
    {
        val butState = findViewById<Button>(R.id.button_state);

        butState.setOnTouchListener {_, event ->
            when(event.action){

                MotionEvent.ACTION_UP -> {
                    butState.isPressed = true;
                }

                else ->{

                }
            }
            return@setOnTouchListener true;
        }
    }

    fun ToDateTime(view: View)
    {
        val newAct = Intent(this, DateTime::class.java);
        startActivity(newAct);
    }
}