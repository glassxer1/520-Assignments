#include "utilities.h"
#include <iostream>
#include <functional>
#include <algorithm>
#include <cmath>   
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

void sort_by_magnitude(std::vector<double>& vec) {
    std::sort(std::begin(vec), std::end(vec), [](double a, double b) { return std::abs(a) < std::abs(b);});
}

TypedArray<TypedArray<double>> read_matrix_csv(const std::string path) {
    ifstream ifs (path);   /* open file */
    if (!ifs.is_open()) {     /* validate file open for reading */
        perror (("error while opening file " + path).c_str());
        // return TypedArray<double>();
    }
    string line; 
    TypedArray<TypedArray<double>> array = TypedArray<TypedArray<double>>();   
    while (getline (ifs, line)) {         /* read each line */
        string val;                     /* string to hold value */
        TypedArray<double> row = TypedArray<double>();              /* vector for row of values */
        stringstream s (line);          /* stringstream to parse csv */
        while (getline (s, val, ','))   /* for each value */
            row.set (row.size(), stoi(val));  /* convert to int, add to row */
        array.set (array.size(), row);          /* add row to array */
    }
    ifs.close();

    cout << "complete array\n\n";

    return array;
}

void write_matrix_csv(const TypedArray<TypedArray<double>> &matrix, const std::string path) {
    std::ofstream out(path);
    int rows = matrix.size();

    for (int i=0; i<rows; i++) {
        TypedArray<double> row = matrix.safe_get(i);
        int cols = matrix.safe_get(0).size();
        for (int j=0; j<cols; j++)
            out << row.safe_get(j) <<',';
        out << '\n';
    }
}


std::map<std::string, int> occurrence_map(const std::string path) {
    ifstream ifs (path);   /* open file */
    if (!ifs.is_open()) {     /* validate file open for reading */
        perror (("error while opening file " + path).c_str());
        // return TypedArray<double>();
    }
    map<std::string, int> occurrence;
    string line; 
    while (getline (ifs, line)) {         /* read each line */
        string val; 
        stringstream s (line);          /* stringstream to parse csv */
        while (getline (s, val, ' ')) {
            std::for_each(val.begin(), val.end(), [](char & c){ // to lowercase
                c = ::tolower(c);
            });
            // std::cout << val << std::endl;
            occurrence[val]++;
        }   /* for each value */

            
    }
    ifs.close();

    return occurrence;
}
