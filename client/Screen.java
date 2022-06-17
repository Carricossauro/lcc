import processing.core.PApplet;

enum State {
    MENU,
    REGISTER,
    DELETE,
    PLAY,
    USERNAME,
    PASSWORD
}



public class Screen extends PApplet implements Runnable{
    private Mouse mouse;
    private Board board;
    private Data data;
    private int Wscreen = 800;
    private int Hscreen = 800;
    private State state = State.MENU;

    public Screen(){
    }
    public Screen(Mouse mouse, Board board, Data data){
        this.mouse = mouse;
        this.board = board;
        this.data = data;
    }


    public void settings(){
        size(Wscreen, Hscreen);
    }

    public void draw(){
        clear();
        switch (state) {
            case MENU:
                menu();
                break;
            case USERNAME:
            case PASSWORD:
                login();
                break;
            case PLAY:
                board();
                break;
        }
    }
    void board(){
        fill(255,0,0,255);
        ellipse(mouseX, mouseY, 20, 20);
    }

    void button(String text, int x, int y, State buttonState) {
        fill(255,255, 255);
        rect(x, y, Wscreen/2, Hscreen/8, 15);
        fill(0,0,0);
        text(text, x + Wscreen/4 - text.length()*4, y + Hscreen/16);
        if (mousePressed && overRect(x, y, Wscreen/2, Hscreen/8)) {
            state = buttonState;
        }
    }

    void menu(){
        background(255, 255, 255);
        button("Login", Wscreen/4, Hscreen/16, State.USERNAME);
        button("Register", Wscreen/4, Hscreen/4, State.REGISTER);
        button("Delete account", Wscreen/4, Hscreen/16*3+Hscreen/4, State.DELETE);
        button("Play", Wscreen/4, Hscreen/16*4+Hscreen/8*3, State.PLAY);
    }

    void login() {
        background(255, 255, 255);

        button(data.username, Wscreen/4, Hscreen/16, State.USERNAME);
        button(data.password, Wscreen/4, Hscreen/4, State.PASSWORD);
    }

    boolean overRect(int x, int y, int width, int height)  {
        if (mouseX >= x && mouseX <= x+width &&
                mouseY >= y && mouseY <= y+height) {
            return true;
        } else {
            return false;
        }
    }
    @Override
    public void run() {
        String[] processingArgs = {"Screen"};
        Screen screen = new Screen(this.mouse, this.board, this.data);
        PApplet.runSketch(processingArgs, screen);
    }




}



