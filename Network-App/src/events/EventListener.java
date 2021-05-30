package events;

import java.sql.SQLException;

public interface EventListener
{
    void update(EventType eventType, String time) throws SQLException;
}