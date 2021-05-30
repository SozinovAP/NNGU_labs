package events;

public interface MyControlListener {
    void onTimeChanged(int index);

    void onAlarmStart(int index);

    void onAlarmsChange(int index);
}
