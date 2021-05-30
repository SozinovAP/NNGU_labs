package com.example.pract_ms_2

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.view.View

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }

    fun ToFiveRectangles(view: View)
    {
        val newAct = Intent(this, FiveRectangles::class.java);
        startActivity(newAct);
    }
}