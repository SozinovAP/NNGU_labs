package com.example.pract_ms_4

import android.icu.text.SimpleDateFormat
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.cardview.widget.CardView
import androidx.recyclerview.widget.RecyclerView
import com.example.pract_ms_5.R
import java.util.*


class RVAdapter  internal constructor(note: List<Pair<String, String>>): RecyclerView.Adapter<RVAdapter.PersonViewHolder>() {
    class PersonViewHolder internal constructor(itemView: View) : RecyclerView.ViewHolder(itemView) {
        var cardView: CardView = itemView.findViewById(R.id.cardView);
        var country: TextView;
        var value: TextView;

        init {
            country = itemView.findViewById(R.id.country);
            value = itemView.findViewById(R.id.value);
        }
    }

    private var note: List<Pair<String, String>> = note;

    override fun onCreateViewHolder(viewGroup: ViewGroup, i: Int): PersonViewHolder {
        val v: View = LayoutInflater.from(viewGroup.context).inflate(R.layout.card_view_pattern, viewGroup, false);
        return PersonViewHolder(v);
    }

    override fun onBindViewHolder(personViewHolder: PersonViewHolder, i: Int) {
        personViewHolder.country.text = note[i].first;
        personViewHolder.value.text = note[i].second;
    }

    override fun getItemCount(): Int {
        return note.size;
    }

}