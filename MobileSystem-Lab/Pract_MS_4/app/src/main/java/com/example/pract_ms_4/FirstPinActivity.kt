package com.example.pract_ms_4

import android.app.ActivityManager
import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.TextView
import android.widget.Toast

class FirstPinActivity : AppCompatActivity() {
    private lateinit var am: ActivityManager;

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_first_pin)

        am = getSystemService(ACTIVITY_SERVICE) as ActivityManager;
        val task: ActivityManager.AppTask = am.appTasks[0];
        Toast.makeText(applicationContext, task.taskInfo.numActivities.toString() + ":::::" + am.appTasks.size.toString(), Toast.LENGTH_SHORT).show();
    }

    fun NextTask(view: View)
    {
        val newAct = Intent(this, DialogTasksActivity::class.java);
        startActivity(newAct);
    }

    fun PrevTask(view: View)
    {
        this.finish();
    }
}