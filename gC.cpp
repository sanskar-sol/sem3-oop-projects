#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
using namespace std;

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
    string temp;
    cout << "\nEnter any key to go back to menu: ";
    cin >> temp;
    clear_terminal();
}

struct Book
{
    int id;
    string title;
    string author;

    void input_data()
    {
        cout << "Book ID: ";
        if (!(cin >> id) || id <= 0)
        {
            throw invalid_argument("Invalid Book ID");
        }
        cout << "Title: ";
        cin >> title;
        cout << "Author: ";
        cin >> author;
    }

    void display() const
    {
        cout << "ID: " << id << " | Title: " << title << " | Author: " << author << endl;
    }
};

struct Journal
{
    int id;
    string title;
    int volume;

    void input_data()
    {
        cout << "Journal ID: ";
        if (!(cin >> id) || id <= 0)
        {
            throw invalid_argument("Invalid Journal ID");
        }
        cout << "Title: ";
        cin >> title;
        cout << "Volume: ";
        if (!(cin >> volume) || volume <= 0)
        {
            throw invalid_argument("Invalid Volume");
        }
    }

    void display() const
    {
        cout << "ID: " << id << " | Title: " << title << " | Volume: " << volume << endl;
    }
};

struct Magazine
{
    int id;
    string title;
    int issue_number;

    void input_data()
    {
        cout << "Magazine ID: ";
        if (!(cin >> id) || id <= 0)
        {
            throw invalid_argument("Invalid Magazine ID");
        }
        cout << "Title: ";
        cin >> title;
        cout << "Issue Number: ";
        if (!(cin >> issue_number) || issue_number <= 0)
        {
            throw invalid_argument("Invalid Issue Number");
        }
    }

    void display() const
    {
        cout << "ID: " << id << " | Title: " << title << " | Issue: " << issue_number << endl;
    }
};

// template for generic searching by id using STL iterators
template <typename T>
typename vector<T>::iterator find_item_by_id(vector<T>& items, int target_id)
{
    return find_if(items.begin(), items.end(), [target_id](const T& item)
    {
        return item.id == target_id;
    });
}

// class template with a non-type template parameter (MAX_CAPACITY)
template <typename T, int MAX_CAPACITY>
class Inventory
{
    vector<T> items;
    map<int, string> id_index;

public:
    void add_item(const T& item)
    {
        if (items.size() >= MAX_CAPACITY)
        {
            throw runtime_error("Inventory capacity limit reached");
        }
        if (id_index.find(item.id) != id_index.end())
        {
            throw invalid_argument("Duplicate ID already exists");
        }

        items.push_back(item);
        id_index[item.id] = item.title;
    }

    void display_all()
    {
        if (items.empty())
        {
            cout << "No items in inventory." << endl;
            return;
        }

        sort(items.begin(), items.end(), [](const T& a, const T& b)
        {
            return a.id < b.id;
        });

        for (typename vector<T>::iterator it = items.begin(); it != items.end(); ++it)
        {
            it->display();
        }
    }

    void search_item(int target_id)
    {
        typename vector<T>::iterator it = find_item_by_id(items, target_id);
        if (it != items.end())
        {
            cout << "Item Found:" << endl;
            it->display();
        }
        else
        {
            cout << "Item with ID " << target_id << " not found." << endl;
        }
    }

    void remove_item(int target_id)
    {
        typename vector<T>::iterator it = find_item_by_id(items, target_id);
        if (it == items.end())
        {
            throw runtime_error("Cannot remove: ID not found");
        }

        id_index.erase(target_id);
        items.erase(it);
        cout << "Item removed successfully." << endl;
    }
};

template <typename T, int MAX_CAPACITY>
void manage_category(Inventory<T, MAX_CAPACITY>& inv, const string& category_name)
{
    int sub_choice = 0;

    while (true)
    {
        cout << "--- " << category_name << " Inventory (Max: " << MAX_CAPACITY << ") ---\n";
        cout << "1. Add " << category_name << "\n";
        cout << "2. View All " << category_name << "s\n";
        cout << "3. Search by ID\n";
        cout << "4. Remove by ID\n";
        cout << "5. Back to Main Menu\n";
        cout << "Choice: ";

        if (!(cin >> sub_choice))
        {
            cin.clear();
            string bad_input;
            cin >> bad_input;
            throw invalid_argument("Choice must be a number");
        }

        clear_terminal();

        if (sub_choice == 1)
        {
            T item;
            item.input_data();
            inv.add_item(item);
            cout << "\n" << category_name << " added successfully." << endl;
            back_to_menu();
        }
        else if (sub_choice == 2)
        {
            inv.display_all();
            back_to_menu();
        }
        else if (sub_choice == 3)
        {
            int id;
            cout << "Enter ID to search: ";
            if (!(cin >> id))
            {
                throw invalid_argument("Invalid ID");
            }
            inv.search_item(id);
            back_to_menu();
        }
        else if (sub_choice == 4)
        {
            int id;
            cout << "Enter ID to remove: ";
            if (!(cin >> id))
            {
                throw invalid_argument("Invalid ID");
            }
            inv.remove_item(id);
            back_to_menu();
        }
        else if (sub_choice == 5)
        {
            break;
        }
        else
        {
            throw invalid_argument("Invalid choice");
        }
    }
}

int main()
{
    Inventory<Book, 50> book_inventory;
    Inventory<Journal, 30> journal_inventory;
    Inventory<Magazine, 20> magazine_inventory;

    int choice = 0;
    clear_terminal();

    while (true)
    {
        cout << "=== Generic Library Inventory System ===\n";
        cout << "1. Manage Books\n";
        cout << "2. Manage Journals\n";
        cout << "3. Manage Magazines\n";
        cout << "4. Exit\n";
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
                manage_category(book_inventory, "Book");
            }
            else if (choice == 2)
            {
                manage_category(journal_inventory, "Journal");
            }
            else if (choice == 3)
            {
                manage_category(magazine_inventory, "Magazine");
            }
            else if (choice == 4)
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