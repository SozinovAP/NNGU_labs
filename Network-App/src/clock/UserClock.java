package clock;

import java.util.ArrayList;

public final class UserClock {
    private final ArrayList<BaseClock> clock = new ArrayList<>();
    private final static UserClock INSTANCE = new UserClock();

    private UserClock() {}

    public static UserClock getInstance()
    {
        return INSTANCE;
    }

    public void SetClock(BaseClock _clock)
    {
        this.clock.add(_clock);
    }

    public void SetClock(Integer index, BaseClock _clock)
    {
        clock.remove(index);
        clock.add(index, _clock);
    }

    public ArrayList<BaseClock> GetClock()
    {
        return this.clock;
    }

    public Integer GetCountClock()
    {
        return clock.size();
    }
}
