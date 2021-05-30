package com.example.pract_ms_4

import android.app.ActivityManager
import android.app.ActivityManager.AppTask
import android.content.Intent
import android.os.Bundle
import android.support.v4.app.NotificationManagerCompat
import android.support.v4.content.ContextCompat
import android.support.v7.app.AppCompatActivity
import android.view.View
import android.widget.TextView
import android.widget.Toast


class MainActivity : AppCompatActivity() {
    private lateinit var am: ActivityManager;

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        am = getSystemService(ACTIVITY_SERVICE) as ActivityManager;
        val task: AppTask = am.appTasks[0];
        findViewById<TextView>(R.id.dep_stack).text = getString(R.string.text_cur_stack_depth).plus(task.taskInfo.numActivities);

        ContextCompat.startForegroundService(this, Intent(this, ForegroundService::class.java));
    }

    fun IncStackDepth(view: View)
    {
        val newAct = Intent(this, MainActivity::class.java);
        startActivity(newAct);
   }

    fun DecStackDepth(view: View)
    {
        if (am.appTasks[0].taskInfo.numActivities != 1)
            this.finish();
        else
            Toast.makeText(applicationContext, "It's last activity in the stack", Toast.LENGTH_SHORT).show();
    }

    fun NextTask(view: View)
    {
        ClearStack(view);
        val newAct = Intent(this, FirstPinActivity::class.java);
        startActivity(newAct);
    }

    fun ClearStack(view: View)
    {
        val intent = Intent(applicationContext, MainActivity::class.java);
        val cn = intent.component;
        val mainIntent = Intent.makeRestartActivityTask(cn);
        applicationContext.startActivity(mainIntent)
    }
}