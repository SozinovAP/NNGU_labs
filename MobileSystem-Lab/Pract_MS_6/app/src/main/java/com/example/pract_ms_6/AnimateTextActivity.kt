package com.example.pract_ms_6

import android.animation.ArgbEvaluator
import android.animation.ValueAnimator
import android.annotation.SuppressLint
import android.content.Intent
import android.graphics.Color
import android.os.Bundle
import android.view.MotionEvent
import android.view.View
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity


class AnimateTextActivity : AppCompatActivity() {
    @SuppressLint("ClickableViewAccessibility")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_animate_text);

        var textView = findViewById<TextView>(R.id.curTextView);

        textView.setOnTouchListener { v: View?, event: MotionEvent ->
            when (event.action) {
                MotionEvent.ACTION_DOWN -> {
                    textView.animate().y(2000f).rotation(180f).duration = 5000;
                    val colorFrom = textView.currentTextColor;
                    val colorTo = resources.getColor(R.color.red);
                    val colorAnimation = ValueAnimator.ofObject(ArgbEvaluator(), colorFrom, colorTo);
                    colorAnimation.duration = 5000;
                    colorAnimation.addUpdateListener { animator -> textView.setTextColor((animator.animatedValue as Int)!!) }
                    colorAnimation.start()
                }
                MotionEvent.ACTION_UP -> {
                    textView.animate().y(0f).rotation(0f).duration = 5000;
                    val colorFrom = textView.currentTextColor
                    val colorTo = resources.getColor(R.color.white);
                    val colorAnimation = ValueAnimator.ofObject(ArgbEvaluator(), colorFrom, colorTo)
                    colorAnimation.duration = 5000;
                    colorAnimation.addUpdateListener { animator -> textView.setTextColor((animator.animatedValue as Int)!!) }
                    colorAnimation.start()
                }
            }
            true
        }
    }

    fun NextTask(view: View)
    {
        val newAct = Intent(this, CustomComponentActivity::class.java);
        startActivity(newAct);
    }

    fun PrevTask(view: View)
    {
        this.finish();
    }
}