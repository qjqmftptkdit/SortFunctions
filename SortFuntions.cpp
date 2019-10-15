#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

enum ARRAYCASE {
	RANDOM,
	ASCENDING,
	DESCENDING,
};

// Base of every sort funtions
class SortFunction
{
public:
	virtual vector<int> startSorting(vector<int> targetArray) { return vector<int>(); };
};

// Useful functions when creating sort functions
class SortTools
{
public:
	static void swap(int& target1, int& target2); // Swap two targets
	static void testSortFunction(SortFunction* sortFunction, string sortName, ARRAYCASE caseNum); // Test sort funtion for all cases

	static vector<int> getArray(int length, ARRAYCASE caseNum); // Get array depended on ARRAYCASE
	static vector<int> getRandArray(int length); // Get array that is create by random
	static vector<int> getAscendingArray(int length); // Get array that is already ascended
	static vector<int> getDesceningArray(int length); // Get array that is already descended

	static void printTakedTime(SortFunction* sortFunction, int length, ARRAYCASE caseNum); // Measure time and print by microseconds
	static bool printTakedTimeByMean(SortFunction* sortFunction, int length, long long loop, ARRAYCASE caseNum); // Measure mean time and print by microseconds 
	static void printArray(vector<int> array); // Function to print array
};

// Sort by Selection sort algorithm
class SelectionSort : public SortFunction
{
public:
	vector<int> startSorting(vector<int> targetArray); // Sort given arrays and return result.
};

class InsertionSort : public SortFunction
{
public:
	vector<int> startSorting(vector<int> targetArray); // Sort given arrays and return result.
};

class ShellSort : public SortFunction
{
public:
	vector<int> startSorting(vector<int> targetArray); // Sort given arrays and return result.
};

class QuickSort : public SortFunction
{
public:
	vector<int> startSorting(vector<int> targetArray); // Sort given arrays and return result.

private:
	void quickSort(vector<int>& targetArray, int left, int right); // Sort arrays with Quick sort
	int partition(vector<int>& targetArray, int left, int right); // Divide conquer algorithm
};

class CycleMergeSort : public SortFunction
{
public :
	vector<int> startSorting(vector<int> targetArray); // Sort given arrays and return result

private :
	void cycleMergeSort(vector<int>& targetArray, int left, int right); // Sort arrays with Cycle merge sort
	void merge(vector<int>& targetArray, int left, int middle, int right); // Merge each sorted array
};

class AcyclicMergeSort : public SortFunction
{
public:
	vector<int> startSorting(vector<int> targetArray); // Sort given arrays and return result

private:
	void acyclicMergeSort(vector<int>& targetArray); // Sort arrays with Acyclic merge sort
	void merge(vector<int>& targetArray, int left, int middle, int right); // Merge each sorted array
};

class HeapSort : public SortFunction
{
public :
	vector<int> startSorting(vector<int> targetArray); // Sort given arrays and return result

private :
	void heapSort(vector<int>& targetArray); // Sort arrays with Heap sort
	void makeHeap(vector<int>& targetArray, int root, int lastNode); // Make heap constructor by using bottom-up way
};

// Swap two targets
void SortTools::swap(int& target1, int& target2)
{
	int temp = target1;
	target1 = target2;
	target2 = temp;
}

// Test sort funtion for all cases
void SortTools::testSortFunction(SortFunction* sortFunction, string sortName, ARRAYCASE caseNum)
{
	if (caseNum == RANDOM)
	{
		cout << "[*] Assignment Number 1 - " << sortName << endl;
		vector<int> randArray = getRandArray(10);
		cout << "[*] Before : "; printArray(randArray); cout << endl;

		vector<int> sortedArray = sortFunction->startSorting(randArray);
		cout << "[*] After : "; printArray(sortedArray); cout << endl << endl;
	}


	cout << "[*] Assignment Number 2 - " << sortName << endl;
	vector<int> lengthList({ 10, 100, 1000, 10000, 50000, 100000 });
	bool isOverload = false;
	for (int length : lengthList)
	{
		if (!isOverload)
		{
			if (length < 1000) printTakedTimeByMean(sortFunction, length, 10000, caseNum);
			else isOverload = printTakedTimeByMean(sortFunction, length, 10, caseNum);
		}
		else
		{
			cout << "[*] " << length << " length time measure (avg of 10 try) : 100,000+ Ms" << endl;
		}
	}
	cout << endl;
}

vector<int> SortTools::getArray(int length, ARRAYCASE caseNum)
{
	vector<int> resultArray;

	switch (caseNum)
	{
	case RANDOM:
		resultArray = getRandArray(length);
		break;
	case ASCENDING:
		resultArray = getAscendingArray(length);
		break;
	case DESCENDING:
		resultArray = getDesceningArray(length);
		break;
	}
	return resultArray;
}

// Get array that is create by random
vector<int> SortTools::getRandArray(int length)
{
	vector<int> randArray;
	for (int i = 0; i < length; i++)
		randArray.push_back(rand() % 10000);
	return randArray;
}

// Get array that is already ascended
vector<int> SortTools::getAscendingArray(int length)
{
	vector<int> resultArray;
	for (int i = 0; i < length; i++)
		resultArray.push_back(i);
	return resultArray;
}

// Get array that is already descended
vector<int> SortTools::getDesceningArray(int length)
{
	vector<int> resultArray;
	for (int i = length; i > 0; i--)
		resultArray.push_back(i);
	return resultArray;
}


// Measure time and print by microseconds (one by one test)
void SortTools::printTakedTime(SortFunction* sortFunction, int length, ARRAYCASE caseNum)
{
	vector<int> resultArray;

	auto start = high_resolution_clock::now();
	resultArray = getArray(length, caseNum);
	sortFunction->startSorting(resultArray);
	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);
	cout << "[*] " << length << " length time measure : " << duration.count() << "Ms" << endl;
}

// Measure mean time and print by microseconds 
bool SortTools::printTakedTimeByMean(SortFunction* sortFunction, int length, long long loop, ARRAYCASE caseNum)
{
	long long sumTime = 0;
	vector<int> resultArray;

	// Loop and get avg time
	for (int i = 0; i < loop; i++)
	{
		auto start = high_resolution_clock::now(); 
		resultArray = getArray(length, caseNum);
		sortFunction->startSorting(resultArray);
		auto stop = high_resolution_clock::now(); 
		auto duration = duration_cast<microseconds>(stop - start); 
		sumTime += duration.count();
		if (sumTime >= 1000000 && length >= 10000) break;
	}
	if (sumTime >= 1000000 && length >= 10000)
	{
		cout << "[*] " << length << " length time measure (avg of " << loop << " try) : 100,000+ Ms" << endl;
		return true;
	}
	else
	{
		long long avgTime = sumTime / loop;
		cout << "[*] " << length << " length time measure (avg of " << loop << " try) :" << avgTime << "Ms" << endl;
		return false;
	}
	

}

// Function to print array
void SortTools::printArray(vector<int> array)
{
	cout << "[";
	for (int i = 0; i < array.size(); i++)
	{
		cout << array[i];
		if (i < array.size() - 1) cout << ", ";
	}
	cout << "]";
}


// Sort given arrays and return result.
vector<int> SelectionSort::startSorting(vector<int> targetArray)
{
	int MinIndex;
	int len = targetArray.size();

	for (int i = 0; i < len - 1; i++)
	{
		MinIndex = i; // Assign start index that is assigned min valus's index after.
		for (int j = MinIndex + 1; j < len; j++)
			if (targetArray[MinIndex] > targetArray[j])
				MinIndex = j;
		if (MinIndex != i)
			SortTools::swap(targetArray[i], targetArray[MinIndex]);
	}

	return targetArray;
}

// Sort given arrays and return result.
vector<int> InsertionSort::startSorting(vector<int> targetArray)
{
	int len = targetArray.size();

	for (int sertTarget = 1; sertTarget < len; sertTarget++)
	{
		int sertTargetValue = targetArray[sertTarget];
		int compareTarget = sertTarget;

		while (targetArray[compareTarget - 1] > sertTargetValue)
		{
			targetArray[compareTarget] = targetArray[compareTarget - 1];
			compareTarget--;
			if (compareTarget == 0) break;
		}

		targetArray[compareTarget] = sertTargetValue;
	}

	return targetArray;
}

// Sort given arrays and return result.
vector<int> ShellSort::startSorting(vector<int> targetArray)
{
	int interval = 1;
	int len = targetArray.size();
	do interval = 3 * interval + 1; while (interval < len); // Set interval value

	do {
		interval /= 3;
		for (int sertTarget = interval; sertTarget < len; sertTarget++)
		{
			int sertTargetValue = targetArray[sertTarget];
			int compareTarget = sertTarget;

			while (targetArray[compareTarget - interval] > sertTargetValue)
			{
				targetArray[compareTarget] = targetArray[compareTarget - interval];
				compareTarget -= interval;
				if (compareTarget <= interval - 1) break;
			}

			targetArray[compareTarget] = sertTargetValue;

		}
	} while (interval > 1);

	return targetArray;
}

// Sort given arrays and return result.
vector<int> QuickSort::startSorting(vector<int> targetArray)
{
	int left = 0;
	int right = targetArray.size() - 1;
	quickSort(targetArray, left, right);
	return targetArray;
}

// sort arrays with Quick sort
void QuickSort::quickSort(vector<int>& targetArray, int left, int right)
{
	int middle;

	if (right > left) {
		middle = partition(targetArray, left, right + 1);
		quickSort(targetArray, left, middle - 1);
		quickSort(targetArray, middle + 1, right);
	}
}

// Divide conquer algorithm
int QuickSort::partition(vector<int>& targetArray, int left, int right)
{
	int partElem, partElemValue;
	partElem = left;
	partElemValue = targetArray[partElem];
	do {
		do { 
			left++; 
			if (left >= targetArray.size()) break;
		} while (targetArray[left] < partElemValue);
		do { 
			right--; 
			if (right <= -1) break;
		} while (targetArray[right] > partElemValue);

		if (left < right) SortTools::swap(targetArray[left], targetArray[right]);
		else break;
	} while (1);

	targetArray[partElem] = targetArray[right];
	targetArray[right] = partElemValue;
	return right;
}


vector<int> CycleMergeSort::startSorting(vector<int> targetArray)
{
	int left = 0;
	int right = targetArray.size() - 1;
	cycleMergeSort(targetArray, left, right);
	return targetArray;
}

// Sort arrays with Cycle merge sort
void CycleMergeSort::cycleMergeSort(vector<int>& targetArray, int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2 ;
		cycleMergeSort(targetArray, left, mid);
		cycleMergeSort(targetArray, mid + 1, right);
		merge(targetArray, left, mid, right);
	}
}

// Merge each sorted array
void CycleMergeSort::merge(vector<int>& targetArray, int left, int middle, int right)
{
	vector<int> resultArray(targetArray.size());
	int leftPtr, rightPtr, bufPtr;

	leftPtr = left; rightPtr = middle + 1; bufPtr = left;

	while (leftPtr <= middle && rightPtr <= right)
		if (targetArray[leftPtr] < targetArray[rightPtr])
			resultArray[bufPtr++] = targetArray[leftPtr++];
		else
			resultArray[bufPtr++] = targetArray[rightPtr++];

	if (leftPtr > middle)
		for (int i = rightPtr; i <= right; i++)
			resultArray[bufPtr++] = targetArray[i];
	else
		for (int i = leftPtr; i <= middle; i++)
			resultArray[bufPtr++] = targetArray[i];

	for (int i = left; i <= right; i++)
		targetArray[i] = resultArray[i];
}

vector<int> AcyclicMergeSort::startSorting(vector<int> targetArray)
{
	acyclicMergeSort(targetArray);
	return targetArray;
}

// Sort arrays with Acyclic merge sort
void AcyclicMergeSort::acyclicMergeSort(vector<int>& targetArray)
{
	int len = targetArray.size();
	int low, mid, high;

	for (int i = 1; i < len; i *= 2)
	{
		low = 0;
		while (low < len)
		{
			high = low + 2 * i - 1;
			if (high >= len) high = len-1;

			mid = low + i - 1;
			if (mid < len)
				merge(targetArray, low, mid, high);

			low = high + 1;
		}
	}
}

// Merge each sorted array
void AcyclicMergeSort::merge(vector<int>& targetArray, int left, int middle, int right)
{
	vector<int> resultArray(targetArray.size());
	int leftPtr, rightPtr, bufPtr;

	leftPtr = left; rightPtr = middle + 1; bufPtr = left;

	while (leftPtr <= middle && rightPtr <= right)
		if (targetArray[leftPtr] < targetArray[rightPtr])
			resultArray[bufPtr++] = targetArray[leftPtr++];
		else
			resultArray[bufPtr++] = targetArray[rightPtr++];

	if (leftPtr > middle)
		for (int i = rightPtr; i <= right; i++)
			resultArray[bufPtr++] = targetArray[i];
	else
		for (int i = leftPtr; i <= middle; i++)
			resultArray[bufPtr++] = targetArray[i];

	for (int i = left; i <= right; i++)
		targetArray[i] = resultArray[i];
}

vector<int> HeapSort::startSorting(vector<int> targetArray)
{
	heapSort(targetArray);
	return targetArray;
}

// Sort arrays with Heap sort
void HeapSort::heapSort(vector<int>& targetArray)
{
	int len = targetArray.size();
	for (int i = len / 2; i > 0; i--)
		makeHeap(targetArray, i - 1, len - 1);
	
	for (int i = len - 1; i > 0; i--)
	{
		SortTools::swap(targetArray[0], targetArray[i]);
		makeHeap(targetArray, 0, i - 1);
	}
}

// Make heap constructor by using bottom-up way
void HeapSort::makeHeap(vector<int>& targetArray, int root, int lastNode)
{
	int parent, parentValue, leftSon, rightSon, son;
	parent = root;
	parentValue = targetArray[parent];
	leftSon = 2 * parent + 1;
	rightSon = leftSon + 1;

	while (leftSon <= lastNode)
	{
		if (rightSon <= lastNode && targetArray[leftSon] < targetArray[rightSon])
			son = rightSon;
		else
			son = leftSon;

		if (parentValue < targetArray[son])
		{
			targetArray[parent] = targetArray[son];
			parent = son;
			leftSon = parent * 2 + 1;
			rightSon = leftSon + 1;
		}
		else break;
	}
	targetArray[parent] = parentValue;
}

int main()
{
	srand((int)time(0));
	
	cout << "[*] SELECT SORT MEASURE" << endl;
	SortTools::testSortFunction(new SelectionSort(), "SelectionSort (Avg Case) ", RANDOM);
	SortTools::testSortFunction(new SelectionSort(), "SelectionSort (Best Case) ", ASCENDING);
	SortTools::testSortFunction(new SelectionSort(), "SelectionSort (Worst Case) ", DESCENDING);

	cout << "[*] INSERT SORT MEASURE" << endl;
	SortTools::testSortFunction(new InsertionSort(), "InsertSort (Avg Case) ", RANDOM);
	SortTools::testSortFunction(new InsertionSort(), "InsertSort (Best Case) ", ASCENDING);
	SortTools::testSortFunction(new InsertionSort(), "InsertSort (Worst Case) ", DESCENDING);

	cout << "[*] SHELL SORT MEASURE" << endl;
	SortTools::testSortFunction(new ShellSort(), "ShellSort (Avg Case) ", RANDOM);
	SortTools::testSortFunction(new ShellSort(), "ShellSort (Best Case) ", ASCENDING);
	SortTools::testSortFunction(new ShellSort(), "ShellSort (Worst Case) ", DESCENDING);

	cout << "[*] QUICK SORT MEASURE" << endl;
	SortTools::testSortFunction(new QuickSort(), "QuickSort (Avg Case) ", RANDOM);
	
	cout << "[*] CYCLE MERGE SORT MEASURE" << endl;
	SortTools::testSortFunction(new CycleMergeSort(), "CycleMergeSort (Avg Case) ", RANDOM);

	cout << "[*] ACYCLIC MERGE SORT MEASURE" << endl;
	SortTools::testSortFunction(new AcyclicMergeSort(), "AcyclicMergeSort (Avg Case) ", RANDOM);

	cout << "[*] HEAP SORT MEASURE" << endl;
	SortTools::testSortFunction(new HeapSort(), "HeapSort (Avg Case) ", RANDOM);
	SortTools::testSortFunction(new HeapSort(), "HeapSort (Best Case) ", DESCENDING);
	SortTools::testSortFunction(new HeapSort(), "HeapSort (WorstCase) ", ASCENDING);
	
	
}