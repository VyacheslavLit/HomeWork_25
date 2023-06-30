#include "Admin.h"

/*
	  --- ОСНОВНОЙ МЕТОД класса администротора Admin ---
		LoginMenu - вход администратора.
		В   данном   методе   предоставлется  входа   под   своим  паролем,
	возможность его изменить и выход в предыдущее меню.
*/
void Admin::loginMenu()
{
	string tmp;
	while (true)
	{
		clear();
		cout << "1. Ввод пароля.\n2. Смена пароля.\n0. Выход в предыдущее меню.\n";
		cin >> tmp;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmp == "1")
		{
			inPassword();
			break;
		}
		if (tmp == "2")
		{
			passChange();
			continue;
		}
		if (tmp == "0")
		{
			break;
		}
		cout << "Выбор не пределен. Повторите попытку.\n";
		pauses();
		continue;
	}
}

/*
	  --- ОСНОВНОЙ МЕТОД класса администротора Admin ---
		adminMenu - меню администратора.
		В   данном   методе   администратор выбирает  в  каком  направлении
	работать на данный момент.
		1. Наложение (снятие) бана с пользователя
		2. Администрирование общего чата (возможность удалять сообщения  не
	проходящие цензуру)
		3. Личная  переписка  с  пользователями  (переход на класс PerCor -
	персональная переписка)
*/
void Admin::adminMenu()
{
	string tmp;
	while (true)
	{
		clear();
		cout << "----- Доступные разделы администриррования -----\n";
		cout << "1. Наложение (снятие) бана с пользователя.\n";
		cout << "2. Администрирование общего чата.\n";
		cout << "3. Личная переписка с пользователями\n";
		cout << "------------------------------------------------\n";
		cout << "Выберите необходимый раздел, 0 - выход из администрирования.\n";
		cin >> tmp;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmp == "0") break;
		if (tmp == "1")
		{
			ban();
			continue;
		}
		if (tmp == "2")
		{
			showChat();
			continue;
		}
		if (tmp == "3")
		{
			PerCor perCor;
			perCor.loginAdminPC();
			perCor.userMenuPC();
			if (!perCor.getParty().empty()) perCor.showPC();
			continue;
		}
		cout << "\nВыбор не определен.\nПовторите попытку\n";
		cin.get();
	}
}




/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода loginMenu ---
		loginMenu - ввод пароля.
*/
void Admin::inPassword()
{
	string tmp;
	while (!login_)
	{
		cout << "Введите пароль, 0 - выход без ввода пароля: ";
		cin >> tmp;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmp == "0") break;

		string mes_cl = "ladmin " + tmp;
		string reply = client(mes_cl);
		if (reply[0] == '0')
		{
			cout << "Пароль введен не верно\nПовторите ввод.\n";
			continue;
		}
		if (reply[0] == '-')
		{
			cout << "Связь с сервером не удалась, попробуйте еще.\n";
			continue;
		}
		login_ = (true);
	}
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода loginMenu ---
		passChange - смена пароля.
*/
void Admin::passChange()
{
	string tmpPass;
	string tmpPassNew1;
	string tmpPassNew2;
	string tmp;
	while (true)
	{
		clear();
		cout << "Введите действующий пароль, 0 - для выхода: ";
		cin >> tmpPass;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmpPass == "0")break;
		cout << "Введите новый пароль: ";
		cin >> tmpPassNew1;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		cout << "Повторите новый пароль: ";
		cin >> tmpPassNew2;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		string mes_cl = "ladmin " + tmp;
		string reply = client(mes_cl);
		if (reply == "0")
		{
			cout << "Пароль введен не верно\nПовторите ввод.\n";
			pauses();
			continue;
		}
		if (reply == "-1")
		{
			cout << "Связь с сервером не удалась, попробуйте еще.\n";
			pauses();
			continue;
		}
		if (tmpPassNew1 != tmpPassNew2)
		{
			cout << "\nНовые пароли не совпадают\nПовторите попытку.\n";
			pauses();
			continue;
		}
		client("cadmin " + tmpPassNew1);
		break;
	}
}


/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода adminMenu ---
		ban - в данном методе прописана возможность наложить  и снять бан на
	пользователя.

*/
void Admin::ban()
{
	string statusTMP;
	string tmpBan;
	string tmpUser;
	string reply;
	while (true)
	{
		clear();
		cout << "----- Перечень пользователей -----\n";
		cout << "| id | login | n_name | name  | family  | email           | status |\n";
		reply = client("u");
		int count = 0;
		for (int i = 0; i < reply.size(); i++ )
		{
			cout << reply[i];
			if (reply[i] == ' ')
			{
				cout << "\t";
				count++;
				if (count == 7)
				{
					count = 0;
					cout << endl;
				}
			}
		}
		cout << "\n----------------------------------\n";
		cout << "1. Снять бан.\n2. Наложить бан.\n-------------\nВыберите необходимую операцию, 0 - выход в предыдущее меню.\n";
//выбор операции
		cin >> tmpBan;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmpBan == "0")	break;
		if (tmpBan != "1" && tmpBan != "2")
		{
			cout << "Выбор не определен. Повторите ввод.\n";
			pauses();
			continue;
		}
//выбор пользователя
		cout << "Выберите id пользователя, 0 - выход в предыдущее меню: ";
		cin >> tmpUser;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmpUser == "0") break;
//запрос статуса пользователя по id
		statusTMP = client("w" + tmpUser);
		if (statusTMP == "")
		{
			cout << "Такого пользователя нет. Повторите ввод.\n";
			pauses();
			continue;
		}
		if (tmpBan == "2"&& statusTMP == "2") 
		{
			cout << "На данного пользователя бан уже наложен. Повторите ввод.\n";
			pauses();
			continue;
		}
		if (tmpBan == "1" && statusTMP == "1")
		{
			cout << "На данном пользователе бана нет. Повторите ввод.\n";
			pauses();
			continue;
		}
		cout << endl << "+" <<statusTMP<<"+status+"<<tmpUser<<"=" << endl;
//запрос на смену статуса пользователя
		reply = client("e" + tmpUser);
		if (reply == "admin")
		{
			cout <<endl<<"Ты вообще понял, что ты делаешь?\nКак ты собираешься банить себя?\n";
			pauses();
			continue;
		}
		string zapros = "v" + tmpUser + " " + tmpBan;
		cout << endl << "=" << zapros << "=zapros+" << tmpUser<<"+"<< tmpBan <<endl;
		client(zapros);
	}
}

/*
	  --- ДОПОЛНИТЕЛЬНЫЙ МЕТОД метода adminMenu ---
		showChat  -  вывод  на  экран  переписки с возможностью продолжения
	переписки и удаления сообщений пользователей.
		В  данном  методе  предоставлен  бесконечный цикл, который  выводит
	переписку   и  дает  возможность  написать  новое  сообщение,  обновить
	переписку, чтобы проверить новые сообщения, а также  удалить  сообщение
	не отвечающее правилам форума.
*/
void Admin::showChat()//const
{
	string txt, status, tmp;
	/*
	Применение бесконечного цикла обеспечивает непрерывнсть работы
	и возможность обновлять переписку.
	*/
	while (true)
	{
		clear();
		string reply = client("n");
		cout << "                --- Общая переписка ---\n";
		cout << "| id | от кого | date                | text         | status |\n";
		int count = 0;
		for (int i = 0; i < reply.length(); i++)
		{
			if (count == 5)
			{
				if (reply[i] == '1')
				{
					count = 0;
					cout << endl;
					i++;
					continue;
				}
				else 
				{
					count = 0;
					i++;
					cout << "\t(сообщение удалено)" << endl;
					continue;
				}
			} else	cout << reply[i];
			if (reply[i] == ' ')
			{
				if (count != 2) cout << "\t";
				count++;
			}
		}
		cout << endl << "------------------------------------------------------------------\n";
		cout << "Введите сообщение или: 1 снять удаление с сообщения, 2 - удалить сообщение,\n\t\t\t 3 - обновить переписку, 0 выйти из переписки.\n";
		cin >> txt;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (txt == "0")break;
		if (txt == "3")continue;
		if (txt == "1" || txt == "2")
		{
			cout << "\n№ сообщения для удаления/снятия удаления, 0 - выход из коррекировки: ";
			cin >> tmp;
			if (cin.fail())
			{
				expCin();
				continue;
			}
			if (tmp == "0") break;
			status = client("b" + tmp);
			if (status == "")
			{
				cout << "\nНет такого номера сообщения.\nПовторите ввод.\n";
				pauses();
				continue;
			}
			if (status == "2" && txt == "2")
			{
				cout << "\nСообщение уже удалено.\n";
				pauses();
				break;
			}
			if (status == "1" && txt == "1")
			{
				cout << "\nСообщение не удалено.\n";
				pauses();
				break;
			}
			client("a" + tmp + ' ' + txt);
			continue;
		}
		client("dadmin+" + txt);
	}
}


/*
	  --- вспомогательный метод класса администротора Admin ---
		expCin - обработка лшибок ввода с клавиатуры.
*/
void Admin::expCin()
{
	cin.clear();
	cin.ignore(32767, '\n');
	cout << "Ошибка ввода, повторите попытку.\n";
	cin.get();
};


void Admin::pauses()
{
	cin.clear();
	cin.ignore(32767, '\n');
	cout << endl << "Для продолжени нажмите любую клавишу.";
	cout << cin.get();//pause
}

void Admin::clear()
{
#ifdef __Linux__
	system("clear");
#elif defined(_WIN32)||defined(_WIN64)
	system("cls");
#endif
}

