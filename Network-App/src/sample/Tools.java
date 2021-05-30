package sample;

public class Tools {
    public static String TimeToString(clock.Time time)
    {
        return time.toString();
    }
    /*public static clock.Time StringToTime(String time)
    {
        int prevCurInd = 0;
        int curInd = time.indexOf(":") - 1;
        int hour = Integer.parseInt(time.substring(prevCurInd, curInd));
        prevCurInd = curInd + 3;
        curInd = time.indexOf(":", prevCurInd) - 1;
        int minute = Integer.parseInt(time.substring(prevCurInd, curInd));
        prevCurInd = curInd + 3;
        int second = Integer.parseInt(time.substring(prevCurInd));
        return new clock.Time(hour, minute, second);
    }*/
}
