package com.example.pract_ms_4

import android.app.AlertDialog
import android.content.Intent
import android.icu.util.Calendar
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.support.v7.widget.LinearLayoutManager
import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.widget.*
import java.util.*
import kotlin.collections.ArrayList


class ListTasksOnWeek : AppCompatActivity() {
    private lateinit var date: Date;
    private var dateSelected = false;
    private lateinit var rv: RecyclerView;
    private var notes: ArrayList<Note> = ArrayList();

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_list_tasks_on_week)

        date = Calendar.getInstance().time;

        SettingRecycleView();
    }

    private fun SettingRecycleView()
    {
        rv = findViewById(R.id.list_notes);
        rv.layoutManager = LinearLayoutManager(this);

        notes.sortWith(Comparator{o1: Note, o2: Note ->
            if (o1.date < o2.date)
                return@Comparator -1;
            else if (o1.date == o2.date)
                return@Comparator 0;
            else
                return@Comparator 1;
        });
        val adapter = RVAdapter(notes);
        rv.adapter = adapter;
    }

    fun NextTask(view: View)
    {
        val newAct = Intent(this, WebViewActivity::class.java);
        newAct.putExtra("tasks", notes);
        startActivity(newAct);
    }

    fun PrevTask(view: View)
    {
        this.finish();
    }

    fun AddNote(view: View)
    {
        val promptsView = LayoutInflater.from(applicationContext).inflate(
            R.layout.new_note_doalog,
            null
        );
        val alertDialogBuilder = AlertDialog.Builder(this);
        val calendar = Calendar.getInstance();
        val calendarView = promptsView.findViewById<CalendarView>(R.id.calendar_note);
        calendarView.setOnDateChangeListener { _, year, month, day ->
            calendar.set(year, month, day);
            date = calendar.time;
            dateSelected = true;
        }
        alertDialogBuilder.setView(promptsView);

        alertDialogBuilder.setCancelable(true)
                .setPositiveButton(
                    getString(R.string.text_apply)
                ) { _, _ ->
                    val desc = promptsView.findViewById<EditText>(R.id.edit_text_note).text.toString();
                    val date = if (dateSelected)
                        date;
                    else
                        Date(calendarView.date);

                    notes.add(Note(desc, date));

                    notes.sortWith(Comparator{o1: Note, o2: Note ->
                        if (o1.date < o2.date)
                            return@Comparator -1;
                        else if (o1.date == o2.date)
                            return@Comparator 0;
                        else
                            return@Comparator 1;
                    });

                    val adapter = RVAdapter(notes);
                    rv.adapter = adapter;
                    dateSelected = false;
                }
                .setNegativeButton(
                    getString(R.string.text_cancel)
                ) { dialog, _ -> dialog.cancel() };
        alertDialogBuilder.create().show();
    }
}