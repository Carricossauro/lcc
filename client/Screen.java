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
    GAME,
    LEAVE,
    QUIT,
    WINNER,
    LOSER
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
        fill(240,240, 240);
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
                else if(key==TAB)
                    state = State.MENU;
                break;
            case PASSWORD:
                if (key == ENTER)
                    handleTCPState(State.LOGGED_IN);
                else if (key == BACKSPACE && data.username.length() != 0)
                    data.password = data.password.substring(0, data.password.length() - 1);
                else if (key >= 'a' && key <= 'z')
                    data.password += key;
                else if(key==TAB)
                    state = State.MENU;
                break;
            case CREATE_USERNAME:
                if (key == ENTER)
                    handleTCPState(State.MENU);
                else if (key == BACKSPACE && data.username.length() != 0)
                    data.username = data.username.substring(0, data.username.length() - 1);
                else if (key >= 'a' && key <= 'z')
                    data.username += key;
                else if(key==TAB)
                    state = State.MENU;
                break;
            case CREATE_PASSWORD:
                if (key == ENTER)
                    handleTCPState(State.MENU);
                else if (key == BACKSPACE && data.password.length() != 0)
                    data.password = data.password.substring(0, data.password.length() - 1);
                else if (key >= 'a' && key <= 'z')
                    data.password += key;
                else if(key==TAB)
                    state = State.MENU;
                break;
            case LEADERBOARD:
                if(key==TAB) {
                    state = State.LEAVE;
                    handleTCPState(State.LOGGED_IN);
                }
                break;
            case GAME:
                if(key==TAB) {
                    state = State.QUIT;
                    handleTCPState(State.LOGGED_IN);
                }


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
        background(255, 255, 153);
        Set<Tuple<String, Integer>> lb = data.leaderboard;
        StringBuilder sb1 = new StringBuilder();
        StringBuilder sb2 = new StringBuilder();

        for (Tuple<String, Integer> t : lb) {
            sb1.append(t.first).append("\n\n");
            sb2.append(t.second).append("\n\n");
        }
        fill(0,0,0);
        String title = "*** Leaderboard ***";
        text(title, Wscreen/2 - title.length()*3, Hscreen/16);
        text(sb1.toString(), Wscreen/4, Hscreen/8);
        text(sb2.toString(), 3*Wscreen/4, Hscreen/8);
        state = data.option;

    }



    void starterMenu(){
        background(255, 153, 153);
        button("Login", Wscreen/4, Hscreen/16, State.USERNAME);
        button("Register", Wscreen/4, Hscreen/4, State.CREATE_USERNAME);
    }

    void loggedInMenu() {
        background(153, 204, 255);
        button("Play", Wscreen/4, Hscreen/16, State.JOIN);
        button("Delete account", Wscreen/4, Hscreen/4, State.DELETE);
        button("Logout", Wscreen/4, Hscreen/16*3 + Hscreen/4, State.LOGOUT);
    }

    void login() {
        background(153, 255, 204);
        String username = "Username";
        String password = "Password";
        text(username, Wscreen/2 - username.length()*4, Hscreen/32 + 4);
        text(password, Wscreen/2 - username.length()*4, 7*Hscreen/32 + 4);
        button(data.username, Wscreen/4, Hscreen/16, State.USERNAME);
        button(data.password, Wscreen/4, Hscreen/4, State.PASSWORD);
    }

    void createAccount() {
        background(153, 255, 204);
        String username = "Username";
        String password = "Password";
        text(username, Wscreen/2 - username.length()*4, Hscreen/32 + 4);
        text(password, Wscreen/2 - username.length()*4, 7*Hscreen/32 + 4);
        button(data.username, Wscreen/4, Hscreen/16, State.CREATE_USERNAME);
        button(data.password, Wscreen/4, Hscreen/4, State.CREATE_PASSWORD);
    }



    void game(){
        Tuple<Piece,List<Piece>> pieces = board.getBoard();
        if(pieces.first == null)
            return;
        background(0,0,0);
        fill(pieces.first.r,pieces.first.g,pieces.first.b,255);
        circle(400,400,pieces.first.mass);
        for(Piece p: pieces.second){
            if (p.isPlayer) {
                fill(p.r, p.g,p.b,255);
                circle(400+p.x,400+p.y, p.mass);
            } else drawCrystal(p);
        }
        mouse.setMouse(mouseX - Wscreen/2.0f, mouseY - Hscreen/2.0f, mousePressed);
    }

    void drawCrystal(Piece p) {
        float x1 = 400 + p.x + p.mass;
        float y1 = 400 + p.y;
        float x2 = 400 + p.x - p.mass;
        float y2 = 400 + p.y;
        float x3 = 400 + p.x;
        float y3 = 400 + p.y - p.mass;
        float x4 = 400 + p.x;
        float y4 = 400 + p.y + p.mass;
        fill(p.r, p.g, p.b, 255);
        quad(x1, y1, x3, y3, x2, y2, x4, y4);
    }


    @Override
    public void run() {
        String[] processingArgs = {"Screen"};
        Screen screen = new Screen(this.mouse, this.board, this.data);
        PApplet.runSketch(processingArgs, screen);
    }

}



