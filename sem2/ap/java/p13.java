import java.util.Random;

class Ball {
    private int radius;

    public Ball(int radius) {
        this.radius = radius;
    }

    public int getBallVolume() {
        return (int) Math.pow(radius, 3);
    }

    public void display() {
        System.out.println("Ball Radius       : " + radius);
    }
}

interface ResizableBox extends ResizableTray {
    void D(int depth) throws InvalidDataException;
}

class NewBox implements ResizableBox {
    private int width;
    private int length;
    private int depth;
    private int balls;
    private Ball ball;

    public NewBox(int width, int length, int depth, Ball ball) throws InvalidDataException {
        if (width > 0 && length > 0 && depth > 0 && ball.getBallVolume() > 0) {
            this.width = width;
            this.length = length;
            this.depth = depth;
            this.ball = ball;
            balls = (width * length * depth) / ball.getBallVolume();
        } else
            throw new InvalidDataException("Invalid Value");
    }

    @Override
    public void W(int width) throws InvalidDataException {
        if (width > 0) {
            this.width = width;
            this.balls = calculate();
        } else {
            throw new InvalidDataException("Invalid Width Value");
        }
    }

    @Override
    public void L(int length) throws InvalidDataException {
        if (length > 0) {
            this.length = length;
            this.balls = calculate();
        } else {
            throw new InvalidDataException("Invalid Length Value");
        }
    }

    @Override
    public void D(int depth) throws InvalidDataException {
        if (depth > 0) {
            this.depth = depth;
            this.balls = calculate();
        } else {
            throw new InvalidDataException("Invalid Length Value");
        }
    }

    public int calculate() {
        int ballVolume = ball.getBallVolume();
        if (ballVolume == 0)
            return 0;
        return (width * length * depth) / ballVolume;
    }

    public void ballDisplay() {
        ball.display();
    }

    public void display() {
        System.out.println("Width          : " + width);
        System.out.println("Length         : " + length);
        System.out.println("Depth          : " + depth);
        System.out.println("No. of Balls   : " + balls);
    }
}

public class p13 {
    public static void main(String[] args) {
        Random rand = new Random();

        try {
            int initialWidth = rand.nextInt(50) + 1;
            int initialLength = rand.nextInt(50) + 1;
            int initialDepth = rand.nextInt(50) + 1;
            int ballRadius = rand.nextInt(10) + 1;

            NewBox box = new NewBox(initialWidth, initialLength, initialDepth, new Ball(ballRadius));
            // NewBox box = new NewBox(5, 5, 5, new Ball(5));

            System.out.println("Ball Dimension");
            box.ballDisplay();

            System.out.println("Before Resizing:");
            box.display();

            box.W(rand.nextInt(50));
            box.L(rand.nextInt(50));
            box.D(rand.nextInt(50));
            // box.W(10);
            // box.L(10);
            // box.D(10);

            System.out.println("\nAfter Resizing:");
            box.display();

        } catch (InvalidDataException e) {
            System.err.println(e.getMessage());
        }
    }
}
