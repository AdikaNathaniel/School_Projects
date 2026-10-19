// CPEN 204: Data Structures and Algorithms - Lab Exercise: Tree Traversals
// bst.cpp - implementation of the BST, traversals, metrics and reconstruction.

#include "bst.h"

#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>
#include <unordered_map>

// ===========================================================================
// Task 1: Node and tree structure
// ===========================================================================

// Walk down from the root, going left for smaller values and right for larger
// ones, until an empty position is found; the new node is attached there.
// A value equal to an existing node is ignored, so every value is unique.
Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else if (value > root->value) {
        root->right = insert(root->right, value);
    }
    return root;
}

// Post-order deletion: both subtrees must be freed before the node itself,
// otherwise the pointers to the children would be lost.
void destroyTree(Node* root) {
    if (root == nullptr) {
        return;
    }
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}

// ===========================================================================
// Task 2: Recursive traversals
// ===========================================================================

// In-order (Left, Node, Right): for a BST this prints the values in ascending order.
void inorder(Node* root) {
    if (root == nullptr) {
        return;
    }
    inorder(root->left);
    std::cout << root->value << ' ';
    inorder(root->right);
}

// Pre-order (Node, Left, Right): a parent is always printed before its children.
void preorder(Node* root) {
    if (root == nullptr) {
        return;
    }
    std::cout << root->value << ' ';
    preorder(root->left);
    preorder(root->right);
}

// Post-order (Left, Right, Node): a parent is printed only after both children.
void postorder(Node* root) {
    if (root == nullptr) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    std::cout << root->value << ' ';
}

// ===========================================================================
// Task 3: Level-order traversal (iterative, queue-based)
// ===========================================================================

// Enqueue the root, then repeatedly dequeue a node, print it and enqueue its
// children (left before right). The FIFO queue guarantees that every node on
// level d is printed before any node on level d + 1.
void levelorder(Node* root) {
    if (root == nullptr) {
        return;
    }
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        std::cout << current->value << ' ';
        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
}

// ===========================================================================
// Task 6: Iterative traversals with an explicit stack (no recursion)
// ===========================================================================

// In-order: a node cannot be printed when it is first reached, because its
// entire left subtree must come first. So we push nodes while walking as far
// left as possible; a node is printed only when it is POPPED, i.e. when its
// left subtree is finished. After printing, we continue with its right subtree.
void inorderIterative(Node* root) {
    std::stack<Node*> st;
    Node* current = root;
    while (current != nullptr || !st.empty()) {
        // Push the current node and all of its left descendants.
        while (current != nullptr) {
            st.push(current);
            current = current->left;
        }
        // The top node has no unvisited left subtree, so it is visited now.
        current = st.top();
        st.pop();
        std::cout << current->value << ' ';
        // Its right subtree is traversed next.
        current = current->right;
    }
}

// Pre-order: a node is printed as soon as it is popped. The right child is
// pushed BEFORE the left child so that, because a stack is LIFO, the left
// subtree is processed first (Node, Left, Right).
void preorderIterative(Node* root) {
    if (root == nullptr) {
        return;
    }
    std::stack<Node*> st;
    st.push(root);
    while (!st.empty()) {
        Node* current = st.top();
        st.pop();
        std::cout << current->value << ' ';
        if (current->right != nullptr) {
            st.push(current->right);
        }
        if (current->left != nullptr) {
            st.push(current->left);
        }
    }
}

// ===========================================================================
// Task 7: Tree metrics
// ===========================================================================

// Height in edges: empty tree = -1, so a leaf is 1 + max(-1, -1) = 0.
int height(Node* root) {
    if (root == nullptr) {
        return -1;
    }
    int lh = height(root->left);
    int rh = height(root->right);
    return 1 + (lh > rh ? lh : rh);
}

int countNodes(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countLeaves(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    if (root->left == nullptr && root->right == nullptr) {
        return 1;
    }
    return countLeaves(root->left) + countLeaves(root->right);
}

namespace {

// Sentinel meaning "this subtree is not balanced". Real heights are >= -1,
// so -2 can never be confused with a valid height.
const int UNBALANCED = -2;

// Single post-order pass: each call returns the height of its subtree, or
// UNBALANCED as soon as any node violates |h(left) - h(right)| <= 1.
// Every node is visited at most once and does O(1) extra work, so the whole
// check is O(n), unlike calling height() separately at every node (O(n^2)).
int checkedHeight(Node* root) {
    if (root == nullptr) {
        return -1;
    }
    int lh = checkedHeight(root->left);
    if (lh == UNBALANCED) {
        return UNBALANCED;               // stop early: no need to visit the right subtree
    }
    int rh = checkedHeight(root->right);
    if (rh == UNBALANCED) {
        return UNBALANCED;
    }
    int diff = lh > rh ? lh - rh : rh - lh;
    if (diff > 1) {
        return UNBALANCED;
    }
    return 1 + (lh > rh ? lh : rh);
}

} // namespace

bool isBalanced(Node* root) {
    return checkedHeight(root) != UNBALANCED;
}

// ===========================================================================
// Task 8: Reconstructing a tree from pre-order and in-order sequences
// ===========================================================================

namespace {

// Builds the subtree whose in-order sequence is inorder[inLo..inHi].
// preIdx always points at the next unused element of the pre-order sequence,
// which (by the definition of pre-order) is the root of the subtree being built.
// The root's position in the in-order sequence splits it into the left subtree
// (everything before it) and the right subtree (everything after it).
Node* buildSubtree(const std::vector<int>& pre, int& preIdx, int inLo, int inHi,
                   const std::unordered_map<int, int>& inPos) {
    if (inLo > inHi) {
        return nullptr;                  // empty subtree
    }
    int rootValue = pre[preIdx++];
    Node* root = new Node(rootValue);

    int mid = inPos.at(rootValue);       // O(1) lookup instead of a linear search
    // Pre-order lists the whole left subtree before the right subtree,
    // so the left subtree must be built first.
    root->left = buildSubtree(pre, preIdx, inLo, mid - 1, inPos);
    root->right = buildSubtree(pre, preIdx, mid + 1, inHi, inPos);
    return root;
}

} // namespace

// Reconstructs the exact tree shape from the two sequences alone; it never
// calls insert() or compares values against BST ordering rules.
// Runs in O(n) time thanks to the value -> in-order index map.
Node* buildFromPreIn(std::vector<int>& preorder, std::vector<int>& inorder) {
    if (preorder.size() != inorder.size()) {
        throw std::invalid_argument("pre-order and in-order sequences differ in length");
    }
    std::unordered_map<int, int> inPos;
    for (int i = 0; i < static_cast<int>(inorder.size()); ++i) {
        if (!inPos.insert(std::make_pair(inorder[i], i)).second) {
            throw std::invalid_argument("values must be distinct");
        }
    }
    int preIdx = 0;
    return buildSubtree(preorder, preIdx, 0, static_cast<int>(inorder.size()) - 1, inPos);
}

// ===========================================================================
// Verification helpers
// ===========================================================================

bool sameTree(Node* a, Node* b) {
    if (a == nullptr || b == nullptr) {
        return a == b;
    }
    return a->value == b->value && sameTree(a->left, b->left) && sameTree(a->right, b->right);
}

namespace {

void collectPre(Node* root, std::vector<int>& out) {
    if (root == nullptr) {
        return;
    }
    out.push_back(root->value);
    collectPre(root->left, out);
    collectPre(root->right, out);
}

void collectIn(Node* root, std::vector<int>& out) {
    if (root == nullptr) {
        return;
    }
    collectIn(root->left, out);
    out.push_back(root->value);
    collectIn(root->right, out);
}

} // namespace

std::vector<int> collectPreorder(Node* root) {
    std::vector<int> out;
    collectPre(root, out);
    return out;
}

std::vector<int> collectInorder(Node* root) {
    std::vector<int> out;
    collectIn(root, out);
    return out;
}
