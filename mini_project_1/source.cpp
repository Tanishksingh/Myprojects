//student report card handling system //
#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<fstream>
#include<string>

using namespace std;
void Entry_Menu();
void Show_All_Result();


/*class Create_Student_Data take data from user and save data to database*/
class Create_Student_Data
{
private:
	int Roll_no;
	string Student_name;
	double phy, chem, maths, english, computer;
	double per, total;
	char grade;
public:
	void GetData();
	void Calculate()
	{
		total = phy + chem + maths + english + computer;
		cout << "Total marks He/She get is:" << total<<"\n";
		per = (total / 500) * 100;
		cout << "Over All percentage He/She get is:" << per<<"%\n";
		cout << "Grade He/She get:" << getGrade(per);
	}
	string Search_Student_data();
	char getGrade(double per);
	void Modify_data();
	void Delete_data();
	void StoreData()
	{
		fstream fout;
		fout.open("database.txt", ios::app);
		fout << Student_name << "\t" << Roll_no << "\t" << phy << "\t" << chem << "\t" << maths << "\t" << english << "\t" << computer << "\n";
		fout.close();
	}
};

void Create_Student_Data::Delete_data()
{
	ifstream fin;
	ofstream fout;
	fout.open("copy.txt", ios::out);
	fin.open("database.txt", ios::in);
	char data[100];
	string data_name, name, roll, data_roll;
	cin.ignore();
	cout << "\nEnter name of student:";
	getline(cin, name);
	cout << "\nEnter Roll number student:";
	cin >> roll;
	cout << "deleting.......";
	while (!fin.eof())
	{
		data_name = "";
		data_roll = "";
		int flag = 0;
		fin.getline(data, 100);
		for (int i = 0;data[i] != '\0';i++)
		{
			if ((int)data[i] == 9) {
				flag++;
				continue;
			}
			if (flag == 0)
				data_name += data[i];
			if (flag == 1)
				data_roll += data[i];
			if (flag == 2)
				break;
		}
		if (data_name != name)
		{
			if (data_roll != roll)
			{
				fout << data << "\n";
			}
		}
	}
	fin.close();
	fout.close();
	ofstream fileout;
	ifstream filein;
	fileout.open("database.txt", ios::out);
	filein.open("copy.txt", ios::in);
	while (filein.eof() == 0)
	{
		char getdata[100];
		filein.getline(getdata, 100);
		fileout << getdata << endl;
	}
	fileout.close();
	filein.close();
	return;
}

void Create_Student_Data::Modify_data()
{
	Create_Student_Data modify;
	modify.Delete_data();
	modify.GetData();
	modify.StoreData();
}

string Create_Student_Data::Search_Student_data()
{
	ifstream fin;
	fin.open("database.txt", ios::in);
	char data[100];
	string data_name, name, roll, data_roll;
	cout << "\nEnter name of student:";
	cin >> name;
	cout << "\nEnter Roll number student:";
	cin >> roll;
	while (!fin.eof())
	{
		data_name = "";
		data_roll = "";
		int flag = 0;
		fin.getline(data, 100);
		for (int i = 0;data[i]!='\0';i++)
		{
			if ((int)data[i] == 9) {
				flag++;
				continue;
			}
			if (flag == 0)
				data_name += data[i];
			if (flag == 1)
				data_roll += data[i];
			if (flag == 2)
				break;
		}
		if (data_name==name)
		{
			if (data_roll == roll)
			{
				fin.close();
				cout << "  Name\tRoll\tphy\tchem\tmaths\tenglish\tcomputer\n";
				return data;
			}
		}
	}
	fin.close();
	return "Data Not Found";
}

char Create_Student_Data::getGrade(double per)
{
	if (per > 90)
		return 'A';
	else if (per < 90 && per>70)
		return 'B';
	else if (per < 70 && per>60)
		return 'C';
	else if (per < 60 && per >50)
		return 'D';
	else if (per < 50 && per>45)
		return 'E';
	else
		return 'F';
}
void Create_Student_Data::GetData()
{
	cout << "Roll No. of Student:";
	cin >> Roll_no;
	cin.ignore();
	cout << "Name of student:";
	getline(cin, Student_name);
	cout << "Marks in Physices:";
	cin >> phy;
	cout << "Marks in Chemistry:";
	cin >> chem;
	cout << "Marks in Maths:";
	cin >> maths;
	cout << "Marks in English:";
	cin >> english;
	cout << "Marks in Computer Science:";
	cin >> computer;
	cout << "\n";
	cout << "**********SUBMITTED***************\n";
}

int main()
{
	int ch;
	do {
		cout << endl;
		cout << "\t\t\t\t\tMAIN MENU\n\n";
		cout << "\t01. RESULT MENU\n\n";
		cout << "\t02. ENTRY/EDIT STUDENT RERCORD\n\n";
		cout << "\t03. EXIT\n\n";
		cout << "\tPlease Select Your Option (1-3):";
		cin >> ch;
		switch (ch)
		{
		case 1:
			system("cls");
			cout << "\t--------------Report Card-----------------\n";
			Show_All_Result();
			cout << "\t\t\tPress 'C' for continue:";
			char wait;
			cin >> wait;
			break;
		case 2:
			system("cls");
			Entry_Menu();
			break;
		case 3:exit(0);
		default:
			break;
		}
		system("cls");
	} while (ch != 3);
	return 0;
}
void Show_All_Result()
{
	ifstream fin;
	char str[100];
	fin.open("database.txt", ios::in);
	while (fin.eof() == 0)
	{
		fin.getline(str,100);
		cout << str << endl;
		cout << endl;
	}
}
void Entry_Menu()
{
	Create_Student_Data obj;
	do {
		int ch;
		cout << endl << "\t\t\t\t\tENTRY MENU\n\n";
		cout << "\t01.CREATE STUDENT RECORD\n\n";
		cout << "\t02.SEARCH STUDENT RECORD\n\n";
		cout << "\t03.MODIFY STUDENT RECORD\n\n";
		cout << "\t04.DELETE STUDET RECORD\n\n";
		cout << "\t05.BACK TO MAIN MENU\n\n";
		cout << "\tPlease Enter Your Choice(1-5):";
		cin >> ch;
		switch (ch)
		{
		case 1:
			obj.GetData();
			obj.StoreData();
			break;
		case 2:
			cout<<obj.Search_Student_data()<<endl;
			break;
		case 3:
			obj.Modify_data();
			break;
		case 4:obj.Delete_data();
			break;
		case 5:return;
			break;
		default:
			cout << "plss enter a valid choice";
		}
		cout << "\t\t\tPress 'C' for continue:";
		char wait;
		cin >> wait;
		system("cls");
	} while (true);
}
