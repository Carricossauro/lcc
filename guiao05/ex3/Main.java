class Barreira {
    private final int N;
    private int counter = 0;
    private boolean w = false;


    Barreira(int N) {
        this.N = N;
    }

    public synchronized void await() throws InterruptedException {
        counter++;

        if (counter == 1) w = true;

        if (counter == N) {
            notifyAll();
            counter = 0;
            w = false;
        }

        while (w) wait();
    }
}

public class Main {
    public static void main(String args[]) {
        try {
            int N = 5;
            Barreira b = new Barreira(N);

            for (int i = 0; i < N; i++) {
                new Thread(() -> {
                    try {
                        System.out.println("Await");
                        b.await();
                        System.out.println("Released");
                    } catch (Exception e) {}
                }).start();
                Thread.sleep(200);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}