#include <iostream>

using namespace std;

// —труктура вузла (елемента б≥нарного дерева)
struct Node {
    int key;
    int value;
    Node* left;
    Node* right;
};

// ‘ункц≥€ дл€ вставки нового вузла у б≥нарне дерево
Node* insert(Node* root, int key, int value) {
    // якщо дерево порожнЇ, створюЇмо новий вузол ≥ повертаЇмо його
    if (root == nullptr) {
        return new Node{ key, value, nullptr, nullptr };
    }

    // якщо ключ менший за ключ поточного вузла, вставл€Їмо новий вузол у л≥ве п≥ддерево
    if (key < root->key) {
        root->left = insert(root->left, key, value);
    }

    // якщо ключ б≥льший або р≥вний ключу поточного вузла, вставл€Їмо новий вузол у праве п≥ддерево
    else {
        root->right = insert(root->right, key, value);
    }

    return root;
}

// ‘ункц≥€ дл€ пошуку вузла з м≥н≥мальним ключем у б≥нарному дерев≥
Node* findMin(Node* root) {
    // якщо дерево порожнЇ, повертаЇмо nullptr
    if (root == nullptr) {
        return nullptr;
    }

    // якщо л≥ве п≥ддерево порожнЇ, поточний вузол маЇ м≥н≥мальний ключ
    if (root->left == nullptr) {
        return root;
    }

    // ¬ ≥ншому випадку шукаЇмо м≥н≥мальний ключ у л≥вому п≥ддерев≥
    return findMin(root->left);
}

// ‘ункц≥€ дл€ видаленн€ вузла з б≥нарного дерева
Node* deleteNode(Node* root, int key) {
    // якщо дерево порожнЇ, повертаЇмо nullptr
    if (root == nullptr) {
        return nullptr;
    }

    // якщо ключ менший за ключ поточного вузла, видал€Їмо вузол з л≥вого п≥ддерева
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }

    // якщо ключ б≥льший за ключ поточного вузла, видал€Їмо вузол з правого п≥ддерева
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }

    // якщо ключ≥ р≥вн≥, видал€Їмо цей вузол
    else {
        // ¬ипадок 1: ¬узол не маЇ доч≥рн≥х елемент≥в
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }

        // ¬ипадок 2: ¬узол маЇ т≥льки один доч≥рн≥й елемент
        else if (root->left == nullptr || root->right == nullptr) {
            Node* temp = (root->left != nullptr) ? root->left : root->right;
            delete root;
            return temp;
        }

        // ¬ипадок 3: ¬узол маЇ два доч≥рн≥ елементи
        else {
            Node* temp = findMin(root->right);
            root->key = temp->key;
            root->value = temp->value;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    return root;
}

// –екурсивна функц≥€ дл€ перев≥рки р≥вност≥ двох б≥нарних дерев
bool isEqual(Node* T1, Node* T2) {
    // якщо обидва дерева порожн≥, вони р≥вн≥
    if (T1 == nullptr && T2 == nullptr) {
        return true;
    }

    // якщо одне дерево порожнЇ, а ≥нше н≥, вони не р≥вн≥
    if (T1 == nullptr || T2 == nullptr) {
        return false;
    }

    // якщо ключ≥ та значенн€ поточних вузл≥в не р≥вн≥, дерева не р≥вн≥
    if (T1->key != T2->key || T1->value != T2->value) {
        return false;
    }

    // –екурсивно перев≥р€Їмо р≥вн≥сть л≥вих та правих п≥ддерев
    return isEqual(T1->left, T2->left) && isEqual(T1->right, T2->right);
}

// ‘ункц≥€ дл€ виводу б≥нарного дерева у пор€дку
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
        cout << "\n¬ведiть команду: ";
        cout << "\n1: ¬ставити у T1";
        cout << "\n2: ¬ставити у T2";
        cout << "\n3: ¬идалити з T1";
        cout << "\n4: ¬идалити з T2";
        cout << "\n5: ¬ивести T1";
        cout << "\n6: ¬ивести T2";
        cout << "\n7: ѕеревiрити рiвнiсть T1 та T2";
        cout << "\n8: ¬ийти\n";

        int cmd;
        cin >> cmd;

        //¬ставленн€ вузла в дерево
        if (cmd == 1 || cmd == 2) {
            int key, value;
            cout << "¬ведiть ключ та значенн€: ";
            cin >> key >> value;

            if (cmd == 1) {
                T1 = insert(T1, key, value);
            }
            else {
                T2 = insert(T2, key, value);
            }
        }

        //¬идаленн€ вузла з дерева
        else if (cmd == 3 || cmd == 4) {
            int key;
            cout << "¬ведiть ключ: ";
            cin >> key;

            if (cmd == 3) {
                T1 = deleteNode(T1, key);
            }
            else {
                T2 = deleteNode(T2, key);
            }
        }

        //¬иведенн€ дерев в консоль
        else if (cmd == 5 || cmd == 6) {
            if (cmd == 5) {
                printTree(T1);
            }
            else {
                printTree(T2);
            }
            cout << endl;
        }

        //ѕор≥вн€нн€ дерев
        else if (cmd == 7) {
            cout << "„и рiвнi T1 та T2? " << boolalpha << isEqual(T1, T2) << endl;
        }

        //«авершенн€ роботи програми
        else if (cmd == 8) {
            break;
        }
    }

    return 0;
}