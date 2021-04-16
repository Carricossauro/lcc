package projeto;

import java.util.ArrayList;
import java.util.Map;

public class GuardaRedes extends Jogador {
    private int elasticidade;

    public GuardaRedes() {
        super();
        this.elasticidade = 0;
    }

    public GuardaRedes(String nom, String eq, int ide, ArrayList<String> hist, Map<String,Integer> ats, int elas) {
        super(nom, eq,ide, hist, ats);
        this.elasticidade = elas;
    }

    public GuardaRedes(GuardaRedes gr) {
        super(gr);
        this.elasticidade = gr.elasticidade;
    }

    public GuardaRedes clone() {
        return new GuardaRedes(this);
    }

    public boolean equals(Object o) {
        if (this == o) return true;

        if (o == null || o.getClass() != this.getClass()) return false;

        GuardaRedes gr = (GuardaRedes) o;
        return super.equals(o) && this.elasticidade == gr.elasticidade;
    }

    public String toString() {
        return super.toString() + "\nElasticidade: " + elasticidade + "\n";
    }

    public int calculaOverall() {
        return 0;
    }

    // setters e getters
    public void setElasticidade(int elas) {
        this.elasticidade = elas;
    }
    public int getElasticidade() {
        return this.elasticidade;
    }
}
