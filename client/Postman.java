public class Postman implements Runnable{

    private TCP tcp;
    private Mouse mouse;

    private Board board;

    public Postman(TCP tcp, Mouse mouse, Board board){
        this.tcp = tcp;
        this.mouse = mouse;
        this.board = board;
    }

    public void run(){


    }
}
