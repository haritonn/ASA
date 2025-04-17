#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Функция для вычисления префиксной функции
vector<int> prefix_function(const string &s)
{
    int n = s.size();
    vector<int> p(n, 0); // Инициализация вектора префиксов

    for (int i = 1; i < n; i++)
    {
        int j = p[i - 1]; // Текущий индекс префикса

        while (j > 0 && s[i] != s[j]) // Поиск корректного префикса
            j = p[j - 1];

        if (s[i] == s[j]) // Совпадение символов
            p[i] = j + 1; // Увеличиваем длину префикса
    }

    return p; // Возвращаем вектор префиксов
}

// Функция для поиска подстроки с использованием алгоритма КМП
vector<int> kmp_search(const string &text, const string &pattern)
{
    string concatenated = pattern + "#" + text;    // Сцепляем шаблон и текст
    vector<int> p = prefix_function(concatenated); // Вычисляем префиксную функцию
    vector<int> matches;                           // Вектор для хранения индексов совпадений

    for (int i = pattern.size() + 1; i < p.size(); i++)
    { // Начинаем после шаблона и разделителя
        if (p[i] == pattern.size())
        {                                              // Нахождение полного совпадения
            matches.push_back(i - 2 * pattern.size()); // Индекс совпадения
        }
    }

    return matches; // Возвращаем вектор совпадений
}

int main()
{
    string text, pattern;

    cout << "Введите текст: ";  // Запрос пользователю
    getline(cin, text);         // Считываем текст с терминала
    cout << "Введите шаблон: "; // Запрос шаблона
    getline(cin, pattern);      // Считываем шаблон

    vector<int> matches = kmp_search(text, pattern);

    cout << "Совпадения найдены на следующих индексах: ";
    for (int idx : matches)
    {
        cout << idx << " ";
    }
    cout << endl;

    return 0;
}
