package projeto;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Avancado extends Jogador {
    private int finalizacao;
    private int compostura;

    public Avancado() {
        super();
        this.finalizacao = 0;
        this.compostura = 0;
    }

    public Avancado(String nom, int ide, ArrayList<String> hist, Map<String,Integer> ats, int fn, int cp) {
        super(nom,ide, hist, ats);
        this.finalizacao = fn;
        this.compostura = cp;
    }

    public Avancado(Avancado a) {
        super(a);
        this.finalizacao = a.finalizacao;
        this.compostura = a.compostura;
    }

    public Avancado clone() {
        return new Avancado(this);
    }

    public boolean equals(Object o) {
        if (this == o) return true;

        if (o == null || o.getClass() != this.getClass()) return false;

        Avancado a = (Avancado) o;
        return super.equals(o) && this.finalizacao == a.finalizacao && this.compostura == a.compostura;
    }

    public String toString() {
        return super.toString() + "\nFinalizacao: " + this.finalizacao + "\nCompostura: " + this.compostura + "\n";
    }

    public void setFinalizacao(int fn) {
        this.finalizacao = fn;
    }
    public void setCompostura(int cp) {
        this.compostura = cp;
    }
    public int getFinalizacao() {
        return this.finalizacao;
    }
    public int getCompostura() {
        return this.compostura;
    }

    public int calculaOverall() {
        return (int) (this.getVelocidade() * 0.15
                 + this.getResistencia() * 0.05
                 + this.getDestreza() * 0.10
                 + this.getImpulsao() * 0.05
                 + this.getJogoCabeca() * 0.10
                 + this.getRemate() * 0.20
                 + this.getPasse()  * 0.05
                 + this.finalizacao * 0.20
                 + this.compostura * 0.10);
    }

    public static Avancado parse(String input) {
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
        return new Avancado(campos[0], Integer.parseInt(campos[1]), new ArrayList<>(), atributos, 70, 70);
    }
}
