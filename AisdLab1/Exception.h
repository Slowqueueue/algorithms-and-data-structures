#pragma once

#include <iostream>
using namespace std;

class Exception
{
public:
	virtual void PrintError()=0;
	Exception(){}
	~Exception(){}
};

class IndexException: public Exception
{
public:

	IndexException(){}
	void PrintError()
	{
		cout<<endl<<"����������"<<endl;  //���������� �� �������(� ������ 2,3,4,5)
	}
};

class ValueException: public Exception
{
public:

	ValueException(){}
	void PrintError()
	{
		cout<<endl<<"����������"<<endl; //���������� �� ��������(� ������ 6 � 7)
	}
};

class EmptyException: public Exception
{
public:

	EmptyException(){}
	void PrintError()
	{
		cout<<endl<<"����������"<<endl; //���������� �� ������ ������� ������
	}
};

class IterException: public Exception
{
public:

	IterException(){}
	void PrintError()
	{
		cout<<endl<<"����������"<<endl; //���������� �� ������ ���������������� ���������(� ������ t,y)
	}
};
