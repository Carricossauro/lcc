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

    // setters e getters
    public void setElasticidade(int elas) {
        this.elasticidade = elas;
    }
    public int getElasticidade() {
        return this.elasticidade;
    }

    public int calculaOverall() {
        return (int) (this.getVelocidade() * 0.01
                 + this.getResistencia() * 0.05
                 + this.getDestreza() * 0.05
                 + this.getImpulsao() * 0.15
                 + this.getJogoCabeca() * 0.01
                 + this.getRemate() * 0.10
                 + this.getPasse()  * 0.10
                 + this.elasticidade * 0.53);
    }
}
