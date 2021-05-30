package clock;

public class FactoryClock {

    final String mark;
    final int cost;

    public FactoryClock(int cost, String mark)
    {

        this.mark = mark;
        this.cost = cost;
    }

    public BaseClock GetClock(TypeClock type)
    {
        BaseClock toReturn = null;
        switch (type)
        {
            case TwoArrows:
                toReturn = new TwoClock(cost, mark);
                break;
            case ThreeArrows:
                toReturn = new ThreeClock(cost, mark);
                break;
            default:
                throw new IllegalArgumentException("Wrong type:" + type);
        }
        return toReturn;
    }
}
