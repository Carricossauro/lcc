import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.stream.Collectors;

public class Equipa {
    private String nome;
    private Map<Integer,Jogador> jogadores;
    private int titulares [];

    public Equipa (){
        this.nome = "n/a";
        this.jogadores = new HashMap<>();
        this.titulares = new int[11];
        for(int i =0; i<11; i++){
            this.titulares [i] = -1;
        }
    }

    public Equipa (String nome, Map<Integer,Jogador> jogadores, int titulares[]){
        this.nome = nome;
        this.jogadores = jogadores.entrySet()
                                    .stream()
                                    .collect(Collectors.toMap(Map.Entry::getKey,a->a.getValue().clone()));
        this.titulares = new int[11];
        System.arraycopy(titulares,0,this.titulares,0,11);
    }

    public Equipa (Equipa e){
        this(e.nome, e.jogadores, e.titulares);
    }

    public Equipa clone () {
        return new Equipa(this);
    }

    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Equipa: "); sb.append(this.nome);
        sb.append("\nJogadores: ");this.jogadores.forEach((y,x) -> {
        sb.append("Camisola: "); sb.append(y.toString());
        sb.append("\n");sb.append(x.toString()); 
        });
        sb.append("\nTitulares: "); sb.append(this.titulares.toString());
        return sb.toString();
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o==null || o.getClass() != this.getClass() ) return false;
        Equipa a = (Equipa) o;
        return this.nome.equals(a.nome) && this.jogadores.equals(a.jogadores) && Arrays.equals(this.titulares, a.titulares);
    }

}
