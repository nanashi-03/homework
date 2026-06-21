import java.util.Scanner;

public class p2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter stack size: ");
        int size = sc.nextInt();
        Stack st = new Stack(size);

        while (true) {
            System.out.println("\n--- Stack Operations ---");
            System.out.println("1. Push\n2. Pop\n3. Peek\n4. Display All\n5. Display at Index\n6. Exit");
            System.out.print("Choice: ");
            int choice = sc.nextInt();

            switch (choice) {
                case 1:
                    System.out.print("Enter value to push: ");
                    st.push(sc.nextInt());
                    break;
                case 2:
                    int popped = st.pop();
                    if (popped != -1)
                        System.out.println("Popped: " + popped);
                    break;
                case 3:
                    System.out.println(st.peek());
                    break;
                case 4:
                    st.display();
                    break;
                case 5:
                    System.out.print("Enter index: ");
                    st.display(sc.nextInt());
                    break;
                case 6:
                    System.out.println("Exiting...");
                    sc.close();
                    System.exit(0);
                default:
                    System.out.println("Invalid choice!");
            }
        }
    }
}
