package unused;

import clock.BaseClock;
import clock.Field;
import clock.UserClock;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import clock.FactoryClock;
import clock.TypeClock;

import java.sql.SQLException;

public class ControllerCreateClock {

    public CheckBox hasSecond;
    public TextField hour;
    public TextField minute;
    public TextField second;
    public TextField mark;
    public TextField cost;
    public Button createClock;
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

    public void Create() throws SQLException {
        if (!(cost.getText().isEmpty() || mark.getText().isEmpty() ||
                hour.getText().isEmpty() || minute.getText().isEmpty() ||
                (hasSecond.isSelected() && second.getText().isEmpty())))
        {
            BaseClock clock;
            FactoryClock factory = new FactoryClock(Integer.parseInt(cost.getText()), mark.getText());
            clock = factory.GetClock(hasSecond.isSelected() ? TypeClock.ThreeArrows : TypeClock.TwoArrows);

            clock.SetTimeByField(Field.H, Integer.parseInt(hour.getText()));
            clock.SetTimeByField(Field.M, Integer.parseInt(minute.getText()));
            if (hasSecond.isSelected())
                clock.SetTimeByField(Field.S, Integer.parseInt(second.getText()));

            UserClock.getInstance().SetClock(clock);
            ((Stage) createClock.getScene().getWindow()).close();
        }
    }
}
