import java.util.Random;
import java.util.Scanner;

class Emp {

    protected long id;
    protected int depCode;

    public Emp(long id) {
        this.id = id;
    }

    public Emp(long id, int depCode) throws InvalidDataException {
        if (depCode < 0 || depCode > 5) {
            throw new InvalidDataException(
                "Department Code must be between 0 and 5"
            );
        }
        this.id = id;
        this.depCode = depCode;
    }

    public void print() {
        System.out.println("ID: " + id + ", Department Code: " + depCode);
    }
}

class Graded_Emp extends Emp {

    protected char grade;

    public Graded_Emp(long id, int depCode, char grade)
        throws InvalidDataException {
        super(id);

        if (depCode < 0 || depCode > 10) {
            throw new InvalidDataException(
                "Department Code must be between 0 and 10"
            );
        }

        if (grade < 'A' || grade > 'E') {
            throw new InvalidDataException("Grade must be between A and E");
        }

        this.depCode = depCode;
        this.grade = grade;
    }

    @Override
    public void print() {
        System.out.println(
            "ID: " + id + ", Department Code: " + depCode + ", Grade: " + grade
        );
    }
}

class Graded_Emp_ByMarks extends Emp {

    private int[] marks;

    public Graded_Emp_ByMarks(long id, int depCode, int[] marks)
        throws InvalidDataException {
        super(id);

        if (depCode < 0 || depCode > 10) {
            throw new InvalidDataException(
                "Department Code must be between 0 and 10"
            );
        }

        if (marks == null) {
            throw new InvalidDataException("Marks array cannot be null");
        }

        for (int m : marks) {
            if (m < 0 || m > 100) {
                throw new InvalidDataException(
                    "Marks must be between 0 and 100"
                );
            }
        }

        this.depCode = depCode;
        this.marks = marks;
    }

    public double getAverage() {
        if (marks.length == 0) {
            throw new ArithmeticException("Division by zero error!");
        }

        int sum = 0;
        for (int m : marks) {
            sum += m;
        }
        return (double) sum / marks.length;
    }

    public char getGrade() {
        double avg = getAverage();
        if (avg >= 90) return 'A';
        else if (avg >= 80) return 'B';
        else if (avg >= 70) return 'C';
        else if (avg >= 60) return 'D';
        else return 'E';
    }

    @Override
    public void print() {
        double avg = getAverage();

        System.out.println("ID: " + id + ", Department Code: " + depCode);
        System.out.print("Skill Marks: ");
        for (int i = 0; i < marks.length; i++) {
            System.out.print(marks[i] + (i == marks.length - 1 ? "" : ", "));
        }
        System.out.println(
            "\nAverage Marks: " + avg + ", Grade: " + getGrade()
        );
    }
}

public class p5_8 {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Random rand = new Random();

        while (true) {
            System.out.println("\n=========================================");
            System.out.println("          EMPLOYEE CREATION MENU         ");
            System.out.println("=========================================");
            System.out.println("1. Create Standard Employee (Emp)");
            System.out.println("2. Create Graded Employee (Graded_Emp)");
            System.out.println(
                "3. Create Graded Employee by Marks (Graded_Emp_ByMarks)"
            );
            System.out.println("4. Exit");
            System.out.print("Enter your choice: ");

            int choice = sc.nextInt();
            long id;
            int depCode;

            try {
                switch (choice) {
                    case 1:
                        System.out.println(
                            "\n--- Create Standard Employee ---"
                        );
                        System.out.print("Enter Employee ID: ");
                        id = sc.nextLong();
                        System.out.print("Enter Department Code (0-5): ");
                        depCode = sc.nextInt();

                        Emp e = new Emp(id, depCode);
                        System.out.println(
                            "\nEmployee profile created successfully:"
                        );
                        e.print();
                        break;
                    case 2:
                        System.out.println("\n--- Create Graded Employee ---");
                        System.out.print("Enter Employee ID: ");
                        id = sc.nextLong();
                        System.out.print("Enter Department Code (0-10): ");
                        depCode = sc.nextInt();
                        System.out.print("Enter Grade (A-E): ");
                        char grade = sc.next().charAt(0);

                        Graded_Emp ge = new Graded_Emp(id, depCode, grade);
                        System.out.println(
                            "\nGraded Employee profile created successfully:"
                        );
                        ge.print();
                        break;
                    case 3:
                        System.out.println(
                            "\n--- Create Graded Employee By Marks ---"
                        );
                        System.out.print("Enter Employee ID: ");
                        id = sc.nextLong();
                        System.out.print("Enter Department Code (0-10): ");
                        depCode = sc.nextInt();
                        System.out.print("Enter number of skills: ");
                        int n = sc.nextInt();

                        if (n < 0) n = 0;

                        int[] marks = new int[n];
                        for (int i = 0; i < n; i++) {
                            marks[i] = rand.nextInt(101);
                        }

                        Graded_Emp_ByMarks mge = new Graded_Emp_ByMarks(
                            id,
                            depCode,
                            marks
                        );

                        try {
                            System.out.println(
                                "\nGraded Employee By Marks metrics computed:"
                            );
                            mge.print();
                        } catch (ArithmeticException ae) {
                            System.out.println(
                                "\n[Notice] Cannot calculate average (0 skills entered). Falling back to manual entry."
                            );
                            System.out.print(
                                "Please manually enter the grade (A-E) for this employee: "
                            );
                            char manualGrade = sc.next().charAt(0);

                            Graded_Emp fallbackGe = new Graded_Emp(
                                id,
                                depCode,
                                manualGrade
                            );
                            System.out.println(
                                "Created replacement Graded_Emp object successfully:"
                            );
                            fallbackGe.print();
                        }
                        break;
                    case 4:
                        System.out.println("Exiting system. Goodbye!");
                        sc.close();
                        System.exit(0);
                    default:
                        System.out.println(
                            "Invalid choice! Please pick an option between 1 and 4."
                        );
                }
            } catch (InvalidDataException ide) {
                System.out.println("\n[Data Error]: " + ide.getMessage());
            }
        }
    }
}
