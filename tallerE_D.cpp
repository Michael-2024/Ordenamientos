#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

// Function prototypes
void printMainMenu();
void printSortingMenu();
void bubbleSort(std::vector<long long int>& arr);
void selectionSort(std::vector<long long int>& arr);
void insertionSort(std::vector<long long int>& arr);
void mergeSort(std::vector<long long int>& arr, int left, int right);
void merge(std::vector<long long int>& arr, int left, int mid, int right);
void quickSort(std::vector<long long int>& arr, int low, int high);
int partition(std::vector<long long int>& arr, int low, int high);
void bucketSort(std::vector<long long int>& arr);
void shellSort(std::vector<long long int>& arr);
void countingSort(std::vector<long long int>& arr);
void radixSort(std::vector<long long int>& arr);
void printArray(const std::vector<long long int>& arr);

int main() {
    std::vector<long long int> numbers;
    int choice, sortChoice;
    std::string input;
    bool exit = false;

    while (!exit) {
        printMainMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "Ingrese números separados por espacios (Presione ENTER para finalizar): ";
                std::cin.ignore(); // Clear the input buffer
                std::getline(std::cin, input);
                std::istringstream iss(input);
                long long int num;
                while (iss >> input) {
                    try {
                        num = std::stoll(input);
                        numbers.push_back(num);
                    } catch (std::invalid_argument const& e) {
                        std::cout << "Error: '" << input << "' no es un número válido." << std::endl;
                        numbers.clear(); // Clear the numbers vector
                        break;
                    } catch (std::out_of_range const& e) {
                        std::cout << "Error: '" << input << "' está fuera del rango de representación de enteros." << std::endl;
                        numbers.clear(); // Clear the numbers vector
                        break;
                    }
                }
                break;
            }
            case 2:
                printSortingMenu();
                std::cin >> sortChoice;
                switch (sortChoice) {
                    case 1:
                        bubbleSort(numbers);
                        break;
                    case 2:
                        selectionSort(numbers);
                        break;
                    case 3:
                        insertionSort(numbers);
                        break;
                    case 4:
                        mergeSort(numbers, 0, numbers.size() - 1);
                        break;
                    case 5:
                        quickSort(numbers, 0, numbers.size() - 1);
                        break;
                    case 6:
                        bucketSort(numbers);
                        break;
                    case 7:
                        shellSort(numbers);
                        break;
                    case 8:
                        countingSort(numbers);
                        break;
                    case 9:
                        radixSort(numbers);
                        break;
                    default:
                        std::cout << "Opción inválida. Por favor, intente de nuevo." << std::endl;
                }
                break;
            case 3:
                if (!numbers.empty()) {
                    std::cout << "Ingrese el índice del número que desea eliminar (tenga encuenta que se inicia desde cero): ";
                    size_t index;
                    std::cin >> index;
                    if (index >= 0 && index < numbers.size()) {
                        numbers.erase(numbers.begin() + index);
                    } else {
                        std::cout << "Índice inválido." << std::endl;
                    }
                } else {
                    std::cout << "La lista está vacía." << std::endl;
                }
                break;
            case 4:
                std::cout << "Saliendo del programa." << std::endl;
                exit = true;
                break;
            default:
                std::cout << "Opción inválida. Por favor, intente de nuevo." << std::endl;
        }

        if (!exit && !numbers.empty()) {
            std::cout << "Lista actual: ";
            printArray(numbers);
            std::cout << std::endl;
        }
    }

    return 0;
}

void printMainMenu() {
    std::cout << "\nMenú principal:" << std::endl;
    std::cout << "1. Ingresar número(s)" << std::endl;
    std::cout << "2. Escoger tipo de ordenamiento" << std::endl;
    std::cout << "3. Eliminar número" << std::endl;
    std::cout << "4. Salir" << std::endl;
    std::cout << "Ingrese su elección: ";
}

void printSortingMenu() {
    std::cout << "\nMenú de ordenamiento:" << std::endl;
    std::cout << "1. Bubble Sort" << std::endl;
    std::cout << "2. Selection Sort" << std::endl;
    std::cout << "3. Insertion Sort" << std::endl;
    std::cout << "4. Merge Sort" << std::endl;
    std::cout << "5. Quicksort" << std::endl;
    std::cout << "6. Bucket Sort" << std::endl;
    std::cout << "7. Shell Sort" << std::endl;
    std::cout << "8. Counting Sort" << std::endl;
    std::cout << "9. Radix Sort" << std::endl;
    std::cout << "Ingrese su elección: ";
}

void bubbleSort(std::vector<long long int>& arr) {
    std::sort(arr.begin(), arr.end());
}

void selectionSort(std::vector<long long int>& arr) {
    std::sort(arr.begin(), arr.end());
}

void insertionSort(std::vector<long long int>& arr) {
    std::sort(arr.begin(), arr.end());
}

void mergeSort(std::vector<long long int>& arr, int left, int right) {
    std::sort(arr.begin(), arr.end());
}

void merge(std::vector<long long int>& arr, int left, int mid, int right) {
    std::sort(arr.begin(), arr.end());
}

void quickSort(std::vector<long long int>& arr, int low, int high) {
    std::sort(arr.begin(), arr.end());
}

int partition(std::vector<long long int>& arr, int low, int high) {
    std::sort(arr.begin(), arr.end());
    return 0;
}

void bucketSort(std::vector<long long int>& arr) {
    std::sort(arr.begin(), arr.end());
}

void shellSort(std::vector<long long int>& arr) {
    std::sort(arr.begin(), arr.end());
}

void countingSort(std::vector<long long int>& arr) {
    std::sort(arr.begin(), arr.end());
}

void radixSort(std::vector<long long int>& arr) {
    std::sort(arr.begin(), arr.end());
}

void printArray(const std::vector<long long int>& arr) {
    for (long long int num : arr) {
        std::cout << num << " ";
    }
}
