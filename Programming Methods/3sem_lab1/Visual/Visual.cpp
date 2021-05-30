#include "Visual.h"
#include <conio.h>
#include <algorithm>
#include <math.h>
#include "../Parser/Parser.h"

#define COMMAND_KEYS 224
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DELETE 83

#define KEY_TAB 9
#define KEY_ENTER 13
#define KEY_SPACE 32
#define KEY_BACKSPACE 8

using namespace std;


string Visual::InputStr(string info, bool goBack=false)
{
	
	Vector2i prevPos = console.Where();
	console.GotoXY(0, max(tableManager.GetCount(), consoleSize.y - 1));

	UpdateMenu();

	int argNum = 0;
	cout << info << ": ";
	int startX = console.WhereX();

	string result = "";
	
	int tabNumOfClick = 0;
	string tabPart = "";

	string curInput = "";
	list<string>::iterator itMind = prevInputs.end();

	while (true)
	{
		int input = _getch();
		if (input == COMMAND_KEYS)
		{
			int arrow = _getch();
			if (arrow == KEY_LEFT)
			{
				int whereX = console.WhereX();
				if (whereX > startX)
				{
					console.GotoXY(whereX - 1, console.WhereY());
				}
			}
			else if (arrow == KEY_RIGHT)
			{
				int whereX = console.WhereX();
				if (whereX < startX+result.length())
				{
					console.GotoXY(whereX + 1, console.WhereY());
				}
			}
			else if (arrow == KEY_UP)
			{
				if (prevInputs.size() != 0 && itMind != prevInputs.begin())
				{
					if (itMind == prevInputs.end())
					{
						curInput = result;
					}
					itMind--;
					result = *(itMind);
					console.GotoXY(startX, console.WhereY());
					console.ClrEol();
					cout << result;
				}
			}
			else if (arrow == KEY_DOWN)
			{
				if (prevInputs.size() != 0 && itMind != prevInputs.end())
				{
					itMind++;
					if (itMind == prevInputs.end())
					{
						result = curInput;
					}
					else
					{
						result = *(itMind);
					}
					console.GotoXY(startX, console.WhereY());
					console.ClrEol();
					cout << result;
				}
			}
			else if (arrow == KEY_DELETE)
			{
				int erasePos = console.WhereX() - startX;
				if (erasePos < result.length())
				{
					result.erase(erasePos, 1);
					int whereX = console.WhereX();
					cout << result.substr(erasePos) << ' ';
					console.GotoXY(whereX, console.WhereY());
				}
			}
		}
		else if (input == KEY_TAB)
		{
			int curPos = console.WhereX() - startX;
			string leftStr = result.substr(0, curPos);
			int argNum = count(leftStr.begin(), leftStr.end(), ' ') + 1;
			int argStart = leftStr.find_last_of(' ') + 1;
			string arg = result.substr(argStart, curPos - argStart);

			if (tabNumOfClick==0)
			{
				tabPart = arg;
			}
			string newStr = tableManager.FindNameByPart(tabPart, tabNumOfClick);

			if (newStr == "")
			{
				tabNumOfClick = 0;
				newStr = tableManager.FindNameByPart(tabPart, tabNumOfClick);
			}

			if (newStr != "")
			{
				result.replace(argStart, arg.length(), newStr);
				console.GotoXY(startX+argStart, console.WhereY());
				console.ClrEol();
				cout << result.substr(argStart);
				tabNumOfClick++;
			}
			continue;
		}
		else if (input == KEY_ENTER)
		{
			console.GotoXY(0, console.WhereY());
			console.ClrEol();
			if (goBack)
			{
				console.GotoXY(prevPos);
			}
			else
			{
				console.GotoXY(0, console.WhereY());
			}
			UpdateMenu();
			prevInputs.push_back(result);
			return result;
		}
		else if (input == KEY_BACKSPACE)
		{
			int erasePos = console.WhereX() - startX;
			if (erasePos > 0)
			{
				result.erase(erasePos-1, 1);
				int whereX = console.WhereX() - 1;
				console.GotoXY(whereX, console.WhereY());
				cout << result.substr(erasePos-1) << ' ';
				console.GotoXY(whereX, console.WhereY());
			}
		}
		else if (isalpha(input) || isdigit(input) || std::find(std::begin(allowedChars), std::end(allowedChars), input) != std::end(allowedChars))
		{
			char inputChar = (char)input;
			int insertPos = console.WhereX() - startX;
			result.insert(insertPos, 1, inputChar);
			int whereX = console.WhereX();
			cout << result.substr(insertPos);
			console.GotoXY(whereX + 1, console.WhereY());
		}
		tabNumOfClick = 0;
	}
	
	throw "Must not be there";
}

bool Visual::OnMenuPressed()
{
	switch (curMenu)
	{
	case menus::Formula:
		{
			string str = InputStr("¬ведите формулу");
			try
			{
				try
				{
					Parser::Parse(str, &tableManager);
				}
				catch (const char* msg)
				{
					throw msg;
				}
				catch (...)
				{
					throw "Parsing Error";
				}
			}
			catch (const char* msg)
			{
				Vector2i prevPos = console.Where();
				cout << "error: " << msg;
				console.ReadKey();
				console.GotoXY(prevPos);
				console.ClrEol();
			}

			UpdateMenu();
			UpdatePolynoms();
		}
		break;
	case menus::DeletePolynom:

		{
			string str = InputStr("¬ведите им€ полинома");
			try
			{
				try
				{
					tableManager.Remove(str);
				}
				catch (const char* msg)
				{
					throw msg;
				}
				catch (...)
				{
					throw "Can't remove polynom";
				}
			}
			catch (const char* msg)
			{
				Vector2i prevPos = console.Where();
				cout << "error: " << msg;
				console.ReadKey();
				console.GotoXY(prevPos);
				console.ClrEol();
			}

			UpdateMenu();

			UpdatePolynoms();
		}

		break;
	case menus::SaveToFile:
		{
			string str = InputStr("¬ведите им€ файла");
			tableManager.Write(str);
		}
		break;
	case menus::LoadFromFile:
		{
			string str = InputStr("¬ведите им€ файла");
			try
			{
				try
				{
					tableManager.Read(str);
				}
				catch (const char* msg)
				{
					throw msg;
				}
				catch (...)
				{
					throw "File doesn't exist";
				}
			}
			catch (const char* msg)
			{
				Vector2i prevPos = console.Where();
				cout << "error: " << msg;
				console.ReadKey();
				console.GotoXY(prevPos);
				console.ClrEol();
			}
			UpdateMenu();
			UpdatePolynoms();
		}
		break;
	case menus::Exit:
		return true;
	default:
		break;
	}
	return false;
}

void Visual::InputOnMenu()
{
	int c = _getch();
	int arrow;
	bool exit = false;
	switch (c)
	{
	case KEY_ENTER:
		exit = OnMenuPressed();
		break;
	case COMMAND_KEYS:
		arrow = _getch();
		switch (arrow)
		{
		case KEY_DOWN:
			curMenu = (menus)(((int)curMenu + 1) % (int)menus::menusCount);
			UpdateMenu();
			break;
		case KEY_UP:
			curMenu = (menus)(((int)curMenu + (int)menus::menusCount - 1) % (int)menus::menusCount);
			UpdateMenu();
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	
	if (!exit)
	{
		InputOnMenu();
	}
}

Visual::Visual(TableManager& tableManager)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//console.Window(120, 50);
	consoleSize = console.GetWindowSize();

	tableXPos = (int)(consoleSize.x * 2.0 / 3.0);
	console.GotoXY(0, consoleSize.y-1);

	curMenu = (menus)0;

	this->tableManager = tableManager;
	UpdateMenu();
	UpdatePolynoms();

	InputOnMenu();
}

void Visual::UpdatePolynoms()
{
	if (tableManager.GetTablesCount() == 0)
	{
		return;
	}

	Vector2i lastPos = console.Where();
	bool wasLVertical = console.IsLVertical();
	bool wasUnderscore = console.IsUnderscore();

	console.SetUnderscore(false);
	Table* firstTable = tableManager.GetTable(0);
	int i = 0;
	for (auto it = firstTable->begin(); it != firstTable->end(); it++, i++)
	{
		string str = (*it).GetName() + " = " + (*it).polynomial.ToStr();
		console.GotoXY(tableXPos, i);
		console.ClrEol();
		if (i+1 == firstTable->GetCount())
		{
			console.SetUnderscore(true);
		}
		console.SetLVertical(true);
		if (str.length() != 0)
		{
			cout << str.substr(0, 1);
		}
		console.SetLVertical(false);
		if (str.length() > 1)
		{
			cout << str.substr(1, str.length() - 1);
		}
	}
	console.SetLVertical(false);
	console.SetUnderscore(false);

	for (; i < prevPolynomsCount; i++)
	{
		console.GotoXY(tableXPos, i);
		console.ClrEol();
	}
	prevPolynomsCount = tableManager.GetCount();

	console.SetLVertical(wasLVertical);
	console.SetUnderscore(wasUnderscore);
	console.GotoXY(lastPos);
}

void Visual::UpdateMenu()
{
	Vector2i pos(0, max(0, max(tableManager.GetCount(), console.WhereY()+1) - consoleSize.y));

	Vector2i lastConsolePos = console.Where();
	Colors prevTextColor = console.GetTextColor();
	Colors prevBackgroundColor = console.GetBackgroundColor();

	for (int i = 0; i < (int)menus::menusCount; i++)
	{
		Vector2i p(0, i);
		console.GotoXY(p + prevMenuPos);

		string str(string(to_string(i) + "." + menuStrings[i] + ".").length(), ' ');
		cout << string(string(to_string(i) + "." + menuStrings[i] + ".").length(), ' ');
	}


	
	for (int i = 0; i < (int)menus::menusCount; i++)
	{
		Vector2i p(0, i);
		console.GotoXY(p + pos);
		console.SetBackgroundColor((int)curMenu == i ? Colors::COLOR_WHITE : Colors::COLOR_BLACK);
		console.SetTextColor((int)curMenu == i ? Colors::COLOR_BLACK : Colors::COLOR_WHITE);

		cout << string(to_string(i) + "." + menuStrings[i] + ".");
	}
	console.SetBackgroundColor(prevBackgroundColor);
	console.SetTextColor(prevTextColor);
	console.GotoXY(lastConsolePos);

	prevMenuPos = pos;
}






