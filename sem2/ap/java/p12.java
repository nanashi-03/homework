import java.util.Random;

class Plate {
    private int radius;

    public Plate(int radius) {
        this.radius = radius;
    }

    public int getPlateArea() {
        return (int) Math.pow(radius, 2);
    }

    public void display() {
        System.out.println("Plate Radius       : " + radius);
    }
}

class Tray implements ResizableTray {
    private int width;
    private int length;
    private Plate plate;
    private int plates;

    public Tray(int width, int length, Plate plate) throws InvalidDataException {
        if (width > 0 && length > 0) {
            this.width = width;
            this.length = length;
            this.plate = plate;
            plates = (width * length) / plate.getPlateArea();
        } else {
            throw new InvalidDataException("Invalid Value: Dimensions must be > 0 and plates must be > 0");
        }
    }

    @Override
    public void W(int width) throws InvalidDataException {
        if (width > 0) {
            this.width = width;
            this.plates = calculate();
        } else {
            throw new InvalidDataException("Invalid Width Value");
        }
    }

    @Override
    public void L(int length) throws InvalidDataException {
        if (length > 0) {
            this.length = length;
            this.plates = calculate();
        } else {
            throw new InvalidDataException("Invalid Length Value");
        }
    }

    public int calculate() {
        int plateArea = plate.getPlateArea();
        if (plateArea == 0)
            return 0;
        return (width * length) / plateArea;
    }

    public void plateDisplay() {
        plate.display();
    }

    public void display() {
        System.out.println("Tray Width       : " + width);
        System.out.println("Tray Length      : " + length);
        System.out.println("Number of Plates : " + plates);
    }
}

public class p12 {
    public static void main(String[] args) {
        Random rand = new Random();

        try {
            int initialWidth = rand.nextInt(100) + 1;
            int initialLength = rand.nextInt(100) + 1;
            int plateRadius = rand.nextInt(10) + 1;

            Tray t = new Tray(initialWidth, initialLength, new Plate(plateRadius));
            // Tray t = new Tray(25, 25, new Plate(5));

            System.out.println("Plate Dimension");
            t.plateDisplay();

            System.out.println("\nBefore Resizing");
            t.display();

            int newWidth = rand.nextInt(100) + 1;
            int newLength = rand.nextInt(100) + 1;

            System.out.println("\nResizing to Width: " + newWidth + ", Length: " + newLength);
            t.W(newWidth);
            t.L(newLength);
            // t.W(50);
            // t.L(50);

            System.out.println("\nAfter Resizing");
            t.display();

        } catch (InvalidDataException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}
