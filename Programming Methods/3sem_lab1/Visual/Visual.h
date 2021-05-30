#pragma once
#include <string>
#include "TConsole.h"
#include "../TableManager.h"
#include <list>


class Visual
{
private:
	
	enum class menus
	{
		Formula,
		DeletePolynom,
		SaveToFile,
		LoadFromFile,
		Exit,
		menusCount
	};

	std::string menuStrings[(int)menus::menusCount] = {
		"Ввести формулу",
		"Удалить полином",
		"Сохранить в файл",
		"Загрузить из файла",
		"Выйти"
	};
	char allowedChars[11]{' ','=','+','-','*','^','.','(',')','\'',','};

	TConsole console;
	int tableXPos;
	Vector2i consoleSize;

	menus curMenu;

	bool OnMenuPressed();
	void InputOnMenu();
	void UpdateMenu();

	std::string InputStr(std::string info, bool goBack);

	TableManager tableManager;

	int prevPolynomsCount = 0;
	Vector2i prevMenuPos;

	std::list<std::string> prevInputs;
public:
	Visual(TableManager& tableManager);
	
	void UpdatePolynoms();

	

};

