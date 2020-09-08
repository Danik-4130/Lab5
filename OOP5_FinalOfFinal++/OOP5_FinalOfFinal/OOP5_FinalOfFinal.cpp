// OOP5_FinalOfFinal.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <typeinfo>
#include <ostream>
#include <istream>
#include <locale.h>
#include <forward_list>
#include <iterator>
#include<string.h>

using namespace std;

class List {
private:
	struct Element {
		string name;
		string surname;
		int otdel;
		int zarplata;
		int rate_sotrydnika;

		~Element() {
			name = "";
			surname = "";
			otdel = NULL;
			zarplata = NULL;
			rate_sotrydnika = NULL;
		}

		struct Element* next;
	};

	int Count;
	Element* Head;
	string _name, _surname;
	int _otdel, _zarplata, _rate_sotrydnika;

public:
	class Iterator {
	private:
		Element* currNode;
	public:
		Iterator(Element * node) {
			currNode = node;
		}

		bool operator==(const Iterator& other) const {
			if (this == &other) {
				return true;
			}
			return currNode == other.currNode;
		}

		bool operator!=(const Iterator& other) const {
			return !operator==(other);
		}

		Element* operator*() const {
			return currNode;
		}

		void operator++() {
			if (currNode) {
				currNode = currNode->next;
			}
			else cout << "Оп, а тут уже конец!" << endl;
		}

		Element* nextNode() {
			return currNode->next;
		}

		void addElement(Element* node)
		{
			Element* temp = currNode;
			currNode = node;
			currNode->next = temp;
		}

		void changeElement(string name, string surname, int otdel, int zarplata, double rate_sotrydnika)
		{
			currNode->name = name;
			currNode->surname = surname;
			currNode->otdel = otdel;
			currNode->zarplata = zarplata;
			currNode->rate_sotrydnika = rate_sotrydnika;
		}

		void CurrShow() {
			cout << setw(10) << currNode->name << setw(10)
				<< currNode->surname << setw(10)
				<< currNode->zarplata << setw(10)
				<< currNode->otdel << setw(10)
				<< currNode->rate_sotrydnika << endl;
		}
	};

	Iterator begin() const {
		return Iterator(Head);
	}
	Iterator end() const {
		return Iterator(NULL);
	}

	List() {
		Head = nullptr;
		Count = 0;
	}

	~List() {
		while (Head) {
			Remove();
		}
	}

	void Enter() {
		cout << "Имя: ";
		cin >> _name;
		cout << "Фамилия : ";
		cin >> _surname;
		while(true){
			cout << "Отдел : ";
			cin >> _otdel;
			if (!cin)
			{
				cout << "ne verno vveli, povtorite vvod\n";
				cin.clear();
				while (cin.get() != '\n');
			}
			else break;
		}
		while(true){
			cout << "Зарплата : ";
			cin >> _zarplata;
			if (!cin)
			{
				cout << "ne verno vveli, povtorite vvod\n";
				cin.clear();
				while (cin.get() != '\n');
			}
			else break;
		}
		while(true){
			cout << "Рейтинг сотрудника : ";
			cin >> _rate_sotrydnika; 
			if (!cin)
			{
				cout << "ne verno vveli, povtorite vvod\n";
				cin.clear();
				while (cin.get() != '\n');
			}
			else break;
		}
	}

	int GetCount() {
		return Count;
	};

	void Add(string name, string surname, int otdel, int zarplata, double rate_sotrydnika)
	{
		Iterator it = begin();
		Element* newSotrudnik = new Element;
		newSotrudnik->name = name;
		newSotrudnik->surname = surname;
		newSotrudnik->zarplata = zarplata;
		newSotrudnik->otdel = otdel;
		newSotrudnik->rate_sotrydnika = rate_sotrydnika;

		it.addElement(newSotrudnik);
		Head = *it;
		Count++;
	}

	void Add()
	{
		Enter();
		Iterator it = begin();
		Element* newSotrudnik = new Element;
		newSotrudnik->name = _name;
		newSotrudnik->surname = _surname;
		newSotrudnik->zarplata = _zarplata;
		newSotrudnik->otdel = _otdel;
		newSotrudnik->rate_sotrydnika = _rate_sotrydnika;

		it.addElement(newSotrudnik);
		Head = *it;
		Count++;
	}

	void Change()
	{
		try {
			int id;
			cout << "Ид замены: ";
			cin >> id;

			if (id == 0 || id > Size())
				throw string("Оп, произошла ошибочка, мы не можем изменить! ");

			Iterator it = begin();
			for (int i = 1; i < id; i++)
				++it;

			Enter();
			it.changeElement(_name, _surname, _otdel, _zarplata, _rate_sotrydnika);
		}
		catch (string str) {
			cout << str << endl;
		}
	}

	void Remove() {
		try {
			Iterator it = begin();
			if (it == end())
				throw string("Пусто!");
			Head = it.nextNode();
			delete *it;
			cout << "Поздравляю, удалили " << endl;
		}
		catch (string str) {
			cout << str << endl;
		}
	}

	void Clear()
	{
		while (Head) {
			Remove();
		}
	}

	void HeadElem() {
		try {
			Iterator it = begin();
			if (it == end())
				throw string("Пусто!");
			cout << "Заголовочный : \n   ";
			it.CurrShow();
		}
		catch (string str) {
			cout << str << endl;
		}
	}

	void Print() {
		int i = 1;
		for (Iterator it = begin(); it != end(); ++it) {
			cout << i << ". ";
			it.CurrShow();
			i++;
		}
	};

	int Size() const {
		int s = 0;
		for (Iterator it = begin(); it != end(); ++it) {
			s++;
		}
		return s;
	}

	void Sort(int props)
	{
		Iterator left = begin();
		Iterator right = left.nextNode();

		while (left.nextNode())
		{
			while (*right)
			{
				switch (props)
				{
				case 0:
					if ((*left)->name > (*right)->name)
					{
						swap(left, right);
					}
					break;
				case 1:
					if ((*left)->surname > (*right)->surname)
					{
						swap(left, right);
					}
					break;
				case 2:
					if ((*left)->otdel > (*right)->otdel)
					{
						swap(left, right);
					}
					break;
				case 3:
					if ((*left)->zarplata > (*right)->zarplata)
					{
						swap(left, right);
					}
					break;
				case 4:
					if ((*left)->rate_sotrydnika < (*right)->rate_sotrydnika)
					{
						swap(left, right);
					}
					break;
				}
				right = right.nextNode();
			}
			left = left.nextNode();
			right = left.nextNode();
		}
	}

	void swap(Iterator q, Iterator p)
	{
		string temp = (*q)->name.substr(0, (*q)->name.size());
		(*q)->name = (*p)->name.substr(0, (*p)->name.size());
		(*p)->name = temp;

		string temp2 = (*q)->surname.substr(0, (*q)->surname.size());
		(*q)->surname = (*p)->surname.substr(0, (*p)->surname.size());
		(*p)->surname = temp2;

		int tempi = (*q)->otdel;
		(*q)->otdel = (*p)->otdel;
		(*p)->otdel = tempi;

		int tempi2 = (*q)->zarplata;
		(*q)->zarplata = (*p)->zarplata;
		(*p)->zarplata = tempi2;

		int tempi3 = (*q)->rate_sotrydnika;
		(*q)->rate_sotrydnika = (*p)->rate_sotrydnika;
		(*p)->rate_sotrydnika = tempi3;
	}

	void FindElement(string str)
	{
		try {
			Iterator it = begin();
			if (it == end())
				throw string("Пусто!");

			bool result = false;
			for (it = begin(); result == true, it != end(); ++it) {
				size_t pos = ((*it)->name).find(str);
				if (pos != string::npos)
				{
					cout << "Нашли :" << endl;
					it.CurrShow();
					cout << endl;
					result = true;
				}
			}
			if (result == false)
				cout << "Не нашли(" << endl;
		}
		catch (string str) {
			cout << str << endl;
		}
	}

	void DeleteDuplicates()
	{
		try {
			Iterator it = begin();
			if (it == end())
				throw string("Пусто!");
			Sort(0);
			for (it = begin(); it.nextNode() != NULL && it != end(); ++it) {
				Iterator itN = it.nextNode();
				if ((*it)->name == (*itN)->name && (*it)->surname == (*itN)->surname &&
					(*it)->zarplata == (*itN)->zarplata && (*it)->otdel == (*itN)->otdel)
				{
					(*it)->next = (*itN)->next;
					delete (*itN);
				}
			}
		}
		catch (string str) {
			cout << str << endl;
		}
	}
};


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	List example;
	example.Add("Егор", "Топор", 2, 1200, 7.5);
	example.Add("Иван", "Банан", 6, 800, 8.7);
	example.Add("Питер", "Паркер", 10, 2000, 9.8);
	cout << "Размер списка: " << example.Size() << endl;
	example.HeadElem();
	example.Print();

	int choice;

	cout << "Меню: \n1 - Добавить;\n2 - Показать;\n3 - Показать шапочный элемент; \n4 - Изменить; \n5 - Удалить;" <<
		"\n6 - Сорт по имени; \n7 - Сорт по фамилии; \n8 - Сорт по отделу; \n9 - Сорт по ЗП; \n10 - Сорт по рейту сотрудника \n" <<
		"11 - Поиск по имени; \n12 - Удалить повторяющиеся; \n13 - Выход" << endl;
	cout << "\nВыбор: ";
	cin >> choice;

	while (choice >= 1 & choice <= 12) {
		switch (choice)
		{
		case 1: {
			example.Add();
			break;
		}
		case 2: {
			example.Print();
			break;
		}
		case 3: {
			example.HeadElem();
			break;
		}
		case 4: {
			example.Change();
			break;
		}
		case 5: {
			example.Change();
			break;
		}
		case 6: {
			example.Sort(0);
			cout << "По Имени: " << endl;
			cout << endl;
			example.Print();
			break;
		}
		case 7: {
			example.Sort(1);
			cout << "По Фамилии" << endl;
			cout << endl;
			example.Print();
			break;
		}case 8: {
			example.Sort(2);
			cout << "По Отделу" << endl;
			cout << endl;
			example.Print();
			break;
		}
		case 9: {
			example.Sort(3);
			cout << "По ЗП" << endl;
			cout << endl;
			example.Print();
			break;
		}
		case 10: {
			example.Sort(4);
			cout << "По Рейтингу сотрудников" << endl;
			cout << endl;
			example.Print();
			break;
		}
		case 11: {
			cout << "Введите имя: ";
			string findStr;
			cin >> findStr;
			example.FindElement(findStr);
			break; }
		case 12: {
			example.DeleteDuplicates();
			cout << "Повторяющиеся удалены." << endl;
			break; }
		}
		cout << "Выбор: ";
		cin >> choice;
	}
	system("pause");
}
