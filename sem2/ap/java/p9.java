import java.util.Scanner;

interface Shape {
    double getArea();
}

class Rectangle implements Shape {
    private double length;
    private double width;

    public Rectangle(double length, double width) {
        this.length = length;
        this.width = width;
    }

    @Override
    public double getArea() {
        return length * width;
    }
}

class Circle implements Shape {
    private double radius;

    public Circle(double radius) {
        this.radius = radius;
    }

    @Override
    public double getArea() {
        return Math.PI * radius * radius;
    }
}

class Triangle implements Shape {
    private double base;
    private double height;

    public Triangle(double base, double height) {
        this.base = base;
        this.height = height;
    }

    @Override
    public double getArea() {
        return 0.5 * base * height;
    }
}

public class p9 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the length and breadth: ");
        Shape rect = new Rectangle(Math.abs(sc.nextInt()), Math.abs(sc.nextInt()));
        System.out.println("Enter the radius: ");
        Shape circle = new Circle(Math.abs(sc.nextInt()));
        System.out.println("Enter the base and height: ");
        Shape triangle = new Triangle(Math.abs(sc.nextInt()), Math.abs(sc.nextInt()));

        System.out.println("Rectangle Area = " + rect.getArea());
        System.out.println("Circle Area = " + circle.getArea());
        System.out.println("Triangle Area = " + triangle.getArea());
        sc.close();
    }
}
