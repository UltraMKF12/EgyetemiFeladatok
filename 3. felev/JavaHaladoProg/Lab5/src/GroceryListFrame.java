// Széri József - 514
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

class GroceryListFrame extends Frame {
    private List fruitList;
    private List vegetableList;
    private Button leftButton;
    private Button rightButton;

    public GroceryListFrame() {
        setBounds(100, 100, 500, 500);
        setLayout(new FlowLayout());

        fruitList = new List(10, true);
        vegetableList = new List(10, true);
        leftButton = new Button("<-");
        rightButton = new Button("->");

        fruitList.add("Alma");
        fruitList.add("Körte");
        fruitList.add("Szilva");
        fruitList.add("Eper");
        fruitList.add("Cseresznye");

        vegetableList.add("Káposzta");
        vegetableList.add("Saláta");
        vegetableList.add("Uborka");
        vegetableList.add("Paprika");
        vegetableList.add("Répa");

        add(fruitList);
        add(rightButton);
        add(leftButton);
        add(vegetableList);


        // ->
        rightButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String[] selectedItems = fruitList.getSelectedItems();
                for(String item : selectedItems) {
                    vegetableList.add(item);
                    fruitList.remove(item);
                }
            }
        });

        // <-
        leftButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String[] selectedItems = vegetableList.getSelectedItems();
                for(String item : selectedItems) {
                    fruitList.add(item);
                    vegetableList.remove(item);
                }
            }
        });


        setVisible(true);
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                dispose();
            }
        });
    }

    public static void main(String[] args) {
        new GroceryListFrame();
    }
}
