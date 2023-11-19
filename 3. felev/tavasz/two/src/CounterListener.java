import java.util.EventListener;

public interface CounterListener extends EventListener {
    public void counterValueChanged(CounterEvent e);
}
