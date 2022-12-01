public class Tuple<A, B> {
    public A first;
    public B second;

    public Tuple(A fst, B snd) {
        this.first = fst;
        this.second = snd;
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(first);
        sb.append(" ");
        sb.append(second);
        return sb.toString();
    }
}