#include "hanoi.hpp"
#include "bst.hpp"
#include <vector>
#include <cstdint>

int main() {
    if (calculate_minimum_hanoi_moves(0) != 0) return 1;
    if (calculate_minimum_hanoi_moves(1) != 1) return 2;
    if (calculate_minimum_hanoi_moves(10) != 1023) return 3;

    BinarySearchTree t = BinarySearchTree::from_csv("5,2,7,3");
    std::vector<int> want{2,3,5,7};
    if (t.inorder_keys() != want) return 4;

    return 0;
}
