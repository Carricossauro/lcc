package projeto;

import java.io.IOException;
import java.util.*;

public class Interface {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        Map<String,Equipa> equipas = new HashMap<>();
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
                    break;
                case 4:
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
}
