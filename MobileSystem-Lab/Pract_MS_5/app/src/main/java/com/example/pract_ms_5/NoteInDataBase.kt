package com.example.pract_ms_5

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.*

class NoteInDataBase : AppCompatActivity() {
    val db = DataBaseNotes(this);
    var lv: ListView? = null;
    var notes = ArrayList<String>();
    lateinit var adapter: ArrayAdapter<String>;

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_note_in_data_base);
        lv = findViewById(R.id.list_view_db);

        notes = db.Notes();
        adapter = ArrayAdapter(this,
                android.R.layout.simple_list_item_1, notes);
        lv?.adapter = adapter;

        lv?.onItemClickListener = AdapterView.OnItemClickListener {
                parent, view, position, id ->
            db.DeleteNote(notes[position]);
            notes = db.Notes();
            adapter.clear();
            adapter.addAll(notes)
            adapter.notifyDataSetChanged();
        }

    }

    fun AddNote(view: View)
    {
        val text = findViewById<EditText>(R.id.input_note).text;
        if (!text.isNullOrEmpty())
        {
            db.InsertNote(text.toString());
            notes = db.Notes();
            adapter.clear();
            adapter.addAll(notes)
            adapter.notifyDataSetChanged();
            findViewById<EditText>(R.id.input_note).text.clear();
        }
    }

    fun NextTask(view: View)
    {
        val newAct = Intent(this, ConfigSaveActivity::class.java);
        startActivity(newAct);
    }

    fun PrevTask(view: View)
    {
        this.finish();
    }
}