#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i, n) for (int i = 0; i < n; i++)

void signal(int& x)
{
    x++;
}
void wait(int& x)
{
    x--;
}

int main()
{

    int choice;
    set<string> reader;
    set<string> writer;

    while (1) {
        cout << "Choose an operation :";
        cout << "1 to Add a new reader\n";
        cout << "2 to Add a new writer\n";
        cout << "3 to remove existing reader\n";
        cout << "4 to remove existing writer\n";
        cin >> choice;
        if (choice == 3) {
            if (reader.size() == 0) {
                cout << "\nThere are NO readers.\n";
            } else {
                cout << "Name of the reader to be removed : ";
                string s;
                cin >> s;
                reader.erase(s);
                cout << "reader " << s << " is removed \n";
            }
        } else if (choice == 1) //
        {
            if (writer.size() != 0) {
                cout << "\nnew reader cannot be added as a writer is writing data.\n";
            } else {
                cout << "Name of the new reader: ";
                string s;
                cin >> s;
                reader.insert(s);
                cout << "The reader " << s << " is added and is now reading the data\n";
            }
        } else if (choice == 4) {
            if (writer.size() == 0) {
                cout << "\nThere are NO writers\n";
            } else {
                cout << "name of the writer to be removed : ";
                string s;
                cin >> s;
                writer.erase(s);
                cout << "The writer " << s << " is removed \n";
            }
        } else //
        {
            if (writer.size() != 0) {
                cout << "\nnew writer cannot be added as the data is being written by another writer " << *(writer.begin()) << "\n";
            } else if (reader.size() != 0) {
                cout << "\nThe data is currently being read by " << reader.size() << " readers.\n";
                cout << "So a new writer cannot be added\n";
            } else {
                cout << "name of the new writer: ";
                string s;
                cin >> s;
                writer.insert(s);
                cout << "The writer " << s << " was added \n";
            }
        }
    }
    return 0;
}
