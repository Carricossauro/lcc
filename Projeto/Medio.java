package projeto;

import java.util.ArrayList;
import java.util.Map;

public class Medio extends Jogador {
    private int intersecao;
    private int visao;

    public Medio() {
        super();
        this.intersecao = 0;
        this.visao = 0;
    }

    public Medio(String nom, String eq, int ide, ArrayList<String> hist, Map<String,Integer> ats, int it, int vs) {
        super(nom, eq,ide, hist, ats);
        this.intersecao = it;
        this.visao = vs;
    }

    public Medio(Medio m) {
        super(m);
        this.intersecao = m.intersecao;
        this.visao = m.visao;
    }

    public Medio clone() {
        return new Medio(this);
    }

    public boolean equals(Object o) {
        if (this == o) return true;

        if (o == null || o.getClass() != this.getClass()) return false;

        Medio m = (Medio) o;
        return super.equals(o) && this.intersecao == m.intersecao && this.visao == m.visao;
    }

    public String toString() {
        return super.toString() + "\nInterseçao: " + this.intersecao + "\nVisao: " + this.visao + "\n";
    }

    public int calculaOverall() {
        return 0;
    }

    public void setIntersecao(int it) {
        this.intersecao = it;
    }
    public void setVisao(int vs) {
        this.visao = vs;
    }
    public int getIntersecao() {
        return this.intersecao;
    }
    public int getVisao() {
        return this.visao;
    }
}
