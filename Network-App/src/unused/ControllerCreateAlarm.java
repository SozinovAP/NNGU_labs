package unused;

import clock.UserClock;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

public class ControllerCreateAlarm {

    public TextField hour;
    public TextField minute;
    public TextField second;
    public CheckBox hasSecond;
    public Button createAlarm;
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

    public void Create() throws Exception {
        if (!(hour.getText().isEmpty() || minute.getText().isEmpty() ||
                (hasSecond.isSelected() && second.getText().isEmpty())))
        {
            UserClock.getInstance().GetClock().get(0).AddAlarm(Integer.parseInt(hour.getText()),
                                                    Integer.parseInt(minute.getText()),
                                                    hasSecond.isSelected() ? Integer.parseInt(second.getText()) : 0);

            ((Stage) createAlarm.getScene().getWindow()).close();
        }
    }
}
