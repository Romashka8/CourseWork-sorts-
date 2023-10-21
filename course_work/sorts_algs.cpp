#include "sorts_algs.h"
#include "unistd.h"

using namespace std;

// arr - указатель на сортируемый массив.
// head - "часть" сортируемого массива.
void insert_sort(int* arr, int head)
{
    // начинаем проверку со второго элемента и пока не достигнем последнего.
    for (int i = 1; i < head; i++)
    {
        // проверка нового элемента и "вставка" его в подходящее место.
        for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--)
        {
            // "вставка" элемента, если выполнены условия цикла.
            swap(arr[j - 1], arr[j]);
        }
    }
}

// arr - указатель на преобразуемый массив.
// head - "часть" преобразуемого массива.
void bubble_sort(int* arr, int head)
{
    // переменная для хранения предыдущего значения.
    int buff = 0;
    // при помощи этих циклов поднимаем самое "лёгкое" значение на верх.
    for(int i = 0; i < head - 1; i++)
    {
        for(int j = head - 1; j > i; j--)
        {
            if(arr[j] < arr[j - 1])
            {
                buff = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = buff;
            }
        }
    }
}

// arr - указатель на преобразуемый массив.
// head - "часть" преобразуемого массива.
void quick_sort(int* arr, int head)
{
    // указатели в начало и конец массива.
    int arr_start = 0;
    int arr_end = head - 1;
    // опорный элемент(тот, относительно которого происходит разбиение).
    int pivot = arr[head / 2];
    // делим массив.
    do
    {
        // usleep(1);
        // пробегаем массив, ищем те элементы, которые нужно перекинуть в другую часть массива.
        // в левой части массива оставляем элементы, меньшие опорного.
        while(arr[arr_start] < pivot) arr_start++;
        // в праввой части оставляем элементы, большие опорного.
        while (arr[arr_end] > pivot) arr_end--;
        // меняем элементы местами.
        if (arr_start <= arr_end)
        {
            int temp = arr[arr_start];
            arr[arr_start] = arr[arr_end];
            arr[arr_end] = temp;
            arr_start++;
            arr_end--;
        }
    } while(arr_start <= arr_end);
    // рекурсия, если осталось, что сортировать.
    // левый кусок.
    if(arr_end > 0) quick_sort(arr, arr_end + 1);
    // правый кусок.
    if(arr_start < head) quick_sort(&arr[arr_start], head - arr_start);
}

// arr - указатель на преобразуемый массив.
// head - "часть" преобразуемого массива.
void selection_sort(int* arr, int head)
{
    int min_elem = 0;
    // сюда будем записывать значение при обмене.
    int buff = 0;
    for(int i = 0; i < head; i++)
    {
        // пусть минимум в текущей ячейке.
        min_elem = i;
        // ищем реальный минимум.
        for(int j = i + 1; j < head; j++) min_elem = (arr[j] < arr[min_elem]) ? j : min_elem;
        // делаем перестановку элементов.
        if (i != min_elem)
        {
            buff = arr[i];
            arr[i] = arr[min_elem];
            arr[min_elem] = buff;
        }
    }
}

// arr - указатель на преобразуемый массив.
// head - "часть" преобразуемого массива.
// i - корневой узел(корень).
void heapify(int* arr, int head, int i)
{
    int largest = i;
    // пусть наибольший элемент будет корнем(инициализиркем его как корень).
    int l = 2 * i + 1; // левый лист.
    int r = 2 * i + 2; // правый лист.

    // если левый дочерний элемент больше корня.
    if (l < head && arr[l] > arr[largest]) largest = l;
    // если правый дочерний элемент больше, чем самый большой элемент на данный момент.
    if (r < head && arr[r] > arr[largest]) largest = r;
    // если самый большой элемент не корень.
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        // рекурсивно преобразуем в двоичную кучу затронутое поддерево.
        heapify(arr, head, largest);
    }
}

// arr - указатель на сортируемый массив.
// head - "часть" сортируемого массива. 
void heap_sort(int* arr, int head)
{
    // построение кучи(перегруппировка массива).
    for (int i = head / 2 - 1; i >= 0; i--) heapify(arr, head, i);
    // один за другим извдекаем элементы из кучи.
    // usleep(1000);
    for (int i = head - 1; i >= 0; i--)
    {
        // usleep(1);
        // перемещаем текущий корень в конец.
        swap(arr[0], arr[i]);
        // вызываем процедуру hepify уже на уменьшенной куче(просеиваем её).
        heapify(arr, i, 0);
    }
}

// int main()
// {
//     int test[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
//     selection_sort(test, 10);
//     for (int i = 0; i < 10; i++){std::cout << test[i] << " ";}
//     std::cout << "\n";
//     return 0;
// }
