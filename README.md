`#include <iostream>`: Incluye la biblioteca estándar de entrada/salida para la entrada/salida básica.
`#include <fstream>`: Incluye la biblioteca para la entrada/salida de archivos.
`#include <vector>`: Incluye la biblioteca de vectores de la STL (Standard Template Library).
`#include <algorithm>`: Incluye la biblioteca de algoritmos estándar.
`#include <chrono>`: Incluye la biblioteca de cronometraje para medir el tiempo de ejecución de los algoritmos.

`using namespace std;`: para evitar la necesidad de prefijar los nombres de las funciones de la biblioteca estándar
 `using namespace std::chrono;` para trabajar con las funcionalidades de cronometraje.

`El algoritmo Counting Sort ordena los elementos contando el número de ocurrencias de cada valor y luego reconstruyendo el arreglo ordenado. `
int countingSort(vector<long long> &vec) {
    // Cálculo de valores mínimo y máximo
    long long maxVal = *max_element(vec.begin(), vec.end());
    long long minVal = *min_element(vec.begin(), vec.end());
    long long range = maxVal - minVal + 1;
    vector<long long> count(range), output(vec.size());
    int iterations = 0;

    // Conteo de elementos
    for (long long i = 0; i < vec.size(); i++) {
        count[vec[i] - minVal]++;
        iterations++;
    }

    // Cálculo de posiciones finales
    for (long long i = 1; i < range; i++) {
        count[i] += count[i - 1];
        iterations++;
    }

    // Construcción del arreglo de salida
    for (long long i = vec.size() - 1; i >= 0; i--) {
        output[count[vec[i] - minVal] - 1] = vec[i];
        count[vec[i] - minVal]--;
        iterations++;
    }

    // Copiado del arreglo de salida al vector original
    for (long long i = 0; i < vec.size(); i++) {
        vec[i] = output[i];
        iterations++;
    }

    return iterations;
}

// Función para obtener el dígito en la posición especificada
`getDigit: Obtiene el dígito en la posición especificada (unidad, decena, centena, etc.).`
long long getDigit(long long num, long long exp) {
    return (num / exp) % 10;
}

// Función auxiliar para realizar el conteo de los dígitos
`countSort: Ordena los elementos del vector según el dígito actual.`
void countSort(vector<long long> &vec, long long exp, int &iterations) {
    long long n = vec.size();
    vector<long long> output(n);
    long long count[10] = {0};

    // Contar ocurrencias de los dígitos
    for (long long i = 0; i < n; i++) {
        count[getDigit(vec[i], exp)]++;
        iterations++;
    }

    // Cambiar count[i] para que contenga la posición real de este dígito en output[]
    for (long long i = 1; i < 10; i++) {
        count[i] += count[i - 1];
        iterations++;
    }

    // Construir el arreglo de salida
    for (long long i = n - 1; i >= 0; i--) {
        output[count[getDigit(vec[i], exp)] - 1] = vec[i];
        count[getDigit(vec[i], exp)]--;
        iterations++;
    }

    // Copiar el arreglo de salida a vec[], para que vec ahora contenga los números ordenados
    for (long long i = 0; i < n; i++) {
        vec[i] = output[i];
        iterations++;
    }
}

// Función principal de Radix Sort con conteo de iteraciones
int radixSort(vector<long long> &vec) {
    int iterations = 0;

    // Encuentra el número máximo para saber el número de dígitos
    long long maxNum = *max_element(vec.begin(), vec.end());

    // Realiza el conteo y la suma de los dígitos en cada posición
    for (long long exp = 1; maxNum / exp > 0; exp *= 10) {
        countSort(vec, exp, iterations);
    }

    return iterations;
}

// Función para ordenar el vector usando el método de la burbuja
`Comparar elementos adyacentes y cambiarlos si están en el orden incorrecto y repite el proceso hasta que no haya intercambios.`
int bubbleSort(vector<long long> &vec) {
    long long n = vec.size();
    int iterations = 0;
    for (long long i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (long long j = 0; j < n - i - 1; j++) {
            iterations++;
            if (vec[j] > vec[j + 1]) {
                swap(vec[j], vec[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) // Si no hubo intercambios, el arreglo ya está ordenado
            break;
    }
    return iterations;
}

// Función para ordenar el vector usando el método de inserción
`Divide el vector en una parte ordenada y otra desordenada, para luego insertar cada elemento de la parte desordenada en su posición correcta en la parte ordenada.`
int insertionSort(vector<long long> &vec) {
    long long n = vec.size();
    int iterations = 0;
    for (long long i = 1; i < n; i++) {
        long long key = vec[i];
        long long j = i - 1;
        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            j = j - 1;
            iterations++;
        }
        vec[j + 1] = key;
        iterations++;
    }
    return iterations;
}

// Función para ordenar el vector usando el método de selección
`Encuentra el elemento mínimo en la parte desordenada y cámbia con el primer elemento desordenado y luego repite el proceso para el resto del vector.`
int selectionSort(vector<long long> &vec) {
    long long n = vec.size();
    int iterations = 0;
    for (long long i = 0; i < n - 1; i++) {
        long long minIndex = i;
        for (long long j = i + 1; j < n; j++) {
            iterations++;
            if (vec[j] < vec[minIndex]) {
                minIndex = j;
            }
        }
        swap(vec[i], vec[minIndex]);
    }
    return iterations;
}

// Función para combinar dos subarreglos ordenados
``
void merge(vector<long long> &vec, long long l, long long m, long long r, int &iterations) {
    long long n1 = m - l + 1;
    long long n2 = r - m;

    // Creamos subarreglos temporales
    vector<long long> L(n1), R(n2);

    // Copiamos los datos a los subarreglos temporales L[] y R[]
    for (long long i = 0; i < n1; i++)
        L[i] = vec[l + i];
    for (long long j = 0; j < n2; j++)
        R[j] = vec[m + 1 + j];

    // Fusionamos los subarreglos temporales de vuelta a vec[l..r]
    long long i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vec[k] = L[i];
            i++;
        } else {
            vec[k] = R[j];
            j++;
        }
        k++;
        iterations++; // Incrementamos las iteraciones en cada comparación
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
`Divide el vector en dos mitades recursivamente para asi ordenar cada mitad y Fusionar las mitades ordenadas.`
void mergeSort(vector<long long> &vec, long long l, long long r, int &iterations) {
    if (l < r) {
        long long m = l + (r - l) / 2;
        mergeSort(vec, l, m, iterations);
        mergeSort(vec, m + 1, r, iterations);
        merge(vec, l, m, r, iterations); // Pasamos la referencia de 'iterations' a 'merge'
    }
}


// Función para particionar el vector en torno a un pivote
`Selecciona un pivote y reparte el vector en elementos menores y mayores al pivote para ordenar recursivamente las particiones.`
long long partition(vector<long long> &vec, long long low, long long high, int &iterations) {
    long long pivot = vec[high]; // Tomamos el último elemento como pivote
    long long i = (low - 1); // Índice del menor elemento

    for (long long j = low; j <= high - 1; j++) {
        if (vec[j] < pivot) {
            i++; // Incrementamos el índice del menor elemento
            swap(vec[i], vec[j]);
        }
        iterations++;
    }
    swap(vec[i + 1], vec[high]);
    return (i + 1);
}

int quickSort(vector<long long> &vec, long long low, long long high) {
    int iterations = 0;
    if (low < high) {
        long long pi = partition(vec, low, high, iterations);
        iterations += quickSort(vec, low, pi - 1);
        iterations += quickSort(vec, pi + 1, high);
    }
    return iterations;
}

// Función principal de bucketSort
`Encuentra el valor máximo y mínimo en el vector para determinar el rango y asi crear numBucketscubos vacíos para distribuir los elementos del vector en los cubos correspondientes y luego
 combinar todos los cubos ordenados.`
void bucketSort(vector<long long> &vec, int numBuckets, int &iterations) {
    long long n = vec.size();
    if (n == 0)
        return;

    // Encuentra el valor máximo y mínimo en el vector
    long long maxVal = *max_element(vec.begin(), vec.end());
    long long minVal = *min_element(vec.begin(), vec.end());

    // Calcula el tamaño de cada balde
    double range = (double)(maxVal - minVal + 1) / numBuckets;

    // Crea un vector de baldes
    vector<vector<long long>> buckets(numBuckets);

    // Coloca cada elemento en su balde correspondiente
    for (long long i = 0; i < n; i++) {
        int index = (int)((vec[i] - minVal) / range);
        buckets[index].push_back(vec[i]);
    }

    // Ordena cada balde
    iterations = 0;
    for (int i = 0; i < numBuckets; i++) {
        iterations += insertionSort(buckets[i]);
    }

    // Une los baldes en el vector original
    vec.clear();
    for (int i = 0; i < numBuckets; i++) {
        for (long long j = 0; j < buckets[i].size(); j++) {
            vec.push_back(buckets[i][j]);
            iterations++;
        }
    }
}

// Función para ordenar el vector usando el método de Shell Sort
`El algoritmo de Shell Sort es una extensión del ordenamiento por inserción que permite comparaciones y movimientos de elementos distantes, lo cual mejora la eficiencia en comparación con el ordenamiento por inserción simple.`
int shellSort(vector<long long> &vec) {
    long long n = vec.size();
    int iterations = 0;
    for (long long gap = n / 2; gap > 0; gap /= 2) {
        for (long long i = gap; i < n; i++) {
            long long temp = vec[i];
            long long j;
            for (j = i; j >= gap && vec[j - gap] > temp; j -= gap) {
                vec[j] = vec[j - gap];
                iterations++;
            }
            vec[j] = temp;
            iterations++;
        }
    }
    return iterations;
}

// Función para leer datos de un archivo de texto y almacenarlos en un vector
void readDataFromFile(vector<long long> &vec, const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo " << filename << endl;
        return;
    }

    long long num;
    while (file >> num) {
        vec.push_back(num);
    }
    file.close();
}

// Función para agregar un número al vector
void insertNumber(vector<long long> &vec, long long number) {
    vec.push_back(number);
}

// Función para eliminar un número del vector
bool deleteNumber(vector<long long> &vec, long long number) {
    auto it = find(vec.begin(), vec.end(), number);
    if (it != vec.end()) {
        vec.erase(it);
        return true;
    }
    return false;
}

int main() {
    vector<long long> data;
    string filename = "numeros_aleatorios.txt"; // Nombre del archivo de datos

    // Leer datos del archivo
    readDataFromFile(data, filename);

    // Muestra la cantidad de datos
    cout << "Cantidad de datos: " << data.size() << endl;

    while (true) {
        int choice;
        cout << "Seleccione una opción:" << endl;
        cout << "1. Ordenar usando Bubble Sort" << endl;
        cout << "2. Ordenar usando Insertion Sort" << endl;
        cout << "3. Ordenar usando Selection Sort" << endl;
        cout << "4. Ordenar usando Merge Sort" << endl;
        cout << "5. Ordenar usando Quick Sort" << endl;
        cout << "6. Ordenar usando Bucket Sort" << endl;
        cout << "7. Ordenar usando Shell Sort" << endl;
        cout << "8. Ordenar usando Radix Sort" << endl;
        cout << "9. Ordenar usando Counting Sort" << endl;
        cout << "10. Insertar un número" << endl;
        cout << "11. Eliminar un número" << endl;
        cout << "12. Salir" << endl;
        cout << "Ingrese su elección: ";
        cin >> choice;

        vector<long long> sortedData = data;
        auto start = high_resolution_clock::now();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        int iterations = 0;

        switch (choice) {
            case 1:
                start = high_resolution_clock::now();
                iterations = bubbleSort(sortedData);
                stop = high_resolution_clock::now();
                break;
            case 2:
                start = high_resolution_clock::now();
                iterations = insertionSort(sortedData);
                stop = high_resolution_clock::now();
                break;
            case 3:
                start = high_resolution_clock::now();
                iterations = selectionSort(sortedData);
                stop = high_resolution_clock::now();
                break;
            case 4:
                start = high_resolution_clock::now();
                iterations = 0;
                mergeSort(sortedData, 0, sortedData.size() - 1, iterations);
                stop = high_resolution_clock::now();
                break;
            case 5:
                start = high_resolution_clock::now();
                iterations = quickSort(sortedData, 0, sortedData.size() - 1);
                stop = high_resolution_clock::now();
                break;
            case 6:
                start = high_resolution_clock::now();
                bucketSort(sortedData, 10, iterations);
                stop = high_resolution_clock::now();
                break;
            case 7:
                start = high_resolution_clock::now();
                iterations = shellSort(sortedData);
                stop = high_resolution_clock::now();
                break;
            case 8:
                start = high_resolution_clock::now();
                iterations = radixSort(sortedData);
                stop = high_resolution_clock::now();
                break;
            case 9:
                start = high_resolution_clock::now();
                iterations = countingSort(sortedData);
                stop = high_resolution_clock::now();
                break;
            case 10: {
                long long number;
                cout << "Ingrese el número a insertar: ";
                cin >> number;
                insertNumber(data, number);
                cout << "Número insertado correctamente." << endl;
                continue;
            }
            case 11: {
                long long number;
                cout << "Ingrese el número a eliminar: ";
                cin >> number;
                if (deleteNumber(data, number)) {
                    cout << "Número eliminado correctamente." << endl;
                } else {
                    cout << "Número no encontrado." << endl;
                }
                continue;
            }
            case 12:
                return 0;
            default:
                cout << "Opción no válida." << endl;
                continue;
        }

        duration = duration_cast<microseconds>(stop - start);
        cout << "Datos ordenados: ";
        for (long long num : sortedData) {
            cout << num << " ";
        }
        cout << endl;
        cout << "Tiempo de ejecución: " << duration.count() << " microsegundos" << endl;
        cout << "Iteraciones: " << iterations << endl;
    }

    return 0;
}
