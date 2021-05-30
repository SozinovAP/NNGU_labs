package com.example.pract_ms_5

import android.content.Intent
import android.content.SharedPreferences
import android.content.SharedPreferences.Editor
import android.os.Bundle
import android.text.Editable
import android.text.TextWatcher
import android.view.View
import android.widget.CheckBox
import android.widget.EditText
import androidx.appcompat.app.AppCompatActivity


class ConfigSaveActivity : AppCompatActivity() {
    lateinit var textOp1: EditText;
    lateinit var textOp2: EditText;
    lateinit var checkOp1: CheckBox;
    lateinit var checkOp2: CheckBox;

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_config_save)

        val settings: SharedPreferences = applicationContext.getSharedPreferences("data", 0);
        val editor: Editor = settings.edit();

        val editText1ID = "text_option_1";
        val checkBox1ID = "checkBox_1";
        val editText2ID = "text_option_2";
        val checkBox2ID = "checkBox_2";

        textOp1 = findViewById(R.id.text_option_1);
        textOp1.addTextChangedListener(object : TextWatcher {
            override fun beforeTextChanged(s: CharSequence, start: Int, count: Int, after: Int) {}
            override fun onTextChanged(s: CharSequence, start: Int, before: Int, count: Int) {
                editor.putString(editText1ID, s.toString()).apply();
            }

            override fun afterTextChanged(s: Editable) {}
        });

        textOp2 = findViewById(R.id.text_option_2);
        textOp2.addTextChangedListener(object : TextWatcher {
            override fun beforeTextChanged(s: CharSequence, start: Int, count: Int, after: Int) {}
            override fun onTextChanged(s: CharSequence, start: Int, before: Int, count: Int) {
                editor.putString(editText2ID, s.toString()).apply();
            }

            override fun afterTextChanged(s: Editable) {}
        });

        checkOp1 = findViewById(R.id.checkBox_1);
        checkOp1.setOnCheckedChangeListener { _, isChecked ->
            editor.putBoolean(checkBox1ID, isChecked).commit();
        }

        checkOp2 = findViewById(R.id.checkBox_2);
        checkOp2.setOnCheckedChangeListener { _, isChecked ->
            editor.putBoolean(checkBox2ID, isChecked).commit();
        }


        textOp1.setText(settings.getString(editText1ID, ""));
        checkOp1.isChecked = settings.getBoolean(checkBox1ID, false);
    }

    fun NextTask(view: View)
    {
        val newAct = Intent(this, ConfigSaveActivity::class.java);
        startActivity(newAct);
    }

    fun PrevTask(view: View)
    {
        this.finish();
    }
}