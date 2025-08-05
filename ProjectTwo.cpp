/*
Author: Burak Tutkavul
Date: August 05, 2025
Description:
This program is an advising assistance tool for ABCU's Computer Science Department.
It loads course data from a CSV file into a Binary Search Tree (BST) and allows users to:
1. Load data
2. Display all courses in alphanumeric order
3. Search and display details of a specific course, including prerequisites.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Struct to represent a course with its number, title, and list of prerequisites
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Node struct for each node in the Binary Search Tree
struct Node {
    Course course;
    Node* left;
    Node* right;

    // Constructor to initialize a node with a course
    Node(Course newCourse) {
        course = newCourse;
        left = nullptr;
        right = nullptr;
    }
};

// Class for managing the Course Binary Search Tree
class CourseBST {
private:
    Node* root;

    // Recursively adds a course to the BST
    void addNode(Node*& node, Course course) {
        if (node == nullptr) {
            node = new Node(course);
        }
        else if (course.courseNumber < node->course.courseNumber) {
            addNode(node->left, course);
        }
        else {
            addNode(node->right, course);
        }
    }

    // In-order traversal to print the course list in sorted order
    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;
            inOrder(node->right);
        }
    }

    // Recursively searches for a course in the BST
    Node* search(Node* node, string courseNumber) {
        if (node == nullptr || node->course.courseNumber == courseNumber) {
            return node;
        }
        else if (courseNumber < node->course.courseNumber) {
            return search(node->left, courseNumber);
        }
        else {
            return search(node->right, courseNumber);
        }
    }

public:
    // Constructor initializes the root to nullptr
    CourseBST() { root = nullptr; }

    // Public method to insert a course into the BST
    void Insert(Course course) {
        addNode(root, course);
    }

    // Public method to print all courses in sorted order
    void PrintCourseList() {
        inOrder(root);
    }

    // Public method to print detailed information about a specific course
    void PrintCourse(string courseNumber) {
        Node* node = search(root, courseNumber);
        if (node == nullptr) {
            cout << "Course not found." << endl;
        }
        else {
            cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;
            if (node->course.prerequisites.empty()) {
                cout << "Prerequisites: None" << endl;
            }
            else {
                cout << "Prerequisites: ";
                for (size_t i = 0; i < node->course.prerequisites.size(); ++i) {
                    cout << node->course.prerequisites[i];
                    if (i < node->course.prerequisites.size() - 1) cout << ", ";
                }
                cout << endl;
            }
        }
    }
};

// Function to read course data from a CSV file and load into the BST
void LoadCourses(string filename, CourseBST& bst) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Course course;

        // Parse course number and title
        getline(ss, course.courseNumber, ',');
        getline(ss, course.courseTitle, ',');

        // Parse remaining tokens as prerequisites
        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(token);
        }

        // Insert the course into the BST
        bst.Insert(course);
    }

    file.close();
}

// Main program loop with interactive menu
int main() {
    CourseBST bst;
    int choice;
    string filename;
    string courseInput;

    cout << "Welcome to the course planner." << endl;

    while (true) {
        // Display the menu
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "\nWhat would you like to do? ";
        cin >> choice;
        cin.ignore();

        // Handle user menu selection
        switch (choice) {
        case 1:
            cout << "Enter the file name: ";
            getline(cin, filename);
            LoadCourses(filename, bst);
            break;
        case 2:
            cout << "\nHere is a sample schedule:\n" << endl;
            bst.PrintCourseList();
            break;
        case 3:
            cout << "What course do you want to know about? ";
            getline(cin, courseInput);
            transform(courseInput.begin(), courseInput.end(), courseInput.begin(), ::toupper);
            bst.PrintCourse(courseInput);
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            return 0;
        default:
            cout << "\n" << choice << " is not a valid option.\n" << endl;
            break;
        }
    }
}
