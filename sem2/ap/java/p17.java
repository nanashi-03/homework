import java.io.*;
import java.util.Random;
import java.util.Scanner;

public class p17 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Random random = new Random();
        String fileName = "Profile.bin";

        String[] firstNames = { "Anubhav", "Bijan", "Mainak", "Bappa", "Subhayu", "Aviraj", "Gourav", "Tashif",
                "Baisakhi",
                "Sangita" };
        String[] lastNames = { "Chakraborty", "Roy", "Mondal", "Das", "Ganguly", "Chhetri", "Karmakar", "Ahmed",
                "Paul" };

        System.out.print("Enter the number of profiles to generate automatically: ");
        int n = scanner.nextInt();

        Profile[] profiles = new Profile[n];

        for (int i = 0; i < n; i++) {
            String randomName = firstNames[random.nextInt(firstNames.length)] + " " +
                    lastNames[random.nextInt(lastNames.length)];

            int randomAge = 18 + random.nextInt(8);

            double randomMarks = 50.0 + (random.nextDouble() * 50.0);
            randomMarks = Math.round(randomMarks * 100.0) / 100.0;

            profiles[i] = new Profile(randomName, randomAge, randomMarks);
        }

        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(fileName))) {

            oos.writeObject(profiles);

            System.out.println("\n--- Successfully generated and saved " + n + " profiles ---");
            for (Profile p : profiles) {
                System.out.println(p);
            }

        } catch (IOException e) {
            System.err.println("An error occurred while saving profiles: " + e.getMessage());
        } finally {
            scanner.close();
        }
    }
}
