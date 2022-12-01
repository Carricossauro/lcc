package projeto;

import java.io.*;
import java.util.*;

public class Controller implements Serializable {
    private static final int CASA = -1;
    private static final int FORA = 1;

    private Map<String,Equipa> equipas;
    private List<Jogo> jogos;
    private SimulacaoJogo simulacao;

    public Controller(Map<String,Equipa> equipas, List<Jogo> jogos) {
        this.equipas = equipas;
        this.jogos = jogos;
        this.simulacao = null;
    }

    public void lerEquipas(String ficheiro) throws JogadorJaExisteException, LinhaIncorretaException {
        Map<String, Equipa> novasEquipas = new HashMap<>();
        List<Jogo> novosJogos = new ArrayList<>();
        Parser.parse(novasEquipas, novosJogos, ficheiro);

        for (String nome: novasEquipas.keySet()) {
            this.equipas.put(nome, novasEquipas.get(nome));
        }
        this.jogos.addAll(novosJogos);
    }

    public void gravarEstado(String ficheiro) throws IOException {
        SaveGame.gravar(equipas, jogos, ficheiro);
    }

    public void lerEquipasObjetos(String ficheiro) throws IOException, ClassNotFoundException {
        FileInputStream fis = new FileInputStream(ficheiro);
        ObjectInputStream ois = new ObjectInputStream(fis);

        Controller controladorLido = (Controller) ois.readObject();

        controladorLido.equipas.forEach((k,v)->this.equipas.put(k,v));
        this.jogos.addAll(controladorLido.jogos);

        ois.close();
        fis.close();
    }

    public void gravarEstadoObjetos(String ficheiro) throws IOException {
        FileOutputStream fos = new FileOutputStream(ficheiro);
        ObjectOutputStream oos = new ObjectOutputStream(fos);

        oos.writeObject(this);

        oos.close();
        fos.close();
    }

    public void criarEquipa(String equipa) throws EquipaJaExisteException {
        if (!equipas.containsKey(equipa)) {
            equipas.put(equipa, new Equipa(equipa));
        } else throw new EquipaJaExisteException();
    }

    public List<String> nomesEquipas() {
        return new ArrayList<>(this.equipas.keySet());
    }

    public void adicionarJogador(int posicao, String nome, int numero, String equipa, Map<String, Integer> atributos, int atributoExtra1, int atributoExtra2) throws NumeroInvalidoException, JogadorJaExisteException {
        Jogador jogador;

        switch (posicao) {
            case 0:
                jogador = new GuardaRedes(nome, numero, new ArrayList<>(),atributos, atributoExtra1);
                break;
            case 1:
                jogador = new Lateral(nome, numero, new ArrayList<>(), atributos, atributoExtra1, atributoExtra2);
                break;
            case 2:
                jogador = new Defesa(nome, numero, new ArrayList<>(), atributos, atributoExtra1, atributoExtra2);
                break;
            case 3:
                jogador = new Medio(nome, numero, new ArrayList<>(), atributos, atributoExtra1, atributoExtra2);
                break;
            case 4:
                jogador = new Avancado(nome, numero, new ArrayList<>(), atributos, atributoExtra1, atributoExtra2);
                break;
            default:
                throw new NumeroInvalidoException();
        }

        this.equipas.get(equipa).adicionaJogador(jogador, numero);
    }

    public Map<Integer, String> jogadoresEquipa(String equipa) {
        return this.equipas.get(equipa).getJogadores();
    }

    public void transferenciaJogador(String equipaSai, String equipaEntra, int camisola, int novaCamisola) throws JogadorNaoExisteException, JogadorJaExisteException, EquipaNaoDefinidaException {
        if (!this.equipas.containsKey(equipaSai) || !this.equipas.containsKey(equipaEntra)) throw new EquipaNaoDefinidaException();

        this.equipas.get(equipaSai).transfere(this.equipas.get(equipaEntra), camisola, novaCamisola);
    }

    public void removerEquipa(String equipa) throws EquipaNaoDefinidaException {
        if (!this.equipas.containsKey(equipa)) throw new EquipaNaoDefinidaException();

        Map<Integer, String> jogadoresRenegados = this.equipas.get(equipa).getJogadores();

        for (int numero: jogadoresRenegados.keySet()) {
            int novoNumero = 0;
            boolean cond = true;
            while (cond) {
                try {
                    this.equipas.get(equipa).transfere(this.equipas.get("Jogadores sem clube"), numero, novoNumero++);
                    cond = false;
                } catch (JogadorJaExisteException ignored) {
                } catch (JogadorNaoExisteException e) {
                    cond = false;
                }
            }
        }

        this.equipas.remove(equipa);
    }

    public void removerJogador(String equipa, int numero) throws EquipaNaoDefinidaException, JogadorNaoExisteException {
        if (!this.equipas.containsKey(equipa)) throw new EquipaNaoDefinidaException();

        this.equipas.get(equipa).removeJogador(numero);
    }

    public int overallEquipa(String equipa) throws EquipaNaoDefinidaException {
        if (!this.equipas.containsKey(equipa)) throw new EquipaNaoDefinidaException();

        return this.equipas.get(equipa).calculaOverall();
    }

    public String informacaojogador(String equipa, int numero) throws EquipaNaoDefinidaException, JogadorNaoExisteException {
        if (!this.equipas.containsKey(equipa)) throw new EquipaNaoDefinidaException();

        return this.equipas.get(equipa).getJogador(numero).toString();
    }

    public Map<Integer, String> jogadoresPosicao(String equipa, String pos) throws EquipaNaoDefinidaException {
        if (!this.equipas.containsKey(equipa)) throw new EquipaNaoDefinidaException();

        return this.equipas.get(equipa).getJogadoresPorPosicao(pos);
    }

    public void setTitulares(String equipa, int[] array) throws EquipaNaoDefinidaException {
        if (!this.equipas.containsKey(equipa)) throw new EquipaNaoDefinidaException();

        this.equipas.get(equipa).setTitulares(array);
    }

    public void simularJogo(String casa, String fora, View view) throws EquipaNaoDefinidaException, JogadorNaoExisteException, TitularesNaoDefinidosException {
        if (!this.equipas.containsKey(casa) || !this.equipas.containsKey(fora)) throw new EquipaNaoDefinidaException();

        this.simulacao = new SimulacaoJogo(this.equipas.get(casa), this.equipas.get(fora));

        this.jogos.add(this.simulacao.simulaJogo(view));

        this.simulacao = null;
    }

    public int overallJogador(String equipa, int numero) throws JogadorNaoExisteException, EquipaNaoDefinidaException {
        if (!this.equipas.containsKey(equipa)) throw new EquipaNaoDefinidaException();

        return this.equipas.get(equipa).getJogador(numero).calculaOverall();
    }

    public String posicaoJogador(String equipa, int numero) throws EquipaNaoDefinidaException, JogadorNaoExisteException {
        if (!this.equipas.containsKey(equipa)) throw new EquipaNaoDefinidaException();

        return this.equipas.get(equipa).getJogador(numero).getClass().getSimpleName();
    }

    public void processaSubstituicao(int entra, int sai, int equipa) throws JogadorNaoExisteException, SubstituicaoErradaException {
        this.simulacao.processaSubstituicao(entra, sai, equipa);
    }
}