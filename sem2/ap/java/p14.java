import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class p14 {
    public static void main(String[] args) {
        String fileName = "Fibo.txt";
        int count = 10;
        double sqrt5 = Math.sqrt(5);
        double phi = (1 + sqrt5) / 2;
        double psi = (1 - sqrt5) / 2;

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            for (int i = 0; i < count; i++) {
                int fibo = (int) Math.floor((Math.pow(phi, i) - Math.pow(psi, i)) / sqrt5);
                writer.write(fibo + "\n");
            }
            System.out.println("Successfully wrote the first 10 Fibonacci numbers to " + fileName);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }
    }
}
