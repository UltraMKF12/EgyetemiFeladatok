public class TrackRefresher extends Thread {
    private RaceTrack raceTrack;

    public TrackRefresher(RaceTrack raceTrack) {
        this.raceTrack = raceTrack;
    }

    @Override
    public void run() {
        while(!RaceController.finished) {
            raceTrack.repaint();
            try {
                Thread.sleep(30);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
