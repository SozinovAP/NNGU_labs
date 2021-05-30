package unused;

import clock.BaseClock;
import clock.Field;
import clock.UserClock;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import events.EventType;
import clock.TypeClock;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;


public class Controller implements Initializable{

    public AnchorPane AnchorPane;
    public Label hour;
    public Label minute;
    public Label second;
    public ListView<String> alarmsView;
    public Button setTime;
    public Button alarm;
    public Button startClock;
    public Button pauseClock;
    public Button stopClock;
    private UserClock clock;
    public final static ClockRunnable runnable = new ClockRunnable();
    public Thread thread = new Thread(runnable);

    @FXML
    private void StartAlarm(BaseClock clock)
    {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Alarm!");
        alert.setHeaderText("Alarm: " + clock.toString());
        alert.show();
    }

    @FXML
    private void CreateNewClock(ActionEvent event) throws IOException
    {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("createClock.fxml"));
        Parent parent = fxmlLoader.load();

        Scene scene = new Scene(parent);
        Stage stage = new Stage();
        stage.initModality(Modality.APPLICATION_MODAL);
        stage.setScene(scene);
        stage.setOnHidden(e -> DrawClock());
        stage.showAndWait();
        clock.GetClock().get(0).events.subscribe(EventType.TimeChanged, (eventType, index) -> PrintTime(clock.GetClock().get(0)));
        clock.GetClock().get(0).GetAlarms().events.subscribe(EventType.AlarmStarted,
                (eventType, index) -> {
            StartAlarm(clock.GetClock().get(0));
            SetAlarm();
        });
    }

    @FXML
    private void CreateNewAlarm(ActionEvent event) throws IOException
    {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("createAlarm.fxml"));
        Parent parent = fxmlLoader.load();

        Scene scene = new Scene(parent);
        Stage stage = new Stage();
        stage.initModality(Modality.APPLICATION_MODAL);
        stage.setScene(scene);
        stage.setOnHidden(e -> SetAlarm());
        stage.showAndWait();
    }

    @FXML
    private void SetTime(ActionEvent event) throws IOException
    {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("setTime.fxml"));
        Parent parent = fxmlLoader.load();

        Scene scene = new Scene(parent);
        Stage stage = new Stage();
        stage.initModality(Modality.APPLICATION_MODAL);
        stage.setScene(scene);
        stage.setOnHidden(e -> DrawClock());
        stage.showAndWait();
    }

    public void SetAlarm()
    {
        BaseClock userClock = clock.GetClock().get(0);
        ObservableList<String> alarmList = FXCollections.observableList(userClock.GetAlarms().GetList());
        alarmsView.setItems(alarmList);
    }

    public void PrintTime(BaseClock clock)
    {
        hour.setText(clock.GetTimeByField(Field.H));
        minute.setText(clock.GetTimeByField(Field.M));
        second.setText(clock.GetTimeByField(Field.S));
    }

    public void DrawClock()
    {
        BaseClock userClock = clock.GetClock().get(0);
        ObservableList<String> alarmList = FXCollections.observableList(userClock.GetAlarms().GetList());

        PrintTime(userClock);
        alarmsView.setItems(alarmList);
        alarmsView.setVisible(true);

        hour.setVisible(true);
        minute.setVisible(true);
        second.setVisible(clock.GetClock().get(0).GetType().equals(TypeClock.ThreeArrows));

        setTime.setDisable(false);
        alarm.setDisable(false);
        pauseClock.setDisable(false);
        stopClock.setDisable(false);
        thread.start();
    }

    public void StartTime()
    {
        startClock.setDisable(true);
        pauseClock.setDisable(false);
        stopClock.setDisable(false);
        runnable.resume();
    }

    public void PauseTime()
    {
        startClock.setDisable(false);
        pauseClock.setDisable(true);
        stopClock.setDisable(false);
        runnable.pause();
    }

    public void StopTime()
    {
        startClock.setDisable(false);
        pauseClock.setDisable(true);
        stopClock.setDisable(true);
        runnable.stop();
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        clock = UserClock.getInstance();
    }
}
