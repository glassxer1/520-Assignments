#ifndef UTILITIES
#define UTILITIES

#include "typed_array.h"
#include <map>
#include <vector>

void sort_by_magnitude(std::vector<double>& vec);

TypedArray<TypedArray<double>> read_matrix_csv(const std::string path);

void write_matrix_csv(const TypedArray<TypedArray<double>> &matrix, const std::string path);

std::map<std::string, int> occurrence_map(const std::string path);

#endif