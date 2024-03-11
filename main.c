#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int arr[], int n, int *comparisons, int *swaps) {
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            (*comparisons)++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            (*swaps)++;
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

void bubbleSort(int arr[], int n, int *comparisons, int *swaps) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            (*comparisons)++;
            if (arr[j] > arr[j + 1]) {
                (*swaps)++;
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertionSort(int arr[], int n, int *comparisons, int *swaps) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            (*comparisons)++;
            (*swaps)++;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int l, int m, int r, int *comparisons, int *swaps) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        (*comparisons)++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        (*swaps)++;
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r, int *comparisons, int *swaps) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, comparisons, swaps);
        mergeSort(arr, m + 1, r, comparisons, swaps);
        merge(arr, l, m, r, comparisons, swaps);
    }
}

int partition(int arr[], int low, int high, int *comparisons, int *swaps) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        (*comparisons)++;
        if (arr[j] < pivot) {
            i++;
            (*swaps)++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    (*swaps)++;
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high, int *comparisons, int *swaps) {
    if (low < high) {
        int pi = partition(arr, low, high, comparisons, swaps);
        quickSort(arr, low, pi - 1, comparisons, swaps);
        quickSort(arr, pi + 1, high, comparisons, swaps);
    }
}

void heapify(int arr[], int n, int i, int *comparisons, int *swaps) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }
    (*comparisons)++;
    if (largest != i) {
        (*swaps)++;
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest, comparisons, swaps);
    }
}

void heapSort(int arr[], int n, int *comparisons, int *swaps) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, comparisons, swaps);
    }
    for (int i = n - 1; i >= 0; i--) {
        (*swaps)++;
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0, comparisons, swaps);
    }
}
void countingSort(int arr[], int n, int *comparisons, int *swaps) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        (*comparisons)++;
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    int *count = (int *) calloc(max + 1, sizeof(int));
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }
    int index = 0;
    for (int i = 0; i <= max; i++) {
        for (int j = 0; j < count[i]; j++) {
            (*swaps)++;
            arr[index++] = i;
        }
    }
    free(count);
}

void radixSort(int arr[], int n, int *comparisons, int *swaps) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        (*comparisons)++;
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    for (int exp = 1; max / exp > 0; exp *= 10) {
        int *output = (int *) malloc(n * sizeof(int));
        int count[10] = {0};
        for (int i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            (*swaps)++;
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
        for (int i = 0; i < n; i++) {
            (*swaps)++;
            arr[i] = output[i];
        }
        free(output);
    }
}

int main() {
    FILE *fp;
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    int rows = 0, cols = 0;
    char c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            rows++;
        }
        if (rows == 0 && c == ' ') {
            cols++;
        }
    }
    rewind(fp);
    int **arr = (int **) malloc(rows * sizeof(int *));
    int **arr_copy = (int **) malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        arr[i] = (int *) malloc(cols * sizeof(int));
        arr_copy[i] = (int *) malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            fscanf(fp, "%d", &arr[i][j]);
            arr_copy[i][j] = arr[i][j];
        }
    }
    fclose(fp);
    double total_time[8] = {0};
    int total_comparisons[8] = {0};
    int total_swaps[8] = {0};
    for (int i = 0; i < rows; i++) {
        int *row = arr[i];
        int n = cols;
        int comparisons = 0, swaps = 0;
        clock_t start, end;
        // selection sort
        start = clock();
        selectionSort(row, n, &comparisons, &swaps);
        end = clock();
        total_time[0] += ((double) (end - start)) / CLOCKS_PER_SEC;
        total_comparisons[0] += comparisons;
        total_swaps[0] += swaps;
        // bubble sort
        comparisons = 0, swaps = 0;
        int *row_copy = (int *) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            row_copy[j] = arr_copy[i][j];
        }
        start = clock();
        bubbleSort(row_copy, n, &comparisons, &swaps);
        end = clock();
        total_time[1] += ((double) (end - start)) / CLOCKS_PER_SEC;
        total_comparisons[1] += comparisons;
        total_swaps[1] += swaps;
        free(row_copy);
        // insertion sort
        comparisons = 0, swaps = 0;
        row_copy = (int *) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            row_copy[j] = arr_copy[i][j];
        }
        start = clock();
        insertionSort(row_copy, n, &comparisons, &swaps);
        end = clock();
        total_time[2] += ((double) (end - start)) / CLOCKS_PER_SEC;
        total_comparisons[2] += comparisons;
        total_swaps[2] += swaps;
        free(row_copy);
        // merge sort
        comparisons = 0, swaps = 0;
        row_copy = (int *) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            row_copy[j] = arr_copy[i][j];
        }
        start = clock();
        mergeSort(row, 0, n - 1, &comparisons, &swaps);
        end = clock();
        total_time[3] += ((double) (end - start)) / CLOCKS_PER_SEC;
        total_comparisons[3] += comparisons;
        total_swaps[3] += swaps;
        free(row_copy);
        // quick sort
        comparisons = 0, swaps = 0;
        row_copy = (int *) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            row_copy[j] = arr_copy[i][j];
        }
        start = clock();
        quickSort(row_copy, 0, n - 1, &comparisons, &swaps);
        end = clock();
        total_time[4] += ((double) (end - start)) / CLOCKS_PER_SEC;
        total_comparisons[4] += comparisons;
        total_swaps[4] += swaps;
        free(row_copy);
        // heap sort
        comparisons = 0, swaps = 0;
        row_copy = (int *) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            row_copy[j] = arr_copy[i][j];
        }
        start = clock();
        heapSort(row_copy, n, &comparisons, &swaps);
        end = clock();
        total_time[5] += ((double) (end - start)) / CLOCKS_PER_SEC;
        total_comparisons[5] += comparisons;
        total_swaps[5] += swaps;
        free(row_copy);
        // counting sort
        comparisons = 0, swaps = 0;
        row_copy = (int *) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            row_copy[j] = arr_copy[i][j];
        }
        start = clock();
        countingSort(row_copy, n, &comparisons, &swaps);
        end = clock();
        total_time[6] += ((double) (end - start)) / CLOCKS_PER_SEC;
        total_comparisons[6] += comparisons;
        total_swaps[6] += swaps;
        free(row_copy);
        // radix sort
        comparisons = 0, swaps = 0;
        row_copy = (int *) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            row_copy[j] = arr_copy[i][j];
        }
        start = clock();
        radixSort(row_copy, n, &comparisons, &swaps);
        end = clock();
        total_time[7] += ((double) (end - start)) / CLOCKS_PER_SEC;
        total_comparisons[7] += comparisons;
        total_swaps[7] += swaps;
        free(row_copy);
    }
    printf("Selection sort: total time %f seconds, total comparisons %d, total swaps %d\n", total_time[0], total_comparisons[0], total_swaps[0]);
    printf("Bubble sort: total time %f seconds, total comparisons %d, total swaps %d\n", total_time[1], total_comparisons[1], total_swaps[1]);
    printf("Insertion sort: total time %f seconds, total comparisons %d, total swaps %d\n", total_time[2], total_comparisons[2], total_swaps[2]);
    printf("Merge sort: total time %f seconds, total comparisons %d, total swaps %d\n", total_time[3], total_comparisons[3], total_swaps[3]);
    printf("Quick sort: total time %f seconds, total comparisons %d, total swaps %d\n", total_time[4], total_comparisons[4], total_swaps[4]);
    printf("Heap sort: total time %f seconds, total comparisons %d, total swaps %d\n", total_time[5], total_comparisons[5], total_swaps[5]);
    printf("Counting sort: total time %f seconds, total comparisons %d, total swaps %d\n", total_time[6], total_comparisons[6], total_swaps[6]);
    printf("Radix sort: total time %f seconds, total comparisons %d, total swaps %d\n", total_time[7], total_comparisons[7], total_swaps[7]);
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
        free(arr_copy[i]);
    }
    free(arr);
    free(arr_copy);
    return 0;
}
