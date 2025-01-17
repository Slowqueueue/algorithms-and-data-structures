#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Exception.h"

template <class T>		//����� ������
class List
{	
	class Elem		//����� ������� ������										
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
	class Iterator		//����� ���������
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

	void Add(T& data);						//���������� �������� � ����� ������
	void InsertByIndex(int index,T& data);	//���������� �������� � ������ �� �������
	T& GetByIndex(int index);				//��������� �������� �� �������
	void DeleteByIndex(int index);			//�������� �������� �� �������
	void Change(int index, T& value);		//��������� �������� �� �������
	int GetByValue(T& value);				//��������� ������� �� ��������� ��������
	void DeleteByValue(T& value);			//�������� ��������� ��������
	BOOL IsValue(T& value);					//�������� ������� ��������� ��������
	void Clear();							//������� ������
	int GetCount();							//��������� ������� ������
	BOOL IsEmpty();							//�������� ������ �� �������
	int GetTest();							//������ ���������� ��������
	List();	
	List(List<T>& anotherList);
	~List();

};

template <class T> List<T>::Elem::Elem(T& d)	//����������� ������ Elem
{
	data=d;		
}

template <class T> List<T>::List()		//����������� ������ List (��� ���������)
{		
	first=last=NULL;
	count=0;
	test=0;
}

template <class T> List<T>::List(List<T>& anotherList)	//���������� �����������
{
	first=last=NULL;
	count = 0;
	test = 0;
	Elem* temp = anotherList.first;		//������ ������, ������ ��������
	while (temp != anotherList.last)  //��������, ���� �� ������ �� ���������� ��������
	{
		this->Add(temp->data);
		temp = temp->next;
	}
	this->Add(temp->data); //�������� ��������� �������
	temp = temp->next;
}

template <class T> List<T>::~List()		//����������
{
	Clear();
}

template <class T> void List<T>::Add(T& data)	//���������� �������� � ������
{
	if (first==NULL)	//���� ������ ���� (���������� ������� ��������)
	{
		first=last=new Elem (data);		
		first->next=last;
	}
	else	//���������� � ����� ������������� ������
	{	
		Elem  *p=new Elem (data);
		last->next=p;
		last=p;
		last->next=first;
	}
	count++;
}

template <class T> void List<T>::InsertByIndex(int index,T& data)	//���������� �� �������
{	
	test=0;

	if (index>=0 && index<=count)
	{
		Elem  *q=new Elem (data);		

		if (index==0)	//���� ��������� � ������ (����� first)
		{
			if (first==NULL)	//���� ������ ���� (���������� ������� ��������)
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
			if (index==count)	//���� ��������� ����� ����������
			{
				last->next=q;
				q->next=first;
				last=q;

				test++;
			}
			else	//���� ��������� � ��������
			{
				Elem  *p,*tmp;
				int i;
				
				for (i=0,p=first;i<index-1;i++,p=p->next)test++;	//����� �� ������� ��������, ��������������� ������������		
				
				tmp=p->next;
				p->next=q;
				q->next=tmp;
			}
		}
		count++;
	}
	else	//���� �������� �� ��������
		throw new IndexException();
}

template <class T> T& List<T>::GetByIndex(int index)	//���������� �������� �� �������
{
	if (first==NULL)	//���� ������ ����
		throw new EmptyException();

	if (index>=0 && index<=count-1)
	{
		Elem  *p;
		int i;		

		for (i=0,p=first;i<index;i++,p=p->next);	//����� �������� �� �������
		
		return p->data;
	}
	else	//���� �������� � ����� �������� ���
		throw new IndexException();
}

template <class T> void List<T>::DeleteByIndex(int index)	//�������� �� �������
{
	if (first==NULL) 	//���� ������ ����
		throw new EmptyException();
	
	test=0;

	if (index>=0 && index<=count-1)
	{		
		if (index==0)	//���� ������� first
		{
			if (first->next==first)		//���� first - ������������ ������� � ������
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
		else	//���� ������� �� ��������
		{
			Elem  *p, *tmp;
			int i;

			for (i=0,p=first;i<index-1;i++,p=p->next)test++;	//����� �� ������� ��������, ��������������� ����������			
			tmp=p->next;
			p->next=tmp->next;
			if (index==count-1)		//�������� �� ������ �������� ���������� ��������
				last=p;
			delete tmp;
		}
		count--;
	}
	else	//���� �������� � ����� �������� ���
		throw new IndexException();
}

template <class T> void List<T>::Change(int index, T& value)	//��������� �������� �� ������
{
	if (first==NULL)	//���� ������ ����
		throw new EmptyException();

	if (index>=0 && index<=count-1)
	{
		Elem  *p;
		int i;
		
		for (i=0,p=first;i<index;i++,p=p->next);	//����� �������� �� �������
		
		p->data=value;	//��������� �������� �� ��������
	}
	else	//���� �������� � ����� �������� ���														
		throw new IndexException();
}

template <class T>	int List<T>::GetByValue(T& value)	//��������� ������� ��������� ��������
{
	if (first==NULL) 	//���� ������ ����
		throw new EmptyException();

	Elem  *p;
	int i;

	for (i=0,p=first;i<count;i++,p=p->next)		//����� ������� ��������� ��������
	{	
		if (p->data==value)
			return i;
	}
	throw new ValueException();		//���� �������� �������� �� �������
}

template <class T>	void List<T>::DeleteByValue(T& value)	//�������� ��������� ��������
{
	if (first==NULL) 	//���� ������ ����
		throw new EmptyException();

	Elem  *p,*tmp = nullptr;
	int i;

	for (i=0,p=first;i<count && p->data!=value;i++,tmp=p,p=p->next);	//����� ������� ��������� ��������
	if (i==count)	//���� �������� �������� �� �������
		throw new ValueException();

	if (i==0)	//���� ������� first
	{
		if (first->next==first)		//���� first - ������������ ������� � ������
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
	else	//���� ������� �� ��������
	{
		tmp->next=p->next;
		if (i==count-1)		//�������� �� ������ �������� ���������� ��������
			last=tmp;
		delete p;
	}
	count--;
}


template <class T>	BOOL List<T>::IsValue(T& value)		//�������� ������� ��������� ��������
{
	if (first==NULL) 	//���� ������ ����
		throw new EmptyException();

	test=0;	

	Elem  *p;
	int i;
	for (i=0,p=first;i<count;i++,p=p->next)		//����� ��������� ��������
	{	
		test++;
		if (p->data==value)		//�������� �������
			return 1;
	}
	return 0;	//�������� �� �������
}

template <class T> void List<T>::Clear()	//������� ������
{
	if (first==NULL) 	//���� ������ ����
		throw new EmptyException();

	Elem  *p, *tmp;

	for (p=first->next;p!=first;)
	{
		tmp=p;	//��������� �������
		p=p->next;		//������� � ����������
		if (tmp) delete tmp;	//������� �������
	}
	delete first;	//������� first

	count=0;
	first=last=NULL;
}


template <class T> int List<T>::GetCount()	//���������� ���������� ��������� ������
{
	return count;
}

template <class T> BOOL List<T>::IsEmpty()	//�������� ������ �� �������
{
	if (count==0)	//���� ������ ����
		return 1;
	else
		return 0;
}
template <class T> int List<T>::GetTest()	//���������� ���������� ��������
{	
	return test;
}