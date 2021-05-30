package com.example.pract_ms_6

import android.content.Context
import android.graphics.Color
import android.util.AttributeSet
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.LinearLayout
import android.widget.TextView
import kotlin.collections.ArrayList
import kotlin.random.Random

class CustomComponent(context: Context?, attrs: AttributeSet?) : LinearLayout(context, attrs)  {
    private var viewArray = ArrayList<Pair<View, TypeView>>();
    private var red: Int = 0;
    private var green: Int = 0;
    private var blue: Int = 0;
    init
    {
        inflate(context, R.layout.custom_component, this);
        val typedArray = context!!.obtainStyledAttributes(attrs, R.styleable.MyCustomCompAttributes);
        red = typedArray.getInt(R.styleable.MyCustomCompAttributes_red, 0);
        green = typedArray.getInt(R.styleable.MyCustomCompAttributes_green, 0);
        blue = typedArray.getInt(R.styleable.MyCustomCompAttributes_blue, 0);
        typedArray.recycle();

        InitArray();
    }
    
    private fun InitArray()
    {
        viewArray.add(Pair(findViewById(R.id.custom_1), TypeView.isButton));
        viewArray.add(Pair(findViewById(R.id.custom_2), TypeView.isTextView));
        viewArray.add(Pair(findViewById(R.id.custom_3), TypeView.isEditText));
        viewArray.add(Pair(findViewById(R.id.custom_4), TypeView.isTextView));
    }

    fun GetRandomText(): String?
    {
        val ind = Random.nextInt(0, viewArray.size);
        val randView = viewArray[ind].first;
        return when (viewArray[ind].second)
        {
            TypeView.isTextView -> (randView as TextView).text.toString();
            TypeView.isEditText -> (randView as EditText).text.toString();
            TypeView.isButton -> (randView as Button).text.toString();
            else -> null;
        }
    }

    fun GetColor(): Int
    {
        return Color.rgb(red, green, blue);
    }
}