import java.io.*;

public class p15 {
    public static void main(String[] args) {
        String fileName = "Fibo.txt";
        int last = -1;

        double sqrt5 = Math.sqrt(5);
        double phi = (1 + sqrt5) / 2;
        double psi = (1 - sqrt5) / 2;

        try (BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
            String line;
            while ((line = reader.readLine()) != null) {
                if (!line.trim().isEmpty()) {
                    last = Integer.parseInt(line.trim());
                }
            }
        } catch (IOException | NumberFormatException e) {
            System.err.println("Error reading file: " + e.getMessage());
            return;
        }

        if (last == -1) {
            System.out.println("Not enough data in file to continue the sequence.");
            return;
        }

        int fibo = 0, i = 0;

        while (fibo < last) {
            fibo = (int) Math.floor((Math.pow(phi, i) - Math.pow(psi, i)) / sqrt5);
            i++;
        }

        // 2. Append next numbers < 250
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName, true))) {
            while (true) {
                fibo = (int) Math.floor((Math.pow(phi, i) - Math.pow(psi, i)) / sqrt5);

                if (fibo >= 250)
                    break;

                writer.write(fibo + "\n");
                i++;
            }
            System.out.println("Successfully appended Fibonacci numbers.");
        } catch (IOException e) {
            System.err.println("Error appending to file: " + e.getMessage());
        }
    }
}
