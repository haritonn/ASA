#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<char, int> bad_character_rule(const string &pattern) {
    unordered_map<char, int> bad_char;
    int m = pattern.size();

    for (int i = 0; i < m; i++)
    {
        bad_char[pattern[i]] = i;
    }
    return bad_char;
}


vector<int> boyer_moore_search(const string &str, const string &pattern) {
    vector<int> matches; 
    int n = str.size();
    int m = pattern.size();

    if (m > n)
        return matches;

    unordered_map<char, int> bad_char = bad_character_rule(pattern);
    int s = 0; 

    while (s <= n - m){
        int j = m - 1;

        while (j >= 0 && pattern[j] == str[s + j])
            j--;        

        if (j < 0){
            matches.push_back(s - 1);                             
            s += (s + m < n) ? m - bad_char[str[s + m]] : 1; 
        }

        else
            s += max(1, j - bad_char[str[s + j]]); 
    }

    return matches; 
}

int main() {

    string str, pattern;
    cout << "Исходная строка: ";  getline(cin, str);         

    cout << "Подстрока: ";
    cin.ignore(); 
    getline(cin, pattern);      

    vector<int> matches = boyer_moore_search(str, pattern);
    cout << "Результат: ";
    for (int idx : matches)
        cout << idx << " ";
    
    
    cout << endl;
    return 0;
}