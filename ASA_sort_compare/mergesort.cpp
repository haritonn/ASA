#include <iostream>
#include <chrono>
using namespace std;

//Процесс объединения отсортированных подпоследовательностей
void mergeProcess(int arr[], int low, int br, int high)
{
	int sizeFirst = br - low + 1;
	int sizeSecond = high - br;
	
	//Создание и заполнение подмассивов
	int first[sizeFirst], second[sizeSecond];
	for (int i = 0; i < sizeFirst; ++i)
		first[i] = arr[low + i];
	for (int i = 0; i < sizeSecond; ++i)
		second[i] = arr[br + 1 + i];

	int i = 0, j = 0, k = low;

	//Запись в отсортированном порядке
	while (i < sizeFirst && j < sizeSecond)
	{
		if (first[i] <= second[j])
		{
			arr[k] = first[i];
			i++;
		}
		else 
		{
			arr[k] = second[j];
			++j;
		}
		++k;
	}
	
	//'Доделывание' одного из условий предыдущего while
	while (i < sizeFirst)
	{
		arr[k] = first[i];
		++i;
		++k;
	}
	while (j < sizeSecond)
	{
		arr[k] = second[j];
		++j;
		++k;
	}
}

void mergeSort(int arr[], int low, int high)
{
	if (low < high)
	{
		//Высчитываем точку 'перелома'
		int br = low + (high - low) / 2;
		
		//Относительно неё сортируем 2 подпоследовательности
		mergeSort(arr, low, br);
		mergeSort(arr, br + 1, high);

		//А затем объединяем их
		mergeProcess(arr, low, br, high);
	}
}

int main()
{
	int size;
	int n;
	cout << "0 - custom, 1 - 50.000, 2 - 100.000, 3 - 500.000, 4 - 1.000.000: "; cin >> n;
	bool large = true;
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
	mergeSort(arr, 0, size - 1);
	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> duration = end - start;

	if (!large)
	{
	cout << "\nResult:\n";
	for (int i = 0; i < size; ++i)
		cout << arr[i] << " ";
	}
	
	cout << "\n Time: " << duration.count() << " seconds" << endl;
	
	return 0;
}
