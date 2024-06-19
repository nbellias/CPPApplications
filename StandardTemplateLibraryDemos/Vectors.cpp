#include "Vectors.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // For std::accumulate
#include <iterator>
#include <functional> // For function adapters
#include <utility> // For std::pair

void UseVectors() {
    // Creating and initializing a vector
    std::vector<int> vec = { 10, 20, 30, 40, 50 };

    // Using an iterator to traverse and print the vector
    std::cout << "Vector elements: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Using an algorithm to sort the vector in descending order
    std::sort(vec.begin(), vec.end(), std::greater<int>());
    std::cout << "Sorted vector (descending): ";
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Using std::accumulate to find the sum of elements
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    std::cout << "Sum of vector elements: " << sum << std::endl;

    // Using std::transform with std::negate to negate each element
    std::transform(vec.begin(), vec.end(), vec.begin(), std::negate<int>());
    std::cout << "Negated vector elements: ";
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Using std::find to find an element in the vector
    auto find_it = std::find(vec.begin(), vec.end(), -30);
    if (find_it != vec.end()) {
        std::cout << "Element -30 found at position: " << std::distance(vec.begin(), find_it) << std::endl;
    }
    else {
        std::cout << "Element -30 not found." << std::endl;
    }

    // Using std::reverse to reverse the vector
    std::reverse(vec.begin(), vec.end());
    std::cout << "Reversed vector elements: ";
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Using std::for_each with a lambda to print each element
    std::cout << "Vector elements using std::for_each: ";
    std::for_each(vec.begin(), vec.end(), [](int x) { std::cout << x << " "; });
    std::cout << std::endl;

    // Using std::pair to store a pair of values
    std::pair<int, int> min_max = std::minmax({ 10, 20, 30, 40, 50 });
    std::cout << "Min element: " << min_max.first << ", Max element: " << min_max.second << std::endl;

    // Using std::transform and std::bind to multiply each element by 2
    std::transform(vec.begin(), vec.end(), vec.begin(), std::bind(std::multiplies<int>(), std::placeholders::_1, 2));
    std::cout << "Vector elements multiplied by 2: ";
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

}
