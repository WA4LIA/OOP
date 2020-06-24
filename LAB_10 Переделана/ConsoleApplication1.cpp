//���������� ������������ ������

#include <stdio.h>
#include "stdafx.h"
#include "iostream"
#include "string"

using namespace std;

class Printer
{
protected:
	int id, length, width;
	char *name = new char[50];

public:

	virtual void pprint()
	{
		if (id < 0)  throw 1;
		else cout << "ID: " << endl;
		if (name == "") throw 2;
		else cout << "��������: " << name << endl;
		if (length || width == 0) throw 3;
		else cout << "�������: " << length << "x" << width << endl;
	}

	virtual void pread()
	{
		cout << "ID: "; scanf("%d", &id);
		cout << "����� ��������: "; scanf("%d", &length);
		cout << "������ ��������: "; scanf("%d", &width);
		cout << "��������: "; scanf("%s", name);
	}

	Printer()
	{
		this->id = 0;
		this->length = 0;
		this->width = 0;
	}

	Printer(int _id, char* _name, int _length, int _width)
	{
		this->id = _id;
		this->length = _length;
		this->width = _width;
		this->name = _name;
	}

	virtual bool operator== (const Printer & print2)
	{
		return (width == print2.width && length == print2.length);
	}

	virtual bool operator== (const int & _id)
	{
		return (id == _id);
	}
};

class Lazer_Printer :virtual public Printer
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

	Lazer_Printer(int _id, char* _name, int _length, int _width, int _dpi) :Printer(_id, _name, _length, _width)
	{
		DPI = _dpi;
	}
};

class Scanner_Printer : virtual public Printer
{
protected:
	int SCAN_DPI;
public:
	void pprint()
	{
		Printer::pprint();
		cout << "���������� �������: " << SCAN_DPI << endl;
	}

	void pread() {
		Printer::pread();
		cout << "���������� �������: "; scanf("%d", &SCAN_DPI);
	}

	Scanner_Printer() :Printer()
	{
		SCAN_DPI = 300;
	}

	Scanner_Printer(int _id, char* _name, int _length, int _width, bool _scan) :Printer(_id, _name, _length, _width)
	{
		SCAN_DPI = _scan;
	}
};

class Fast_Printer :public Lazer_Printer
{
protected:
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

	Fast_Printer(int _id, char* _name, int _length, int _width, int _dpi, int _speed) :Printer(_id, _name, _length, _width), Lazer_Printer(_id, _name, _length, _width, _dpi)
	{
		Speed = _speed;
	}
};

class WiFi_Printer :public Fast_Printer
{
protected:
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

	WiFi_Printer(int _id, char* _name, int _length, int _width, int _dpi, int _speed, bool _wifi) :Printer(_id, _name, _length, _width), Fast_Printer(_id, _name, _length, _width, _dpi, _speed)
	{
		WiFi = _wifi;
	}
};

class MFU_Printer :public WiFi_Printer, public Scanner_Printer
{
protected:
	int Class;

public:
	virtual void pprint() {
		WiFi_Printer::pprint();
		cout << "���������� �������: " << SCAN_DPI << endl;
		cout << "����� ����������: " << Class << endl;
	}

	virtual void pread() {
		WiFi_Printer::pread();
		cout << "���������� �������: "; scanf("%d", &SCAN_DPI);
		cout << "����� ����������: "; scanf("%d", &Class);
	}

	MFU_Printer() :WiFi_Printer(), Scanner_Printer()
	{
		Class = 0;
	}

	MFU_Printer(int _id, char* _name, int _length, int _width, int _dpi, int _speed, bool _wifi, bool _scan, int _class) :Printer(_id, _name, _length, _width), WiFi_Printer(_id, _name, _length, _width, _dpi, _speed, _wifi), Scanner_Printer(_id, _name, _length, _width, _scan)
	{
		Class = _class;
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
		if (empty())
		{
			cout << "���� ����" << endl << endl;
		}
		else
		{
			top = top->next;
		}
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
		else out << "���� ����" << endl << endl;
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
	MFU_Printer Toshiba(5, "e - STUDIO2809A", 540, 575, 300, 20, 1, 1, 5);
	printers.push(&Toshiba);
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
				<< "5 - MFU-�������" << endl
				<< "6 - ������-�������" << endl
				<< "0 - ������" << endl << endl;
			int chs;
			scanf("%d", &chs);
			while (!(chs >= 0 && chs <= 6))
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
			else if (chs == 5)
			{
				MFU_Printer print;
				print.pread();
				printers.push(&print);
			}
			else if (chs == 5)
			{
				Scanner_Printer print;
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
						<< "5 - MFU-�������" << endl
						<< "6 - ������-�������" << endl
						<< "0 - ������" << endl << endl;
					int chs;
					scanf("%d", &chs);
					while (!(chs >= 0 && chs <= 6))
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
					else if (chs == 5)
					{
						printers.poisk_first("class MFU_Printer");
					}
					else if (chs == 6)
					{
						printers.poisk_first("class Scanner_Printer");
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
						<< "5 - MFU-�������" << endl
						<< "6 - ������-�������" << endl
						<< "0 - ������" << endl << endl;
					int chs;
					scanf("%d", &chs);
					while (!(chs >= 0 && chs <= 6))
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
					else if (chs == 5)
					{
						printers.poisk_count("class MFU_Printer");
					}
					else if (chs == 6)
					{
						printers.poisk_count("class Scanner_Printer");
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

		case 5: {
			try
			{
				cout << printers;
				system("pause");
				cout << endl;
				break;
			}
			catch (int a)
			{
				switch (a)
				{
				case 1:
				{
					cout << "����������� ������ ID. ������� ��������� ������ � ��������� ���������!" << endl;
					break;
				}
				case 2:
				{
					cout << "��������� ��� ��������. ������� ��������� ������ � ��������� ���������!" << endl;
					break;
				}
				case 3:
				{
					cout << "����������� ������ ������� ��������. ������� ��������� ������ � ��������� ���������!" << endl;
					break;
				}
				}
			}

		}

		case 6:
			printers.~Stec();
			break;
		}
	}
	return 0;
}