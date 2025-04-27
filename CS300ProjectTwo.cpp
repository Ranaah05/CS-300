//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Raner Chow
// Version     : 1.0
// Copyright   : Copyright ? 2023 SNHU COCE
// Description : Lab 7-1 Project Two
//============================================================================


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// ========== STRUCT DEFINITIONS ==========
struct Course {
    string courseId;
    string courseName;
    vector<string> prerequisites;

};
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

// ========== BINARY SEARCH TREE CLASS ==========

class BinarySearchTree {
private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
	Node* removeNode(Node* node, string courseId);
	void deleteTree(Node* node);
        

public:
    BinarySearchTree();
	virtual ~BinarySearchTree();
	void InOrder();
    void Insert(Course course);
	void Remove(string courseId);
    Course Search(string courseId);
};

// ========== BST FUNCTION IMPLEMENTATION ==========
// define a structure to hold bid information


// Internal structure for tree node

BinarySearchTree::BinarySearchTree()
{
    // (1): initialize housekeeping variables
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree()
{
    // (2)
    // recurse from root deleting every node
    while (root != nullptr) {
        // remove node root
        Remove(root->course.courseId);
    }
}
void BinarySearchTree::deleteTree(Node* node) {
	// (2a): delete tree
	// if node is not equal to null ptr
	if (node != nullptr) {
		// delete left node
		deleteTree(node->left);
		// delete right node
		deleteTree(node->right);
		// delete current node
		delete node;
	}
}
/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // (3a): In order root
    // call inOrder fuction and pass root 
    inOrder(root);
}




/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Course course)
{
    // (6a) Implement inserting a bid into the tree
    // if root equarl to null ptr
    if (root == nullptr) {
        // root is equal to new node bid
        root = new Node(course);
    }
    else {
        // add Node root and bid
        this->addNode(root, course);
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string courseId)
{
    // FIXME (7a) Implement removing a bid from the tree
    // remove node root bidID
    this->removeNode(root, courseId);
}

/**
 * Search for a bid
 */
Course BinarySearchTree::Search(string courseId) {
    // (8) Implement searching the tree for a bid
    // set current node equal to root
    Node* curNode = root;
    // keep looping downwards until bottom reached or matching bidId found
    while (curNode != nullptr)
    {
        // if bidId is equal to current node bidId
        if (curNode->course.courseId.compare(courseId) == 0)
            return curNode->course;
        else if (curNode->course.courseId.compare(courseId) > 0)
            curNode = curNode->left;  // if bid is smaller than current node then traverse left
        else
            curNode = curNode->right;   // else larger so traverse right
    }

    Course course;
    return course;
}
/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Course course)
{
    // (6b) Implement inserting a bid into the tree
    // if node is larger then add to left
    if (node != nullptr && node->course.courseId.compare(course.courseId) > 0)
    {
        // if no left node
        if (node->left == nullptr)
        {
            // this node becomes left
            node->left = new Node(course);
            return;
        }
        else
        {
            // else recurse left
            this->addNode(node->left, course);
        }
    }
    else if (node != nullptr && node->course.courseId.compare(course.courseId) < 0)
    {
        if (node->right == nullptr)
        {
            node->right = new Node(course);
            return;

        }
        else
        {
            this->addNode(node->right, course);
        }
    }
}
void BinarySearchTree::inOrder(Node* node)
{
    // (3b): In order root
    //if node is not equal to null ptr
    if (node != nullptr)
    {
        //InOrder left
        inOrder(node->left);
        //output courseID, name and prereqs
        cout << node->course.courseId << ": " << node->course.courseName << " | ";
        for (int i = 0; i < node->course.prerequisites.size(); i++) {
            cout << node->course.prerequisites.at(i) << " | ";
        }
        cout << endl;
        //InOrder right
        inOrder(node->right);
    }

}


/**
 * Remove a bid from some node (recursive)
 */
Node* BinarySearchTree::removeNode(Node* node, string courseId)
{
    //  (7b) Implement removing a bid from the tree
    // if node = nullptr return node
    if (node == nullptr)
    {
        return node;
    }
    else if (courseId.compare(node->course.courseId) < 0)
    {
        // if bidId is less than node bidId then recurse left{
        node->left = removeNode(node->left, courseId);
    }
    else if (courseId.compare(node->course.courseId) > 0)
    {
        // if bidId is greater than node bidId then recurse right
        node->right = removeNode(node->right, courseId);
    }

    else
    {
        // if left node = nullptr && right node = nullptr delete node 
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node;
            node = nullptr;
        }
        else if (node->left != nullptr && node->right == nullptr)
        {
            Node* temp = node;
            // create temp node to left
            node = node->left;
            delete temp;
            temp = nullptr;
        }
        // if left node != nullptr && right node = nullptr delete node 
        else if (node->left == nullptr && node->right != nullptr)
        {
            Node* temp = node;
            // create temp node to right
            node = node->right;
            delete temp;
            temp = nullptr;
        }
        else
        {
            Node* temp = node->right;
            // while left node is not nullptr keep moving temp left
            while (temp->left != nullptr)
            {
                temp = temp->left;

            }
            // make node course (right) equal to temp course (left)
            node->course = temp->course;
            // remove right node using recursive call
            removeNode(node->right, temp->course.courseId);
        }
        return node;
    }

}


// ========== LOAD FUNCTION ==========

void loadCourses(BinarySearchTree* courses, const string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: file not found." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) {
            cout << "Error: invalid course format" << endl;
            continue;
        }

        Course course;
        course.courseId = tokens[0];
        course.courseName = tokens[1];

        for (size_t i = 2; i < tokens.size(); ++i) {
            course.prerequisites.push_back(tokens[i]);
        }

        courses->Insert(course);
    }

    file.close();
}

void displayCourse(BinarySearchTree* courses, string courseId) {
	Course course = courses->Search(courseId);
    cout << "Course ID: " << course.courseId << " | ";
    cout << "Course Name: " << course.courseName << " | ";
    cout << "Prerequisites: ";
    for (int i = 0; i < course.prerequisites.size(); i++) {
			cout << course.prerequisites.at(i) << " | ";
	}
	cout << endl;
}

// ========== MAIN FUNCTION ==========

int main() {
	BinarySearchTree* courses; // binarySearchTree pointer to hold courses
    courses = new BinarySearchTree();
    Course course; 
    string courseId;
 
    // Menu
    int choice = 0;
    while (choice != 9) {
        cout << "\nMenu:" << endl;
        cout << "1. Load Courses" << endl;
        cout << "2. Display Course List InOrder" << endl;
        cout << "3. Display a Course" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        string courseId;
        switch (choice) {
        case 1:
			//load course data from file
            loadCourses(courses, "courses.csv");
            cout << "Courses loaded successfully!" << endl;
            break;
        case 2:
			//display course list in order
            courses->InOrder();
            break;
        case 3: 
			//display a specific course
            cout << "Enter course ID (e.g. CS101): ";
            cin >> courseId;
			displayCourse(courses, courseId);
            break;

        case 9:
			// exit program
            cout << "Exiting program." << endl;
            break;

        default:
			//Handle invalid input
            cout << "Invalid choice. Try again." << endl;
            break;
        }
    }

    return 0;
}
