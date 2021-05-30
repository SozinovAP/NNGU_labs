package clock;

import alarm.AlarmClock;
import events.EventManager;
import events.EventType;

import java.sql.SQLException;

public abstract class BaseClock
{
    protected String mark;
    protected int cost;
    protected AlarmClock alarmsClocks;
    protected TypeClock type;
    public EventManager events;

    public BaseClock(int _cost, String _mark)
    {
        this.mark = _mark;
        this.cost = _cost;
        this.alarmsClocks = new AlarmClock();
        this.events = new EventManager(EventType.TimeChanged);
    }

    public abstract void SetTimeByField(Field type, int val) throws SQLException;

    public abstract void SetTime(String time);

    public abstract void MovingClock(Field type, int val);

    public abstract String toString();

    public abstract int GetTimeInSec();

    public abstract Time GetTime();

    public abstract String GetTimeByField(Field type);

    public abstract void AddAlarm(int _hour, int _minute, int _second) throws Exception;

    public abstract void AddAlarm(Time time) throws Exception;

    public int GetCost()
    {
        return cost;
    }

    public String GetMark()
    {
        return mark;
    }

    public TypeClock GetType() {
        return type;
    }

    public AlarmClock GetAlarms() {
        return alarmsClocks;
    }
}
