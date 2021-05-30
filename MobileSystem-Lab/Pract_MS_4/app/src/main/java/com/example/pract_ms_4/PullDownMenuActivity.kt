package com.example.pract_ms_4

import android.content.Intent
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.view.GestureDetector
import android.view.MenuItem
import android.view.MotionEvent
import android.view.View
import android.widget.PopupMenu
import android.widget.TextView


class PullDownMenuActivity : AppCompatActivity() {
    private lateinit var gestDetect: GestureDetector;
    private var setMenu: Boolean = false;
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_pull_down_menu)

        val simpleGestureListener = SimpleGestureListener()
        simpleGestureListener.SetListener(object : SimpleGestureListener.Listener {
            override fun OnSwipeLeftRight() {
                Log.d("GL", "OnSwipeLeftRight");
                setMenu = false;
            }

            override fun OnSwipeRightLeft() {
                Log.d("Gl", "OnSwipeRightLeft");
            }

            override fun OnSwipeUpDown() {
                if (!setMenu)
                    SetMenu(findViewById(R.id.UpMenu));
            }

            override fun OnSwipeDownUp() {
                if (!setMenu)
                    SetMenu(findViewById(R.id.downMenu));
            }

        })
        gestDetect = GestureDetector(this, simpleGestureListener)
    }

    override fun onTouchEvent(event: MotionEvent?): Boolean {
        gestDetect.onTouchEvent(event);
        return super.onTouchEvent(event);
    }

    fun SetMenu(view: View)
    {
        setMenu = true;
        val popup = PopupMenu(this, view);
        popup.setOnDismissListener{
            setMenu = false;
        }
        popup.setOnMenuItemClickListener { item: MenuItem? ->
            if (item != null) {
                findViewById<TextView>(R.id.result).text = item.title
            };
            true;
        };
        val inflater = popup.menuInflater;
        inflater.inflate(R.menu.menuu, popup.menu);
        popup.show();
    }


    fun NextTask(view: View)
    {
        val newAct = Intent(this, DownDropMenuActivity::class.java);
        startActivity(newAct);
    }

    fun PrevTask(view: View)
    {
        this.finish();
    }
}