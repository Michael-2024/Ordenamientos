#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>
#include <algorithm>

using namespace std;

vector<int> arr;

// Prototipos de funciones
void bubbleSort(vector<int>& arr);
void selectionSort(vector<int>& arr);
void insertionSort(vector<int>& arr);
void mergeSort(vector<int>& arr, int l, int r);
void quickSort(vector<int>& arr, int low, int high);
void bucketSort(vector<int>& arr);
void shellSort(vector<int>& arr);
void countingSort(vector<int>& arr);

void insertar() {
    if (!arr.empty()) {
        cout << "Ya hay un array insertado. Para insertar uno nuevo, primero elimine el actual." << endl;
        return;
    }

    cout << "Ingrese el array de numeros separados por espacios: ";
    string input;
    getline(cin, input);
    stringstream ss(input);
    int num;
    while (ss >> num) {
        arr.push_back(num);
    }
}

void eliminar() {
    if (arr.empty()) {
        cout << "No hay ningún array insertado para eliminar." << endl;
        return;
    }

    arr.clear();
    cout << "Array eliminado exitosamente." << endl;
}

void ordenar() {
    if (arr.empty()) {
        cout << "Antes de ordenar, debe ingresar un array." << endl;
        return;
    }

    vector<int> arr_copy = arr;

    cout << "Seleccione el metodo de ordenamiento:" << endl;
    cout << "1. Bubble Sort" << endl;
    cout << "2. Selection Sort" << endl;
    cout << "3. Insertion Sort" << endl;
    cout << "4. Merge Sort" << endl;
    cout << "5. Quicksort" << endl;
    cout << "6. Bucket Sort" << endl;
    cout << "7. Shell Sort" << endl;
    cout << "8. Counting Sort" << endl;

    int opcion;
    cin >> opcion;

    auto start = chrono::high_resolution_clock::now();

    switch (opcion) {
        case 1:
            // Bubble Sort
            bubbleSort(arr_copy);
            break;
        case 2:
            // Selection Sort
            selectionSort(arr_copy);
            break;
        case 3:
            // Insertion Sort
            insertionSort(arr_copy);
            break;
        case 4:
            // Merge Sort
            mergeSort(arr_copy, 0, arr_copy.size() - 1);
            break;
        case 5:
            // Quicksort
            quickSort(arr_copy, 0, arr_copy.size() - 1);
            break;
        case 6:
            // Bucket Sort
            bucketSort(arr_copy);
            break;
        case 7:
            // Shell Sort
            shellSort(arr_copy);
            break;
        case 8:
            // Counting Sort
            countingSort(arr_copy);
            break;
        default:
            cout << "Opción no válida." << endl;
            return;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> tiempo = end - start;

    cout << "Array ordenado exitosamente." << endl;
    cout << "Tiempo total: " << tiempo.count() << " segundos" << endl;

    cout << "Array ordenado: ";
    for (int num : arr_copy) {
        cout << num << " ";
    }
    cout << endl;
}

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]);
    }
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

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

void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void bucketSort(vector<int>& arr) {
    const int max_val = *max_element(arr.begin(), arr.end()) + 1;
    vector<int> bucket(max_val, 0);

    for (int num : arr) {
        bucket[num]++;
    }

    arr.clear();
    for (int i = 0; i < max_val; ++i) {
        for (int j = 0; j < bucket[i]; ++j) {
            arr.push_back(i);
        }
    }
}

void shellSort(vector<int>& arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void countingSort(vector<int>& arr) {
    const int max_val = *max_element(arr.begin(), arr.end()) + 1;
    vector<int> count(max_val, 0);
    vector<int> output(arr.size());

    for (int num : arr) {
        count[num]++;
    }

    for (int i = 1; i < max_val; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = arr.size() - 1; i >= 0; --i) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    arr = output;
}

int main() {
    int opcion;

    do {
        cout << "\nMENU PRINCIPAL" << endl;
        cout << "1. Insertar" << endl;
        cout << "2. Ordenar" << endl;
        cout << "3. Eliminar" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        cin.ignore(); // Limpiar el buffer del teclado

        switch (opcion) {
            case 1:
                insertar();
                break;
            case 2:
                ordenar();
                break;
            case 3:
                eliminar();
                break;
            case 4:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción no válida." << endl;
                break;
        }
    } while (opcion != 4);

    return 0;
}
