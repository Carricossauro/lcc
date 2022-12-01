import java.util.ArrayList;

public class Stack {
    private ArrayList<String> valores;

    public Stack() {
        this.valores = new ArrayList<String>();
    }

    public Stack(int n) {
        this.valores = new ArrayList<String>(n);
    }

    public Stack(Stack s) {
        this.valores = new ArrayList<String>();
        //this.valores = new ArrayList<String>(s.valores); <-- Soluçao one-liner
        /* Soluçao nao ideal
         for (int i = 0; i < s.valores.size(); i++) {
            this.valores.set(i, new String(s.valores.get(i)));
        }
        */
        for (String str: s.valores) {
            this.valores.add(str);
            //this.valores.add(str.clone()); <-- Para objetos nao String (Strings sao imutaveis, nao precisam)
        }

    }

    public Stack clone() {
        return new Stack(this);
    }

    public boolean equals(Object s) {
        if (s == this) return true;

        if (s == null || this.getClass() != s.getClass()) return false;

        Stack o = (Stack) s;
        return this.valores.equals(o.getValores());
    }

    public String toString() {
        return "Stack: " + this.valores.toString();
    }

    public int length() {
        return this.valores.size();
    }

    public boolean empty() {
        return this.valores.isEmpty();
    }

    public String top() {
        return this.valores.get(this.valores.size() - 1);
    }

    public void push(String s) {
        this.valores.add(s);
    }

    public void pop() {
        if (!this.empty()) {
		this.valores.remove(this.valores.size() - 1);
	}
    }

    public String popR() {
        String s = null;
	if (!this.empty()) {
		int ind = this.valores.size() - 1;
        	String s = this.valores.get(ind);
        	this.valores.remove(ind);
        }
	return s;
    }

    public ArrayList<String> getValores() {
        return new ArrayList<String>(this.valores);
    }
}
