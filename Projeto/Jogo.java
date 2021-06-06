package projeto;

import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.*;

public class Jogo {
    private String equipaCasa;
    private String equipaFora;
    private int golosCasa;
    private int golosFora;
    private LocalDate date;
    private List<Integer> jogadoresCasa;
    private List<Integer> jogadoresFora;
    Map<Integer, Integer> substituicoesCasa = new HashMap<>(); // sai -> entra
    Map<Integer, Integer> substituicoesFora = new HashMap<>(); // sai -> entra

    public Jogo() {
        equipaCasa = "n/a";
        equipaFora = "n/a";
        golosCasa = 0;
        golosFora = 0;
        date = LocalDate.now();
        jogadoresCasa = new ArrayList<>();
        jogadoresFora = new ArrayList<>();
        substituicoesCasa = new HashMap<>();
        substituicoesFora = new HashMap<>();
    }

    public Jogo (String ec, String ef, int gc, int gf, LocalDate d,  List<Integer> jc, Map<Integer, Integer> sc,  List<Integer> jf, Map<Integer, Integer> sf){
        equipaCasa = ec;
        equipaFora = ef;
        golosCasa = gc;
        golosFora = gf;
        date = d;
        jogadoresCasa = new ArrayList<>(jc);
        jogadoresFora = new ArrayList<>(jf);
        substituicoesCasa = new HashMap<>(sc);
        substituicoesFora = new HashMap<>(sf);
    }

    public static Jogo parse(String input){
        String[] campos = input.split(",");
        String[] data = campos[4].split("-");
        List<Integer> jc = new ArrayList<>();
        List<Integer> jf = new ArrayList<>();
        Map<Integer, Integer> subsC = new HashMap<>();
        Map<Integer, Integer> subsF = new HashMap<>();
        int i = 5;
        for (; i < 16; i++){
            jc.add(Integer.parseInt(campos[i]));
        }
        for (; i < 19; i++){
            String[] sub = campos[i].split("->");
            if (sub.length <= 1) break;
            subsC.put(Integer.parseInt(sub[0]), Integer.parseInt(sub[1]));
        }
        for (int j = 0; j < 11; j++, i++){
            jf.add(Integer.parseInt(campos[i]));
        }
        for (int subs = 0; subs < 3 && i < campos.length; subs++, i++){
            String[] sub = campos[i].split("->");
            if (sub.length <= 1) break;
            subsF.put(Integer.parseInt(sub[0]), Integer.parseInt(sub[1]));
        }
        return new Jogo(campos[0], campos[1], Integer.parseInt(campos[2]), Integer.parseInt(campos[3]),
                LocalDate.of(Integer.parseInt(data[0]), Integer.parseInt(data[1]), Integer.parseInt(data[2])),
                jc, subsC, jf, subsF);
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();

        sb.append("Jogo:").append(this.equipaCasa).append(" ").append(this.golosCasa);
        sb.append(" - ").append(this.golosFora).append(" ").append(this.equipaFora);
        // Jogo: Benfica 4 - 3 Sporting
        sb.append("\nData: ").append(this.date);
        sb.append("\nEquipa casa: ");
        this.jogadoresCasa.forEach(j->sb.append(j).append(" "));
        // Equipa casa: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
        sb.append("Substituiçoes casa: ");
        this.substituicoesCasa.forEach((key, value) -> sb.append(key).append(" -> ").append(value).append(" "));
        sb.append("\nEquipa fora: ");
        this.jogadoresFora.forEach(j->sb.append(j).append(" "));
        sb.append("Substituiçoes fora: ");
        this.substituicoesFora.forEach((key, value) -> sb.append(key).append(" -> ").append(value).append(" "));

        return sb.toString();
    }

    public Jogo clone() {
        return new Jogo(this.equipaCasa, this.equipaFora, this.golosCasa, this.golosFora, this.date, this.jogadoresCasa, this.substituicoesCasa, this.jogadoresFora, this.substituicoesFora);
    }

    public void adicionaSubstituicaoCasa(int entra, int sai) throws SubstituicaoErradaException {
        if (entra == sai || this.substituicoesCasa.size() >= 3 || this.substituicoesCasa.containsKey(entra)) throw new SubstituicaoErradaException();

        this.substituicoesCasa.put(sai, entra);
    }

    public void adicionaSubstituicaoFora(int entra, int sai) throws SubstituicaoErradaException {
        if (entra == sai || this.substituicoesFora.size() >= 3 || this.substituicoesFora.containsKey(entra)) throw new SubstituicaoErradaException();

        this.substituicoesFora.put(sai, entra);
    }

    public void goloCasa() {
        this.golosCasa++;
    }

    public void goloFora() {
        this.golosFora++;
    }

    public void escrever(FileWriter writer) throws IOException {
        writer.write("Jogo:");

        writer.write(this.equipaCasa + ",");
        writer.write(this.equipaFora + ",");
        writer.write(this.golosCasa + ",");
        writer.write(this.golosFora + ",");

        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("YYYY-MM-dd");
        writer.write(formatter.format(this.date));

        for (int numero: this.jogadoresCasa) {
            writer.write("," + numero);
        }

        if (this.substituicoesCasa.isEmpty()) writer.write(",");
        for (int sai: this.substituicoesCasa.keySet()) {
            writer.write("," + sai + "->" + this.substituicoesCasa.get(sai));
        }

        for (int numero: this.jogadoresFora) {
            writer.write("," + numero);
        }

        if (this.substituicoesFora.isEmpty()) writer.write(",");
        for (int sai: this.substituicoesFora.keySet()) {
            writer.write("," + sai + "->" + this.substituicoesFora.get(sai));
        }

        writer.write("\n");
        writer.flush();
    }

    // setters e getters
    public String getEquipaCasa() {
        return this.equipaCasa;
    }
    public String getEquipaFora() {
        return this.equipaFora;
    }
    public void setEquipaCasa(String nome) {
        this.equipaCasa = nome;
    }
    public void setEquipaFora(String nome) {
        this.equipaFora = nome;
    }
    public int getGolosCasa() {
        return this.golosCasa;
    }
    public int getGolosFora() {
        return this.golosFora;
    }
    public void setGolosCasa(int g) {
        this.golosCasa = g;
    }
    public void setGolosFora(int g) {
        this.golosFora = g;
    }
    public LocalDate getDate() {
        return LocalDate.from(this.date);
    }
    public void setDate(LocalDate dt) {
        this.date = LocalDate.from(dt);
    }
    public List<Integer> getJogadoresCasa() {
        return new ArrayList<>(this.jogadoresCasa);
    }
    public List<Integer> getJogadoresFora() {
        return new ArrayList<>(this.jogadoresFora);
    }
    public void setJogadoresCasa(List<Integer> lista) {
        this.jogadoresCasa = new ArrayList<>(lista);
    }
    public void setJogadoresFora(List<Integer> lista) {
        this.jogadoresFora = new ArrayList<>(lista);
    }
    public Map<Integer, Integer> getSubstituicoesCasa() {
        return new HashMap<>(this.substituicoesCasa);
    }
    public Map<Integer, Integer> getSubstituicoesFora() {
        return new HashMap<>(this.substituicoesFora);
    }
    public void setSubstituicoesCasa(Map<Integer, Integer> mapa) {
        this.substituicoesCasa = new HashMap<>(mapa);
    }
    public void setSubstituicoesFora(Map<Integer, Integer> mapa) {
        this.substituicoesFora = new HashMap<>(mapa);
    }
}