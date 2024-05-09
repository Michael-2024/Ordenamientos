#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

// Función para ordenar el vector usando el método de la burbuja
int bubbleSort(vector<int> &vec) {
    auto start = std::chrono::steady_clock::now();
    int n = vec.size();
    int iterations = 0;
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            iterations++;
            if (vec[j] > vec[j + 1]) {
                swap(vec[j], vec[j + 1]);
                swapped = true;
            }
            
        }
        if (!swapped) // Si no hubo intercambios, el arreglo ya está ordenado
            break;
    }
    auto end = std::chrono::steady_clock::now();
            cout << "Tiempo de ejecución de Bubble Sort: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microsegundos" << std::endl;
    return iterations;
}

// Función para ordenar el vector usando el método de inserción
int insertionSort(vector<int> &vec) {
    auto start = std::chrono::steady_clock::now();
    int n = vec.size();
    int iterations = 0;
    for (int i = 1; i < n; i++) {
        int key = vec[i];
        int j = i - 1;
        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            j = j - 1;
            iterations++;
        }
        vec[j + 1] = key;
    }
    auto end = std::chrono::steady_clock::now();
            cout << "Tiempo de ejecución de Bubble Sort: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microsegundos" << std::endl;
    return iterations;
}

// Función para ordenar el vector usando el método de selección
int selectionSort(vector<int> &vec) {
    auto start = std::chrono::steady_clock::now();
    int n = vec.size();
    int iterations = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            iterations++;
            if (vec[j] < vec[minIndex]) {
                minIndex = j;
            }
        }
        swap(vec[i], vec[minIndex]);
    }
    auto end = std::chrono::steady_clock::now();
            cout << "Tiempo de ejecución de Bubble Sort: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microsegundos" << std::endl;
    return iterations;
}

// Función para combinar dos subarreglos ordenados
void merge(vector<int> &vec, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Creamos subarreglos temporales
    vector<int> L(n1), R(n2);

    // Copiamos los datos a los subarreglos temporales L[] y R[]
    for (int i = 0; i < n1; i++)
        L[i] = vec[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = vec[m + 1 + j];

    // Fusionamos los subarreglos temporales de vuelta a vec[l..r]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vec[k] = L[i];
            i++;
        } else {
            vec[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiamos los elementos restantes de L[], si hay alguno
    while (i < n1) {
        vec[k] = L[i];
        i++;
        k++;
    }

    // Copiamos los elementos restantes de R[], si hay alguno
    while (j < n2) {
        vec[k] = R[j];
        j++;
        k++;
    }
    
    
}

// Función principal de Merge Sort
void mergeSort(vector<int> &vec, int l, int r) {
    
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(vec, l, m);
        mergeSort(vec, m + 1, r);
        merge(vec, l, m, r);
    }
    
}


// Función para particionar el vector en torno a un pivote
int partition(vector<int> &vec, int low, int high) {
    int pivot = vec[high]; // Tomamos el último elemento como pivote
    int i = (low - 1); // Índice del menor elemento

    for (int j = low; j <= high - 1; j++) {
        if (vec[j] < pivot) {
            i++; // Incrementamos el índice del menor elemento
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[i + 1], vec[high]);
    return (i + 1);
}

int quickSort(vector<int> &vec, int low, int high) {
    
    if (low < high) {
        int pi = partition(vec, low, high);
        int leftIterations = quickSort(vec, low, pi - 1);
        int rightIterations = quickSort(vec, pi + 1, high);
        return leftIterations + rightIterations + high - low;
    }
    return 0;
}

void bucketSort(vector<int> &vec, int numBuckets, int &iterations) {
    auto start = std::chrono::steady_clock::now();
    int n = vec.size();
    if (n == 0)
        return;

    // Encuentra el valor máximo y mínimo en el vector
    int maxVal = *max_element(vec.begin(), vec.end());
    int minVal = *min_element(vec.begin(), vec.end());

    // Calcula el tamaño de cada balde
    double range = (double)(maxVal - minVal + 1) / numBuckets;

    // Crea un vector de baldes
    vector<vector<int>> buckets(numBuckets);

    // Coloca cada elemento en su balde correspondiente
    for (int i = 0; i < n; i++) {
        int index = (int)((vec[i] - minVal) / range);
        buckets[index].push_back(vec[i]);
    }

    // Ordena cada balde
    iterations = 0;
    for (int i = 0; i < numBuckets; i++) {
        iterations += insertionSort(buckets[i]); // Usamos Insertion Sort para ordenar cada balde
    }

    // Combina todos los baldes en el vector original
    int index = 0;
    for (int i = 0; i < numBuckets; i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            vec[index++] = buckets[i][j];
        }
    }
    auto end = std::chrono::steady_clock::now();
            cout << "Tiempo de ejecución de Bubble Sort: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microsegundos" << std::endl;
}

int shellSort(vector<int> &vec) {
    auto start = std::chrono::steady_clock::now();
    int n = vec.size();
    int iterations = 0;

    // Comienza con un gran intervalo y lo reduce gradualmente
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Realiza el insertion sort para los elementos en el intervalo gap
        for (int i = gap; i < n; i++) {
            int temp = vec[i];
            int j;
            for (j = i; j >= gap && vec[j - gap] > temp; j -= gap) {
                vec[j] = vec[j - gap];
                iterations++;
            }
            vec[j] = temp;
        }
    }
    auto end = std::chrono::steady_clock::now();
            cout << "Tiempo de ejecución de Bubble Sort: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microsegundos" << std::endl;
    return iterations;
}

// Función para contar los elementos de un vector
void countingSort(vector<int> &vec) {
    auto start = std::chrono::steady_clock::now();
    int max = *max_element(vec.begin(), vec.end());
    int min = *min_element(vec.begin(), vec.end());
    int range = max - min + 1;

    vector<int> count(range), output(vec.size());
    for (int i = 0; i < vec.size(); i++)
        count[vec[i] - min]++;

    for (int i = 1; i < count.size(); i++)
        count[i] += count[i - 1];

    for (int i = vec.size() - 1; i >= 0; i--) {
        output[count[vec[i] - min] - 1] = vec[i];
        count[vec[i] - min]--;
    }

    for (int i = 0; i < vec.size(); i++)
        vec[i] = output[i];
        auto end = std::chrono::steady_clock::now();
            cout << "Tiempo de ejecución de Bubble Sort: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microsegundos" << std::endl;
}


// Función auxiliar para obtener el dígito en la posición especificada
int getDigit(int num, int pos) {
    for (int i = 1; i < pos; i++)
        num /= 10;
    return num % 10;
}

// Función principal de Radix Sort
void radixSort(vector<int> &vec) {
    auto start = std::chrono::steady_clock::now();
    int n = vec.size();
    if (n == 0)
        return;

    // Encuentra el número máximo para determinar el número de dígitos
    int maxNum = *max_element(vec.begin(), vec.end());

    // Realiza el conteo y la suma de los dígitos en cada posición
    for (int exp = 1; maxNum / exp > 0; exp *= 10) {
        vector<int> count(10, 0), output(n);
        for (int i = 0; i < n; i++)
            count[getDigit(vec[i], exp)]++;

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        // Construye el arreglo de salida
        for (int i = n - 1; i >= 0; i--) {
            output[count[getDigit(vec[i], exp)] - 1] = vec[i];
            count[getDigit(vec[i], exp)]--;
        }

        // Copia el arreglo de salida al arreglo original
        for (int i = 0; i < n; i++)
            vec[i] = output[i];
    }
    auto end = std::chrono::steady_clock::now();
            cout << "Tiempo de ejecución de Bubble Sort: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microsegundos" << std::endl;
}

// Función para leer datos de un archivo de texto y almacenarlos en un vector
void readDataFromFile(vector<int> &vec, const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo " << filename << endl;
        return;
    }

    int num;
    while (file >> num) {
        vec.push_back(num);
    }
    file.close();
}

// Función para imprimir el vector
void printVector(const vector<int> &vec) {
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    vector<int> data;
    string filename = "numeros_aleatorios.txt"; // Nombre del archivo de datos

    // Leer datos del archivo
    readDataFromFile(data, filename);

    // Muestra la cantidad de datos
    cout << "Cantidad de datos: " << data.size() << endl;

    // Muestra los datos desordenados
    cout << "Datos desordenados: ";
    printVector(data);

    int choice;
    do {
        cout << "\nMenú:\n";
        cout << "1. Ordenar los datos (Bubble Sort)\n";
        cout << "2. Ordenar los datos (Insertion Sort )\n";
        cout << "3. Ordenar los datos (Selection Sort)\n";
        cout << "4. Ordenar los datos (Merge Sort)\n";
        cout << "5. Ordenar los datos (Quick Sort)\n";
        cout << "6. Ordenar los datos (Bucket Sort)\n";
        cout << "7. Ordenar los datos (Shell Sort)\n";
        cout << "8. Ordenar los datos (Counting Sort)\n";
        cout << "9. Ordenar los datos (Radix Sort)\n";
        cout << "10. Agregar dato\n";
        cout << "11. Eliminar dato\n";
        cout << "12. Salir\n";
        cout << "Ingrese su elección: ";
        cin >> choice;

        switch (choice) {
            case 1:
                {
                    vector<int> tempData = data; // Copia de los datos para no alterar el original
                    int iterations = bubbleSort(tempData);
                    cout << "Número de iteraciones realizadas: " << iterations << endl;
                    cout << "Datos ordenados: ";
                    printVector(tempData);
                }
                break;
            case 2:
                {
                    vector<int> tempData = data;
                    int iterations = insertionSort(tempData);
                    cout << "Número de iteraciones realizadas: " << iterations << endl;
                    cout << "Datos ordenados: ";
                    printVector(tempData);
                }
                break;
            case 3:
                {
                    vector<int> tempData = data;
                    int iterations = selectionSort(tempData);
                    cout << "Número de iteraciones realizadas: " << iterations << endl;
                    cout << "Datos ordenados: ";
                    printVector(tempData);
                }
                break;
            case 4:
                {
                    vector<int> tempData = data;
                    int n = tempData.size();
                    mergeSort(tempData, 0, n - 1);
                    cout << "Datos ordenados con Merge Sort: ";
                    printVector(tempData);
                }
                break;
            case 5:
                {
                    vector<int> tempData = data;
                    int iterations = quickSort(tempData, 0, tempData.size() - 1);
                    cout << "Número de iteraciones realizadas: " << iterations << endl;
                    cout << "Datos ordenados con Quick Sort: ";
                    printVector(tempData);
                }
                break;
            case 6:
                {
                    vector<int> tempData = data;
                    int iterations;
                    cout << "Datos ordenados con Bucket Sort: ";
                    bucketSort(tempData, 10, iterations);
                    cout << "Número de iteraciones realizadas en Bucket Sort: " << iterations << endl;
                    printVector(tempData);
                }
                break;    
            case 7:
                {
                    vector<int> tempData = data;
                    int iterations = shellSort(tempData);
                    cout << "Número de iteraciones realizadas en Shell Sort: " << iterations << endl;
                    cout << "Datos ordenados con Shell Sort: ";
                    printVector(tempData);
                }
                break;
            case 8:
                {
                    vector<int> tempData = data;
                    countingSort(tempData);
                    cout << "Datos ordenados con Counting Sort: ";
                    printVector(tempData);
                }
                break;
            case 9:
                {
                    vector<int> tempData = data;
                    radixSort(tempData);
                    cout << "Datos ordenados con Radix Sort: ";
                    printVector(tempData);
                }
                break;    
            case 10:
                int newData;
                cout << "Ingrese el nuevo dato: ";
                cin >> newData;
                data.push_back(newData);
                cout << "Dato agregado correctamente.\n";
                break;
            case 11:
                if (!data.empty()) {
                    int index;
                    cout << "Ingrese el índice del dato que desea eliminar (0 - " << data.size() - 1 << "): ";
                    cin >> index;
                    if (index >= 0 && index < data.size()) {
                        data.erase(data.begin() + index);
                        cout << "Dato eliminado correctamente.\n";
                    } else {
                        cout << "Índice inválido.\n";
                    }
                } else {
                    cout << "No hay datos para eliminar.\n";
                }
                break;
            case 12:
                break;
            default:
                cout << "Opción no válida. Por favor, ingrese un número del 1 al 12.\n";
        }
    } while (choice != 12);

    cout << "Gracias por usar el programa.\n";

    return 0;
}
