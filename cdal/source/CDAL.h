#ifndef CDAL_H
#define CDAL_H


 
#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;

template <typename T>
class CDAL{
	struct node{
		node(){
			arr = new T[50];
		}
		node* next;
		T *arr;
	};
public:
	class CDAL_ITER {
	private:
		node* myNode;
		T *ptr;
		int index;
		int count;
	public:
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;

		typedef CDAL_ITER self_type;
		typedef CDAL_ITER& self_reference;

		explicit CDAL_ITER(node *n, T *p, int k){
			myNode = n;
			ptr = p;
			index = k;
			count = 0;
			int i = 0;
			while (i != index){
				++ptr;
				i++;
			}

		}
		CDAL_ITER(const CDAL_ITER& src){
			myNode = src.myNode;
		}

		pointer operator->(){ 
			return myNode;
		}

		reference operator *(){
			return *ptr;
		}
		self_reference operator++(){
			if (count==49){
				myNode = myNode->next;
				ptr = &myNode->arr[0];
				count = 0;
			}
			else{
				++ptr;
				++count;
				
			}
			return *this;
		}
		self_type operator++(int){
			CDAL_ITER l = *this;
			if (count==49){
				myNode = myNode->next;
				ptr = &myNode->arr[0];
				count = 0;
			}
			else{
				++ptr;
				++count;
				}
			return l;
		}
		bool operator ==(CDAL_ITER &rhs){
			return ptr == rhs.ptr;
		}
		bool operator!=(CDAL_ITER &rhs){
			return ptr != rhs.ptr;

		}
		self_reference operator=(CDAL_ITER &rhs){   
			return this->myNode = rhs;

		}
		ostream &operator<<(ostream &obj) {     
			obj << this.myNode->data<<endl;
			return obj;
		}
	};
public:
	class CDAL_Const_ITER {
	private:
		const node* myNode;
		const T *ptr;
		int index;
		int count;
	public:
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef const T& reference;
		typedef const T* pointer;
		typedef std::forward_iterator_tag iterator_category;

		typedef CDAL_Const_ITER self_type;
		typedef CDAL_Const_ITER& self_reference;

		explicit CDAL_Const_ITER(node *n, T *p, int k){
			myNode = n;
			ptr = p;
			index = k;
			count = 0;
			int i = 0;
			while (i != index){
				++ptr;
				i++;
			}

		}
		CDAL_Const_ITER(const CDAL_Const_ITER& src){
			myNode = src.myNode;
		}

		pointer operator->(){ 
			return myNode;
		}

		reference operator *(){
			return *ptr;
		}
		self_reference operator++(){
			if (count==49){
				myNode = myNode->next;
				ptr = &myNode->arr[0];
				count = 0;
			}
			else{
				++ptr;
				++count;
				
			}
			return *this;
		}
		self_type operator++(int){
			CDAL_Const_ITER l = *this;
			if (count==49){
				myNode = myNode->next;
				ptr = &myNode->arr[0];
				count = 0;
			}
			else{
				++ptr;
				++count;
				}
			return l;
		}
		bool operator ==(CDAL_Const_ITER &rhs){
			return ptr == rhs.ptr;
		}
		bool operator!=(CDAL_Const_ITER &rhs){
			return ptr != rhs.ptr;

		}
		self_reference operator=(CDAL_Const_ITER &rhs){  
			return this->myNode = rhs;
			

		}
		ostream &operator<<(ostream &obj) {     
			obj << this.myNode->data<<endl;
			return obj;
		}
	};
	
public:
	CDAL();
	~CDAL(); 
	CDAL( const CDAL& src ){
	head=src.head;
	tail=src.tail;
	index=src.index;
	amtNodes=src.amtNodes;
	count=src.count;
	}
	CDAL &operator=(const CDAL &src){
		if (&src == this)
			return *this;
	}
	typedef std::size_t size_t;
	typedef T value_type;
	typedef CDAL_ITER iterator;
	typedef CDAL_Const_ITER const_iterator;
	T replace(T e, int position);
	void insert(T e, int position);
	void push_front(T e);
	void push_back(T e);
	T pop_front();
	T pop_back();
	T remove(int position);
	T itemAt(int position);
	bool isEmpty();
	int size();
	void clear();
	bool contains(T e, bool equals_function);
	bool equals_function(T e);
	const ostream &print(ostream &out);
	CDAL_ITER begin();
	CDAL_ITER end();
	CDAL_Const_ITER begin() const;
	CDAL_Const_ITER end() const;
	T &operator[](int k){    
	node *current = head;
	if(k<50){
	return current->arr[k];
	}
	else{
		while (current != NULL){
			for (int i = 0; i < 50; i++){
				if(i==k){
				return current->arr[k];
				}
			}
			k=k-50;
			if(k<0){
			k=0;
			}
			current = current->next;
			}
		}
	}
	
	T const &operator[](int k) const{    
	node *current = head;
	if(k<50){
	return current->arr[k];
	}
	else{
		while (current != NULL){
			for (int i = 0; i < 50; i++){
				if(i==k){
				return current->arr[k];
				}
			}
			k=k-50;
			if(k<0){
			k=0;
			}
			current = current->next;
			}
		}
	}

private:
	node* head;
	node* tail;
	size_t count;
	int amtNodes;
	int index;
	void shift(node *current);
	void allocNode(T e);
	void indexConvert();
	void insertHelper(node* current, int position, int nodeNumber);
};

template <typename T>
CDAL<T>::CDAL(){
	head = NULL;
	tail = NULL;
	count = 0;
	int amtNodes = 0;
	index = 0;
}
template <typename T>
CDAL<T>::~CDAL(){
}

template <typename T>
void CDAL<T>::indexConvert(){
	if (index == 50){
		index = 0;
	}
	else{
		index++;
	}
}

template <typename T>
void CDAL<T>::shift(node *current){
	T temp = 0;
	T temp1 = 0;
	node *trail = NULL;
	int nodeNumber = 0;
	while (current != NULL){
		temp = current->arr[49];
		for (int i = 49; i != 0; i--){
			current->arr[i] = current->arr[i - 1];
		}

		trail = current;
		nodeNumber++;
		current = current->next;

		if (nodeNumber != 1 && nodeNumber - 1 != amtNodes){
			trail->arr[0] = temp1;
		}
		if (index == 50 && nodeNumber == amtNodes){
			allocNode(temp);
		}
		temp1 = temp;
	}
}

template <typename T>
void CDAL<T>::insertHelper(node* current, int position, int nodeNumber){
	T temp = 0;
	T temp1 = 0;
	node *trail = NULL;
	int check = nodeNumber;
	while (current != NULL){
		temp = current->arr[49];
		for (int i = 49; i != position - 1; i--){
			current->arr[i] = current->arr[i - 1];
		}
		position = 1;
		trail = current;
		nodeNumber++;
		current = current->next;

		if (nodeNumber - 1 != check && nodeNumber - 1 != amtNodes){
			trail->arr[0] = temp1;
		}
		if (index == 50 && nodeNumber == amtNodes){
			allocNode(temp);
		}
		temp1 = temp;
	}

}

template <typename T>
void CDAL<T>::allocNode(T e){

	node* newNode = new node();
	newNode->next = NULL;
	tail->next = newNode;
	index = 0;
	newNode->arr[index] = e;
	tail = newNode;
	amtNodes++;
	count++;
}

template <typename T>
void CDAL<T>::insert(T e, int position){
	if (position < 0 || position > size() ){
		throw out_of_range("Invalid Position");
	}
	node *current = head;
	int loops = 0;
	if (position == 0){
		push_front(e);
	}
	else if (position == size()){
		push_back(e);
	}
	else{
		int at = position / 50;
		int mod = position % 50;       
		for (int i = 0; i < at; i++){
			current = current->next;
			loops++;
		}
		insertHelper(current, mod, loops);
		current->arr[mod] = e;
		indexConvert();

	}

}

template <typename T>
T CDAL<T>::replace(T e, int position){
	if (position < 0 || position > size()){
		throw out_of_range("Invalid Position");
	}
	node *current = head;
	int at = position / 50;
	int mod = position % 50;       
	for (int i = 0; i < at; i++){
		current = current->next;
	}
	T temp = current->arr[mod - 1];
	current->arr[mod] = e;
	return temp;
}

template <typename T>
void CDAL<T>::push_front(T e){
	if (head == NULL){
		node *newNode = new node();
		newNode->arr[count] = e;
		newNode->next = NULL;
		head = newNode;
		tail = newNode;
		count++;
		index++;
		amtNodes++;
	}
	else{
		node* current = head;
		if (amtNodes > 1 || index == 50){
			shift(current);
			indexConvert();
			count++;
		}
		else{
			for (int i = 49; i != 0; i--){
				head->arr[i] = head->arr[i - 1];
			}
			indexConvert();
			count++;
		}
		head->arr[0] = e;
	}



}

template <typename T>
void CDAL<T>::push_back(T e){

	if (head == NULL){
		node *newNode = new node();
		newNode->arr[count] = e;
		newNode->next = NULL;
		head = newNode;
		tail = newNode;
		count++;
		index++;
		amtNodes++;
	}
	else{
		if (index == 50){
			allocNode(e);
			indexConvert();
		}
		else{
			tail->arr[index] = e; 
			count++;
			indexConvert();
		}
	}
}


template <typename T>
T CDAL<T>::pop_front(){
	if (isEmpty()){
		throw logic_error("List is Empty");
	}
	node *current = head;
	T temp = current->arr[0];
	current->arr[0] = NULL;
	T temp1 = 0;
	T temp2 = 0;
	if (amtNodes > 1){
		node *current = head;
		bool flag = false;
		if (index == 1){
			//index = 5;
			flag = true;
		}
		while (current != NULL){
			if (current->next != NULL){
				temp1 = current->next->arr[0];
			}
			for (int i = 1; i <= 50; i++){
				current->arr[i - 1] = current->arr[i];
			}
			if (current->next == NULL && index == 5){
				current->arr[49] = temp2;
			}
			if (temp1 != 0){
				current->arr[49] = temp1;
			}
			current = current->next;
			temp1 = 0;
		}
		index--; 
		if (flag == true){
			tail->next = NULL;
			index = 50;
		}

	}
	else{
		for (int i = 1; i <= 50; i++){
			head->arr[i - 1] = head->arr[i];
		}
		index--;
	}
	count--;
	return temp;
}

template <typename T>
T CDAL<T>::pop_back(){
	if (isEmpty()){
		throw logic_error("List is Empty");
	}
	T temp = 0;
	if (index == 0 && amtNodes>1){
		node* current = head;
		while (current->next->next != NULL){
			current = current->next;
		}
		tail = current;
		
		amtNodes--;
		index = 50;
	}
	temp = tail->arr[index - 1];
	tail->arr[index - 1] = NULL;
	index--;
	count--;
	return temp;
}

template <typename T>
T CDAL<T>::remove(int position){   
	if (isEmpty()){
		throw logic_error("List is Empty");
	}
	if (position < 0 || position > size()){
		throw out_of_range("Invalid Position");
	}
	bool flag = false;
	int temp = 0;
	int temp1 = 0;
	node *current = head;
	node *trail = NULL;
	if (position == 0){
		pop_front();
	}
	else if(position==size()-1){
		pop_back();
	}
	else{
		int nodeNumber = 0;
		int at = position / 50;
		int mod = position % 50;       
		for (int i = 0; i < at; i++){
			current = current->next;
			nodeNumber++;
		}
		temp = current->arr[mod];
		if (nodeNumber == at){  
			for (int i = mod+1; i < index; i++){  
				current->arr[i - 1] = current->arr[i];
			}
		}
		else{
			while (current != NULL){
				for (int i = mod; i < 50; i++){  
					current->arr[i - 1] = current->arr[i];
				}
				mod = 0;
				if (current->next != NULL){
					temp1 = current->next->arr[0];
					current->arr[49] = temp1;
				}
				if (index == 50){
					current->arr[49] = NULL;
					flag = true;
				}
				if (index == 1 && nodeNumber == amtNodes){
					index = 50;
					delete current->next;
					tail = trail;
				}
				nodeNumber++;
				trail = current;
				current = current->next;
			}
		}
	}
	if (flag == true){
		index--;
	}
	return temp;
}

template <typename T>
T CDAL<T>::itemAt(int position){
	if (position < 0 || position > size()+1){
		throw out_of_range("Invalid Position");
	}
	node *current = head;
	int at = position / 50;
	int mod = position % 50;       
	for (int i = 0; i < at; i++){
		current = current->next;
	}
	return current->arr[mod];
}

template <typename T>
bool CDAL<T>::isEmpty(){
	if (head == NULL){
		return true;
	}
	return false;
}

template <typename T>
int CDAL<T>::size(){
	return count;
}

template <typename T>
void CDAL<T>::clear(){         
	node *current = head;
	while (current != NULL){
		delete current->arr;
		head=head->next;
		current=current->next;
	}
}

template <typename T>
bool CDAL<T>::equals_function(T e){
	node *current = head;
	int i = 0;
	while (current != NULL){
		if (current->arr[i] == e){
			return true;
		}
		i++;
		if (i == 50){
			i = 0;
			current = current->next;
		}
	}
	return false;
}

template <typename T>
bool CDAL<T>::contains(T e, bool equals_function) {    
	return CDAL<T>::equals_function(e);
}

template <typename T>
const ostream& CDAL<T>::print(ostream &out) {
	int c = 0;
	node *current = head;
	if (isEmpty() == true){
		out << "<Empty>" << endl;
	}
	else{
		out << "[";
		while (current != NULL){
			for (int i = 0; i < 50; i++){
				if (i != size()-1){
					out << current->arr[i] << ",";
				}
				else{
				out<<current->arr[i]<<"]";
				}
				c++;
			}
			current = current->next;
		}
	}
	return out;
}

template <typename T>
typename CDAL<T>::CDAL_ITER CDAL<T>::begin(){
	return CDAL_ITER(head, head->arr, 0);

}

template <typename T>
typename CDAL<T>::CDAL_ITER CDAL<T>::end(){
	return CDAL_ITER(tail, tail->arr, index);
}

template <typename T>
typename CDAL<T>::CDAL_Const_ITER CDAL<T>::begin() const{
	return CDAL_Const_ITER(head, head->arr, 0);

}

template <typename T>
typename CDAL<T>::CDAL_Const_ITER CDAL<T>::end() const{
	return CDAL_Const_ITER(tail, tail->arr, index);
}


#endif