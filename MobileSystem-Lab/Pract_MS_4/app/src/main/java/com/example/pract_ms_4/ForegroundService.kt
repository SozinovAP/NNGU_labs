package com.example.pract_ms_4

import android.app.*
import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.graphics.Color
import android.os.IBinder
import android.support.v4.app.NotificationCompat
import android.support.v4.content.ContextCompat


var channelId: String = "";
var counter: Int = 0;
class ForegroundService : Service() {

    override fun onStartCommand(intent: Intent?, flags: Int, startId: Int): Int {
        channelId = CreateNotification("exampleService", "My Background Service");

        val builder = NotificationCompat.Builder(this, channelId)
                .setSmallIcon(R.drawable.ic_launcher_background)
                .setContentTitle("Counter")
                .setContentText(counter.toString())
                .setPriority(NotificationCompat.PRIORITY_DEFAULT)
                .setAutoCancel(true);

        val broadcastIntentInc = Intent(this, ActionReceiver::class.java);
        broadcastIntentInc.putExtra("action", "Increment");
        val broadcastPendingIntentInc = PendingIntent.getBroadcast(this, 0,
                broadcastIntentInc, 0);
        builder.addAction(R.drawable.ic_launcher_foreground, "Increment", broadcastPendingIntentInc);

        val broadcastIntentDec = Intent(this, ActionReceiver::class.java);
        broadcastIntentDec.putExtra("action", "Decrement");
        val broadcastPendingIntentDec = PendingIntent.getBroadcast(this, 1,
                broadcastIntentDec, 0);
        builder.addAction(R.drawable.ic_launcher_foreground, "Decrement", broadcastPendingIntentDec);

        startForeground(101,
                builder.build())
        return START_STICKY
    }

    private fun CreateNotification(channelId: String, channelName: String): String{
        val chan = NotificationChannel(channelId,
                channelName, NotificationManager.IMPORTANCE_NONE)
        chan.lightColor = Color.BLACK
        chan.lockscreenVisibility = Notification.VISIBILITY_PRIVATE
        val service = getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager
        service.createNotificationChannel(chan)
        return channelId
    }
    override fun onDestroy() {
        super.onDestroy()
        stopForeground(true)
    }

    override fun onBind(intent: Intent?): IBinder? {
        return null
    }


    class ActionReceiver : BroadcastReceiver() {
        override fun onReceive(context: Context, intent: Intent) {
            val action = intent.getStringExtra("action")
            if (action == "Decrement") {
                Decrement(context)
            } else if (action == "Increment") {
                Increment(context)
            }
        }

        fun Decrement(context: Context) {
            --counter;
            ContextCompat.startForegroundService(context, Intent(context, ForegroundService::class.java))
        }
        fun Increment(context: Context) {
            ++counter;
            ContextCompat.startForegroundService(context, Intent(context, ForegroundService::class.java))
        }
    }
}