#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Exception.h"

template <class T>		//класс список
class List
{	
	class Elem		//класс элемент списка										
	{	
		Elem *next;
		T data;

	public:
		Elem(T& data);
		friend class List<T>::Iterator;
		friend class List<T>;
	};
	Elem *first;
	Elem *last;
	int count;
	int test;		

public:	
	class Iterator		//класс итератора
	{
		Elem *itcur;
		List<T> *list;
		bool m_End;
	
	public:
		Iterator(List<T> &l):list(&l)
		{			
			begin();
		}
		void begin()
		{
			itcur=list->first;
			m_End=itcur==NULL;
		}
		int end()
		{
			return m_End;
		}
		void next()
		{
			if (m_End) throw new IterException();
			itcur=itcur->next;
			if (itcur==list->first) m_End=1;
		}		
		T& operator *()
		{
			if (m_End) throw new IterException();
			return itcur->data;
		}
	};

	void Add(T& data);						//добавление значения в конец списка
	void InsertByIndex(int index,T& data);	//добавление значения в список по индексу
	T& GetByIndex(int index);				//получение значения по индексу
	void DeleteByIndex(int index);			//удаление значения по индексу
	void Change(int index, T& value);		//изменение значения по индексу
	int GetByValue(T& value);				//получение индекса по заданному значению
	void DeleteByValue(T& value);			//удаление заданного значения
	BOOL IsValue(T& value);					//проверка наличия заданного значения
	void Clear();							//очистка списка
	int GetCount();							//получение размера списка
	BOOL IsEmpty();							//проверка списка на пустоту
	int GetTest();							//запрос количества итераций
	List();	
	List(List<T>& anotherList);
	~List();

};

template <class T> List<T>::Elem::Elem(T& d)	//конструктор класса Elem
{
	data=d;		
}

template <class T> List<T>::List()		//конструктор класса List (без параметра)
{		
	first=last=NULL;
	count=0;
	test=0;
}

template <class T> List<T>::List(List<T>& anotherList)	//копирующий конструктор
{
	first=last=NULL;
	count = 0;
	test = 0;
	Elem* temp = anotherList.first;		//начало списка, откуда копируем
	while (temp != anotherList.last)  //копируем, пока не дойдем до последнего элемента
	{
		this->Add(temp->data);
		temp = temp->next;
	}
	this->Add(temp->data); //копируем последний элемент
	temp = temp->next;
}

template <class T> List<T>::~List()		//деструктор
{
	Clear();
}

template <class T> void List<T>::Add(T& data)	//добавление элемента в список
{
	if (first==NULL)	//если список пуст (добавление первого элемента)
	{
		first=last=new Elem (data);		
		first->next=last;
	}
	else	//добавление в конец существующего списка
	{	
		Elem  *p=new Elem (data);
		last->next=p;
		last=p;
		last->next=first;
	}
	count++;
}

template <class T> void List<T>::InsertByIndex(int index,T& data)	//добавление по индексу
{	
	test=0;

	if (index>=0 && index<=count)
	{
		Elem  *q=new Elem (data);		

		if (index==0)	//если вставляем в голову (перед first)
		{
			if (first==NULL)	//если список пуст (добавление первого элемента)
			{
				first=last=q;	
				first->next=last;
			}
			else
			{
				last->next=q;
				q->next=first;
				first=q;
			}
			test++;
		}
		else
		{
			if (index==count)	//если вставляем после последнего
			{
				last->next=q;
				q->next=first;
				last=q;

				test++;
			}
			else	//если вставляем в середину
			{
				Elem  *p,*tmp;
				int i;
				
				for (i=0,p=first;i<index-1;i++,p=p->next)test++;	//поиск по индексу элемента, предшествующего добавляемому		
				
				tmp=p->next;
				p->next=q;
				q->next=tmp;
			}
		}
		count++;
	}
	else	//если индексом не подходит
		throw new IndexException();
}

template <class T> T& List<T>::GetByIndex(int index)	//извлечение значения по индексу
{
	if (first==NULL)	//если список пуст
		throw new EmptyException();

	if (index>=0 && index<=count-1)
	{
		Elem  *p;
		int i;		

		for (i=0,p=first;i<index;i++,p=p->next);	//поиск элемента по индексу
		
		return p->data;
	}
	else	//если элемента с таким индексом нет
		throw new IndexException();
}

template <class T> void List<T>::DeleteByIndex(int index)	//удаление по индексу
{
	if (first==NULL) 	//если список пуст
		throw new EmptyException();
	
	test=0;

	if (index>=0 && index<=count-1)
	{		
		if (index==0)	//если удаляем first
		{
			if (first->next==first)		//если first - единственный элемент в списке
			{
				delete first;
				first=last=NULL;
			}
			else
			{
				Elem *tmp=first;
				last->next=first->next;
				first=first->next;
				delete tmp;						
			}
			test++;
		}
		else	//если удаляем из середины
		{
			Elem  *p, *tmp;
			int i;

			for (i=0,p=first;i<index-1;i++,p=p->next)test++;	//поиск по индексу элемента, предшествующего удаляемому			
			tmp=p->next;
			p->next=tmp->next;
			if (index==count-1)		//поправка на случай удаления последнего элемента
				last=p;
			delete tmp;
		}
		count--;
	}
	else	//если элемента с таким индексом нет
		throw new IndexException();
}

template <class T> void List<T>::Change(int index, T& value)	//изменение значения по индекс
{
	if (first==NULL)	//если список пуст
		throw new EmptyException();

	if (index>=0 && index<=count-1)
	{
		Elem  *p;
		int i;
		
		for (i=0,p=first;i<index;i++,p=p->next);	//поиск элемента по индексу
		
		p->data=value;	//изменение значения на заданное
	}
	else	//если элемента с таким индексом нет														
		throw new IndexException();
}

template <class T>	int List<T>::GetByValue(T& value)	//получение индекса заданного значения
{
	if (first==NULL) 	//если список пуст
		throw new EmptyException();

	Elem  *p;
	int i;

	for (i=0,p=first;i<count;i++,p=p->next)		//поиск индекса заданного значения
	{	
		if (p->data==value)
			return i;
	}
	throw new ValueException();		//если заданное значение не найдено
}

template <class T>	void List<T>::DeleteByValue(T& value)	//удаление заданного значения
{
	if (first==NULL) 	//если список пуст
		throw new EmptyException();

	Elem  *p,*tmp = nullptr;
	int i;

	for (i=0,p=first;i<count && p->data!=value;i++,tmp=p,p=p->next);	//поиск индекса заданного значения
	if (i==count)	//если заданное значение не найдено
		throw new ValueException();

	if (i==0)	//если удаляем first
	{
		if (first->next==first)		//если first - единственный элемент в списке
		{
			delete first;
			first=last=NULL;
		}
		else
		{
			last->next=first->next;
			first=first->next;		
			delete p;
		}
	}
	else	//если удаляем из середины
	{
		tmp->next=p->next;
		if (i==count-1)		//поправка на случай удаления последнего элемента
			last=tmp;
		delete p;
	}
	count--;
}


template <class T>	BOOL List<T>::IsValue(T& value)		//проверка наличия заданного значения
{
	if (first==NULL) 	//если список пуст
		throw new EmptyException();

	test=0;	

	Elem  *p;
	int i;
	for (i=0,p=first;i<count;i++,p=p->next)		//поиск заданного значения
	{	
		test++;
		if (p->data==value)		//значение найдено
			return 1;
	}
	return 0;	//значение не найдено
}

template <class T> void List<T>::Clear()	//очистка списка
{
	if (first==NULL) 	//если список пуст
		throw new EmptyException();

	Elem  *p, *tmp;

	for (p=first->next;p!=first;)
	{
		tmp=p;	//запомнить текущее
		p=p->next;		//перейти к следующему
		if (tmp) delete tmp;	//удалить текущее
	}
	delete first;	//удалить first

	count=0;
	first=last=NULL;
}


template <class T> int List<T>::GetCount()	//возвращает количество элементов списка
{
	return count;
}

template <class T> BOOL List<T>::IsEmpty()	//проверка списка на пустоту
{
	if (count==0)	//если список пуст
		return 1;
	else
		return 0;
}
template <class T> int List<T>::GetTest()	//возвращает количество итераций
{	
	return test;
}