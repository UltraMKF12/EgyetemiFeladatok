import javax.swing.*;
import java.awt.*;

public class RaceFrame extends JFrame {
    private RaceTrack raceTrack;
    private JPanel contentPanel;

    public RaceFrame(RaceTrack raceTrack) {
        this.raceTrack = raceTrack;

        contentPanel = new JPanel();
        contentPanel.setLayout(new BorderLayout());

        contentPanel.add(raceTrack, BorderLayout.CENTER);
        this.setContentPane(contentPanel);
    }
}
