package sample;

import clock.ServerWork;
import clock.Time;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import database.DataBaseHelper;
import events.Observer;

import java.io.*;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

public class ClockObserver extends Thread implements Observer
{
    Socket socket;
    ServerWork serverWork;
    OutputStream outputStream;
    InputStream inputStream;
    DataInputStream dataInputStream;
    DataOutputStream dataOutputStream;
    
    Gson gson = new GsonBuilder().setPrettyPrinting().create();
    DataBaseHelper db = new DataBaseHelper();
    
    public ClockObserver(Socket socket, ServerWork serverWork) throws Exception
    {
        this.socket = socket;
        this.serverWork = serverWork;
        try
        {
            outputStream = this.socket.getOutputStream();
            dataOutputStream = new DataOutputStream(outputStream);
        }
        catch (IOException ex)
        {
            Logger.getLogger(ClockObserver.class.getName()).log(Level.SEVERE, null, ex);
        }
        serverWork.AddO(this);
        this.start();
        InitDB();

        serverWork.SetDB(db);
        Update("time:" + serverWork.GetTime().toString());
        Update(serverWork.GetAlarms());
        Update(serverWork.StartAlarm());
    }

    private void InitDB()
    {
        db.DataBaseConnect();
        db.CreateTable();
    }

    public void Send(String s)
    {
        try
        {
            dataOutputStream.writeUTF(s);
        } catch (IOException ex)
        {
            Logger.getLogger(ClockObserver.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    @Override
    public void run()
    {
        try
        {
            inputStream = socket.getInputStream();
            dataInputStream = new DataInputStream(inputStream);
            
            while (true)
            {
                String obj = dataInputStream.readUTF();
                Msg msg = gson.fromJson(obj, Msg.class);
                String al = msg.GetMsg();
                try
                {
                    if (al.startsWith("Alarm:"))
                    {
                        int prevCurInd = 6;
                        int curInd = al.indexOf(":", 6) - 1;
                        int hour = Integer.parseInt(al.substring(prevCurInd, curInd));
                        prevCurInd = curInd + 3;
                        curInd = al.indexOf(":", prevCurInd) - 1;
                        int minute = Integer.parseInt(al.substring(prevCurInd, curInd));
                        prevCurInd = curInd + 3;
                        int second = Integer.parseInt(al.substring(prevCurInd));
                        serverWork.Add(new Time(hour, minute, second));
                        //serverWork.Add(StringToTime(al.substring(6)));
                    }
                    else if (al.startsWith("clockRun: "))
                    {
                        switch (al.substring(10))
                        {
                            case "resume":
                                serverWork.ChangeThreadState(ThreadState.Start);
                                break;
                            case "stop":
                                serverWork.ChangeThreadState(ThreadState.Stop);
                                break;
                            case "pause":
                                serverWork.ChangeThreadState(ThreadState.Pause);
                                break;
                        }
                    } else if (al.startsWith("Remove:"))
                    {
                        serverWork.RemoveAlarm(al.substring(7));
                    } else if (al.startsWith("resume:"))
                    {
                        serverWork.UpdateAll();
                    }


                }
                catch (IOException ignored)
                {}
                catch (Exception e)
                {
                    e.printStackTrace();
                }
            }
        }
        catch (IOException ex)
        {
            Logger.getLogger(ClockObserver.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    @Override
    public void Update(String message)
    {
        Send(message);
    }
}
