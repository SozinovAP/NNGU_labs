package com.example.pract_ms_2

import android.app.AlertDialog
import android.content.Intent
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.widget.EditText
import android.widget.Toast


class CountSum : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_count_sum)
    }

    fun ToActionRec(view: View)
    {
        val newAct = Intent(this, ActionRectangle::class.java);
        startActivity(newAct);
    }

    fun CalcDialog(view: View) {
        val promptsView = LayoutInflater.from(applicationContext).inflate(R.layout.calc_dialog, null);
        val alertDialogBuilder = AlertDialog.Builder(this);
        alertDialogBuilder.setView(promptsView);

        alertDialogBuilder.setCancelable(true)
                .setPositiveButton(getString(R.string.text_apply)
                ) { _, _ ->
                    val first = promptsView.findViewById<EditText>(R.id.first_num).text.toString();
                    val second = promptsView.findViewById<EditText>(R.id.second_num).text.toString();
                    if (first.isNotEmpty() && second.isNotEmpty()) {
                        val sum = Integer.parseInt(first) + Integer.parseInt(second);
                        Toast.makeText(applicationContext, "Summa: " + sum.toString(), Toast.LENGTH_LONG).show();
                        Log.d("summa", sum.toString());
                    }
                }
                .setNegativeButton(getString(R.string.text_cancel)
                ) { dialog, id -> dialog.cancel() };
        alertDialogBuilder.create().show();
    }
}