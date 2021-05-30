package com.example.pract_ms_3

import android.content.Intent
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.view.View
import android.widget.CalendarView
import android.widget.TimePicker
import android.widget.Toast


class DateTime : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_date_time)

        val calendarView = findViewById<CalendarView>(R.id.calendarView);
        val time = findViewById<TimePicker>(R.id.timePicker);

        calendarView.setOnDateChangeListener { _, year, month, dayOfMonth ->
            Log.d("date", year.toString().plus('/').plus(month.toString()).plus('/').plus(dayOfMonth.toString()));
            Toast.makeText(applicationContext, year.toString().plus('/').plus(month.toString()).plus('/').plus(dayOfMonth.toString()), Toast.LENGTH_LONG).show();
        }
        time.setOnTimeChangedListener { _, hourOfDay, minute ->
            Log.d("time", hourOfDay.toString().plus(':').plus(minute.toString()));
            Toast.makeText(applicationContext, hourOfDay.toString().plus(':').plus(minute.toString()), Toast.LENGTH_LONG).show();
        }
    }

    fun SelectDate(view: View)
    {
        val calendar = findViewById<CalendarView>(R.id.calendarView);
        Log.d("date", calendar.date.toString());
    }

    fun SelectTime(view: View)
    {
        val time = findViewById<TimePicker>(R.id.timePicker);
        Log.d("time", time.toString());
    }

    fun ToRemaind(view: View)
    {
        val newAct = Intent(this, RemainedTasks::class.java);
        startActivity(newAct);
    }
}