#include <iostream>
#include <vector>
#include <string>

using namespace std;

//префикс-функция
vector<int> prefix_function(const string &s)
{
    int n = s.size();
    vector<int> p(n, 0); 

    for (int i = 1; i < n; i++)
    {
        int j = p[i - 1]; 

        while (j > 0 && s[i] != s[j]) 
            j = p[j - 1];

        if (s[i] == s[j]) 
            p[i] = j + 1; 
    }

    return p; 
}

//КМП
vector<int> kmp_search(const string &text, const string &pattern)
{
    string concatenated = pattern + "@" + text;    
    vector<int> p = prefix_function(concatenated); 
    vector<int> matches;                           

    for (int i = pattern.size() + 1; i < p.size(); i++)
    { 
        if (p[i] == pattern.size())
        {                                              
            matches.push_back(i - 2 * pattern.size()); 
        }
    }

    return matches; 
}

int main()
{
    string text, pattern;

    cout << "Введите исходную строку: ";  
    getline(cin, text);         
    cout << "Введите искомую подстроку: "; 
    getline(cin, pattern);      

    vector<int> matches = kmp_search(text, pattern);
    
    if (matches.size() == 0)
        cout << "Не удалось найти совпадения";
    else 
    {
        cout << "Результат (индекс(-ы), с которого начинается подстрока): ";
        for (int idx : matches)
        {
            cout << idx << " ";
        }
        cout << endl;
    }

    return 0;
}
