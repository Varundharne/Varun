// contributed code from mallikarjun 

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

    void displayAll() const {
        if (students.empty()) {
            cout << "No students to display.\n";
            return;
        }

        cout << "\n--- Student List ---\n";
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

    void deleteById(int id) {
        bool found = false;
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->id == id) {
                students.erase(it);
                saveToFile();
                cout << "Student deleted successfully.\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Student with ID " << id << " not found.\n";
        }
    }

    void editById(int id) {
        for (auto& s : students) {
            if (s.id == id) {
                cout << "Editing student:\n";
                s.display();
                cout << "Enter new details:\n";
                s.input();
                saveToFile();
                cout << "Student updated successfully.\n";
                return;
            }
        }
        cout << "Student with ID " << id << " not found.\n";
    }

    void sortById() {
        sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.id < b.id;
        });
        cout << "Students sorted by ID.\n";
    }

    void sortByName() {
        sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.name < b.name;
        });
        cout << "Students sorted by Name.\n";
    }

    void loadFromFile() {
        ifstream in(filename);
        students.clear();
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
            out << s.id << endl
                << s.name << endl
                << s.age << endl
                << s.course << endl;
        }
        out.close();
    }
};

void showMenu() {
    cout << "\n===== Student Management System =====\n";
    cout << "1. Add Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Search Student by ID\n";
    cout << "4. Delete Student by ID\n";
    cout << "5. Edit Student by ID\n";
    cout << "6. Sort Students by ID\n";
    cout << "7. Sort Students by Name\n";
    cout << "8. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    StudentManager manager;
    int choice;

    do {
        showMenu();
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
        case 4: {
            int id;
            cout << "Enter ID to delete: ";
            cin >> id;
            manager.deleteById(id);
            break;
        }
        case 5: {
            int id;
            cout << "Enter ID to edit: ";
            cin >> id;
            manager.editById(id);
            break;
        }
        case 6:
            manager.sortById();
            break;
        case 7:
            manager.sortByName();
            break;
        case 8:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 8);

    return 0;
}
