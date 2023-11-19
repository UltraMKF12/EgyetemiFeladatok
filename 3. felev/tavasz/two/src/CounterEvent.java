import java.util.EventObject;

public class CounterEvent extends EventObject {

    private int value;

    public CounterEvent(Object source, int value) {
        super(source);
        this.value = value;
    }

    public int getValue() {
        return value;
    }
}
