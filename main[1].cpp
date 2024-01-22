#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

struct SoccerPlayerRecord {
    string club;
    string firstname;
    string lastname;
    string position;
    double baseCompensation;
};

struct Node {
    SoccerPlayerRecord data;
    Node* left;
    Node* right;
};

class BST {
public:
    BST() : root(nullptr) {}

    void insert(const SoccerPlayerRecord& player) {
        root = insert(root, player);
    }

    void printTree() {
        printHeader(); // Print header (column names)
        printTree(root);
    }

    void searchByInitials(char firstInitial, char lastInitial) {
        searchByInitials(root, firstInitial, lastInitial);
    }

private:
    Node* root;

    Node* insert(Node* root, const SoccerPlayerRecord& player) {
        if (root == nullptr) {
            Node* newNode = new Node{ player, nullptr, nullptr };
            return newNode;
        }

        if (player.baseCompensation < root->data.baseCompensation) {
            root->left = insert(root->left, player);
        }
        else {
            root->right = insert(root->right, player);
        }

        return root;
    }

    void printHeader() {
        cout << "club, lastname, firstname, position, baseCompensation" << endl;
    }

    void printTree(Node* root) {
        if (root == nullptr) {
            return;
        }

        printTree(root->left);
        cout << root->data.club << ", " << root->data.lastname << ", " << root->data.firstname
            << ", " << root->data.position << ", " << root->data.baseCompensation << endl;
        printTree(root->right);
    }

    void searchByInitials(Node* root, char firstInitial, char lastInitial) {
        if (root == nullptr) {
            return;
        }

        if (root->data.firstname[0] == firstInitial && root->data.lastname[0] == lastInitial) {
            cout << root->data.club << ", " << root->data.lastname << ", " << root->data.firstname
                << ", " << root->data.position << ", " << root->data.baseCompensation << endl;
        }

        searchByInitials(root->left, firstInitial, lastInitial);
        searchByInitials(root->right, firstInitial, lastInitial);
    }
};

BST csvToBST(string csvfile) {
    BST bst;
    ifstream ReadFile(csvfile);

    string line, curvalue;
    getline(ReadFile, line); // throw away the first line (column names)

    while (getline(ReadFile, line)) {
        stringstream ss(line);
        int fielditer = 0;
        SoccerPlayerRecord newrec;

        while (getline(ss, curvalue, ',')) {
            switch (fielditer) {
            case 0: newrec.club = curvalue; break;
            case 1: newrec.firstname = curvalue; break;
            case 2: newrec.lastname = curvalue; break;
            case 3: newrec.position = curvalue; break;
            case 4: newrec.baseCompensation = stod(curvalue); break;
            }
            fielditer++;
        }

        bst.insert(newrec);
    }

    return bst;
}

int main(int argc, char** argv) {
    BST soccerPlayerBST = csvToBST("mlssalaries2017.csv");

    // Print the data record-by-record
    cout << "Print the data record-by-record:" << endl;
    soccerPlayerBST.printTree();

    // Search for records by first name and last name initials
    char firstInitial, lastInitial;
    cout << "Enter the first letter of the first name: ";
    cin >> firstInitial;
    cout << "Enter the first letter of the last name: ";
    cin >> lastInitial;

    cout << "Records with initials (" << firstInitial << ", " << lastInitial << "):" << endl;
    soccerPlayerBST.searchByInitials(firstInitial, lastInitial);

    return 0;
}