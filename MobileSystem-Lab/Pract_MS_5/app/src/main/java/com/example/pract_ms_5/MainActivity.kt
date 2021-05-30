package com.example.pract_ms_5

import android.content.Intent
import android.graphics.Color
import android.os.Bundle
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import android.widget.ListView
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import kotlin.collections.ArrayList

val arrayValues = ArrayList<Triple<Int, Int, String>> ();

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        arrayValues.clear();
        arrayValues.add(Triple(Color.WHITE, Color.BLACK, "White"));
        arrayValues.add(Triple(Color.BLUE, Color.RED, "Blue"));
        arrayValues.add(Triple(Color.BLACK, Color.WHITE, "Black"));

        val lv: ListView = findViewById(R.id.list_view);

        val arrayAdapter: ArrayAdapter<Triple<Int, Int, String>> =
                object : ArrayAdapter<Triple<Int, Int, String>>(this, android.R.layout.simple_list_item_1, arrayValues) {
            override fun getView(position: Int, convertView: View?, parent: ViewGroup): View {
                val view = super.getView(position, convertView, parent);
                view.setBackgroundColor(arrayValues[position].first);
                val tv = view.findViewById<TextView>(android.R.id.text1);
                tv.setTextColor(arrayValues[position].second);
                tv.text = arrayValues[position].third;
                return view;
            }
        }
        lv.adapter = arrayAdapter;
    }

    fun NextTask(view: View)
    {
        val newAct = Intent(this, ListViewActivity::class.java);
        startActivity(newAct);
    }
}