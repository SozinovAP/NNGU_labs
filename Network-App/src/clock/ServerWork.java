package clock;

import alarm.AlarmClock;
import database.DataBaseHelper;
import events.EventType;
import events.Observer;
import sample.ThreadState;

import java.sql.SQLException;
import java.util.ArrayList;

public class ServerWork
{
    FactoryClock factory = new FactoryClock(100, "clock2");
    UserClock userClock = UserClock.getInstance();
    ArrayList<Observer> observers = new ArrayList<>();
    Thread thread;
    private final MyRunnable runnable = new MyRunnable();
    private boolean alarmsStart = false;
    private DataBaseHelper db;
    private boolean dbInit = false;

    public ServerWork()
    {

        userClock.SetClock(factory.GetClock(TypeClock.ThreeArrows));
        userClock.GetClock().get(0).GetAlarms().events.subscribe(EventType.AlarmStarted,
                (eventType, time) ->
                {
            alarmsStart = true;
            Update(StartAlarm());
                });
        userClock.GetClock().get(0).GetAlarms().events.subscribe(EventType.AlarmAdded,
                ((eventType, time) ->
                {
                    InsertAlarmToDB(time);
                    Update(GetAlarms());
                }));
        userClock.GetClock().get(0).GetAlarms().events.subscribe(EventType.AlarmRemoved,
                ((eventType, time) ->
                {
                    RemoveAlarmFromDB(time);
                    Update(GetAlarms());
                }));
        userClock.GetClock().get(0).events.subscribe(EventType.TimeChanged,
                (eventType, time) -> Update("time:" + GetTime().toString()));

        if (thread == null)
        {
            thread = new Thread(new MyRunnable());
            thread.start();
        }
    }

    public void SetDB(DataBaseHelper db) throws Exception
    {
        if (dbInit)
            return;
        this.db = db;

        dbInit = true;
        AlarmClock alarmsC = db.GetAlarms();
        if (alarmsC != null)
        {
            Add(alarmsC);
        }
    }

    void Update(String message)
    {
        for (Observer o : observers)
        {
            o.Update(message);
        }
    }

    public void ChangeThreadState(ThreadState state)
    {
        switch (state)
        {
            case Start:
                runnable.resume();
                break;
            case Stop:
                runnable.stop();
                break;
            case Pause:
                runnable.pause();
                break;
        }
    }

    public void Add(Time time) throws Exception
    {
        userClock.GetClock().get(0).AddAlarm(time);
        Update("time:" + GetTime().toString());
    }

    public void Add(AlarmClock alarmClock) throws Exception
    {
        for (Time time : alarmClock.GetAlarms())
            userClock.GetClock().get(0).AddAlarm(time);
        Update("time:" + GetTime().toString());
    }

    public Time GetTime()
    {
        return userClock.GetClock().get(0).GetTime();
    }

    public String GetAlarms() throws SQLException
    {
        StringBuilder alarms = new StringBuilder("alarms:");
        if (!dbInit)
            return alarms.toString();
        ArrayList list = db.GetAlarms().GetList();
        for (Object o : list)
        {
            alarms.append(o).append("\n");
        }
        return alarms.toString();
    }

    public void RemoveAlarm(String time) throws SQLException
    {
        userClock.GetClock().get(0).GetAlarms().RemoveAlarm(time);
    }

    public void UpdateAll() throws SQLException
    {
        Update(GetAlarms());
        Update(GetTime().toString());
    }

    public String StartAlarm()
    {
        if (alarmsStart)
        {
            alarmsStart = false;
            return "start:" + "Alarm! Time: " + GetTime().toString();
        }
        else
            return "";
    }

    public void AddO(Observer o)
    {
        observers.add(o);
    }

    private static class MyRunnable implements Runnable
    {

        private boolean runTask = true;
        private volatile boolean paused = false;
        private final Object pauseLock = new Object();
        private int tick = 0;

        private synchronized boolean keepRunning()
        {
            return !this.paused;
        }

        public void stop()
        {
            runTask = false;
            resume();
        }

        public void pause()
        {
            paused = true;
        }

        public void resume()
        {
            synchronized (pauseLock)
            {
                paused = false;
                pauseLock.notifyAll();
            }
        }

        @Override
        public void run()
        {
            BaseClock clock = null;
            if (!UserClock.getInstance().GetClock().isEmpty())
                clock = UserClock.getInstance().GetClock().get(0);

            while (runTask)
            {
                synchronized (pauseLock)
                {
                    if (!runTask)
                    {
                        break;
                    }
                    if (paused)
                    {
                        try
                        {
                            synchronized (pauseLock)
                            {
                                pauseLock.wait();
                            }
                        }
                        catch (InterruptedException ex)
                        {
                            break;
                        }
                        if (!runTask)
                        {
                            break;
                        }
                    }
                }

                tick = (++tick) % 60;
                assert clock != null;
                if (clock.GetType() == TypeClock.TwoArrows && tick == 0)
                {
                    clock.MovingClock(Field.M, 1);
                }
                else if (clock.GetType() == TypeClock.ThreeArrows)
                {
                    clock.MovingClock(Field.S, 1);
                }
                try {
                    clock.GetAlarms().CheckAlarm(clock.GetTime());
                } catch (SQLException e) {
                    e.printStackTrace();
                }

                try
                {
                    Thread.sleep(1000L);
                } catch (InterruptedException e)
                {
                    e.printStackTrace();
                }
            }
        }
    }

    public void RemoveAlarmFromDB(String time)
    {
        db.RemoveAlarm(time);
    }

    public void InsertAlarmToDB(String time)
    {
        db.InsertReplaceAlarm(time);
    }
}
