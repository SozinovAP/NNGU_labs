package com.example.praact_ms_8

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View

val viewArray = ViewClassSingleTon.instance;

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        viewArray.AddView(findViewById(R.id.textView_get));
        viewArray.AddView(findViewById(R.id.textView_post));
        viewArray.AddView(findViewById(R.id.imageView_get));
    }

    fun GetRequest(view: View)
    {
        val task = HTTPReqTextTask();
        task.execute(Triple("http://httpbin.org/ip", RequestType.GET, 0));
    }

    fun PostRequest(view: View)
    {
        val task = HTTPReqTextTask();
        task.execute(Triple("http://httpbin.org/post", RequestType.POST, 1));
    }

    fun ImageRequest(view: View)
    {
        val task = HttpReqImgTask();
        task.execute(Triple("http://httpbin.org/image/png", RequestType.GET, 2));
    }

    fun Next(view: View)
    {
        val newAct = Intent(this, PutRequestActivity::class.java);
        startActivity(newAct);
    }

}