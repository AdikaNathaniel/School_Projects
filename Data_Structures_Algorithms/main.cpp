// CPEN 204: Data Structures and Algorithms - Lab Exercise: Tree Traversals
// main.cpp - builds the trees and runs Tasks 4 to 8.
//
// Build:  g++ -std=c++11 -Wall -Wextra -o tree_lab main.cpp bst.cpp
// Run:    ./tree_lab        (tree_lab.exe on Windows)
//
// ---------------------------------------------------------------------------
// Task 4 tree (insert 50, 30, 70, 20, 40, 60, 80):
//
//                 50
//              /      \
//            30        70
//           /  \      /  \
//         20    40  60    80
//
// Hand prediction:
//   In-order:    20 30 40 50 60 70 80
//   Pre-order:   50 30 20 40 70 60 80
//   Post-order:  20 40 30 60 80 70 50
//   Level-order: 50 30 70 20 40 60 80
//
// ---------------------------------------------------------------------------
// Task 5 tree (insert 45, 25, 65, 15, 35, 55, 80, 10, 30, 90, 85):
//
//                    45
//                /        \
//              25          65
//             /  \        /  \
//           15    35    55    80
//          /     /              \
//        10    30                90
//                               /
//                             85
//
// Hand prediction:
//   In-order:    10 15 25 30 35 45 55 65 80 85 90
//   Pre-order:   45 25 15 10 35 30 65 55 80 90 85
//   Post-order:  10 15 30 35 25 55 85 90 80 65 45
//   Level-order: 45 25 65 15 35 55 80 10 30 90 85
//
// Hand-computed metrics (Task 7):
//   height = 4 (path 45 -> 65 -> 80 -> 90 -> 85), nodes = 11,
//   leaves = 4 (10, 30, 55, 85),
//   balanced = false (at node 80 the left height is -1 and the right is 1,
//                     a difference of 2)
// ---------------------------------------------------------------------------

#include "bst.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

typedef void (*Traversal)(Node*);

// Runs a printing traversal and captures what it prints, so that outputs can
// be compared exactly. The traversal functions themselves keep the required
// void f(Node* root) signature.
std::string capture(Traversal fn, Node* root) {
    std::ostringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    fn(root);
    std::cout.rdbuf(old);
    std::string s = buffer.str();
    if (!s.empty() && s[s.size() - 1] == ' ') {
        s.erase(s.size() - 1);           // drop the trailing separator
    }
    return s;
}

Node* buildTree(const std::vector<int>& values) {
    Node* root = nullptr;
    for (size_t i = 0; i < values.size(); ++i) {
        root = insert(root, values[i]);
    }
    return root;
}

std::string join(const std::vector<int>& v) {
    std::ostringstream out;
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) {
            out << ' ';
        }
        out << v[i];
    }
    return out.str();
}

const char* verdict(bool ok) {
    return ok ? "MATCH" : "MISMATCH";
}

// Prints the four traversals of a tree and compares each one with the
// hand prediction. Returns true if all four match.
bool printAndVerify(Node* root, const std::string expected[4]) {
    const char* labels[4] = {"In-order:    ", "Pre-order:   ", "Post-order:  ", "Level-order: "};
    Traversal fns[4] = {inorder, preorder, postorder, levelorder};
    bool allOk = true;
    for (int i = 0; i < 4; ++i) {
        std::string actual = capture(fns[i], root);
        bool ok = (actual == expected[i]);
        allOk = allOk && ok;
        std::cout << labels[i] << actual << "    [prediction: " << verdict(ok) << "]\n";
    }
    return allOk;
}

// Task 6: prints the iterative traversals and checks them against the
// recursive versions from Task 2.
void compareIterative(Node* root, const std::string& name) {
    std::string recIn = capture(inorder, root);
    std::string itIn = capture(inorderIterative, root);
    std::string recPre = capture(preorder, root);
    std::string itPre = capture(preorderIterative, root);
    std::cout << name << '\n';
    std::cout << "  In-order  (iterative): " << itIn << "    [vs recursive: " << verdict(itIn == recIn) << "]\n";
    std::cout << "  Pre-order (iterative): " << itPre << "    [vs recursive: " << verdict(itPre == recPre) << "]\n";
}

void printMetrics(Node* root) {
    std::cout << "  height(root)      = " << height(root) << '\n';
    std::cout << "  countNodes(root)  = " << countNodes(root) << '\n';
    std::cout << "  countLeaves(root) = " << countLeaves(root) << '\n';
    std::cout << "  isBalanced(root)  = " << (isBalanced(root) ? "true" : "false") << '\n';
}

void banner(const std::string& title) {
    std::cout << "\n==================================================\n"
              << title
              << "\n==================================================\n";
}

} // namespace

int main() {
    // ----------------------------------------------------------------------
    // Task 4: Build, run and verify the worked example
    // ----------------------------------------------------------------------
    banner("Task 4: Worked example (50 30 70 20 40 60 80)");
    std::vector<int> exampleValues = {50, 30, 70, 20, 40, 60, 80};
    Node* example = buildTree(exampleValues);
    const std::string exampleExpected[4] = {
        "20 30 40 50 60 70 80",
        "50 30 20 40 70 60 80",
        "20 40 30 60 80 70 50",
        "50 30 70 20 40 60 80"};
    printAndVerify(example, exampleExpected);

    // ----------------------------------------------------------------------
    // Task 5: Own tree with 11 distinct values
    // ----------------------------------------------------------------------
    banner("Task 5: Own tree (45 25 65 15 35 55 80 10 30 90 85)");
    std::vector<int> ownValues = {45, 25, 65, 15, 35, 55, 80, 10, 30, 90, 85};
    Node* own = buildTree(ownValues);
    const std::string ownExpected[4] = {
        "10 15 25 30 35 45 55 65 80 85 90",
        "45 25 15 10 35 30 65 55 80 90 85",
        "10 15 30 35 25 55 85 90 80 65 45",
        "45 25 65 15 35 55 80 10 30 90 85"};
    printAndVerify(own, ownExpected);

    // ----------------------------------------------------------------------
    // Task 6: Iterative traversals must match the recursive ones
    // ----------------------------------------------------------------------
    banner("Task 6: Iterative traversals (explicit std::stack)");
    compareIterative(example, "Worked example tree:");
    compareIterative(own, "Own tree (Task 5):");

    // ----------------------------------------------------------------------
    // Task 7: Tree metrics on the Task 5 tree
    // ----------------------------------------------------------------------
    banner("Task 7: Tree metrics");
    std::cout << "Own tree (Task 5):\n";
    printMetrics(own);
    std::cout << "Expected by hand: height 4, nodes 11, leaves 4, balanced false\n";
    std::cout << "(Node 80 has an empty left subtree (height -1) and a right subtree of height 1.)\n";

    std::cout << "\nFor comparison, the worked example tree:\n";
    printMetrics(example);

    std::cout << "\nEdge cases:\n";
    Node* single = insert(nullptr, 7);
    std::cout << "  empty tree:  height = " << height(nullptr)
              << ", nodes = " << countNodes(nullptr)
              << ", leaves = " << countLeaves(nullptr)
              << ", balanced = " << (isBalanced(nullptr) ? "true" : "false") << '\n';
    std::cout << "  single node: height = " << height(single)
              << ", nodes = " << countNodes(single)
              << ", leaves = " << countLeaves(single)
              << ", balanced = " << (isBalanced(single) ? "true" : "false") << '\n';
    destroyTree(single);

    // ----------------------------------------------------------------------
    // Task 8: Reconstruct the Task 5 tree from its pre-order and in-order
    // ----------------------------------------------------------------------
    banner("Task 8: Reconstruction from pre-order + in-order");
    std::vector<int> pre = collectPreorder(own);
    std::vector<int> in = collectInorder(own);
    std::cout << "Input pre-order: " << join(pre) << '\n';
    std::cout << "Input in-order:  " << join(in) << '\n';

    Node* rebuilt = buildFromPreIn(pre, in);

    std::string originalLevel = capture(levelorder, own);
    std::string rebuiltLevel = capture(levelorder, rebuilt);
    std::cout << "Original  level-order: " << originalLevel << '\n';
    std::cout << "Rebuilt   level-order: " << rebuiltLevel << '\n';
    std::cout << "Level-order sequences: " << verdict(originalLevel == rebuiltLevel) << '\n';
    std::cout << "Rebuilt   pre-order:   " << capture(preorder, rebuilt) << '\n';
    std::cout << "Rebuilt   post-order:  " << capture(postorder, rebuilt) << '\n';
    std::cout << "Structure check (node by node): "
              << (sameTree(own, rebuilt) ? "IDENTICAL to the original tree" : "DIFFERENT from the original tree")
              << '\n';

    // Clean up all dynamically allocated nodes.
    destroyTree(example);
    destroyTree(own);
    destroyTree(rebuilt);
    return 0;
}
