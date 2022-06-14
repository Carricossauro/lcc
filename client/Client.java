import java.io.*;
import java.net.*;
import java.util.Comparator;
import java.util.Set;
import java.util.TreeSet;

class InvalidPassword extends Exception {
    public InvalidPassword(String message) {
        super(message);
    }
}
class InvalidAccount extends Exception {
    public InvalidAccount(String message) {
        super(message);
    }
}
class UserExists extends Exception {
    public UserExists(String message) {
        super(message);
    }
}

class Tuple<A, B> {
    public A first;
    public B second;

    public Tuple(A fst, B snd) {
        this.first = fst;
        this.second = snd;
    }

    public Tuple<A, B> clone() {
        return new Tuple<>(first, second);
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(first);
        sb.append(" ");
        sb.append(second);
        return sb.toString();
    }
}

class TCP {
    private Socket socket;
    private BufferedReader in;
    private PrintWriter out;
    StringBuilder sb = new StringBuilder();

    public TCP(String host, int port) throws IOException {
        this.socket = new Socket(host, port);
        this.in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        this.out = new PrintWriter(socket.getOutputStream());
    }

    public void send(String message) {
        out.println(message);
        out.flush();
    }

    public String receive() throws IOException {
        String message = in.readLine();
        return message;
    }

    public void login(String username, String password) throws IOException, InvalidPassword, InvalidAccount {
        sb.append("login#");
        sb.append(username);
        sb.append(" ");
        sb.append(password);
        this.send(sb.toString()); // login#username password
        sb.setLength(0);

        String response = this.receive();
        switch (response) {
            case "done":
                break;
            case "invalid_account":
                throw new InvalidAccount("Invalid account.");
            case "invalid_password":
                throw new InvalidPassword("Invalid password.");
        }
    }

    public void logout(String username, String password) throws IOException, InvalidPassword, InvalidAccount {
        sb.append("logout#");
        sb.append(username);
        sb.append(" ");
        sb.append(password);
        this.send(sb.toString()); // logout#username password
        sb.setLength(0);

        String response = this.receive();
        switch (response) {
            case "done":
                break;
            case "invalid_account":
                throw new InvalidAccount("Invalid account.");
            case "invalid_password":
                throw new InvalidPassword("Invalid password.");
        }
    }

    public void create_account(String username, String password) throws IOException, InvalidPassword, UserExists {
        sb.append("create_account#");
        sb.append(username);
        sb.append(" ");
        sb.append(password);
        this.send(sb.toString()); // create_account#username password
        sb.setLength(0);

        String response = this.receive();
        switch (response) {
            case "done":
                break;
            case "user_exists":
                throw new UserExists("User already exists.");
            case "invalid_password":
                throw new InvalidPassword("Invalid password.");
        }
    }

    public void remove_account(String username, String password) throws IOException, InvalidPassword, InvalidAccount {
        sb.append("remove_account#");
        sb.append(username);
        sb.append(" ");
        sb.append(password);
        this.send(sb.toString()); // remove_account#username password
        sb.setLength(0);

        String response = this.receive();
        switch (response) {
            case "done":
                break;
            case "invalid_account":
                throw new InvalidAccount("Invalid account.");
            case "invalid_password":
                throw new InvalidPassword("Invalid password.");
        }
    }

    public Set<Tuple<String, Integer>> leaderboard() throws IOException {
        sb.append("leaderboard#");
        this.send(sb.toString()); // leaderboard#
        sb.setLength(0);

        String response = this.receive();
        String[] playerStrings = response.split("\\|");

        Comparator<Tuple<String, Integer>> comp = (a1, a2) -> (a1.second != a2.second) ? (a2.second - a1.second) : a1.first.compareTo(a2.first);
        Set<Tuple<String, Integer>> players = new TreeSet<>(comp);

        for (String playerString : playerStrings) {
            String[] playerInfo = playerString.split(" ");
            Tuple<String, Integer> newPlayer = new Tuple<>(playerInfo[0], Integer.parseInt(playerInfo[1]));
            players.add(newPlayer);
        }

        return players;
    }
}

class Mouse {
    private Tuple<Float, Float> pos = new Tuple<Float, Float>(0.0f,0.0f);
    private boolean pressed = false;

    public synchronized Tuple<Float, Float> getPos() {
        return pos.clone();
    }

    public synchronized void setPos(Float x, Float y) {
        pos.first = x;
        pos.second = y;
    }

    public synchronized String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(pos.toString());
        sb.append(" ");
        sb.append(pressed);
        return sb.toString();
    }
}

class Client {
    public static void main(String[] args) {
        try {
            if (args.length < 2) {
                print("Incorrect syntax:");
                print("java client [host] [port] ");
                System.exit(1);
            }

            TCP tcp = new TCP(args[0], Integer.parseInt(args[1]));
            Mouse mouse = new Mouse();

            print(mouse.toString());
            
        } catch (Exception e) {
            print(e.getMessage());
        }
    }

    public static void print(String message) {
        System.out.println(message);
    }
}