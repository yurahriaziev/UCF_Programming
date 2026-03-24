#include <stdio.h>

void print_perm(int perm[], int n) {
    for (int i=0; i<n; i++) {
        printf("%d ", perm[i]);
    }
    printf("\n");
}

void generate_perms(int arr[], int perm[], int used[], int n, int level) {
    if (level == n) {
        print_perm(perm, n);
        return;
    }

    for (int i=0; i<n; i++) {
        if (used[i] == 0) {
            perm[level] = arr[i];
            used[i] = 1;

            generate_perms(arr, perm, used, n, level + 1);

            used[i] = 0;
        }
    }
}

int main(void) {
    int arr[] = {1, 2, 3};
    int n = 3;

    int perm[3];
    int used[3] = {0};

    generate_perms(arr, perm, used, n, 0);

    return 0;
}