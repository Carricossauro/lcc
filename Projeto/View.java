package projeto;

import java.io.IOException;
import java.util.*;

public class View {
    private Controller controller;
    private Scanner input;

    public View(Controller controller, Scanner input) {
        this.controller = controller;
        this.input = input;
    }

    public void run() {
        System.out.println(
                "  ____                                        _               _                               ______   __  __ \n" +
                " |  _ \\                                      (_)             | |                             |  ____| |  \\/  |\n" +
                " | |_) |   ___   _ __ ___    ______  __   __  _   _ __     __| |   ___       __ _    ___     | |__    | \\  / |\n" +
                " |  _ <   / _ \\ | '_ ` _ \\  |______| \\ \\ / / | | | '_ \\   / _` |  / _ \\     / _` |  / _ \\    |  __|   | |\\/| |\n" +
                " | |_) | |  __/ | | | | | |           \\ V /  | | | | | | | (_| | | (_) |   | (_| | | (_) |   | |      | |  | |\n" +
                " |____/   \\___| |_| |_| |_|            \\_/   |_| |_| |_|  \\__,_|  \\___/     \\__,_|  \\___/    |_|      |_|  |_|\n");

        int opcao;
        do {
            opcao = receberComandos();
            switch (opcao) {
                case 0:
                    System.out.println("\nSimulação encerrada.");
                    break;
                case 1:
                    lerFicheiro();
                    break;
                case 2:
                    gravarEmFicheiro();
                    break;
                case 3:
                    lerFicheiroObjetos();
                    break;
                case 4:
                    gravarEmFicheiroObjetos();
                    break;
                case 5:
                    adicionarEquipa();
                    break;
                case 6:
                    adicionarJogador();
                    break;
                case 7:
                    transferirJogador();
                    break;
                case 8:
                    removerEquipa();
                    break;
                case 9:
                    removerJogador();
                    break;
                case 10:
                    simulacao();
                    break;
                case 11:
                    informacao();
                    break;
                default:
                    System.out.println("\nOpção Inválida. Escolha um numero entre 0 e 11.\n");
                    break;
            }
        } while (opcao != 0);
    }

    public int receberComandos() {
        try {
            System.out.println("Introduza a opção que preferir:\n" +
                    "0. Sair\n" +
                    "1. Carregar ficheiro\n" +
                    "2. Gravar estado em ficheiro\n" +
                    "3. Carregar ficheiro de objetos\n" +
                    "4. Gravar estado em ficheiro de objetos\n" +
                    "5. Criar Equipa\n" +
                    "6. Adicionar Jogador\n" +
                    "7. Transferir Jogador\n" +
                    "8. Remover Equipa\n" +
                    "9. Remover Jogador\n" +
                    "10. Simular Jogo\n" +
                    "11. Informação\n");

            System.out.print("Opção: ");
            return Integer.parseInt(this.input.next());
        } catch (Exception e) {
            return 99;
        }
    }

    public void lerFicheiro() {
        try {
            System.out.print("Introduza o nome do ficheiro que pretende ler: ");

            this.controller.lerEquipas(this.input.next());

            System.out.println("\nInformação do ficheiro carregada.\n");
        } catch (LinhaIncorretaException | JogadorJaExisteException e) {
            System.out.println("\nFicheiro está mal formado.\n");
        } catch (Exception e) {
            System.out.println("\nOcorreu um erro. Tente outra vez.\n");
        }
    }

    public void gravarEmFicheiro() {
        System.out.print("Introduza o nome do ficheiro onde pretende gravar: ");
        String ficheiro = this.input.next();

        try {
            this.controller.gravarEstado(ficheiro);
            System.out.println("\nGravação concluída.\n");
        } catch (IOException e) {
            System.out.println("\nImpossível gravar no ficheiro " + ficheiro + ".\n");
        } catch (Exception e) {
            System.out.println("\nOcorreu um erro. Tente outra vez.\n");
        }
    }

    public void lerFicheiroObjetos() {
        try {
            System.out.print("Introduza o nome do ficheiro que pretende ler: ");

            this.controller.lerEquipasObjetos(this.input.next());

            System.out.println("\nInformação do ficheiro carregada.\n");
        } catch (IOException | ClassNotFoundException e) {
            System.out.println("\nImpossivel ler ficheiro.\n");
        } catch (Exception e) {
            System.out.println("\nOcorreu um erro. Tente outra vez.\n");
        }
    }

    public void gravarEmFicheiroObjetos() {
        System.out.print("Introduza o nome do ficheiro onde pretende gravar: ");
        String ficheiro = this.input.next();

        try {
            this.controller.gravarEstadoObjetos(ficheiro);
            System.out.println("\nGravação concluída.\n");
        } catch (IOException e) {
            System.out.println("\nImpossível gravar no ficheiro " + ficheiro + ".\n");
            System.out.println(e.toString());
        } catch (Exception e) {
            System.out.println("\nOcorreu um erro. Tente outra vez.\n");
            System.out.println(e.toString());
        }
    }

    public void adicionarEquipa() {
        System.out.print("Introduza o nome da equipa que pretende criar: ");
        String equipa = input.next();

        try {
            this.controller.criarEquipa(equipa);
            System.out.println("\nEquipa criada com sucesso.\n");
        } catch (EquipaJaExisteException e) {
            System.out.println("\nA equipa " + equipa + " ja existe.\n");
        } catch (Exception e) {
            System.out.println("\nOcorreu um erro. Tente outra vez.\n");
        }
    }

    public void adicionarJogador() {
        try {
            System.out.println("Escolha a equipa a que pertence adicionar o jogador: ");
            List<String> nomesEquipas = this.controller.nomesEquipas();

            for(int i = 0; i < nomesEquipas.size(); i++) System.out.println(i + ". " + nomesEquipas.get(i));
            System.out.print("\nEquipa (0-" + (nomesEquipas.size()-1) + "): ");

            int eq = Integer.parseInt(this.input.next());

            String equipa = nomesEquipas.get(eq);

            System.out.println("\nIntroduza a posiçao do jogador: ");
            System.out.println("0. Guarda-Redes");
            System.out.println("1. Lateral");
            System.out.println("2. Defesa");
            System.out.println("3. Medio");
            System.out.println("4. Avançado");
            System.out.print("Posiçao: ");
            int posicao = Integer.parseInt(this.input.next());

            System.out.print("\nIntroduza o nome do jogador: ");
            String nome =  input.next();
            System.out.print("\nEscolha um numero para o jogador: ");
            int numero = Integer.parseInt(this.input.next());
            if (numero < 0 || numero > 99) throw new NumeroInvalidoException();

            Map<String, Integer> atributos = new HashMap<>();
            System.out.println("\nAtributos: ");
            System.out.print("Velocidade: ");
            atributos.put("velocidade", Integer.parseInt(this.input.next()));
            System.out.print("\nResistencia: ");
            atributos.put("resistencia", Integer.parseInt(this.input.next()));
            System.out.print("\nDestreza: ");
            atributos.put("destreza", Integer.parseInt(this.input.next()));
            System.out.print("\nImpulsao: ");
            atributos.put("impulsao", Integer.parseInt(this.input.next()));
            System.out.print("\nJogo de Cabeça: ");
            atributos.put("jogocabeca", Integer.parseInt(this.input.next()));
            System.out.print("\nRemate: ");
            atributos.put("remate", Integer.parseInt(this.input.next()));
            System.out.print("\nPasse: ");
            atributos.put("passe", Integer.parseInt(this.input.next()));

            if (atributos.values().stream().anyMatch(a-> a < 0 || a > 100)) throw new NumeroInvalidoException();

            Jogador jogador = null;
            switch (posicao) {
                case 0: // Guarda-Redes
                    System.out.print("\nElasticidade: ");
                    int elasticidade = Integer.parseInt(this.input.next());
                    if (elasticidade < 0 || elasticidade > 100) throw new NumeroInvalidoException();
                    this.controller.adicionarJogador(0,nome, numero, equipa, atributos, elasticidade, 0);
                    break;
                case 1: // Lateral
                    System.out.print("\nCruzamento: ");
                    int cruzamento = Integer.parseInt(this.input.next());
                    System.out.print("\nDrible: ");
                    int drible = Integer.parseInt(this.input.next());
                    if (cruzamento < 0 || cruzamento > 100 || drible < 0 || drible > 100) throw new NumeroInvalidoException();
                    this.controller.adicionarJogador(1,nome, numero, equipa, atributos, cruzamento, drible);
                    break;
                case 2: // Defesa
                    System.out.print("\nCorte: ");
                    int corte = Integer.parseInt(this.input.next());
                    System.out.print("\nInterseçao: ");
                    int intersecao = Integer.parseInt(this.input.next());
                    if (corte < 0 || corte > 100 || intersecao < 0 || intersecao > 100) throw new NumeroInvalidoException();
                    this.controller.adicionarJogador(2,nome, numero, equipa, atributos, corte, intersecao);
                    break;
                case 3: // Medio
                    System.out.print("\nInterseçao: ");
                    int interseca = Integer.parseInt(this.input.next());
                    System.out.print("\nVisao: ");
                    int visao = Integer.parseInt(this.input.next());
                    if (interseca < 0 || interseca > 100 || visao < 0 || visao > 100) throw new NumeroInvalidoException();
                    this.controller.adicionarJogador(3,nome, numero, equipa, atributos, interseca, visao);
                    break;
                case 4: // Avançado
                    System.out.print("\nFinalizaçao: ");
                    int finalizacao = Integer.parseInt(this.input.next());
                    System.out.print("\nCompostura: ");
                    int compostura = Integer.parseInt(this.input.next());
                    if (finalizacao < 0 || finalizacao > 100 || compostura < 0 || compostura > 100) throw new NumeroInvalidoException();
                    this.controller.adicionarJogador(4,nome, numero, equipa, atributos, finalizacao, compostura);
                    break;
                default:
                    System.out.println("\nA posiçao que escolheu nao existe.");
                    break;
            }

            System.out.println("Jogador adicionado com sucesso.");
        } catch (JogadorJaExisteException e) {
            System.out.println(e.getMessage());
        } catch (IndexOutOfBoundsException e) {
            System.out.println("\nA equipa que escolheu nao existe.\n");
        } catch (Exception e) {
            System.out.println("\nA informaçao submetida nao esta correta.\n");
        }
    }

    public void transferirJogador() {
        try {
            System.out.println("Escolha a equipa de onde pretende transferir o jogador:");
            List<String> nomesEquipas = this.controller.nomesEquipas();

            for(int i = 0; i < nomesEquipas.size(); i++) System.out.println(i + ". " + nomesEquipas.get(i));
            System.out.print("\nEquipa (0-" + (nomesEquipas.size()-1) + "): ");

            int eq = Integer.parseInt(this.input.next());
            String equipaSai = nomesEquipas.get(eq);

            Map<Integer,String> nomesJogadores = this.controller.jogadoresEquipa(equipaSai);
            for (int numero: nomesJogadores.keySet()) {
                System.out.println(numero + ". " + nomesJogadores.get(numero));
            }

            System.out.print("\nNumero de camisola: ");
            int camisola = Integer.parseInt(this.input.next());

            System.out.println("Escolha a equipa para onde pretende transferir o jogador:");
            nomesEquipas = this.controller.nomesEquipas();

            for(int i = 0; i < nomesEquipas.size(); i++) System.out.println(i + ". " + nomesEquipas.get(i));
            System.out.print("\nEquipa (0-" + (nomesEquipas.size()-1) + "): ");

            eq = Integer.parseInt(this.input.next());
            String equipaEntra = nomesEquipas.get(eq);

            nomesJogadores = this.controller.jogadoresEquipa(equipaEntra);
            System.out.println("Numero de camisola ja ocupados: ");
            for(int numero: nomesJogadores.keySet()) {
                System.out.print(numero + " ");
            }

            System.out.print("\nEscolha o novo numero de camisola: ");
            int novaCamisola = Integer.parseInt(this.input.next());

            this.controller.transferenciaJogador(equipaSai, equipaEntra, camisola, novaCamisola);

            System.out.println("\nJogador transferido com sucesso.\n");
        } catch (JogadorJaExisteException | JogadorNaoExisteException e) {
            System.out.println("\nEscolha de jogadores incorreta.\n");
        } catch (EquipaNaoDefinidaException e) {
            System.out.println("\nEquipa escolhida nao existe.\n");
        } catch (IndexOutOfBoundsException e) {
            System.out.println("\nNumero escolhido invalido.\n");
        } catch (Exception e) {
            System.out.println("\nOcorreu um erro. Tente outra vez.\n");
        }
    }

    public void removerEquipa() {
        try {
            System.out.println("Escolha a equipa que pretende remover: ");
            List<String> nomesEquipas = this.controller.nomesEquipas();

            for(int i = 0; i < nomesEquipas.size(); i++) System.out.println(i + ". " + nomesEquipas.get(i));
            System.out.print("\nEquipa (0-" + (nomesEquipas.size()-1) + "): ");

            int eq = Integer.parseInt(this.input.next());
            String equipa = nomesEquipas.get(eq);

            this.controller.removerEquipa(equipa);

            System.out.println("\nEquipa removida com sucesso.\n");
        } catch (EquipaNaoDefinidaException | IndexOutOfBoundsException e) {
            System.out.println("\nEquipa escolhida nao existe.\n");
        } catch (Exception e) {
            System.out.println("\nOcorreu um erro. Tente outra vez.\n");
        }
    }

    public void removerJogador() {
        try {
            System.out.println("Escolha a equipa de onde pretende remover o jogador: ");
            List<String> nomesEquipas = this.controller.nomesEquipas();

            for(int i = 0; i < nomesEquipas.size(); i++) System.out.println(i + ". " + nomesEquipas.get(i));
            System.out.print("\nEquipa (0-" + (nomesEquipas.size()-1) + "): ");

            int eq = Integer.parseInt(this.input.next());
            String equipa = nomesEquipas.get(eq);

            System.out.println("Escolha o jogador que pretende remover: ");
            Map<Integer, String> nomesJogadores = this.controller.jogadoresEquipa(equipa);

            for (int numero: nomesJogadores.keySet()) {
                System.out.println(numero + ". " + nomesJogadores.get(numero));
            }

            System.out.print("Numero de camisola do jogador: ");
            int jogador = Integer.parseInt(this.input.next());

            this.controller.removerJogador(equipa, jogador);
            System.out.println("\nJogador removido com sucesso.\n");
        } catch (EquipaNaoDefinidaException e) {
            System.out.println("\nEquipa escolhida nao existe.\n");
        } catch (JogadorNaoExisteException e) {
            System.out.println("\nJogador escolhido nao existe.\n");
        } catch (Exception e) {
            System.out.println("\nOcorreu um erro. Tente outra vez.\n");
        }
    }

    public void informacao() {
        try {
            System.out.println("Escolha a equipa que pretende consultar: ");
            List<String> nomesEquipas = this.controller.nomesEquipas();

            for(int i = 0; i < nomesEquipas.size(); i++) System.out.println(i + ". " + nomesEquipas.get(i));
            System.out.print("\nEquipa (0-" + (nomesEquipas.size()-1) + "): ");

            int eq = Integer.parseInt(this.input.next());
            String equipa = nomesEquipas.get(eq);


            System.out.println("\nIntroduza a opção que preferir: \n" +
                    "1. Consultar Overall de Equipa\n" +
                    "2. Consultar Informaçao de Jogadores");

            System.out.print("\nOpçao: ");
            int opcao = Integer.parseInt(this.input.next());

            switch (opcao) {
                case 1:
                    System.out.println("\nA equipa " + equipa + " tem overall de " + this.controller.overallEquipa(equipa) + ".\n");
                    break;
                case 2:
                    informacaoJogador(equipa);
                    break;
                default:
                    System.out.println("\nOpcao invalida.\n");
                    break;
            }
        } catch (JogadorNaoExisteException e) {
            System.out.println("\nJogador escolhido nao existe.\n");
        } catch (EquipaNaoDefinidaException e) {
            System.out.println("\nEquipa escolhida nao existe.\n");
        } catch (Exception e) {
            System.out.println("\nOcorreu um erro. Tente outra vez.\n");
        }
    }
    
    public void informacaoJogador(String equipa) throws JogadorNaoExisteException, EquipaNaoDefinidaException {
        System.out.println("Escolha o jogador que pretende consultar: ");

        Map<Integer,String> nomesJogadores = this.controller.jogadoresEquipa(equipa);
        for (int numero: nomesJogadores.keySet()) {
            System.out.println(numero + ". " + nomesJogadores.get(numero));
        }

        System.out.print("\nNumero de camisola: ");
        int camisola = Integer.parseInt(this.input.next());

        System.out.println(this.controller.informacaojogador(equipa, camisola));
    }

    public void simulacao() {
        try {
            System.out.println("Escolha as equipas que jogam: ");
            List<String> nomesEquipas = this.controller.nomesEquipas();

            for(int i = 0; i < nomesEquipas.size(); i++) System.out.println(i + ". " + nomesEquipas.get(i));
            System.out.print("\nCasa: (0-" + (nomesEquipas.size()-1) + "): ");

            int eqCasa = Integer.parseInt(this.input.next());
            String casa = nomesEquipas.get(eqCasa);

            System.out.print("Fora: (0-" + (nomesEquipas.size()-1) + "): ");

            int eqFora = Integer.parseInt(this.input.next());
            String fora = nomesEquipas.get(eqFora);

            System.out.println("\nEscolha o esquema tatico da equipa de casa: \n" +
                    "1. 1-4-3-3\n" +
                    "2. 1-4-2-2\n");

            System.out.print("Esquema tatico: ");
            int taticaCasa = Integer.parseInt(this.input.next());
            switch (taticaCasa) {
                case 1:
                    escolhe433(casa);
                    break;
                case 2:
                    escolhe442(casa);
                    break;
                default:
                    break;
            }


            System.out.println("\nEscolha o esquema tatico da equipa de fora: \n" +
                    "1. 1-4-3-3\n" +
                    "2. 1-4-2-2\n");

            System.out.print("Esquema tatico: ");
            int taticaFora = Integer.parseInt(this.input.next());
            switch (taticaFora) {
                case 1:
                    escolhe433(fora);
                    break;
                case 2:
                    escolhe442(fora);
                    break;
                default:
                    break;
            }

            this.controller.simularJogo(casa, fora);
        } catch (SimulacaoImpossivelException e) {
            System.out.println("\nNao foi possivel fazer a simulacao do jogo.\n");
        } catch (Exception e) {
            System.out.println("\nOcorreu um erro. Tente outra vez.\n");
        }
    }

    public void escolhe433(String equipa) throws SimulacaoImpossivelException {
        try {
            System.out.println("Escolha de titulares: ");
            Integer[] titulares = new Integer[11];
            int i = 0;

            titulares[i++] = escolheJogadorPorPosicao(equipa, "GuardaRedes", Arrays.asList(titulares));

            for (; i < 3; i++) titulares[i] = escolheJogadorPorPosicao(equipa, "Defesa", Arrays.asList(titulares));

            for (; i < 5; i++) titulares[i] = escolheJogadorPorPosicao(equipa, "Lateral", Arrays.asList(titulares));

            for (; i < 8; i++) titulares[i] = escolheJogadorPorPosicao(equipa, "Medio", Arrays.asList(titulares));

            for (; i < 11; i++) titulares[i] = escolheJogadorPorPosicao(equipa, "Avancado", Arrays.asList(titulares));

            int[] array = new int[11];
            for (int p = 0; p < 11; p++) array[p] = titulares[p];
            this.controller.setTitulares(equipa, array);
        } catch (EquipaNaoDefinidaException e){
            System.out.println("\nEquipa escolhida nao existe.\n");
        } catch (Exception e) {
            throw new SimulacaoImpossivelException();
        }
    }

    public void escolhe442(String equipa) throws SimulacaoImpossivelException {
        try {
            System.out.println("Escolha de titulares: ");
            Integer[] titulares = new Integer[11];
            int i = 0;

            titulares[i++] = escolheJogadorPorPosicao(equipa, "GuardaRedes", Arrays.asList(titulares));

            for (; i < 3; i++) titulares[i] = escolheJogadorPorPosicao(equipa, "Defesa", Arrays.asList(titulares));

            for (; i < 5; i++) titulares[i] = escolheJogadorPorPosicao(equipa, "Lateral", Arrays.asList(titulares));

            for (; i < 9; i++) titulares[i] = escolheJogadorPorPosicao(equipa, "Medio", Arrays.asList(titulares));

            for (; i < 11; i++) titulares[i] = escolheJogadorPorPosicao(equipa, "Avancado", Arrays.asList(titulares));

            int[] array = new int[11];
            for (int p = 0; p < 11; p++) array[p] = titulares[p];
            this.controller.setTitulares(equipa, array);
        } catch (EquipaNaoDefinidaException e){
            System.out.println("\nEquipa escolhida nao existe.\n");
        } catch (Exception e) {
            throw new SimulacaoImpossivelException();
        }
    }

    public int escolheJogadorPorPosicao(String equipa, String  pos, List<Integer> titulares) throws Exception {
        while (true) {
            try {
                System.out.println("\nOpçoes para " + pos + ": ");
                Map<Integer, String> jogadoresPos = this.controller.jogadoresPosicao(equipa, pos);
                Map<Integer, String> jogadoresPosExtra = new HashMap<>();
                String posExtra = "";

                switch (pos) {
                    case "Avancado":
                        posExtra = "Medio";
                        jogadoresPosExtra = this.controller.jogadoresPosicao(equipa, "Medio");
                        break;
                    case "Medio":
                        posExtra = "Lateral";
                        jogadoresPosExtra = this.controller.jogadoresPosicao(equipa, "Lateral");
                        break;
                    case "Lateral":
                        posExtra = "Defesa";
                        jogadoresPosExtra = this.controller.jogadoresPosicao(equipa, "Defesa");
                        break;
                    case "Defesa":
                        posExtra = "Lateral";
                        jogadoresPosExtra = this.controller.jogadoresPosicao(equipa, "Lateral");
                        break;
                }

                if (jogadoresPosExtra.isEmpty() && jogadoresPos.isEmpty()) throw new EquipaNaoDefinidaException();

                for (int numero: jogadoresPos.keySet()) {
                    if (!titulares.contains(numero)) System.out.println(numero + ". " + jogadoresPos.get(numero) + " - " + pos);
                }
                for (int numero: jogadoresPosExtra.keySet()) {
                    if (!titulares.contains(numero)) System.out.println(numero + ". " + jogadoresPosExtra.get(numero) + " - " + posExtra);
                }

                System.out.print("\nNumero de camisola: ");
                int numero = Integer.parseInt(this.input.next());

                if (!jogadoresPos.containsKey(numero) && !jogadoresPosExtra.containsKey(numero)) throw new JogadorNaoExisteException();

                return numero;
            } catch (JogadorNaoExisteException e) {
                System.out.println("\nJogador escolhido nao existe.\n");
            }
        }
    }
}