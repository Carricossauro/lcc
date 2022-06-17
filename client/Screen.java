import processing.core.PApplet;

public class Screen extends PApplet implements Runnable{

    private Mouse mouse;
    private Board board;

    public Screen(){
    }
    public Screen(Mouse mouse, Board board){
        this.mouse = mouse;
    }

    public void settings(){
        size(200, 200);
    }

    public void draw(){
        background(0);
        ellipse(mouseX, mouseY, 20, 20);
    }

    @Override
    public void run() {
        PApplet.main("Screen");
    }


}



