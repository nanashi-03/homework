public class StackSorter {
    public static SpecialStack sortStack(final Stack A) {
        // Stack A = new Stack();
        final Stack B = new Stack(A.size());
        final SpecialStack C = new SpecialStack(A.size());

        System.out.println("Initial Stack A: ");
        A.display();

        while (!A.isEmpty()) {
            int x = A.peek();
            int y = C.peek();

            if (x <= y) {
                x = A.pop();
                C.push(x);

                while (!B.isEmpty()) {
                    final int z = B.pop();
                    C.push(z);
                }
            } else {
                y = C.pop();
                B.push(y);
            }
        }

        return C;
    }
}
