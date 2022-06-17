import processing.core.PApplet;

enum State {
    MENU,
    LOGGED_IN,
    LOGOUT,
    DELETE,
    PLAY,
    USERNAME,
    PASSWORD,
    CREATE_USERNAME,
    CREATE_PASSWORD
}

public class Screen extends PApplet implements Runnable{
    private Mouse mouse;
    private Board board;
    private Data data;
    private int Wscreen = 800;
    private int Hscreen = 800;
    private State state = State.MENU;

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
                starterMenu();
                break;
            case LOGGED_IN:
                loggedInMenu();
                break;
            case USERNAME:
            case PASSWORD:
                login();
                break;
            case CREATE_USERNAME:
            case CREATE_PASSWORD:
                createAccount();
                break;
            case DELETE:
            case LOGOUT:
                handleTCPState(State.MENU);
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

    void starterMenu(){
        background(255, 255, 255);
        button("Login", Wscreen/4, Hscreen/16, State.USERNAME);
        button("Register", Wscreen/4, Hscreen/4, State.CREATE_USERNAME);
    }

    void loggedInMenu() {
        background(255, 255, 255);
        button("Play", Wscreen/4, Hscreen/16, State.PLAY);
        button("Delete account", Wscreen/4, Hscreen/4, State.DELETE);
        button("Logout", Wscreen/4, Hscreen/16*3 + Hscreen/4, State.LOGOUT);
    }

    void login() {
        background(255, 255, 255);
        button(data.username, Wscreen/4, Hscreen/16, State.USERNAME);
        button(data.password, Wscreen/4, Hscreen/4, State.PASSWORD);
    }

    void createAccount() {
        background(255, 255, 255);
        button(data.username, Wscreen/4, Hscreen/16, State.CREATE_USERNAME);
        button(data.password, Wscreen/4, Hscreen/4, State.CREATE_PASSWORD);
    }

    void handleTCPState(State nextState) {
        try {
            data.lock.lock();
            data.option = state;
            data.waitPostman.signal();
            while (data.response == Response.NOTHING) data.waitScreen.await();

            if (data.response == Response.DONE) {
                state = nextState;
            } else {
                state = State.MENU;
            }
            data.response = Response.NOTHING;
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        } finally {
            data.lock.unlock();
        }
    }

    boolean overRect(int x, int y, int width, int height)  {
        return mouseX >= x && mouseX <= x + width &&
                mouseY >= y && mouseY <= y + height;
    }

    public void keyPressed() {
        switch (state) {
            case USERNAME:
                if (handleEnter(State.LOGGED_IN)) return;
                if (key == BACKSPACE) {
                    if (data.username.length() != 0)
                        data.username = data.username.substring(0, data.username.length() - 1);
                } else if (key >= 'a' && key <= 'z') data.username += key;
                break;
            case PASSWORD:
                if (handleEnter(State.LOGGED_IN))  return;
                if (key == BACKSPACE) {
                    if (data.username.length() != 0)
                        data.password = data.password.substring(0, data.password.length() - 1);
                } else if (key >= 'a' && key <= 'z') data.password += key;
                break;
            case CREATE_USERNAME:
                if (handleEnter(State.MENU)) return;
                if (key == BACKSPACE) {
                    if (data.username.length() != 0)
                        data.username = data.username.substring(0, data.username.length() - 1);
                } else if (key >= 'a' && key <= 'z') data.username += key;
                break;
            case CREATE_PASSWORD:
                if (handleEnter(State.MENU))  return;
                if (key == BACKSPACE) {
                    if (data.username.length() != 0)
                        data.password = data.password.substring(0, data.password.length() - 1);
                } else if (key >= 'a' && key <= 'z') data.password += key;
                break;
        }
    }

    boolean handleEnter(State nextState) {
        if (key == ENTER) {
            handleTCPState(nextState);
            return true;
        }
        return false;
    }

    @Override
    public void run() {
        String[] processingArgs = {"Screen"};
        Screen screen = new Screen(this.mouse, this.board, this.data);
        PApplet.runSketch(processingArgs, screen);
    }




}



