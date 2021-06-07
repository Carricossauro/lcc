package projeto;

import java.io.IOException;
import java.util.*;
import java.util.stream.Collectors;

public class Interface {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in).useDelimiter("\n");
        Map<String,Equipa> equipas = new LinkedHashMap<>();
        equipas.put("Jogadores sem clube", new Equipa("Jogadores sem clube"));
        List<Jogo> jogos = new ArrayList<>();

        System.out.println("  ____                                        _               _                               ______   __  __ \n" +
                " |  _ \\                                      (_)             | |                             |  ____| |  \\/  |\n" +
                " | |_) |   ___   _ __ ___    ______  __   __  _   _ __     __| |   ___       __ _    ___     | |__    | \\  / |\n" +
                " |  _ <   / _ \\ | '_ ` _ \\  |______| \\ \\ / / | | | '_ \\   / _` |  / _ \\     / _` |  / _ \\    |  __|   | |\\/| |\n" +
                " | |_) | |  __/ | | | | | |           \\ V /  | | | | | | | (_| | | (_) |   | (_| | | (_) |   | |      | |  | |\n" +
                " |____/   \\___| |_| |_| |_|            \\_/   |_| |_| |_|  \\__,_|  \\___/     \\__,_|  \\___/    |_|      |_|  |_|\n" +
                "                                                                                                              ");

        int opcao;
        do {
            opcao = receberComandos(input);
            switch (opcao) {
                case 0:
                    System.out.println("\nSimulação encerrada.");
                    break;
                case 1:
                    try {
                        Map<String, Equipa> novasEquipas = new HashMap<>();
                        List<Jogo> novosJogos = new ArrayList<>();
                        System.out.print("Introduza o nome do ficheiro que pretende ler: ");
                        String ficheiro = input.next();
                        Parser.parse(novasEquipas, novosJogos, ficheiro);
                        System.out.println("\nInformação do ficheiro carregada.\n");
                        for (String nome: novasEquipas.keySet()) {
                            equipas.put(nome, novasEquipas.get(nome));
                        }
                        jogos.addAll(novosJogos);
                    } catch (LinhaIncorretaException | JogadorJaExisteException e) {
                        System.out.println("\nFicheiro está mal formado.\n");
                        equipas = new HashMap<>();
                        jogos = new ArrayList<>();
                    }
                    break;
                case 2:
                    System.out.print("Introduza o nome do ficheiro onde pretende gravar: ");
                    String ficheiro = input.next();
                    try {
                        SaveGame.gravar(equipas, jogos, ficheiro);
                        System.out.println("\nGravação concluída.\n");
                    } catch (IOException e) {
                        System.out.println("Impossível gravar no ficheiro " + ficheiro + ".");
                    }
                    break;
                case 3:
                    System.out.print("Introduza o nome da equipa que pretende criar: ");
                    String equipa = input.next();
                    if (!equipas.containsKey(equipa)) {
                        equipas.put(equipa, new Equipa(equipa));
                        System.out.println("Equipa " + equipa + " criada.");
                    } else {
                        System.out.println("A equipa que esta a tentar criar ja existe.");
                    }
                    break;
                case 4:
                    adicionarJogador(input, equipas, jogos);
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    break;
                case 9:
                    break;
                default:
                    System.out.println("\nOpção Inválida. Escolha um numero entre 0 e 9.\n");
                    break;
            }
        } while (opcao != 0);
    }

    public static int receberComandos(Scanner input) {
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
        return input.nextInt();
    }

    public static void adicionarJogador(Scanner input, Map<String, Equipa> equipas, List<Jogo> jogos) {
        try {
            System.out.println("Escolha a equipa a que pertence adicionar o jogador: ");
            List<String> nomesEquipas = new ArrayList<>(equipas.keySet());
            for(int i = 0; i < nomesEquipas.size(); i++) System.out.println(i + ". " + nomesEquipas.get(i));
            System.out.print("\nEquipa (0-" + (nomesEquipas.size()-1) + "): ");
            int eq = input.nextInt();

            Equipa equipa = equipas.get(nomesEquipas.get(eq));

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
                    jogador = new GuardaRedes(nome, numero, new ArrayList<>(),atributos, elasticidade);
                    break;
                case 1: // Lateral
                    System.out.print("\nCruzamento: ");
                    int cruzamento = input.nextInt();
                    System.out.print("\nDrible: ");
                    int drible = input.nextInt();
                    if (cruzamento < 0 || cruzamento > 100 || drible < 0 || drible > 100) throw new NumeroInvalidoException();
                    jogador = new Lateral(nome, numero, new ArrayList<>(), atributos, cruzamento, drible);
                    break;
                case 2: // Defesa
                    System.out.print("\nCorte: ");
                    int corte = input.nextInt();
                    System.out.print("\nInterseçao: ");
                    int intersecao = input.nextInt();
                    if (corte < 0 || corte > 100 || intersecao < 0 || intersecao > 100) throw new NumeroInvalidoException();
                    jogador = new Defesa(nome, numero, new ArrayList<>(), atributos, corte, intersecao);
                    break;
                case 3: // Medio
                    System.out.print("\nInterseçao: ");
                    int interseca = input.nextInt();
                    System.out.print("\nVisao: ");
                    int visao = input.nextInt();
                    if (interseca < 0 || interseca > 100 || visao < 0 || visao > 100) throw new NumeroInvalidoException();
                    jogador = new Medio(nome, numero, new ArrayList<>(), atributos, interseca, visao);
                    break;
                case 4: // Avançado
                    System.out.print("\nFinalizaçao: ");
                    int finalizacao = input.nextInt();
                    System.out.print("\nCompostura: ");
                    int compostura = input.nextInt();
                    if (finalizacao < 0 || finalizacao > 100 || compostura < 0 || compostura > 100) throw new NumeroInvalidoException();
                    jogador = new Avancado(nome, numero, new ArrayList<>(), atributos, finalizacao, compostura);
                    break;
                default:
                    System.out.println("\nA posiçao que escolheu nao existe.");
                    break;
            }
            equipa.adicionaJogador(jogador, numero);
            System.out.println("Jogador adicionado com sucesso.");
        } catch (JogadorJaExisteException e) {
            System.out.println(e.getMessage());
        } catch (IndexOutOfBoundsException e) {
            System.out.println("\nA equipa que escolheu nao existe.\n");
        } catch (Exception e) {
            System.out.println("\nA informaçao submetida nao esta correta.\n");
        }
    }
}
