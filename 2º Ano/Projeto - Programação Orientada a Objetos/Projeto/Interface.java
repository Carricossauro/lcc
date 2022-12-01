package projeto;

import java.util.*;

public class Interface {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in).useDelimiter("\n");
        Map<String,Equipa> equipas = new LinkedHashMap<>();
        equipas.put("Jogadores sem clube", new Equipa("Jogadores sem clube"));
        List<Jogo> jogos = new ArrayList<>();

        Controller controller = new Controller(equipas, jogos);
        View view = new View(controller, input);

        view.run();
    }
}
