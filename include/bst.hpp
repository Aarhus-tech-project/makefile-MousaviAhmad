#pragma once
#include <vector>
#include <string>

class BinarySearchTree {
public:
    struct TreeNode {
        int key;
        TreeNode* left;
        TreeNode* right;
        explicit TreeNode(int value) : key(value), left(nullptr), right(nullptr) {}
    };

    BinarySearchTree() = default;
    ~BinarySearchTree();

    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    BinarySearchTree(BinarySearchTree&& other) noexcept;
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;

    void insert_key(int key_value);
    std::vector<int> inorder_keys() const;

    static BinarySearchTree from_csv(const std::string& comma_separated_values);

private:
    TreeNode* root_ = nullptr;

    static void destroy_subtree(TreeNode* node);
    static void insert_node(TreeNode*& node_ref, int key_value);
    static void collect_inorder(TreeNode* node, std::vector<int>& output);
};
