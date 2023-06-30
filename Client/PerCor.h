#pragma once
#include <vector>
#include <memory>
#include <set>
#include <exception>
#include <iostream>
#include <map>
#include "Client.h"


//отработка исключений на повтор логина
struct ExpLogin :public exception
{
	const char* what() const noexcept override
	{
		return "К сожалению данный логин занят, измените логин.\n";
	}
};

//отработка исключений на повтор имени
struct ExpName :public exception
{
	const char* what() const noexcept override
	{
		return "К сожалению данное имя занято, измените имя.\n";
	}
};




/*
	Класс PerCor - основной класс обеспечивающий линую переписку.

	me_ - переменная определяющая пользователя              -- второстепенные методы - метода LoginMenu --
	party_ - переменная определяющая собеседника       login - вход пользователя
				--- ОСНОВНЫЕ МЕТОДЫ ---			       registration - регистрация пользователя
	LoginMenuPC - вход и регистрацию пользователя      
	UserMenuPC - выбор собеседника							 -- второстепенные методы - метода UserMenu --
	showPC - переписка								   perCorParty - заполнение контейнера пользователей с которыми открыта личная переписка
															-- второстепенные методы - метода showPC --
													   chat - вывод личной переписки с выбранным собеседником
*/
class PerCor {
	string me_="";
	string party_="";

public:
	string getMe() const { return me_; }
	void loginMenuPC();
	void userMenuPC();
	void showPC();
	void loginAdminPC();
	auto getParty() { return party_; }

private:
	void login();
	void registration();
	void chat();
	void expCin();

	void pauses();
	void clear();
};
