public class Stack {
    private final int maxSize;
    private final int[] s;
    private int top;

    public Stack(final int size) {
        this.maxSize = size;
        this.s = new int[maxSize];
        this.top = -1;
    }

    public boolean isEmpty() {
        return top == -1;
    }

    public int size() {
        return top + 1;
    }

    public void push(final int value) {
        if (top == maxSize - 1) {
            System.out.println("Stack Overflow! Cannot push " + value);
        } else {
            s[++top] = value;
            // System.out.println("Pushed " + value);
        }
    }

    public int pop() {
        if (top == -1) {
            System.out.println("Stack Underflow! Nothing to pop.");
            return -1;
        } else {
            return s[top--];
        }
    }

    public int peek() {
        if (top == -1) {
            return Integer.MAX_VALUE;
        }
        return s[top];
    }

    public void display() {
        if (top == -1) {
            System.out.println("Stack is empty.");
        } else {
            System.out.print("Stack (Top to Bottom): ");
            for (int i = top; i >= 0; i--) {
                System.out.print(s[i] + " ");
            }
            System.out.println();
        }
    }

    public void display(final int depth) {
        if (depth < 0 || depth > top) {
            System.out.println("Invalid position!");
        } else {
            System.out.println("Value at index " + depth + ": " + s[depth]);
        }
    }
}
