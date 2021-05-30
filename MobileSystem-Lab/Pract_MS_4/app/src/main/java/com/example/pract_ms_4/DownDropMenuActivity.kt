package com.example.pract_ms_4

import android.content.Intent
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.view.ContextMenu
import android.view.ContextMenu.ContextMenuInfo
import android.view.Menu
import android.view.MenuItem
import android.view.View
import android.widget.AdapterView.AdapterContextMenuInfo
import android.widget.ArrayAdapter
import android.widget.ListView
import android.widget.Toast


class DownDropMenuActivity : AppCompatActivity() {
    lateinit var listView: ListView;
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_down_drop_menu)

        listView = findViewById(R.id.menu_list);

        val elementsMenu = resources.getStringArray(R.array.listView)
        val adapter: ArrayAdapter<String> = ArrayAdapter<String>(
            this,
            android.R.layout.simple_list_item_1,
            elementsMenu
        );
        listView.adapter = adapter;
        registerForContextMenu(listView);
    }

    override fun onCreateContextMenu(menu: ContextMenu?, v: View?, menuInfo: ContextMenuInfo?) {
        super.onCreateContextMenu(menu, v, menuInfo);
        val inflater = menuInflater;
        inflater.inflate(R.menu.context_menu, menu);
    }

    override fun onContextItemSelected(item: MenuItem): Boolean {
        SelectItem(item);
        return true;
    }

    private fun SelectItem(item: MenuItem) {
        Log.d("Name", item.toString());
        Log.d("Position", (item.menuInfo as AdapterContextMenuInfo).position.toString());
        Toast.makeText(applicationContext,
            "Name: $item \n Position in list: " + (item.menuInfo as AdapterContextMenuInfo).position.toString(),
            Toast.LENGTH_SHORT).show();
    }

    fun PrevTask(view: View)
    {
        this.finish();
    }
}