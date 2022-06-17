import java.io.IOException;

public class Postman implements Runnable{

    private TCP tcp;
    private Mouse mouse;
    private Data data;
    private Board board;

    public Postman(TCP tcp, Mouse mouse, Board board, Data data){
        this.tcp = tcp;
        this.mouse = mouse;
        this.board = board;
        this.data = data;
    }

    public void run(){
        while (1) {
            try {
                data.lock.lock();
                data.waitPostman.await();
                System.out.println(data.username);
                System.out.println(data.password);

                tcp.login(data.username, data.password);

                data.waitScreen.signal();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            } finally {
                data.lock.unlock();
            }
        }
    }
}
