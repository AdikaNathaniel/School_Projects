// CPEN 204: Data Structures and Algorithms - Lab Exercise: Tree Traversals
// bst.h - declarations for the binary search tree, its traversals, metrics
//         and reconstruction (Tasks 1-3 and 6-8).

#ifndef BST_H
#define BST_H

#include <vector>

// ---------------------------------------------------------------------------
// Task 1: Node and tree structure
// ---------------------------------------------------------------------------
struct Node {
    int value;
    Node* left;
    Node* right;

    explicit Node(int v) : value(v), left(nullptr), right(nullptr) {}
};

// Inserts value into the BST rooted at root and returns the (possibly new) root.
// Smaller values go left, larger values go right. Duplicates are ignored.
Node* insert(Node* root, int value);

// Frees every node of the tree (post-order: children before parent).
void destroyTree(Node* root);

// ---------------------------------------------------------------------------
// Task 2: Recursive depth-first traversals (print values separated by spaces)
// ---------------------------------------------------------------------------
void inorder(Node* root);     // Left, Node, Right
void preorder(Node* root);    // Node, Left, Right
void postorder(Node* root);   // Left, Right, Node

// ---------------------------------------------------------------------------
// Task 3: Iterative breadth-first traversal using std::queue<Node*>
// ---------------------------------------------------------------------------
void levelorder(Node* root);

// ---------------------------------------------------------------------------
// Task 6: Iterative depth-first traversals using an explicit std::stack<Node*>
// ---------------------------------------------------------------------------
void inorderIterative(Node* root);
void preorderIterative(Node* root);

// ---------------------------------------------------------------------------
// Task 7: Tree metrics
// ---------------------------------------------------------------------------
int height(Node* root);        // edges on the longest root-to-leaf path; empty tree = -1
int countNodes(Node* root);
int countLeaves(Node* root);
bool isBalanced(Node* root);   // O(n): height and balance checked in one post-order pass

// ---------------------------------------------------------------------------
// Task 8: Reconstruction from pre-order and in-order sequences
// ---------------------------------------------------------------------------
Node* buildFromPreIn(std::vector<int>& preorder, std::vector<int>& inorder);

// Helpers used to verify results
bool sameTree(Node* a, Node* b);                       // identical shape and values
std::vector<int> collectPreorder(Node* root);          // traversal into a vector
std::vector<int> collectInorder(Node* root);

#endif // BST_H
