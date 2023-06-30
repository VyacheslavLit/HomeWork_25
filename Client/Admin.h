#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <ctime>
#include <fstream>
#include "PerCor.h"
#include "Client.h"



/*
	Класс Admin - основной класс обеспечивающий администрирование.

	login_ - переменная индикатор входа							-- вспомогательные методы - метода LoginMenu --
	numAdmin_ - порядковый № в векторе			       inPassword - ввод пароля
	users_ - контейнер пользователей                   passChange - смена пароля
	message_ - контейнер с перепиской			       registration - регистрация пользователя
	currentAdmin_ - указатель на админа				   setUsersFile (дополнительный метод метода LoginMenu) -
				из общего контейнера рользователе					внесение зарегистриррованного пользователя в файл
																-- второстепенные методы - метода adminMenu --
													   ban - наложение, снятие бана
			--- ОСНОВНЫЕ МЕТОДЫ ---					   showChat - вывод чата на экран
	LoginMenu - вход администратора					   getMessage_File - заполнение вектора сообщений из файла
	adminMenu - основное меня для работы			   delMess - пометка сообщения как удаленного
				администатора						   upDelMess - снятие отметки об удалении с сообщения
													   setMessage_File - выгрузка сообщений из вектора в файл.
													   addMessage - добавление сообщения в чат и сохранения его в контейнер переписки
	getAdminByLogin - указатель проверяющий логин				-- вспомогательные методы --
		на предмеет повторов						   expCin - обработка ошибок при использовании оператора cin
	getAdminByName - указатель проверяющий имя		   getUsersFile - загрузкапользователей из файла
		на предмеет повторов						   setNumAdmin - присвоение значения numAdmin_
*/
class Admin
{
	bool login_{ false };

public:
	void loginMenu();
	void adminMenu();

	bool getLogin() { return login_; }
private:
	void inPassword();
	void passChange();
	void ban();
	void showChat();
	void expCin();

	void pauses();
	void clear();
};
