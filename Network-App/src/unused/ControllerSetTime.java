package unused;

import clock.BaseClock;
import clock.Field;
import clock.UserClock;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

public class ControllerSetTime {
    public TextField hour;
    public TextField minute;
    public TextField second;
    public CheckBox hasSecond;
    public Button setTime;
    public Button cancelW;

    @FXML
    public void CheckStatus()
    {
        second.setDisable(!hasSecond.isSelected());
    }

    public void CancelWindow()
    {
        ((Stage) cancelW.getScene().getWindow()).close();
    }

    public void SetTime() throws Exception {
        if (!(hour.getText().isEmpty() || minute.getText().isEmpty() ||
                (hasSecond.isSelected() && second.getText().isEmpty())))
        {
            BaseClock clock = UserClock.getInstance().GetClock().get(0);

            clock.SetTimeByField(Field.H, Integer.parseInt(hour.getText()));
            clock.SetTimeByField(Field.M, Integer.parseInt(minute.getText()));
            if (hasSecond.isSelected())
                clock.SetTimeByField(Field.S, Integer.parseInt(second.getText()));
            ((Stage) setTime.getScene().getWindow()).close();
        }
    }
}
