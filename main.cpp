#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<string> experssions{"+", "-", "x", "÷"};

class Node {
public:
    string expression;     // 表达式
    int value = -100000;   // 值
    int priority = -1;     // 优先级
    Node *left = nullptr;  // 左子节点
    Node *right = nullptr; // 右子节点

    //释放子节点内存
    void del() {
        if (left) {
            left->del();
            delete left;
        }
        if (right) {
            right->del();
            delete right;
        }
        return;
    }
};

//生成存储表达式的二叉树
void generator(Node *root, int count);

//计算算术表达式值并验证是否符合要求
bool calculator(Node *root);

//返回符合要求的中缀算术表达式
Node *factory(int count);

//中序遍历输出中缀表达式
void in_order(Node *root);

int main() {
    vector<Node *> nodes;
    auto count = 0;
    cout << "欢迎使用小学生四则运算题目生成器，本程序生成的题目不推荐六年级以上文化程度用户使用，可能造成降智。" << endl;
    cout << "请输入您期望的四则运算符数量：";
    cin >> count;
    count *= 2;
    if (count <= 0) {
        cout << "非法输入" << endl;
        system("pause");
        return 0;
    }
    for (int i = 0; i < 300; ++i) {
        nodes.push_back(factory(count));
    }
    count = 1;
    for (auto &i : nodes) {
        cout << "第" << count << "题: ";
        in_order(i);
        cout << "= " << i->value << endl;
        ++count;
    }
    system("pause");
    return 0;
}

Node *factory(int count) {
    Node *root = nullptr;
    do {
        if (root) {
            root->del();
            delete root;
        }
        root = new Node;
        generator(root, count);
    } while (!calculator(root) || root->value == 0);
    return root;
}

void in_order(Node *root) {
    if (root->left) {
        if (root->left->priority != -1 && root->priority > root->left->priority) {
            cout << "(";
            in_order(root->left);
            cout << ")";
        } else if (root->left->priority != -1 && root->priority == root->left->priority && root->expression == "-") {
            in_order(root->left);
        } else {
            in_order(root->left);
        }
    }
    if (root->priority == -1) {
        cout << root->value << " ";
    } else {
        cout << root->expression << " ";
    }
    if (root->right) {
        if (root->right->priority != -1 && root->priority > root->right->priority) {
            cout << "(";
            in_order(root->right);
            cout << ")";
        } else if (root->right->priority != -1 && root->priority == root->right->priority && root->expression == "-") {
            in_order(root->right);
        } else {
            in_order(root->right);
        }
    }
    return;
}

bool calculator(Node *root) {
    if (root->value == -100000) {
        if (!calculator(root->left)) {
            return false;
        }
        if (!calculator(root->left)) {
            return false;
        }
        if (root->expression == "+") {
            root->value = root->left->value + root->right->value;
            if (root->value > 100 || root->value < 0) {
                return false;
            } else {
                return true;
            }
        } else if (root->expression == "-") {
            root->value = root->left->value - root->right->value;
            if (root->value > 100 || root->value < 0) {
                return false;
            } else {
                return true;
            }
        } else if (root->expression == "x") {
            root->value = root->left->value * root->right->value;
            if (root->value > 100 || root->value < 0) {
                return false;
            } else {
                return true;
            }
        } else if (root->expression == "÷") {
            if (!root->right->value) {
                return false;
            }
            if (root->left->value % root->right->value) {
                return false;
            }
            root->value = root->left->value / root->right->value;
            if (root->value > 100 || root->value < 0) {
                return false;
            } else {
                return true;
            }
            return true;
        }
    } else {
        if (root->value < 0 || root->value > 100) {
            return false;
        } else {
            return true;
        }
    }
}

void generator(Node *root, int count) {
    if (count) {
        count -= 2;
        root->left = new Node;
        root->right = new Node;
        auto exp = rand() % 4;
        root->expression = experssions[exp];
        root->priority = exp / 2;
        auto count_left = (rand() % (count / 2 + 1)) * 2;
        auto count_right = count - count_left;
        generator(root->left, count_left);
        generator(root->right, count_right);
        return;
    } else {
        root->value = rand() % 100;
        return;
    }
}