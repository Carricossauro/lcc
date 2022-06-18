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

    public synchronized String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(pos.toString());
        sb.append(" ");
        sb.append(pressed);
        return sb.toString();
    }
}