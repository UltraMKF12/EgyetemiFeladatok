import java.util.LinkedList;
import java.util.List;

public class Counter implements Runnable {
    private volatile Thread control;
    private int counter;
    private volatile boolean suspended;

    private List<CounterListener> listeners;

    public Counter() {
        listeners = new LinkedList<>();
    }

    public synchronized void addCounterListener(CounterListener listener) {
        listeners.add(listener);
    }

    public synchronized void removeCounterListener(CounterListener listener) {
        listeners.remove(listener);
    }

    @Override
    public void run() {
        Thread current = Thread.currentThread();
        while (control == current) {
            synchronized (this) {
                while (suspended) {
                    try {
                        wait();
                    } catch (InterruptedException e) {
                        break;
                    }
                }
            }

            counter++;
            synchronized (this) {
                CounterEvent event = new CounterEvent(this, counter);
                for (CounterListener c1 : listeners) {
                    c1.counterValueChanged(event);
                }
            }

            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                break;
            }
        }
    }

    public void start() {
        suspended = false;
        control = new Thread(this);
        counter = 0;
        control.start();
    }

    public void stop() {
        Thread tmp = control;
        control = null;
        tmp.interrupt();
    }

    public void suspend() {
        suspended = true;
    }

    public synchronized void resume() {
        suspended = false;
        notifyAll();
    }
}
