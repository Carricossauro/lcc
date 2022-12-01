import java.util.Objects;

public class Piece {
    public float x;
    public float y;
    public String username;
    public int r = 0;
    public int g = 0;
    public int b = 0;
    public int mass;
    public boolean isPlayer;



    public Piece(String username, String color, float x, float y, int mass){
        this.username = username;
        setColor(color);
        this.x = x;
        this.y = y;
        this.mass = mass;
        this.isPlayer = !username.equals("<>");
    }

    void setColor(String color){

        if(color.equals("blue"))
            this.b = 255;
        else if (color.equals("red"))
            this.r = 255;
        else
            this.g  = 255;

    }
}
