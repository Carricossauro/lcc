import java.util.Set;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Data {
    Lock lock = new ReentrantLock();
    private int option;
    public int turn;
    public boolean state;

    private String name;
    private String password;
    private Set leaderboard;




}
