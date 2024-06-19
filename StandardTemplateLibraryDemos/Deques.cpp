#include <iostream>
#include <deque>
#include <algorithm>
#include <numeric> // For std::accumulate
#include <iterator>
#include <functional> // For function adapters
#include <utility> // For std::pair

void UseDeques() {
    // Creating and initializing a deque
    std::deque<int> deq = { 10, 20, 30, 40, 50 };

    // Using an iterator to traverse and print the deque
    std::cout << "Deque elements: ";
    for (auto it = deq.begin(); it != deq.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Using an algorithm to sort the deque in descending order
    std::sort(deq.begin(), deq.end(), std::greater<int>());
    std::cout << "Sorted deque (descending): ";
    for (const auto& val : deq) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Using std::accumulate to find the sum of elements
    int sum = std::accumulate(deq.begin(), deq.end(), 0);
    std::cout << "Sum of deque elements: " << sum << std::endl;

    // Using std::transform with std::negate to negate each element
    std::transform(deq.begin(), deq.end(), deq.begin(), std::negate<int>());
    std::cout << "Negated deque elements: ";
    for (const auto& val : deq) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Using std::find to find an element in the deque
    auto find_it = std::find(deq.begin(), deq.end(), -30);
    if (find_it != deq.end()) {
        std::cout << "Element -30 found at position: " << std::distance(deq.begin(), find_it) << std::endl;
    }
    else {
        std::cout << "Element -30 not found." << std::endl;
    }

    // Using std::reverse to reverse the deque
    std::reverse(deq.begin(), deq.end());
    std::cout << "Reversed deque elements: ";
    for (const auto& val : deq) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Using std::for_each with a lambda to print each element
    std::cout << "Deque elements using std::for_each: ";
    std::for_each(deq.begin(), deq.end(), [](int x) { std::cout << x << " "; });
    std::cout << std::endl;

    // Using std::pair to store a pair of values
    std::pair<int, int> min_max = std::minmax({ 10, 20, 30, 40, 50 });
    std::cout << "Min element: " << min_max.first << ", Max element: " << min_max.second << std::endl;

    // Using std::transform and std::bind to multiply each element by 2
    std::transform(deq.begin(), deq.end(), deq.begin(), std::bind(std::multiplies<int>(), std::placeholders::_1, 2));
    std::cout << "Deque elements multiplied by 2: ";
    for (const auto& val : deq) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}
