package com.example.pract_ms_5

import android.os.AsyncTask
import com.example.pract_ms_4.RVAdapter
import org.w3c.dom.Document
import org.w3c.dom.Element
import org.w3c.dom.Node
import org.w3c.dom.NodeList
import org.xml.sax.InputSource
import java.net.URL
import javax.xml.parsers.DocumentBuilder
import javax.xml.parsers.DocumentBuilderFactory

class XMLParser : AsyncTask<String, Void, ArrayList<Pair<String, String>>>() {

    override fun doInBackground(vararg urls: String): ArrayList<Pair<String, String>>? {
        exchangeRates.clear();

        try {
            for (curUrl in urls)
            {
                val url = URL(curUrl);
                val dbf: DocumentBuilderFactory = DocumentBuilderFactory.newInstance();
                val db: DocumentBuilder = dbf.newDocumentBuilder();
                val doc: Document = db.parse(InputSource(url.openStream()));
                doc.documentElement.normalize();
                val nodeList: NodeList = doc.getElementsByTagName("Valute");

                for (i in 0 until nodeList.length) {
                    var country: String;
                    var course: String;
                    val node: Node = nodeList.item(i);
                    val curElem: Element = node as Element;
                    var nameList: NodeList = curElem.getElementsByTagName("Name");
                    var courseList: NodeList = curElem.getElementsByTagName("Value");
                    val nameElement: Element = nameList.item(0) as Element;
                    val courseElem: Element = courseList.item(0) as Element;
                    nameList = nameElement.childNodes;
                    courseList = courseElem.childNodes;
                    country = (nameList.item(0) as Node).nodeValue.toString();
                    course = (courseList.item(0) as Node).nodeValue.toString();
                    exchangeRates.add(Pair(country, course));
                }
            }
        } catch (e: Exception) {
            println("XML Pasing Excpetion = $e")
        }
        return exchangeRates;
    }

    override fun onPostExecute(res: ArrayList<Pair<String, String>>)
    {
        exchangeRates = res;
        exchangeRates.sortWith(Comparator { o1: Pair<String, String>, o2: Pair<String, String> ->
            when {
                o1.first < o2.first -> return@Comparator -1
                o1.first == o2.first -> return@Comparator 0
                else -> return@Comparator 1
            };
        });
        val adapter = exchangeRates.let { RVAdapter(it) };
        recView?.adapter = adapter;
    }
}