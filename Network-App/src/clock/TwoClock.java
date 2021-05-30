package clock;

import events.EventType;

import java.sql.SQLException;

public class TwoClock extends BaseClock
{
    protected int hour;
    protected int minute;

    public TwoClock(int _cost, String _mark)
    {
        super(_cost, _mark);
        this.hour = 0;
        this.minute = 0;
        this.type = TypeClock.TwoArrows;
    }

    public TwoClock(int _cost, String _mark, int _hour, int _minute) throws SQLException
    {
        super(_cost, _mark);
        if (_hour < 0 || _hour > 23) {
            this.hour = 0;
        }
        this.hour = _hour;

        if (_minute < 0 || _minute > 60)
            this.minute = 0;
        else
            this.minute = _minute;
        this.type = TypeClock.TwoArrows;
        alarmsClocks.CheckAlarm(new Time(this.hour, this.minute, 0));
    }

    @Override
    public void SetTimeByField(Field type, int val) throws SQLException
    {
        if (type == Field.H)
        {
            if (val < 0 || val > 23)
                val = 0;
            this.hour = val;
        }
        else if (type == Field.M)
        {
            if (val < 0 || val > 59)
                val = 0;
            this.minute = val;
        }
        alarmsClocks.CheckAlarm(new Time(this.hour, this.minute, 0));
    }

    @Override
    public void SetTime(String time)
    {
        int prevCurInd = 0;
        int curInd = time.indexOf(":") - 1;
        this.hour = Integer.parseInt(time.substring(prevCurInd, curInd));
        prevCurInd = curInd + 3;
        this.minute = Integer.parseInt(time.substring(prevCurInd));
    }

    public void SetTime(int _hour) throws Exception
    {
        try {
            if (_hour < 0 || _hour > 23)
                throw new Exception("SetTime: Incorrect time!");

            this.hour = _hour;
            this.minute = 0;
            alarmsClocks.CheckAlarm(new Time(this.hour, this.minute, 0));
        }
        catch (Exception e)
        {
            System.out.println(e.toString());
        }
    }

    public void SetTime(int _hour, int _minute) throws Exception
    {
        try {
            if (_hour < 0 || _hour > 23 || _minute < 0 || _minute > 59)
                throw new Exception("SetTime: Incorrect time!");

            this.hour = _hour;
            this.minute = _minute;
            alarmsClocks.CheckAlarm(new Time(this.hour, this.minute, 0));
        }
        catch (Exception e)
        {
            System.out.println(e.toString());
        }
    }

    @Override
    public void MovingClock(Field type, int val)
    {
        try {
            if (type == Field.H)
            {
                if (val < 0 || val > 23)
                    throw new Exception("MovingClock: Incorrect time!");
                this.hour = (this.hour + val) % 24;

            }
            else if (type == Field.M)
            {
                if (val < 0 || val > 59)
                    throw new Exception("MovingClock: Incorrect time!");
                MovingClock(Field.H, (this.minute + val) / 60);
                this.minute = (this.minute + val) % 60;
            }
            events.notify(EventType.TimeChanged, GetTime().toString());
        }
        catch (Exception e)
        {
            System.out.println(e.toString());
        }
    }

    @Override
    public String toString()
    {
        return hour + " : " + minute;
    }

    @Override
    public int GetTimeInSec()
    {
        return this.hour * 60 * 60 + this.minute * 60;
    }

    @Override
    public Time GetTime()
    {
        return new Time(this.hour, this.minute, 0);
    }

    @Override
    public String GetTimeByField(Field type)
    {
        if (type == Field.H)
            return  String.valueOf(this.hour);
        else if (type == Field.M)
            return  String.valueOf(this.minute);
        return "";
    }

    @Override
    public void AddAlarm(int _hour, int _minute, int _second)
    {
        try{
            if (_hour < 0 || _hour > 23 || _minute < 0 || _minute > 59)
                throw new Exception("AddAlarm: Incorrect time!");

            alarmsClocks.AddAlarm(_hour, _minute, 0);
            alarmsClocks.CheckAlarm(new Time(this.hour, this.minute, 0));
        }
        catch (Exception e)
        {
            System.out.println(e.toString());
        }
    }

    @Override
    public void AddAlarm(Time time) throws SQLException
    {
        alarmsClocks.AddAlarm(time);
        alarmsClocks.CheckAlarm(new Time(this.hour, this.minute, 0));
    }
}
