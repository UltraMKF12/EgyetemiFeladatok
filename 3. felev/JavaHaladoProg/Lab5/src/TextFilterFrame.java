// Széri József - 514
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class TextFilterFrame extends Frame {
    private TextField filterTextField;
    private Button filterButton;
    private TextArea textArea;

    public TextFilterFrame() {
        setBounds(100, 100, 500, 500);
        setLayout(new BorderLayout());


        filterTextField = new TextField(20);
        add(filterTextField, BorderLayout.NORTH);

        filterButton = new Button("Filter");
        add(filterButton, BorderLayout.CENTER);

        textArea = new TextArea();
        add(textArea, BorderLayout.SOUTH);


        filterButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String filterWord = filterTextField.getText();
                String selectedText = textArea.getSelectedText();

                String filteredText = selectedText.replace(filterWord, "");
                textArea.setText(filteredText);
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
        new TextFilterFrame();
    }
}
