import javax.swing.*;

public class RaceController {
    public static boolean finished;
    public static final int TRACK_LENGTH = 800;

    private Car[] cars;
    private CarController[] carControllers;
    private RaceTrack raceTrack;
    private TrackRefresher trackRefresher;
    private RaceFrame raceFrame;

    public void initRace(int carCount) {
        cars = new Car[carCount];
        carControllers = new CarController[carCount];

        for(int i = 0; i < carCount; i++) {
            cars[i] = new Car();
            carControllers[i] = new CarController(cars[i]);
        }

        raceTrack = new RaceTrack();
        raceTrack.setCars(cars);

        trackRefresher = new TrackRefresher(raceTrack);

        raceFrame = new RaceFrame(raceTrack);
        raceFrame.setBounds(100, 100, 1000, 20 * carCount + 50);
        raceFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        raceFrame.setVisible(true);
    }

    public void startRace() {
        for(int i = 0; i < carControllers.length; i++) {
            carControllers[i].start();
        }

        trackRefresher.start();
    }
}
