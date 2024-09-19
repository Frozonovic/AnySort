/**
 * @file anysort.cpp
 * @brief Parallel (threaded) implementation of the selection sort algorithm.
 *
 * @author Brody Lee (blee20@georgefox.edu)
 */


#include "anysort.h"

/**
 * @brief Main entry point of the program.
 *
 * @return The exit status of the program.
 */
int main() {
   // TODO implement program
   long long *arr = randomized_array();
   size_t arr_size = sizeof(arr);
   size_t thread_count = random_thread_count();
   
   selection_sort(arr, arr_size);
   // parallel_selection_sort(thread_cout, arr_size, arr);
   
   delete[] arr;
   return 0;
}


size_t random_thread_count() {
   std::random_device rand;
   std::mt19937 gen(rand());
   std::uniform_int_distribution<> dist(1, 12);
   
   return dist(gen);
}


long long *randomized_array() {
   std::random_device rand;
   std::mt19937 gen(rand());
   std::uniform_int_distribution<> dist(1, 100);
   
   size_t arr_size = dist(gen);
   
   auto *arr = new long long[arr_size];
   
   for (int i = 0; i < arr_size; ++i) {
      arr[i] = dist(gen);
   }
   
   return arr;
}


void selection_sort(long long *arr, size_t arr_size) {
   for (size_t i = 0; i < arr_size - 1; ++i) {
      size_t min_index = i;
      for (size_t j = i + 1; j < arr_size; ++j) {
         if (arr[j] < arr[min_index]) {
            min_index = j;
         }
      }
      
      if (min_index != i) {
         swap(min_index, i, arr);
      }
   }
}


void parallel_selection_sort(long long *arr, size_t arr_size, size_t thread_count) {
   std::thread threads[thread_count];
   
   for (int i = 0; i < thread_count; ++i) {
      threads[i] = std::thread(i, thread_sort);
   }
}


void thread_sort() {

}


void swap(const size_t j, const size_t i, long long *arr) {
   long long temp_j = arr[j];
   arr[j] = arr[i];
   arr[i] = temp_j;
}
