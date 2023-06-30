#include "Menu.h"
#include <filesystem>
#include <locale>
#include <iostream>
using namespace std;

#ifdef __Linux__
#include <mysql/mysql.h>
#elif defined(_WIN32)||defined(_WIN64)
#include <mysql.h>
#include <Windows.h>
#else 
#error Not implemented!
#endif

void clear()
{
#ifdef __Linux__
	system("clear");
#elif defined(_WIN32)||defined(_WIN64)
	system("cls");
#endif
}

/*Баззовая функция.
  В ней пользовательвыбирает между тремя возможными вариантами работы:

  1. Администрироваие  функции администратора и модератора.
  2. общий чат, в котором все пользователи могут общаться одновременно.
  3. личная переписка, в данном варианте предусмтрено общение тет&тет, другие пользователи не могут просмотреть переписку 2 пользователей.
  4. просмотр правил пользоваия чатом.
  И конечно предусмотрен выход из прграммы.
*/
int main()
{
#ifdef __Linux__
	locale ru("ru_RU.utf8"); 
#elif defined(_WIN32)||defined(_WIN64)
	system ("chcp 65001");
	setlocale(LC_ALL, "Rus");
	//SetConsoleCP(1200);
	//SetConsoleOutputCP(1200);
#endif
	int tmp;
	//бесконечный цикл для обеспечения непрерывной работы программы.
	while (true)
	{
		clear();
		cout << "Выбирите раздел:\n1. Администрирование.\n2. Чат.\n3. Личная переписка.\n4. Правила пользования чатом.\n0. Выход.\n";
		cin.clear();
		cin >> tmp;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
		}
		if (tmp == 1)
		{
			administration();
			continue;
		}
		if (tmp == 2)
		{
			chat();
			continue;
		}
		if (tmp == 3)
		{
			perCor();
			continue;
		}
		if (tmp == 4)
		{
			regulation();
			continue;
		}
		if (tmp == 0)
		{
			cout << "Нам жаль, что вы уже уходите. Приходите еще.\n";
			pauses();
			break;
		}
		cout << "Выбор не определен. Повторите попытку.\n";
		pauses();
		continue;
	}
	return 0;
}
