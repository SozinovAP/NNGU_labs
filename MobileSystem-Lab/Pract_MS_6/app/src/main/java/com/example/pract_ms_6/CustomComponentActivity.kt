package com.example.pract_ms_6

import android.R.attr.button
import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.RelativeLayout
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.constraintlayout.solver.state.State
import androidx.constraintlayout.widget.ConstraintLayout
import androidx.constraintlayout.widget.ConstraintSet


class CustomComponentActivity : AppCompatActivity() {
    lateinit var custComp: CustomComponent;
    var customBut: Button? = null;

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_custom_component)

        custComp = findViewById(R.id.custom_comp_1);
    }

    fun CreateNewButton(view: View)
    {
        val layout = findViewById<ConstraintLayout>(R.id.activity_custom_component_layout);

        val randText = custComp.GetRandomText();
        if (randText.isNullOrEmpty())
            Toast.makeText(applicationContext, "Failed: get text from component", Toast.LENGTH_SHORT).show();
        else
        {
            if (customBut == null) {
                customBut = Button(this);
                customBut!!.setBackgroundColor(custComp.GetColor());

                customBut!!.text = randText;
                customBut!!.id = R.id.random_button;
                layout.addView(customBut);
            }
            else
            {
                customBut!!.text = randText;
            }

            val set = ConstraintSet();
            set.clone(layout);
            set.connect(customBut!!.id, ConstraintSet.LEFT, layout.id, ConstraintSet.LEFT, 0);
            set.connect(customBut!!.id, ConstraintSet.RIGHT, layout.id, ConstraintSet.RIGHT, 0);
            set.connect(customBut!!.id, ConstraintSet.BOTTOM, findViewById<Button>(R.id.but_create).id, ConstraintSet.TOP, 20);
            set.applyTo(layout);
        };
    }

    fun NextTask(view: View)
    {
        val newAct = Intent(this, CustomTimePickerActivity::class.java);
        startActivity(newAct);
    }

    fun PrevTask(view: View)
    {
        this.finish();
    }
}