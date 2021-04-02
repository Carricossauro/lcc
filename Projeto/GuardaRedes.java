package projeto;

import java.util.ArrayList;

public class GuardaRedes extends Jogador {
    private int elasticidade;

    public GuardaRedes() {
        super();
        this.elasticidade = 0;
    }

    public GuardaRedes(String nom, String eq, int pos, int ide, ArrayList<String> hist, ArrayList<Integer> ats, int elas) {
        super(nom, eq, pos, ide, hist, ats);
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
        if (!super.equals(o)) return false;

        if (o.getClass() != this.getClass()) return false;

        GuardaRedes gr = (GuardaRedes) o;
        return this.elasticidade == gr.elasticidade;
    }

    public String toString() {
        return super.toString() + "\nElasticidade: " + elasticidade + "\n";
    }

    // setters e getters
    public void setElasticidade(int elas) {
        this.elasticidade = elas;
    }
    public int getElasticidade() {
        return this.elasticidade;
    }

}
