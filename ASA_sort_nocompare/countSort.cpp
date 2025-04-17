#include<iostream>
#include<climits>

using namespace std;

//��������������� ������� ��� ������ �������� � ��������� �������
//����: �������� ������, ��� �����������
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

//���������� ���������
//����: ������, �����������
void countSort(int arr[], int size)
{
	int minVal = INT_MAX, maxVal = INT_MIN;
	findMaxMin(arr, size, maxVal, minVal); //������� ��������, �������

	int sizeOfFreq = maxVal - minVal + 1; //���������� ������ ������� �������

	int* freqArray = new int[sizeOfFreq] {0};
	int* resultArray = new int[size]; 
	
	for (int i = 0; i < size; ++i)
		freqArray[arr[i] - minVal]++; //������� ���������� ��������� �������


	for (int i = 1; i < sizeOfFreq; ++i)
		freqArray[i] += freqArray[i - 1]; //������� ������������ �����


	for (int i = size - 1; i >= 0; --i)
		resultArray[--freqArray[arr[i] - minVal]] = arr[i]; //��������� �������� � ������ �������, ����������� �������� �������� freqArray
	

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