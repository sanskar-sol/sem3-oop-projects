#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <cctype>

#define VAULT_FILE "vault.dat"
#define VERIFY_TOKEN "VAULT_OK"

// Printable ASCII range constants (excludes space: '!' to '~')
#define ASCII_PRINT_START 33   // '!'
#define ASCII_PRINT_END   126  // '~'
#define ASCII_RANGE_SIZE  (ASCII_PRINT_END - ASCII_PRINT_START + 1) // 94 printable characters

using namespace std;

// HELPERS & TEMPLATE 

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

void print_title(string title)
{
    cout << "----- " << title << " -----" << endl;
}

template <typename T>
void print_stat(string label, T value)
{
    cout << "  " << label << ": " << value << endl;
}

// Printable-ASCII Vigenere/XOR-style cipher (keeps output space-free for file >>)
string cipher_text(string text, string key, bool encrypt)
{
    if (key.empty())
    {
        throw invalid_argument("Key cannot be empty");
    }

    for (size_t i = 0; i < text.size(); i++)
    {
        unsigned char c = text[i];
        if (c >= ASCII_PRINT_START && c <= ASCII_PRINT_END)
        {
            int shift = key[i % key.size()] % ASCII_RANGE_SIZE;
            int offset = c - ASCII_PRINT_START;
            int res = encrypt ? (offset + shift) % ASCII_RANGE_SIZE 
                              : (offset - shift + ASCII_RANGE_SIZE) % ASCII_RANGE_SIZE;
            text[i] = static_cast<char>(ASCII_PRINT_START + res);
        }
    }
    return text;
}

//  DATE & OPERATOR OVERLOADING 

struct Date
{
    int day, month, year;

    friend ostream& operator<<(ostream& os, const Date& d)
    {
        os << d.day << "/" << d.month << "/" << d.year;
        return os;
    }
};

// ABSTRACT BASE CLASS 

class VaultItem
{
protected:
    int id;
    string title;
    string category;
    Date created_at;
    static int total_created;

public:
    VaultItem(int item_id = 0, string t = "Untitled", string cat = "General", Date d = {1, 1, 2026})
        : id(item_id), title(t), category(cat), created_at(d)
    {
        total_created++;
    }

    VaultItem(const VaultItem& other)
        : id(other.id), title(other.title), category(other.category), created_at(other.created_at)
    {
        total_created++;
    }

    virtual ~VaultItem() {}

    int get_id() const { return id; }
    string get_title() const { return title; }
    string get_category() const { return category; }
    static int get_total_created() { return total_created; }

    void set_title(string t)
    {
        if (t.empty()) throw invalid_argument("Title cannot be empty");
        title = t;
    }

    // Pure virtual methods (Abstraction + Runtime Polymorphism)
    virtual string get_type() const = 0;
    virtual void input_data(string master_key) = 0;
    virtual void display(string master_key) const = 0;
    virtual void save(ofstream& out) const = 0;
};

int VaultItem::total_created = 0;

// DERIVED CLASS 1: CREDENTIAL 

class PasswordCredential : public VaultItem
{
private:
    string username;
    string encrypted_password;

public:
    PasswordCredential(int id = 0, string t = "", string cat = "General", Date d = {1, 1, 2026},
                       string user = "", string enc_pass = "")
        : VaultItem(id, t, cat, d), username(user), encrypted_password(enc_pass)
    {}

    string get_type() const override { return "CREDENTIAL"; }

    void input_data(string master_key) override
    {
        cout << "ID: ";
        if (!(cin >> id) || id <= 0) throw invalid_argument("Invalid ID");

        cout << "Service (no spaces): ";
        cin >> title;
        set_title(title);

        cout << "Category (e.g. Work, Social): ";
        cin >> category;

        cout << "Date (DD MM YYYY): ";
        if (!(cin >> created_at.day >> created_at.month >> created_at.year))
        {
            throw invalid_argument("Invalid date input");
        }

        cout << "Username: ";
        cin >> username;

        string raw_pass;
        cout << "Password (min 6 chars, no spaces): ";
        cin >> raw_pass;
        if (raw_pass.size() < 6) throw invalid_argument("Password too short (min 6)");

        encrypted_password = cipher_text(raw_pass, master_key, true);
    }

    void display(string master_key) const override
    {
        string pass = cipher_text(encrypted_password, master_key, false);
        cout << "[CRED] ID: " << id << " | " << title << " (" << category << ")"
             << " | User: " << username << " | Pass: " << pass
             << " | " << created_at << endl;
    }

    void save(ofstream& out) const override
    {
        out << "CRED " << id << " " << title << " " << category << " "
            << created_at.day << " " << created_at.month << " " << created_at.year << " "
            << username << " " << encrypted_password << "\n";
    }
};

// DERIVED CLASS 2: SECURE NOTE

class SecureNote : public VaultItem
{
private:
    string encrypted_note;

public:
    SecureNote(int id = 0, string t = "", string cat = "Notes", Date d = {1, 1, 2026}, string enc = "")
        : VaultItem(id, t, cat, d), encrypted_note(enc)
    {}

    string get_type() const override { return "NOTE"; }

    void input_data(string master_key) override
    {
        cout << "ID: ";
        if (!(cin >> id) || id <= 0) throw invalid_argument("Invalid ID");

        cout << "Title (no spaces): ";
        cin >> title;
        set_title(title);

        cout << "Category: ";
        cin >> category;

        cout << "Date (DD MM YYYY): ";
        if (!(cin >> created_at.day >> created_at.month >> created_at.year))
        {
            throw invalid_argument("Invalid date input");
        }

        string raw_note;
        cout << "Secret Note (no spaces, use _): ";
        cin >> raw_note;

        encrypted_note = cipher_text(raw_note, master_key, true);
    }

    void display(string master_key) const override
    {
        string content = cipher_text(encrypted_note, master_key, false);
        cout << "[NOTE] ID: " << id << " | " << title << " (" << category << ")"
             << " | Content: " << content << " | " << created_at << endl;
    }

    void save(ofstream& out) const override
    {
        out << "NOTE " << id << " " << title << " " << category << " "
            << created_at.day << " " << created_at.month << " " << created_at.year << " "
            << encrypted_note << "\n";
    }
};

// VAULT MANAGER (STL + FILE I/O) 

class VaultManager
{
private:
    vector<VaultItem*> items;
    map<string, int> category_counts;
    string master_key;

    void rebuild_counts()
    {
        category_counts.clear();
        for (VaultItem* item : items)
        {
            category_counts[item->get_category()]++;
        }
    }

public:
    ~VaultManager()
    {
        for (VaultItem* item : items) delete item;
    }

    void set_master_key(string key)
    {
        if (key.size() < 4) throw invalid_argument("Master password must be at least 4 chars");
        master_key = key;
    }

    string get_master_key() const { return master_key; }

    void add_item(VaultItem* item)
    {
        for (VaultItem* existing : items)
        {
            if (existing->get_id() == item->get_id())
            {
                delete item;
                throw invalid_argument("Duplicate ID");
            }
        }
        items.push_back(item);
        category_counts[item->get_category()]++;
    }

    void display_all() const
    {
        if (items.empty())
        {
            cout << "Vault is empty." << endl;
            return;
        }
        for (VaultItem* item : items)
        {
            item->display(master_key);
        }
    }

    void search_item(string keyword) const
    {
        bool found = false;
        for (VaultItem* item : items)
        {
            if (item->get_title().find(keyword) != string::npos ||
                item->get_category().find(keyword) != string::npos)
            {
                item->display(master_key);
                found = true;
            }
        }
        if (!found) cout << "No matching entries found." << endl;
    }

    void remove_item(int id)
    {
        auto it = find_if(items.begin(), items.end(), [id](VaultItem* item) {
            return item->get_id() == id;
        });
        if (it == items.end()) throw runtime_error("ID not found");

        delete *it;
        items.erase(it);
        rebuild_counts();
        cout << "Entry deleted." << endl;
    }

    void sort_alphabetically()
    {
        if (items.empty())
        {
            cout << "Vault is empty. Nothing to sort." << endl;
            return;
        }

        sort(items.begin(), items.end(), [](const VaultItem* a, const VaultItem* b) {
            return a->get_title() < b->get_title();
        });

        cout << "Vault entries sorted alphabetically (A-Z)!" << endl;
    }

    void show_stats() const
    {
        if (items.empty())
        {
            cout << "Vault is empty." << endl;
            return;
        }

        print_title("Vault Statistics");
        print_stat("Total Items", items.size());
        print_stat("Objects Created", VaultItem::get_total_created());
        for (auto const& pair : category_counts)
        {
            print_stat("Category [" + pair.first + "]", pair.second);
        }
    }

    void save_to_file(string filename) const
    {
        ofstream out(filename);
        if (!out.is_open()) throw runtime_error("Cannot open file to save");

        out << cipher_text(VERIFY_TOKEN, master_key, true) << "\n";
        for (VaultItem* item : items)
        {
            item->save(out);
        }
        out.close();
    }

    void load_from_file(string filename)
    {
        ifstream in(filename);
        if (!in.is_open()) throw runtime_error("Vault file not found");

        string token;
        if (!(in >> token) || cipher_text(token, master_key, false) != VERIFY_TOKEN)
        {
            throw runtime_error("Incorrect master password!");
        }

        string type;
        while (in >> type)
        {
            int id;
            string title, cat;
            Date d;
            in >> id >> title >> cat >> d.day >> d.month >> d.year;

            if (type == "CRED")
            {
                string user, enc_pass;
                in >> user >> enc_pass;
                items.push_back(new PasswordCredential(id, title, cat, d, user, enc_pass));
            }
            else if (type == "NOTE")
            {
                string enc_note;
                in >> enc_note;
                items.push_back(new SecureNote(id, title, cat, d, enc_note));
            }
        }
        rebuild_counts();
        in.close();
    }
};

// MAIN 

int main()
{
    VaultManager vault;
    clear_terminal();
    print_title("Password & Secret Vault");

    // Unlock or create vault
    while (true)
    {
        try
        {
            string master;
            ifstream check(VAULT_FILE);
            if (check.good())
            {
                check.close();
                cout << "Enter Master Password: ";
                cin >> master;
                vault.set_master_key(master);
                vault.load_from_file(VAULT_FILE);
                cout << "Vault unlocked!" << endl;
            }
            else
            {
                cout << "Create Master Password (min 4 chars): ";
                cin >> master;
                vault.set_master_key(master);
                vault.save_to_file(VAULT_FILE);
                cout << "New vault created!" << endl;
            }
            back_to_menu();
            break;
        }
        catch (const exception& e)
        {
            cout << "Error: " << e.what() << "\n" << endl;
        }
    }

    int choice = 0;
    while (true)
    {
        print_title("Vault Menu");
        cout << "1. Add Entry (Credential / Note)\n";
        cout << "2. View All Entries\n";
        cout << "3. Search Entries\n";
        cout << "4. Sort Entries (A-Z) & Stats\n";
        cout << "5. Delete Entry\n";
        cout << "6. Save & Exit\n";
        cout << "Choice: ";

        try
        {
            if (!(cin >> choice))
            {
                cin.clear();
                string bad;
                cin >> bad;
                throw invalid_argument("Choice must be a number");
            }
            clear_terminal();

            if (choice == 1)
            {
                int type_choice;
                cout << "1. Password Credential\n2. Secure Note\nType: ";
                if (!(cin >> type_choice) || (type_choice != 1 && type_choice != 2))
                {
                    throw invalid_argument("Invalid entry type");
                }

                VaultItem* item = nullptr;
                if (type_choice == 1)
                {
                    item = new PasswordCredential();
                }
                else
                {
                    item = new SecureNote();
                }
                try
                {
                    item->input_data(vault.get_master_key());
                    vault.add_item(item);
                    cout << "Added to vault!" << endl;
                }
                catch (...)
                {
                    delete item;
                    throw;
                }
                back_to_menu();
            }
            else if (choice == 2)
            {
                print_title("All Vault Entries");
                vault.display_all();
                back_to_menu();
            }
            else if (choice == 3)
            {
                string kw;
                cout << "Search keyword: ";
                cin >> kw;
                vault.search_item(kw);
                back_to_menu();
            }
            else if (choice == 4)
            {
                vault.sort_alphabetically();
                vault.show_stats();
                back_to_menu();
            }
            else if (choice == 5)
            {
                int id;
                cout << "Enter ID to delete: ";
                if (!(cin >> id)) throw invalid_argument("Invalid ID");
                vault.remove_item(id);
                back_to_menu();
            }
            else if (choice == 6)
            {
                vault.save_to_file(VAULT_FILE);
                cout << "Vault saved. Goodbye!" << endl;
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
