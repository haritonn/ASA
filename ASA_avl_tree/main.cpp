#include<iostream>

using namespace std;

class AVL
{
    struct node
    {
        int inf;
        node* left;
        node* right;
        int height;
    };

    node* root;

    void makeEmpty(node* t)
    {
        if(t == NULL)
            return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

    //Вставка
    node* insert(int x, node* t)
    {
        if(t == NULL)
        {
            t = new node;
            t->inf = x;
            t->height = 0;
            t->left = t->right = NULL;
        }
        else if(x < t->inf)
        {
            t->left = insert(x, t->left);
            if(height(t->left) - height(t->right) == 2)
            {
                if(x < t->left->inf)
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if(x > t->inf)
        {
            t->right = insert(x, t->right);
            if(height(t->right) - height(t->left) == 2)
            {
                if(x > t->right->inf)
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }

        t->height = max(height(t->left), height(t->right))+1;
        return t;
    }

    //LL
    node* singleRightRotate(node* &t)
    {
        node* u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = max(height(t->left), height(t->right))+1;
        u->height = max(height(u->left), t->height)+1;
        return u;
    }
    
    //RR
    node* singleLeftRotate(node* &t)
    {
        node* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->left), height(t->right))+1;
        u->height = max(height(t->right), t->height)+1 ;
        return u;
    }

    //LR
    node* doubleLeftRotate(node* &t)
    {
        t->right = singleRightRotate(t->right);
        return singleLeftRotate(t);
    }

    //RL
    node* doubleRightRotate(node* &t)
    {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }

    node* findMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node* findMax(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    //Удалить узел
    node* remove(int x, node* t)
    {
        node* temp;

        if(t == NULL)
            return NULL;

        else if(x < t->inf)
            t->left = remove(x, t->left);
        else if(x > t->inf)
            t->right = remove(x, t->right);

        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->inf = temp->inf;
            t->right = remove(t->inf, t->right);
        }
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }
        if(t == NULL)
            return t;

        t->height = max(height(t->left), height(t->right))+1;

        if(height(t->left) - height(t->right) == -2)
        {
            if(height(t->right->right) >= height(t->right->left))
                return singleLeftRotate(t);  // Right Right
            else
                return doubleLeftRotate(t);  // Right Left
        }
        else if(height(t->left) - height(t->right) == 2)
        {
            if(height(t->left->left) >= height(t->left->right))
                return singleRightRotate(t);  // Left Left
            else
                return doubleRightRotate(t);  // Left Right
        }

        return t;
    }

    // Поиск высоты
    int height(node* t)
    {
        return (t == NULL ? -1 : t->height);
    }

    // Узнать баланс в текущем узле
    int getBalance(node* t)
    {
        if(t == NULL)
            return 0;
        else
            return height(t->left) - height(t->right);
    }

    // Симметричный обход
    void inorder(node* t)
    {
        if(t == NULL)
            return;
        inorder(t->left);
        cout << t->inf << " ";
        inorder(t->right);
    }

public:
    AVL()
    {
        root = NULL;
    }

    void insert(int x)
    {
        root = insert(x, root);
    }

    void remove(int x)
    {
        root = remove(x, root);
    }

    void inorder()
    {
        inorder(root);
        cout << endl;
    }
};

int main()
{   
    AVL t;
    int n;
    cout << "N = "; cin >> n;
    
    int x;
    for (int i = 0; i < n; ++i)
    {
        cout << "x[" << i << "] = ";
        cin >> x;
        t.insert(x);
    }


    cout << "Текущее дерево (симметричный обход):\n";
    t.inorder();
    cout << endl;
    
    int nodeToInset;
    cout << "\nВведите элемент для вставки: "; cin >> nodeToInset;
    t.insert(nodeToInset);
    cout << "\nРезультат:\n"; t.inorder(); 

    int j = 0;
    int nodeToDelete;
    while (j < 2) {
        cout << "\nВведите элемент для удаления: "; cin >> nodeToDelete;
        t.remove(nodeToDelete);
        cout << "\nРезультат:\n"; t.inorder();
        ++j;
    }

    return 0;
}