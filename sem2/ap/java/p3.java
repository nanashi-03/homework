import java.util.Random;
import java.util.Scanner;

public class p3 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Random rand = new Random();
        System.out.println("Enter the size of first Array:");
        int a = sc.nextInt();
        Stack s1 = new Stack(a);

        System.out.println("Enter the elements to push in one by one:");
        while (s1.size() < a) {
            s1.push(rand.nextInt(100) + 1);
        }

        SpecialStack ss1 = StackSorter.sortStack(s1);

        System.out.println("Enter the size of second Array:");
        int b = sc.nextInt();
        Stack s2 = new Stack(b);

        System.out.println("Enter the elements to push in one by one:");
        while (s2.size() < b) {
            s2.push(rand.nextInt(100) + 1);
        }

        SpecialStack ss2 = StackSorter.sortStack(s2);

        System.out.println("Stack 1:");
        ss1.display();

        System.out.println("Stack 2:");
        ss2.display();

        SpecialStack merged = merge(ss1, ss2, 20);

        System.out.println("\nMerged Special Stack:");
        merged.display();
        sc.close();
    }

    static SpecialStack merge(SpecialStack s1, SpecialStack s2, int totalSize) {

        Stack temp = new Stack(totalSize);

        while (!s1.isEmpty() && !s2.isEmpty()) {

            if (s1.peek() < s2.peek()) {
                temp.push(s1.pop());
            } else {
                temp.push(s2.pop());
            }
        }

        while (!s1.isEmpty()) {
            temp.push(s1.pop());
        }

        while (!s2.isEmpty()) {
            temp.push(s2.pop());
        }

        SpecialStack result = new SpecialStack(totalSize);

        while (!temp.isEmpty()) {
            result.push(temp.pop());
        }

        return result;
    }
}
