#include <iostream>
using namespace std;

int NChE; //�������

template <class T>
class List
{
protected:
	T* Arr_of_values;			//��������� �� ������ �������� ��������� ������
	int* Arr_of_idx;			//��������� �� ������ �������� ��������� ������
	int size;					//��������� ������ ������
	int count;					//������� ������ ������
	int idx_first_value;		//������ ������� ��������
	int idx_last_value;			//������ ���������� ��������
	int idx_first_empty_value;	//����� ������� �������
	//----------------------------------------------------------------------------------------------------------
	int return_index(int ser_number)	//���������� ������ ��-�� �� ��� ����������� ������
	{
		NChE = 0;
		int j = idx_first_value;
		for (int i = 0; j != -1; i++)//���� �� ��������� ���������� ������� � �������
		{
			NChE++;
			if (ser_number == i) return j;//����� ��������� ����������� ������ ��-��, ���������� ��� ������
			j = Arr_of_idx[j];//����������� ������ ���������� �� ������� ��-��
		}
		return -1;//���� �� �����
	};
	//----------------------------------------------------------------------------------------------------------
public:
	List(int sizeArr);							//����������� � �����������
	List(const List<T>& L);						//����������� ����������� ������ List,
	//������� ��������� ������ �� ������ ������ ������ List � �������� ���������. 
	//���� ����������� ������� ����� ������ List, ������������� ��� ���������� ������� L
	~List();									//����������
	bool add_val(T value);						//�������� �������� ��-��
	bool add_val_by_num(T value, int por_num);	//�������� �������� ��-�� �� ��� ����������� ������
	bool check_value(T value);					//��������� ������� ��-�� �� ��� ��������
	T read_val_by_num(int por_num);				//��������� �������� ��-�� �� ��� ����������� ������
	int get_pos_by_val(T value);				//�������� ���������� ����� ��-�� �� ��� ��������
	bool change_val_by_num(int por_num, T value);//�������� �������� ��-�� �� ��� ����������� ������
	bool delete_val(T value);					//������� ��-� �� ��� ��������
	bool delete_val_by_num(int por_num);		//������� ��-� �� ��� ����������� ������
	void clear_list();							//������� ������
	void print();								//������
	int ret_size();								//������ ������ ������
	int get_num_of_check_elem();				//������� ���-�� ��������
	bool check_list_empty();					//�������� ������ �� �������

	class Iterator
	{
		List* L_ptr;	//��������� �� ������ ������
		int idx_curr_cell;		//������ ������� ������
		bool fl_end;		//���� ��������� ���������
	public:
		Iterator(List<T>* L_obj);
		bool begin(List<T>* L_obj);
		bool operator++();
		T& operator*();
		bool end();
	};
	friend class Iterator;

	class ReverseIterator
	{
		List* L_ptr;	//��������� �� ������ ������
		int idx_curr_cell;		//������ ������� ������
		bool fl_end;		//���� ��������� ���������
	public:
		ReverseIterator(List<T>* L_obj);
		bool Rbegin(List<T>* L_obj);
		bool operator++();
		T& operator*();
		bool Rend();
	};
	friend class ReverseIterator;
};

template<class T> List<T>::Iterator::Iterator(List* L_obj) : L_ptr(L_obj) {
	fl_end = true;
	idx_curr_cell = -1;
}

template<class T> bool List<T>::Iterator::begin(List* L_obj) {
	L_ptr = L_obj;
	idx_curr_cell = L_ptr->idx_first_value;
	if (idx_curr_cell == -1) return false;
	fl_end = false;
	return true;
}

template<class T> bool List<T>::Iterator::operator++() {
	if (fl_end == true) return false;
	idx_curr_cell = L_ptr->Arr_of_idx[idx_curr_cell];
	if (idx_curr_cell == -1) fl_end = true;
	return true;
}

template<class T> T& List<T>::Iterator::operator*() {
	return L_ptr->Arr_of_values[idx_curr_cell];
}

template<class T> bool List<T>::Iterator::end() {
	return fl_end;
}

template<class T> List<T>::ReverseIterator::ReverseIterator(List* L_obj) : L_ptr(L_obj) {
	fl_end = true;
	idx_curr_cell = -1;
}

template<class T> bool List<T>::ReverseIterator::Rbegin(List* L_obj) {
	L_ptr = L_obj;
	idx_curr_cell = L_ptr->ret_size() - 1;
	if (idx_curr_cell == -1) return false;
	fl_end = false;
	return true;
}

template<class T> bool List<T>::ReverseIterator::operator++() {
	if (fl_end == true || idx_curr_cell == 0) { fl_end = true; return false; }
	if (idx_curr_cell == 1) idx_curr_cell = L_ptr->idx_first_value;
	else idx_curr_cell = L_ptr->Arr_of_idx[idx_curr_cell - 2];
	if (idx_curr_cell == -1) fl_end = true;
	return true;
}

template<class T> T& List<T>::ReverseIterator::operator*() {
	return L_ptr->Arr_of_values[idx_curr_cell];
}

template<class T> bool List<T>::ReverseIterator::Rend() {
	return fl_end;
}



//=========================================================================================================
template <class T> List<T>::List(int sizeArr) //�����������
{
	idx_first_value = -1;//������ ���� ����
	idx_last_value = -1;//������ ���� ����
	size = sizeArr;//����������� ���������� size ��������, ���������� � �����������
	Arr_of_values = new T[size];//������� ������������ ������ Arr_of_values ���� T �������� size ��� �������� �������� ��������� ������
	Arr_of_idx = new int[size];//������� ������������ ������ Arr_of_idx ���� int �������� size ��� �������� �������� ��������� ������
	idx_first_empty_value = 0;//������ ������ ��-� ������ ��������� � ������ �������
	//size = size0;//������� ������ ������
	for (int i = 0; i < size; i++) { Arr_of_idx[i] = i + 1; }//�������������� ������ ���, 
	//����� ������ ��-� �������� ������ ���������� ��-�� � ������
	Arr_of_idx[size - 1] = -1;//����� ������
	return;
};
//---------------------------------------------------------------------------------------------------------
template <class T> List<T>::~List() //����������
{
	delete Arr_of_values;
	delete Arr_of_idx;
	return;
};
//---------------------------------------------------------------------------------------------------------
template <class T> List<T>::List(const List<T>& L)	//����������� �����������
{
	//�������� �������� �� ������� L � ������� ������
	size = L.size;
	idx_first_value = L.idx_first_value;
	idx_last_value = L.idx_last_value;
	idx_first_empty_value = L.idx_first_empty_value;
	//�������� ������ ��� �������� Arr_of_values � Arr_of_idx ������ �� �������, ��� � ������ L
	Arr_of_values = new T[size];
	Arr_of_idx = new int[size];
	//�������� �������� ��������� �������� Arr_of_values � Arr_of_idx �� ������� L � ������� ������
	for (int i = 0; i < size; i++)
	{
		Arr_of_values[i] = L.Arr_of_values[i];
		Arr_of_idx[i] = L.Arr_of_idx[i];
	}
};
//---------------------------------------------------------------------------------------------------------
template <class T> int List<T>::ret_size() //������ ������ ������
{
	count = 0;
	int j = 0;//��� �����������
	for (count, j = idx_first_value; j != -1; count++) j = Arr_of_idx[j];
	return count;
};
//---------------------------------------------------------------------------------------------------------
template <class T> void List<T>::clear_list()//������� ������
{
	idx_first_value = -1; // ������������� ������ ������� �������� � -1, ����� �������, ��� ������ ����.
	idx_last_value = -1; //������������� ������ ������� �������� � - 1, ����� �������, ��� ������ ����.
	idx_first_empty_value = 0; // ������������� ������ ������� ������� ��-�� � 0, ��� ��� ����� ������� ��� �������� ����� ������ ����������.
	delete Arr_of_idx; delete Arr_of_values; // ������� ������� �������� � ��������, ����� ���������� ������.
	Arr_of_idx = new int[size]; Arr_of_values = new T[size]; // �������� ����� ������ ��� �������� �������� � �������� � �������� ��������.
	//size = size0; // ��������� ���������� size, ����� ��� �������� �������� ������ ������.
	for (int i = 0; i < size; i++) { Arr_of_idx[i] = i + 1; } // �������������� ������ �������� ���, ����� ������ ��-� �������� �� ���������.
	Arr_of_idx[size - 1] = -1; // ������������� ��������� ��-� ������� �������� � -1, ����� ���������� ����� ������.
	return; // ��������� �������.
};

//---------------------------------------------------------------------------------------------------------
template <class T> bool List<T>::check_list_empty()//�������� ������ �� �������
{
	if (idx_first_value == -1) return true;
	else return false;
};
//---------------------------------------------------------------------------------------------------------
template <class T> bool List<T>::check_value(T value) //��������� ������� ��-�� �� ��� ��������
{
	int j = idx_first_value; // �������������� ���������� j �������� ������� ��-�� � ������.
	NChE = 0;
	for (int i = 0; j != -1; i++) // �������� ����, ������� ����� ������������, ���� j �� ������ ������ -1 (��� �������� ����� ������).
	{
		NChE++;
		if (Arr_of_values[j] == value) return true; // ���� �������� �������� ��-�� ����� ��������� ��������, ���������� true, ��� �������� ������� ��-�� � ������.
		j = Arr_of_idx[j]; // ��������� � ���������� �������� ������, �������� �������� j �� ������� ���������� ��-��.
		//NChE++; // ����������� �������� ��� ��������.
	}
	return false; // ���� ���� ����������, � ��-� �� ��� ������, ���������� false, ��� �������� ���������� ��-�� � ������.
};

//---------------------------------------------------------------------------------------------------------
template <class T> T List<T>::read_val_by_num(int por_num)//��������� �������� ��-�� �� ��� ����������� ������
{
	int j = idx_first_value; // �������������� ���������� j �������� ������� ��-�� � ������.
	for (int i = 0; j != -1; i++) // �������� ����, ������� ����� ������������, ���� j �� ������ ������ -1 (��� �������� ����� ������).
	{
		if (i == por_num) return Arr_of_values[j]; // ���� ������� ���������� ����� i ����� ��������� ����������� ������ por_num, ���������� �������� ��-�� � ���� �������.
		j = Arr_of_idx[j]; // ��������� � ���������� �������� ������, �������� �������� j �� ������� ���������� ��-��.
	}
	throw(111); // ���� �� ������� ����� ��-� � �������� ���������� �������, ������������ ����������.
};

//---------------------------------------------------------------------------------------------------------
template <class T> bool List<T>::change_val_by_num(int por_num, T value)//�������� �������� ��-�� �� ��� ����������� ������
{
	int j = idx_first_value; // �������������� ���������� j �������� ������� ��-�� � ������.
	for (int i = 0; j != -1; i++) // �������� ����, ������� ����� ������������, ���� j �� ������ ������ -1 (��� �������� ����� ������).
	{
		if (i == por_num) // ���� ������� ���������� ����� i ����� ��������� ����������� ������ por_num,
		{
			Arr_of_values[j] = value; // �������� �������� ��-�� �� ������� j �� �������� �������� value.
			return true; // ���������� true, �������� �� �������� ��������� ��������.
		}
		j = Arr_of_idx[j]; // ��������� � ���������� �������� ������, �������� �������� j �� ������� ���������� ��-��.
	}
	return false; // ���� ���� ����������, � ��-� � �������� ���������� ������� �� ��� ������, ���������� false.
};

//---------------------------------------------------------------------------------------------------------
template <class T> int List<T>::get_pos_by_val(T value) // �������� ���������� ����� ��-�� �� ��� ��������
{
	int j = idx_first_value; // �������������� ���������� j �������� ������� ��-�� � ������.

	while (j != -1) // �������� ����, ������� ����� ������������, ���� j �� ������ ������ -1 (��� �������� ����� ������).
	{
		if (Arr_of_values[j] == value) // ���������, ����� �� �������� �������� ��-�� ��������� ��������.
			return j; // ���� �������� �������� ��-�� ����� ��������� ��������, ���������� ��� ���������� ����� j.

		j = Arr_of_idx[j]; // ��������� � ���������� �������� ������, �������� �������� j �� ������� ���������� ��-��.
	}

	return -1; // ���� �������� �� ���� ������� � ������, ���������� -1, ����� ������� �� ����.
}

//---------------------------------------------------------------------------------------------------------
template <class T> bool List<T>::add_val(T value)//�������� �������� ��-��
{
	if (idx_first_empty_value == -1)//���� ������ ����� ���
	{
		return false;
	}
	int j = idx_first_empty_value; // ����������� ���������� j ������ ������ ������ ������.
	idx_first_empty_value = Arr_of_idx[j]; // ��������� ������ ������ ������ ������ �� ������ ��������� ������ ������.
	Arr_of_values[j] = value; // ����������� �������� � ������� j �������� ��������.
	int k = idx_first_value; // ����������� ���������� k ������ ������� �������� � ������.
	if (k == -1) { idx_first_value = 0; Arr_of_idx[0] = -1; return true; } // ���� ������ ����, ����������� idx_first_value �������� 0 � Arr_of_idx[0] �������� -1, ��������� ������ � ����� ������ ��������������.
	while (Arr_of_idx[k] != -1) { k = Arr_of_idx[k]; } // ��������� � ���������� �������� � ������.
	Arr_of_idx[k] = j; // ������������� ������ ����������� ��-�� � ������ �� j.
	Arr_of_idx[j] = -1; // ������������� ������ j ��� ����� ������.
	return true;
}

//---------------------------------------------------------------------------------------------------------
template <class T> bool List<T>::delete_val(T value)//������� ��-� �� ��� ��������
{
	if (idx_first_value == -1) return false; // ���������, ���� �� ������. ���� ������ ����, ���������� false.
	int j = idx_first_value;// �������������� j �������� ������� ��-�� ������.
	int temp;	


	if (Arr_of_values[idx_first_value] == value) // ���������, ����� �� �������� ������� ��-�� ������ ��������� �������� ��� ��������.
	{
		int tmp_f = idx_first_empty_value; // ��������� ������ ������ ������ ������ �� ��������� ����������.
		idx_first_empty_value = idx_first_value; // ��������� ������ ������ ������ ������ �� ������ ������� ��-�� ������.
		idx_first_value = Arr_of_idx[idx_first_value]; // ��������� ������ ������� ��-�� ������ �� ������ ���������� ��-��.
		Arr_of_idx[idx_first_empty_value] = tmp_f; // ����������� ������� ������� ��-�� ������ ������ ������ ������ ������.
		return true; // ���������� true, �������� �� �������� �������� ��-��.
	}

	while (j != -1) // ���� �� ��������� ����� ������,
	{
		if (Arr_of_values[j] == value) // ���� �������� �������� ��-�� ����� ��������� �������� ��� ��������,
		{
			Arr_of_idx[temp] = Arr_of_idx[j]; // ������� ������� ��-� �� ������, ������������ ��������� ����������� ��-�� �� ���������.
			Arr_of_idx[j] = idx_first_empty_value; // �������� ������ �������� ��-�� ��� ������.
			idx_first_empty_value = j; // ��������� ������ ������ ������ ������ �� ������ �������� ��-��.
			return true; // ���������� true, �������� �� �������� �������� ��-��.
		}
		temp = j; // ��������� ������ �������� ��-�� ��� ����������.
		j = Arr_of_idx[j]; // ��������� � ���������� �������� ������.
	}
	return false; // ���� ��-� �� ������, ���������� false.
}

//---------------------------------------------------------------------------------------------------------
template <class T> bool List<T>::add_val_by_num(T value, int por_num)//�������� �������� ��-�� �� ��� ����������� ������
{
	NChE = 0;
	if (por_num == 0 && idx_first_value == -1) { // ���� ���������� ����� ����� 0 � ������ ����
		idx_first_value = 0; // ������������� ������ ������� �������� � ������ ��� 0
		idx_first_empty_value = 1; // ������������� ������ ������ ������ ������ ��� 1
		Arr_of_idx[0] = -1; // ������������� ������ ������� ��-�� � -1, ��������� ����� ������
		Arr_of_values[0] = value; // ����������� ������� �������� � ������ �������� ��������
		return true; // ���������� true, �������� �� �������� ���������� ��-��
	}
	if (por_num == ret_size()) // ���� ���������� ����� ����� �������� ������� ������
	{
		this->add_val(value); // ��������� �������� � ����� ������ � ������� ������ add_val()
		return true; // ���������� true, �������� �� �������� ���������� ��-��
	}

	int pred_j = return_index(por_num); // �������� ������ ��-�� �� ��������� ����������� ������

	if (pred_j == -1) // ���� ������� �� ��������� �������� ������
		return false; // ���������� false, �������� �� ������� ���������� ��-��

	if (idx_first_empty_value == -1) // ���� ��� ������ ����� � ������
	{
		return false;
	}

	int j = idx_first_empty_value; // ��������� ������ ������ ������
	idx_first_empty_value = Arr_of_idx[j]; // ��������� ������ ������ ������ ������ �� ������ ��������� ������ ������

	Arr_of_values[j] = Arr_of_values[pred_j]; // �������� �������� ��-�� �� ������� por_num � ������ ������ ������
	Arr_of_values[pred_j] = value; // ��������� �������� ��-��

	int temp = Arr_of_idx[pred_j]; // ��������� ������ ��-��, ���������� �� ��-��� �� ������� por_num
	Arr_of_idx[pred_j] = j; // ��������� ������ ��-��, ���������� �� ��-��� �� ������� por_num
	Arr_of_idx[j] = temp; // ������������� ������ ������ ��-�� �� ����������� ������ ���������� ��-��

	return true; // ���������� true, �������� �� �������� ���������� ��-��
}

//---------------------------------------------------------------------------------------------------------
template <class T> bool List<T>::delete_val_by_num(int por_num)//������� ��-� �� ��� ����������� ������
{
	int del_j; // ��������� ���������� ��� �������� ������� ��-��, ������� ����� �������
	NChE = 0;
	if (por_num == 0) // ���� ���������� ����� ��-�� ����� 0
	{
		del_j = idx_first_value; // ����������� ������� ���������� ��-�� ������ ������� ��-�� ������
		if (idx_first_value == -1) // ���� ������ ����
			return false; // ���������� false
		idx_first_value = Arr_of_idx[idx_first_value]; // ��������� ������ ������� ��-�� ������ �� ������ ���������� ��-��
		Arr_of_idx[del_j] = idx_first_empty_value; // ������������� ������ ���������� ��-�� �� ������ ������ ������ ������
		idx_first_empty_value = del_j; // ��������� ������ ������ ������ ������ �� ������ ���������� ��-��
		return true; // ���������� true, �������� �� �������� �������� ��-��
	}

	int pred_j = return_index(por_num - 1); // ������� ������ ����������� ��-�� �� ����������� ������

	del_j = Arr_of_idx[pred_j]; // ��������� ������ ���������� ��-��
	NChE++;
	if (del_j == -1) // ���� ������ ���������� ��-�� ����� -1
		return false; // ���������� false, �������� �� ������� �������� ��-��

	Arr_of_idx[pred_j] = Arr_of_idx[del_j]; // ������� ��-� �� ������, ������������ ��������� ����������� ��-�� �� ���������
	Arr_of_idx[del_j] = idx_first_empty_value; // �������� ������ ���������� ��-�� ��� ������
	idx_first_empty_value = del_j; // ��������� ������ ������ ������ ������ �� ������ ���������� ��-��
	return true; // ���������� true, �������� �� �������� �������� ��-��
}

//--------------------------------------------------------------------------------------------------------
template <class T> void List<T>::print()
{
	int j;
	int i;
	j = idx_first_value;
	int sizeNow = this->ret_size();
	cout << "\nsize:" << sizeNow << "\n\n";
	//cout << "idx_first_value:" << idx_first_value << "\n";
	//cout << "idx_first_empty_value:" << idx_first_empty_value << "\n";

	for (int i = 0; i < sizeNow; i++)
	{
		cout << i << "\t";
	}
	cout << "\n\n";
	for (i = 0; j != -1; i++)
	{
		cout << Arr_of_values[j] << "\t";
		j = Arr_of_idx[j];
	}
	cout << endl;
	return;
};

template <class T> int List<T>::get_num_of_check_elem()	//���������� ���������� ��������
{
	return NChE;
};