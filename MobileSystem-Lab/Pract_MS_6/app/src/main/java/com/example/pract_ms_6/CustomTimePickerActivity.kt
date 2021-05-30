package com.example.pract_ms_6

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity
import com.google.android.material.internal.ContextUtils.getActivity
import java.util.*

class CustomTimePickerActivity : AppCompatActivity() {
    var clockTimer: Timer = Timer();
    lateinit var timerTask: TimerTask;
    lateinit var clockView: Clock;

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_custom_time_picker)

        clockView = findViewById(R.id.clock);
        timerTask = object : TimerTask() {
            override fun run() {
                runOnUiThread{ clockView.go() };
            }
        }

    }

    fun StartStop(view: View)
    {
        if (clockView.GetState() == State.Start)
        {
            findViewById<Button>(R.id.but_start_stop).text = getString(R.string.text_start);
            findViewById<Button>(R.id.but_reset).isEnabled = true;
            clockView.SetState(State.Stop);
            clockTimer.cancel();
        }
        else
        {
            findViewById<Button>(R.id.but_start_stop).text = getString(R.string.text_stop);
            findViewById<Button>(R.id.but_reset).isEnabled = false;
            clockView.SetState(State.Start);
            clockTimer = Timer();
            timerTask = object : TimerTask() {
                override fun run() {
                    runOnUiThread{ clockView.go() };
                }
            };
            clockTimer.schedule(timerTask, 1000, 1000);
        }
    }

    fun ResetTimer(view: View)
    {
        if (clockView.GetState() == State.Stop)
        {
            clockView.SetTime(0, Field.Second);
            clockView.SetTime(0, Field.Minute);
            clockView.SetTime(0, Field.Hour);
        }
    }

    fun PrevTask(view: View)
    {
        this.finish();
    }
}