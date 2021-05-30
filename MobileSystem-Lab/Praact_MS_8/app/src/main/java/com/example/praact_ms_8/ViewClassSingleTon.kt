package com.example.praact_ms_8

import android.view.View

class ViewClassSingleTon private constructor() {
    private val viewArray: ArrayList<View> = ArrayList<View>();

    fun AddView(view: View)
    {
        viewArray.add(view);
    }

    fun GetByIndex(ind: Int): View?
    {
        if (ind < 0 || ind >= viewArray.size)
            return null;
        return viewArray[ind];
    }

    private object HOLDER {
        val INSTANCE = ViewClassSingleTon()
    }

    companion object {
        val instance: ViewClassSingleTon by lazy { HOLDER.INSTANCE }
    }
}
