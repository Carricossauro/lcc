package projeto;

import java.util.ArrayList;
import java.util.Map;

public class Defesa extends Jogador {
    private int corte;
    private int intersecao;

    public Defesa() {
        super();
        this.corte = 0;
        this.intersecao = 0;
    }

    public Defesa(String nom, String eq, int ide, ArrayList<String> hist, Map<String,Integer> ats, int co, int it) {
        super(nom, eq,ide, hist, ats);
        this.corte = co;
        this.intersecao = it;
    }

    public Defesa(Defesa d) {
        super(d);
        this.corte = d.corte;
        this.intersecao = d.intersecao;
    }

    public Defesa clone() {
        return new Defesa(this);
    }

    public boolean equals(Object o) {
        if (this == o) return true;

        if (o == null || o.getClass() != this.getClass()) return false;

        Defesa d = (Defesa) o;
        return super.equals(o) && this.corte == d.corte && this.intersecao == d.intersecao;
    }

    public String toString() {
        return super.toString() + "\nCorte: " + this.corte + "\nIntersecçao: " + this.intersecao + "\n";
    }

    public int calculaOverall() {
        return 0;
    }

    public void setIntersecao(int it) {
        this.intersecao = it;
    }
    public int getIntersecao() {
        return this.intersecao;
    }
    public void setCorte(int co) {
        this.corte = co;
    }
    public int getCorte() {
        return this.corte;
    }
}
