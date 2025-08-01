#include <iostream>
using namespace std;

int NChE; //счетчик

template <class T>
class List
{
protected:
	T* Arr_of_values;			//указатель на массив значений элементов списка
	int* Arr_of_idx;			//указатель на массив индексов элементов списка
	int size;					//Начальный размер списка
	int count;					//Текущий размер списка
	int idx_first_value;		//Индекс первого значения
	int idx_last_value;			//Индекс последнего значения
	int idx_first_empty_value;	//Индкс первого пустого
	//----------------------------------------------------------------------------------------------------------
	int return_index(int ser_number)	//возвращает индекс эл-та по его порядковому номеру
	{
		NChE = 0;
		int j = idx_first_value;
		for (int i = 0; j != -1; i++)//пока не достигнем последнего индекса в массиве
		{
			NChE++;
			if (ser_number == i) return j;//когда достигаем порядкового номера эл-та, возвращаем его индекс
			j = Arr_of_idx[j];//присваиваем индекс следующего по порядку эл-та
		}
		return -1;//если не нашли
	};
	//----------------------------------------------------------------------------------------------------------
public:
	List(int sizeArr);							//Конструктор с параметрами
	List(const List<T>& L);						//конструктор копирования класса List,
	//который принимает ссылку на другой объект класса List в качестве аргумента. 
	//Этот конструктор создает новый объект List, инициализируя его содержимым объекта L
	~List();									//Деструктор
	bool add_val(T value);						//Добавить значение эл-та
	bool add_val_by_num(T value, int por_num);	//Добавить значение эл-та по его порядковому номеру
	bool check_value(T value);					//Проверить наличие эл-та по его значению
	T read_val_by_num(int por_num);				//Прочитать значение эл-та по его порядковому номеру
	int get_pos_by_val(T value);				//Получить порядковый номер эл-та по его значению
	bool change_val_by_num(int por_num, T value);//Изменить значение эл-та по его порядковому номеру
	bool delete_val(T value);					//Удалить эл-т по его значению
	bool delete_val_by_num(int por_num);		//Удалить эл-т по его порядковому номеру
	void clear_list();							//Очистка списка
	void print();								//Печать
	int ret_size();								//Узнать размер списка
	int get_num_of_check_elem();				//Вернуть кол-во итераций
	bool check_list_empty();					//Проверка списка на пустоту

	class Iterator
	{
		List* L_ptr;	//Указатель на объект списка
		int idx_curr_cell;		//Индекс текущей ячейки
		bool fl_end;		//Флаг установки итератора
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
		List* L_ptr;	//Указатель на объект списка
		int idx_curr_cell;		//Индекс текущей ячейки
		bool fl_end;		//Флаг установки итератора
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
template <class T> List<T>::List(int sizeArr) //конструктор
{
	idx_first_value = -1;//список пока пуст
	idx_last_value = -1;//список пока пуст
	size = sizeArr;//Присваиваем переменной size значение, переданное в конструктор
	Arr_of_values = new T[size];//Создаем динамический массив Arr_of_values типа T размером size для хранения значений элементов списка
	Arr_of_idx = new int[size];//Создаем динамический массив Arr_of_idx типа int размером size для хранения индексов элементов списка
	idx_first_empty_value = 0;//первый пустой эл-т списка находится в начале массива
	//size = size0;//текущий размер списка
	for (int i = 0; i < size; i++) { Arr_of_idx[i] = i + 1; }//Инициализируем массив так, 
	//чтобы каждый эл-т содержал индекс следующего эл-та в списке
	Arr_of_idx[size - 1] = -1;//конец списка
	return;
};
//---------------------------------------------------------------------------------------------------------
template <class T> List<T>::~List() //деструктор
{
	delete Arr_of_values;
	delete Arr_of_idx;
	return;
};
//---------------------------------------------------------------------------------------------------------
template <class T> List<T>::List(const List<T>& L)	//конструктор копирования
{
	//Копируем значения из объекта L в текущий объект
	size = L.size;
	idx_first_value = L.idx_first_value;
	idx_last_value = L.idx_last_value;
	idx_first_empty_value = L.idx_first_empty_value;
	//Выделяем память для массивов Arr_of_values и Arr_of_idx такого же размера, как у списка L
	Arr_of_values = new T[size];
	Arr_of_idx = new int[size];
	//Копируем значения элементов массивов Arr_of_values и Arr_of_idx из объекта L в текущий объект
	for (int i = 0; i < size; i++)
	{
		Arr_of_values[i] = L.Arr_of_values[i];
		Arr_of_idx[i] = L.Arr_of_idx[i];
	}
};
//---------------------------------------------------------------------------------------------------------
template <class T> int List<T>::ret_size() //Узнать размер списка
{
	count = 0;
	int j = 0;//для перемещения
	for (count, j = idx_first_value; j != -1; count++) j = Arr_of_idx[j];
	return count;
};
//---------------------------------------------------------------------------------------------------------
template <class T> void List<T>::clear_list()//Очистка списка
{
	idx_first_value = -1; // Устанавливаем индекс первого значения в -1, чтобы указать, что список пуст.
	idx_last_value = -1; //Устанавливаем индекс первого значения в - 1, чтобы указать, что список пуст.
	idx_first_empty_value = 0; // Устанавливаем индекс первого пустого эл-та в 0, так как после очистки все элементы снова станут доступными.
	delete Arr_of_idx; delete Arr_of_values; // Удаляем массивы значений и индексов, чтобы освободить память.
	Arr_of_idx = new int[size]; Arr_of_values = new T[size]; // Выделяем новую память для массивов значений и индексов с исходным размером.
	//size = size0; // Обновляем переменную size, чтобы она отражала исходный размер списка.
	for (int i = 0; i < size; i++) { Arr_of_idx[i] = i + 1; } // Инициализируем массив индексов так, чтобы каждый эл-т указывал на следующий.
	Arr_of_idx[size - 1] = -1; // Устанавливаем последний эл-т массива индексов в -1, чтобы обозначить конец списка.
	return; // Завершаем функцию.
};

//---------------------------------------------------------------------------------------------------------
template <class T> bool List<T>::check_list_empty()//Проверка списка на пустоту
{
	if (idx_first_value == -1) return true;
	else return false;
};
//---------------------------------------------------------------------------------------------------------
template <class T> bool List<T>::check_value(T value) //Проверить наличие эл-та по его значению
{
	int j = idx_first_value; // Инициализируем переменную j индексом первого эл-та в списке.
	NChE = 0;
	for (int i = 0; j != -1; i++) // Начинаем цикл, который будет продолжаться, пока j не станет равным -1 (что означает конец списка).
	{
		NChE++;
		if (Arr_of_values[j] == value) return true; // Если значение текущего эл-та равно заданному значению, возвращаем true, что означает наличие эл-та в списке.
		j = Arr_of_idx[j]; // Переходим к следующему элементу списка, обновляя значение j до индекса следующего эл-та.
		//NChE++; // Увеличиваем значение для подсчета.
	}
	return false; // Если цикл завершился, и эл-т не был найден, возвращаем false, что означает отсутствие эл-та в списке.
};

//---------------------------------------------------------------------------------------------------------
template <class T> T List<T>::read_val_by_num(int por_num)//Прочитать значение эл-та по его порядковому номеру
{
	int j = idx_first_value; // Инициализируем переменную j индексом первого эл-та в списке.
	for (int i = 0; j != -1; i++) // Начинаем цикл, который будет продолжаться, пока j не станет равным -1 (что означает конец списка).
	{
		if (i == por_num) return Arr_of_values[j]; // Если текущий порядковый номер i равен заданному порядковому номеру por_num, возвращаем значение эл-та в этой позиции.
		j = Arr_of_idx[j]; // Переходим к следующему элементу списка, обновляя значение j до индекса следующего эл-та.
	}
	throw(111); // Если не удалось найти эл-т с заданным порядковым номером, генерируется исключение.
};

//---------------------------------------------------------------------------------------------------------
template <class T> bool List<T>::change_val_by_num(int por_num, T value)//Изменить значение эл-та по его порядковому номеру
{
	int j = idx_first_value; // Инициализируем переменную j индексом первого эл-та в списке.
	for (int i = 0; j != -1; i++) // Начинаем цикл, который будет продолжаться, пока j не станет равным -1 (что означает конец списка).
	{
		if (i == por_num) // Если текущий порядковый номер i равен заданному порядковому номеру por_num,
		{
			Arr_of_values[j] = value; // Заменяем значение эл-та по индексу j на заданное значение value.
			return true; // Возвращаем true, указывая на успешное изменение значения.
		}
		j = Arr_of_idx[j]; // Переходим к следующему элементу списка, обновляя значение j до индекса следующего эл-та.
	}
	return false; // Если цикл завершился, и эл-т с заданным порядковым номером не был найден, возвращаем false.
};

//---------------------------------------------------------------------------------------------------------
template <class T> int List<T>::get_pos_by_val(T value) // Получить порядковый номер эл-та по его значению
{
	int j = idx_first_value; // Инициализируем переменную j индексом первого эл-та в списке.

	while (j != -1) // Начинаем цикл, который будет продолжаться, пока j не станет равным -1 (что означает конец списка).
	{
		if (Arr_of_values[j] == value) // Проверяем, равно ли значение текущего эл-та заданному значению.
			return j; // Если значение текущего эл-та равно заданному значению, возвращаем его порядковый номер j.

		j = Arr_of_idx[j]; // Переходим к следующему элементу списка, обновляя значение j до индекса следующего эл-та.
	}

	return -1; // Если значение не было найдено в списке, возвращаем -1, чтобы указать об этом.
}

//---------------------------------------------------------------------------------------------------------
template <class T> bool List<T>::add_val(T value)//Добавить значение эл-та
{
	if (idx_first_empty_value == -1)//если пустых ячеек нет
	{
		return false;
	}
	int j = idx_first_empty_value; // Присваиваем переменной j индекс первой пустой ячейки.
	idx_first_empty_value = Arr_of_idx[j]; // Обновляем индекс первой пустой ячейки на индекс следующей пустой ячейки.
	Arr_of_values[j] = value; // Присваиваем значению в позиции j заданное значение.
	int k = idx_first_value; // Присваиваем переменной k индекс первого значения в списке.
	if (k == -1) { idx_first_value = 0; Arr_of_idx[0] = -1; return true; } // Если список пуст, присваиваем idx_first_value значение 0 и Arr_of_idx[0] значение -1, обозначая начало и конец списка соответственно.
	while (Arr_of_idx[k] != -1) { k = Arr_of_idx[k]; } // Переходим к последнему элементу в списке.
	Arr_of_idx[k] = j; // Устанавливаем индекс предыдущего эл-та в списке на j.
	Arr_of_idx[j] = -1; // Устанавливаем индекс j как конец списка.
	return true;
}

//---------------------------------------------------------------------------------------------------------
template <class T> bool List<T>::delete_val(T value)//Удалить эл-т по его значению
{
	if (idx_first_value == -1) return false; // Проверяем, пуст ли список. Если список пуст, возвращаем false.
	int j = idx_first_value;// Инициализируем j индексом первого эл-та списка.
	int temp;	


	if (Arr_of_values[idx_first_value] == value) // Проверяем, равно ли значение первого эл-та списку заданному значению для удаления.
	{
		int tmp_f = idx_first_empty_value; // Сохраняем индекс первой пустой ячейки во временную переменную.
		idx_first_empty_value = idx_first_value; // Обновляем индекс первой пустой ячейки на индекс первого эл-та списка.
		idx_first_value = Arr_of_idx[idx_first_value]; // Обновляем индекс первого эл-та списка на индекс следующего эл-та.
		Arr_of_idx[idx_first_empty_value] = tmp_f; // Присваиваем индексу первого эл-та списка индекс первой пустой ячейки.
		return true; // Возвращаем true, указывая на успешное удаление эл-та.
	}

	while (j != -1) // Пока не достигнут конец списка,
	{
		if (Arr_of_values[j] == value) // Если значение текущего эл-та равно заданному значению для удаления,
		{
			Arr_of_idx[temp] = Arr_of_idx[j]; // Удаляем текущий эл-т из списка, перенаправив указатель предыдущего эл-та на следующий.
			Arr_of_idx[j] = idx_first_empty_value; // Помечаем индекс текущего эл-та как пустой.
			idx_first_empty_value = j; // Обновляем индекс первой пустой ячейки на индекс текущего эл-та.
			return true; // Возвращаем true, указывая на успешное удаление эл-та.
		}
		temp = j; // Сохраняем индекс текущего эл-та как предыдущий.
		j = Arr_of_idx[j]; // Переходим к следующему элементу списка.
	}
	return false; // Если эл-т не найден, возвращаем false.
}

//---------------------------------------------------------------------------------------------------------
template <class T> bool List<T>::add_val_by_num(T value, int por_num)//Добавить значение эл-та по его порядковому номеру
{
	NChE = 0;
	if (por_num == 0 && idx_first_value == -1) { // Если порядковый номер равен 0 и список пуст
		idx_first_value = 0; // Устанавливаем индекс первого значения в списке как 0
		idx_first_empty_value = 1; // Устанавливаем индекс первой пустой ячейки как 1
		Arr_of_idx[0] = -1; // Устанавливаем индекс первого эл-та в -1, обозначая конец списка
		Arr_of_values[0] = value; // Присваиваем первому элементу в списке заданное значение
		return true; // Возвращаем true, указывая на успешное добавление эл-та
	}
	if (por_num == ret_size()) // Если порядковый номер равен текущему размеру списка
	{
		this->add_val(value); // Добавляем значение в конец списка с помощью метода add_val()
		return true; // Возвращаем true, указывая на успешное добавление эл-та
	}

	int pred_j = return_index(por_num); // Получаем индекс эл-та по заданному порядковому номеру

	if (pred_j == -1) // Если элемент за пределами текущего списка
		return false; // Возвращаем false, указывая на неудачу добавления эл-та

	if (idx_first_empty_value == -1) // Если нет пустых ячеек в списке
	{
		return false;
	}

	int j = idx_first_empty_value; // Сохраняем индекс первой пустой
	idx_first_empty_value = Arr_of_idx[j]; // Обновляем индекс первой пустой ячейки на индекс следующей пустой ячейки

	Arr_of_values[j] = Arr_of_values[pred_j]; // Копируем значение эл-та на позиции por_num в первую пустую ячейку
	Arr_of_values[pred_j] = value; // Обновляем значение эл-та

	int temp = Arr_of_idx[pred_j]; // Сохраняем индекс эл-та, следующего за эл-том на позиции por_num
	Arr_of_idx[pred_j] = j; // Обновляем индекс эл-та, следующего за эл-том на позиции por_num
	Arr_of_idx[j] = temp; // Устанавливаем индекс нового эл-та на сохраненный индекс следующего эл-та

	return true; // Возвращаем true, указывая на успешное добавление эл-та
}

//---------------------------------------------------------------------------------------------------------
template <class T> bool List<T>::delete_val_by_num(int por_num)//Удалить эл-т по его порядковому номеру
{
	int del_j; // Объявляем переменную для хранения индекса эл-та, который нужно удалить
	NChE = 0;
	if (por_num == 0) // Если порядковый номер эл-та равен 0
	{
		del_j = idx_first_value; // Присваиваем индексу удаляемого эл-та индекс первого эл-та списка
		if (idx_first_value == -1) // Если список пуст
			return false; // Возвращаем false
		idx_first_value = Arr_of_idx[idx_first_value]; // Обновляем индекс первого эл-та списка на индекс следующего эл-та
		Arr_of_idx[del_j] = idx_first_empty_value; // Устанавливаем индекс удаляемого эл-та на индекс первой пустой ячейки
		idx_first_empty_value = del_j; // Обновляем индекс первой пустой ячейки на индекс удаляемого эл-та
		return true; // Возвращаем true, указывая на успешное удаление эл-та
	}

	int pred_j = return_index(por_num - 1); // Находим индекс предыдущего эл-та по порядковому номеру

	del_j = Arr_of_idx[pred_j]; // сохраняем индекс удаляемого эл-та
	NChE++;
	if (del_j == -1) // Если индекс удаляемого эл-та равен -1
		return false; // Возвращаем false, указывая на неудачу удаления эл-та

	Arr_of_idx[pred_j] = Arr_of_idx[del_j]; // Удаляем эл-т из списка, перенаправив указатель предыдущего эл-та на следующий
	Arr_of_idx[del_j] = idx_first_empty_value; // Помечаем индекс удаляемого эл-та как пустой
	idx_first_empty_value = del_j; // Обновляем индекс первой пустой ячейки на индекс удаляемого эл-та
	return true; // Возвращаем true, указывая на успешное удаление эл-та
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

template <class T> int List<T>::get_num_of_check_elem()	//возвращает количество итераций
{
	return NChE;
};