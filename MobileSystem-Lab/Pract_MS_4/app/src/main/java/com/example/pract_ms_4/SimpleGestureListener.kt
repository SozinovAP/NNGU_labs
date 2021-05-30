package com.example.pract_ms_4

import android.view.GestureDetector.SimpleOnGestureListener
import android.view.MotionEvent
import kotlin.math.abs

class SimpleGestureListener : SimpleOnGestureListener() {
    private var mListener: Listener? = null;
    override fun onDown(e: MotionEvent): Boolean {
        return true;
    }

    override fun onScroll(
        e1: MotionEvent,
        e2: MotionEvent,
        distanceX: Float,
        distanceY: Float
    ): Boolean {
        val swipeThreshold = 100;
        val swipeVelocityThreshold = 100;
        var result = false;
        try {
            val diffY = e2.y - e1.y;
            val diffX = e2.x - e1.x;
            if (abs(diffX) > abs(diffY)) {
                if (abs(diffX) > swipeThreshold && abs(distanceX) > swipeVelocityThreshold) {
                    if (diffX > 0) {
                        mListener!!.OnSwipeLeftRight();
                    } else {
                        mListener!!.OnSwipeRightLeft();
                    }
                    result = true
                }
            }
            if (abs(diffY) > swipeThreshold && abs(distanceY) > swipeVelocityThreshold) {
                if (diffY > 0) {
                    mListener!!.OnSwipeUpDown();
                } else {
                    mListener!!.OnSwipeDownUp();
                }
                result = true
            }
        } catch (exception: Exception) {
            exception.printStackTrace();
        }
        return result
    }

    fun SetListener(mListener: Listener?) {
        this.mListener = mListener
    }

    interface Listener {
        fun OnSwipeLeftRight();
        fun OnSwipeRightLeft();
        fun OnSwipeUpDown();
        fun OnSwipeDownUp();

    }
}