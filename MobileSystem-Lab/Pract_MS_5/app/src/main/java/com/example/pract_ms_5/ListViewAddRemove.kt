package com.example.pract_ms_5

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View

class ListViewAddRemove : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_list_view_add_remove)

    }

    fun NextTask(view: View)
    {
        val newAct = Intent(this, MainActivity::class.java);
        startActivity(newAct);
    }

    fun PrevTask(view: View)
    {
        val newAct = Intent(this, MainActivity::class.java);
        startActivity(newAct);
    }
}