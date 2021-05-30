package com.example.praact_ms_8

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.webkit.WebView
import android.webkit.WebViewClient
import android.widget.EditText
import android.widget.TextView


class PutRequestActivity : AppCompatActivity() {
    private val url = "http://httpbin.org/put";

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_put_request)

        viewArray.AddView(findViewById(R.id.textView_put));
    }

    fun PutRequest(view: View)
    {
        val task = HttpReqPutTask();
        task.execute(Triple(url, findViewById<EditText>(R.id.editText_put).text.toString(), 3));
        findViewById<EditText>(R.id.editText_put).text.clear();
    }
}
