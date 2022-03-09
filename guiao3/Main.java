import java.util.HashMap;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class NotEnoughFunds extends Exception {}
class InvalidAccount extends Exception {}

class Bank {
    private static class Account {
        private int balance;
        Lock lock = new ReentrantLock();

        Account(int bal) {
            this.balance = bal;
        }

        int balance() { return balance; }
        void deposit(int val) { balance += val; }
        void withdraw(int val) throws NotEnoughFunds {
            if (balance < val) throw new NotEnoughFunds();
            balance -= val;
        }
    }

    private HashMap<Integer ,Account> accounts;
    Lock lock = new ReentrantLock();
    private int number_account;

    Bank() {
        this.accounts = new HashMap<Integer, Account>();
        this.number_account = 0;
    }

    synchronized int createAccount(int initialBalance) {
        this.accounts.put(this.number_account, new Account(initialBalance));
        return this.number_account++;
    }

    synchronized int closeAccount(int id) throws InvalidAccount {
        if (!this.accounts.containsKey(id)) throw new InvalidAccount();

        Account a = this.accounts.get(id);
        this.accounts.remove(id);

        return a.balance();
    }

    void deposit(int id, int val) throws InvalidAccount {
        if (!this.accounts.containsKey(id)) throw new InvalidAccount();

        this.accounts.get(id).deposit(val);
    }

    void withdraw(int id, int val) throws InvalidAccount, NotEnoughFunds {
        if (!this.accounts.containsKey(id)) throw new InvalidAccount();

        this.accounts.get(id).withdraw(val);
    }

    void transfer(int from, int to, int amount) throws InvalidAccount, NotEnoughFunds {
        if (!this.accounts.containsKey(from)) throw new InvalidAccount();
        if (!this.accounts.containsKey(to)) throw new InvalidAccount();

        Account o1 = this.accounts.get(Math.min(from, to));
        Account o2 = this.accounts.get(Math.max(from, to));
        Account cfrom = this.accounts.get(from);
        Account cto = this.accounts.get(to);

        o1.lock.lock();
        o2.lock.lock();

        try {
            cfrom.withdraw(amount);
            cto.deposit(amount);
        } catch (NotEnoughFunds nef) {
            o1.lock.unlock();
            o2.lock.unlock();
            throw nef;
        } finally {
            o1.lock.unlock();
            o2.lock.unlock();
        }
    }

    int totalBalance(int accs[]) throws InvalidAccount {
        int total = 0;
        for (int i = 0; i < accs.length; i++) {
            if (!this.accounts.containsKey(accs[i])) throw new InvalidAccount();

            total += this.accounts.get(accs[i]).balance();
        }

        return total;
    }

    int accountBalance(int id) throws InvalidAccount {
        if (!this.accounts.containsKey(id)) throw new InvalidAccount();

        return this.accounts.get(id).balance();
    }
}

public class Main {
    public static void main(String args[]) {
            try {
                int accounts[] = new int[10];
                int n = 10;
                Bank b = new Bank();

                for (int i = 0; i < n; i++) accounts[i] = b.createAccount(i+1);
                for (int i = 0; i < n; i++) b.deposit(accounts[i], 100*(i+1));

                printAccountBalances(accounts, b, n);

                System.out.println("Closed account 5 with $" + b.closeAccount(5) + ".");

                b.transfer(9, 0, 300);
                printAccountBalances(accounts, b, n);
            } catch (Exception e) {
                e.printStackTrace();
            }

    }

    public static void printAccountBalances(int accounts[], Bank b, int n) throws InvalidAccount, NotEnoughFunds {
        for (int i = 0; i < n; i++) {
            try {
                System.out.println("Account " + i + ": " + b.accountBalance(accounts[i]));
            } catch (InvalidAccount ia) {
                System.out.println("Account "+ i + " does not exist.");
            }
        }
    }
}
