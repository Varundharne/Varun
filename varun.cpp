#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

class Student {
public:
    int id;
    string name;
    int age;
    string course;

    void input() {
        cout << "Enter Student ID: ";
        while (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a valid integer ID: ";
        }
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        while (!(cin >> age)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a valid age: ";
        }
        cin.ignore();

        cout << "Enter Course: ";
        getline(cin, course);
    }

    void display() const {
        cout << "ID: " << id
             << " | Name: " << name
             << " | Age: " << age
             << " | Course: " << course << endl;
    }
};

class StudentManager {
private:
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

    void displayStudents() const {
        if (students.empty()) {
            cout << "No student records found.\n";
            return;
        }
        cout << "\n--- Student List ---\n";
        for (const auto& s : students) {
            s.display();
        }
        cout << "---------------------\n";
    }

    void searchById(int searchId) const {
        auto it = find_if(students.begin(), students.end(), [searchId](const Student& s) {
            return s.id == searchId;
        });

        if (it != students.end()) {
            cout << "Student found:\n";
            it->display();
        } else {
            cout << "Student with ID " << searchId << " not found.\n";
        }
    }

    // ✅ CONTRIBUTION: Delete Student by ID
    void deleteStudentById(int deleteId) {
        auto it = remove_if(students.begin(), students.end(), [deleteId](const Student& s) {
            return s.id == deleteId;
        });

        if (it != students.end()) {
            students.erase(it, students.end());
            saveToFile();
            cout << "Student with ID " << deleteId << " deleted successfully.\n";
        } else {
            cout << "No student found with ID " << deleteId << ".\n";
        }
    }

    void saveToFile() const {
        ofstream outFile(filename);
        for (const auto& s : students) {
            outFile << s.id << ',' << s.name << ',' << s.age << ',' << s.course << '\n';
        }
    }

    void loadFromFile() {
        ifstream inFile(filename);
        students.clear();
        string line;

        while (getline(inFile, line)) {
            Student s;
            size_t pos = 0;

            // Parse ID
            pos = line.find(',');
            s.id = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            // Parse Name
            pos = line.find(',');
            s.name = line.substr(0, pos);
            line.erase(0, pos + 1);

            // Parse Age
            pos = line.find(',');
            s.age = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            // Remaining is Course
            s.course = line;

            students.push_back(s);
        }
    }
};

// ---------- Main Program ----------
int main() {
    StudentManager manager;
    int choice;

    do {
        cout << "\n===== Student Management Menu =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by ID\n";
        cout << "4. Exit\n";
        cout << "5. Delete Student by ID\n"; // ✅ New Menu Option
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                manager.addStudent();
                break;
            case 2:
                manager.displayStudents();
                break;
            case 3: {
                int id;
                cout << "Enter ID to search: ";
                cin >> id;
                manager.searchById(id);
                break;
            }
            case 4:
                cout << "Exiting the program.\n";
                break;
            case 5: {
                int id;
                cout << "Enter ID to delete: ";
                cin >> id;
                manager.deleteStudentById(id);
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

