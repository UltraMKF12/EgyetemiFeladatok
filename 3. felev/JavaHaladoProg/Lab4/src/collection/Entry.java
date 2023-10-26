//Széri József - 514/2
package collection;

import core.*;

public class Entry {
    private Integer key;
    private Car value;
    private Entry next;

    public Entry(Integer key, Car value, Entry next) {
        this.key = key;
        this.value = value;
        this.next = next;
    }

    public Integer getKey() {
        return this.key;
    }

    public Car getValue() {
        return this.value;
    }

    public Entry getNext() {
        return this.next;
    }
}
