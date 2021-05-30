package database;

import alarm.AlarmClock;

import java.sql.*;
import java.util.ArrayList;

public class DataBaseHelper
{
    static public final String ALARM_TABLE_NAME = "AlarmTable";
    static public final String TIME = "time";
    static private Connection connection;

    public void DataBaseConnect()
    {
        try {
            Class.forName("org.sqlite.JDBC");
            connection = DriverManager.getConnection("jdbc:sqlite:C:\\Users\\alexs\\IdeaProjects\\untitled\\database.db");
            if (connection != null) {
                DatabaseMetaData meta = connection.getMetaData();
                System.out.println("The driver name is " + meta.getDriverName());
            }
        }
        catch (SQLException | ClassNotFoundException e)
        {
            e.printStackTrace();
        }
    }

    public void CreateTable()
    {
        try
        {
            Statement statement = connection.createStatement();

            statement.execute("CREATE TABLE IF NOT EXISTS " + ALARM_TABLE_NAME + " (" +
                    TIME +" TEXT NOT NULL, " +
                    "PRIMARY KEY ("+ TIME +")" +
                    ");");

        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
    }

    public clock.Time GetAlarm(String time) throws SQLException
    {
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery("SELECT " + TIME + " FROM " +
                ALARM_TABLE_NAME + " WHERE " + TIME + " = '" + time + "';");

        if (!resultSet.next())
        {
            return null;
        }
        else
            {
            return new clock.Time(resultSet.getString(TIME));
        }
    }

    public AlarmClock GetAlarms() throws SQLException
    {
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery("SELECT " + TIME + " FROM " + ALARM_TABLE_NAME + ";");

        ArrayList<clock.Time> alarms = new ArrayList<>();
        while (resultSet.next())
        {
            String time = resultSet.getString(TIME);
            alarms.add(new clock.Time(time));
        }

        return new AlarmClock(alarms);
    }

    public Statement createStatement() throws SQLException
    {
        return connection.createStatement();
    }

    public void InsertReplaceAlarm(String time)
    {
        Statement statement;
        try
        {
            statement = connection.createStatement();

            statement.execute("INSERT OR REPLACE INTO " + ALARM_TABLE_NAME +
                    " (" + TIME + ")" +
                    "VALUES('" + time + "');"
            );
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }

    }

    public void RemoveAlarm(String time)
    {
        Statement statement;
        try
        {
            statement = connection.createStatement();

            statement.execute("DELETE FROM " + ALARM_TABLE_NAME + " WHERE "
                    + TIME + " = '" + time + "';");

        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }

    }
}
