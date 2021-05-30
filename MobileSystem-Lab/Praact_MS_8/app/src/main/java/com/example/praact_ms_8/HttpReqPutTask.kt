package com.example.praact_ms_8

import android.os.AsyncTask
import android.widget.EditText
import android.widget.TextView
import java.io.BufferedReader
import java.io.IOException
import java.io.InputStreamReader
import java.io.OutputStreamWriter
import java.net.HttpURLConnection
import java.net.URL

class HttpReqPutTask : AsyncTask<Triple<String, String, Int>, Void?, ArrayList<String>>() {
    var curButton = ArrayList<Int>();
    override fun doInBackground(vararg params: Triple<String, String, Int>): ArrayList<String> {
        var urlConnection: HttpURLConnection? = null;
        val resReq = ArrayList<String>();
        try {
            for (curUrl in params)
            {
                curButton.add(curUrl.third);
                val url = URL(curUrl.first);
                urlConnection = url.openConnection() as HttpURLConnection;

                urlConnection.doOutput = true;
                urlConnection.requestMethod = "PUT";

                val out = OutputStreamWriter(urlConnection.outputStream);
                out.write(curUrl.second);
                out.close();

                val readerString = BufferedReader(InputStreamReader(urlConnection.inputStream));
                var line: String?;
                var linePrev = "";
                while (readerString.readLine().also { line = it } != null) {
                    if (linePrev.indexOf("\"form\"") != -1)
                    {
                        if (linePrev.indexOf("}") == -1)
                        {
                            line?.let { resReq.add(it) };
                            break;
                        }
                        else
                        {
                            resReq.add("form is EMPTY");
                            break;
                        }
                    }
                    linePrev = line.toString();
                }

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