import java.io.*;

public class p18 {
    public static void main(String[] args) {
        String fileName = "Profile.bin";

        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(fileName))) {

            Profile[] profiles = (Profile[]) ois.readObject();

            if (profiles == null || profiles.length == 0) {
                System.out.println("No records found inside the profile file.");
                return;
            }

            Profile highestScorer = profiles[0];

            for (int i = 1; i < profiles.length; i++) {
                if (profiles[i].getAvgMarks() > highestScorer.getAvgMarks()) {
                    highestScorer = profiles[i];
                }
            }
            System.out.println(highestScorer);

        } catch (FileNotFoundException e) {
            System.err.println("Error: The file '" + fileName
                    + "' could not be found. Please run your ProfileSaver program first.");
        } catch (IOException e) {
            System.err.println("An I/O error occurred while reading the file: " + e.getMessage());
        } catch (ClassNotFoundException e) {
            System.err.println("Class structure matching the data could not be found: " + e.getMessage());
        }
    }
}
