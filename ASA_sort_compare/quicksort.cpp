#include <iostream>
#include <chrono>
using namespace std;

//Алгоритм быстрой сортировки
//Вход: массив, опорные элементы (при первом вызове - 0 и size - 1)
void quickSort(int arr[], int low, int high)
{
	int low_index = low;
	int high_index = high;
	int mid_index = arr[(low_index + high_index) / 2]; 

	while (low_index <= high_index)
	{
		//Итерации до тех пор, пока элементы отсортированны относительно центрального
		while (arr[low_index] < mid_index) 
			low_index++;
		while (arr[high_index] > mid_index)
			high_index--;
		
		//Если после этого нижний индекс не превышает верхний, то меняем элементы местами (со сдвигом индексов) 
		if (low_index <= high_index)
		{
			swap(arr[low_index], arr[high_index]);
			low_index++;
			high_index--;
		}
	}
		if (high_index > low)
			quickSort(arr, low, high_index);
		if (low_index < high)
			quickSort(arr, low_index, high);
	
}


int main()
{
	//Заполнение массива
	int size;
	int n;
	cout << "0 - custom, 1 - 50.000, 2 - 100.000, 3 - 500.000, 4 - 1.000.000: "; cin >> n;
	bool large = true; //флаг, чтобы не выводить слишком большие массивы
	switch(n)
	{
		case 0:
			cin >> size;
			if (size <= 50)
				large = false;
			break;
		case 1:
			size = 50000;
			break;
		case 2:
			size = 100000;
			break;
		case 3:
			size = 500000;
			break;
		case 4:
			size = 1000000;
			break;
	}
	int arr[size];
	for (int i = 0; i < size; ++i)
		arr[i] = rand() % 100;

	if (!large)
	{
	cout << "Array:\n";
	for (int i = 0; i < size; ++i)
		cout << arr[i] << " ";
	}
	
	auto start = chrono::high_resolution_clock::now();
	quickSort(arr, 0, size - 1);
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;

	//Вывод результата
	if (!large)
	{
		cout << "\nResult:\n";
		for (int i = 0; i < size; ++i)
			cout << arr[i] << " ";
	}   	
	cout << "\n Time: " << duration.count()  << " seconds." << endl;

	return 0;
}
