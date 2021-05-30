package com.example.pract_ms_6

import android.annotation.SuppressLint
import android.content.Context
import android.util.AttributeSet
import android.widget.LinearLayout
import android.widget.TextView



enum class State{
    Start,
    Stop,
}

enum class Field{
    Hour,
    Minute,
    Second
}

class Clock(context: Context?, attrs: AttributeSet?) : LinearLayout(context, attrs)  {
    private var hour: Int = 0;
    private var minute: Int = 0;
    private var second: Int = 0;
    private lateinit var clockView: TextView;
    private val tick: Int = 1;
    private var state: State = State.Stop;

    init
    {
        inflate(context, R.layout.clock, this);

        val typedArray = context!!.obtainStyledAttributes(attrs, R.styleable.MyAttributes);
        val hour = typedArray.getInt(R.styleable.MyAttributes_hour, 0);
        val minutes = typedArray.getInt(R.styleable.MyAttributes_minute, 0);
        val seconds = typedArray.getInt(R.styleable.MyAttributes_second, 0);
        typedArray.recycle();

        InitComponents();
        SetTime(hour, Field.Hour);
        SetTime(minutes, Field.Minute);
        SetTime(seconds, Field.Second);
        SetTimeOnView();
    }

    fun SetState(state: State)
    {
        this.state = state;
    }

    fun GetState(): State
    {
        return state;
    }

    private fun InitComponents()
    {
        clockView = findViewById(R.id.textView_timer);
    }

    fun SetTime(value: Int, f: Field)
    {
        when (f)
        {
            Field.Hour -> hour = if (value < 0 || value > 23)
                0
            else
                value;
            Field.Minute -> minute = if (value < 0 || value > 59)
                0
            else
                value;
            Field.Second -> second = if (value < 0 || value > 59)
                0
            else
                value;
        }
        SetTimeOnView();
    }

    fun MovingTime(value: Int, f: Field)
    {
        when (f)
        {
            Field.Hour -> hour = (hour + value) % 24;
            Field.Minute -> {
                MovingTime((minute + value) / 60, Field.Hour);
                minute = (minute + value) % 60
            };

            Field.Second -> {
                MovingTime((second + value) / 60, Field.Minute);
                second = (second + value) % 60
            };
        }
        SetTimeOnView();
    }

    @SuppressLint("SetTextI18n")
    fun SetTimeOnView()
    {
        clockView.text = "$hour : $minute  : $second";
    }

    fun GetTime(f: Field): Int
    {
        return when (f) {
            Field.Hour -> hour;
            Field.Minute -> minute
            Field.Second -> second;
        }
    }

    fun go(value: Int) {
        MovingTime(value, Field.Second);
    }

    fun go() {
        go(tick);
    }
}