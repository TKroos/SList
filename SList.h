#include <iostream>
using namespace std;
template<class T> class SList{
	friend class Iterator;
	friend class Node;
public:
	class Node{
	public:
		T data;
		Node *next;
		Node(){
			next = NULL;
		}
		Node(const T& a, Node *p = 0) {
			data = a;
			next = p;
		}
	};
	// An iterator type that can point to an item of type T.
	class Iterator{
	public:
		Iterator(Node *input, SList<T> inputList){
			p = input;
			list = inputList;
		}

		bool operator==(const Iterator &iter){
			return this->p == iter.p ? true : false;
		}

		Iterator &operator++(){  // PreFix ++p
			p = p->next;
			return *this;
		}

		Iterator operator++(int){ // Postfix p++
			SList<T>::Iterator temp = *this;
			p = p->next;
			return temp;
		}

		Iterator &operator--(){  // PreFix --p
			SList<T>::Iterator temp = (*this).list.Begin();
			//SList<T> tempList = (*this).list;
			for (temp = (*this).list.Begin(); temp != (*this).list.End(); temp++) {
				if ((temp.p)->next == (*this).GetNode()) break;
			}
			(*this).p = temp.p;
			return *this;
		}

		T &operator* (){
			return (*((*this).GetNode())).data;
		}

		bool operator!=(const Iterator &iter){
			return this->p == iter.p ? false : true;
		}

		friend ostream& operator<<(ostream &out, const Iterator &iter){
			out << iter.p->data;
			return out;
		}

		Node *GetNode(){
			return p;
		}

	private:
		Node *p;
		SList<T> list;
	};
	// The default constructor, which constructs an empty list.
	SList(){
		size = 0;
		head = NULL;
		tail = NULL;
	}
	// The List copy constructor, which constructs a list and
	// initializes it with copies of the items of list cObj.
	SList(const SList<T> &slist){
		size = slist.size;
		head = slist.head;
		tail = slist.tail;
	}
	// The List assignment operator, which replaces the
	// current list with a copy of list cObj.
	SList<T>& operator=(const SList<T> &slist){
		size = slist.size;
		head = slist.head;
		tail = slist.tail;
		return *this;
	}
	// The List assignment operator, which replaces the
	// current list with a copy of list cObj.
	~SList(){
	}

	// Returns an Iterator set to the first item of the list.
	Iterator Begin(){
		return Iterator(head, *this);
	}

	// Returns an Iterator set to the End position of
	// the list.
	Iterator End(){
		return Iterator(tail, *this);
	}

	// Returns an Iterator set to the first item of the list.
	bool IsEmpty(){
		return size == 0;
	}

	// Return first item of list
	const T& ShowFirst(){
		if (head == NULL)
			return NULL;
		else
			return head->data;
	}

	// Adds a copy of newItem at the beginning of the list.
	void AddFirst(const T &newItem){
		Node *temp = new Node();
		temp->data = newItem;
		if (tail == NULL){
			head = temp;
			tail = head;
		}
		else{
			temp->next = head;
			head = temp;
		}
		size++;
	}

	// Adds a copy of newItem at the end of the list.
	void AddLast(const T &newItem){
		Node *temp = new Node();
		temp->data = newItem;
		if (head == NULL){
			head = temp;
			tail = head;
		}
		else{
			tail->next = temp;
			tail = temp;
		}
		size++;
	}

	// Adds a copy of the newItem following the position
	// pointed by iterator i.
	void AddAfter(Iterator i, const T &newItem){
		Node *temp = new Node();
		temp->data = newItem;
		temp->next = i.GetNode()->next;
		i.GetNode()->next = temp;
		size++;
	}

	// Removes the first item from the list.
	void RemoveFirst(){
		if (size == 0)
			cout << "the list is empty!" << endl;
		else if (size == 1){
			head = NULL;
			tail = NULL;
			size = 0;
		}
		else{
			head = head->next;
			size--;
		}
	}

	// Removes the item following the position pointed by
	// iterator i.
	void RemoveAfter(Iterator i){
		i.GetNode()->next = i.GetNode()->next->next;
		size--;
	}

	// Removes all items from the list. The list object
	// is empty after this operation.
	void SetToEmpty(){
		if (head == NULL)
			cout << "list is empty!" << endl;
		else{
			while (head != NULL){
				head = head->next;
				size--;
			}
			tail = head;
		}
	}
	// Output the data of the list
	void PrintList(){
		SList<T>::Iterator it = this->Begin();
		while (it != this->End()){
			cout << it << " ";
			it++;
		}
		cout << it << endl;
	}

private:
	int size;
	Node *head;
	Node *tail;
};