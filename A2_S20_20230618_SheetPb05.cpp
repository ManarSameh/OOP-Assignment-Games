
#include "bits/stdc++.h"

using namespace std;

// mohamed ayman afifi
// 20230618
// problem 5: task manger

struct process_info
{
    int pid;
    string name;
    string session_name;
    int session;
    int memory_usage;

};

class process
{
    public:
    vector<process_info> processes;

    string trimRight(const string& str)
    {
        string result = str;
        result.erase(find_if(result.rbegin(), result.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), result.end()); 
        return result;
    }
    string removecommas(const string& str)
    {
        string result = str;
        result.erase(remove_if(result.begin(), result.end(), [](unsigned char ch) { return ch == ','; }), result.end()); 
        return result;
    }

    void loadprocess()
    {
        system("tasklist > output.txt");
        ifstream out("output.txt");
        string line;
        getline(out, line);
        getline(out, line);
        getline(out, line);
        while(getline(out, line))
        {
            process_info temp;
            temp.name = trimRight(line.substr(0, 25));
            temp.pid = stoi(line.substr(27, 8));
            temp.session_name = trimRight(line.substr(35, 16));
            temp.session = stoi(line.substr(53, 11));
            string memory = line.substr(65, 12);
            memory = removecommas(memory);
            temp.memory_usage = stoi(memory);

            processes.push_back(temp);
        }
        out.close();
    }
    void print()
    {
        cout << "Image Name                     PID Session Name                    Session#    Mem Usage\n";
        cout << "========================= ======== ================            =========== ============\n";
        for(auto &i : processes)
        {
            cout << i.name << setw(30 - i.name.size())  << i.pid << setw(20) << i.session_name << setw(22);
            cout << i.session << setw(15) << i.memory_usage << " K"<< endl;
        }
    }

    void sortByName()
    {
        sort(processes.begin(), processes.end(), [](const process_info& a, const process_info& b) { return a.name < b.name; });
    }
    void sortByMemory()
    {
        sort(processes.begin(), processes.end(), [](const process_info& a, const process_info& b) { return a.memory_usage < b.memory_usage; });
    }
    void sortBypid()
    {
        sort(processes.begin(), processes.end(), [](const process_info& a, const process_info& b) { return a.pid < b.pid; });
    }
};

int main()
{
    process p;
    string choice;
    cout << "----------------------------------------------------------------\n";
    cout << "choose the option you want\n";
    cout << "1. Load processes\n";
    cout << "2. Print processes\n";
    cout << "3. Sort by name\n";
    cout << "4. Sort by memory\n";
    cout << "5. Sort by PID\n";
    cout << "6. Exit\n";
    cout << "----------------------------------------------------------------\n";
    while(true)
    {
        cout << "Enter your choice: ";
        cin >> choice;
        if(choice == "1")
        {
            p.loadprocess();
        }
        else if(choice == "2")
        {
            p.print();
        }
        else if(choice == "3")
        {
            p.sortByName();
            p.print();
        }
        else if(choice == "4")
        {
            p.sortByMemory();
            p.print();
        }
        else if(choice == "5")
        {
            p.sortBypid();
            p.print();
        }
        else if(choice == "6")
        {
            break;
        }
        else{
            cout << "Invalid choice. Please try again.\n";
        }

    }


    return 0;
}
