import java.util.Random;

public class CarController extends Thread {
    private Car car;

    public CarController(Car car) {
        this.car = car;
    }

    @Override
    public void run() {
        Random random = new Random();

        while(!RaceController.finished && this.car.getX() < RaceController.TRACK_LENGTH) {
            car.setX(car.getX() + random.nextInt(5));

            try {
                Thread.sleep(random.nextInt(10));
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }

        if(this.car.getX() >= RaceController.TRACK_LENGTH) {
            RaceController.finished = true;
        }
    }
}
