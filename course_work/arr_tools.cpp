#include "arr_tools.h"

void init_arr(int* arr, int part_to_init)
{
    srand(time(NULL));
    for (int i = 0; i < part_to_init; i++)
    {
        arr[i] = rand() % 5000;
    }
}

void make_zeros(double* arr, int arr_size)
{
    for (int index = 0; index < arr_size; index++)
    {
        arr[index] = 0.0;
    }
}

void display_output_array(int* arr, int part_to_output)
{
    for (int i = 0; i < part_to_output; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
