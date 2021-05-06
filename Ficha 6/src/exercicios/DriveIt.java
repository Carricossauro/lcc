package exercicios;

import java.util.*;
import java.util.stream.Collectors;

public class DriveIt {
    private Map<String, Veiculo> veiculos;
    private boolean promocao;

    public DriveIt() {
        this.veiculos = new HashMap<>();
        this.promocao = false;
    }
    public DriveIt(Map<String, Veiculo> mapa, boolean pro) {
        this.veiculos = mapa.entrySet().stream().collect(Collectors.toMap(Map.Entry::getKey, e-> e.getValue().clone()));
        this.promocao = pro;
    }

    public boolean existeVeiculo(String mat) {
        return this.veiculos.containsKey(mat);
    }

    public int quantos() {
        return this.veiculos.size();
    }

    public int quantos(String marca) {
        return (int) this.veiculos.values().stream().filter(a->a.getMarca().equals(marca)).count();
    }

    public Veiculo getVeiculo(String mat) {
        Veiculo v = this.veiculos.get(mat);
        if (v != null) v = v.clone();
        return v;
    }

    public void adiciona(Veiculo v) {
        if (!this.veiculos.containsKey(v.getMarca())) {
            this.veiculos.put(v.getMarca(), v.clone());
        }
    }

    public List<Veiculo> getVeiculos() {
        return this.veiculos.values().stream().map(Veiculo::clone).collect(Collectors.toList());
    }

    public void adiciona(Set<Veiculo> vs) {
        vs.forEach(this::adiciona);
    }

    public void registarAluguer(String mat, int numKms) {
        Veiculo v = this.veiculos.get(mat);
        if (v != null) {
            v.addViagem(numKms);
        }
    }

    public void ClassificarVeiculo(String mat, int clas) {
        Veiculo v = this.veiculos.get(mat);
        if (v != null) {
            v.addClassificacao(clas);
        }
    }

    public double custoRealKm(String mat) {
        Veiculo v = this.veiculos.get(mat);
        if (v != null) {
            if (v instanceof VeiculoOcasiao && this.promocao) return ((VeiculoOcasiao) v).custorealDesconto();
            else return v.custoRealKM();
        }
        return 0;
    }

    public int quantosT(String tipo) {
        return (int) this.veiculos.values().stream().filter(a->a.getClass().getSimpleName().equals(tipo)).count();
    }

    public List<Veiculo> veiculosOrdenadosCusto() {
        return this.veiculos.values().stream().sorted((a,b)->{
            double pA, pB;

            if (a instanceof VeiculoOcasiao) pA = ((VeiculoOcasiao) a).custorealDesconto();
            else pA = a.custoRealKM();

            if (b instanceof VeiculoOcasiao) pB = ((VeiculoOcasiao) b).custorealDesconto();
            else pB = b.custoRealKM();

            return (int) (pB-pA);
        }).map(Veiculo::clone).collect(Collectors.toList());
    }

    public Veiculo veiculoMaisBarato() {
        List<Veiculo> vs = this.veiculosOrdenadosCusto();
        return vs.get(vs.size()-1);
    }

    public Veiculo veiculoMenosUtilizado() {
        return this.veiculos.values().stream().sorted(Comparator.comparingInt(Veiculo::getKms))
                .map(Veiculo::clone).collect(Collectors.toList()).stream().findFirst().get();
    }

    public void alteraPromocao(boolean estado) {
        this.promocao = estado;
    }
}