import java.io.*;
import java.net.*;

class TCP {
    private Socket socket;
    private BufferedReader in;
    private PrintWriter out;

    public TCP(String host, int port) throws Exception {
        this.socket = new Socket(host, port);
        this.in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        this.out = new PrintWriter(socket.getOutputStream());
    }
}
