package com.example.pract_ms_7

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.EditText
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity

class CounterActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_counter)
        System.loadLibrary("library-c");

        Counter();
    }

    fun UpdateTextView()
    {
        findViewById<TextView>(R.id.counter_value).text = GetCount().toString();
    }

    fun Increment(view: View)
    {
        Increment();
        UpdateTextView();
    }

    fun Decrement(view: View)
    {
        Decrement();
        UpdateTextView();
    }

    fun Reset(view: View)
    {
        Reset();
        UpdateTextView();
    }

    fun SetValue(view: View)
    {
        try {
            SetCount(findViewById<EditText>(R.id.input_value_couter).text.toString().toInt());
            UpdateTextView();
            findViewById<EditText>(R.id.input_value_couter).text.clear();
        }
        catch(e: NumberFormatException) {}
    }

    fun Next(view: View)
    {
        val newAct = Intent(this, DictionaryActivity::class.java);
        startActivity(newAct);
    }

    private external fun Counter();

    private external fun Counter(count: Int);

    private external fun Increment(): Int;

    private external fun Decrement(): Int;

    private external fun Reset(): Int;

    private external fun GetCount(): Int;

    private external fun SetCount(newCount: Int);

}