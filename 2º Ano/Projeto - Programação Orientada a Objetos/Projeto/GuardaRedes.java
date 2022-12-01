package projeto;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class GuardaRedes extends Jogador {
    private int elasticidade;

    public GuardaRedes() {
        super();
        this.elasticidade = 0;
    }

    public GuardaRedes(String nom, int ide, ArrayList<String> hist, Map<String,Integer> ats, int elas) {
        super(nom, ide, hist, ats);
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

    public static GuardaRedes parse(String input) {
        String[] campos = input.split(",");
        // Nome - campos[0]
        // Numero da camisola - campos[1]
        Map<String, Integer> atributos = new HashMap<>();
        // Velocidade
        atributos.put("velocidade", Integer.parseInt(campos[2]));
        // Resistencia
        atributos.put("resistencia", Integer.parseInt(campos[3]));
        // Destreza
        atributos.put("destreza", Integer.parseInt(campos[4]));
        // Impulsao
        atributos.put("impulsao", Integer.parseInt(campos[5]));
        // Jogocabeça
        atributos.put("jogocabeca", Integer.parseInt(campos[6]));
        // Remate
        atributos.put("remate", Integer.parseInt(campos[7]));
        // Passe
        atributos.put("passe", Integer.parseInt(campos[8]));
        return new GuardaRedes(campos[0], Integer.parseInt(campos[1]), new ArrayList<>(), atributos, 70);
    }
}
