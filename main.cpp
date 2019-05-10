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

	
	cout << "Выберите пункт для следующего действия \n\nn - новая строка \nr - чтение \np - печать \ns - сохранение \nq - выход \ne - очистка \nf - печать свободных звеньев \nd - сборщик мусора\n" <<
		"a - перейти по предыдущей ссылке \nz - перейти по следующей ссылке \nx - перейти по нисходящей ссылке \n1 - вставить следующую строку \n2 - вставить следующий раздел \n" <<
		"3 - вставить нисходящую строку \n4 - вставить нисходящий раздел \n5 - удалить следующее звено \n6 - удалить нисходящую ссылку \n";

	while (true)
	{
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		s = _getch();
		cout << s << endl;
		
		switch (s) 
		{

		case 'n': cout << "Введите строку:"; 
			cin >> buf; 
			tmp.SetStr(buf); 
			text.SetFirst(&tmp); 
			break;

		case 'r': text.Read(fileName); 
			break;

		case 'p': text.Print(); 
			break;

		case 's': text.Save("C:\\Users\\Sane\\Desktop\\Text\\TextFile.txt"); 
			cout << "Успешное сохранение\n"; 
			break;

		case 'c': 
		{ 
			TText tmp; 
			tmp.Save("C:\\Users\\Sane\\Desktop\\Text\\TextFile.txt"); 
		} 
				  break;

		case 'e': clrscr(); 
			cout << "Выберите пункт для следующего действия \n\nn - новая строка \nr - чтение \np - печать \ns - сохранение \nq - выход \ne - очистка \nf - печать свободных звеньев \nd - сборщик мусора\n" <<
				"a - перейти по предыдущей ссылке \nz - перейти по следующей ссылке \nx - перейти по нисходящей ссылке \n1 - вставить следующую строку \n2 - вставить следующий раздел \n" <<
				"3 - вставить нисходящую строку \n4 - вставить нисходящий раздел \n5 - удалить следующее звено \n6 - удалить нисходящую ссылку \n";
			break;

		case 'f': TLink::PrintFree(); 
			break;

		case 'd': 
			if (readFlag) 
		{ 
			TLink::MemClear(text); cout << "Память очищена\n"; 
		}
				  else cout << "Уже пусто\n"; 
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

		case '1': cout << "Введите строку: "; 
			cin >> buf; 
			text.InsNextLine(buf); 
			text.Print();  
			break;

		case '2': cout << "Введите строку: "; 
			cin >> buf; 
			text.InsNextSection(buf); 
			text.Print();  
			break;

		case '3': cout << "Введите строку: "; 
			cin >> buf; 
			text.InsDownLine(buf); 
			text.Print(); 
			break;

		case '4': cout << "Введите строку: "; 
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

		default: cout << "Ошибка ввода\n";
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
