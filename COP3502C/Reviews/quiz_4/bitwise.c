#include <stdio.h>

int bitNumOn(int b) {
    // 12 -> 1100, should return 2, since there are 2 1s
    int count = 0;
    int mask = 1;

    // loop version
    while (mask != 0) {
        if (b & mask != 0) {
            count++;
            b = mask << 1;
        }
    }

    return count;

    // recursive version
}

int isOdd(int i) {
    return i&1;
}

// int main() {
//     // printf("%d\n", isOdd(4));
//     // printf("%d", isOdd(5));

//     unsigned char a = 5, b = 9;
//     printf("a<<1 = %d\n", a<<1);
//     printf("b<<1 = %d\n\n", b<<1);
    
//     printf("a>>1 = %d\n", a>>1);
//     printf("b>>1 = %d\n", b>>1);

//     return 0;
// }

int sumBits(int n) {
    // int sum = 0;
    // while (n > 0) {
    //     sum += (n & 1);
    //     n = (n >> 1);
    // }

    if (n == 0) {
        return 0;
    }

    return (n & 1) + sumBits(n >> 1);
}

int paintFence(int pattern, int paintLoc[], int paintLen) {
    int finalFence = 0;
    for (int i=0; i<paintLen; i++) {
        finalFence = finalFence | (pattern << (paintLoc[i]));
    }
    return finalFence;
}

int main() {
    int arr[] = {9, 3, 4, 5, 12};
    int n = 5;
    int target = 22;

    for (int i=0; i < (1 << n); i++) {
        int sum = 0;
        for (int j=0; j < n; j++) {
            if ( (i & (1 << j)) != 0) {
                sum += arr[j];
            }
        }

        if (sum == target) {
            printf("Can add to target");
        }
    }

    printf("\n%d", sumBits(12));
}
