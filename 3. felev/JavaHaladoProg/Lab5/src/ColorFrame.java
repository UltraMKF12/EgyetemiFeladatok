// Széri József - 514
import java.awt.*;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.Random;

public class ColorFrame extends Frame {
    private Choice colorChoice;
    private Random random;

    public ColorFrame() {
        setBounds(100, 100, 500, 500);
        setLayout(new FlowLayout());

        colorChoice = new Choice();
        colorChoice.add("red");
        colorChoice.add("green");
        colorChoice.add("blue");
        colorChoice.add("random");
        add(colorChoice);

        random = new Random();

        colorChoice.addItemListener(new ItemListener() {
            @Override
            public void itemStateChanged(ItemEvent e) {
                String selectedColor = colorChoice.getSelectedItem();

                if (selectedColor.equals("red")) {
                    setBackground(Color.RED);
                } else if (selectedColor.equals("green")) {
                    setBackground(Color.GREEN);
                } else if (selectedColor.equals("blue")) {
                    setBackground(Color.BLUE);
                } else if (selectedColor.equals("random")) {
                    int r = random.nextInt(256);
                    int g = random.nextInt(256);
                    int b = random.nextInt(256);
                    setBackground(new Color(r, g, b));
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
        new ColorFrame();
    }
}
