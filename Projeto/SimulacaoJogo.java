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
    private int posseIntervalo;
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
            throw new SubstituicaoErradaException();
        }
    }

    public Jogo simulaJogo() throws JogadorNaoExisteException {
        int numeroJogadas = (this.overallCasa + this.overallFora) / 6;
        int jogadas = 0;
        System.out.println("Overall Casa: " + this.overallCasa);
        System.out.println("Overall Fora: " + this.overallFora);

        Random rand = new Random();
        for (jogadas = 0; jogadas < numeroJogadas / 2; jogadas++) {
            if (this.substituicoesCasa > 0) {
                if (rand.nextInt(numeroJogadas*10) < jogadas) {
                    substituicaoCasa();
                    substituicoesCasa--;
                }
            }
            if (this.substituicoesFora > 0) {
                if (rand.nextInt(numeroJogadas*10) < jogadas) {
                    substituicaoFora();
                    substituicoesFora--;
                }
            }
            jogada(this.posseBola);
            System.out.println("Jogada " + jogadas);
            System.out.println("Posse de bola: " + ((this.posseBola == CASA) ? "Casa" : "Fora"));
            System.out.println(jogo.toString() + "\n-------------");
        }
        System.out.println("Intervalo\n-------------");
        this.posseBola = this.posseIntervalo;

        for (; jogadas < numeroJogadas; jogadas++) {
            if (this.substituicoesCasa > 0) {
                if (rand.nextInt(numeroJogadas*3) < numeroJogadas) {
                    substituicaoCasa();
                    substituicoesCasa--;
                }
            }
            if (this.substituicoesFora > 0) {
                if (rand.nextInt(numeroJogadas*3) < numeroJogadas) {
                    substituicaoFora();
                    substituicoesFora--;
                }
            }
            jogada(this.posseBola);
            System.out.println("Jogada " + jogadas);
            System.out.println("Posse de bola: " + ((this.posseBola == CASA) ? "Casa" : "Fora"));
            System.out.println(jogo.toString() + "\n-------------");
        }
        return this.jogo.clone();
    }

    public void substituicaoCasa() throws JogadorNaoExisteException {
        System.out.println("Fase de substituiçao (Casa)");
        boolean cond = true;

        System.out.println("Jogadores em campo:");
        List<Integer> listaTitulares = this.equipaCasa.getListTitulares();
        for (int numero: listaTitulares) {
            System.out.println(numero + " " + this.equipaCasa.getJogador(numero).getNome() + " - " + this.equipaCasa.getJogador(numero).getClass().getSimpleName()
                    + " - " +this.equipaCasa.getJogador(numero).calculaOverall());
        }
        System.out.println("\nJogadores no banco:");
        List<Integer> jogadoresNaoTitulares = this.equipaCasa.getJogadoresNaoTitulares();
        for (int numero: jogadoresNaoTitulares) {
            System.out.println(numero + " " + this.equipaCasa.getJogador(numero).getNome() + " - " + this.equipaCasa.getJogador(numero).getClass().getSimpleName()
                    + " - " + this.equipaCasa.getJogador(numero).calculaOverall());
        }
        while (cond) {
            try {
                Scanner in = new Scanner(System.in);

                int sai = -1;
                System.out.print("Jogador que sai: ");
                sai = in.nextInt();

                int entra = -1;
                System.out.print("\nJogador que entra: ");
                entra = in.nextInt();

                processaSubstituicao(entra, sai, CASA);
                cond = false;
            } catch (Exception e) {
                System.out.println("Substituiçao Falhada. Tente outra vez.");
            }
        }
    }

    public void substituicaoFora() throws JogadorNaoExisteException {
        System.out.println("Fase de substituiçao (Fora)");
        boolean cond = true;

        System.out.println("Jogadores em campo:");
        List<Integer> listaTitulares = this.equipaFora.getListTitulares();
        for (int numero: listaTitulares) {
            System.out.println(numero + " " + this.equipaFora.getJogador(numero).getNome() + " - " + this.equipaFora.getJogador(numero).getClass().getSimpleName()
                    + " - " + this.equipaFora.getJogador(numero).calculaOverall());
        }
        System.out.println("\nJogadores no banco:");
        List<Integer> jogadoresNaoTitulares = this.equipaFora.getJogadoresNaoTitulares();
        for (int numero: jogadoresNaoTitulares) {
            System.out.println(numero + " " + this.equipaFora.getJogador(numero).getNome() + " - " + this.equipaFora.getJogador(numero).getClass().getSimpleName()
                    + " - " + this.equipaFora.getJogador(numero).calculaOverall());
        }
        while (cond) {
            try {
                Scanner in = new Scanner(System.in);

                int sai = -1;
                System.out.println("Jogador que sai: ");
                sai = in.nextInt();

                int entra = -1;
                System.out.println("Jogador que entra: ");
                entra = in.nextInt();

                processaSubstituicao(entra, sai, FORA);
                cond = false;
            } catch (Exception e) {
                System.out.println("Substituiçao Falhada. Tente outra vez.");
            }
        }
    }
}