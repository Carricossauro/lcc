package projeto;

import java.io.FileWriter;
import java.io.IOException;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

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

    public Equipa(String nome) {
        this.nome = nome;
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
        sb.append(x.toString());
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

    public int calculaOverallTitulares() throws TitularesNaoDefinidosException, JogadorNaoExisteException {
        int soma = 0;
        for (int i = 0; i < 11; i++) {
            int jogador = this.titulares[i];
            if (jogador == -1) throw new TitularesNaoDefinidosException("Titulares nao definidos");
            if (!this.jogadores.containsKey(jogador)) throw new JogadorNaoExisteException("Nao existe jogador com camisola " + jogador);
            soma += this.jogadores.get(jogador).calculaOverall();
        }
        return soma/11;
    }

    public int calculaOverall() throws EquipaNaoDefinidaException {
        if (this.jogadores.isEmpty()) throw new EquipaNaoDefinidaException("Equipa nao tem jogadores");
        return (int) this.jogadores.values().stream().mapToInt(Jogador::calculaOverall).average().getAsDouble();
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
        if (eq.jogadores.containsKey(numCamisolaNovo)) throw new JogadorJaExisteException();
        if (!this.jogadores.containsKey(numCamisola)) throw new JogadorNaoExisteException();
        Jogador j = getJogador(numCamisola);
        this.removeJogador(numCamisola);
        j.adicionarAoHistorico(this.nome);
        eq.adicionaJogador(j, numCamisolaNovo);
    }

    public int[] getTitulares() {
        int[] titulares = new int[11];
        System.arraycopy(this.titulares, 0, titulares, 0, 11);
        return titulares;
    }

    public List<Integer> getListTitulares() {
        List<Integer> lista = new ArrayList<>();
        for (int i = 0; i < 11; i++) lista.add(this.titulares[i]);
        return lista;
    }

    public void setTitulares(int[] titulares) {
        this.titulares = new int[11];
        System.arraycopy(titulares,0,this.titulares,0,11);
    }

    public void substituicao(int entra, int sai) throws SubstituicaoErradaException, JogadorNaoExisteException {
        if (!this.jogadores.containsKey(entra)) throw new JogadorNaoExisteException("Nao existe jogador com numero " + entra);
        if (!this.jogadores.containsKey(sai)) throw new JogadorNaoExisteException("Nao existe jogador com numero " + sai);

        boolean subs = false;
        for (int i = 0; i < 11; i++) {
            int num = this.titulares[i];
            if (num == entra) throw new SubstituicaoErradaException("O jogador com numero " + entra + " ja esta em campo");
            if (num == sai) {
                this.titulares[i] = entra;
                subs = true;
            }
        }
        if (!subs) throw new SubstituicaoErradaException("Nao existe jogador em campo com numero " + sai);
    }

    public String getNome(){
        return this.nome;
    }

    public void setNome(String n){
        this.nome = n;
    }

    public static Equipa parse(String input){
        String[] campos = input.split(",");
        return new Equipa(campos[0]);
    }

    public void escrever(FileWriter writer) throws IOException {
        String eq = "Equipa:" + this.nome + "\n";
        writer.write(eq);
        writer.flush();
        for (Jogador jogador: this.jogadores.values()) {
            jogador.escrever(writer);
        }
    }

    public List<Integer> getJogadoresNaoTitulares() {
        return this.jogadores.keySet().stream().filter(a->Arrays.stream(titulares).noneMatch(b->b==a)).collect(Collectors.toList());
    }

    public Map<Integer, String> getJogadores() {
        Map<Integer, String> mapa = new HashMap<>();
        this.jogadores.forEach((key, value) -> mapa.put(key, value.getNome()));
        return mapa;
    }
}
