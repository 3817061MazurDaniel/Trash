#include "TText.h"
#include <Windows.h>
#include <conio.h>
#include <locale.h>

void clrscr(void);
void clreol(void);
void gotoxy(int x, int y);

TMem TLink::mem;
int LinkCount = 100;

int main() 
{
	TLink::InitMem(LinkCount);

	setlocale(LC_ALL, "Rus");

	char fileName[] = "C:\\Users\\Sane\\Desktop\\Text\\TextFile.txt";
	TText text;
	TLink tmp;

	char s;
	char buf[80];
	bool readFlag = false;

	
	cout << "�������� ����� ��� ���������� �������� \n\nn - ����� ������ \nr - ������ \np - ������ \ns - ���������� \nq - ����� \ne - ������� \nf - ������ ��������� ������� \nd - ������� ������\n" <<
		"a - ������� �� ���������� ������ \nz - ������� �� ��������� ������ \nx - ������� �� ���������� ������ \n1 - �������� ��������� ������ \n2 - �������� ��������� ������ \n" <<
		"3 - �������� ���������� ������ \n4 - �������� ���������� ������ \n5 - ������� ��������� ����� \n6 - ������� ���������� ������ \n";

	while (true)
	{
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		s = _getch();
		cout << s << endl;
		
		switch (s) 
		{

		case 'n': cout << "������� ������:"; 
			cin >> buf; 
			tmp.SetStr(buf); 
			text.SetFirst(&tmp); 
			break;

		case 'r': text.Read(fileName); 
			break;

		case 'p': text.Print(); 
			break;

		case 's': text.Save("C:\\Users\\Sane\\Desktop\\Text\\TextFile.txt"); 
			cout << "�������� ����������\n"; 
			break;

		case 'c': 
		{ 
			TText tmp; 
			tmp.Save("C:\\Users\\Sane\\Desktop\\Text\\TextFile.txt"); 
		} 
				  break;

		case 'e': clrscr(); 
			cout << "�������� ����� ��� ���������� �������� \n\nn - ����� ������ \nr - ������ \np - ������ \ns - ���������� \nq - ����� \ne - ������� \nf - ������ ��������� ������� \nd - ������� ������\n" <<
				"a - ������� �� ���������� ������ \nz - ������� �� ��������� ������ \nx - ������� �� ���������� ������ \n1 - �������� ��������� ������ \n2 - �������� ��������� ������ \n" <<
				"3 - �������� ���������� ������ \n4 - �������� ���������� ������ \n5 - ������� ��������� ����� \n6 - ������� ���������� ������ \n";
			break;

		case 'f': TLink::PrintFree(); 
			break;

		case 'd': 
			if (readFlag) 
		{ 
			TLink::MemClear(text); cout << "������ �������\n"; 
		}
				  else cout << "��� �����\n"; 
				  break;

		case 'q': if (readFlag) 
		{ 
			TLink::MemClear(text); 
		} 
				  return 0;

		case 'a': text.GoPrevLink(); 
			text.Print(); 
			break;
		case 'z': text.GoNextLink(); 
			text.Print(); 
			break;


		case 'x': text.GoDownLink(); text.Print(); 
			break;

		case '1': cout << "������� ������: "; 
			cin >> buf; 
			text.InsNextLine(buf); 
			text.Print();  
			break;

		case '2': cout << "������� ������: "; 
			cin >> buf; 
			text.InsNextSection(buf); 
			text.Print();  
			break;

		case '3': cout << "������� ������: "; 
			cin >> buf; 
			text.InsDownLine(buf); 
			text.Print(); 
			break;

		case '4': cout << "������� ������: "; 
			cin >> buf; 
			text.InsDownSection(buf); 
			text.Print(); 
			break;

		case '5': text.DelNext(); 
			text.Print(); 
			break;

		case '6': text.DelDown(); 
			text.Print(); 
			break;

		default: cout << "������ �����\n";
		}
	}
}




void clrscr(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console) return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	DWORD Count;

	COORD zpos;
	zpos.X = 0;
	zpos.Y = 0;

	FillConsoleOutputCharacter(Console, ' ', buf.dwSize.X * buf.dwSize.Y, zpos, &Count);
	SetConsoleCursorPosition(Console, zpos);
}

void clreol(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	WORD Attr;
	DWORD Count;

	COORD zpos = buf.dwCursorPosition;

	zpos.X = buf.dwCursorPosition.X + 1;
	zpos.Y = buf.dwCursorPosition.Y;

	FillConsoleOutputCharacter(Console, ' ', buf.dwSize.X - buf.dwCursorPosition.X - 1, zpos, &Count);
	SetConsoleCursorPosition(Console, buf.dwCursorPosition);
}

void gotoxy(int x, int y)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)return;

	COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(Console, pos);
}
