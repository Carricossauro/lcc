package casainteligente;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class CasaInteligente {
    private String morada;
    private Map<String, SmartDevice> devices;
    private Map<String, List<SmartDevice>> salas;

    public CasaInteligente() {
        this.morada = "";
        this.devices = new HashMap<>();
        this.salas = new HashMap<>();
    }
    public CasaInteligente(String mo) {
        this.morada = "";
        this.devices = new HashMap<>();
        this.salas = new HashMap<>();
    }

    public boolean existsDevice(String dev) {
        return this.devices.containsKey(dev);
    }

    public void addDevice(Object o) {
        if (o instanceof SmartBulb) {

            SmartBulb s = (SmartBulb) o;
            this.devices.put(s.getID(), s.clone());

        } else if (o instanceof SmartSpeaker) {

            SmartSpeaker s  = (SmartSpeaker) o;
            this.devices.put(s.getID(), s.clone());

        }
    }

    public SmartDevice getDevice(String ID) {
        return this.devices.get(ID);
    }

    public void setAllOn(boolean estado) {
        this.devices.values().forEach(a-> {
            a.setOn(estado);
        });
    }

    public void addRoom(String sala) {
        if (!this.salas.containsKey(sala)) {
            this.salas.put(sala, new ArrayList<>());
        }
    }

    public boolean hasRoom(String sala) {
        return this.salas.containsKey(sala);
    }

    public void addToRoom(String sala, String dev) {
        if (this.salas.containsKey(sala)) {
            if (this.devices.containsKey(dev)) {
                List<SmartDevice> lista = this.salas.get(sala);
                lista.add(this.devices.get(dev));
                this.salas.put(sala, lista);
            }
        }
    }

    public boolean roomHasDevice(String sala, String dev) {
        if (!this.salas.containsKey(sala)) return false;

        return this.salas.get(sala).stream().anyMatch(a->a.getID().equals(dev));
    }
}
