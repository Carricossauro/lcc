package casainteligente;

public class SmartDevice {
    private String id;
    private boolean on;

    public SmartDevice() {
        this.id = "";
        this.on = false;
    }

    public SmartDevice(String ID) {
        this.id = ID;
    }

    public SmartDevice(String ID, boolean ON) {
        this.id = ID;
        this.on = ON;
    }

    // setters e getters
    public void setID(String ID) {
        this.id = ID;
        this.on = false;
    }
    public String getID() {
        return this.id;
    }
    public void setOn(boolean estado) {
        this.on = estado;
    }
    public boolean getOn() {
        return this.on;
    }
}
