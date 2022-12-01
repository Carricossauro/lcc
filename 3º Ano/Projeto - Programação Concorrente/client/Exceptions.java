class InvalidPassword extends Exception {
    public InvalidPassword(String message) {
        super(message);
    }
}
class InvalidAccount extends Exception {
    public InvalidAccount(String message) {
        super(message);
    }
}
class UserExists extends Exception {
    public UserExists(String message) {
        super(message);
    }
}

class FullServer extends Exception {
    public FullServer(String message) {
        super(message);
    }
}