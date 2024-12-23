#include "bits/stdc++.h"

using namespace std;

/**
 * name: mohamed ayman afifi
 * id: 20230618
 * problem: 2
 **/

class StringSet
{
    private:
        vector<string> strSet;
    
    public:
    StringSet(string fileOrString = ""){
        if(ifstream(fileOrString)){
            ifstream inputFile(fileOrString);
            string line;
            while(inputFile >> line){
                string word = "";
                for( char c : line)
                {
                    if(isalpha(c)){
                        c = tolower(c);
                        word += c;
                    }
                }
                if (find(strSet.begin(), strSet.end(), word) == strSet.end())
                strSet.push_back(word);
            }
            inputFile.close();
        } else {
            string word = "";
            for(int i = 0; i < fileOrString.size() + 1; i++)
            {
                char c = fileOrString[i];
                if(isalpha(c)){
                    c = tolower(c);
                    word += c;
                }
                else
                {
                    if(word != ""){
                        if (find(strSet.begin(), strSet.end(), word) == strSet.end())
                        strSet.push_back(word);
                    }
                    word = "";
                }
            }
        }
    }

    void printSet(){
        cout << "String Set: {";
        for(auto word : strSet){
            cout << word << ", ";
        }
        cout << "}" << endl;
    }

    void addWord(string word){
        string newword = "";
        for(char c : word){
            if(isalpha(c)){
            c = tolower(c);
            newword += c;
            }
        }
        strSet.push_back(newword);
    }

    void addManyWords(string words)
    {
            string word = "";
            for(int i = 0; i < words.size() + 1; i++)
            {
                char c = words[i];
                if(isalpha(c)){
                    c = tolower(c);
                    word += c;
                }
                else
                {
                    if(word != ""){
                        if (find(strSet.begin(), strSet.end(), word) == strSet.end())
                        strSet.push_back(word);
                    }
                    word = "";
                }
            }
    }

    void removeWord(string word){
        strSet.erase(remove(strSet.begin(), strSet.end(), word), strSet.end());
    }

    void clear() {
        strSet.clear();
    }

    int size() {
        return strSet.size();
    }
    
    StringSet operator +(StringSet &set)
    {
        StringSet result;
        for(auto word : strSet)
        {
            result.addWord(word);
        }
        for(auto word : set.strSet)
        {
            if (find(strSet.begin(), strSet.end(), word) == strSet.end())
            result.addWord(word);
        }
        return result;
    }

    StringSet operator *(StringSet &set)
    {
        StringSet result;
        for(auto word : strSet)
        {
            if(find(set.strSet.begin(), set.strSet.end(), word) != set.strSet.end())
            {
                result.addWord(word);
            }
        }
        return result;
    }

    float similarity(StringSet &set)
    {
        StringSet intersect = set * *this;
        if(intersect.size() == 0) return 0;
        float result = (float)intersect.size() / (sqrt(set.size()) * sqrt(size()));
        return result;
    }
};

int main()
{
    string control;
    cout << "----------------------------------------------------------------\n";
        cout << "1. Exit\n";
        cout << "2. Create two string sets from a file or string\n";
        cout << "(if the file don't exist the file name will be treated as string)\n";
        cout << "(don't forget to enter the extension Ex: file.txt)\n";
        cout << "3. Print the string sets\n";
        cout << "4. Add a word to the sets\n";
        cout << "5. Add many words to the sets\n";
        cout << "6. Remove a word from the sets\n";
        cout << "7. Clear the sets\n";
        cout << "8. Get the size of the sets\n";
        cout << "9. Union of two sets\n";
        cout << "10. Intersection of two sets\n";
        cout << "11. Similarity between two sets\n";
        cout << "any thing else will be invalid" << endl;
        cout << "----------------------------------------------------------------";
        StringSet set1, set2;
    while(control != "1")
    {
        cout << "\nChoose an option:\n";
        cin >> control;
        if(control == "2")
        {
            cout << "(if the file don't exist the file name will be treated as string)\n";
            cout << "(don't forget to enter the extension Ex: file.txt)\n";
            string filename;
            cout << "Enter the first file name or string: ";
            cin.ignore();
            getline(cin, filename);
            set1 = StringSet(filename);
            cout << "Enter the second file name or string: ";
            getline(cin, filename);
            cout << filename << endl;
            set2 = StringSet(filename);
            
        }
        else if(control == "3")
        {
            cout << "first set contains: " << endl;
            set1.printSet();
            cout << "second set contains: " << endl;
            set2.printSet();
        }
        else if(control == "4")
        {
            string word;
            cout << "Enter a word to add to first set: " << endl;
            cin >> word;
            set1.addWord(word);
            cout << "Ender the word you want to add to the second set: " << endl;
            cin >> word;
            set2.addWord(word);
        }
        else if(control == "5")
        {
            string words;
            cout << "Enter many words to add in the first set: ";
            cin.ignore();
            getline(cin, words);
            set1.addManyWords(words);
            cout << "Enter many words to add in the second set: ";
            getline(cin, words);
            set2.addManyWords(words);
        }
        else if(control == "6")
        {
            string word;
            cout << "Enter a word to remove from first set: ";
            cin >> word;
            set1.removeWord(word);
            cout << "Enter a word to remove from the second set: ";
            cin >> word;
            set2.removeWord(word);
        }
        else if(control == "7")
        {
            cout << "Which set you want to clear?\n1. for the first\n 2. for the second\n";
            string choice;
            cin >> choice;
            if(choice == "1") set1.clear();
            else if(choice == "2") set2.clear();
            else cout << "Invalid choice" << endl;
        }
        else if(control == "8")
        {
            cout << "Size of the first set: " << set1.size() << endl;
            cout << "Size of the second set: " << set2.size() << endl;
        }
        else if(control == "9")
        {
            StringSet unionSet = set1 + set2;
            cout << "Union of two sets: " << endl;
            unionSet.printSet();
        }
        else if(control == "10")
        {
            StringSet intersectionSet = set1 * set2;
            cout << "Intersection of two sets: " << endl;
            intersectionSet.printSet();
        }
        else if(control == "11")
        {
            float similarityScore = set1.similarity(set2);
            cout << "Similarity between two sets: " << similarityScore << endl;
        }
        else if (control == "1")
        {
            cout << "Exiting the program" << endl;
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
    }
    return 0;
}
