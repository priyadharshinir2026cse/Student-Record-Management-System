
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Student class
class Student
{
public:
    int rollNo;
    string name;
    float marks[3];

    // Calculate average marks
    float average()
    {
        return (marks[0] + marks[1] + marks[2]) / 3;
    }
};

// Save student details into a file
void saveRecords(Student s[], int count)
{
    ofstream file("students.txt");

    for (int i = 0; i < count; i++)
    {
        file << s[i].rollNo << endl;
        file << s[i].name << endl;

        for (int j = 0; j < 3; j++)
        {
            file << s[i].marks[j] << endl;
        }
    }

    file.close();
}

// Load student details from a file
int loadRecords(Student s[])
{
    ifstream file("students.txt");
    int count = 0;

    if (!file)
        return 0;

    while (count < 100)
    {
        if (!(file >> s[count].rollNo))
            break;

        file.ignore(1000, '\n');

        if (!getline(file, s[count].name))
            break;

        bool valid = true;

        for (int j = 0; j < 3; j++)
        {
            if (!(file >> s[count].marks[j]))
            {
                valid = false;
                break;
            }
        }

        if (!valid)
            break;

        count++;
    }

    file.close();
    return count;
}

// Add a new student
void addStudent(Student s[], int &count)
{
    if (count >= 100)
    {
        cout << "Student limit reached!\n";
        return;
    }

    cout << "Enter Roll Number: ";
    cin >> s[count].rollNo;

    cin.ignore();

    cout << "Enter Student Name: ";
    getline(cin, s[count].name);

    for (int i = 0; i < 3; i++)
    {
        cout << "Enter Subject " << i + 1 << " Marks: ";
        cin >> s[count].marks[i];
    }

    count++;

    saveRecords(s, count);

    cout << "\nStudent added successfully!\n";
}

// Display all students
void displayStudents(Student s[], int count)
{
    if (count == 0)
    {
        cout << "No student records found!\n";
        return;
    }

    for (int i = 0; i < count; i++)
    {
        cout << "\n----------------------\n";
        cout << "Name: " << s[i].name << endl;
        cout << "Roll Number: " << s[i].rollNo << endl;
        cout << "Subject 1 Marks: " << s[i].marks[0] << endl;
        cout << "Subject 2 Marks: " << s[i].marks[1] << endl;
        cout << "Subject 3 Marks: " << s[i].marks[2] << endl;
        cout << "Average Marks: " << s[i].average() << endl;
    }
}

// Search for a student
void searchStudent(Student s[], int count)
{
    int roll;

    cout << "Enter Roll Number to Search: ";
    cin >> roll;

    for (int i = 0; i < count; i++)
    {
        if (s[i].rollNo == roll)
        {
            cout << "\nStudent Found!\n";
            cout << "Name: " << s[i].name << endl;
            cout << "Roll Number: " << s[i].rollNo << endl;
            cout << "Average Marks: " << s[i].average() << endl;
            return;
        }
    }

    cout << "Student not found!\n";
}

// Calculate average marks
void calculateAverage(Student s[], int count)
{
    if (count == 0)
    {
        cout << "No student records available!\n";
        return;
    }

    for (int i = 0; i < count; i++)
    {
        cout << "\nName: " << s[i].name;
        cout << "\nAverage Marks: " << s[i].average() << endl;
    }
}

// Main function
int main()
{
    Student students[100];

    int count = loadRecords(students);
    int choice;

    do
    {
        cout << "\n===== STUDENT RECORD MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Calculate Average Marks\n";
        cout << "5. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addStudent(students, count);
                break;

            case 2:
                displayStudents(students, count);
                break;

            case 3:
                searchStudent(students, count);
                break;

            case 4:
                calculateAverage(students, count);
                break;

            case 5:
                saveRecords(students, count);
                cout << "Records saved successfully!\n";
                cout << "Thank you for using the system!\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
