#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

//ѕоиск максимального разр€да
//¬ход: массив, размерность
void findMaxDigit(int arr[], int size, int& digit)
{
    digit = 0;
    for (int i = 0; i < size; ++i)
    {
        int num = arr[i]; 
        int counter = (num == 0) ? 1 : 0; 
        while (num > 0)
        {
            num /= 10; // удал€ем разр€д
            counter++;
        }
        if (counter > digit)
            digit = counter;
    }
}

//ѕоразр€дна€ сортировка
//¬ход: массив, его размерность
void radixSort(int arr[], int size)
{
    int digit;
    findMaxDigit(arr, size, digit);

    std::vector<int> p[10]; // по умолчанию —— 10
    for (int i = 0; i < digit; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            int digit_number = (abs(arr[j]) / static_cast<int>(pow(10, i))) % 10; // записываем текущий разр€д
            p[digit_number].push_back(arr[j]); // в соответствующий вектор
        }

        int ind = 0;
        for (int j = 0; j < 10; ++j) // проходимс€ по разр€дным векторам
        {
            for (int n : p[j])
                arr[ind++] = n; // записываем элементы векторов в результат

            p[j].clear(); // очищаем вектора дл€ дальнейших итераций (если таковые есть)
        }
    }
}

int main()
{
	int size;
	cout << "Array size (Radix): "; cin >> size;

	int* arr = new int[size];
	for (int i = 0; i < size; ++i)
		cin >> arr[i];

	radixSort(arr, size);
	for (int i = 0; i < size; ++i)
		cout << arr[i] << " ";

	return 0;
}