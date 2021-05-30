package com.example.pract_ms_4

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v4.view.ViewPager
import android.view.View
import layout.ViewPagerAdapter

class SlideShowActivity : AppCompatActivity() {
    lateinit var note: ArrayList<Note>;
    lateinit var viewPager: ViewPager;
    lateinit var vAdapter: ViewPagerAdapter;

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_slide_show)

        note = intent.getSerializableExtra("tasks") as ArrayList<Note>;
        viewPager = findViewById(R.id.viewPager);
        vAdapter = ViewPagerAdapter(this, note);
        viewPager.adapter = vAdapter;
    }

    fun NextTask(view: View)
    {
        val newAct = Intent(this, PullDownMenuActivity::class.java);
        startActivity(newAct);
    }

    fun PrevTask(view: View)
    {
        this.finish();
    }
}