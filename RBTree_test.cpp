#include <bits/stdc++.h>
using namespace std;

/*
 Red-Black Tree (int keys) with validation/assertions and random testing.
 - Color: RED / BLACK
 - Uses a sentinel NIL node to simplify null handling.
 - insert, delete, rotations implemented per CLRS.
 - Validation:
    * Root is black.
    * No red node has a red child.
    * For every node, all paths to NIL have same #black nodes (black-height).
    * Inorder traversal is strictly increasing (BST property).
*/

enum Color { RED, BLACK };

struct Node {
    int key;
    Color color;
    Node *left, *right, *parent;
    Node(int k = 0, Color c = BLACK, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr)
        : key(k), color(c), left(l), right(r), parent(p) {}
};

struct RBTree {
    Node* NIL;
    Node* root;

    RBTree() {
        NIL = new Node(); // default black sentinel
        NIL->left = NIL->right = NIL->parent = NIL;
        NIL->color = BLACK;
        root = NIL;
    }

    ~RBTree() {
        // basic cleanup (not strict about memory in tests)
        clear(root);
        delete NIL;
    }

    void clear(Node* x) {
        if (x == NIL) return;
        clear(x->left);
        clear(x->right);
        delete x;
    }

    // Left rotate at x: x must have right != NIL
    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != NIL) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == NIL) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != NIL) x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == NIL) root = x;
        else if (y == y->parent->right) y->parent->right = x;
        else y->parent->left = x;
        x->right = y;
        y->parent = x;
    }

    // Standard BST insert then fixup
    void insert(int key) {
        Node* z = new Node(key, RED, NIL, NIL, NIL);
        Node* y = NIL;
        Node* x = root;
        while (x != NIL) {
            y = x;
            if (z->key < x->key) x = x->left;
            else x = x->right;
        }
        z->parent = y;
        if (y == NIL) root = z;
        else if (z->key < y->key) y->left = z;
        else y->right = z;
        z->left = z->right = NIL;
        z->color = RED;
        insert_fixup(z);
    }

    void insert_fixup(Node* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    // transplant u with v
    void transplant(Node* u, Node* v) {
        if (u->parent == NIL) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        v->parent = u->parent;
    }

    Node* minimum(Node* x) {
        while (x->left != NIL) x = x->left;
        return x;
    }

    Node* search(Node* x, int key) {
        while (x != NIL && key != x->key) {
            if (key < x->key) x = x->left;
            else x = x->right;
        }
        return x;
    }

    bool contains(int key) {
        return search(root, key) != NIL;
    }

    void remove(int key) {
        Node* z = search(root, key);
        if (z == NIL) return; // not found
        Node* y = z;
        Color y_original_color = y->color;
        Node* x = nullptr;
        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) x->parent = y;
            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == BLACK) {
            delete_fixup(x);
        }
    }

    void delete_fixup(Node* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                Node* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    // Inorder traversal to vector
    void inorder(Node* x, vector<int>& out) const {
        if (x == NIL) return;
        inorder(x->left, out);
        out.push_back(x->key);
        inorder(x->right, out);
    }
    vector<int> inorder_keys() const {
        vector<int> out;
        inorder(root, out);
        return out;
    }

    // Validation helpers
    // 1) BST property: inorder strictly increasing
    void validate_bst() const {
        vector<int> v = inorder_keys();
        for (size_t i = 1; i < v.size(); ++i) {
            if (!(v[i-1] < v[i])) {
                cerr << "BST property violated: " << v[i-1] << " >= " << v[i] << "\n";
                assert(false);
            }
        }
    }

    // 2) No red node has red child
    void validate_no_consecutive_red(Node* x) const {
        if (x == NIL) return;
        if (x->color == RED) {
            if (x->left->color == RED || x->right->color == RED) {
                cerr << "Consecutive red nodes around key " << x->key << "\n";
                assert(false);
            }
        }
        validate_no_consecutive_red(x->left);
        validate_no_consecutive_red(x->right);
    }

    // 3) Black-height consistency
    // returns black-height from this node to all leaves, or -inf on mismatch (we use -1 to denote error)
    int validate_black_height(Node* x) const {
        if (x == NIL) return 1; // NIL counts as one black
        int left_bh = validate_black_height(x->left);
        int right_bh = validate_black_height(x->right);
        if (left_bh == -1 || right_bh == -1) return -1;
        if (left_bh != right_bh) {
            cerr << "Black-height mismatch at key " << x->key << ": left " << left_bh << " right " << right_bh << "\n";
            return -1;
        }
        return left_bh + (x->color == BLACK ? 1 : 0);
    }

    void validate_all() const {
        // root black
        if (root != NIL) assert(root->color == BLACK && "Root must be black");
        validate_bst();
        validate_no_consecutive_red(root);
        int bh = validate_black_height(root);
        if (bh == -1) {
            cerr << "Black-height validation failed\n";
            assert(false);
        }
    }

    // Debug print (simple)
    void print_inorder() const {
        vector<int> v = inorder_keys();
        for (int k : v) cout << k << ' ';
        cout << '\n';
    }
};

// ---------------- random test harness ----------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    RBTree tree;
    set<int> truth;

    std::mt19937_64 rng((uint64_t)chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> op_dist(0, 99); // 0..99
    uniform_int_distribution<int> val_dist(0, 999);

    const int OPS = 2000;
    for (int i = 0; i < OPS; ++i) {
        int op = op_dist(rng);
        int val = val_dist(rng);
        if (op < 60) { // 60% inserts
            tree.insert(val);
            truth.insert(val);
        } else { // 40% deletes (by value)
            tree.remove(val);
            truth.erase(val);
        }

        // Validate invariants
        tree.validate_all();

        // Compare inorder with truth set
        vector<int> got = tree.inorder_keys();
        vector<int> expected(truth.begin(), truth.end());
        if (got != expected) {
            cerr << "Mismatch after op " << i << " (op=" << op << " val=" << val << ")\n";
            cerr << "Expected (" << expected.size() << "): ";
            for (int x : expected) cerr << x << ' ';
            cerr << "\nGot (" << got.size() << "): ";
            for (int x : got) cerr << x << ' ';
            cerr << "\n";
            assert(false && "Tree contents differ from std::set");
        }

        if ((i & 127) == 0) {
            cout << "Progress: " << i << "/" << OPS << " (size=" << expected.size() << ")\n";
        }
    }

    cout << "All " << OPS << " operations passed. Final tree size: " << truth.size() << "\n";
    return 0;
}
