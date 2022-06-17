package client;
import client.TCP;

import java.util.Set;

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

    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(first);
        sb.append(" ");
        sb.append(second);
        return sb.toString();
    }
}



class Mouse {
    private Tuple<Float, Float> pos = new Tuple<Float, Float>(0.0f,0.0f);
    private boolean pressed = false;

    public synchronized Tuple<Float, Float> getPos() {
        return pos;
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

            Set<String> users = tcp.online();
            for (String user : users) {
                print(user);
            }
            
        } catch (Exception e) {
            print(e.getMessage());
        }
    }

    public static void print(String message) {
        System.out.println(message);
    }
}