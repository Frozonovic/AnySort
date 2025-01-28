/**
 * @file anysort.h
 * @brief Declarations for anysort
 *
 * @author Frozonovic
 */

#ifndef ANYSORT_H
#define ANYSORT_H

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <random>
#include <thread>
#include <tuple>

/**
 * @brief Generates a random number of threads to spin off
 *
 * @return Random, positive integer
 */
size_t random_thread_count();

/**
 * @brief Randomizes an array of values
 *
 * @return Filled array with size
 */
std::tuple<long long *, size_t> randomized_array();

/**
 * @brief Parallelized implementation of selection sort
 *
 * @param arr Array of values for sorting
 * @param arr_size Size of the array of values
 */
void par_selection_sort(long long *arr, size_t arr_size);

/**
 * @brief Gets the local minimum value from a subset of the global array
 *
 * @param arr Global array of values
 * @param start First index of subset
 * @param end Last index of subset
 * @param local A paired value with its global array index
 */
void get_local_minima(const long long *arr, size_t start, size_t end, std::tuple<long long, size_t> &local);

/**
 * @brief Globally sorts the local minima
 *
 * @param arr Global array of values
 * @param locals All local minima paired values
 * @param global_index Global index for elements left to sort
 * @param thread_count Number of threads spun off
 */
void global_sort(long long *arr, std::tuple<long long, size_t> *locals, size_t global_index, size_t thread_count);

/**
 * @brief Takes two elements and switches their place in the array
 *
 * @param j Second index of
 * @param i
 * @param arr
 */
void swap(size_t j, size_t i, long long *arr);

#endif
