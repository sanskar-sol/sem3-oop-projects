---
marp: true
theme: default
paginate: true
style: |
  :root {
    --color-background: #fbf9f5;
    --color-foreground: #191817;
    --color-muted: #797670;
    --color-accent: #c96442;
    --color-code-bg: #f4efe6;
    --color-code-border: #e6dfd3;
  }

  section {
    display: flex;
    flex-direction: column;
    justify-content: flex-start;
    font-family: -apple-system, BlinkMacSystemFont, "SF Pro Text", "SF Pro Display", "Helvetica Neue", Helvetica, Arial, sans-serif;
    font-size: 20px;
    line-height: 1.45;
    letter-spacing: -0.012em;
    color: #191817;
    background-color: #fbf9f5;
    padding: 46px 60px;
  }

  /* Academic Lead Slide */
  section.lead {
    background-color: #fbf9f5;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    text-align: center;
  }

  section.lead h1 {
    font-size: 44px;
    font-weight: 700;
    letter-spacing: -0.025em;
    color: #191817;
    margin-bottom: 8px;
    border: none;
  }

  section.lead h3 {
    font-size: 22px;
    font-weight: 400;
    color: #c96442;
    margin-bottom: 24px;
  }

  section.lead p {
    color: #797670;
    font-size: 17px;
    line-height: 1.5;
  }

  /* Slide Typography */
  h1 {
    font-weight: 600;
    letter-spacing: -0.02em;
    color: #191817;
  }

  h2 {
    font-size: 31px;
    font-weight: 600;
    letter-spacing: -0.02em;
    color: #191817;
    border-bottom: none;
    margin-bottom: 4px;
    padding-bottom: 0;
  }

  .subtitle {
    font-size: 16px;
    font-weight: 400;
    color: #797670;
    margin-bottom: 16px;
  }

  p, li {
    font-weight: 400;
    color: #2b2927;
  }

  li {
    margin-bottom: 8px;
  }

  strong {
    font-weight: 600;
    color: #191817;
  }

  /* Anthropic-style Code Containers */
  pre {
    background: #f4efe6;
    border: 1px solid #e7e0d3;
    border-radius: 12px;
    box-shadow: 0 1px 4px rgba(0, 0, 0, 0.02);
    padding: 14px 18px;
    font-size: 14.5px;
    line-height: 1.32;
  }

  code, pre code {
    font-family: "SF Mono", Menlo, Consolas, Monaco, monospace;
    font-size: 14px;
    color: #191817;
  }

  p code, li code, td code {
    background: #eee8dc;
    border-radius: 5px;
    padding: 2px 6px;
    font-size: 0.88em;
  }

  /* Editorial Table Styling */
  table {
    width: 100%;
    border-collapse: collapse;
    margin-top: 10px;
    font-size: 16px;
  }

  th {
    text-align: left;
    font-weight: 600;
    color: #191817;
    background: #f4efe6;
    border-bottom: 2px solid #d9d0c1;
    padding: 10px 12px;
  }

  td {
    color: #2b2927;
    border-bottom: 1px solid #e7e0d3;
    padding: 10px 12px;
    vertical-align: top;
  }

  .caption {
    font-size: 14px;
    color: #797670;
    margin-top: 10px;
  }

  /* Link Styling */
  a {
    color: #c96442;
    text-decoration: none;
  }
  a:hover {
    text-decoration: underline;
  }
---

<!-- Slide 1: Title Slide -->
<!-- _class: lead -->

# Object-Oriented Programming in C++
### Integrated Systems: Groups A, B, and C

**Course:** Object-Oriented Programming (B.Tech CSE, Semester 3)  

**Team Members:**  
Sanskar Virat  
Kunal Bagal  
Mayuri Dhavalikar  
Prachi Salunke  

**GitHub Repository:**  
[github.com/sanskar-sol/Assignment-employee-management-system](https://github.com/sanskar-sol/Assignment-employee-management-system)

---

<!-- Slide 2: Assignment Progression Overview -->

## Assignment Progression Overview
<div class="subtitle">From foundational class design to generic programming and STL</div>

- **Group A: Employee Management System (`employee.cpp`)**
  Encapsulation, composition (*has-a* relationships), constructor initializer lists, `static` members, and `switch`-driven menu traversal.
- **Group B: Student Report Card System (`gB.cpp`)**
  Persistent file I/O (`ifstream`, `ofstream`), `friend` serialization functions, and structured exception handling (`try`, `catch`, `throw`).
- **Group C: Generic Library Inventory System (`gC.cpp`)**
  Function and class templates, non-type template parameters, STL containers (`vector`, `map`), iterators, and lambda-based algorithms.

---

<!-- Slide 3: Group A Objectives & OOP Concepts -->

## Group A: Employee Management System
<div class="subtitle">Core OOP paradigms applied in employee.cpp</div>

- **Classes and Data Hiding:** Declaring state attributes `private` and exposing controlled `public` accessors and mutators.
- **Composition (Has-A Pattern):** Partitioning employee data into `EmployeeIdentity` and `EmployeeProfile` instead of a monolithic class.
- **Constructor Member Initializer Lists:** Direct member initialization prior to constructor body execution.
- **Copy Constructors:** Explicit member-wise copy semantics for sub-object duplication.
- **Static and Mutable Members:** Tracking class-wide active records (`static int count`) and read diagnostics (`mutable int access_count`).

---

<!-- Slide 4: Group A Sub-Objects -->

## Group A: Identity and Profile Sub-Objects
<div class="subtitle">Encapsulating credentials and guarded business validation</div>

```cpp
struct Date { int day, month, year; };

class EmployeeIdentity {
private:
    int employee_id;
    Date date_of_hire;
public:
    EmployeeIdentity(int emp_id = 0, Date date = {0, 0, 0})
        : employee_id(emp_id), date_of_hire(date) {}
    EmployeeIdentity(EmployeeIdentity& emp_id) {
        employee_id = emp_id.employee_id;
        date_of_hire = emp_id.date_of_hire;
    }
    int get_employee_id() const { return employee_id; }
};

class EmployeeProfile {
private:
    string department, job_title;
    long salary;
    bool is_valid_amount(int amount) { return amount > 0; }
public:
    void set_salary(long sal) { if (is_valid_amount(sal)) salary = sal; }
};
```

---

<!-- Slide 5: Group A Composite Class & Static State -->

## Group A: Composite Entity and Static Scope
<div class="subtitle">Aggregating sub-objects with delegation and class-wide counters</div>

```cpp
class Employee {
private:
    static int count;
    string name;
    int age;
    mutable int access_count = 0; // Modifiable inside const methods
    EmployeeIdentity emp_id;      // Composition
    EmployeeProfile emp_profile;  // Composition
public:
    Employee(string _name = "Unknown", int _age = 0,
             EmployeeIdentity _emp_id = EmployeeIdentity(),
             EmployeeProfile _emp_profile = EmployeeProfile())
        : name(_name), age(_age), emp_id(_emp_id), emp_profile(_emp_profile) {}

    static int get_count() { return count; }
    static void add_count() { count++; }
    void set_salary(long sal) { emp_profile.set_salary(sal); } // Delegation

    void print_info() const {
        cout << "Name: " << name << " | Salary: " << this->get_salary() << endl;
        access_count++;
    }
};
int Employee::count = 0;
```

---

<!-- Slide 6: Group A Menu-Driven Switch Traversal -->

## Group A: Menu-Driven `switch` Traversal
<div class="subtitle">State-driven console navigation in main()</div>

```cpp
int main() {
    Employee e[20];
    int menu_index = 0;
    bool run = true;

    while (run) {
        switch (menu_index) {
            case 0: // Main Menu
                clear_screen();
                print_title("Employee Management System");
                cin >> menu_index;
                break;
            case 1: { // Instantiate sub-objects and compose Employee
                EmployeeIdentity temp_id(tempid, {d, m, y});
                EmployeeProfile temp_prof(tdep, tsalary, title);
                e[Employee::get_count()] = Employee(tname, tage, temp_id, temp_prof);
                Employee::add_count();
                cin >> menu_index;
                break;
            }
            case 2: // Linear search by ID -> e[i].set_salary(tsalary)
            case 3: // Linear search by ID -> e[i].print_info()
            default: run = false; break;
        }
    }
}
```

---

<!-- Slide 7: Group A Sample Execution -->

## Group A: Sample Execution
<div class="subtitle">Console verification of registration and record lookup</div>

```text
-----Adding Employee Information-----
Enter Employee Name(No spaces): AliceSmith
Enter Employee Age: 29
Enter Employee Id: 201
Enter Date of Hire (Format-> dd mm yy): 12 04 2022
Enter the Department(No spaces): Cybersecurity
Enter the Job Title(No spaces): SecurityAnalyst
Enter the salary: 82000
Employee Information Added
```

```text
-----Print Employee Information-----
Enter the EmployeeID: 201
Employee Found!

Name: AliceSmith | Age: 29 | Salary: 82000
Department: Cybersecurity | Job_Title: SecurityAnalyst
```

---

<!-- Slide 8: Group B Objectives & Architecture -->

## Group B: Student Report Card System
<div class="subtitle">Persistent file I/O and structured exception handling in gB.cpp</div>

- **Problem Statement:** Manage student academic records (`EMMD`, `DSA`, `OOP`, `COA`) with file reading, writing, and appending while handling runtime failures safely.
- **Core C++ Mechanisms Used:**
  - **File Streams (`<fstream>`):** `ofstream` (overwrite and `ios::app` append modes) and `ifstream` against `students.txt`.
  - **Exception Handling (`<stdexcept>`):** Throwing and catching `std::invalid_argument` and `std::runtime_error`.
  - **Friend Functions:** Granting `write_student()` and `read_all_students()` direct access to `StudentRecord` private members.

---

<!-- Slide 9: Group B StudentRecord Validation & Division by Zero -->

## Group B: Validation and Division-by-Zero Guard
<div class="subtitle">Defensive input checks and result computation in StudentRecord</div>

```cpp
class StudentRecord {
    int roll_number, year, marks[SUBJECT_COUNT], total_marks;
    string first_name, last_name;
    float percentage;
    bool isPassed;

    void calculate_results() {
        if (SUBJECT_COUNT == 0 || MAX_SUB_MARKS == 0)
            throw runtime_error("Division by zero error");
        total_marks = 0;
        for (int i = 0; i < SUBJECT_COUNT; i++) total_marks += marks[i];
        percentage = ((float)total_marks / (SUBJECT_COUNT * MAX_SUB_MARKS)) * 100.0f;
        isPassed = (percentage >= PASS_PERCENTAGE);
    }
public:
    void input_data() {
        if (!(cin >> roll_number) || roll_number <= 0)
            throw invalid_argument("Invalid Roll Number");
        // ... name input ...
        if (!(cin >> year) || year < 1 || year > 4)
            throw invalid_argument("Invalid Year");
        for (int i = 0; i < SUBJECT_COUNT; i++)
            if (!(cin >> marks[i]) || marks[i] < 0 || marks[i] > MAX_SUB_MARKS)
                throw invalid_argument("Invalid Marks (must be 0 to 100)");
        calculate_results();
    }
    friend void write_student(const StudentRecord& s, const string& filename, bool append);
    friend void read_all_students(const string& filename);
};
```

---

<!-- Slide 10: Group B File I/O & Friend Serialization -->

## Group B: File I/O and `friend` Serialization
<div class="subtitle">Writing, appending, and reading records with stream validation</div>

```cpp
void write_student(const StudentRecord& s, const string& filename, bool append) {
    ofstream file;
    if (append) file.open(filename, ios::app);
    else        file.open(filename);

    if (!file.is_open())
        throw runtime_error("Cannot open file: " + filename);

    file << s.roll_number << " " << s.year << " "
         << s.first_name << " " << s.last_name;
    for (int i = 0; i < SUBJECT_COUNT; i++) file << " " << s.marks[i];
    file << "\n";
    file.close();
}

void read_all_students(const string& filename) {
    ifstream file(filename);
    if (!file.is_open())
        throw runtime_error("File not found: " + filename);

    StudentRecord s;
    while (file >> s.roll_number) {
        file >> s.year >> s.first_name >> s.last_name;
        for (int i = 0; i < SUBJECT_COUNT; i++) file >> s.marks[i];
        s.calculate_results();
        s.display_report_card();
    }
    file.close();
}
```

---

<!-- Slide 11: Group B Exception Handling in main() -->

## Group B: Exception Handling in `main()`
<div class="subtitle">Centralized try-catch block with stream state recovery</div>

```cpp
try {
    if (!(cin >> choice)) {
        cin.clear();
        string bad_input;
        cin >> bad_input;
        throw invalid_argument("Choice must be a number");
    }
    if (choice == 1 || choice == 2) {
        StudentRecord s;
        s.input_data();
        write_student(s, filename, choice == 2); // false: overwrite, true: append
    }
    else if (choice == 3) read_all_students(filename);
    else if (choice == 4) read_all_students("does_not_exist.txt"); // Error demo
    else if (choice == 5) break;
    else throw invalid_argument("Invalid menu choice");
}
catch (const exception& e) {
    cin.clear();
    cout << "\nError: " << e.what() << endl;
    back_to_menu();
}
```

---

<!-- Slide 12: Group B Sample Execution & Error Output -->

## Group B: Sample Execution and Error Recovery
<div class="subtitle">Report card generation alongside caught runtime exceptions</div>

```text
Roll Number: 14
Name: Rohan Kulkarni
Year: 2
EMMD: 78
DSA: 84
OOP: 91
COA: 75
Total: 328/400
Percentage: 82%
Status: PASS
```

```text
Choice: 4

Error: File not found: does_not_exist.txt

Press Enter to go back to menu...
```

---

<!-- Slide 13: Group C Objectives & Generic Design -->

## Group C: Generic Library Inventory System
<div class="subtitle">Compile-time polymorphism and STL integration in gC.cpp</div>

- **Problem Statement:** Manage books, journals, and magazines generically without duplicating storage, search, or menu logic.
- **Core C++ Mechanisms Used:**
  - **Class Templates & Non-Type Parameters:** `Inventory<T, MAX_CAPACITY>` enforces per-category capacity bounds at compile time.
  - **Function Templates:** `find_item_by_id<T>()` and `manage_category<T, MAX_CAPACITY>()` generalize search and UI workflows.
  - **STL Containers & Algorithms:** `std::vector<T>`, `std::map<int, string>`, `std::find_if`, `std::sort`, iterators, and lambda expressions.

---

<!-- Slide 14: Group C Domain Entities -->

## Group C: Uniform Domain Entities
<div class="subtitle">Structural contract across Book, Journal, and Magazine</div>

```cpp
struct Book {
    int id;
    string title, author;
    void input_data() { /* validates id > 0, reads title and author */ }
    void display() const {
        cout << "ID: " << id << " | Title: " << title << " | Author: " << author << endl;
    }
};

struct Journal {
    int id, volume;
    string title;
    void input_data() { /* validates id > 0 and volume > 0 */ }
    void display() const {
        cout << "ID: " << id << " | Title: " << title << " | Volume: " << volume << endl;
    }
};

struct Magazine {
    int id, issue_number;
    string title;
    void input_data() { /* validates id > 0 and issue_number > 0 */ }
    void display() const {
        cout << "ID: " << id << " | Title: " << title << " | Issue: " << issue_number << endl;
    }
};
```

---

<!-- Slide 15: Group C Function Template & STL Algorithms -->

## Group C: Function Template and STL Algorithms
<div class="subtitle">Iterator-based searching and sorting with lambda predicates</div>

```cpp
// Function template returning a vector<T> iterator
template <typename T>
typename vector<T>::iterator find_item_by_id(vector<T>& items, int target_id) {
    return find_if(items.begin(), items.end(), [target_id](const T& item) {
        return item.id == target_id;
    });
}
```

- **Why `typename`?** Required to tell the compiler that `vector<T>::iterator` is a dependent type rather than a static member.
- **STL `std::find_if`:** Scans `[items.begin(), items.end())` using a lambda capturing `target_id`.
- **STL `std::sort` in `display_all()`:** Orders items ascending by `id` via `[](const T& a, const T& b) { return a.id < b.id; }` before iterator traversal.

---

<!-- Slide 16: Group C Class Template Inventory -->

## Group C: `Inventory<T, MAX_CAPACITY>` Class Template
<div class="subtitle">Non-type template parameter with dual STL containers</div>

```cpp
template <typename T, int MAX_CAPACITY>
class Inventory {
    vector<T> items;
    map<int, string> id_index; // O(log N) duplicate-ID lookup
public:
    void add_item(const T& item) {
        if (items.size() >= MAX_CAPACITY)
            throw runtime_error("Inventory capacity limit reached");
        if (id_index.find(item.id) != id_index.end())
            throw invalid_argument("Duplicate ID already exists");

        items.push_back(item);
        id_index[item.id] = item.title;
    }

    void remove_item(int target_id) {
        typename vector<T>::iterator it = find_item_by_id(items, target_id);
        if (it == items.end())
            throw runtime_error("Cannot remove: ID not found");
        id_index.erase(target_id);
        items.erase(it);
    }
};
```

---

<!-- Slide 17: Group C Generic Controller & main() -->

## Group C: Generic Controller and Instantiation
<div class="subtitle">Reusing one submenu workflow across three concrete types</div>

```cpp
template <typename T, int MAX_CAPACITY>
void manage_category(Inventory<T, MAX_CAPACITY>& inv, const string& category_name) {
    // Handles Add, View All (sorted), Search by ID, and Remove by ID for any T
    if (sub_choice == 1) { T item; item.input_data(); inv.add_item(item); }
    else if (sub_choice == 2) { inv.display_all(); }
    else if (sub_choice == 3) { inv.search_item(id); }
    else if (sub_choice == 4) { inv.remove_item(id); }
}

int main() {
    Inventory<Book, 50> book_inventory;
    Inventory<Journal, 30> journal_inventory;
    Inventory<Magazine, 20> magazine_inventory;

    // Dispatches menu choice 1, 2, or 3 to manage_category(...)
    if (choice == 1)      manage_category(book_inventory, "Book");
    else if (choice == 2) manage_category(journal_inventory, "Journal");
    else if (choice == 3) manage_category(magazine_inventory, "Magazine");
}
```

---

<!-- Slide 18: Group C Sample Execution & STL Benefits -->

## Group C: Sample Execution and Design Benefits
<div class="subtitle">Runtime verification and template advantages</div>

```text
--- Book Inventory (Max: 50) ---
1. Add Book | 2. View All Books | 3. Search by ID | 4. Remove by ID | 5. Back
Choice: 2
ID: 101 | Title: CleanCode | Author: RobertMartin
ID: 204 | Title: EffectiveC++ | Author: ScottMeyers
```

- **Zero Code Duplication:** A single `Inventory` class template and `manage_category` function template serve `Book`, `Journal`, and `Magazine`.
- **Compile-Time Capacity Safety:** Non-type parameter `MAX_CAPACITY` binds distinct upper limits (`50`, `30`, `20`) per instantiation.
- **Efficient Lookup:** `std::map` prevents duplicate IDs in $O(\log N)$ time while `std::vector` keeps contiguous storage for sorting.

---

<!-- Slide 19: Comparative Summary -->

## Comparative Summary Across Groups A, B, and C
<div class="subtitle">Progression of C++ paradigms and engineering trade-offs</div>

| Dimension | Group A (`employee.cpp`) | Group B (`gB.cpp`) | Group C (`gC.cpp`) |
| :--- | :--- | :--- | :--- |
| **Domain** | Employee Management | Student Report Cards | Library Inventory |
| **Core C++ Focus** | Classes, Composition, `static` | File I/O, `friend`, Exceptions | Templates, STL, Lambdas |
| **Data Storage** | Fixed array `Employee e[20]` | Text file `students.txt` | `std::vector<T>` + `std::map` |
| **Error Handling** | Validation helper (`bool`) | `try`/`catch`/`throw` (`stdexcept`) | Exceptions + capacity guards |
| **Extensibility** | Add sub-objects via composition | Add fields to `StudentRecord` | Instantiate `Inventory<T, N>` |

---

<!-- Slide 20: Q&A / Thank You -->
<!-- _class: lead -->

# Thank You

### Questions and Discussion

**Object-Oriented Programming with C++** · Groups A, B, and C  
*Ready for Demonstration*

[github.com/sanskar-sol/Assignment-employee-management-system](https://github.com/sanskar-sol/Assignment-employee-management-system)
