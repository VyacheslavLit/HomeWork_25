#pragma once
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <fstream>
#include <iterator>
#include <string.h>
#include "PerCor.h"
#include "Client.h"


/*
	Класс Chat - основной класс обеспечивающий общую переписку.

	me_ - переменная определяющая пользователя              -- второстепенные методы - метода LoginMenu --
	users_ - контейнер пользователей					getUsersFile  -  загрузка  пользователей в контейнер из файла
	message_ - контейнер с перепиской					login - вход пользователя
	currentUser_ - указатель на пользователя (меня)		registration - регистрация пользователя
			из общего контейнера пользователей				setUsersFile (дополнительный метод метода registration) -
																		внесение   зарегистрированного  пользователя
		--- ОСНОВНЫЕ МЕТОДЫ ---											в файл
	LoginMenu - вход и регистрацию пользователя				-- второстепенные методы - метода showChat --
	showChat - переписка								getMessage_File - загрузка переписки из файла
														chat - вывод переписки
	getUserByLogin - указатель проверяющий логин		addMessage - добавление  сообщения  в  чат  и  сохранения его
		на предмет повторов										в контейнер переписки
	getUserByName - указатель проверяющий имя				-- вспомогательный метод --
		на предмет повторов								expCin - обработка ошибок при использовании оператора cin
*/
class Chat {
	string me_ = ""; 

public:
	string getMe() const { return me_; }
	void loginMenu();
	void showChat();

private:
	void login();
	void registration();
	void expCin();

	void pauses();
	void clear();
};

