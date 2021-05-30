package com.example.pract_ms_2

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.view.View

class FiveRectangles : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_five_rectangles)
    }

    fun ToMoveRect(view: View)
    {
        val newAct = Intent(this, ActionRectangle::class.java);
        startActivity(newAct);
    }

    fun ToMain(view: View)
    {
        val newAct = Intent(this, MainActivity::class.java);
        startActivity(newAct);
    }
}