#include <stdio.h>

int binary_search_iterative(int list[], int k, int len) {
    int left = 0, right = len-1, mid;

    while (left <= right) {
        mid = (left + right) / 2;
    
        if (list[mid] == k) {
            return mid;
        } else if (k > list[mid]) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

int binary_search_recursive(int list[], int left, int right, int k) {
    if (left <= right) {
        int mid = (left + right) / 2;
        if (k < list[mid]) {
            return binary_search_recursive(list, list, mid-1, k);
        } else if (k > list[mid]) {
            return binary_search_recursive(list, mid+1, right, k);
        } else {
            return mid;
        }
    } else {
        return -1;
    }
}

int main(void) {

}