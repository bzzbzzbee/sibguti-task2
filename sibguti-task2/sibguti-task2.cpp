#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int temp_m = 0, temp_c = 0;
int batch[4] = { 10, 50, 100, 200 };

void swap(int* xp, int* yp) {
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

int sereiesNum(const vector<int> arr) {
    int num = 1;
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] != arr[i - 1]) {
            num++;
        }
    }
    return num;
}

void printArray(const vector<int> arr) {
    unsigned int i;
    for (i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void initArray(unsigned int maxSize, vector<int>& arr) {

    for (size_t i = 0; i < maxSize; i++) {
        int num = rand() % 100 + 1;
        arr.push_back(num);
    }
}

bool ascending(int i, int j) {
    return (i < j);
}

bool descending(int i, int j) {
    return (i > j);
}

pair<int,int> shellSort(vector<int> arr) {
    int size = arr.size(), m = 0, c = 0;
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i += 1) {

            int temp = arr[i];

            int j;

            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
                c++;
                m++;
            }
            arr[j] = temp;
            m++;
        }
    }

    return make_pair(m, c);
}

void heapify(vector<int> arr, int size, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    temp_c++;
    if (l < size && arr[l] > arr[largest]) {
        largest = l;
    }
    temp_c++;
    if (r < size && arr[r] > arr[largest]) {
        largest = r;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        temp_m++;
        heapify(arr, size, largest);
    }
}

void heapSort(vector<int> arr, int size) {

    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(arr, size, i);
    }

    for (int i = size - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        temp_m++;
        heapify(arr, i, 0);
    }
}

pair<int, int> heapSort(vector<int> arr) {
    temp_m = 0;
    temp_c = 0;

    heapSort(arr, arr.size());

    return make_pair(temp_m, temp_c);
}

int partition(vector<int> arr, int low, int high) {
    int pivot = arr[low];
    int i = low - 1, j = high + 1;

    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
            temp_c++;
        } while (arr[j] > pivot);

        if (i >= j)
            return j;

        swap(arr[i], arr[j]);
        temp_m++;
    }
}

void quickSort(vector<int> arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi);
        quickSort(arr, pi + 1, high);
    }
}

pair<int, int> quickSort(vector<int> arr) {
    temp_m = 0;
    temp_c = 0;

    quickSort(arr, 0, arr.size() - 1);

    return make_pair(temp_m, temp_c);
}

pair<int, int> examineShellSort(int batchSize, vector<int> arr, string arrayState) {
    cout << arrayState << " array, size = " << batchSize << endl << "Sorting with Shell sort" << endl << endl;
    auto pair = shellSort(arr);
    cout << "M = " << pair.first << ", C = " << pair.second << endl << endl;

    int sum = accumulate(arr.begin(), arr.end(), 0);
    int ser = sereiesNum(arr);

    return  make_pair(sum, ser);
}

pair<int, int> examineHeapSort(int batchSize, vector<int> arr, string arrayState) {
    cout << arrayState << " array, size = " << batchSize << endl << "Sorting with Heap sort" << endl << endl;
    auto pair = heapSort(arr);
    cout << "M = " << pair.first << ", C = " << pair.second << endl << endl;

    int sum = accumulate(arr.begin(), arr.end(), 0);
    int ser = sereiesNum(arr);

    return  make_pair(sum, ser);
}

pair<int, int> examineQuickSort(int batchSize, vector<int> arr, string arrayState) {
    cout << arrayState << " array, size = " << batchSize << endl << "Sorting with Quick sort" << endl << endl;
    auto pair = quickSort(arr);
    cout << "M = " << pair.first << ", C = " << pair.second << endl << endl;

    int sum = accumulate(arr.begin(), arr.end(), 0);
    int ser = sereiesNum(arr);

    return  make_pair(sum, ser);
}

void examineSortRandom() {
    string state = "Random";
    for (size_t i = 0; i < 4; i++) {
        vector<int> arr = vector<int>();
        initArray(batch[i], arr);
        vector<int> arr1 = vector<int>(arr);
        vector<int> arr2 = vector<int>(arr);

        auto shellRes = examineShellSort(batch[i], arr, state);
        auto heapRes = examineHeapSort(batch[i], arr1, state);
        auto quickRes = examineQuickSort(batch[i], arr2, state);

        if (shellRes.first == heapRes.first && heapRes.first == quickRes.first) {
            cout << "Sum is matching" << endl;
        }
        else {
            cout << "Sum is not matching" << endl;
        }

        if (shellRes.second == heapRes.second && heapRes.second == quickRes.second) {
            cout << "Series is matching" << endl;
        }
        else {
            cout << "Series is not matching" << endl;
        }
        cout << endl;
    }
    cout << "End of Random arrays" << endl << endl;
}

void examineSortAscending() {
    string state = "Ascending";
    for (size_t i = 0; i < 4; i++) {
        vector<int> arr = vector<int>();
        initArray(batch[i], arr);
        sort(arr.begin(), arr.end(), ascending);
        vector<int> arr1 = vector<int>(arr);
        vector<int> arr2 = vector<int>(arr);

        auto shellRes = examineShellSort(batch[i], arr, state);
        auto heapRes = examineHeapSort(batch[i], arr1, state);
        auto quickRes = examineQuickSort(batch[i], arr2, state);

        if (shellRes.first == heapRes.first && heapRes.first == quickRes.first) {
            cout << "Sum is matching" << endl;
        }
        else {
            cout << "Sum is not matching" << endl;
        }

        if (shellRes.second == heapRes.second && heapRes.second == quickRes.second) {
            cout << "Series is matching" << endl;
        }
        else {
            cout << "Series is not matching" << endl;
        }
        cout << endl;
    }
    cout << "End of Ascending arrays" << endl << endl;
}

int main() {
    srand(time(NULL));
    examineSortRandom();
    examineSortAscending();
}