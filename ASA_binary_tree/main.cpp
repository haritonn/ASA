#include <iostream>
#include <string>
using namespace std;

//структура для реализации дерева
struct tree
{
	int inf;
	tree* left;
	tree* right;
	tree* parent;
};


//Для создания узла дерева
tree* node(int x)
{
	tree* node = new tree;
	node->inf = x;
	node->left = node->right = NULL;
	node->parent = NULL;

	return node;
}


//Вставка узла в дерево
void insert(tree *&tr, int x)
{
	tree* n = node(x);
	if (!tr) tr = n; //если дерево пустое, тогда tr - корень
	else
	{
		tree *y = tr;
		while(y)
		{
			if (n->inf > y->inf)
				if (y->right)
					y = y->right;
				else
				{
					n->parent = y;
					y->right = n;
					break;
				}
			else if (n->inf < y->inf)
				if (y->left)
					y = y->left;
				else
				{
					n->parent = y;
					y->left = n;
					break;
				}
		}
	}
}

//ОБХОДЫ

//Симметричный обход
void symmetric(tree *tr)
{
	if(tr)
	{
		symmetric(tr->left);
		cout << tr->inf << " ";
		symmetric(tr->right);
	}
}


//Прямой обход
void forward(tree *tr)
{
	if(tr)
	{
		cout << tr->inf << " ";
		forward(tr->left);
		forward(tr->right);
	}
}

//Обратный обход
void backward(tree *tr)
{
	if(tr)
	{
		backward(tr->left);
		backward(tr->right);
		cout << tr->inf << " ";
	}
}

//Поиск по ключу
tree *find(tree *tr, int x)
{
	if (!tr || x == tr->inf)
		return tr;

	if (x < tr->inf)
		return find(tr->left, x);
	else
		return find(tr->right, x);
}


//Поиск минимума
tree *Min(tree *tr)
{
	tree* curr = tr;
	while (curr && curr->left != nullptr)
		curr = curr->left;

	return curr;
}



//Поиск максимума
tree *Max(tree *tr)
{
	tree* curr = tr;
	while (curr && curr->right != nullptr)
		curr = curr->right;

	return curr;
}


//Поиск следующего элемента
tree *Next(tree* tr, int x)
{
	tree* n = find(tr, x);
	if (n->right)
		return Min(n->right);

	tree* y = n->parent;
	while (y && n == y->right)
	{
		n = y;
		y = y->parent;
	}

	return y;
}

//Поиск предыдущего
tree *Prev(tree* tr, int x)
{
	tree *n = find(tr, x);
	if (n->left)
		return Max(n->left);

	tree* y = n->parent;
	while (y && n == y->left)
	{
		n = y;
		y =y->parent;
	}

	return y;
}

//Удаление узла из дерева
tree* Delete(tree* tr, int x)
{
    //Если дерево пустое
	if (tr == nullptr) return tr;

    //Если удаляемый слева
	if (x < tr->inf)
		tr->left = Delete(tr->left, x);

    //Если удаляемый справа
	else if (x > tr->inf)
		tr->right = Delete(tr->right, x);

    //Иначе
	else
	{
		if (tr->left == nullptr)
		{
			tree* temp = tr->right;
			delete tr;
			return temp;
		}
		else if (tr->right == nullptr)
		{
			tree* temp = tr->left;
			delete tr;
			return temp;
		}

		tree* temp = Min(tr->right);

		tr->inf = temp->inf;

		tr->right = Delete(tr->right, temp->inf);
	}

	return tr;
}

//Основная работа программы
int main()
{
	int n, x;
	cout << "n = ";cin >> n;
	tree *tr = NULL;
	for (int i = 0; i < n; ++i)
	{
		cout << i << " ";
		cin >> x;
		if (find(tr, x))
		{
			cout << "Недопустимое значение" << endl;
			--i;
		}
		else
			insert(tr, x);
	}

	cout << "-------------------------------------" << endl;

	cout << "Симметричный обход: ";symmetric(tr);cout << endl;
	cout << "Прямой обход: ";forward(tr);cout << endl;
	cout << "Обратный обход: ";backward(tr); cout << endl;

	cout << endl;

	cout << "min = " << Min(tr)->inf << endl;
	cout << "max = " << Max(tr)->inf << endl;


	cout << "Введите узел, который желаете удалить: ";cin >> x;

	tree* node_to_delete = find(tr, x);

	if(!node_to_delete)
		cout << "Такого узла нет" << endl;
	else
	{
		tr = Delete(tr, x);

		cout << endl << "Результат: " << endl;
		cout << "Симметричный обход: ";symmetric(tr);cout << endl;
		cout << "Прямой обход: ";forward(tr);cout << endl;
		cout << "Обратный обход: ";backward(tr); cout << endl;
	}

	cout << "Введите узел, который желаете вставить: ";cin >> x;

	if (!find(tr, x))
		insert(tr, x);
	cout << endl << "Результат: " << endl;

	cout << "Симметричный обход: ";symmetric(tr);cout << endl;
	cout << "Прямой обход: ";forward(tr);cout << endl;
	cout << "Обратный обход: ";backward(tr); cout << endl;

	return 0;
}
