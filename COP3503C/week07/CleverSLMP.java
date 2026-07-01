package COP3503C.week07;

public class CleverSLMP {
    public static void main(String[] args) {
        int[] list1 = {2, 5, 8, 10, 15, 20};
        int[] list2 = {5, 9, 10, 12, 15, 22, 25};

        System.out.println("Common elements:");
        findCommonLinear(list1, list2);
    }

    static void findCommonLinear(int arr1[], int arr2[]) {
        int i=0;
        int j=0;

        boolean match = false;

        while (i<arr1.length && j<arr2.length) {
            if (arr1[i] < arr2[j]) {
                i++;
            } else if (arr2[j] < arr1[i]) {
                j++;
            } else {
                System.out.println("Found match: " + arr1[i]);
                match = true;

                i++;
                j++;
            }
        }

        if (!match) {
            System.out.println("No matches found");
        }
    }
}
