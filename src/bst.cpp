#include "bst.hpp"
#include <sstream>
#include <string>
#include <cctype>

BinarySearchTree::~BinarySearchTree() {
    destroy_subtree(root_);
}

BinarySearchTree::BinarySearchTree(BinarySearchTree&& other) noexcept {
    root_ = other.root_;
    other.root_ = nullptr;
}

BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree&& other) noexcept {
    if (this != &other) {
        destroy_subtree(root_);
        root_ = other.root_;
        other.root_ = nullptr;
    }
    return *this;
}

void BinarySearchTree::destroy_subtree(TreeNode* node) {
    if (!node) return;
    destroy_subtree(node->left);
    destroy_subtree(node->right);
    delete node;
}

void BinarySearchTree::insert_key(int key_value) {
    insert_node(root_, key_value);
}

void BinarySearchTree::insert_node(TreeNode*& node_ref, int key_value) {
    if (!node_ref) {
        node_ref = new TreeNode(key_value);
        return;
    }
    if (key_value < node_ref->key) {
        insert_node(node_ref->left, key_value);
    } else {
        insert_node(node_ref->right, key_value);
    }
}

std::vector<int> BinarySearchTree::inorder_keys() const {
    std::vector<int> ordered_keys;
    collect_inorder(root_, ordered_keys);
    return ordered_keys;
}

void BinarySearchTree::collect_inorder(TreeNode* node, std::vector<int>& output) {
    if (!node) return;
    collect_inorder(node->left, output);
    output.push_back(node->key);
    collect_inorder(node->right, output);
}

static inline std::string trim_whitespace(const std::string& s) {
    size_t start = 0, end = s.size();
    while (start < end && std::isspace(static_cast<unsigned char>(s[start]))) ++start;
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) --end;
    return s.substr(start, end - start);
}

BinarySearchTree BinarySearchTree::from_csv(const std::string& comma_separated_values) {
    BinarySearchTree tree;
    std::istringstream csv_stream(comma_separated_values);
    std::string token;
    while (std::getline(csv_stream, token, ',')) {
        std::string trimmed = trim_whitespace(token);
        if (trimmed.empty()) continue;
        tree.insert_key(std::stoi(trimmed));
    }
    return tree;
}
