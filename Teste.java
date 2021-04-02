package projeto;

import java.util.Scanner;

public class Teste {
    public static void main(String[] args) {
        Scanner ler = new Scanner(System.in);

        Jogador jog = new Jogador();

        System.out.print("Introduza o metodo para testar: ");
        int x = ler.nextInt();

        switch(x) {
            case 0: {
                break;
            }
            case 1: {
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                break;
            }
            default: {
                System.out.println("Metodo nao existe.");
                break;
            }
        }
        ler.close();

    }
}
