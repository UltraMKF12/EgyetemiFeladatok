//Széri József - 514/2
package collection;

import core.*;

public class MyHashMap {
    private Entry[] entries;

    public MyHashMap(int size) {
        this.entries = new Entry[size];
    }

    public void put(Integer key, Car value) {
        if (key < 1000 || key > 9999) {
            System.out.println("Nem negyszamjegyu a " + key + "!");
        } else if (containsKey(key)) {
            System.out.println("Mar letezik a " + key + "!");
        } else {
            int hash = hashFunction(key);
            Entry newEntry = new Entry(key, value, entries[hash]);
            entries[hash] = newEntry;
        }
    }

    public Car get(Integer key) {
        int hash = hashFunction(key);
        Entry entry = entries[hash];
        while (entry != null) {
            if (entry.getKey().equals(key)) {
                return entry.getValue();
            }
            entry = entry.getNext();
        }

        return null;
    }

    public boolean containsKey(Integer key) {
        return get(key) != null;
    }

    private int hashFunction(Integer key) {
        return key % entries.length;
    }
}
