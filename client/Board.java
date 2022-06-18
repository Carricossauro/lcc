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

    public synchronized void setBoard(String username, String response){
        this.pieces.clear();
        String[] positionsString = response.split("\\|");
        for(String pieceString: positionsString) {
            String[] pieceInfo = pieceString.split(" ");
            Piece piece = new Piece(pieceInfo[0], pieceInfo[1], Float.parseFloat(pieceInfo[2]), Float.parseFloat(pieceInfo[3]), Integer.parseInt(pieceInfo[4]));
            if(piece.username.equals(username))
                this.me = piece;
            else
                this.pieces.add(piece);
            for(Piece p : this.pieces){
                p.x -= me.x;
                p.y -= me.y;
            }
            me.x = 0;
            me.y = 0;
        }
    }

    public synchronized Tuple<Piece,List<Piece>> getBoard() {
        return new Tuple<>(this.me, this.pieces);
    }
}
