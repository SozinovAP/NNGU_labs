package clock;

public class Time {

    private final int hour;
    private final int minute;
    private final int second;

    public Time(int hour, int minute, int second)
    {
        this.hour = hour;
        this.minute = minute;
        this.second = second;
    }

    public Time(String time)
    {
        int prevCurInd = 0;
        int curInd = time.indexOf(":") - 1;
        this.hour = Integer.parseInt(time.substring(prevCurInd, curInd));
        prevCurInd = curInd + 3;
        curInd = time.indexOf(":", prevCurInd) - 1;
        this.minute = Integer.parseInt(time.substring(prevCurInd, curInd));
        prevCurInd = curInd + 3;
        this.second = Integer.parseInt(time.substring(prevCurInd));
    }

    public int GetFirst() {
        return hour;
    }

    public int GetSecond() {
        return minute;
    }

    public int GetThird() {
        return second;
    }

    @Override
    public String toString()
    {
        return hour + " : " + minute + " : " + second;
    }

    @Override
    public boolean equals(Object o)
    {
        if (o == null)
            return false;
        if (o.getClass() != this.getClass())
            return false;
        final Time other = (Time)o;
        return (this.hour == other.hour) && (this.minute == other.minute) && (this.second == other.second);
    }
}
