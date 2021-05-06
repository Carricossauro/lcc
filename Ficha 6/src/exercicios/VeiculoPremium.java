package exercicios;

import java.util.ArrayList;

public class VeiculoPremium extends Veiculo {
    private double taxaLuxo; // ex.: 1.25 -> 25% taxa de luxo

    public VeiculoPremium() {
        this("n/a","n/a","n/a", 0, 0, 0, new ArrayList<Integer>(), 0, 0, 1.25);
    }

    public VeiculoPremium(String marca, String modelo, String matricula,
                   int ano, double velociademedia, double precokm,
                   ArrayList<Integer> classificacao,
                   int kms, int kmsUltimo, double luxo) {
        super.setMarca(marca);
        super.setModelo(modelo);
        super.setMatricula(matricula);
        super.setAno(ano);
        super.setVelociademedia(velociademedia);
        super.setPrecokm(precokm);
        super.setClassificacao(classificacao);
        super.setKms(kms);
        super.setKmsUltimo(kmsUltimo);
        this.taxaLuxo = luxo;
    }

    public void setTaxaLuxo(double tax) {
        this.taxaLuxo = tax;
    }

    public double getTaxaLuxo() {
        return this.taxaLuxo;
    }

    public VeiculoPremium clone() {
        return new VeiculoPremium(this.getMarca(), this.getModelo(), this.getMatricula(), this.getAno(), this.getVelociademedia(), this.getPrecokm(),
                this.getClassificacao(), this.getKms(), this.getKmsUltimo(), this.taxaLuxo);
    }

    public double custoRealKM() {
        return super.custoRealKM()*taxaLuxo;
    }

}
