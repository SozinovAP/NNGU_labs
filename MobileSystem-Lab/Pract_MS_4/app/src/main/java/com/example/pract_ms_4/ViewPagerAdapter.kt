package layout

import android.annotation.SuppressLint
import android.content.Context
import android.icu.text.SimpleDateFormat
import android.support.v4.view.PagerAdapter
import android.support.v7.widget.CardView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.LinearLayout
import android.widget.TextView
import com.example.pract_ms_4.Note
import com.example.pract_ms_4.R
import java.util.*

class ViewPagerAdapter internal constructor(context: Context, note: List<Note>): PagerAdapter() {
    private var note: List<Note>;

    var context: Context;
    lateinit var inf: LayoutInflater;

    init {
        this.context = context;
        this.note = note;
    }
    override fun getCount(): Int {
        return note.size;
    }

    override fun isViewFromObject(p0: View, p1: Any): Boolean {
        return p0 == p1 as LinearLayout;
    }

    override fun instantiateItem(container: ViewGroup, position: Int): Any {
        inf = context.getSystemService(Context.LAYOUT_INFLATER_SERVICE) as LayoutInflater;
        val view = inf.inflate(R.layout.card_view_pattern, container, false);

        val sdfDate = SimpleDateFormat("d MMMM yyyy", Locale.getDefault());
        view.findViewById<TextView>(R.id.cv_date).text = sdfDate.format(note[position].date);
        view.findViewById<TextView>(R.id.description).text = note[position].description;
        container.addView(view);
        return view;
    }

    override fun destroyItem(container: ViewGroup, position: Int, `object`: Any) {
        container.removeView(`object` as LinearLayout);
    }
}