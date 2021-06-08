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
        System.out.println("  ____                                        _               _                               ______   __  __ \n" +
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
                    adicionarEquipa();
                    break;
                case 4:
                    adicionarJogador();
                    break;
                case 5:
                    transferirJogador();
                    break;
                case 6:
                    removerEquipa();
                    break;
                default:
                    System.out.println("\nOpção Inválida. Escolha um numero entre 0 e 9.\n");
                    break;
            }
        } while (opcao != 0);
    }
    public int receberComandos() {
        System.out.println("Introduza a opção que preferir:\n" +
                "0. Sair\n" +
                "1. Carregar ficheiro\n" +
                "2. Gravar estado em ficheiro\n" +
                "3. Criar Equipa\n" +
                "4. Adicionar Jogador\n" +
                "5. Transferir Jogador\n" +
                "6. Remover Equipa\n" +
                "7. Remover Jogador\n" +
                "8. Simular Jogo\n" +
                "9. Informação\n");

        System.out.print("Opção: ");
        return this.input.nextInt();
    }

    public void lerFicheiro() {
        try {
            System.out.print("Introduza o nome do ficheiro que pretende ler: ");

            this.controller.lerEquipas(this.input.next());

            System.out.println("\nInformação do ficheiro carregada.\n");
        } catch (LinhaIncorretaException | JogadorJaExisteException e) {
            System.out.println("\nFicheiro está mal formado.\n");
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
        }
    }

    public void adicionarJogador() {
        try {
            System.out.println("Escolha a equipa a que pertence adicionar o jogador: ");
            List<String> nomesEquipas = this.controller.nomesEquipas();

            for(int i = 0; i < nomesEquipas.size(); i++) System.out.println(i + ". " + nomesEquipas.get(i));
            System.out.print("\nEquipa (0-" + (nomesEquipas.size()-1) + "): ");

            int eq = input.nextInt();

            String equipa = nomesEquipas.get(eq);

            System.out.println("\nIntroduza a posiçao do jogador: ");
            System.out.println("0. Guarda-Redes");
            System.out.println("1. Lateral");
            System.out.println("2. Defesa");
            System.out.println("3. Medio");
            System.out.println("4. Avançado");
            System.out.print("Posiçao: ");
            int posicao = input.nextInt();

            System.out.print("\nIntroduza o nome do jogador: ");
            String nome =  input.next();
            System.out.print("\nEscolha um numero para o jogador: ");
            int numero = input.nextInt();
            if (numero < 0 || numero > 99) throw new NumeroInvalidoException();

            Map<String, Integer> atributos = new HashMap<>();
            System.out.println("\nAtributos: ");
            System.out.print("Velocidade: ");
            atributos.put("velocidade", input.nextInt());
            System.out.print("\nResistencia: ");
            atributos.put("resistencia", input.nextInt());
            System.out.print("\nDestreza: ");
            atributos.put("destreza", input.nextInt());
            System.out.print("\nImpulsao: ");
            atributos.put("impulsao", input.nextInt());
            System.out.print("\nJogo de Cabeça: ");
            atributos.put("jogocabeca", input.nextInt());
            System.out.print("\nRemate: ");
            atributos.put("remate", input.nextInt());
            System.out.print("\nPasse: ");
            atributos.put("passe", input.nextInt());

            if (atributos.values().stream().anyMatch(a-> a < 0 || a > 100)) throw new NumeroInvalidoException();

            Jogador jogador = null;
            switch (posicao) {
                case 0: // Guarda-Redes
                    System.out.print("\nElasticidade: ");
                    int elasticidade = input.nextInt();
                    if (elasticidade < 0 || elasticidade > 100) throw new NumeroInvalidoException();
                    this.controller.adicionarJogador(0,nome, numero, equipa, atributos, elasticidade, 0);
                    break;
                case 1: // Lateral
                    System.out.print("\nCruzamento: ");
                    int cruzamento = input.nextInt();
                    System.out.print("\nDrible: ");
                    int drible = input.nextInt();
                    if (cruzamento < 0 || cruzamento > 100 || drible < 0 || drible > 100) throw new NumeroInvalidoException();
                    this.controller.adicionarJogador(1,nome, numero, equipa, atributos, cruzamento, drible);
                    break;
                case 2: // Defesa
                    System.out.print("\nCorte: ");
                    int corte = input.nextInt();
                    System.out.print("\nInterseçao: ");
                    int intersecao = input.nextInt();
                    if (corte < 0 || corte > 100 || intersecao < 0 || intersecao > 100) throw new NumeroInvalidoException();
                    this.controller.adicionarJogador(2,nome, numero, equipa, atributos, corte, intersecao);
                    break;
                case 3: // Medio
                    System.out.print("\nInterseçao: ");
                    int interseca = input.nextInt();
                    System.out.print("\nVisao: ");
                    int visao = input.nextInt();
                    if (interseca < 0 || interseca > 100 || visao < 0 || visao > 100) throw new NumeroInvalidoException();
                    this.controller.adicionarJogador(3,nome, numero, equipa, atributos, interseca, visao);
                    break;
                case 4: // Avançado
                    System.out.print("\nFinalizaçao: ");
                    int finalizacao = input.nextInt();
                    System.out.print("\nCompostura: ");
                    int compostura = input.nextInt();
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

            int eq = this.input.nextInt();
            String equipaSai = nomesEquipas.get(eq);

            Map<Integer,String> nomesJogadores = this.controller.jogadoresEquipa(equipaSai);
            for (int numero: nomesJogadores.keySet()) {
                System.out.println(numero + ". " + nomesJogadores.get(numero));
            }

            System.out.print("\nNumero de camisola: ");
            int camisola = this.input.nextInt();

            System.out.println("Escolha a equipa para onde pretende transferir o jogador:");
            nomesEquipas = this.controller.nomesEquipas();

            for(int i = 0; i < nomesEquipas.size(); i++) System.out.println(i + ". " + nomesEquipas.get(i));
            System.out.print("\nEquipa (0-" + (nomesEquipas.size()-1) + "): ");

            eq = this.input.nextInt();
            String equipaEntra = nomesEquipas.get(eq);

            nomesJogadores = this.controller.jogadoresEquipa(equipaEntra);
            System.out.println("Numero de camisola ja ocupados: ");
            for(int numero: nomesJogadores.keySet()) {
                System.out.print(numero + " ");
            }

            System.out.print("\nEscolha o novo numero de camisola: ");
            int novaCamisola = this.input.nextInt();

            this.controller.transferenciaJogador(equipaSai, equipaEntra, camisola, novaCamisola);

            System.out.println("\nJogador transferido com sucesso.\n");
        } catch (JogadorJaExisteException | JogadorNaoExisteException e) {
            System.out.println("\nEscolha de jogadores incorreta.\n");
        } catch (EquipaNaoDefinidaException e) {
            System.out.println("\nEquipa escolhida nao existe.\n");
        } catch (IndexOutOfBoundsException e) {
            System.out.println("\nNumero escolhido invalido.\n");
        }
    }

    public void removerEquipa() {
        try {
            System.out.println("Escolha a equipa que pretende remover: ");
            List<String> nomesEquipas = this.controller.nomesEquipas();

            for(int i = 0; i < nomesEquipas.size(); i++) System.out.println(i + ". " + nomesEquipas.get(i));
            System.out.print("\nEquipa (0-" + (nomesEquipas.size()-1) + "): ");

            int eq = input.nextInt();
            String equipa = nomesEquipas.get(eq);

            this.controller.removerEquipa(equipa);

            System.out.println("\nEquipa removida com sucesso.\n");
        } catch (EquipaNaoDefinidaException e) {
            System.out.println("\nEquipa escolhida nao existe.\n");
        }
    }
}