#include <iostream>
#include <list>
#include <algorithm>
#include <numeric> // For std::accumulate
#include <iterator>
#include <functional> // For function adapters
#include <utility> // For std::pair

void UseLists() {
    // Creating and initializing a list
    std::list<int> lst = { 10, 20, 30, 40, 50 };

    // Using an iterator to traverse and print the list
    std::cout << "List elements: ";
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Using an algorithm to sort the list in descending order
    lst.sort(std::greater<int>());
    std::cout << "Sorted list (descending): ";
    for (const auto& val : lst) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Using std::accumulate to find the sum of elements (requires conversion to vector)
    int sum = std::accumulate(lst.begin(), lst.end(), 0);
    std::cout << "Sum of list elements: " << sum << std::endl;

    // Using std::transform with std::negate to negate each element
    std::transform(lst.begin(), lst.end(), lst.begin(), std::negate<int>());
    std::cout << "Negated list elements: ";
    for (const auto& val : lst) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Using std::find to find an element in the list
    auto find_it = std::find(lst.begin(), lst.end(), -30);
    if (find_it != lst.end()) {
        std::cout << "Element -30 found at position: " << std::distance(lst.begin(), find_it) << std::endl;
    }
    else {
        std::cout << "Element -30 not found." << std::endl;
    }

    // Using std::reverse to reverse the list (requires conversion to vector)
    lst.reverse();
    std::cout << "Reversed list elements: ";
    for (const auto& val : lst) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Using std::for_each with a lambda to print each element
    std::cout << "List elements using std::for_each: ";
    std::for_each(lst.begin(), lst.end(), [](int x) { std::cout << x << " "; });
    std::cout << std::endl;

    // Using std::pair to store a pair of values
    std::pair<int, int> min_max = std::minmax({ 10, 20, 30, 40, 50 });
    std::cout << "Min element: " << min_max.first << ", Max element: " << min_max.second << std::endl;

    // Using std::transform and std::bind to multiply each element by 2
    std::transform(lst.begin(), lst.end(), lst.begin(), std::bind(std::multiplies<int>(), std::placeholders::_1, 2));
    std::cout << "List elements multiplied by 2: ";
    for (const auto& val : lst) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}
