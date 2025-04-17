#include<iostream>
#include<climits>

using namespace std;

//Вспомогательная функция для поиска минимума и максимума массива
//Вход: исходный массив, его размерность
void findMaxMin(int arr[], int size, int& maxValue, int& minValue)
{
	for (int i = 0; i < size; ++i)
	{
		if (arr[i] > maxValue)
			maxValue = arr[i];

		if (arr[i] < minValue)
			minValue = arr[i];
	}
}

//Сортировка подсчётом
//Вход: массив, размерность
void countSort(int arr[], int size)
{
	int minVal = INT_MAX, maxVal = INT_MIN;
	findMaxMin(arr, size, maxVal, minVal); //Находим максимум, минимум

	int sizeOfFreq = maxVal - minVal + 1; //Определяем размер массива частоты

	int* freqArray = new int[sizeOfFreq] {0};
	int* resultArray = new int[size]; 
	
	for (int i = 0; i < size; ++i)
		freqArray[arr[i] - minVal]++; //Считаем количество вхождений каждого


	for (int i = 1; i < sizeOfFreq; ++i)
		freqArray[i] += freqArray[i - 1]; //Считаем кумулятивную сумму


	for (int i = size - 1; i >= 0; --i)
		resultArray[--freqArray[arr[i] - minVal]] = arr[i]; //Заполняем элементы в нужном порядке, параллельно уменьшая значения freqArray
	

	for (int i = 0; i < size; ++i)
		arr[i] = resultArray[i];

	delete[] freqArray;
	delete[] resultArray;
}

int main()
{
	int size;
	cout << "Array size (Count): "; cin >> size;
	int* arr = new int[size];
	
	for (int i = 0; i < size; ++i)
		cin >> arr[i];

	countSort(arr, size);
	for (int i = 0; i < size; ++i)
		cout << arr[i] << " ";
	cout << endl;

	delete[] arr;
	return 0;
}