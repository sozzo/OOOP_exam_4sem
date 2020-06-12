#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

/* List Node: */

template <class T>
class DLListNode {
private:
	T data;
public:
	DLListNode* next;
	DLListNode* previous;
	DLListNode(T data);
	T getData();
	string toString();
	~DLListNode();
};

template <class T>
DLListNode<T>::DLListNode(T data) {
	this->data = data;
}

template <class T>
T DLListNode<T>::getData() {
	return this->data;
}

template <class T>
string DLListNode<T>::toString() {
	stringstream s;
	s << this->getData();
	return s.str();
}

template <class T>
DLListNode<T>::~DLListNode() { }

/* Linked List: */

template <class T>
class DLList {
private:
	T* head;
	T* tail;
	int list_size;
public:
	DLList();
	T* getHead();
	T* getTail();
	int size(bool update = false);
	void addNodeAsTail(T* new_node);
	void addNodeAsHead(T* new_node);
	void push(T* new_node);
	T* pop();
	T* peek();
	void enqueue(T* new_node);
	T* dequeue();
	T* get(int index);
	void printList();
	void printListBackwards();
	~DLList();
};

template <class T>
DLList<T>::DLList() {
	this->head = NULL;
	this->tail = NULL;
	this->list_size = 0;
}

template <class T>
T* DLList<T>::getHead() {
	return this->head;
}

template <class T>
T* DLList<T>::getTail() {
	return this->tail;
}

template <class T>
int DLList<T>::size(bool update) {
	if (!update) {
		return this->list_size;
	}
	int size = 0;
	T* temp = this->head;
	while (temp) {
		size++;
		temp = temp->next;
	}
	this->list_size = size;
	return this->list_size;
}

template <class T>
void DLList<T>::addNodeAsTail(T* new_node) {
	new_node->next = NULL;
	new_node->previous = NULL;

	if (this->head == NULL) {
		this->head = new_node;
		this->tail = this->head;
		this->list_size = this->list_size + 1;
	}
	else {
		this->tail->next = new_node;
		new_node->previous = this->tail;
		this->tail = new_node;
		this->list_size = this->list_size + 1;
	}
}

template <class T>
void DLList<T>::addNodeAsHead(T* new_node) {
	new_node->next = NULL;
	new_node->previous = NULL;

	if (this->head == NULL) {
		this->head = new_node;
		this->tail = this->head;
		this->list_size = this->list_size + 1;
	}
	else {
		this->head->previous = new_node;
		new_node->next = this->head;
		this->head = new_node;
		this->list_size = this->list_size + 1;
	}
}

template <class T>
void DLList<T>::push(T* new_node) {
	this->addNodeAsHead(new_node);
}

template <class T>
T* DLList<T>::pop() {
	T* temp = this->head;
	this->head = this->head->next;
	this->head->previous = NULL;
	this->list_size = this->list_size - 1;
	return temp;
}

template <class T>
T* DLList<T>::peek() {
	return this->head;
}

template <class T>
void DLList<T>::enqueue(T* new_node) {
	this->addNodeAsTail(new_node);
}

template <class T>
T* DLList<T>::dequeue() {
	return this->pop();
}

template <class T>
T* DLList<T>::get(int index) {
	if (index == 0) {
		return this->head;
	}
	else if (index == this->list_size - 1) {
		return this->tail;
	}
	else if (index < 0 || index >= this->list_size) {
		return NULL;
	}
	if (index < this->list_size / 2) {
		T* temp = this->head;
		int i = 0;
		while (temp) {
			if (i == index) { return temp; }
			i++;
			temp = temp->next;
		}
	}
	else {
		T* temp = this->tail;
		int i = this->list_size - 1;
		while (temp) {
			if (i == index) { return temp; }
			i--;
			temp = temp->previous;
		}
	}
	return NULL;
}

template <class T>
void DLList<T>::printList() {
	cout << "HEAD: ";
	T* temp = this->head;
	while (temp) {
		cout << temp->toString() << " -> ";
		temp = temp->next;
	}
	cout << "\b\b\b\b :TAIL" << endl;
}

template <class T>
void DLList<T>::printListBackwards() {
	cout << "TAIL: ";
	T* temp = this->tail;
	while (temp) {
		cout << temp->toString() << " -> ";
		temp = temp->previous;
	}
	cout << "\b\b\b\b :HEAD" << endl;
}

template <class T>
DLList<T>::~DLList() {
	while (this->head) {
		T* next = this->head->next;
		delete this->head;
		this->list_size = this->list_size - 1;
		this->head = next;
	}
}
	/*avl tree*/
template <typename T>
struct AVLNode
{
	AVLNode(T v, int b = 0, AVLNode<T> * l = 0, AVLNode<T> * r = 0) :
		value(v),
		balance(b),

		left(l),
		right(r)
	{}

	T value;
	int balance;

	AVLNode<T>* left;
	AVLNode<T>* right;

	void Print(int offset = 0)
	{
		using namespace std;

		if (right) right->Print(5 + offset);
		cout << setw(offset) << value << "(" << balance << ")" << endl;
		if (left) left->Print(5 + offset);
	}
};

template <typename T>
class AVLTree
{
private:
	AVLNode<T>* root;

public:
	AVLTree(T root_key) :
		root(new AVLNode<T>(root_key, 0))
	{}
	~AVLTree()
	{
		Delete(root);
	}

	void Print()
	{
		root->Print();
	}

	bool Add(T item)
	{
		return Add(item, root);
	}

	bool Remove(T item)
	{
		return Remove(item, root);
	}

	T Max()
	{
		return Max(root);
	}

	T Min()
	{
		return Min(root);
	}

private:

	void Delete(AVLNode<T>*& node)
	{
		if (node != NULL)
		{
			Delete(node->left);
			Delete(node->right);

			delete node;
			node = NULL;
		}
	}

	void RotateRight(AVLNode<T>*& node)
	{
		AVLNode<T>* x = node;
		AVLNode<T>* y = node->left;

		x->left = y->right;
		y->right = x;
		node = y;

		x->balance += 1;
		if (y->balance < 0) x->balance += -y->balance;

		y->balance += 1;
		if (x->balance > 0) y->balance += x->balance;
	}

	void RotateLeft(AVLNode<T>*& node)
	{
		AVLNode<T>* x = node;
		AVLNode<T>* y = node->right;

		x->right = y->left;
		y->left = x;
		node = y;

		x->balance -= 1;
		if (y->balance > 0) x->balance -= y->balance;

		y->balance -= 1;
		if (x->balance < 0) y->balance -= -x->balance;
	}

	bool IncrementBalance(AVLNode<T>*& node)
	{
		node->balance++;

		if (node->balance == 0)
			return false;

		if (node->balance == 1)
			return true;

		if (node->balance == 2)
		{
			if (node->right->balance == -1)
				RotateRight(node->right);

			RotateLeft(node);

			return false;
		}
		return true;
	}

	bool DecrementBalance(AVLNode<T>*& node)
	{
		node->balance--;

		if (node->balance == 0)
			return false;

		if (node->balance == -1)
			return true;

		if (node->balance == -2)
		{
			if (node->left->balance == 1)
				RotateLeft(node->left);

			RotateRight(node);

			return false;
		}
		return true;
	}

	bool Add(T item, AVLNode<T>*& node)
	{
		if (node == NULL)
		{
			node = new AVLNode<T>(item);
			return true;
		}
		else if (item > node->value)
		{
			return Add(item, node->right) && IncrementBalance(node);
		}
		else if (item < node->value)
		{
			return Add(item, node->left) && DecrementBalance(node);
		}

		return false; // no need to add already existing node
	}

	bool Remove(T item, AVLNode<T>*& node)
	{
		if (node == NULL)
		{
			return false;
		}
		else if (node->value > item)
		{
			return Remove(item, node->left) && IncrementBalance(node);
		}
		else if (node->value < item)
		{
			return Remove(item, node->right) && DecrementBalance(node);
		}
		else // if (node->value == item)
		{
			if (node->left == NULL && node->right == NULL)
			{
				Delete(node);
			}
			else if (node->left != NULL && node->right != NULL)
			{
				AVLNode<T>* current_node = node;
				T min_node_value = Min(node->right);

				bool isHeightChanged = Remove(min_node_value, node);
				current_node->value = min_node_value;

				return isHeightChanged;
			}
			else
			{
				AVLNode<T>* node_to_remove = node;

				if (node->left == NULL)
				{
					node = node_to_remove->right;
					node_to_remove->right = NULL;
				}
				else
				{
					node = node_to_remove->left;
					node_to_remove->left = NULL;
				}

				Delete(node_to_remove);
			}

			return true;
		}
	}

	T Max(const AVLNode<T>* const node)
	{
		return node->right == NULL ? node->value : Max(node->right);
	}

	T Min(const AVLNode<T>* const node)
	{
		return node->left == NULL ? node->value : Min(node->left);
	}
};
int main()
{
	return 0;
}