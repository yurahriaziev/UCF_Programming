#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// selection sort
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void selectionSort(int arr[], int n)
{
	int i, j, min_idx, temp;
	// One by one move boundary of unsorted subarray
	for (i = 0; i < n-1; i++)
	{
	    // printf("\nIteration# %d\n",i+1);
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i+1; j < n; j++)
		if (arr[j] < arr[min_idx])
			min_idx = j;
		// Swap the found minimum element with the first element
		
		swap(&arr[i], &arr[min_idx]);
		//swapping directly in the sorting fuction
		//temp = arr[i];
		//arr[i] = arr[min_idx];
		//arr[min_idx] = temp;

		// printArray(arr, n);
	}
}

// bubble sort
// A function to implement bubble sort
// A function to implement bubble sort
void bubbleSort(int arr[], int n) {
    int i, j,temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {//then swap
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}

// insertion sort
void insertionSort(int arr[], int l, int r) {
    int i, item, j;
    for (i = l + 1; i <= r; i++) {
        item = arr[i];
        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        for(j=i-1; j>=l; j--) {
            if(arr[j]>item) {
                arr[j+1] = arr[j];
            } else {
                break;
            }
        }
        arr[j+1] = item;
    }
}

// marge sort
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    /* create temp arrays */
    int *L = (int*) malloc(n1*sizeof(int));
    int *R = (int*) malloc(n2*sizeof(int));
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1+ j];
    }
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
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
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
        /* Copy the remaining elements of R[], if there
        are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}
/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        // get the mid point
        int m = (l+r)/2;
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        // printf("Testing l=%d r=%d m=%d\n", l, r, m);
        merge(arr, l, m, r);
    }
}

// merge insertion sort
void mergeInsertionSort(int arr[], int l, int r) {
    if (l < r) {
        if ((r - l + 1) <= 25) {
            insertionSort(arr, l, r);
            return;
        }

        int m = (l + r) / 2;

        mergeInsertionSort(arr, l, m);
        mergeInsertionSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

// quick sort
int is_sorted(int values[], int length) {
    int i;
    // Return false if any adjacent pair is out of order.
    for (i=0; i<length-1; i++)
    if (values[i] > values[i+1])
    return 0;
    return 1;
}
// Pre-condition: low and high are valid indexes into values
// Post-condition: Returns the partition index such that all the values
// stored in vals from index low to until that index are
// less or equal to the value stored there and all the values
// after that index until index high are greater than that
//
int partition(int *vals, int low, int high) {
// Pick a random partition element and swap it into index low.
    int i = low + rand()%(high-low+1);
    swap(&vals[low], &vals[i]);
    int lowpos = low; //here is our pivot located.
    low++; //our starting point is after the pivot.
    // Run the partition so long as the low and high counters don't cross.
    while(low<=high) {
        // Move the low pointer until we find a value too large for this side.
        while(low<=high && vals[low]<=vals[lowpos]) low++;
        // Move the high pointer until we find a value too small for this side.
        while(high>=low && vals[high] > vals[lowpos]) high--;
        // Now that we've identified two values on the wrong side, swap them.
        if (low<high)
            swap(&vals[low], &vals[high]);
    }
    // Swap the pivot element element into its correct location.
    swap(&vals[lowpos], &vals[high]);
    return high; //return the partition point
}
// Pre-condition: s and f are value indexes into numbers.
// Post-condition: The values in numbers will be sorted in between indexes s
// and f.
void quickSort(int* numbers, int low, int high) {
    // Only have to sort if we are sorting more than one number
    if (low < high) {
        int split = partition(numbers,low,high);
        quickSort(numbers,low,split-1);
        quickSort(numbers,split+1,high);
    }
}

// function to get algo runtime in milli seconds
long timediff(clock_t t1, clock_t t2) {
    long elapsed;
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}

// function to create a list of random numbers with a given size
void create_list(int list[], int size) {
    for (int i=0; i<size; i++) {
        list[i] = rand() % size + 1;
    }
}

// function to copy a given list to use on the sorting algos
void copy_list(int dest[], int origin[], int size) {
    for (int i=0; i<size; i++) {
        dest[i] = origin[i];
    }
}

// function that will perform the run time analysis of all list sizes and all algos
void get_runtime(int sizes[], int sizes_count) {
    for (int i=0; i<sizes_count; i++) {
        int size = sizes[i];
        int list[size];
        int copy[size];
        clock_t start, end;
        long elapsed;
        
        create_list(list, size);
        
        copy_list(copy, list, size);
        start = clock();
        selectionSort(copy, size);
        end = clock();
        elapsed = timediff(start, end);
        printf("\nSorting %d values takes %ld milli seconds for Selection Sort\n", size, elapsed);
        
        copy_list(copy, list, size);
        start = clock();
        bubbleSort(copy, size);
        end = clock();
        elapsed = timediff(start, end);
        printf("\nSorting %d values takes %ld milli seconds for Bubble Sort\n", size, elapsed);
        
        copy_list(copy, list, size);
        start = clock();
        insertionSort(copy, 0, size-1);
        end = clock();
        elapsed = timediff(start, end);
        printf("\nSorting %d values takes %ld milli seconds for Insertion Sort\n", size, elapsed);
        
        copy_list(copy, list, size);
        start = clock();
        mergeSort(copy, 0, size-1);
        end = clock();
        elapsed = timediff(start, end);
        printf("\nSorting %d values takes %ld milli seconds for Merge Sort\n", size, elapsed);
        
        copy_list(copy, list, size);
        start = clock();
        mergeInsertionSort(copy, 0, size-1);
        end = clock();
        elapsed = timediff(start, end);
        printf("\nSorting %d values takes %ld milli seconds for Merge Insertion Sort\n", size, elapsed);
        
        copy_list(copy, list, size);
        start = clock();
        quickSort(copy, 0, size-1);
        end = clock();
        elapsed = timediff(start, end);
        printf("\nSorting %d values takes %ld milli seconds for Quick Sort\n", size, elapsed);
    }
}

// main runner
int main() {
    int sizes_count = 6;
    int sizes[] = {1000, 5000, 10000, 15000, 20000, 100000};

    get_runtime(sizes, sizes_count);

    return 0;
}