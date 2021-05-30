package com.example.pract_ms_5

import android.content.Intent
import android.os.Bundle
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView

var exchangeRates = ArrayList<Pair<String, String>>();
var recView: RecyclerView? = null;
class ExchangeRatesActivity : AppCompatActivity() {
    private lateinit var rv: RecyclerView;

    public override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_exchange_rates);
        val xmlParser = XMLParser();
        xmlParser.execute("https://www.cbr.ru/scripts/XML_daily.asp");
        SettingRecycleView();
    }

    private fun SettingRecycleView()
    {
        rv = findViewById(R.id.list_rates);
        rv.layoutManager = LinearLayoutManager(this);
        recView = rv;
    }

    fun NextTask(view: View)
    {
        val newAct = Intent(this, ExchangeRatesHttpRequestActivity::class.java);
        startActivity(newAct);
    }

    fun PrevTask(view: View)
    {
        this.finish();
    }

}
