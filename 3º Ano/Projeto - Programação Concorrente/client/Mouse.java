public class Mouse {
    private Tuple<Float, Float> pos = new Tuple<Float, Float>(0.0f,0.0f);
    public boolean pressed = false;

    public synchronized Tuple<Float, Float> getPos() {
        return pos;
    }

    public synchronized void setPos(float x, float y) {
        pos.first = x;
        pos.second = y;
    }

    public synchronized void setMouse(float x, float y, boolean isPressed) {
        this.pos.first = x;
        this.pos.second = y;
        this.pressed = isPressed;

    }



    public synchronized String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(pos.toString());
        sb.append(" ");
        if(this.pressed)
            sb.append(2);
        else
            sb.append(1);
        this.pressed = false;
        return sb.toString();
    }
}