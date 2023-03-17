// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include <limits>
#include <iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int i, j;
    int key;
    for (i = 1; i < data.size(); i++){
        if (data[i] < data[i - 1]){
            key = data[i];
            j = i;
            //move array[j - 1] one array slot down
            //until the element in the upper list at j - 1 is less than that at i
            while(j > 0 && data[j - 1] > key){
                data[j] = data[j - 1];
                j--;
            }
            data[j] = key;
        }
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    int pivotLocation;
    if (low < high){
        pivotLocation = Partition(data, low, high);
        QuickSortSubVector(data, low, pivotLocation - 1);
        QuickSortSubVector(data, pivotLocation + 1, high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    //pivot: the last element in array 
    int pivot = data[high];
    //smallIndex: record the ending position of smaller array
    int smallIndex = low - 1;
    for (int j = low; j < high; j++) {
        if (data[j] < pivot) {
            smallIndex++;
            swap(data[smallIndex], data[j]);
        }
    }
    smallIndex++;
    swap(data[smallIndex], data[high]);
    return smallIndex;
}

void SortTool::swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    int mid1, mid2;
    if (low < high){
        mid1 = (low + high) / 2;
        mid2 = mid1 + 1;
        MergeSortSubVector(data, low, mid1);
        MergeSortSubVector(data, mid2, high);
        Merge(data, low, mid1, mid2, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int leftArrLength = middle1 - low + 1;
    int rightArrLength = high - middle2 + 1;
    //create two temporary subarrays
    vector<int> leftArr(leftArrLength + 1);
    vector<int> rightArr(rightArrLength + 1);
    //copy elements into two subarrays
    for (int i = 0; i < leftArrLength; i++){
        leftArr[i] = data[low + i];
    }
    for (int i = 0; i < rightArrLength; i++){
        rightArr[i] = data[middle2 + i];
    }
    //insert a large value in the end of two subarrays
    leftArr[leftArrLength] = numeric_limits<int>::max();
    rightArr[rightArrLength] = numeric_limits<int>::max();
    int leftIndex = 0;
    int rightIndex = 0;
    for (int i = low; i <= high; i++){
        if (leftArr[leftIndex] <= rightArr[rightIndex]){
            data[i] = leftArr[leftIndex];
            leftIndex++;
        }
        else{
            data[i] = rightArr[rightIndex];
            rightIndex++;
        }
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data){
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--){
        swap(data[0], data[i]);
        heapSize--;
        MaxHeapify(data, 0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root){
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int left = 2 * root + 1; //left child of the root
    int right = 2 * root + 2; //right child of the root
    int largestIndex;
    int maxIndex = heapSize - 1; //largest index of data
    //Find the largest element in the subtree
    if (left <= maxIndex && data[left] > data[root]){
        largestIndex = left;
    }
    else{
        largestIndex = root;
    }
    if (right <= maxIndex && data[right] > data[largestIndex]){
        largestIndex = right;
    }
    //If the tree is not a max heap
    if (largestIndex == left || largestIndex == right){
        swap(data[largestIndex], data[root]);
        MaxHeapify(data, largestIndex);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    int maxIndex = heapSize - 1;
    //node with child start from (maxIndex - 1) / 2
    for (int i = (maxIndex - 1) / 2; i >= 0; i--){
        MaxHeapify(data, i);
    }
}
