//
// DD1388 - Lab 5: Binary tree
//

#include "bintree.h"
#include <iostream>

void insert(Node * & p, int key, double to_be_inserted) {
    if (p == nullptr) {
        p = new Node();
        p -> key = key;
        p -> data = to_be_inserted;
        p -> left = nullptr;
        p -> right = nullptr;
        return;
    }
    else if (p -> key > key) {
        insert(p -> left, key, to_be_inserted);
    }
    else if (p -> key < key) {
        insert(p -> right, key, to_be_inserted);
    }
    else if (p -> key == key) {
        p -> data = to_be_inserted;
    }
}

void remove(Node * & p, const int & key) {
    if (p == nullptr) {
        throw std::out_of_range("placeholder");
    }
    else if (p -> key > key) {
        remove(p -> left, key);     // If p -> left is a nullptr, then the key is not found and out_of_range is thrown
    }
    else if (p -> key < key) {
        remove(p -> right, key);    // If p -> right is a nullptr, then the key is not found and out_of_range is thrown
    }
    else if (p -> key == key) {     // Remove this node
        if (p -> left != nullptr) {    // Need to find max to the left
            Node *temp1 = p;
            Node *temp2 = p -> left;
            while (temp2 -> right != nullptr) {
                temp1 = temp2;
                temp2 = temp2 -> right;
            }
            p -> key = temp2 -> key;
            p -> data = temp2 -> data;
            if (temp2 -> left != nullptr) {
                temp1 -> right = temp2 -> left;
            }
            else {
                temp1 -> right = nullptr;
            }

            delete temp2;
        }
        else if (p -> right != nullptr) {    // Need to find min to the right
            Node *temp1 = p;
            Node *temp2 = p -> right;
            while (temp2 -> left != nullptr) {
                temp1 = temp2;
                temp2 = temp2 -> left;
            }
            p -> key = temp2 -> key;
            p -> data = temp2 -> data;
            if (temp2 -> right != nullptr) {
                temp1 -> left = temp2 -> right;
            }
            else {
                temp1 -> left = nullptr;
            }

            delete temp2;
        }
        else {
            delete p;
            p = nullptr;
        }
    }
}


const double & find(Node * p, const int & to_be_found) {
    if (p == nullptr) {
        throw std::out_of_range("placeholder");
    }
    if (p -> key == to_be_found) {
        return p -> data;
    }

    // The following makes the g++ compiler give a warning due to both return statements are inside if statements
    // Could potentially fix by setting a node inside a if statement depening on key > or key < and then making a general recursion
    // return find(node, to_be_found);
    else if (p -> key > to_be_found) {
        return find(p -> left, to_be_found);
    }
    else if (p -> key < to_be_found) {
        return find(p -> right, to_be_found);
    }

}

double & edit(Node * p, const int & to_be_changed) {
    if (p == nullptr) {
        throw std::out_of_range("placeholder");
    }
    if (p -> key == to_be_changed) {
        return p -> data;
    }
    else if (p -> key > to_be_changed) {
        return edit(p -> left, to_be_changed);
    }
    else if (p -> key < to_be_changed) {
        return edit(p -> right, to_be_changed);
    }
}

void delete_tree(Node * & p) {
    if (p != nullptr) {
        delete_tree(p -> left);
        delete_tree(p -> right);
        delete p;
        p = nullptr;    // Prevents memory leak
    }
}


// Unsure if max_height is supposed to count the edges or the nodes in a path
// https://www.baeldung.com/cs/binary-tree-height Counted edges so that's what I did.
unsigned int max_height(Node * p) {
    if (p == nullptr || (p -> left == nullptr && p -> right == nullptr)) {
        return 0;
    }

    return 1 + std::max(max_height(p -> left), max_height(p -> right));
}

// Counts number of nodes in longest path, root included
unsigned int max_node_height(Node * p) {
    if (p == nullptr) {
        return 0;
    }

    return 1 + std::max(max_node_height(p -> left), max_node_height(p -> right));
}


// Follows the algorithm from max_height
unsigned int min_height(Node * p) {
    if (p == nullptr || (p -> left == nullptr && p -> right == nullptr)) {
        return 0;
    }

    if (p -> left != nullptr && p -> right != nullptr) {
        return 1 + std::min(min_height(p -> left), min_height(p -> right));
    }

    // If one child is null then we need to take the height of the one that is not null
    return 1 + std::max(min_height(p -> left), min_height(p -> right));
}

unsigned int size(Node * p) {
    if (p == nullptr) {
        return 0;
    }

    return 1 + size(p -> left) + size(p -> right);
}

bool is_balanced(Node * p) {
    if (p == nullptr) {
        return true;
    }

    int dif = abs(max_node_height(p -> left) - max_node_height(p -> right));
    return (dif <= 1 && is_balanced(p -> left) && is_balanced(p -> right));
}
