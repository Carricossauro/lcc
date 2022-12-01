package projeto;

public class EquipaJaExisteException extends Exception {
    public EquipaJaExisteException() {
        super();
    }
    public EquipaJaExisteException(String mensagem) {
        super(mensagem);
    }
}
