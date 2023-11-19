import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class CounterFrame extends JFrame implements CounterListener {
    private JButton startButton;
    private JButton stopButton;
    private JButton suspendButton;
    private JButton resumeButton;
    private JLabel counterLabel;
    private JPanel contentPanel;
    private Counter counter;

    public CounterFrame() {
        startButton = new JButton("Start");
        stopButton = new JButton("Stop");
        suspendButton = new JButton("Suspend");
        resumeButton = new JButton("Resume");
        counterLabel = new JLabel("0");
        contentPanel = new JPanel();

        counter = new Counter();

        contentPanel.add(startButton);
        contentPanel.add(stopButton);
        contentPanel.add(suspendButton);
        contentPanel.add(resumeButton);
        contentPanel.add(counterLabel);

        enableButtons(true, false, false, false);

        this.setContentPane(contentPanel);
        this.setTitle("CounterFrame");
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);

        startButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                counter.start();
                enableButtons(false, true, true, false);
            }
        });

        stopButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                counter.stop();
                enableButtons(true, false, false, false);
            }
        });

        suspendButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                counter.suspend();
                enableButtons(false, false, false, true);
            }
        });

        resumeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                counter.resume();
                enableButtons(false, true, true, false);
            }
        });

        counter.addCounterListener(this);
        counter.addCounterListener(new CounterListener() {
            @Override
            public void counterValueChanged(CounterEvent e) {
                System.out.println(e.getValue());
            }
        });
    }

    public void setCounterValue(int value) {
        counterLabel.setText(value+"");
    }

    private void enableButtons(boolean start, boolean stop, boolean suspend, boolean resume) {
        startButton.setEnabled(start);
        stopButton.setEnabled(stop);
        suspendButton.setEnabled(suspend);
        resumeButton.setEnabled(resume);
    }

    @Override
    public void counterValueChanged(CounterEvent e) {
        setCounterValue(e.getValue());
    }
}
