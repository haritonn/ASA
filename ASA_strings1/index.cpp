#include <iostream>
#include <vector>
#include <string>

using namespace std;

//префикс-функция
vector<int> prefix_function(string s)
{
    int n = (int)s.size();
    vector<int> p(n, 0); 

    for (int i = 1; i < n; i++)
    {
        int j = p[i - 1]; 

        while (s[i] != s[j] && j > 0) 
            j = p[j - 1];

        if (s[i] == s[j]) //если символы совпали, то увеличиваем длину рассматриваемого префикса 
            p[i] = j + 1; 
    }

    return p; 
}

//z-функция 
vector<int> z_function(string s)
{
    int n = (int)s.size();
    vector<int> z(n, 0); 
    int l = 0, r = 0;    

    for (int i = 1; i < n; i++)
    {
        if (i <= r)                          
            z[i] = min(r - i + 1, z[i - l]); 
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) 
            z[i]++;                                    

        if (i + z[i] - 1 > r)
        { 
            r = i + z[i] - 1;
            l = i;
        }
    }
    z[0] = n;

    return z; 
}

int main()
{
    string s;
    cout << "Введите строку: "; 
    getline(cin, s);           

    vector<int> prefix = prefix_function(s);
    vector<int> z = z_function(s);

    cout << "Префикс-функция: ";
    for (int val : prefix)
        cout << val << " ";
    cout << "\n";

    cout << "Z-функция: ";
    for (int val : z)
        cout << val << " ";
    cout << "\n";

    return 0;
}
