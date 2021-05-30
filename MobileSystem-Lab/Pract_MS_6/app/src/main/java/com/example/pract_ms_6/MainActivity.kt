package com.example.pract_ms_6

import android.content.Intent
import android.graphics.PorterDuff
import android.os.Bundle
import android.os.Handler
import android.util.Log
import android.view.View
import android.view.animation.AnimationUtils
import android.widget.ImageView
import androidx.appcompat.app.AppCompatActivity
import androidx.core.content.res.ResourcesCompat
import com.example.pract_ms_6.TrafficLight.TrafficLightState
import java.util.*


class MainActivity : AppCompatActivity() {
    lateinit var redLight: ImageView;
    lateinit var greenLight: ImageView;
    lateinit var yellowLight: ImageView;
    var trafLight = TrafficLight();
    var index = 0;

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main);

        redLight = findViewById(R.id.red_light);
        yellowLight = findViewById(R.id.yellow_light);
        greenLight = findViewById(R.id.green_light);
        val person = findViewById<ImageView>(R.id.person);
        val anim = AnimationUtils.loadAnimation(this, R.anim.move_person);

        val timer = Timer();
        val changeTrafficLight: TimerTask = object : TimerTask() {
            override fun run() {
                index = (++index) % 3;
                val state = trafLight.ChangeTrafficLight();
                ChangeLight(state);
                if (state == TrafficLightState.GREEN) {
                    anim.duration = timeLight[2];
                    person.startAnimation(anim);
                }
            }
        }
        timer.schedule(changeTrafficLight, 1000, timeLight[index]);

    }

    fun ChangeLight(state: TrafficLightState?) {
        when (state) {
            TrafficLightState.RED -> {
                redLight.drawable.setColorFilter(
                    ResourcesCompat.getColor(
                        resources, R.color.red_light, null
                    ), PorterDuff.Mode.ADD
                );
                yellowLight.drawable.setColorFilter(
                    ResourcesCompat.getColor(
                        resources, R.color.inactive_light, null
                    ), PorterDuff.Mode.ADD
                );
                greenLight.drawable.setColorFilter(
                    ResourcesCompat.getColor(
                        resources, R.color.inactive_light, null
                    ), PorterDuff.Mode.ADD
                );
            }
            TrafficLightState.YELLOW -> {
                redLight.drawable.setColorFilter(
                    ResourcesCompat.getColor(
                        resources, R.color.inactive_light, null
                    ), PorterDuff.Mode.ADD
                );
                yellowLight.drawable.setColorFilter(
                    ResourcesCompat.getColor(
                        resources, R.color.yellow_light, null
                    ), PorterDuff.Mode.ADD
                );
                greenLight.drawable.setColorFilter(
                    ResourcesCompat.getColor(
                        resources, R.color.inactive_light, null
                    ), PorterDuff.Mode.ADD
                );
            }
            TrafficLightState.GREEN -> {
                redLight.drawable.setColorFilter(
                    ResourcesCompat.getColor(
                        resources, R.color.inactive_light, null
                    ), PorterDuff.Mode.ADD
                );
                yellowLight.drawable.setColorFilter(
                    ResourcesCompat.getColor(
                        resources, R.color.inactive_light, null
                    ), PorterDuff.Mode.ADD
                );
                greenLight.drawable.setColorFilter(
                    ResourcesCompat.getColor(
                        resources, R.color.green_light, null
                    ), PorterDuff.Mode.ADD
                );
            }
            else -> Log.e("TrafficLightFragment", "Invalid TrafficLightState")
        }
    }

    fun NextTask(view: View)
    {
        val newAct = Intent(this, AnimateTextActivity::class.java);
        startActivity(newAct);
    }
}