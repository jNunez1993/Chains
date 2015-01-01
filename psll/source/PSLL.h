#ifndef PSLL_h
#define PSLL_h
#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;


template <typename T>
class PSLL{
	struct node{
		T data;
		node *next;
	};
public:
	class PSLL_ITER {
	private:
		node* myNode;
	public:

		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;

		typedef PSLL_ITER self_type;
		typedef PSLL_ITER& self_reference;


		PSLL_ITER(node *n){
			myNode = n;
		}
		PSLL_ITER(const PSLL_ITER &src){
			myNode = src.myNode;
		}

		pointer operator->(){  
			return myNode;
		}

		reference operator *(){
			return myNode->data;
		}
		self_reference operator++(){
			myNode = myNode->next;
			return *this;
		}
		self_type operator++(int){
			PSLL_ITER l = *this;
			myNode = myNode->next;
			return l;

		}
		bool operator ==(PSLL_ITER &rhs){
			return this->myNode == rhs.myNode;

		}
		bool operator!=(PSLL_ITER &rhs){
			return this->myNode != rhs.myNode;

		}
		self_reference operator=(PSLL_ITER &rhs){
			return this->myNode = rhs->myNode;

		}
		ostream &operator<<(ostream &obj) {
			obj << this.myNode->data;
			return obj;
		}
	};

public:
	class PSLL_Const_ITER {
	private:
		const node* myNode;
	public:

		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef const T& reference;
		typedef const T* pointer;
		typedef std::forward_iterator_tag iterator_category;

		typedef PSLL_Const_ITER self_type;
		typedef PSLL_Const_ITER& self_reference;


		PSLL_Const_ITER(node *n){
			myNode = n;
		}
		PSLL_Const_ITER(const PSLL_Const_ITER &src){
			myNode = src.myNode;
		}

		pointer operator->(){  
			return myNode;
		}

		reference operator *(){
			return myNode->data;
		}
		self_reference operator++(){
			myNode = myNode->next;
			return *this;
		}
		self_type operator++(int){
			PSLL_Const_ITER l = *this;
			myNode = myNode->next;
			return l;
		}
		bool operator ==(PSLL_Const_ITER &rhs){
			return this->myNode == rhs.myNode;

		}
		bool operator!=(PSLL_Const_ITER &rhs){
			return this->myNode != rhs.myNode;

		}
		self_reference operator=(PSLL_Const_ITER &rhs){
			return this->myNode = rhs->myNode;

		}

		PSLL_Const_ITER operator+(int x)
		{
			for (int i = 0; i < x - 1; i++)
			{
				this->myNode = this->myNode->next;
			}
			return *this;
		}

		ostream &operator<<(ostream &obj) {
			obj << this.myNode->data;
			return obj;
		}
	};

public:
	PSLL();
	PSLL( const PSLL& src ){
	head=src.head;
	tail=src.tail;
	}
	~PSLL();
	PSLL& operator=( const PSLL& src ) {
      if ( &src == this ) 
	return *this;   
	}
	typedef std::size_t size_t;
	typedef T value_type;
	typedef PSLL_ITER iterator;
	typedef PSLL_Const_ITER const_iterator;
	T replace(const T& e, int position);
	void insert(const T&, int position);
	void push_front(const T& e);
	void push_back(const T& e);
	T pop_front();
	T pop_back();
	T remove(int position);
	T itemAt(int position) const;
	bool isEmpty() const;
	int size() const;
	void clear();
	bool contains(T e, bool equals_function);
	bool equals_function(T e);
	const ostream &print(ostream &out);
	PSLL_ITER begin();
	PSLL_ITER end();
	PSLL_Const_ITER begin() const;
	PSLL_Const_ITER end() const;
	T& operator[](int i){
		node *current = head;
		int k = 0;
		while (k != i){
			current = current->next;
			k++;
		}
		return current->data;
	}
	T const& operator[](int i)const {
		node *current = head;
		int k = 0;
		while (k != i){
			current = current->next;
			k++;
		}
		return current->data;
	}

private:
	node *head;
	node *tail;
	node *free;
	node *freeTail;
	int count;
};


template <typename T>
PSLL<T>::PSLL(){
	head = NULL;
	tail = NULL;
	free = NULL;
	freeTail = NULL;
	count = 0;
}

template <typename T>
PSLL<T>::~PSLL(){
}

template <typename T>
T PSLL<T>::replace(const T& e, int position){
	int temp = 0;
	if (position < 0 || position > size()){
		throw out_of_range("Invalid Position");
	}
	if (position == 0){
		temp = head->data;
		head->data = e;
		return temp;
	}
	else{
		node *current = head;
		node *prev = NULL;
		int i = 0;
		while (i < position ){
			prev = current;
			current = current->next;
			i++;
		}
		int temp = current->data;
		node *newNode;
		if (count > 0){
			newNode = free;
			if (free->next != NULL){
				free = free->next;
			}
			if (count == 1){
				free = NULL;
			}
			count--;
		}
		else{
			newNode = new node();
		}

		newNode->data = e;
		newNode->next = current->next;
		current = newNode;
		prev->next = current;
		return temp;
	}
}


template <typename T>
void PSLL<T>::insert(const T& e, int position){
	if (position < 0 || position > size()){
		throw out_of_range("Invalid Position");
	}
	if (position == 0){
		push_front(e);
	}
	else if (position == size()){
		push_back(e);
	}
	else{
		node *current = head;
		node *prev = NULL;
		int i = 0;
		if (position == 0){
			push_front(e);
		}
		else{
			while (i < position ){
				prev = current;
				current = current->next;
				i++;
			}
			node *newNode;
			if (count > 0){
				newNode = free;
				if (free->next != NULL){
					free = free->next;
				}
				if (count == 1){
					free = NULL;
				}
				count--;
			}
			else{
				newNode = new node();
			}
			newNode->data = e;
			prev->next = newNode;
			newNode->next = current;
		}
	}

}


template <typename T>
void PSLL<T>::push_front(const T& e){
	node *newNode;
	if (count > 0){
		newNode = free;
		if (free->next != NULL){
			free = free->next;
		}
		if (count == 1){
			free = NULL;
		}
		count--;
	}
	else{
		newNode = new node();
	}
	newNode->data = e;
	newNode->next = head;

	if (head == NULL){
		head = newNode;
		tail = newNode;
	}
	else{
		head = newNode;
	}
}

template <typename T>
void PSLL<T>::push_back(const T& e){
	node *newNode;
	if (count > 0){
		newNode = free;
		if (free->next != NULL){
			free = free->next;
		}
		if (count == 1){
			free = NULL;
		}
		count--;
	}
	else{
		newNode = new node();
	}
	newNode->data = e;
	newNode->next = NULL;
	if (head == NULL){
		head = newNode;
		tail = newNode;
	}
	else{
		tail->next = newNode;
		tail = newNode;
	}
}

template <typename T>
T PSLL<T>::pop_front(){
	if (isEmpty()){
		throw logic_error("List is Empty");
	}
	node *current = head;
	int temp = head->data;
	head = head->next;
	if (free == NULL){
		current->next = NULL;
		free = current;
		freeTail = current;
		freeTail->next = NULL;
		count++;
	}
	else{
		freeTail->next = current;
		current->next = NULL;
		freeTail = current;
		count++;
	}
	return temp;

}

template <typename T>
T PSLL<T>::pop_back(){
	if (isEmpty()){
		throw logic_error("List is Empty");
	}
	node *current = head;
	
	while (current->next != tail){
		
		current = current->next;
	}
	int temp = tail->data;
	tail = current;
	if (free == NULL){
		free = current->next;
		free->next = NULL;
		freeTail = current->next;
		freeTail->next = NULL;
		count++;
	}
	else{
		freeTail->next = current->next;
		freeTail = current;
		count++;
	}
	tail->next = NULL;
	return temp;

}


template <typename T>
T PSLL<T>::remove(int position){
	if (isEmpty()){
		throw logic_error("List is Empty");
	}
	if (position < 0 || position > size()){
		throw out_of_range("Invalid Position");
	}
	node *current = head;
	int temp = 0;
	node *prev = NULL;
	int i = 0;
	if (position == 0){
		return pop_front();
	}
	else{
		while (i < position ){
			prev = current;
			current = current->next;
			i++;
		}
		prev->next = current->next;
		temp = current->data;
		if (free == NULL){
			current->next = NULL;
			free = current;
			freeTail = current;
			freeTail->next = NULL;
			count++;
		}
		else{
			freeTail->next = current;
			current->next = NULL;
			freeTail = current;
			count++;
		}
	}
	return temp;
}


template <typename T>
T PSLL<T>::itemAt(int position)const {
	if (position < 0 || position > size()){
		throw out_of_range("Invalid Position");
	}
	node* current = head;
	int i = 0;
	while (i < position ){
		current = current->next;
		i++;
	}
	return current->data;
}

template <typename T>
bool PSLL<T>::isEmpty()const {
	if (head == NULL){
		return true;
	}
	return false;
}

template <typename T>
int PSLL<T>::size() const {
	node *current = head;
	size_t count = 0;
	if (head == NULL){
		return 0;
	}
	else{
		while (current != NULL){
			current = current->next;
			count++;
		}
	}
	return count;
}

template <typename T>
void PSLL<T>::clear(){
	while (isEmpty() != true){
		pop_front();
	}
}

template <typename T>
bool PSLL<T>::equals_function(T e){
	node *current = head;
	while (current != NULL){
		if (current->data == e){
			return true;
		}
		current = current->next;
	}
	return false;
}

template <typename T>
bool PSLL<T>::contains(T e, bool equals_function) {
	return PSLL<T>::equals_function(e);
}


template <typename T>
const ostream& PSLL<T>::print(ostream& out)  {
	node *current = head;
	if (isEmpty() == true){
		out << "<Empty>" << endl;
	}
	else{
		out << "[";
		while (current != NULL){
			out << current->data;
			if (current->next != NULL){
				out << ",";
			}
			current = current->next;
		}
		out << "]" << endl;
	}
	return out;
}

template <typename T>
typename PSLL<T>::PSLL_ITER PSLL<T>::begin(){
	return PSLL_ITER(head);
}

template <typename T>
typename PSLL<T>::PSLL_ITER PSLL<T>::end(){
	return PSLL_ITER(tail->next);
}

template <typename T>
typename PSLL<T>::PSLL_Const_ITER PSLL<T>::begin() const{
	return PSLL_Const_ITER(head);
}

template <typename T>
typename PSLL<T>::PSLL_Const_ITER PSLL<T>::end() const{
	return PSLL_Const_ITER(tail->next);
}


#endif