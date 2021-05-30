package com.example.praact_ms_8

import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.os.AsyncTask
import android.widget.ImageView
import java.io.IOException
import java.net.HttpURLConnection
import java.net.URL

class HttpReqImgTask : AsyncTask<Triple<String, RequestType, Int>, Void?, ArrayList<Bitmap>>() {
    var curButton = ArrayList<Int>();
    override fun doInBackground(vararg params: Triple<String, RequestType, Int>): ArrayList<Bitmap> {
        var urlConnection: HttpURLConnection? = null;
        val resReq = ArrayList<Bitmap>();
        try {
            for (curUrl in params)
            {
                curButton.add(curUrl.third);
                val url = URL(curUrl.first);
                urlConnection = url.openConnection() as HttpURLConnection;

                when (curUrl.second)
                {
                    RequestType.GET -> urlConnection.requestMethod = "GET";
                    RequestType.POST -> urlConnection.requestMethod = "POST";
                }

                val code: Int = urlConnection.responseCode;
                if (code != 200) {
                    throw IOException("Invalid response from server: $code");
                }

                val bitmap = BitmapFactory.decodeStream(urlConnection.inputStream);
                resReq.add(bitmap);
            }
        } catch (e: Exception) {
            e.printStackTrace();
        } finally {
            urlConnection?.disconnect();
        }
        return resReq;
    }

    override fun onPostExecute(res: ArrayList<Bitmap>)
    {
        for (ind in 0 until curButton.size)
        {
            val imageView = viewArray.GetByIndex(curButton[ind]) as ImageView;
            imageView.setImageBitmap(res[ind]);
        }

    }
}