package com.example.praact_ms_8

import android.os.AsyncTask
import android.widget.TextView
import java.io.BufferedReader
import java.io.IOException
import java.io.InputStreamReader
import java.net.HttpURLConnection
import java.net.URL

class HTTPReqTextTask : AsyncTask<Triple<String, RequestType, Int>, Void?, ArrayList<String>>() {
    var curButton = ArrayList<Int>();
    override fun doInBackground(vararg params: Triple<String, RequestType, Int>): ArrayList<String> {
        var urlConnection: HttpURLConnection? = null;
        val resReq = ArrayList<String>();
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
                    else -> {};
                }

                val code: Int = urlConnection.responseCode;
                if (code != 200) {
                    throw IOException("Invalid response from server: $code");
                }

                val readerString = BufferedReader(InputStreamReader(urlConnection.inputStream));
                var resString = "";
                var line: String?;
                while (readerString.readLine().also { line = it } != null) {
                    resString += line;
                }

                resReq.add(resString);
            }
        } catch (e: Exception) {
            e.printStackTrace();
        } finally {
            urlConnection?.disconnect();
        }
        return resReq;
    }

    override fun onPostExecute(res: ArrayList<String>)
    {
        for (ind in 0 until curButton.size)
        {
            val tv = viewArray.GetByIndex(curButton[ind]) as TextView;
            tv.text = res[ind];
        }

    }
}