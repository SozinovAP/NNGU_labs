package com.example.pract_ms_5

import android.view.View
import android.view.ViewGroup
import android.widget.BaseAdapter
import android.widget.TextView

class ListViewAdapterAR : BaseAdapter() {
    private val lastIndex = 0;
    private val itemList = ArrayList<Pair<String, Int>>();

    override fun getCount(): Int {
        return itemList.size;
    }

    override fun getItem(position: Int): Any {
        return itemList[position];
    }

    override fun getItemId(position: Int): Long {
        return 0;
    }

    override fun getView(position: Int, convertView: View?, parent: ViewGroup?): View {
        val view = super.getView(position, convertView, parent);
        view.setBackgroundColor(arrayValues[position].first);
        val tv = view.findViewById<TextView>(android.R.id.text1);
        tv.setTextColor(arrayValues[position].second);
        tv.text = arrayValues[position].third;
        return view;
    }
}