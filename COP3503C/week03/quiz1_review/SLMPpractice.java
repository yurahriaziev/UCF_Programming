package COP3503C.week03.quiz1_review;

public class SLMPpractice {
    public static void main(String[] args) {
        int[] list1 = {2, 5, 8, 10, 15, 20};
        int[] list2 = {5, 9, 10, 12, 15, 22, 25};

        System.out.println("Common elements:");
        findCommonLinear(list1, list2);
    }

    public static void findCommonLinear(int[] arr1, int[] arr2) {
        int i = 0, j = 0;
        boolean match = false;
        while (i < arr1.length && j < arr2.length) {
            if (arr1[i] < arr2[j]) {
                i++;
            } else if (arr2[j] < arr1[i]) {
                j++;
            } else {
                match = true;
                System.out.println("Item: " + arr1[i]);
                i++;
                j++;
            }
        }

        if (!match) {
            System.out.println("No common items");
        }
    }
}
