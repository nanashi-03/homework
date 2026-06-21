import java.time.LocalDate;
import java.util.Scanner;

public class p1 {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the Name:");
        String name = sc.nextLine();
        System.out.println("Enter date of birth (YYYY-MM-DD):");
        String dobString = sc.nextLine();

        Student s = new Student(name, LocalDate.parse(dobString));
        s.calculateAge();

        System.out.println("Age = " + s.age);
        s.category();
        sc.close();
    }
}

class Student {
    String name;
    LocalDate dob;
    int age;

    public Student(String n, LocalDate d) {
        name = n;
        dob = d;
    }

    void calculateAge() {
        LocalDate today = LocalDate.now();

        int currentYear = today.getYear();
        int birthYear = dob.getYear();

        age = currentYear - birthYear;

        int currentMonth = today.getMonthValue();
        int birthMonth = dob.getMonthValue();

        if (currentMonth < birthMonth) {
            age--;
        } else if (currentMonth == birthMonth) {
            int currentDay = today.getDayOfMonth();
            int birthDay = dob.getDayOfMonth();
            if (currentDay < birthDay) {
                age--;
            }
        }
    }

    void category() {
        if (age < 18)
            System.out.println("Under Age");
        else if (age < 30)
            System.out.println("Young Adult");
        else if (age < 45)
            System.out.println("Matured Age");
        else
            System.out.println("Middle Aged");
    }
}
