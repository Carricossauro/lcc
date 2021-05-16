package projeto;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.stream.Collectors;

public abstract class Jogador {
    private String nome; // Nome do jogador
    private String equipa; // Nome da equipa
    private int numeroCamisola; // Numero de camisola do jogador
    private ArrayList<String> historico; // Historico de equipas
    private Map<String,Integer> atributos; // Atributos do jogador

    public Jogador() {
        this.nome = "n/a";
        this.equipa = "n/a";
        this.numeroCamisola = 0;
        this.historico = new ArrayList<>();
        this.atributos = new HashMap<>();
        this.atributos.put("velocidade", 0);
        this.atributos.put("resistencia", 0);
        this.atributos.put("destreza", 0);
        this.atributos.put("impulsao", 0);
        this.atributos.put("jogocabeca", 0);
        this.atributos.put("remate", 0);
        this.atributos.put("passe", 0);
    }

    public Jogador(String nom, String eq, int nC, ArrayList<String> hist, Map<String,Integer> ats) {
        this.nome = nom;
        this.equipa = eq;
        this.numeroCamisola = nC;
        this.historico = new ArrayList<String>(hist);
        this.atributos = ats.entrySet().stream().collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    public Jogador(Jogador j) {
        this(j.nome, j.equipa, j.numeroCamisola, j.historico, j.atributos);
    }

    public boolean equals(Object o) {
        if (this == o) return true;

        if (o == null || o.getClass() != this.getClass()) return false;

        Jogador that = (Jogador) o;
        return this.numeroCamisola == that.numeroCamisola && this.nome.equals(that.nome) &&
                this.equipa.equals(that.equipa) &&
                this.historico.equals(that.historico) &&
                this.atributos.equals(that.atributos);
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();

        sb.append("Jogador: "); sb.append(this.nome);
        sb.append("\nEquipa: "); sb.append(this.equipa);
        sb.append("\nNumero de Camisola: "); sb.append(this.numeroCamisola);
        sb.append("\nHistórico de equipas: "); sb.append(this.historico.toString());
        sb.append("\nAtributos: "); sb.append(this.atributos.toString());

        return sb.toString();
    }

    public abstract int calculaOverall();
    public abstract Jogador clone();

    public void adicionarAoHistorico(String nomeEquipa) {
        this.historico.add(nomeEquipa);
    }

    // setters e getters
    public String getNome() {
        return this.nome;
    }
    public void setNome(String nom) {
        this.nome = nom;
    }
    public String getEquipa() {
        return this.equipa;
    }
    public void setEquipa(String eq) {
        this.equipa = eq;
    }
    public int getNumeroCamisola() {
        return this.numeroCamisola;
    }
    public void setNumeroCamisola(int numeroCamisola) {
        this.numeroCamisola = numeroCamisola;
    }
    public ArrayList<String> getHistorico() {
        return new ArrayList<String>(this.historico);
    }
    public void setHistorico(ArrayList<String> hist) {
        this.historico = new ArrayList<String>(hist);
    }
    public void setAtributo(String atr, int at) {
        this.atributos.put(atr, at);
    }
    public int getAtributo(String atr) {
        return this.atributos.get(atr);
    }
    public void setVelocidade(int at) {
        setAtributo("velocidade", at);
    }
    public int getVelocidade() {
        return getAtributo("velocidade");
    }
    public void setResistencia(int at) {
        setAtributo("resistencia", at);
    }
    public int getResistencia() {
        return getAtributo("resistencia");
    }
    public void setDestreza(int at) {
        setAtributo("destreza", at);
    }
    public int getDestreza() {
        return getAtributo("destreza");
    }
    public void setImpulsao(int at) {
        setAtributo("impulsao", at);
    }
    public int getImpulsao() {
        return getAtributo("impulsao");
    }
    public void setJogoCabeca(int at) {
        setAtributo("jogocabeca", at);
    }
    public int getJogoCabeca() {
        return getAtributo("jogocabeca");
    }
    public void setRemate(int at) {
        setAtributo("remate", at);
    }
    public int getRemate() {
        return getAtributo("remate");
    }
    public void setPasse(int at) {
        setAtributo("passe", at);
    }
    public int getPasse() {
        return getAtributo("passe");
    }
}
