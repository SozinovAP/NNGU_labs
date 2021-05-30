package visual;

import clock.BaseClock;
import clock.Field;
import clock.UserClock;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import sample.Msg;
import sample.ThreadState;
import unused.ClockRunnable;

import java.io.*;
import java.net.InetAddress;
import java.net.Socket;
import java.net.URL;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;

public class ControllerClient implements Initializable {
    public javafx.scene.layout.AnchorPane AnchorPane;
    public Label hour;
    public Label minute;
    public Label second;
    public ListView<String> alarmsView;
    public Button setTime;
    public Button alarm;
    public Button startClock;
    public Button pauseClock;
    public Button workWithClient;
    public TextField alarmHour;
    public TextField alarmMinute;
    public TextField alarmSecond;
    public CheckBox hasSecond;
    private UserClock clock;
    private boolean flagClientStatus = false;
    public final static ClockRunnable runnable = new ClockRunnable();
    public Thread thread = new Thread(runnable);
    Socket socket;
    private ThreadState state;

    OutputStream outputStream;
    InputStream inputStream;
    DataInputStream dataInputStream;
    DataOutputStream dataOutputStream;
    public Thread t;

    int port = 8001;
    InetAddress host;

    Gson gson = new GsonBuilder().setPrettyPrinting().create();

    @FXML
    private void StartAlarm(String time)
    {
        System.out.println("ALARM");
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Alarm!");
        alert.setHeaderText("Alarm: " + time);
        alert.show();
    }

    @FXML
    public void CheckStatus()
    {
        second.setDisable(!hasSecond.isSelected());
    }

    @FXML
    private void CreateNewAlarm(ActionEvent event) {
        if (!(alarmHour.getText().isEmpty() || alarmMinute.getText().isEmpty() ||
                (hasSecond.isSelected() && alarmSecond.getText().isEmpty())))
        {
            try{
                Msg msg = new Msg();

                String message = alarmHour.getText() + " : " + alarmMinute.getText() + " : " +
                        (hasSecond.isSelected() ? alarmSecond.getText() : "0");

                msg.SetMsg("Alarm:" + message);
                String jsString = gson.toJson(msg);
                dataOutputStream.writeUTF(jsString);

                alarmHour.clear();
                alarmMinute.clear();
                alarmSecond.clear();
            }
            catch(Exception ignored) {}
        }
    }

    @FXML
    private void SetTime(ActionEvent event) {
        if (!(hour.getText().isEmpty() || minute.getText().isEmpty() ||
                (hasSecond.isSelected() && second.getText().isEmpty())))
        {
            try {
                BaseClock clock = UserClock.getInstance().GetClock().get(0);

                clock.SetTimeByField(Field.H, Integer.parseInt(hour.getText()));
                clock.SetTimeByField(Field.M, Integer.parseInt(minute.getText()));
                if (hasSecond.isSelected())
                    clock.SetTimeByField(Field.S, Integer.parseInt(second.getText()));
                hour.setText("");
                minute.setText("");
                second.setText("");
            }
            catch(Exception ignored) {}
        }
    }

    @FXML
    private void ConnectDisconnect(ActionEvent event) throws IOException {
        if (!flagClientStatus)
        {
            state = ThreadState.Start;
            flagClientStatus = true;
            ActivateUI();
            workWithClient.setDisable(true);
            try {
                try {
                    host = InetAddress.getLocalHost();
                    System.out.println(host);
                    System.out.println(port);
                } catch (UnknownHostException ex) {
                    Logger.getLogger(ControllerClient.class.getName()).log(Level.SEVERE, null, ex);
                }

                socket = new Socket(host, port);
                outputStream = socket.getOutputStream();
                dataOutputStream = new DataOutputStream(outputStream);


                t = new Thread(() -> {
                    try {
                        inputStream = socket.getInputStream();
                        dataInputStream = new DataInputStream(inputStream);
                        while(true) {
                            String s = dataInputStream.readUTF();
                            System.out.println(s);
                            if (state == ThreadState.Start) {
                                if (s.startsWith("alarms:")) {
                                    Platform.runLater(() -> SetAlarm(s.substring(7)));
                                } else if (s.startsWith("time:")) {
                                    Platform.runLater(() -> PrintTime(s.substring(5)));
                                } else if (s.startsWith("start:")) {
                                Platform.runLater(() -> StartAlarm(s.substring(6)));
                            }
                            }
                        }
                    } catch (IOException ex) {
                        Logger.getLogger(ControllerClient.class.getName()).log(Level.SEVERE, null, ex);
                    } finally {
                        try {
                            inputStream.close();
                        } catch (IOException ex) {
                            Logger.getLogger(ControllerClient.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    }

                });
                t.start();

            } catch (IOException ex) {
                Logger.getLogger(ControllerClient.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    public void SetAlarm(String strAl)
    {
        ArrayList<String> alarmsList = new ArrayList<>();
        int prevPos = 0;
        int nextPos = strAl.indexOf("\n", prevPos + 1);
        while (nextPos != -1) {
            alarmsList.add(strAl.substring(prevPos, nextPos));
            prevPos = nextPos + 1;
            nextPos = strAl.indexOf("\n", prevPos + 1);
        }
        ObservableList<String> alarmList = FXCollections.observableList(alarmsList);
        alarmsView.setItems(alarmList);
    }

    public void PrintTime(String time)
    {
        int prevCurInd = 0;
        int curInd = time.indexOf(":") - 1;
        hour.setText(time.substring(prevCurInd, curInd));
        prevCurInd = curInd + 3;
        curInd = time.indexOf(":", prevCurInd) - 1;
        minute.setText(time.substring(prevCurInd, curInd));
        prevCurInd = curInd + 3;
        second.setText(time.substring(prevCurInd));
    }

    public void StartTime() throws IOException {
        startClock.setDisable(true);
        pauseClock.setDisable(false);

        System.out.println("start");
        state = ThreadState.Start;

        Msg msg = new Msg();

        msg.SetMsg("resume:" + " client");
        String jsString = gson.toJson(msg);
        try {
            dataOutputStream.writeUTF(jsString);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void PauseTime() throws IOException {
        startClock.setDisable(false);
        pauseClock.setDisable(true);

        System.out.println("pause");
        state = ThreadState.Pause;
    }

    public void StopTime() throws IOException {
        startClock.setDisable(false);
        pauseClock.setDisable(true);

        state = ThreadState.Stop;
    }

    public void ActivateUI()
    {
        startClock.setDisable(true);
        pauseClock.setDisable(false);
        alarmsView.setVisible(true);
        hour.setVisible(true);
        minute.setVisible(true);
        second.setVisible(true);
        setTime.setDisable(false);
        alarm.setDisable(false);
        alarmsView.setOnMouseClicked(event -> {
            System.out.println("clicked on " + alarmsView.getSelectionModel().getSelectedItem());
            Msg msg = new Msg();

            String time = alarmsView.getSelectionModel().getSelectedItem();

            msg.SetMsg("Remove:" + time);
            String jsString = gson.toJson(msg);
            try {
                dataOutputStream.writeUTF(jsString);
            } catch (IOException e) {
                e.printStackTrace();
            }
        });
    }

    public void DeactivateUI()
    {
        startClock.setDisable(false);
        pauseClock.setDisable(true);
        alarmsView.setVisible(false);
        hour.setVisible(false);
        minute.setVisible(false);
        second.setVisible(false);
        setTime.setDisable(true);
        alarm.setDisable(true);
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        clock = UserClock.getInstance();
    }

}
