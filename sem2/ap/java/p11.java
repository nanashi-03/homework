import java.util.Random;

interface Sortable {
    void sort(int[] arr);
}

class BubbleSort implements Sortable {
    @Override
    public void sort(int[] arr) {
        int n = arr.length;

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}

public class p11 {
    public static void main(String[] args) {
        Random rand = new Random();
        int n = rand.nextInt(50);
        int[] arr = new int[n];

        for (int i = 0; i < n; i++) {
            arr[i] = rand.nextInt() % 100;
        }

        Sortable sorter = new BubbleSort();

        System.out.println("Before Sorting:");

        for (int num : arr) {
            System.out.print(num + " ");
        }

        sorter.sort(arr);

        System.out.println("\nAfter Sorting:");

        for (int num : arr) {
            System.out.print(num + " ");
        }
    }
}
