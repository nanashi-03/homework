import java.util.Random;
import java.util.Scanner;

public class p5 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Random rand = new Random();

        try {
            System.out.println("Enter the id of Employee e and the department code: ");
            long id = sc.nextLong();
            int depCode = sc.nextInt();
            Emp e = new Emp(id, depCode);
            e.print();

            // System.out.println("\nEnter the id of Graded Employee ge, the department
            // code, and the grade: ");
            // id = sc.nextLong();
            // depCode = sc.nextInt();
            // char grade = sc.next().charAt(0);
            // Graded_Emp ge = new Graded_Emp(id, depCode, grade);
            // ge.print();

            System.out
                    .println("\nEnter the id of Marks Graded Employee mge, the department code, and number of skills:");
            id = sc.nextLong();
            depCode = sc.nextInt();
            int n = sc.nextInt();

            if (n < 0)
                n = 0;

            int[] marks = new int[n];
            for (int i = 0; i < n; i++) {
                marks[i] = rand.nextInt(100);
            }

            Graded_Emp_ByMarks mge = new Graded_Emp_ByMarks(id, depCode, marks);

            try {
                mge.print();
            } catch (ArithmeticException ae) {
                System.out.println("\n[Notice] Cannot calculate average. Falling back to manual entry.");
                System.out.print("Please manually enter the grade (A-E) for this employee: ");
                char manualGrade = sc.next().charAt(0);

                Graded_Emp fallbackGe = new Graded_Emp(id, depCode, manualGrade);
                System.out.println("Created replacement Graded_Emp object successfully:");
                fallbackGe.print();
            }

        } catch (InvalidDataException e) {
            System.out.println("Error: " + e.getMessage());
        } finally {
            sc.close();
        }
    }
}

class Emp {
    protected long id;
    protected int depCode;

    public Emp(long id) {
        this.id = id;
    }

    public Emp(long id, int depCode) throws InvalidDataException {
        if (depCode < 0 || depCode > 5) {
            throw new InvalidDataException("Department Code must be between 0 and 5");
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

    public Graded_Emp(long id, int depCode, char grade) throws InvalidDataException {
        super(id);

        if (depCode < 0 || depCode > 10) {
            throw new InvalidDataException("Department Code must be between 0 and 10");
        }

        if (grade < 'A' || grade > 'E') {
            throw new InvalidDataException("Grade must be between A and E");
        }

        this.depCode = depCode;
        this.grade = grade;
    }

    @Override
    public void print() {
        System.out.println("ID: " + id + ", Department Code: " + depCode + ", Grade: " + grade);
    }
}

class Graded_Emp_ByMarks extends Emp {
    private int[] marks;

    public Graded_Emp_ByMarks(long id, int depCode, int[] marks) throws InvalidDataException {
        super(id);

        if (depCode < 0 || depCode > 10) {
            throw new InvalidDataException("Department Code must be between 0 and 10");
        }

        if (marks == null) {
            throw new InvalidDataException("Marks array cannot be null");
        }

        for (int m : marks) {
            if (m < 0 || m > 100) {
                throw new InvalidDataException("Marks must be between 0 and 100");
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
        if (avg >= 90)
            return 'A';
        else if (avg >= 80)
            return 'B';
        else if (avg >= 70)
            return 'C';
        else if (avg >= 60)
            return 'D';
        else
            return 'E';
    }

    @Override
    public void print() {
        double avg = getAverage();

        System.out.println("ID: " + id + ", Department Code: " + depCode);

        System.out.println("Skill Marks:");
        for (int m : marks) {
            System.out.print(m + ", ");
        }

        System.out.println("\nAverage Marks: " + avg + ", Grade: " + getGrade());
    }
}
