#include <stdio.h>
#include "stdafx.h"
#include "iostream"
#include "string"

using namespace std;

class Printer
{
protected:
	int id, width, height;
	char *name = new char[50];

public:

	virtual void pprint()
	{
		cout << "ID: " << id << endl << "��������: " << name << endl << "�������: " << width << "x" << height << endl;
	}

	virtual void pread()
	{
		cout << "ID: "; scanf("%d", &id);
		cout << "������ ��������: "; scanf("%d", &width);
		cout << "������ ��������: "; scanf("%d", &height);
		cout << "��������: "; scanf("%s", name);
	}

	Printer()
	{
		this->id = 0;
		this->width = 0;
		this->height = 0;
	}

	Printer(int _id, char* _name, int _width, int _height)
	{
		this->id = _id;
		this->width = _width;
		this->height = _height;
		this->name = _name;
	}

	virtual bool operator== (const Printer & print2)
	{
		return (height == print2.height && width == print2.width);
	}

	virtual bool operator== (const int & _id)
	{
		return (id == _id);
	}
};

class Lazer_Printer :public Printer
{
protected:
	int DPI;

public:
	void pprint()
	{
		Printer::pprint();
		cout << "���������� ������: " << DPI << endl;
	}

	void pread()
	{
		Printer::pread();
		cout << "���������� ������: "; scanf("%d", &DPI);
	}

	Lazer_Printer() :Printer()
	{
		DPI = 300;
	}

	Lazer_Printer(int _id, char* _name, int _width, int _height, int _dpi) :Printer(_id, _name, _width, _height)
	{
		DPI = _dpi;
	}
};

class Fast_Printer :public Lazer_Printer
{
private:
	int Speed;

public:
	void pprint()
	{
		Lazer_Printer::pprint();
		cout << "����. �������� ������, ������/���. : " << Speed << endl;
	}

	void pread()
	{
		Lazer_Printer::pread();
		cout << "����. �������� ������, ������ / ���."; scanf("%d", &Speed);
	}

	Fast_Printer() :Lazer_Printer()
	{
		Speed = 15;
	}

	Fast_Printer(int _id, char* _name, int _width, int _height, int _dpi, int _speed) :Lazer_Printer(_id, _name, _width, _height, _dpi)
	{
		Speed = _speed;
	}
};

class WiFi_Printer :public Fast_Printer
{
private:
	bool WiFi;

public:
	void pprint() {
		Fast_Printer::pprint();
		cout << "���������� ����� WiFi (1 - ����, 0 - ���): " << (int)WiFi << endl;
	}

	void pread() {
		Fast_Printer::pread();
		cout << "���������� ����� WiFi (1 - ����, 0 - ���): "; scanf("%d", &WiFi);
	}

	WiFi_Printer() :Fast_Printer()
	{
		WiFi = 0;
	}

	WiFi_Printer(int _id, char* _name, int _width, int _height, int _dpi, int _speed, bool _wifi) :Fast_Printer(_id, _name, _width, _height, _dpi, _speed)
	{
		WiFi = _wifi;
	}
};

class Stec
{
private: //������, ������� �� ������������
	struct Node
	{
		Printer* data;
		Node* next;
	};
	Node* top;

public:
	//������ ��� �������������� �����
	Stec()
	{
		this->top = NULL;
	}

	Stec(const Stec& paren)
	{
		this->top = paren.top;
	}

	~Stec()
	{
		top = NULL;
	}

	void push(Printer* value)
	{
		Node* tmp = new Node;
		tmp->next = top;
		top = tmp;
		top->data = value;
	}

	void pop()
	{
		top = top->next;
	}

	bool empty() const
	{
		return top == NULL;
	}

	//������������� ���������
	Stec& operator = (const Stec& paren)
	{
		this->~Stec();
		this->top = paren.top;
	}

	friend ostream& operator << (ostream& out, const Stec& stek)
	{
		if (!stek.empty())
		{
			stek.top->data->pprint();
			out << endl << endl;
		}
		else out << "����� �����" << endl << endl;
		return out;
	}

	//������ ��� ��������� �����

	void poisk_count(Printer* printer)
	{
		int i = 0;
		Node* tmp = top;
		while (tmp)
		{
			if (*tmp->data == *printer)
				i++;

			tmp = tmp->next;
		}
		if (i) cout << "������� ���������: " << i << endl;
		else cout << "��������� �� �������" << endl;
	}

	void poisk_count(int _id)
	{
		int i = 0;
		Node* tmp = top;
		while (tmp)
		{
			if (*tmp->data == _id)
				i++;

			tmp = tmp->next;
		}
		if (i) cout << "������� ���������: " << i << endl;
		else cout << "��������� �� �������" << endl;
	}

	void poisk_count(string namen)
	{
		int i = 0;
		Node* tmp = top;
		while (tmp)
		{
			if (typeid(*tmp->data).name() == namen)
				i++;

			tmp = tmp->next;
		}
		if (i) cout << "������� ���������: " << i << endl;
		else cout << "��������� �� �������" << endl;
	}

	void poisk_first(Printer* printer)
	{
		int i = 1;
		Node* tmp = top;
		bool fl = false;
		while (tmp && !fl)
		{
			if (*tmp->data == *printer)
			{
				fl = true;
				break;
			}
			else
			{
				i++;
				tmp = tmp->next;
			}
		}
		if (fl) cout << "��������� ������� �� " << i << " �������" << endl;
		else cout << "������� �������� ���" << endl;
	}

	void poisk_first(int _id)
	{
		int i = 1;
		Node* tmp = top;
		bool fl = false;
		while (tmp)
		{
			if (*tmp->data == _id)
			{
				fl = true;
				break;
			}
			else
			{
				i++;
				tmp = tmp->next;
			}
		}
		if (fl) cout << "��������� ������� �� " << i << " �������" << endl;
		else cout << "������� �������� ���" << endl;
	}

	void poisk_first(string namen)
	{
		int i = 1;
		Node* tmp = top;
		bool fl = false;
		while (tmp)
		{
			if (typeid(*tmp->data).name() == namen)
			{
				fl = true;
				break;
			}
			else
			{
				i++;
				tmp = tmp->next;
			}
		}
		if (fl) cout << "��������� ������� �� " << i << " �������" << endl;
		else cout << "������� �������� ���" << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "");
	Stec printers;
	Lazer_Printer HP(1, "LaserJet Enterprise M608n", 466, 431, 1200);
	printers.push(&HP);
	int doin = 1;

	while (doin > 0 && doin <= 6)
	{
		cout << "�������� ��������:" << endl
			<< "0 - �����" << endl
			<< "1 - �������� ������� � ����" << endl
			<< "2 - ������ ������� �� �����" << endl
			<< "3 - ����� ��������" << endl
			<< "4 - ������� ������ ���������" << endl
			<< "5 - �������� ���������� � ��������� ����������� ��������" << endl
			<< "6 - �������� ����" << endl;
		scanf("%d", &doin);

		switch (doin)
		{
		case 1:
		{
			cout << "�������� ��� ����������: " << endl
				<< "1 - ������� �������" << endl
				<< "2 - �������� �������" << endl
				<< "3 - ������� �������" << endl
				<< "4 - ����� �������" << endl
				<< "0 - ������" << endl << endl;
			int chs;
			scanf("%d", &chs);
			while (!(chs >= 0 && chs <= 5))
			{
				cout << "������� ���������� �����" << endl;
				scanf("%d", &chs);
			}
			if (chs == 1)
			{
				Printer print;
				print.pread();
				printers.push(&print);
			}
			else if (chs == 2)
			{
				Lazer_Printer print;
				print.pread();
				printers.push(&print);
			}
			else if (chs == 3)
			{
				Fast_Printer print;
				print.pread();
				printers.push(&print);
			}
			else if (chs == 4)
			{
				WiFi_Printer print;
				print.pread();
				printers.push(&print);
			}
			break;
		}

		case 2:
			if (printers.empty()) { cout << "���� ����" << endl; system("pause"); }
			else
			{
				printers.pop();
			}
			cout << endl;
			break;

		case 3: {
			if (printers.empty()) cout << "���� ����" << endl;
			else
			{
				cout << "�������� ��������: " << endl
					<< "1 - �� id" << endl
					<< "2 - �� ����" << endl
					<< "3 - �� �������" << endl
					<< "0 - ������" << endl << endl;
				int chs;
				scanf("%d", &chs);
				while (!(chs >= 0 && chs <= 3))
				{
					cout << "������� ���������� �����" << endl;
					scanf("%d", &chs);
				}
				if (chs == 1)
				{
					cout << "������� id: ";
					int id;
					scanf("%d", &id);
					printers.poisk_first(id);
				}
				else if (chs == 2)
				{
					cout << "�������� ���: " << endl
						<< "1 - ������� �������" << endl
						<< "2 - �������� �������" << endl
						<< "3 - ������� �������" << endl
						<< "4 - ����� �������" << endl
						<< "0 - ������" << endl << endl;
					int chs;
					scanf("%d", &chs);
					while (!(chs >= 0 && chs <= 5))
					{
						cout << "������� ���������� �����" << endl;
						scanf("%d", &chs);
					}
					if (chs == 1)
					{
						printers.poisk_first("class Printer");
					}
					else if (chs == 2)
					{
						printers.poisk_first("class Lazer_Printer");
					}
					else if (chs == 3)
					{
						printers.poisk_first("class Fast_Printer");
					}
					else if (chs == 4)
					{
						printers.poisk_first("class WiFi_Printer");
					}
				}
				else if (chs == 3)
				{
					Printer print;
					print.pread();
					printers.poisk_first(&print);
				}
			}
			system("pause");
			cout << endl;
			break;
		}

		case 4: {
			if (printers.empty()) cout << "���� ����" << endl;
			else
			{
				cout << "�������� ��������: " << endl
					<< "1 - �� id" << endl
					<< "2 - �� ����" << endl
					<< "3 - �� �������" << endl
					<< "0 - ������" << endl << endl;
				int chs;
				scanf("%d", &chs);
				while (!(chs >= 0 && chs <= 3))
				{
					cout << "������� ���������� �����" << endl;
					scanf("%d", &chs);
				}
				if (chs == 0);
				else if (chs == 1)
				{
					cout << "������� id: ";
					int id;
					scanf("%d", &id);
					printers.poisk_count(id);
				}
				else if (chs == 2)
				{
					cout << "�������� ���: " << endl
						<< "1 - ������� �������" << endl
						<< "2 - �������� �������" << endl
						<< "3 - ������� �������" << endl
						<< "4 - ����� �������" << endl
						<< "0 - ������" << endl << endl;
					int chs;
					scanf("%d", &chs);
					while (!(chs >= 0 && chs <= 5))
					{
						cout << "������� ���������� �����" << endl;
						scanf("%d", &chs);
					}
					if (chs == 1)
					{
						printers.poisk_count("class Printer");
					}
					else if (chs == 2)
					{
						printers.poisk_count("class Lazer_Printer");
					}
					else if (chs == 3)
					{
						printers.poisk_count("class Fast_Printer");
					}
					else if (chs == 4)
					{
						printers.poisk_count("class WiFi_Printer");
					}
				}
				else if (chs == 3)
				{
					Printer print;
					print.pread();
					printers.poisk_count(&print);
				}
			}
			system("pause");
			cout << endl;
			break;
		}

		case 5:
			cout << printers;
			system("pause");
			cout << endl;
			break;

		case 6:
			printers.~Stec();
			break;
		}
	}
	return 0;
}