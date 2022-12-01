package projeto;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Lateral extends Jogador {
    private int cruzamento;
    private int drible;

    public Lateral() {
        super();
        this.cruzamento = 0;
        this.drible = 0;
    }

    public Lateral(String nom, int ide, ArrayList<String> hist, Map<String,Integer> ats, int cr, int dr) {
        super(nom,ide, hist, ats);
        this.cruzamento = cr;
        this.drible = dr;
    }

    public Lateral(Lateral d) {
        super(d);
        this.cruzamento = d.cruzamento;
        this.drible = d.drible;
    }

    public Lateral clone() {
        return new Lateral(this);
    }

    public boolean equals(Object o) {
        if (this == o) return true;

        if (o == null || o.getClass() != this.getClass()) return false;

        Lateral l = (Lateral) o;
        return super.equals(o) && this.cruzamento == l.cruzamento && this.drible == l.drible;
    }

    public String toString() {
        return super.toString() + "\nCorte: " + this.cruzamento + "\nIntersecçao: " + this.drible + "\n";
    }

    public void setCruzamento(int cr) {
        this.cruzamento = cr;
    }
    public int getCruzamento() {
        return this.cruzamento;
    }
    public void setDrible(int dr) {
        this.drible = dr;
    }
    public int getDrible() {
        return this.drible;
    }

    public int calculaOverall() {
      return (int) (this.getVelocidade() * 0.15
                 + this.getResistencia() * 0.15
                 + this.getDestreza() * 0.10
                 + this.getImpulsao() * 0.05
                 + this.getJogoCabeca() * 0.05
                 + this.getRemate() * 0.10
                 + this.getPasse()  * 0.10
                 + this.drible * 0.15
                 + this.cruzamento * 0.15);
    }

    public static Lateral parse(String input) {
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
        return new Lateral(campos[0], Integer.parseInt(campos[1]), new ArrayList<>(), atributos, 70, 70);
    }
}
