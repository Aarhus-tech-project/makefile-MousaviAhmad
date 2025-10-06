#include "hanoi.hpp"
#include "bst.hpp"
#include <iostream>
#include <string>
#include <vector>

static void print_usage(const char* program_name) {
    std::cerr << "Usage:\n"
              << "  " << program_name << " --hanoi N\n"
              << "  " << program_name << " --bst \"5,2,7,3\"\n";
}

int main(int argc, char** argv) {
    std::string selected_command;
    std::string argument_value;

    if (argc == 1) {
        selected_command = "--hanoi";
        argument_value   = "10";
    } else if (argc >= 3) {
        selected_command = argv[1];
        argument_value   = argv[2];
    } else {
        print_usage(argv[0]);
        return 1;
    }

    try {
        if (selected_command == "--hanoi") {
            int disk_count = std::stoi(argument_value);
            std::uint64_t total_move_count = calculate_minimum_hanoi_moves(disk_count);
            std::cout << "Minimum Hanoi moves for " << disk_count
                      << " disks: " << total_move_count << "\n";
        } else if (selected_command == "--bst") {
            BinarySearchTree tree = BinarySearchTree::from_csv(argument_value);
            std::vector<int> sorted_keys = tree.inorder_keys();
            std::cout << "BST inorder:";
            for (size_t i = 0; i < sorted_keys.size(); ++i) {
                std::cout << (i ? "," : " ") << sorted_keys[i];
            }
            std::cout << "\n";
        } else {
            std::cerr << "Unknown option: " << selected_command << "\n";
            print_usage(argv[0]);
            return 2;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 3;
    }

    return 0;
}
