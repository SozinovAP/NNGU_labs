package visual;

import events.MyControlListener;

import java.util.ArrayList;

public class MyControl  {
    private final ArrayList<MyControlListener> listeners = new ArrayList<>();

    public void addListener(MyControlListener listener) {
        listeners.add(listener);
    }

    public void removeListener(MyControlListener listener) {
        listeners.remove(listener);
    }

    public void TimeChanged (int index) {
        for(MyControlListener listener : listeners)
            listener.onTimeChanged(index);
    }

    public void AlarmStart (int index) {
        for(MyControlListener listener : listeners)
            listener.onAlarmStart(index);
    }

    public void AlarmsChange (int index) {
        for(MyControlListener listener : listeners)
            listener.onAlarmStart(index);
    }
}
