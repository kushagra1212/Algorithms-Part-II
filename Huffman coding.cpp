#include<iostream>
#include<queue>
#include<unordered_map>
#include<math.h>

using namespace std;

class Node {
public:
    Node *left = nullptr;
    Node *right = nullptr;
    int value;
    Node(int val): value(val) {}
};
unordered_map<int, Node*> node_array;
Node* create_node(int value) {
    Node *newnode = new Node(value);

    return newnode;
}
Node* combine_nodes(Node *node1, Node * node2) {
    int new_value = node1->value + node2->value;

    Node *newnode = create_node(new_value);

    newnode->left = node1;
    newnode->right = node2;
    return newnode;
}
int recur(priority_queue<int, vector<int>, greater<int>> pq) {
    if (pq.size() == 1) {
        return pq.top();
    }

    auto first = pq.top();
    pq.pop();
    auto second = pq.top();
    pq.pop();

    if (node_array[first] == nullptr) {
        node_array[first] = create_node(first);
    }

    if (node_array[second] == nullptr) {
        node_array[second] =  create_node(second);
    }

    Node *newnode = combine_nodes(node_array[first], node_array[second]);

    node_array[newnode->value] = newnode;
    pq.push(newnode->value);

    return recur(pq);
}

void traverse(Node *root) {
    if (root == nullptr)
        return;
    traverse(root->left);
    cout << root->value << " ";
    traverse(root->right);
}

int find_height(Node*root) {
    if (root == nullptr)
        return 0;

    return (max(find_height(root->left), find_height(root->right)) + 1);
}

int main() {

    int n;
    cin >> n;
    priority_queue<int, vector<int>, greater<int>> pq;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pq.push(a[i]);
    }

    for (int i = 0; i < 100; i++) {
        (node_array)[i] = nullptr;
    }
    auto root_value = node_array[recur(pq)];
    traverse(root_value);
    cout << find_height(root_value) << " ";

    return 0;
}