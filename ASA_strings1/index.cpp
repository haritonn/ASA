#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Функция для вычисления префиксной функции
vector<int> prefix_function(string s)
{
    int n = (int)s.size();
    vector<int> p(n, 0); // Инициализация вектора префиксов

    for (int i = 1; i < n; i++)
    {
        int j = p[i - 1]; // Текущий индекс префикса

        while (s[i] != s[j] && j > 0) // Поиск корректного префикса
            j = p[j - 1];

        if (s[i] == s[j]) // Совпадение символов
            p[i] = j + 1; // Увеличиваем длину префикса
    }

    return p; // Возвращаем вектор префиксов
}

// Функция для вычисления Z-функции
vector<int> z_function(string s)
{
    int n = (int)s.size();
    vector<int> z(n, 0); // Инициализация Z-вектора
    int l = 0, r = 0;    // Границы текущего сегмента

    for (int i = 1; i < n; i++)
    {
        if (i <= r)                          // Проверяем, находимся ли мы внутри Z-границ
            z[i] = min(r - i + 1, z[i - l]); // Используем ранее вычисленные значения

        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) // Поиск совпадений
            z[i]++;                                    // Увеличиваем Z-значение

        if (i + z[i] - 1 > r)
        { // Обновляем границы
            r = i + z[i] - 1;
            l = i;
        }
    }
    z[0] = n; // Начальное значение Z-функции
    return z; // Возвращаем Z-вектор
}

int main()
{
    string s;
    cout << "Введите строку: "; // Запрос пользователю
    getline(cin, s);            // Считываем строку с терминала

    vector<int> prefix = prefix_function(s);
    vector<int> z = z_function(s);

    cout << "Префиксная функция: ";
    for (int val : prefix)
        cout << val << " ";
    cout << endl;

    cout << "Z функция: ";
    for (int val : z)
        cout << val << " ";
    cout << endl;

    return 0;
}
