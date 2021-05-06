package exercicios;

import java.util.ArrayList;

public class AutocarroInteligente extends Veiculo{
    private double ocupacao;

    public AutocarroInteligente() {
        this("n/a","n/a","n/a", 0, 0, 0, new ArrayList<Integer>(), 0, 0, 0);
    }

    public AutocarroInteligente(String marca, String modelo, String matricula,
                                int ano, double velociademedia, double precokm,
                                ArrayList<Integer> classificacao,
                                int kms, int kmsUltimo, double ocup) {
        super.setMarca(marca);
        super.setModelo(modelo);
        super.setMatricula(matricula);
        super.setAno(ano);
        super.setVelociademedia(velociademedia);
        super.setPrecokm(precokm);
        super.setClassificacao(classificacao);
        super.setKms(kms);
        super.setKmsUltimo(kmsUltimo);
        this.ocupacao = ocup;
    }

    public String toString() {
        return super.toString() + "\nOcupaçao: " + (int) this.ocupacao*10 + "%";
    }

    public AutocarroInteligente(AutocarroInteligente a) {
        this(a.getMarca(), a.getModelo(), a.getMatricula(), a.getAno(),
             a.getVelociademedia(), a.getPrecokm(), a.getClassificacao(), a.getKms(), a.getKmsUltimo(), a.getOcupacao());
    }

    public AutocarroInteligente clone() {
        return new AutocarroInteligente(this.getMarca(), this.getModelo(), this.getMatricula(), this.getAno(), this.getVelociademedia(), this.getPrecokm(),
                this.getClassificacao(), this.getKms(), this.getKmsUltimo(), this.ocupacao);
    }

    public void setOcupacao(double oc) {
        this.ocupacao = oc;
    }

    public double getOcupacao() {
        return this.ocupacao;
    }

    public double custoRealKM() {
        if (this.ocupacao< 0.6) return super.custoRealKM() * 0.5;
        return super.custoRealKM() * 0.25;
    }
}
