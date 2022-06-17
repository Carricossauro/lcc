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


    }
}
