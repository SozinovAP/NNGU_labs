package com.example.pract_ms_5

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.AdapterView
import android.widget.ArrayAdapter
import android.widget.ListView
import androidx.appcompat.app.AppCompatActivity

val indexes = ArrayList<String> ();

class ListViewActivity : AppCompatActivity() {
    var lastIndex = 1;

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_list_view_add_remove)

        val lv: ListView = findViewById(R.id.c_list_view);

        val adapter:ArrayAdapter<String> = ArrayAdapter<String>(
                this,
                android.R.layout.simple_list_item_1,
                indexes
        );
        lv.adapter = adapter;
        lv.onItemClickListener = AdapterView.OnItemClickListener {
            parent, view, position, id ->
            indexes.removeAt(position)
            val nAdapter:ArrayAdapter<String> = ArrayAdapter<String>(
                    this,
                    android.R.layout.simple_list_item_1,
                    indexes
            );
            lv.adapter = nAdapter;
        }

    }

    fun NextTask(view: View)
    {
        val newAct = Intent(this, ExchangeRatesActivity::class.java);
        startActivity(newAct);
    }

    fun PrevTask(view: View)
    {
        this.finish();
    }

    fun NewItem(view: View)
    {
        val lv: ListView = findViewById(R.id.c_list_view);

        indexes.add("Number: " + lastIndex++);

        val adapter:ArrayAdapter<String> = ArrayAdapter<String>(
                this,
                android.R.layout.simple_list_item_1,
                indexes
        );
        lv.adapter = adapter;    }
}