import java.io.*;

public class test {
    public static void main(String[] args) {
        String binaryFile = "Fibo.bin";

        System.out.println("Reading contents of " + binaryFile + ":\n");

        try (DataInputStream dis = new DataInputStream(new FileInputStream(binaryFile))) {
            int count = 0;

            while (dis.available() > 0) {
                int number = dis.readInt();

                System.out.print(number + " ");
                count++;

                if (count % 10 == 0) {
                    System.out.println();
                }
            }

            System.out.println("\n\nTotal numbers read: " + count);

        } catch (FileNotFoundException e) {
            System.err.println(
                    "Error: The file '" + binaryFile + "' could not be found. Please run the generator first.");
        } catch (IOException e) {
            System.err.println("An I/O error occurred while reading the binary file: " + e.getMessage());
        }
    }
}
