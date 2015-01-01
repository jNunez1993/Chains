#ifndef SDAL_H
#define SDAL_H

#include <iostream>
#include <stdexcept>
#include <exception>
using namespace std;


template <typename T>
class SDAL{
public:
	class SDAL_ITER {
	private:
		T *ptr;
	public:
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef SDAL_ITER self_type;
		typedef SDAL_ITER& self_reference;

		explicit SDAL_ITER(T* l){
			ptr = l;
		}
		SDAL_ITER(const SDAL_ITER& src){
			ptr = src.ptr;
		}

		pointer operator->(){
		return *ptr;
		}
		
		value_type operator*(){
			return *ptr;
		}
		pointer operator++(){
			ptr = ptr + 1;
			return ptr;
		}
		pointer operator++(int){
			T *ptr_ = ptr;
			ptr = ptr + 1;
			return ptr_;
		}

		self_reference operator=(SDAL_ITER &rhs){
			ptr = rhs.ptr;
			return ptr;
		}
		ostream &operator<<(ostream &obj){       
			obj << this.ptr << endl;
			return obj;
		}

		bool operator!=(SDAL_ITER &rhs){
			return ptr != rhs.ptr;
		}

		bool operator==(SDAL_ITER &rhs){
			return ptr == rhs.ptr;
		}

		T &operator[](int i){
			T *ptr_ = ptr;
			int k = 1;
			while (k != i){
				ptr_++;
				k++;
			}
			return *ptr_;
		}

	};
public:
	class SDAL_Const_ITER {
	private:
		const T *ptr;
	public:
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef const T& reference;
		typedef const T* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef SDAL_Const_ITER self_type;
		typedef SDAL_Const_ITER& self_reference;

		explicit SDAL_Const_ITER(T* l){
			ptr = l;
		}
		SDAL_Const_ITER(const SDAL_Const_ITER& src){
			ptr = src.ptr;
		}
		
		pointer operator->(){
		return *ptr;
		}

		value_type operator*(){
			return *ptr;
		}
		pointer operator++(){       
			ptr = ptr + 1;
			return ptr;
		}
		pointer operator++(int){     
			const T* ptr_ = ptr;
			ptr = ptr + 1;
			return ptr_;
		}

		self_reference operator=(SDAL_Const_ITER &rhs){
			ptr = rhs.ptr;
			return ptr;
		}
		ostream &operator<<(ostream &obj){       
			obj << this.ptr << endl;
			return obj;
		}

		bool operator!=(SDAL_Const_ITER &rhs){
			return ptr != rhs.ptr;
		}

		bool operator==(SDAL_Const_ITER &rhs){
			return ptr == rhs.ptr;
		}
		T  const &operator[](int i) const {
			int k = 0;
			T* ptr_ = ptr;
			while (k != i){
				ptr_++;
				k++;
			}
			return *ptr_;
		}
	};

public:
	SDAL();
	SDAL(int arrSize);
	SDAL(const SDAL &src){
	arr=src.arr;
	arrSize=src.arrSize;
	count=src.count;
	}
	SDAL &operator=(const SDAL &src){
	if (&src == this)
			return *this;
	}
	typedef std::size_t size_t;
	typedef T value_type;
	typedef SDAL_ITER iterator;
	typedef SDAL_Const_ITER const_iterator;
	T replace(const T& e, int position);
	void insert(const T& e, int position);
	void push_front(const T& e);
	void push_back(const T& e);
	T pop_front();
	T pop_back();
	T remove(int position);
	T itemAt(int position) const;
	bool isEmpty() const;
	int size() const;
	int sizeofArray() const;
	void clear();
	bool equals_function(T e);
	bool contains(T e, bool equals_function);
	const ostream& print(ostream &out);
	SDAL_ITER begin();
	SDAL_ITER end();
	SDAL_Const_ITER begin() const;
	SDAL_Const_ITER end() const;
	T &operator[](int i){
		return arr[i];
		}
	T  const &operator[](int i) const {
		return arr[i];
		}
private:
	T *arr;
	int arrSize;
	size_t count;
	void Reduce();
	bool isFull();
};



template <typename T>
SDAL<T>::SDAL(){
	arrSize = 50;
	arr = new T[arrSize];
	count = 0;
}

template <typename T>
SDAL<T>::SDAL(int arrSize){
	arr = new T[arrSize];
	count = 0;
}

template <typename T>
void SDAL<T>::Reduce(){
	arrSize = arrSize*.5;
	T *newArr = new T[arrSize];
	for (int i = 0; i < arrSize; i++){
		newArr[i] = arr[i];
	}
	delete []arr;  
	arr = newArr;

}

template <typename T>
bool SDAL<T>::isFull(){
	if (count == arrSize){
		return true;
	}
	return false;
}

template <typename T>
T SDAL<T>::replace(const T& e, int position){
	if (position < 0 || position > size()){
		throw out_of_range("Invalid position");
	}
	T temp = arr[position ];
	arr[position ] = e;
	return temp;
}

template <typename T>
void SDAL<T>::insert(const T& e, int position){
	if (position < 0 || position > size() ){
		throw out_of_range("Invalid position");
	}
	if (isFull() == true){
		int oldSize = arrSize;
		arrSize = arrSize*1.5;
		T *newArr = new T[arrSize];
		for (int i = 0; i < oldSize; i++){
			newArr[i] = arr[i];
		}
		delete []arr;
		arr = newArr;
	}
	if (position == 0){                
		push_front(e);                  
		}
	else if (position == size() ){
		push_back(e);
	}
	else{
		for (int i = count; i != position ; i--){
			arr[i] = arr[i - 1];
		}
		arr[position ] = e;
		count++;
	}

}

template <typename T>
void SDAL<T>::push_front(const T& e){

	if (count < arrSize){
		for (int i = count; i != 0; i--){
			arr[i] = arr[i - 1];
		}
		arr[0] = e;
	}
	else{
		int oldSize = arrSize;
		arrSize = arrSize*1.5;
		T *newArr = new T[arrSize];
		for (int i = 0; i < oldSize; i++){
			newArr[i + 1] = arr[i];
		}
		newArr[0] = e;
		delete[]arr;
		arr = newArr;
	}
	count++;
}


template <typename T>
void SDAL<T>::push_back(const T& e){
	if (count < arrSize){
		arr[count] = e;
	}
	else{
		int oldSize = arrSize;
		arrSize = arrSize*1.5;
		T *newArr = new T[arrSize];
		for (int i = 0; i < oldSize; i++){
			newArr[i] = arr[i];
		}
		newArr[oldSize] = e;
		delete[]arr;
		arr = newArr;
	}
	count++;

}

template <typename T>
T SDAL<T>::pop_front(){
	if (isEmpty()){
		throw logic_error("List is empty");
	}
	if (arrSize >= 100 && count <= arrSize*.5){
		Reduce();
	}
	T temp = arr[0];
	for (int i = 1; i < count; i++){   
		arr[i - 1] = arr[i];           
	}
	arr[count-1]=NULL;  
	count--;
	return temp;
}

template <typename T>
T SDAL<T>::pop_back(){
	if (isEmpty()){
		throw logic_error("List is empty");
	}
	if (arrSize >= 100 && count <= arrSize*.5){
		Reduce();
	}
	T temp = arr[count-1];                
	arr[count-1] = NULL;     
	count--;
	return temp;
}

template <typename T>
T SDAL<T>::remove(int position){ 
	T temp;
	if (position < 0 || position > size()){
		throw out_of_range("Invalid position");
	}
	if (arrSize >= 100 && count <= arrSize*.5){     
		Reduce();
	}
	if(position==0){
	temp=pop_front();
	}
	else if(position=size()-1){
	temp=pop_back();
	}
	else{
	temp = arr[position - 1];
	arr[position ] = NULL;
	for (int i = position; i < count; i++){
		arr[i - 1] = arr[i];
	}
	count--;
	}
	return temp;
}

template <typename T>
T SDAL<T>::itemAt(int position) const{
	if (position < 0 || position > size()){
		throw out_of_range("Invalid position");
	}
	return arr[position ];
}

template <typename T>
bool SDAL<T>::isEmpty() const{
	if (count == 0){
		return true;
	}
	return false;
}

template <typename T>
int SDAL<T>::size() const{
	return count;
}

template <typename T>
int SDAL<T>::sizeofArray() const{
	return arrSize;
}

template <typename T>
void SDAL<T>::clear(){
	for (int i = 0; i < count; i++){
		arr[i] = NULL;
	}
	count = 0;
}

template <typename T>
bool SDAL<T>::equals_function(T e){
	for (int i = 0; i < size(); i++){
		if (arr[i] == e){
			return true;
		}
	}
	return false;
}

template <typename T>
bool SDAL<T>::contains(T e, bool equals_function) {    
	return SDAL<T>::equals_function(e);
}


template <typename T>
const ostream& SDAL<T>::print(ostream &out) {
	if(size()==0){
	cout<<"<Empty List>"<<endl;
	}
	else{
	out << "[";
		for (int i = 0; i < size(); i++){
			if(i!=size()-1){
			out << arr[i] << ",";
			}
			else{
			out<< arr[i] << "]";
			}
		}
	}
	return out;
}


template <typename T>
typename SDAL<T>::SDAL_ITER SDAL<T>::begin(){
	return SDAL_ITER(arr);
}

template <typename T>
typename SDAL<T>::SDAL_ITER SDAL<T>::end(){
	return SDAL_ITER(arr + count);
}

template <typename T>
typename SDAL<T>::SDAL_Const_ITER SDAL<T>::begin() const{
	return SDAL_Const_ITER(arr);
}

template <typename T>
typename SDAL<T>::SDAL_Const_ITER SDAL<T>::end() const{
	return SDAL_Const_ITER(arr + count);
}

#endif
