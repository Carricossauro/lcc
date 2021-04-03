package projeto;

import java.util.ArrayList;

public class Jogador {
    private final int VELOCIDADE = 0;
    private final int RESISTENCIA = 1;
    private final int DESTREZA = 2;
    private final int IMPULSAO = 3;
    private final int JOGOCABECA = 4;
    private final int REMATE = 5;
    private final int PASSE = 6;

    private String nome; // Nome do jogador
    private String equipa; // Nome da equipa
    private int posicao; // 1-gr;2-def/3-med/4-av/5-lat
    private int id; // Identificador do jogador (valor unico)
    private ArrayList<String> historico; // Historico de equipas
    private ArrayList<Integer> atributos; // Atributos do jogador

    public Jogador() {
        this.nome = "n/a";
        this.equipa = "n/a";
        this.posicao = 0;
        this.id = 0;
        this.historico = new ArrayList<>();
        this.atributos = new ArrayList<>();
        for (int i = 0; i < 7; i++) this.atributos.add(0);
    }

    public Jogador(String nom, String eq, int pos, int ide, ArrayList<String> hist, ArrayList<Integer> ats) {
        this.nome = nom;
        this.equipa = eq;
        this.posicao = pos;
        this.id = ide;
        this.historico = new ArrayList<String>(hist);
        this.atributos = new ArrayList<Integer>(ats);
    }

    public Jogador(Jogador j) {
        this(j.nome, j.equipa, j.posicao, j.id, j.historico, j.atributos);
    }

    public Jogador clone() {
        return new Jogador(this);
    }

    public boolean equals(Object o) {
        if (this == o) return true;

        if (o == null || o.getClass() != this.getClass()) return false;

        Jogador that = (Jogador) o;
        return this.posicao == that.posicao &&
                this.id == that.id && this.nome.equals(that.nome) &&
                this.equipa.equals(that.equipa) &&
                this.historico.equals(that.historico) &&
                this.atributos.equals(that.atributos);
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();

        sb.append("Jogador: "); sb.append(this.nome);
        sb.append("\nEquipa: "); sb.append(this.equipa);
        sb.append("\nPosição "); sb.append(this.posicao);
        sb.append("\nId: "); sb.append(this.id);
        sb.append("\nHistórico de equipas: "); sb.append(this.historico.toString());
        sb.append("\nAtributos: "); sb.append(this.atributos.toString());

        return sb.toString();
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
    public int getPosicao() {
        return this.posicao;
    }
    public void setPosicao(int pos) {
        this.posicao = pos;
    }
    public int getId() {
        return this.id;
    }
    public void setId(int id) {
        this.id = id;
    }
    public ArrayList<String> getHistorico() {
        return new ArrayList<String>(this.historico);
    }
    public void setHistorico(ArrayList<String> hist) {
        this.historico = new ArrayList<String>(hist);
    }
    public void setAtributo(int indice, int at) {
        this.atributos.set(indice, at);
    }
    public int getAtributo(int indice) {
        return this.atributos.get(indice);
    }
    public void setVelocidade(int at) {
        setAtributo(VELOCIDADE, at);
    }
    public int getVelocidade() {
        return getAtributo(VELOCIDADE);
    }
    public void setResistencia(int at) {
        setAtributo(RESISTENCIA, at);
    }
    public int getResistencia() {
        return getAtributo(RESISTENCIA);
    }
    public void setDestreza(int at) {
        setAtributo(DESTREZA, at);
    }
    public int getDestreza() {
        return getAtributo(DESTREZA);
    }
    public void setImpulsao(int at) {
        setAtributo(IMPULSAO, at);
    }
    public int getImpulsao() {
        return getAtributo(IMPULSAO);
    }
    public void setJogoCabeca(int at) {
        setAtributo(JOGOCABECA, at);
    }
    public int getJogoCabeca() {
        return getAtributo(JOGOCABECA);
    }
    public void setRemate(int at) {
        setAtributo(REMATE, at);
    }
    public int getRemate() {
        return getAtributo(REMATE);
    }
    public void setPasse(int at) {
        setAtributo(PASSE, at);
    }
    public int getPasse() {
        return getAtributo(PASSE);
    }
}
