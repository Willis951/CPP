//Email : cerro005@cougars.csusm.edu
// Name: William Cerros
// Student ID: Cerro005
//Email : cerro005@cougars.csusm.edu

#include <iostream>

using namespace std;

//const capacity for dynamically created array in merge function
const int capacity = 10;

void merge(int *arr, int low, int mid, int high)
{
	int tempArr[capacity];
	int i = low;
	int j = mid + 1;
	int k = 0;
	

	//Comparing left sub array with right sub array
	//Pushing the lesser of the two onto tempArr
	while (i <= mid && j <= high)
	{
		if (arr[i] <= arr[j])
			tempArr[k++] = arr[i++];

		else
			tempArr[k++] = arr[j++];
	}

	//Copying remaining contents of left sub array to tempArr
	while (i <= mid)
		tempArr[k++] = arr[i++];


	//Copying remaining contents of right sub array to tempArr
	while (j <= high)
		tempArr[k++] = arr[j++];

	k--;

	//tempArr is now sorted, so we copy its contents back to arr
	while (k >= 0)
	{
		arr[k + low] = tempArr[k];
		k--;
	}

}

/* We take an array and recursively perform merge sort until contents can be merged back */
void mergeSort(int *arr, int low, int high)
{
	int mid;

	if (low < high)
	{
		mid = (low + high) / 2;
		mergeSort(arr, low, mid);
		mergeSort(arr, mid + 1, high);
		merge(arr, low, mid, high);
	}
}

void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void printArray(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}

	cout << "\n\n";
}


void insertionSort(int arr[], int size)
{
	/* i is our iterator, we begin at 1 and work our way through the array. i signifies the sorted array. Everything before i should be sorted as the loop runs */
	/* temp holds the value of current element we are sorting */
	int i, temp, tempIndex;
	for (i = 1; i < size; i++)
	{
		temp = arr[i];
		tempIndex = i;

		/* While loop will iterate until either tempIndex reaches 0, or until the element before it is no longer greater than temp*/
		/* The second condition is valid because we know everything before tempIndex is already in sorted order, hence insertion sort */
		while (tempIndex > 0 && arr[tempIndex - 1] > temp)
		{
			arr[tempIndex] = arr[tempIndex - 1];
			tempIndex--;
		}

		arr[tempIndex] = temp;
	}
}

void bubbleSort(int arr[], int size)
{
	bool isSorted = false;

	/* After each pass the largest elements in the array are at the end of the array */
	/* So you don't need to iterate through the entire array for each pass */
	int unsortedPartition = size-1;

	/* Set isSorted to true at the beginning of each while loop, if run is completed without swapping then the array is sorted and while loop concludes*/
	while (!isSorted)
	{
		isSorted = true;
		for (int i = 0; i < unsortedPartition; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(&arr[i], &arr[i + 1]);
				isSorted = false;
			}
		}
		unsortedPartition--; //the unsorted paritition is decremented by one after each pass
	}
}


void selectionSort(int arr[], int n)
{
	int i, j, currentMin;

	/* i will be the sorted parition */
	for (i = 0; i < n-1; i++)
	{
		/* j is the unsorted parition */
		currentMin = i;

		for (j = i + 1; j < n; j++)
		{
			/* If the value of index j is less than value of index then swap */
			if (arr[j] < arr[currentMin])
			{
				currentMin = j;
			}
			swap(&arr[currentMin], &arr[i]);
		}
	}
}


/* partition function will return an index corresponding to the 
   pivot position. we begin by choosing pivot position as our high index*/
int partition(int arr[], int low, int high)
{
	int pivot = arr[high];
	int i = low - 1;
	int j = low;


	//We take the elements smaller than pivot and place them to the left
	//We take the elements greater than pivot and place them to the right
	for (j = low; j <= high - 1; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			swap(arr[i], arr[j]);
		}
	}

	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pivotPosition = partition(arr, low, high);
		quickSort(arr, low, pivotPosition - 1);
		quickSort(arr, pivotPosition + 1, high);
	}
}


/* We apply heapify to a root node at position i, */
/* arrSize is thte size of array, arr is the array we are sorting */
void heapify(int arr[], int arrSize, int i)
{
	/* Initialzing ourt root node along with its left and right children*/
	int rootNode = i;
	int leftChild = 2 * i + 1;
	int rightChild = 2 * i + 2; 

	/* Here we are checking if the leftChild is larger than the rootNode */
	/* If so we make the left child our root node */
	if (leftChild < arrSize && arr[leftChild] > arr[rootNode])
		rootNode = leftChild;

	/* Here we perform the same function as above however we check the right child */
	if (rightChild < arrSize && arr[rightChild] > arr[rootNode])
		rootNode = rightChild;

	/* If root node is not equal to i, we swap values */
	if (rootNode != i)
	{
		swap(arr[i], arr[rootNode]);

		/* Here we recursively apply heapify to our subtree */
		heapify(arr, arrSize, rootNode);
	}
}

/* HeapSort will take an array and sort it according to heap standards. */
/* Each root node i has left child at 2(i) +1  and right child at 2(i) +2*/
void heapSort(int arr[], int arrSize)
{
	/* This for loop will rearrange array into a heap. The last internal node is
	   arrSize/2 - 1. */
	for (int i = arrSize / 2 - 1; i >= 0; i--)
		heapify(arr, arrSize, i);

	/* For loop will then remove elements from array one at a time and place them
	   in min heap order */
	for (int i = arrSize - 1; i >= 0; i--)
	{
		/* We move the current index to the end, and then create a heap out of the subsequent indeces */
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}

int main()
{
	int arr[]{ 10, 33, 22, 11, 9};
	int arr2[]{ 3, 1, 2, 8, 4};
	int arr3[]{ 5, 1, 3, 6, 2};
	int arr4[]{ 9, 5, 10, 4, 6, 1, 3, 9};
	int arr5[]{ 3, 1, 9, 5, 3, 20, 2 };
	int arr6[]{ 10, 5, 3, 9, 4, 22, 1 };

	int arrSize = sizeof(arr) / sizeof(arr[0]);
	int arr2Size = sizeof(arr2) / sizeof(arr2[0]);
	int arr3Size = sizeof(arr3) / sizeof(arr3[0]);
	int arr4Size = sizeof(arr4) / sizeof(arr4[0]);
	int arr5Size = sizeof(arr5) / sizeof(arr5[0]);
	int arr6Size = sizeof(arr6) / sizeof(arr6[0]);
	
	cout << "Unsorted Array: ";
	printArray(arr, arrSize);
	cout << "Selection Sort Applied: ";
	selectionSort(arr, arrSize);
	printArray(arr, arrSize);

	cout << "Unsorted Array: ";
	printArray(arr2, arrSize);
	cout << "Bubble Sort Applied: ";
	bubbleSort(arr2, arr2Size);
	printArray(arr2, arr2Size);


	cout << "Unsorted Array: ";
	printArray(arr3, arr3Size);
	cout << "Insertion Sort Applied: ";
	insertionSort(arr3, arr3Size);
	printArray(arr3, arr3Size);

	cout << "Unsorted Array: ";
	printArray(arr4, arr4Size);
	cout << "Merge Sort Applied: ";
	mergeSort(arr4, 0, arr4Size-1);
	printArray(arr4, arr4Size);


	cout << "Unsorted Array: ";
	printArray(arr5, arr5Size);
	cout << "Quick Sort Applied: ";
	quickSort(arr5, 0, arr5Size-1);
	printArray(arr5, arr5Size);


	cout << "Unsorted Array: ";
	printArray(arr6, arr6Size);
	cout << "Heap Sort Applied: ";
	selectionSort(arr6, arr6Size);
	printArray(arr6, arr6Size);

	return(0);
}
