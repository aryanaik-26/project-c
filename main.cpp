#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <iomanip>
using namespace std;

struct Leave {
    char name[50];
    char roll[20];
    char room[10];
    char date[15];
    char timeOut[10];
    char expectedReturn[15];
    char purpose[50];
    char status[15]; // Returned / Not Returned
};

// Function to split a string by delimiter
vector<string> splitString(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    for (char c : str) {
        if (c == delimiter) {
            tokens.push_back(token);
            token = "";
        } else {
            token += c;
        }
    }
    tokens.push_back(token);
    return tokens;
}

// Function to display a leave record in formatted way
void displayRecord(const Leave& l, int index = -1) {
    if (index != -1) {
        cout << "\n--- Record #" << index << " ---\n";
    }
    cout << "Name: " << l.name << endl;
    cout << "Roll Number: " << l.roll << endl;
    cout << "Room Number: " << l.room << endl;
    cout << "Date of Leave: " << l.date << endl;
    cout << "Time Out: " << l.timeOut << endl;
    cout << "Expected Return: " << l.expectedReturn << endl;
    cout << "Purpose: " << l.purpose << endl;
    cout << "Status: " << l.status << endl;
    cout << "----------------------------------------\n";
}

// Function to read all records from file
vector<Leave> readAllRecords() {
    vector<Leave> records;
    ifstream file("leave_records.txt");
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;
        vector<string> tokens = splitString(line, '|');
        if (tokens.size() >= 8) {
            Leave l;
            strcpy(l.name, tokens[0].c_str());
            strcpy(l.roll, tokens[1].c_str());
            strcpy(l.room, tokens[2].c_str());
            strcpy(l.date, tokens[3].c_str());
            strcpy(l.timeOut, tokens[4].c_str());
            strcpy(l.expectedReturn, tokens[5].c_str());
            strcpy(l.purpose, tokens[6].c_str());
            strcpy(l.status, tokens[7].c_str());
            records.push_back(l);
        }
    }
    file.close();
    return records;
}

// Function to write all records to file
void writeAllRecords(const vector<Leave>& records) {
    ofstream file("leave_records.txt", ios::out);
    for (const auto& l : records) {
        file << l.name << "|" << l.roll << "|" << l.room << "|"
             << l.date << "|" << l.timeOut << "|" << l.expectedReturn
             << "|" << l.purpose << "|" << l.status << endl;
    }
    file.close();
}

void addLeave() {
    Leave l;
    ofstream file("leave_records.txt", ios::app);

    cout << "\n========== Add Leave Entry ==========\n";
    cout << "Enter Student Name: ";
    cin.ignore();
    cin.getline(l.name, 50);

    cout << "Enter Roll Number: ";
    cin.getline(l.roll, 20);

    cout << "Enter Room Number: ";
    cin.getline(l.room, 10);

    cout << "Enter Date of Leave (DD/MM/YYYY): ";
    cin.getline(l.date, 15);

    cout << "Enter Time Out (HH:MM): ";
    cin.getline(l.timeOut, 10);

    cout << "Enter Expected Return Time (DD/MM/YYYY HH:MM): ";
    cin.getline(l.expectedReturn, 15);

    cout << "Enter Purpose of Leave: ";
    cin.getline(l.purpose, 50);

    strcpy(l.status, "Not Returned");

    file << l.name << "|" << l.roll << "|" << l.room << "|"
         << l.date << "|" << l.timeOut << "|" << l.expectedReturn
         << "|" << l.purpose << "|" << l.status << endl;

    file.close();
    cout << "\n✓ Leave entry recorded successfully!\n";
}

void viewLeaves() {
    vector<Leave> records = readAllRecords();

    if (records.empty()) {
        cout << "\nNo leave records found.\n";
        return;
    }

    cout << "\n========== All Leave Records ==========\n";
    cout << "Total Records: " << records.size() << "\n\n";
    
    for (size_t i = 0; i < records.size(); i++) {
        displayRecord(records[i], i + 1);
    }
}

void markReturn() {
    vector<Leave> records = readAllRecords();

    if (records.empty()) {
        cout << "\nNo leave records found.\n";
        return;
    }

    string searchRoll;
    cout << "\n========== Mark Student Return ==========\n";
    cout << "Enter Roll Number: ";
    cin.ignore();
    getline(cin, searchRoll);

    bool found = false;
    vector<int> matchingIndices;

    // Find all records with matching roll number and "Not Returned" status
    for (size_t i = 0; i < records.size(); i++) {
        if (string(records[i].roll) == searchRoll && 
            string(records[i].status) == "Not Returned") {
            matchingIndices.push_back(i);
            found = true;
        }
    }

    if (!found) {
        cout << "\nNo pending leave record found for this roll number.\n";
        return;
    }

    if (matchingIndices.size() == 1) {
        // Only one pending record, update it directly
        strcpy(records[matchingIndices[0]].status, "Returned");
        writeAllRecords(records);
        cout << "\n✓ Return status updated successfully!\n";
        displayRecord(records[matchingIndices[0]]);
    } else {
        // Multiple pending records, show them and let user choose
        cout << "\nMultiple pending records found:\n";
        for (size_t i = 0; i < matchingIndices.size(); i++) {
            cout << "\n[" << (i + 1) << "] ";
            displayRecord(records[matchingIndices[i]]);
        }
        cout << "Enter record number to mark as returned (1-" << matchingIndices.size() << "): ";
        int choice;
        cin >> choice;
        if (choice >= 1 && choice <= (int)matchingIndices.size()) {
            strcpy(records[matchingIndices[choice - 1]].status, "Returned");
            writeAllRecords(records);
            cout << "\n✓ Return status updated successfully!\n";
        } else {
            cout << "\nInvalid choice!\n";
        }
    }
}

void searchLeave() {
    vector<Leave> records = readAllRecords();

    if (records.empty()) {
        cout << "\nNo leave records found.\n";
        return;
    }

    int searchType;
    string searchTerm;
    bool found = false;

    cout << "\n========== Search Leave Record ==========\n";
    cout << "Search by:\n";
    cout << "1. Roll Number\n";
    cout << "2. Student Name\n";
    cout << "Enter choice: ";
    cin >> searchType;

    cout << "Enter search term: ";
    cin.ignore();
    getline(cin, searchTerm);

    cout << "\n--- Search Results ---\n";

    for (size_t i = 0; i < records.size(); i++) {
        bool match = false;
        if (searchType == 1) {
            // Search by roll number
            if (string(records[i].roll).find(searchTerm) != string::npos) {
                match = true;
            }
        } else if (searchType == 2) {
            // Search by name
            if (string(records[i].name).find(searchTerm) != string::npos) {
                match = true;
            }
        }

        if (match) {
            displayRecord(records[i], i + 1);
            found = true;
        }
    }

    if (!found) {
        cout << "\nNo matching records found.\n";
    }
}

int main() {
    int choice;

    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║   Hostel Outing & Leave Management System                ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n";

    do {
        cout << "\n========== Main Menu ==========\n";
        cout << "1. Add Leave / Outing Request\n";
        cout << "2. View All Leave Records\n";
        cout << "3. Mark Student Return (Incoming Entry)\n";
        cout << "4. Search Leave Record\n";
        cout << "5. Exit System\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addLeave();
                break;
            case 2:
                viewLeaves();
                break;
            case 3:
                markReturn();
                break;
            case 4:
                searchLeave();
                break;
            case 5:
                cout << "\n✓ Exiting System... Thank you!\n";
                break;
            default:
                cout << "\n✗ Invalid Choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

