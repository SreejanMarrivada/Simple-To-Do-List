#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void displayMenu() {
    cout << "\n--- To-Do List Menu ---" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. View Tasks" << endl;
    cout << "3. Delete Task" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

void addTask(const string& filename) {
    string task;
    cout << "Enter the task: ";
    cin.ignore(); // Clear input buffer
    getline(cin, task);

    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << task << endl;
        file.close();
        cout << "Task added successfully!" << endl;
    } else {
        cout << "Error: Unable to open file!" << endl;
    }
}

void viewTasks(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string task;
        int taskNumber = 1;
        cout << "\n--- To-Do List ---" << endl;
        while (getline(file, task)) {
            cout << taskNumber++ << ". " << task << endl;
        }
        file.close();
    } else {
        cout << "Error: Unable to open file!" << endl;
    }
}

void deleteTask(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file!" << endl;
        return;
    }

    vector<string> tasks;
    string task;
    while (getline(file, task)) {
        tasks.push_back(task);
    }
    file.close();

    if (tasks.empty()) {
        cout << "No tasks to delete!" << endl;
        return;
    }

    viewTasks(filename);
    int taskNumber;
    cout << "Enter the task number to delete: ";
    cin >> taskNumber;

    if (taskNumber < 1 || taskNumber > tasks.size()) {
        cout << "Invalid task number!" << endl;
        return;
    }

    tasks.erase(tasks.begin() + taskNumber - 1);

    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const string& t : tasks) {
            outFile << t << endl;
        }
        outFile.close();
        cout << "Task deleted successfully!" << endl;
    } else {
        cout << "Error: Unable to open file!" << endl;
    }
}

int main() {
    const string filename = "todo_list.txt";
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addTask(filename);
                break;
            case 2:
                viewTasks(filename);
                break;
            case 3:
                deleteTask(filename);
                break;
            case 4:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
