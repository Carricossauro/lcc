import java.util.Set;





public class Client {
    public static void main(String[] args) {
        try {
            if ( args.length < 2) {
                print("Incorrect syntax:");
                print("java client [host] [port] ");
                System.exit(1);
            }

            //TCP tcp = new TCP(args[0], Integer.parseInt(args[1]));
            Mouse mouse = new Mouse();
            Board board = new Board();

            new Thread(new Screen(mouse,board)).start();

            //new Thread(new Postman(tcp,mouse,board)).start();

            /*Set<String> users = tcp.online();
            for (String user : users) {
                print(user);
            }*/
            
        } catch (Exception e) {
            print(e.getMessage());
        }
    }

    public static void print(String message) {
        System.out.println(message);
    }
}