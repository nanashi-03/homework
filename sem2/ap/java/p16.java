import java.io.*;

public class p16 {
    public static void main(String[] args) {
        String textFile = "Fibo.txt";
        String binaryFile = "Fibo.bin";

        try (BufferedReader reader = new BufferedReader(new FileReader(textFile));
                DataOutputStream dos = new DataOutputStream(new FileOutputStream(binaryFile))) {

            String line;
            int count = 0;

            while ((line = reader.readLine()) != null) {
                String trimmedLine = line.trim();

                if (!trimmedLine.isEmpty()) {
                    int number = Integer.parseInt(trimmedLine);

                    dos.writeInt(number);
                    count++;
                }
            }

            System.out.println("Successfully converted " + count + " numbers from " + textFile + " into binary format ("
                    + binaryFile + ").");

        } catch (IOException e) {
            System.err.println("An I/O error occurred during file operations: " + e.getMessage());
        } catch (NumberFormatException e) {
            System.err.println("Error parsing integer data from text file: " + e.getMessage());
        }
    }
}
