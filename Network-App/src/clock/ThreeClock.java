package clock;

import events.EventType;

import java.sql.SQLException;

public class ThreeClock extends TwoClock
{
    protected int second;

    public ThreeClock(int _cost, String _mark)
    {
        super(_cost, _mark);
        this.second = 0;
        this.type = TypeClock.ThreeArrows;
    }

    public ThreeClock(int _cost, String _mark, int _hour, int _minute, int _second) throws SQLException
    {
        super(_cost, _mark, _hour, _minute);
        if (_second < 0 || _second > 60)
            this.second = 0;
        else
            this.second = _second;
        this.type = TypeClock.ThreeArrows;
        alarmsClocks.CheckAlarm(new Time(this.hour, this.minute, this.second));
    }

    @Override
    public void SetTimeByField(Field type, int val) throws SQLException
    {
        super.SetTimeByField(type, val);

        if(type == Field.S)
        {
            if (val < 0 || val > 59)
                val = 0;
            this.second = val;
            alarmsClocks.CheckAlarm(new Time(this.hour, this.minute, this.second));
        }
    }

    public void SetTime(int _hour) throws Exception
    {
        this.second = 0;
        super.SetTime(_hour);
    }

    @Override
    public void SetTime(String time)
    {
        /*clock.Time t = StringToTime(time);
        this.hour = t.GetFirst();
        this.minute = t.GetSecond();
        this.second = t.GetThird();*/
        int prevCurInd = 0;
        int curInd = time.indexOf(":") - 1;
        this.hour = Integer.parseInt(time.substring(prevCurInd, curInd));
        prevCurInd = curInd + 3;
        curInd = time.indexOf(":", prevCurInd) - 1;
        this.minute = Integer.parseInt(time.substring(prevCurInd, curInd));
        prevCurInd = curInd + 3;
        this.second = Integer.parseInt(time.substring(prevCurInd));
    }

    public void SetTime(int _hour, int _minute) throws Exception
    {
        this.second = 0;
        super.SetTime(_hour, _minute);
    }

    public void SetTime(int _hour, int _minute, int _second)
    {
        try {
            if (_hour < 0 || _hour > 23 || _minute < 0 || _minute > 59 ||_second < 0 || _second > 59)
                throw new Exception("SetTime: Incorrect time!");
            this.hour = _hour;

            this.minute = _minute;
            this.second = _second;
            alarmsClocks.CheckAlarm(new Time(this.hour, this.minute, this.second));
        }
        catch (Exception e)
        {
            System.out.println(e.toString());
        }
    }

    @Override
    public void MovingClock(Field type, int val)
    {
        try
        {
            super.MovingClock(type, val);
            if (type == Field.S)
            {
                MovingClock(Field.M, (this.second + val) / 60);
                this.second = (this.second + val) % 60;
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
        return hour + " : " + minute + " : " + second;
    }

    @Override
    public String GetTimeByField(Field type)
    {
        if (type == Field.H)
            return  String.valueOf(this.hour);
        else if (type == Field.M)
            return  String.valueOf(this.minute);
        else if (type == Field.S)
            return  String.valueOf(this.second);
        return "";
    }

    @Override
    public int GetTimeInSec()
    {
        return this.hour * 60 * 60 + this.minute * 60 + this.second;
    }

    @Override
    public Time GetTime()
    {
        return new Time(this.hour, this.minute, this.second);
    }

    @Override
    public void AddAlarm(int _hour, int _minute, int _second)
    {
        try
        {
            if (_hour < 0 || _hour > 23 || _minute < 0 || _minute > 59 || _second < 0 || _second > 59)
                throw new Exception("AddAlarm: Incorrect time!");

            alarmsClocks.AddAlarm(_hour, _minute, _second);
            alarmsClocks.CheckAlarm(new Time(this.hour, this.minute, this.second));
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
        alarmsClocks.CheckAlarm(new Time(this.hour, this.minute, this.second));
    }
}
