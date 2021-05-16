package projeto;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.stream.Collectors;

public class Equipa {
    private String nome;
    private Map<Integer,Jogador> jogadores;
    private int[] titulares;

    public Equipa (){
        this.nome = "n/a";
        this.jogadores = new HashMap<>();
        this.titulares = new int[11];
        for(int i = 0; i<11; i++){
            this.titulares [i] = -1;
        }
    }

    public Equipa (String nome, Map<Integer,Jogador> jogadores, int[] titulares){
        this.nome = nome;
        this.jogadores = jogadores.entrySet()
                                    .stream()
                                    .collect(Collectors.toMap(Map.Entry::getKey, a->a.getValue().clone()));
        this.titulares = new int[11];
        System.arraycopy(titulares,0,this.titulares,0,11);
    }

    public Equipa (Equipa e){
        this(e.nome, e.jogadores, e.titulares);
    }

    public Equipa clone () {
        return new Equipa(this);
    }

    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Equipa: "); sb.append(this.nome);
        sb.append("\nJogadores: ");this.jogadores.forEach((y,x) -> {
        sb.append("Camisola: "); sb.append(y.toString());
        sb.append("\n");sb.append(x.toString()); 
        });
        sb.append("\nTitulares: "); sb.append(Arrays.toString(this.titulares));
        return sb.toString();
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o==null || o.getClass() != this.getClass() ) return false;
        Equipa a = (Equipa) o;
        return this.nome.equals(a.nome) && this.jogadores.equals(a.jogadores) && Arrays.equals(this.titulares, a.titulares);
    }

    public int calculaOverall() throws TitularesNaoDefinidosException, JogadorNaoExisteException {
        int soma = 0;
        for (int i = 0; i < 11; i++) {
            int jogador = this.titulares[i];
            if (jogador == -1) throw new TitularesNaoDefinidosException("Titulares nao definidos");
            if (!this.jogadores.containsKey(jogador)) throw new JogadorNaoExisteException("Nao existe jogador com camisola " + jogador);
            soma += this.jogadores.get(jogador).calculaOverall();
        }
        return soma/11;
    }

    public void adicionaJogador(Jogador j, int numCamisola) throws JogadorJaExisteException {
        if (this.jogadores.containsKey(numCamisola)) throw new JogadorJaExisteException("Ja existe jogador com camisola " + numCamisola);
        j.setNumeroCamisola(numCamisola);
        this.jogadores.put(numCamisola, j.clone());
    }

    public void removeJogador(int numCamisola) throws JogadorNaoExisteException {
        if (!this.jogadores.containsKey(numCamisola)) throw new JogadorNaoExisteException("Nao existe jogador com camisola " + numCamisola);
        int x = this.JogadorETitular(numCamisola);
        if (x != -1) this.titulares[x] = -1;
        this.jogadores.remove(numCamisola);
    }

    public Jogador getJogador(int numCamisola) throws JogadorNaoExisteException {
        if (!this.jogadores.containsKey(numCamisola)) throw new JogadorNaoExisteException("Nao existe jogador com camisola " + numCamisola);
        return this.jogadores.get(numCamisola).clone();
    }

    public int JogadorETitular(int numCamisola) {
        for (int i = 0; i < 11; i++) {
            if (this.titulares[i] == numCamisola) return i;
        }
        return -1;
    }

    public void transfere(Equipa eq, int numCamisola, int numCamisolaNovo) throws JogadorJaExisteException, JogadorNaoExisteException, NullPointerException {
        Jogador j = getJogador(numCamisola);
        this.removeJogador(numCamisola);
        j.adicionarAoHistorico(this.nome);
        j.setEquipa(eq.nome);
        eq.adicionaJogador(j, numCamisolaNovo);
    }

    public int[] getTitulares() {
        int[] titulares = new int[11];
        System.arraycopy(this.titulares, 0, titulares, 0, 11);
        return titulares;
    }

    public void setTitulares(int[] titulares) {
        this.titulares = new int[11];
        System.arraycopy(titulares,0,this.titulares,0,11);
    }

    public String getNome(){
        return this.nome;
    }

    public void setNome(String n){
        this.nome = n;
    }

    // Falta metodo para determinar jogadores titulares
}
