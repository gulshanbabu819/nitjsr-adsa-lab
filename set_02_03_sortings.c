#include<stdio.h>
#include<stdlib.h>
#include <math.h>

void bubbleSort(int arr[],int n){
    int i,j;
    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}

void insertionSort(int arr[],int n){
    int i, key, j;
    for(i=1;i<n;i++){
        key=arr[i];
        j=i-1;
        while(j>=0 && arr[j]>key){
            arr[j+1]=arr[j];
            j=j-1;
        }
        arr[j+1]=key;
    }
}

void selectionSort(int arr[], int n) {
    int i, j, minIndex, temp;

    for (i = 0; i < n - 1; i++) {
        minIndex = i;

        // Find the index of minimum element in unsorted part
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // Swap arr[i] and arr[minIndex]
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

void shellSort(int arr[], int n){
    int gap, i, j, temp;
    for(gap = n/2; gap > 0; gap /= 2){
        for(i = gap; i < n; i++){
            temp = arr[i];
            for(j = i; j >= gap && arr[j - gap] > temp; j -= gap){
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // choosing last element as pivot
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;   // size of left subarray
    int n2 = right - mid;      // size of right subarray

    int L[n1], R[n2];          // temp arrays

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr[l..r]
    int i = 0, j = 0, k = left;

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

    // Copy remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

void heapify(int arr[], int n, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if(left < n && arr[left] > arr[largest]){
        largest = left;
    }
    if(right < n && arr[right] > arr[largest]){
        largest = right;
    }
    if(largest != i){
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n){
    int i;
    for(i = n / 2 - 1; i >= 0; i--){
        heapify(arr, n, i);
    }
    for(i = n - 1; i >= 0; i--){
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }

}

void radixSort(int arr[], int n){
    int max = arr[0];
    for(int i = 1; i < n; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    for(int exp = 1; max/exp > 0; exp *= 10){
        int output[n];
        int count[10] = {0};
        for(int i = 0; i < n; i++){
            count[(arr[i]/exp)%10]++;
        }
        for(int i = 1; i < 10; i++){
            count[i] += count[i - 1];
        }
        for(int i = n - 1; i >= 0; i--){
            output[count[(arr[i]/exp)%10] - 1] = arr[i];
            count[(arr[i]/exp)%10]--;
        }
        for(int i = 0; i < n; i++){
            arr[i] = output[i];
        }
    }

}

void countingSort(int arr[], int n){
    int max = arr[0];
    for(int i = 1; i < n; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    int count[max + 1];
    for(int i = 0; i <= max; i++){
        count[i] = 0;
    }
    for(int i = 0; i < n; i++){
        count[arr[i]]++;
    }
    for(int i = 1; i <= max; i++){
        count[i] += count[i - 1];
    }
    int output[n];
    for(int i = n - 1; i >= 0; i--){
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    for(int i = 0; i < n; i++){
        arr[i] = output[i];
    }

}

void bucketSort(int arr[], int n){
    int max = arr[0];
    for(int i = 1; i < n; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    int bucket[max + 1];
    for(int i = 0; i <= max; i++){
        bucket[i] = 0;
    }
    for(int i = 0; i < n; i++){
        bucket[arr[i]]++;
    }
    int index = 0;
    for(int i = 0; i <= max; i++){
        while(bucket[i] > 0){
            arr[index++] = i;
            bucket[i]--;
        }
    }

}

void radixExchangeSort(int arr[], int left, int right, int bit) {
    if (left >= right || bit < 0) return;

    int i = left, j = right;

    // Partition based on the current bit
    while (i <= j) {
        while (i <= j && ((arr[i] >> bit) & 1) == 0) i++;
        while (i <= j && ((arr[j] >> bit) & 1) == 1) j--;
        if (i < j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Recursively sort both halves
    radixExchangeSort(arr, left, j, bit - 1);
    radixExchangeSort(arr, j + 1, right, bit - 1);
}

void addressCalculationSort(int arr[], int n) {
    int min = arr[0], max = arr[0];
    
    // Find min and max
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    
    // Create buckets
    int *bucket[n];
    int count[n];
    for (int i = 0; i < n; i++) {
        bucket[i] = (int*)malloc(n * sizeof(int));
        count[i] = 0;
    }
    
    // Distribute elements into buckets
    for (int i = 0; i < n; i++) {
        int index = (arr[i] - min) * n / (max - min + 1);
        bucket[index][count[index]++] = arr[i];
    }
    
    // Sort individual buckets (insertion sort)
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < count[i]; j++) {
            int key = bucket[i][j];
            int k = j - 1;
            while (k >= 0 && bucket[i][k] > key) {
                bucket[i][k + 1] = bucket[i][k];
                k--;
            }
            bucket[i][k + 1] = key;
        }
    }
    
    // Collect sorted elements back
    int idx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < count[i]; j++) {
            arr[idx++] = bucket[i][j];
        }
        free(bucket[i]);
    }
}

int printArray(int arr[],int size){
    int i;
    for(i=0;i<size;i++)
        printf("%d ",arr[i]);
    printf("\n");
}



int main(){
    // int arr[]={64,32,25,22,17};
    // int n=sizeof(arr)/sizeof(arr[0]);
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("original array: \n");
    printArray(arr,n);
    // bubbleSort(arr,n);
    // insertionSort(arr,n);
    // selectionSort(arr,n);
    // quickSort(arr,0,n-1);
    // mergeSort(arr,0,n-1);
    // shellSort(arr,n);
    // heapSort(arr,n);
    // radixSort(arr,n);
    // countingSort(arr,n);
    // bucketSort(arr,n);
    // int maxVal = arr[0];
    // int maxBits = (int)log2(maxVal) ;

    // radixExchangeSort(arr,0,n-1,maxBits);
    addressCalculationSort(arr,n);
    printf("sorted array: \n");
    printArray(arr,n);
    return 0;
}