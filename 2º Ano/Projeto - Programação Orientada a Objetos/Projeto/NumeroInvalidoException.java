package projeto;

public class NumeroInvalidoException extends Exception {
    public NumeroInvalidoException() {
        super();
    }
    public NumeroInvalidoException(String mensagem) {
        super(mensagem);
    }
}
