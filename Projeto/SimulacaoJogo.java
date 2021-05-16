package projeto;

import java.time.LocalDate;
import java.util.HashMap;
import java.util.Random;

public class SimulacaoJogo {
    private static final int CASA = -1;
    private static final int MEIO = 0;
    private static final int FORA = 1;

    private Jogo jogo;
    private Equipa equipaCasa;
    private Equipa equipaFora;
    private int overallCasa;
    private int overallFora;
    private int posseBola;
    private int posicaoBola;

    public SimulacaoJogo(Equipa eC, Equipa eF) throws JogadorNaoExisteException, TitularesNaoDefinidosException, NullPointerException {
        this.jogo = new Jogo(eC.getNome(), eF.getNome(), 0,0,
                LocalDate.now(),  eC.getListTitulares(), new HashMap<>(),  eF.getListTitulares(), new HashMap<>());
        this.equipaCasa = eC.clone();
        this.equipaFora = eF.clone();
        this.overallCasa = this.equipaCasa.calculaOverallTitulares();
        this.overallFora = this.equipaFora.calculaOverallTitulares();
        this.posseBola = pontapeDeSaida();
        this.posicaoBola = MEIO;
    }

    public int pontapeDeSaida() {
        Random rand = new Random();
        int moeda = rand.nextInt();
        if (moeda % 2 == 0) return CASA;
        else return FORA;
    }

    public void jogada(int atacante) {
        int oA;
        if (atacante == CASA) oA = overallCasa;
        else oA = overallFora;

        Random rand = new Random();
        int resultadoJogada = rand.nextInt(overallCasa + overallFora);
        if (resultadoJogada < oA) { // sucesso
            this.posicaoBola -= atacante;
            if (this.posicaoBola > 1) {
                this.jogo.goloCasa();
                this.posseBola = - atacante;
                this.posicaoBola = MEIO;
            }
            else if (this.posicaoBola < -1) {
                this.jogo.goloFora();
                this.posseBola = - atacante;
                this.posicaoBola = MEIO;
            }
        } else this.posseBola = -atacante;
    }

    public void processaSubstituicao(int entra, int sai, int equipa) throws JogadorNaoExisteException, SubstituicaoErradaException {
        boolean cond = false;
        try {
            if (equipa == CASA) {
                this.equipaCasa.substituicao(entra, sai);
                cond = true;
                this.jogo.adicionaSubstituicaoCasa(entra, sai);
            } else {
                this.equipaFora.substituicao(entra, sai);
                cond = true;
                this.jogo.adicionaSubstituicaoFora(entra, sai);
            }
        } catch (JogadorNaoExisteException | SubstituicaoErradaException exc) {
            System.out.println("Substituiçao falhada: " + exc.getMessage());
            if (cond) {
                if (equipa == CASA) {
                    this.equipaCasa.substituicao(sai, entra);
                } else this.equipaFora.substituicao(sai, entra);
            }
        }
    }

    public Jogo simulaJogo() {


        return this.jogo.clone();
    }
}