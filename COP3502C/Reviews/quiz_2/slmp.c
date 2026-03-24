#include <stdio.h>

// Version 1: Brute force
// O(lenA * lenB) runtime
void slmp_bruteforce(int A[], int lenA, int B[], int lenB) {
    printf("Brute Force\n");
    for (int i=0; i<lenA; i++) {
        for (int j=0; j<lenB; j++) {
            if (A[i] == B[j]) {
                // found a match;
                printf("%d ", A[i]);
                break;
            }
        }
    }
    printf("\n\n");
}

// Version 2: Binary search
// O(lenA log lenB) runtime
int bin_search(int list[], int len, int item) {
    int l = 0, h = len - 1;
    int mid;
    while (l <= h) {
        mid = (l + h) / 2;
        if (list[mid] == item) {
            return 1;
        } else if (list[mid] < item) {
            l = mid + 1;
        } else {
            h = mid - 1;
        }
    }

    return 0;
}

void slmp_binsearch(int A[], int lenA, int B[], int lenB) {
    printf("Binary Search:\n");
    for (int i=0; i<lenA; i++) {
        if (bin_search(B, lenB, A[i])) {
            printf("%d ", A[i]);
        }
    }
    printf("\n\n");
}

// Version 3: Two pointers
// O(lenA + lenB) runtime
void slmp_twopointers(int A[], int B[], int lenA, int lenB) {
    printf("Two Pointers:\n");
    
    int i = 0, j = 0;

    while (i < lenA && j < lenB) {
        if (A[i] == B[j]) {
            printf("%d ", A[i]);
            i++;
            j++;
        } else if (A[i] < B[j]) {
            i++;
        } else { 
            j++;
        }
    }
    printf("\n\n");
}

int main() {
    int A[] = {1, 3, 4, 7, 9};
    int B[] = {2, 3, 7, 8, 9};

    int lenA = sizeof(A) / sizeof(int);
    int lenB = sizeof(B) / sizeof(int);

    slmp_bruteforce(A, lenA, B, lenB);
    slmp_binsearch(A, lenA, B, lenB);
    slmp_twopointers(A, B, lenA, lenB);

    return 0;
}