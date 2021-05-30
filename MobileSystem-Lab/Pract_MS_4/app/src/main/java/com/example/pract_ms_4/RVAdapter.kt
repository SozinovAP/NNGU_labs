package com.example.pract_ms_4

import android.icu.text.SimpleDateFormat
import android.provider.ContactsContract
import android.support.v7.widget.CardView
import android.support.v7.widget.RecyclerView
import android.support.v7.widget.RecyclerView.ViewHolder
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import java.util.*


class RVAdapter  internal constructor(note: List<Note>): RecyclerView.Adapter<RVAdapter.PersonViewHolder>() {
    class PersonViewHolder internal constructor(itemView: View) : ViewHolder(itemView) {
        var cardView: CardView = itemView.findViewById(R.id.cardView);
        var description: TextView;
        var date: TextView;

        init {
            description = itemView.findViewById(R.id.description);
            date = itemView.findViewById(R.id.cv_date);
        }
    }

    private var note: List<Note> = note;

    override fun onCreateViewHolder(viewGroup: ViewGroup, i: Int): PersonViewHolder {
        val v: View = LayoutInflater.from(viewGroup.context).inflate(R.layout.card_view_pattern, viewGroup, false);
        return PersonViewHolder(v);
    }

    override fun onBindViewHolder(personViewHolder: PersonViewHolder, i: Int) {
        val sdfDate = SimpleDateFormat("d MMMM yyyy", Locale.getDefault());
        personViewHolder.description.text = note[i].description;
        personViewHolder.date.text = sdfDate.format(note[i].date);
    }

    override fun getItemCount(): Int {
        return note.size;
    }

}