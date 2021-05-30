package com.example.pract_ms_6

import android.os.Handler
import androidx.core.os.postDelayed


class MyRunnable : Runnable {
    private var num = 0;
    override fun run() {
        Handler().postDelayed(this, timeLight[(num++) % 3]);
    }
}