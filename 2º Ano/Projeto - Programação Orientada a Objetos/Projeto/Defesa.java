package projeto;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Defesa extends Jogador {
    private int corte;
    private int intersecao;

    public Defesa() {
        super();
        this.corte = 0;
        this.intersecao = 0;
    }

    public Defesa(String nom, int ide, ArrayList<String> hist, Map<String,Integer> ats, int co, int it) {
        super(nom,ide, hist, ats);
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

    public int calculaOverall() {
        return (int) (this.getVelocidade() * 0.05
                 + this.getResistencia() * 0.10
                 + this.getDestreza() * 0.05
                 + this.getImpulsao() * 0.15
                 + this.getJogoCabeca() * 0.15
                 + this.getRemate() * 0.05
                 + this.getPasse()  * 0.15
                 + this.corte * 0.10
                 + this.intersecao * 0.20);
    }

    public static Defesa parse(String input) {
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
        return new Defesa(campos[0], Integer.parseInt(campos[1]), new ArrayList<>(), atributos, 70, 70);
    }
}
