#include <iostream>

using namespace std;

// ��������� ����� (�������� �������� ������)
struct Node {
    int key;
    int value;
    Node* left;
    Node* right;
};

// ������� ��� ������� ������ ����� � ������ ������
Node* insert(Node* root, int key, int value) {
    // ���� ������ ������, ��������� ����� ����� � ��������� ����
    if (root == nullptr) {
        return new Node{ key, value, nullptr, nullptr };
    }

    // ���� ���� ������ �� ���� ��������� �����, ���������� ����� ����� � ��� ��������
    if (key < root->key) {
        root->left = insert(root->left, key, value);
    }

    // ���� ���� ������ ��� ����� ����� ��������� �����, ���������� ����� ����� � ����� ��������
    else {
        root->right = insert(root->right, key, value);
    }

    return root;
}

// ������� ��� ������ ����� � ��������� ������ � �������� �����
Node* findMin(Node* root) {
    // ���� ������ ������, ��������� nullptr
    if (root == nullptr) {
        return nullptr;
    }

    // ���� ��� �������� ������, �������� ����� �� ��������� ����
    if (root->left == nullptr) {
        return root;
    }

    // � ������ ������� ������ ��������� ���� � ����� �������
    return findMin(root->left);
}

// ������� ��� ��������� ����� � �������� ������
Node* deleteNode(Node* root, int key) {
    // ���� ������ ������, ��������� nullptr
    if (root == nullptr) {
        return nullptr;
    }

    // ���� ���� ������ �� ���� ��������� �����, ��������� ����� � ����� ��������
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }

    // ���� ���� ������ �� ���� ��������� �����, ��������� ����� � ������� ��������
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }

    // ���� ����� ���, ��������� ��� �����
    else {
        // ������� 1: ����� �� �� ������� ��������
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }

        // ������� 2: ����� �� ����� ���� ������� �������
        else if (root->left == nullptr || root->right == nullptr) {
            Node* temp = (root->left != nullptr) ? root->left : root->right;
            delete root;
            return temp;
        }

        // ������� 3: ����� �� ��� ������ ��������
        else {
            Node* temp = findMin(root->right);
            root->key = temp->key;
            root->value = temp->value;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    return root;
}

// ���������� ������� ��� �������� ������ ���� ������� �����
bool isEqual(Node* T1, Node* T2) {
    // ���� ������ ������ ������, ���� ���
    if (T1 == nullptr && T2 == nullptr) {
        return true;
    }

    // ���� ���� ������ ������, � ���� �, ���� �� ���
    if (T1 == nullptr || T2 == nullptr) {
        return false;
    }

    // ���� ����� �� �������� �������� ����� �� ���, ������ �� ���
    if (T1->key != T2->key || T1->value != T2->value) {
        return false;
    }

    // ���������� ���������� ������ ���� �� ������ �������
    return isEqual(T1->left, T2->left) && isEqual(T1->right, T2->right);
}

// ������� ��� ������ �������� ������ � �������
void printTree(Node* root) {
    if (root == nullptr) {
        return;
    }

    printTree(root->left);
    cout << root->key << " ";
    printTree(root->right);
}

int main() {
    setlocale(LC_ALL, "Ukr");
    Node* T1 = nullptr;
    Node* T2 = nullptr;

    while (true) {
        cout << "\n����i�� �������: ";
        cout << "\n1: �������� � T1";
        cout << "\n2: �������� � T2";
        cout << "\n3: �������� � T1";
        cout << "\n4: �������� � T2";
        cout << "\n5: ������� T1";
        cout << "\n6: ������� T2";
        cout << "\n7: �����i���� �i��i��� T1 �� T2";
        cout << "\n8: �����\n";

        int cmd;
        cin >> cmd;

        //���������� ����� � ������
        if (cmd == 1 || cmd == 2) {
            int key, value;
            cout << "����i�� ���� �� ��������: ";
            cin >> key >> value;

            if (cmd == 1) {
                T1 = insert(T1, key, value);
            }
            else {
                T2 = insert(T2, key, value);
            }
        }

        //��������� ����� � ������
        else if (cmd == 3 || cmd == 4) {
            int key;
            cout << "����i�� ����: ";
            cin >> key;

            if (cmd == 3) {
                T1 = deleteNode(T1, key);
            }
            else {
                T2 = deleteNode(T2, key);
            }
        }

        //��������� ����� � �������
        else if (cmd == 5 || cmd == 6) {
            if (cmd == 5) {
                printTree(T1);
            }
            else {
                printTree(T2);
            }
            cout << endl;
        }

        //��������� �����
        else if (cmd == 7) {
            cout << "�� �i��i T1 �� T2? " << boolalpha << isEqual(T1, T2) << endl;
        }

        //���������� ������ ��������
        else if (cmd == 8) {
            break;
        }
    }

    return 0;
}