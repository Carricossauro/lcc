import java.io.IOException;
import java.util.List;

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
        while (true) {
            try {
                data.lock.lock();
                data.waitPostman.await();

                switch(data.option) {
                    case USERNAME:
                    case PASSWORD:
                        tcp.login(data.username, data.password);
                        data.response = Response.DONE;
                        break;
                    case CREATE_USERNAME:
                    case CREATE_PASSWORD:
                        tcp.create_account(data.username, data.password);
                        data.username = "";
                        data.password = "";
                        data.response = Response.DONE;
                        break;
                    case DELETE:
                        tcp.remove_account(data.username, data.password);
                        data.username = "";
                        data.password = "";
                        data.response = Response.DONE;
                        break;
                    case LOGOUT:
                        tcp.logout(data.username, data.password);
                        data.username = "";
                        data.password = "";
                        data.response = Response.DONE;
                        break;
                    case JOIN:
                        data.leaderboard = tcp.leaderboard();
                        data.response = Response.DONE;
                        break;
                    case PLAY:
                        tcp.join(data.username, data.password);
                        data.response = Response.DONE;
                        data.option = State.LEADERBOARD;

                        new Thread(()->{
                            try {
                                String response = tcp.receive();
                                if(response.equals("start"))
                                    data.option = State.GAME;
                            } catch (IOException e) {
                                throw new RuntimeException(e);
                            }
                        }).start();
                        break;
                    case GAME:
                        String response = tcp.receive();
                        if(response == null || response.equals("winner")){
                            data.option = State.LOGGED_IN;
                            data.response = Response.SWITCH;
                        }
                        else{
                            board.setBoard(data.username, response);
                            tcp.mouse(mouse.getPos());
                            data.response = Response.DONE;
                        }
                        break;

                }
                data.waitScreen.signal();
            } catch (InterruptedException | IOException e) {
                throw new RuntimeException(e);
            } catch (InvalidPassword | InvalidAccount | UserExists | FullServer e) {
                data.response = Response.ERROR;
                data.username = "";
                data.password = "";
                data.waitScreen.signal();
            } finally {
                data.lock.unlock();
            }

        }

    }
}
