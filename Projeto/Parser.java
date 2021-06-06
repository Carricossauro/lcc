package projeto;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class Parser {
    public static void parse(Map<String, Equipa> equipas, List<Jogo> jogos, String ficheiro) throws LinhaIncorretaException, JogadorJaExisteException {
        List<String> linhas = lerFicheiro(ficheiro);
        //System.out.println(linhas);
        //Map<String, Equipa> equipas = new HashMap<>(); //nome, equipa
        //Map<Integer, Jogador> jogadores = new HashMap<>(); //numero, jogador
        //List<Jogo> jogos = new ArrayList<>();
        Equipa ultima = null; Jogador j = null;
        String[] linhaPartida;
        for (String linha : linhas) {
            linhaPartida = linha.split(":", 2);
            switch(linhaPartida[0]){
                case "Equipa":
                    Equipa e = Equipa.parse(linhaPartida[1]);
                    equipas.put(e.getNome(), e);
                    ultima = e;
                    break;
                case "Guarda-Redes":
                    j = GuardaRedes.parse(linhaPartida[1]);
                    //jogadores.put(j.getNumeroCamisola(), j);
                    if (ultima == null) throw new LinhaIncorretaException("Equipa inexistente"); //we need to insert the player into the team
                    ultima.adicionaJogador(j.clone(), j.getNumeroCamisola()); //if no team was parsed previously, file is not well-formed
                    break;
                case "Defesa":
                    j = Defesa.parse(linhaPartida[1]);
                    //jogadores.put(j.getNumeroCamisola(), j);
                    if (ultima == null) throw new LinhaIncorretaException("Equipa inexistente"); //we need to insert the player into the team
                    ultima.adicionaJogador(j.clone(), j.getNumeroCamisola()); //if no team was parsed previously, file is not well-formed
                    break;
                case "Medio":
                    j = Medio.parse(linhaPartida[1]);
                    //jogadores.put(j.getNumeroCamisola(), j);
                    if (ultima == null) throw new LinhaIncorretaException("Equipa inexistente"); //we need to insert the player into the team
                    ultima.adicionaJogador(j.clone(), j.getNumeroCamisola()); //if no team was parsed previously, file is not well-formed
                    break;
                case "Lateral":
                    j = Lateral.parse(linhaPartida[1]);
                    //jogadores.put(j.getNumeroCamisola(), j);
                    if (ultima == null) throw new LinhaIncorretaException("Equipa inexistente"); //we need to insert the player into the team
                    ultima.adicionaJogador(j.clone(), j.getNumeroCamisola()); //if no team was parsed previously, file is not well-formed
                    break;
                case "Avancado":
                    j = Avancado.parse(linhaPartida[1]);
                    //jogadores.put(j.getNumeroCamisola(), j);
                    if (ultima == null) throw new LinhaIncorretaException("Equipa inexistente"); //we need to insert the player into the team
                    ultima.adicionaJogador(j.clone(), j.getNumeroCamisola()); //if no team was parsed previously, file is not well-formed
                    break;
                case "Jogo":
                    Jogo jo = Jogo.parse(linhaPartida[1]);
                    jogos.add(jo);
                    break;
                default:
                    throw new LinhaIncorretaException("Linha mal formatada");

            }
        }
        /*
        System.out.println(equipas.size());
        System.out.println(jogos.size());
         debug
        for (Equipa e: equipas.values()){
            System.out.println(e.toString());
            System.out.print("\n");
        }
        for (Jogo jog: jogos){
            System.out.println(jog.toString());
        }*/
    }

    public static List<String> lerFicheiro(String nomeFich) {
        List<String> lines;
        try { lines = Files.readAllLines(Paths.get(nomeFich), StandardCharsets.UTF_8); }
        catch(IOException exc) {
            System.out.println(exc);
            lines = new ArrayList<>();
        }
        return lines;
    }
}
