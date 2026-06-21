public class SpecialStack extends Stack {

    public SpecialStack(final int size) {
        super(size);
    }

    @Override
    public void push(final int value) {

        if (isEmpty()) {
            super.push(value);
        }

        else if (value < peek()) {
            super.push(value);
        }

        else {
            System.out.println(
                    "Cannot push " + value +
                            ". It must be smaller than top element " + peek());
        }
    }
}
