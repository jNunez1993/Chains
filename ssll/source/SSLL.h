#ifndef SSLL_h
#define SSLL_h
#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;


template <typename T>
class SSLL{
	struct node{
		T data;
		node *next;
	};

public:
	class SSLL_ITER {
	private:
		node* myNode;
	public:
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;

		typedef SSLL_ITER self_type;
		typedef SSLL_ITER& self_reference;

		explicit SSLL_ITER(node *n){
			myNode = n;
		}
		SSLL_ITER(const SSLL_ITER& src){
			myNode = src.myNode;
		}

		pointer operator->(){  
			return myNode->data;
		}

		reference operator *(){
			return myNode->data;
		}
		self_reference operator++(){
			myNode = myNode->next;
			return *this;
		}
		self_type operator++(int){
			SSLL_ITER l = *this;
			myNode = myNode->next;
			return l;
		}
		bool operator ==(SSLL_ITER &rhs){
			return this->myNode == rhs.myNode;
		}
		bool operator!=(SSLL_ITER &rhs){
			return this->myNode != rhs.myNode;

		}
		self_reference operator=(SSLL_ITER &rhs){   
			return this->myNode = rhs;

		}

		ostream &operator<<(ostream &obj) {
			obj << this.myNode->data;
			return obj;
		}

		
	};

public:
	class SSLL_Const_ITER {
	private:
		const node* myNode;
	public:
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef const T& reference;
		typedef const T* pointer;
		typedef std::forward_iterator_tag iterator_category;

		typedef SSLL_Const_ITER self_type;
		typedef SSLL_Const_ITER& self_reference;

		explicit SSLL_Const_ITER(node *n){
			myNode = n;
		}
		SSLL_Const_ITER(const SSLL_Const_ITER& src){
			myNode = src.myNode;
		}

		pointer operator->(){  
			return myNode->data;
		}

		reference operator *(){
			return myNode->data;
		}
		self_reference operator++(){
			myNode = myNode->next;
			return *this;
		}
		self_type operator++(int){
			SSLL_Const_ITER l = *this;
			myNode = myNode->next;
			return l;
		}
		bool operator ==(SSLL_Const_ITER &rhs){
			return this->myNode == rhs.myNode;

		}
		bool operator!=(SSLL_Const_ITER &rhs){
			return this->myNode != rhs.myNode;

		}
		self_reference operator=(SSLL_Const_ITER &rhs){   
			return this->myNode = rhs;
			

		}

		ostream &operator<<(ostream &obj) {
			obj << this.myNode->data;
			return obj;
		}

	};

public:
	SSLL();
	SSLL( const SSLL& src ){
	head=src.head;
	tail=src.tail;
	}
	~SSLL();
	SSLL &operator=(const SSLL &src){
		if (&src == this)
			return *this;
	}
	typedef std::size_t size_t;
	typedef T value_type;
	typedef SSLL_ITER iterator;
	typedef SSLL_Const_ITER const_iterator;
	T replace(const T &e, int position);
	void insert(const T &e, int position);
	void push_front(const T &e);
	void push_back(const T &e);
	T pop_front();
	T pop_back();
	T remove(int position);
	T itemAt(int position);
	bool isEmpty() const;
	int size() const;
	void clear();
	bool contains(T e, bool equals_function);
	bool equals_function(T e);
	const ostream& print(ostream &obj);
	SSLL_ITER begin();
	SSLL_ITER end();
	SSLL_Const_ITER begin() const;
	SSLL_Const_ITER end() const;
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
};


template <typename T>
SSLL<T>::SSLL(){
	head = NULL;
	tail = NULL;
}


template <typename T>
SSLL<T>::~SSLL(){
}


template <typename T>
T SSLL<T>::replace(const T &e, int position){
	if (position < 0 || position > size()){
		throw out_of_range("Invalid Position");
	}
	node *current = head;
	node *prev = NULL;
	int i = 0;
	int temp = 0;
	if (position == 0){
		temp = head->data;
		head->data = e;
	}
	else{
		while (i < position ){
			prev = current;
			current = current->next;
			i++;
		}
		 temp = current->data;
		node *newNode = new node();
		newNode->data = e;
		newNode->next = current->next;
		current = newNode;
		prev->next = current;
	}
		return temp;
}


template <typename T>
void SSLL<T>::insert(const T &e, int position){
	if (position < 0 || position > size()){
		throw out_of_range("Invalid Position");
	}
	node *current = head;
	node *prev = NULL;
	int i = 0;
	if (position == 0){
		push_front(e);
	}
	else if (position == size() ){
		push_back(e);
	}
	else{
		while (i < position ){
			prev = current;
			current = current->next;
			i++;
		}
		node *newNode = new node();
		newNode->data = e;
		prev->next = newNode;
		newNode->next = current;
	}

}


template <typename T>
void SSLL<T>::push_front(const T &e){
	node *newNode = new node();
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
void SSLL<T>::push_back(const T &e){
	node *newNode = new node();
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
T SSLL<T>::pop_front(){
	if (isEmpty()){
		throw logic_error("List is Empty");
	}
	node *current = head;
	int temp = head->data;
	head = head->next;
	delete current;
	return temp;

}


template <typename T>
T SSLL<T>::pop_back(){
	if (isEmpty()){
		throw logic_error("List is Empty");
	}
	node *current = head;
	while (current->next != tail){
		current = current->next;
	}
	int temp = tail->data;
	tail = current;
	tail->next = NULL;
	delete current->next;
	return temp;

}


template <typename T>
T SSLL<T>::remove(int position){
	if (isEmpty()){
		throw logic_error("List is Empty");
	}
	if (position < 0 || position > size()){
		throw out_of_range("Invalid Position");
	}
	node *current = head;
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
	}
	int temp = current->data;
	prev->next = current->next;
	delete current;
	return temp;
}


template <typename T>
T SSLL<T>::itemAt(int position){
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
bool SSLL<T>::isEmpty() const{
	if (head == NULL){
		return true;
	}
	return false;
}


template <typename T>
int SSLL<T>::size() const{
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
void SSLL<T>::clear(){
	while (isEmpty() != true){
		pop_front();
	}
}


template <typename T>
bool SSLL<T>::equals_function(T e){
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
bool SSLL<T>::contains(T e, bool equals_function) {    
	return SSLL<T>::equals_function(e);
}




template <typename T>
const ostream& SSLL<T>::print(ostream& out)  { 
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
typename SSLL<T>::SSLL_ITER SSLL<T>::begin(){
	return SSLL_ITER(head);
}

template <typename T>
typename SSLL<T>::SSLL_ITER SSLL<T>::end(){
	return SSLL_ITER(tail->next);
}

template <typename T>
typename SSLL<T>::SSLL_Const_ITER SSLL<T>::begin() const{
	return SSLL_Const_ITER(head);
}

template <typename T>
typename SSLL<T>::SSLL_Const_ITER SSLL<T>::end() const{
	return SSLL_Const_ITER(tail->next);
}

#endif