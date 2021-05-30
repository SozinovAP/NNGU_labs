package com.example.pract_ms_4

import android.annotation.SuppressLint
import android.content.Intent
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.view.View
import android.webkit.WebView
import android.webkit.WebViewClient
import android.widget.EditText


class WebViewActivity : AppCompatActivity() {
    private lateinit var webView: WebView;

    @SuppressLint("SetJavaScriptEnabled")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_web_view)

        webView = findViewById(R.id.web_view);
        webView.webViewClient = SimpleWebViewClient();

        webView.settings.javaScriptEnabled = true;
    }

    fun NextTask(view: View)
    {
        val newAct = Intent(this, SlideShowActivity::class.java);
        newAct.putExtra("tasks", intent.getSerializableExtra("tasks") as ArrayList<Note>);
        startActivity(newAct);
    }

    fun PrevTask(view: View)
    {
        this.finish();
    }

    fun OpenSite(view: View)
    {
        var url = findViewById<EditText>(R.id.input_url).text.toString();
        if (url.indexOf("https://") != 0 || url.indexOf("http://") != 0)
            url = "https://$url";

        webView.loadUrl(url);
    }

    override fun onBackPressed() {
        if (webView.canGoBack()) {
            webView.goBack()
        } else {
            super.onBackPressed()
        }
    }

}

private class SimpleWebViewClient : WebViewClient() {
    override fun shouldOverrideUrlLoading(webView: WebView, url: String): Boolean {
        return false
    }
}