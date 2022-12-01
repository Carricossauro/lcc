package projeto;

public class JogadorNaoExisteException extends Exception {
    public JogadorNaoExisteException() {
        super();
    }
    public JogadorNaoExisteException(String mensagem) {
        super(mensagem);
    }
}
