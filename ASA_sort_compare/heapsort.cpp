#include <iostream>
#include <chrono>
using namespace std;

//Преобразование в тип данных 'куча' (подобие бинарного дерева)
void heapify(int arr[], int size, int i)
{
	int largest = i, l = 2*i + 1, r = 2*i + 2;

	//Находим максимальное (инициализируем как корень дерева)
	if (l < size && arr[l] > arr[largest])
		largest = l;
	if (r < size && arr[r] > arr[largest])
		largest = r;

	//Если нашли другое максимально, то меняем местами элементы и рекурсивно вызываем 
	//в поддерево.
	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		heapify(arr, size, largest);
	}
}

//Алгоритм сортировки
void heapSort(int arr[], int size)
{
	//Сначала преобразуем в кучу
	for (int i = size/2 - 1; i >= 0; --i)
		heapify(arr, size, i);

	//А затем извлекаем из кучи по одному
	for (int i = size - 1; i >= 0; --i)
	{
		//Текущую вершину кучи заносим в конец
		swap(arr[0], arr[i]);
		//Вызываем heapify для оставшейся кучи
		heapify(arr, i, 0);
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
	heapSort(arr, size);
	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> duration = end - start;

	if (!large)
	{
	cout << "\nResult:\n";
	for (int i = 0; i < size; ++i)
		cout << arr[i] << " ";
	}
	cout << "\n Time: " << duration.count() << " seconds.";
	return 0;
}
