package projeto;

import java.io.FileWriter;
import java.io.IOException;
import java.util.List;
import java.util.Map;

public class SaveGame {
    public static void gravar(Map<String, Equipa> equipas, List<Jogo> jogos, String ficheiro) throws IOException {
        FileWriter writer = new FileWriter(ficheiro);

        for (Equipa equipa: equipas.values()) {
            equipa.escrever(writer);
        }

        for (Jogo jogo: jogos) {
            jogo.escrever(writer);
        }

        writer.close();
    }
}
