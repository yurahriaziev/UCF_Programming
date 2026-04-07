#include <stdio.h>
#include <stdlib.h>

void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// SELECTION SORT
// step 1: swap function
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// step 2: selection sort function
void selection_sort(int arr[], int n) {
    int i, j, min_index, temp;

    for (i=0; i<n-1; i++) {
        // find the min element in unsorted array;
        min_index = i;
        for (j = i+1; j<n; j++) {
            // check if an element is more less than current element
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        // swap the found minimum element with the first
        swap(&arr[i], &arr[min_index]);
    }
}

// INSERTION SORT
// step 1 only
void insertion_sort(int arr[], int n) {
    int i, item, j;

    for (i=1; i<n; i++) {
        item = arr[i];

        // move elements of arr[0..i-1], that are
        // greater than key(item), to one position
        // ahead of their current position
        for (j=i-1; j>=0; j--) {
            if (arr[j] > item) {
                arr[j+1] = arr[j];
            } else {
                break;
            }
        }
        arr[j+1] = item;
    }
}

// BUBBLE SORT
// step 1: swap function
// implemented above
// step 2: bubble sort function
void bubble_sort(int arr[], int n) {
    int i, j, temp;

    for (i=0; i<n-1; i++) {
        for (j=0; j<n-i-1; j++) {
            // check if current element is bigger than next one, if so, swap it
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

// MERGE SORT
// step 1: merge funtion
// merge two subarrays of arr[]
// first subarray is arr[left...mid]
// second subarray is arr[mid...right]
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1; // length of left list
    int n2 = right - mid; // length of the right list

    // create temp arrays
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    // copy list items to the left and right arrays
    for (i=0; i<n1; i++) {
        L[i] = arr[left + i];
    }
    for (j=0; j<n2; j++) {
        R[j] = arr[mid + j + 1];
    }

    // merge the temp arrays back to arr[left...right]
    i=0;
    j=0;
    k=left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // copy remaining elements
    while (i < n1) {
        arr[k] = L[i];
        k++;
        i++;
    }

    while (j < n2) {
        arr[k] = R[j];
        k++;
        j++;
    }

    free(L);
    free(R);
}
// step 2: merge sort function
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        // get the mid point
        int mid = (left + right) / 2;

        // sort first and second halves
        merge_sort(arr, left, mid);
        merge_sort(arr, mid+1, right);

        // merge the lists together
        merge(arr, left, mid, right);
    }
}

// QUICK SORT
// step 1: is sorted function
int is_sorted(int arr[], int n) {
    int i;
    for (i=0; i<n-1; i++) {
        if (arr[i] > arr[i+1]) {
            return 0;
        }
    }

    return 1;
}
// step 2: swap function
// implemented above

// step 3: partition function
int partition(int *arr, int low, int high) {
    // pick a random partition element and swap it into the index low
    int i = low + rand()%(high - low + 1);
    swap(&arr[low], &arr[i]);

    // the pivot location
    int lowpos = low;

    // starting point is next of low
    low++;

    // run the partition for as long as low and high don't cross
    while (low <= high) {
        // move the low pointer until we find a value too large for this side
        while (low<=high && arr[low]<=arr[lowpos]) {
            low++;
        }

        // move the high pointer until we find a value too small for this side
        while (high>=low && arr[high] > arr[lowpos]) {
            high--;
        }

        // once two elements that are on the wrong sides are found, swap them
        if (low<high) {
            swap(&arr[low], &arr[high]);
        }
    }

    // swap the pivot point into its correct location
    swap(&arr[lowpos], &arr[high]);

    // return the partition point;
    return high;
}

// step 4: quick sort function
void quick_sort(int *arr, int low, int high) {
    // sort only if we have to sort more than one number
    if (low < high) {
        int split = partition(arr, low, high);
        quick_sort(arr, low, split-1);
        quick_sort(arr, split+1, high);
    }
}

int main()
{
    int arr[] = { 5, 8, 3, 1, 4, 7, 6, 2 };
    int n = 8; //size of the array

    int choice = 5;
    if (choice == 1) {
        // SELECTION SORT
        printArray(arr, n);
        selection_sort(arr, n);
        printArray(arr, n);
    } else if (choice == 2) {
        // INSERTION SORT
        printArray(arr, n);
        insertion_sort(arr, n);
        printArray(arr, n);
    } else if (choice == 3) {
        // BUBBLE SORT
        printArray(arr, n);
        bubble_sort(arr, n);
        printArray(arr, n);
    } else if (choice == 4) {
        // MERGE SORT
        printArray(arr, n);
        merge_sort(arr, 0, n-1);
        printArray(arr, n);
    } else if (choice == 5) {
        // QUICK SORT
        printArray(arr, n);
        quick_sort(arr, 0, n-1);
        printArray(arr, n);
    }

    return 0;
}