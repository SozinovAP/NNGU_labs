package unused;

import clock.BaseClock;
import clock.Field;
import clock.TypeClock;
import clock.UserClock;
import javafx.application.Platform;

import java.sql.SQLException;

public class ClockRunnable implements Runnable {

    private boolean runTask = true;
    private volatile boolean paused = false;
    private final Object pauseLock = new Object();
    private int tick = 0;

    private synchronized boolean keepRunning() {
        return !this.paused;
    }

    public void stop() {
        runTask = false;
        resume();
    }

    public void pause() {
        paused = true;
    }

    public void resume() {
        synchronized (pauseLock) {
            paused = false;
            pauseLock.notifyAll();
        }
    }

    @Override
    public void run() {
        BaseClock clock = null;
        if (!UserClock.getInstance().GetClock().isEmpty())
            clock = UserClock.getInstance().GetClock().get(0);

        while (runTask) {
            synchronized (pauseLock) {
                if (!runTask) {
                    break;
                }
                if (paused) {
                    try {
                        synchronized (pauseLock) {
                            pauseLock.wait();
                        }
                    } catch (InterruptedException ex) {
                        break;
                    }
                    if (!runTask) {
                        break;
                    }
                }
            }

            tick = (++tick) % 60;
            assert clock != null;
            if (clock.GetType() == TypeClock.TwoArrows && tick == 0) {
                BaseClock finalClock = clock;
                Platform.runLater(() -> finalClock.MovingClock(Field.M, 1));
            }
            else if (clock.GetType() == TypeClock.ThreeArrows) {
                BaseClock finalClock1 = clock;
                Platform.runLater(() -> finalClock1.MovingClock(Field.S, 1));
            }
            BaseClock finalClock2 = clock;
            Platform.runLater(() -> {
                try {
                    finalClock2.GetAlarms().CheckAlarm(finalClock2.GetTime());
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            });

            try {
                Thread.sleep(1000L);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}