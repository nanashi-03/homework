import java.util.Random;
import java.util.Scanner;

public class p4 {
    public static void main(String[] args) {
        int n = 0;
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the number of elements:");
        n = sc.nextInt();
        Random rand = new Random();
        Stack A = new Stack(n);
        for (int i = 0; i < n; i++) {
            int num = rand.nextInt(100) + 1;
            A.push(num);
        }

        SpecialStack res = StackSorter.sortStack(A);

        System.out.println("Final Sorted SpecialStack C: ");
        res.display();
        sc.close();
    }
}
