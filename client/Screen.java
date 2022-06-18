import processing.core.PApplet;

import java.util.List;
import java.util.Set;

enum State {
    MENU,
    LOGGED_IN,
    LOGOUT,
    DELETE,
    USERNAME,
    PASSWORD,
    CREATE_USERNAME,
    CREATE_PASSWORD,
    JOIN,
    PLAY,
    LEADERBOARD,
    GAME
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
        //if(state != State.GAME)
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
            case LOGOUT:
            case DELETE:
                handleTCPState(State.MENU);
                break;
            case JOIN:
                handleTCPState(State.PLAY);
                break;
            case PLAY:
                handleTCPState(State.LEADERBOARD);
                break;
            case LEADERBOARD:
                leaderboard();
                break;
            case GAME:
                game();
                handleTCPState(State.GAME);
                break;
        }
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

    boolean overRect(int x, int y, int width, int height)  {
        return mouseX >= x && mouseX <= x + width &&
                mouseY >= y && mouseY <= y + height;
    }

    public void keyPressed() {
        switch (state) {
            case USERNAME:
                if (key == ENTER)
                    handleTCPState(State.LOGGED_IN);
                else if (key == BACKSPACE && data.username.length() != 0)
                    data.username = data.username.substring(0, data.username.length() - 1);
                else if (key >= 'a' && key <= 'z')
                    data.username += key;
                break;
            case PASSWORD:
                if (key == ENTER)
                    handleTCPState(State.LOGGED_IN);
                else if (key == BACKSPACE && data.username.length() != 0)
                    data.password = data.password.substring(0, data.password.length() - 1);
                else if (key >= 'a' && key <= 'z')
                    data.password += key;
                break;
            case CREATE_USERNAME:
                if (key == ENTER)
                    handleTCPState(State.MENU);
                else if (key == BACKSPACE && data.username.length() != 0)
                    data.username = data.username.substring(0, data.username.length() - 1);
                else if (key >= 'a' && key <= 'z')
                    data.username += key;
                break;
            case CREATE_PASSWORD:
                if (key == ENTER)
                    handleTCPState(State.MENU);
                else if (key == BACKSPACE && data.password.length() != 0)
                    data.password = data.password.substring(0, data.password.length() - 1);
                else if (key >= 'a' && key <= 'z')
                    data.password += key;
                break;
        }
    }

    void handleTCPState(State nextState) {
        try {
            data.lock.lock();
            data.option = state;

            data.waitPostman.signal();
            while (data.response == Response.NOTHING) data.waitScreen.await();

            if (data.response == Response.DONE) {
                state = nextState;
            }
            else if(data.response == Response.SWITCH) {
                state = data.option;
            }
            else
                state = State.MENU;
            data.response = Response.NOTHING;
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        } finally {
            data.lock.unlock();
        }
    }

    void leaderboard() {
        background(255, 255, 255);
        Set<Tuple<String, Integer>> lb = data.leaderboard;
        StringBuilder sb = new StringBuilder();
        sb.append("*** Leaderboard ***\n\n");
        for (Tuple<String, Integer> t : lb) {
            sb.append(t.second).append(" ").append(t.first).append("\n\n");
        }
        fill(0,0,0);
        text(sb.toString(), Wscreen/16, Hscreen/16);
        state = data.option;

    }



    void starterMenu(){
        background(255, 255, 255);
        button("Login", Wscreen/4, Hscreen/16, State.USERNAME);
        button("Register", Wscreen/4, Hscreen/4, State.CREATE_USERNAME);
    }

    void loggedInMenu() {
        background(255, 255, 255);
        button("Play", Wscreen/4, Hscreen/16, State.JOIN);
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



    void game(){
        Tuple<Piece,List<Piece>> pieces = board.getBoard();
        if(pieces.first == null)
            return;
        background(0,0,0);
        fill(pieces.first.r,pieces.first.g,pieces.first.b,255);
        circle(400,400,20+pieces.first.mass);
        for(Piece p: pieces.second){
            fill(p.r, p.g,p.b,255);
            circle(400+p.x,400+p.y,20+p.mass);

        }

    }




    @Override
    public void run() {
        String[] processingArgs = {"Screen"};
        Screen screen = new Screen(this.mouse, this.board, this.data);
        PApplet.runSketch(processingArgs, screen);
    }



    /*public void keyPressed() {
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
    }*/

    /*boolean handleEnter(State nextState) {
        if (key == ENTER) {
            handleTCPState(nextState);
            return true;
        }
        return false;
    }*/









}



