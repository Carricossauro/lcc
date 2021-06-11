package projeto;

import java.time.LocalDate;
import java.util.HashMap;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

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
    private final int posseIntervalo;
    private int posicaoBola;
    private int substituicoesCasa;
    private int substituicoesFora;

    public SimulacaoJogo(Equipa eC, Equipa eF) throws JogadorNaoExisteException, TitularesNaoDefinidosException, NullPointerException {
        this.jogo = new Jogo(eC.getNome(), eF.getNome(), 0,0,
                LocalDate.now(),  eC.getListTitulares(), new HashMap<>(),  eF.getListTitulares(), new HashMap<>());
        this.equipaCasa = eC.clone();
        this.equipaFora = eF.clone();
        this.overallCasa = this.equipaCasa.calculaOverallTitulares();
        this.overallFora = this.equipaFora.calculaOverallTitulares();
        this.posseBola = pontapeDeSaida();
        this.posseIntervalo = -this.posseBola;
        this.posicaoBola = MEIO;
        this.substituicoesCasa = 3;
        this.substituicoesFora = 3;
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

        Jogador jogadorSai = (equipa == CASA) ? this.equipaCasa.getJogador(sai) : this.equipaFora.getJogador(sai);
        Jogador jogadorEntra = (equipa == CASA) ? this.equipaCasa.getJogador(entra) : this.equipaFora.getJogador(entra);

        switch (jogadorSai.getClass().getSimpleName()) {
            case "Defesa":
            case "Lateral":
                if (!jogadorEntra.getClass().getSimpleName().equals("Lateral") && !jogadorEntra.getClass().getSimpleName().equals("Defesa"))
                    throw new SubstituicaoErradaException("Posiçoes incompativeis.");
                break;
            case "Medio":
                if (!jogadorEntra.getClass().getSimpleName().equals("Lateral") && !jogadorEntra.getClass().getSimpleName().equals("Medio"))
                    throw new SubstituicaoErradaException("Posiçoes incompativeis.");
                break;
            case "Avancado":
                if (!jogadorEntra.getClass().getSimpleName().equals("Avancado") && !jogadorEntra.getClass().getSimpleName().equals("Medio"))
                    throw new SubstituicaoErradaException("Posiçoes incompativeis.");
                break;
            default:
                if (!jogadorEntra.getClass().getSimpleName().equals(jogadorSai.getClass().getSimpleName()))
                    throw new SubstituicaoErradaException("Posiçoes incompativeis.");
                break;
        }

        try {
            if (equipa == CASA) {
                this.equipaCasa.substituicao(entra, sai);
                cond = true;
                this.jogo.adicionaSubstituicaoCasa(entra, sai);
                this.overallCasa = this.equipaCasa.calculaOverallTitulares();
            } else {
                this.equipaFora.substituicao(entra, sai);
                cond = true;
                this.jogo.adicionaSubstituicaoFora(entra, sai);
                this.overallFora = this.equipaFora.calculaOverallTitulares();
            }
        } catch (JogadorNaoExisteException | SubstituicaoErradaException | TitularesNaoDefinidosException exc) {
            if (cond) {
                if (equipa == CASA) {
                    this.equipaCasa.substituicao(sai, entra);
                } else this.equipaFora.substituicao(sai, entra);
            }
            throw new SubstituicaoErradaException("Substituiçao Falhada. Tente outra vez.");
        }
    }

    public Jogo simulaJogo(View view) throws JogadorNaoExisteException, EquipaNaoDefinidaException {
        int numeroJogadas = (this.overallCasa + this.overallFora) / 6;
        int jogadas = 0;
        view.printOveralls(this.overallCasa, this.overallFora);

        Random rand = new Random();
        for (jogadas = 0; jogadas < numeroJogadas / 2; jogadas++) {
            if (this.substituicoesCasa > 0) {
                if (rand.nextInt(numeroJogadas*10) < jogadas && !this.equipaCasa.getJogadoresNaoTitulares().isEmpty()) {
                    view.substituicao(this.equipaCasa.getNome(), this.equipaCasa.getListTitulares(), this.equipaCasa.getJogadoresNaoTitulares(), CASA);
                    substituicoesCasa--;
                }
            }
            if (this.substituicoesFora > 0) {
                if (rand.nextInt(numeroJogadas*10) < jogadas && !this.equipaFora.getJogadoresNaoTitulares().isEmpty()) {
                    view.substituicao(this.equipaFora.getNome(), this.equipaFora.getListTitulares(), this.equipaFora.getJogadoresNaoTitulares(), FORA);
                    substituicoesFora--;
                }
            }
            jogada(this.posseBola);
            view.printJogada(jogadas, this.posseBola, this.jogo.toString());
        }
        view.printIntervalo();
        this.posseBola = this.posseIntervalo;

        for (; jogadas < numeroJogadas; jogadas++) {
            if (this.substituicoesCasa > 0) {
                if (rand.nextInt(numeroJogadas*3) < numeroJogadas && !this.equipaCasa.getJogadoresNaoTitulares().isEmpty()) {
                    view.substituicao(this.equipaCasa.getNome(), this.equipaCasa.getListTitulares(), this.equipaCasa.getJogadoresNaoTitulares(), CASA);
                    substituicoesCasa--;
                }
            }
            if (this.substituicoesFora > 0) {
                if (rand.nextInt(numeroJogadas*3) < numeroJogadas && !this.equipaFora.getJogadoresNaoTitulares().isEmpty()) {
                    view.substituicao(this.equipaFora.getNome(), this.equipaFora.getListTitulares(), this.equipaFora.getJogadoresNaoTitulares(), FORA);
                    substituicoesFora--;
                }
            }
            jogada(this.posseBola);
            view.printJogada(jogadas, this.posseBola, this.jogo.toString());
        }
        return this.jogo.clone();
    }
}