#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cstdlib>

#define SUBJECT_COUNT 4
#define MAX_SUB_MARKS 100
#define PASS_PERCENTAGE 30.00

using namespace std;

const string subjects[] = {"EMMD", "DSA", "OOP", "COA"};

void clear_terminal()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void back_to_menu()
{
    cout << "\nPress Enter to go back to menu...";
    cin.ignore(10000, '\n');
    cin.get();
    clear_terminal();
}

class StudentRecord
{
    int roll_number;
    int year;
    int marks[SUBJECT_COUNT];
    string first_name;
    string last_name;
    float percentage;
    int total_marks;
    bool isPassed;

    void calculate_results()
    {
        if (SUBJECT_COUNT == 0 || MAX_SUB_MARKS == 0)
        {
            throw runtime_error("Division by zero error");
        }

        total_marks = 0;
        for (int i = 0; i < SUBJECT_COUNT; i++)
        {
            total_marks += marks[i];
        }

        percentage = ((float) total_marks / (SUBJECT_COUNT * MAX_SUB_MARKS)) * 100.0f;
        isPassed = (percentage >= PASS_PERCENTAGE);
    }

public:
    StudentRecord()
    {
        roll_number = 0;
        year = 0;
        first_name = "";
        last_name = "";
        percentage = 0.0f;
        total_marks = 0;
        isPassed = false;

        for (int i = 0; i < SUBJECT_COUNT; i++)
        {
            marks[i] = 0;
        }
    }

    int get_roll_number() const
    {
        return roll_number;
    }

    void input_data()
    {
        cout << "Roll Number: ";
        if (!(cin >> roll_number) || roll_number <= 0)
        {
            throw invalid_argument("Invalid Roll Number");
        }

        cout << "First Name: ";
        cin >> first_name;

        cout << "Last Name: ";
        cin >> last_name;

        cout << "Year (1-4): ";
        if (!(cin >> year) || year < 1 || year > 4)
        {
            throw invalid_argument("Invalid Year");
        }

        for (int i = 0; i < SUBJECT_COUNT; i++)
        {
            cout << subjects[i] << " Marks: ";
            if (!(cin >> marks[i]) || marks[i] < 0 || marks[i] > MAX_SUB_MARKS)
            {
                throw invalid_argument("Invalid Marks (must be 0 to 100)");
            }
        }

        calculate_results();
    }

    void display_report_card() const
    {
        cout << "\nRoll Number: " << roll_number << endl;
        cout << "Name: " << first_name << " " << last_name << endl;
        cout << "Year: " << year << endl;

        for (int i = 0; i < SUBJECT_COUNT; i++)
        {
            cout << subjects[i] << ": " << marks[i] << endl;
        }

        cout << "Total: " << total_marks << "/" << (SUBJECT_COUNT * MAX_SUB_MARKS) << endl;
        cout << "Percentage: " << percentage << "%" << endl;
        cout << "Status: " << (isPassed ? "PASS" : "FAIL") << endl;
    }

    friend void write_student(const StudentRecord& s, const string& filename, bool append);
    friend void read_all_students(const string& filename);
};

void write_student(const StudentRecord& s, const string& filename, bool append)
{
    ofstream file;
    if (append)
    {
        file.open(filename, ios::app);
    }
    else
    {
        file.open(filename);
    }

    if (!file.is_open())
    {
        throw runtime_error("Cannot open file: " + filename);
    }

    file << s.roll_number << " "
         << s.year << " "
         << s.first_name << " "
         << s.last_name;

    for (int i = 0; i < SUBJECT_COUNT; i++)
    {
        file << " " << s.marks[i];
    }
    file << "\n";

    file.close();
}

void read_all_students(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("File not found: " + filename);
    }

    StudentRecord s;
    bool has_records = false;

    while (true)
    {
        file >> s.roll_number;
        if (file.eof())
        {
            break;
        }

        file >> s.year >> s.first_name >> s.last_name;
        for (int i = 0; i < SUBJECT_COUNT; i++)
        {
            file >> s.marks[i];
        }

        s.calculate_results();
        s.display_report_card();
        has_records = true;
    }

    if (!has_records)
    {
        cout << "No records in file." << endl;
    }

    file.close();
}

int main()
{
    const string filename = "students.txt";
    int choice = 0;

    clear_terminal();

    while (true)
    {
        cout << "1. Write New File (Overwrite)\n";
        cout << "2. Append Student Record\n";
        cout << "3. Read All Report Cards\n";
        cout << "4. Test File Not Found Error\n";
        cout << "5. Exit\n";
        cout << "Choice: ";

        try
        {
            if (!(cin >> choice))
            {
                cin.clear();
                string bad_input;
                cin >> bad_input;
                throw invalid_argument("Choice must be a number");
            }

            clear_terminal();

            if (choice == 1)
            {
                StudentRecord s;
                s.input_data();
                write_student(s, filename, false);
                cout << "\nSaved to new file." << endl;
                back_to_menu();
            }
            else if (choice == 2)
            {
                StudentRecord s;
                s.input_data();
                write_student(s, filename, true);
                cout << "\nAppended to file." << endl;
                back_to_menu();
            }
            else if (choice == 3)
            {
                read_all_students(filename);
                back_to_menu();
            }
            else if (choice == 4)
            {
                read_all_students("does_not_exist.txt");
            }
            else if (choice == 5)
            {
                break;
            }
            else
            {
                throw invalid_argument("Invalid menu choice");
            }
        }
        catch (const exception& e)
        {
            cin.clear();
            cout << "\nError: " << e.what() << endl;
            back_to_menu();
        }
    }

    return 0;
}