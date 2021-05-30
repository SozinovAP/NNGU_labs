package alarm;


import clock.Time;

import java.sql.SQLException;
import java.util.ArrayList;

public interface Alarm
{
    void CheckAlarm(Time time) throws SQLException;

    void StartAlarm(Time time) throws SQLException;

    void AddAlarm(int _h, int _m, int _s) throws SQLException;

    void AddAlarm(Time time) throws SQLException;

    void Sort();

    void RemoveAlarm(Time time) throws SQLException;

    void RemoveAlarm(String time) throws SQLException;

    ArrayList<String> GetList();

    ArrayList<Time> GetAlarms();
}
