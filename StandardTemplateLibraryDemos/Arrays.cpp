#include <iostream>
#include <array>
#include <algorithm>
#include <numeric> // For std::accumulate
#include <iterator>
#include <functional> // For function adapters
#include <utility> // For std::pair

void UseArrays() {
    // Creating and initializing an array
    std::array<int, 5> arr = { 10, 20, 30, 40, 50 };

    // Using an iterator to traverse and print the array
    std::cout << "Array elements: ";
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Using an algorithm to sort the array in descending order
    std::sort(arr.begin(), arr.end(), std::greater<int>());
    std::cout << "Sorted array (descending): ";
    for (const auto& val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Using std::accumulate to find the sum of elements
    int sum = std::accumulate(arr.begin(), arr.end(), 0);
    std::cout << "Sum of array elements: " << sum << std::endl;

    // Using std::transform with std::negate to negate each element
    std::transform(arr.begin(), arr.end(), arr.begin(), std::negate<int>());
    std::cout << "Negated array elements: ";
    for (const auto& val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Using std::find to find an element in the array
    auto find_it = std::find(arr.begin(), arr.end(), -30);
    if (find_it != arr.end()) {
        std::cout << "Element -30 found at position: " << std::distance(arr.begin(), find_it) << std::endl;
    }
    else {
        std::cout << "Element -30 not found." << std::endl;
    }

    // Using std::reverse to reverse the array
    std::reverse(arr.begin(), arr.end());
    std::cout << "Reversed array elements: ";
    for (const auto& val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Using std::for_each with a lambda to print each element
    std::cout << "Array elements using std::for_each: ";
    std::for_each(arr.begin(), arr.end(), [](int x) { std::cout << x << " "; });
    std::cout << std::endl;

    // Using std::pair to store a pair of values
    std::pair<int, int> min_max = std::minmax({ 10, 20, 30, 40, 50 });
    std::cout << "Min element: " << min_max.first << ", Max element: " << min_max.second << std::endl;

    // Using std::transform and std::bind to multiply each element by 2
    std::transform(arr.begin(), arr.end(), arr.begin(), std::bind(std::multiplies<int>(), std::placeholders::_1, 2));
    std::cout << "Array elements multiplied by 2: ";
    for (const auto& val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

}
