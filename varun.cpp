#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Student {
public:
    int id;
    string name;
    int age;
    string course;

    void input() {
        cout << "Enter Student ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter Course: ";
        getline(cin, course);
    }

    void display() const {
        cout << "ID: " << id << ", Name: " << name
             << ", Age: " << age << ", Course: " << course << endl;
    }
};

class StudentManager {
    vector<Student> students;
    const string filename = "students.txt";

public:
    StudentManager() {
        loadFromFile();
    }

    void addStudent() {
        Student s;
        s.input();
        students.push_back(s);
        saveToFile();
        cout << "Student added successfully.\n";
    }

    void displayAll() const {
        if (students.empty()) {
            cout << "No students available.\n";
            return;
        }
        for (const auto& s : students) {
            s.display();
        }
    }

    void searchById(int id) const {
        for (const auto& s : students) {
            if (s.id == id) {
                s.display();
                return;
            }
        }
        cout << "Student not found.\n";
    }

    void loadFromFile() {
        ifstream in(filename);
        Student s;
        while (in >> s.id) {
            in.ignore();
            getline(in, s.name);
            in >> s.age;
            in.ignore();
            getline(in, s.course);
            students.push_back(s);
        }
        in.close();
    }

    void saveToFile() const {
        ofstream out(filename);
        for (const auto& s : students) {
            out << s.id << endl;
            out << s.name << endl;
            out << s.age << endl;
            out << s.course << endl;
        }
        out.close();
    }
};

int main() {
    StudentManager manager;
    int choice;

    do {
        cout << "\n---- Student Management System ----\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by ID\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            manager.addStudent();
            break;
        case 2:
            manager.displayAll();
            break;
        case 3: {
            int id;
            cout << "Enter ID to search: ";
            cin >> id;
            manager.searchById(id);
            break;
        }
        case 4:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
