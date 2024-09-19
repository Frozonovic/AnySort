/**
 * @file anysort.h
 * @brief Declarations for anysort
 *
 * @author Brody Lee (blee20@georgefox.edu)
 */

#ifndef ANYSORT_H
#define ANYSORT_H


#include <climits>
#include <cstdlib>
#include <iostream>
#include <random>
#include <thread>


struct min {
   size_t min_index;
   long long value;
   bool mutex;
   
   min(): min_index(ULONG_LONG_MAX), value(LLONG_MAX), mutex(false) {};
};


size_t random_thread_count();


long long* randomized_array();


void selection_sort(long long *arr, size_t n);


void parallel_selection_sort(long long *arr, size_t arr_size, size_t thread_count);


void thread_sort();


void swap(size_t i, size_t j, long long* arr);

#endif
