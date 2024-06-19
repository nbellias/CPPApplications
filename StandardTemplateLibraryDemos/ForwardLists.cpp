#include <iostream>
#include <forward_list>
#include <algorithm>
#include <numeric> // For std::accumulate
#include <iterator>
#include <functional> // For function adapters
#include <utility> // For std::pair
#include <vector>

void UseForwardLists() {
    // Creating and initializing a forward_list
    std::forward_list<int> flst = { 10, 20, 30, 40, 50 };

    // Using an iterator to traverse and print the forward_list
    std::cout << "Forward list elements: ";
    for (auto it = flst.begin(); it != flst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Using an algorithm to sort the forward_list in descending order
    flst.sort(std::greater<int>());
    std::cout << "Sorted forward list (descending): ";
    for (const auto& val : flst) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Using std::accumulate to find the sum of elements
    int sum = std::accumulate(flst.begin(), flst.end(), 0);
    std::cout << "Sum of forward list elements: " << sum << std::endl;

    // Using std::transform with std::negate to negate each element (need to convert to vector for transform)
    std::vector<int> temp(flst.begin(), flst.end());
    std::transform(temp.begin(), temp.end(), temp.begin(), std::negate<int>());
    std::copy(temp.begin(), temp.end(), flst.begin());

    std::cout << "Negated forward list elements: ";
    for (const auto& val : flst) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Using std::find to find an element in the forward_list
    auto find_it = std::find(flst.begin(), flst.end(), -30);
    if (find_it != flst.end()) {
        std::cout << "Element -30 found at position: " << std::distance(flst.begin(), find_it) << std::endl;
    }
    else {
        std::cout << "Element -30 not found." << std::endl;
    }

    // Using std::for_each with a lambda to print each element
    std::cout << "Forward list elements using std::for_each: ";
    std::for_each(flst.begin(), flst.end(), [](int x) { std::cout << x << " "; });
    std::cout << std::endl;

    // Using std::pair to store a pair of values
    std::pair<int, int> min_max = std::minmax({ 10, 20, 30, 40, 50 });
    std::cout << "Min element: " << min_max.first << ", Max element: " << min_max.second << std::endl;

    // Using std::transform and std::bind to multiply each element by 2 (need to convert to vector for transform)
    std::transform(temp.begin(), temp.end(), temp.begin(), std::bind(std::multiplies<int>(), std::placeholders::_1, 2));
    std::copy(temp.begin(), temp.end(), flst.begin());

    std::cout << "Forward list elements multiplied by 2: ";
    for (const auto& val : flst) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

}
