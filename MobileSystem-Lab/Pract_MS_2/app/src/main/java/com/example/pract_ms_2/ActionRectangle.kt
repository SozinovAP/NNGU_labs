package com.example.pract_ms_2

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.view.animation.AnimationUtils
import android.widget.ImageView

class ActionRectangle : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_action_rectangle)
    }

    fun ToFiveRectangles(view: View)
    {
        val newAct = Intent(this, FiveRectangles::class.java);
        startActivity(newAct);
    }

    fun ToCountSum(view: View)
    {
        val newAct = Intent(this, CountSum::class.java);
        startActivity(newAct);
    }

    fun StartAnimation(view: View)
    {
        val image: ImageView = findViewById(R.id.anim_rect)
        val animation = AnimationUtils.loadAnimation(this, R.anim.anim_transaltion_and_scale)
        image.startAnimation(animation)
    }
}