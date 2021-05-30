package com.example.pract_ms_7

import android.os.Bundle
import android.view.View
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity

class DictionaryActivity : AppCompatActivity() {
    lateinit var dict: String;

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_dictionary)

        System.loadLibrary("library-c");

        Dictionary();
    }

    fun Add(view: View)
    {
        Add(findViewById<EditText>(R.id.input_new_word).text.toString());
        findViewById<EditText>(R.id.input_new_word).text.clear();
        UpdateList();
    }

    fun Remove(view: View)
    {
        Remove();
        UpdateList();
    }

    fun GetDictionary(view: View)
    {
        dict = String(GetDictionary());
        UpdateList();
    }

    fun UpdateList()
    {
        Toast.makeText(applicationContext, String(GetDictionary()), Toast.LENGTH_SHORT).show();
        findViewById<TextView>(R.id.dictionary).text = String(GetDictionary());
    }

    private external fun Dictionary();

    private external fun Dictionary(_dictionary: ArrayList<String>);

    private external fun Add(index: Int, word: String);

    private external fun Add(word: String);

    private external fun Remove();

    private external fun Remove(index: Int);

    private external fun GetByIndex(index: Int): ByteArray;

    private external fun GetDictionary(): ByteArray;
}