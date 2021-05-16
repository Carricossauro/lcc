package projeto;

public class JogadorJaExisteException extends Exception {
    public JogadorJaExisteException() {
        super();
    }
    public JogadorJaExisteException(String mensagem) {
        super(mensagem);
    }
}