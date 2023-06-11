#include "bintree.h"
#include <algorithm>
#include <random>
#include <vector>
#include <iostream>
#include <iomanip>

int main() {
    int size = 9000;
    int trees = 800;
    std::srand ( unsigned ( std::time(0) ) );

    std::vector<int> values;
    std::vector<int> max_values;
    std::vector<int> min_values;
    std::vector<int> diff_values;

    for (int i = 1; i <= size; i++) {
        values.push_back(i);
    }

    std::shuffle(values.begin(), values.end(), std::default_random_engine(981028));
    int max;
    int min;
    for (int i = 1; i <= trees; i++) {
        Node *root = nullptr;
        for (int i : values) {
            insert(root, i, i);
        }
        max = max_height(root);
        min = min_height(root);
        max_values.push_back(max);
        min_values.push_back(min);
        diff_values.push_back(max - min);

        //std::next_permutation(values.begin(), values.end());
        std::random_shuffle(values.begin(), values.end());
        delete_tree(root);
    }

    int max_sum = 0;
    max = 0;
    for (int i : max_values) {
        max_sum += i;
        if (i > max) max = i;
    }

    int min_sum = 0;
    min = max;
    for (int i : min_values) {
        min_sum += i;
        if (i < min) min = i;
    }

    int diff_sum = 0;
    int max_diff = 0;
    int min_diff = max;
    for (int i : diff_values) {
        diff_sum += i;
        if (i > max_diff) max_diff = i;
        if (i < min_diff) min_diff = i;
    }

    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    std::cout << "The average height is: " << max_sum/(double)trees << "\n";
    std::cout << "The highest maximum height: " << max << "\n";

    std::cout << "The average minimum height: " << min_sum / (double)trees << "\n";
    std::cout << "The lowest minimum height: " << min << "\n";

    std::cout << "The average difference: " << diff_sum / (double)trees << "\n";
    std::cout << "The greatest difference: " << max_diff << "\n";
    std::cout << "The lowest difference: " << min_diff << "\n";

    return 0;
}
