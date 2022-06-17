import java.util.Set;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

enum Response {
    NOTHING,
    DONE,
    ERROR
}
public class Data {
    public Lock lock = new ReentrantLock();
    public Condition waitPostman = lock.newCondition();
    public Condition waitScreen = lock.newCondition();
    public State option;

    public Response response = Response.NOTHING;

    public String username="";
    public String password="";
    public Set leaderboard;
}
