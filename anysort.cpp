/**
 * @file anysort.cpp
 * @brief Parallel (threaded) implementation of the selection sort algorithm.
 *
 * @author Frozonovic
 */

#include "anysort.h"

/**
 * @brief Main entry point of the program.
 *
 * @return The exit status of the program.
 */
int main()
{
    std::tuple<long long *, size_t> arr_and_size = randomized_array();
    long long *arr = std::get<0>(arr_and_size);
    size_t arr_size = std::get<1>(arr_and_size);

    par_selection_sort(arr, arr_size);

    std::cout << arr_size << '\n'
              << std::endl;
    for (int i = 0; i < arr_size; ++i)
    {
        std::cout << arr[i] << std::endl;
    }

    delete[] arr;
    return 0;
}

size_t random_thread_count()
{
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<> dist(2, 6);

    return dist(gen);
}

std::tuple<long long *, size_t> randomized_array()
{
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<> dist(1, 100);

    size_t arr_size = dist(gen);

    auto *arr = new long long[arr_size];

    for (int i = 0; i < arr_size; ++i)
    {
        arr[i] = dist(gen);
    }

    return std::tuple<long long *, size_t>{arr, arr_size};
}

void par_selection_sort(long long *arr, size_t arr_size)
{
    for (size_t i = 0; i < arr_size - 1; ++i)
    {
        size_t unsorted_elements = arr_size - i;
        size_t second_half = std::floor(unsorted_elements / 4);
        size_t thread_count = std::min(random_thread_count(), second_half);

        if (thread_count == 0)
        {
            thread_count = 1;
        }

        std::thread threads[thread_count];
        std::tuple<long long, size_t> locals[thread_count];

        for (size_t j = 0; j < thread_count; ++j)
        {
            size_t start = j * (unsorted_elements / thread_count) + i;

            size_t end;
            if (j == thread_count - 1)
            {
                // Out of bounds safety measure
                end = arr_size;
            }
            else
            {
                // Starting index plus the number of elements managed
                end = start + (unsorted_elements / thread_count);
            }

            threads[j] = std::thread(get_local_minima, arr, start, end, std::ref(locals[j]));
        }

        for (auto &thread : threads)
        {
            thread.join();
        }

        global_sort(arr, locals, i, thread_count);
    }
}

void get_local_minima(const long long *arr, size_t start, size_t end, std::tuple<long long, size_t> &local)
{
    long long local_min = arr[start];
    size_t local_min_index = start;

    for (size_t i = start + 1; i < end; ++i)
    {
        if (arr[i] < local_min)
        {
            local_min = arr[i];
            local_min_index = i;
        }
    }

    local = std::tuple<long long, size_t>(local_min, local_min_index);
}

void global_sort(long long *arr, std::tuple<long long, size_t> *locals, size_t global_index, size_t thread_count)
{
    std::tuple<long long, size_t> curr_min = locals[0];

    for (size_t i = 1; i < thread_count; ++i)
    {
        std::tuple<long long, size_t> potential_min = locals[i];

        if (std::get<0>(potential_min) < std::get<0>(curr_min))
        {
            curr_min = potential_min;
        }
    }

    swap(global_index, std::get<1>(curr_min), arr);
}

void swap(const size_t j, const size_t i, long long *arr)
{
    long long temp_j = arr[j];
    arr[j] = arr[i];
    arr[i] = temp_j;
}
