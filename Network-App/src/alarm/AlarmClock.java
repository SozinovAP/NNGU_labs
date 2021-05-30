package alarm;


import clock.Time;
import events.EventManager;
import events.EventType;

import java.sql.SQLException;
import java.util.ArrayList;


public class AlarmClock implements Alarm
{
    protected ArrayList<Time> alarms;
    public EventManager events;

    public AlarmClock()
    {
        this.alarms = new ArrayList<>();
        this.events = new EventManager(EventType.AlarmStarted, EventType.AlarmRemoved, EventType.AlarmAdded);
    }

    public AlarmClock(ArrayList<Time> times)
    {
        this.alarms = times;
        Sort();
        this.events = new EventManager(EventType.AlarmStarted, EventType.AlarmRemoved, EventType.AlarmAdded);
    }

    @Override
    public void CheckAlarm(Time time) throws SQLException
    {
        if (alarms.contains(time))
            StartAlarm(time);
    }

    @Override
    public void StartAlarm(Time time) throws SQLException
    {
        System.out.println("Alarm!!!");
        RemoveAlarm(time);
        events.notify(EventType.AlarmStarted, time.toString());
    }

    @Override
    public void AddAlarm(int _h, int _m, int _s) throws SQLException
    {
        if (!alarms.contains(new Time(_h, _m, _s))) {
            alarms.add(new Time(_h, _m, _s));
            Sort();
        }
        events.notify(EventType.AlarmAdded, new Time(_h, _m, _s).toString());
    }

    @Override
    public void AddAlarm(Time time) throws SQLException
    {
        if (!alarms.contains(time))
        {
            alarms.add(time);
            Sort();
        }
        events.notify(EventType.AlarmAdded, time.toString());
    }

    @Override
    public void Sort()
    {
        alarms.sort((o1, o2) -> {
            if (o1.GetFirst() < o2.GetFirst())
                return -1;
            else if (o1.GetFirst() > o2.GetFirst())
                return 1;
            else {
                if (o1.GetSecond() < o2.GetSecond())
                    return -1;
                else if (o1.GetSecond() > o2.GetSecond())
                    return 1;
                else {
                    return Integer.compare(o1.GetThird(), o2.GetThird());
                }
            }
        });
    }

    @Override
    public void RemoveAlarm(Time time) throws SQLException
    {
        alarms.remove(time);
        events.notify(EventType.AlarmRemoved, time.toString());
    }

    @Override
    public void RemoveAlarm(String time) throws SQLException
    {
        int prevCurInd = 0;
        int curInd = time.indexOf(":") - 1;
        int cHour = Integer.parseInt(time.substring(prevCurInd, curInd));
        prevCurInd = curInd + 3;
        curInd = time.indexOf(":", prevCurInd) - 1;
        int cMinute = Integer.parseInt(time.substring(prevCurInd, curInd));
        prevCurInd = curInd + 3;
        int cSecond = Integer.parseInt(time.substring(prevCurInd));
        alarms.remove(new Time(cHour, cMinute, cSecond));
        //alarms.remove(StringToTime(time));
        events.notify(EventType.AlarmRemoved, time);
    }

    @Override
    public ArrayList<String> GetList()
    {
        ArrayList<String> res = new ArrayList<>();

        alarms.forEach(alarm -> res.add(alarm.GetFirst() + " : " + alarm.GetSecond() + " : " + alarm.GetThird()));
        return res;
    }

    @Override
    public ArrayList<Time> GetAlarms()
    {
        return alarms;
    }

}
