import processing.core.PApplet;

import java.util.ArrayList;
import java.util.List;

enum Color {
    RED,
    GREEN,
    BLUE
}

public class Board {
    public Piece me;
    public List<Piece> pieces = new ArrayList<>();

    public synchronized Piece getMe() {
        return this.me;
    }

    public synchronized void setBoard(Piece p, List<Piece> lp) {
        this.me = p;
        this.pieces = lp;
    }

    public synchronized Tuple<Piece,List<Piece>> getBoard() {
        return new Tuple<>(this.me, this.pieces);
    }
}
