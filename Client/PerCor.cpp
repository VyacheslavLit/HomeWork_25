#include <iostream>
#include <ctime>
#include <fstream>
#include "PerCor.h"

/*
	  --- ОСНОВНОЙ МЕТОД класса личной переписки PerCop ---
		LoginMenu - вход и регистрацию пользователя.
		В данном методе предоставлется выбор и реализация Входа в переписку
	под  своим  логином  и  паролем, регистрация нвого пользователя и выход
	в предыдущее меню.
		Определяется    значение    указателя    currentUser_   (корректный
	пользователь)   текущий   пользователь,  от  лица  которого  происходит
	общение.
		База   пользователей   загружается   из   файла   User.txt,   новые
	пользователи добавляются в данный файл.
*/
void PerCor::loginMenuPC()
{
	string operation;
	while (true)
	{
		clear();
		cout << "Логин меню:" << endl;
		cout << "1. Вход.\n2. Регистрация.\n0. Выход в предыдущее меню.\n";
		cin >> operation;
		cin.clear();
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (operation == "1")
		{
			login();
			break;
		}
		//При регистрации отрабатываются исключения на повтор имён и логинов.
		if (operation == "2")
		{
			try
			{
				registration();
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
				pauses();
			}
			continue;
		}
		if (operation == "0")
		{
			break;
		}
		cout << "Выбор не пределен. Повторите попытку.\n";
		pauses();
		continue;
	}
}

/*
	  --- ОСНОВНОЙ МЕТОД класса личной переписки PerCop ---
		userMenuPC - выбор опонента по переписке.
		Выбор  может  быть  произведен  из уже начатых переписок или начата
	новая переписка.

*/
void PerCor::userMenuPC()
{
	clear();
	/*
	далее заполняется map Party(список пользователей, с которыми открыта переписка),
	чтобы в выводимой таблице пользователей мы могли указать с кем переписка уже ведется.
	*/
	map <string, string> party;
	string otvet = client("h");
	string me_id = client("e" + me_);
	otvet.resize(otvet.find('\0'));
	int i = 0;
	string from, to, tmp;
	while (1)
	{
		from.clear();
		to.clear();
		for (i; i < otvet.length(); ++i)
		{
			if (otvet[i] == ' ') break;
			from += otvet[i];
		}
		++i;
		for (i; i < otvet.length(); ++i)
		{
			if (otvet[i] == ' ') break;
			to += otvet[i];
		}
		if (from == me_id) party[to] = client("e" + to);
		if (to == me_id) party[from] = client("e" + from);
		if (i > otvet.length())break;
	}

//выбор собеседника из списка пользователей
	cout << "Привет, " << me_ << ".\nИмеются следующие участники:\n";
	cout << "---------------------------------------------------\n";
	otvet.clear();
	otvet = client("k");
	int j = 0;
	string id_userTMP;
	while (1)
	{
		id_userTMP.clear();
		for (j; j < otvet.length(); ++j)
		{
			if (otvet[j] == ' ')break;
			cout << otvet[j];
			id_userTMP += otvet[j];
		}
		++j;
		cout << "\t";
		for (j; j < otvet.length(); ++j)
		{
			if (otvet[j] == ' ')break;
			cout << otvet[j];
		}
		//при наличии переписки добавляется упоминание
		map <string, string> ::iterator it;
		for (it = party.begin(); it != party.end(); it++) if (it->first == id_userTMP) cout << "\t (имеется переписка)";
		//если пользователь забанен добавляется упоминание
		if (client("w" + id_userTMP) == "2") cout << "\t (забанен)";
		++j;
		cout << endl;
		if (j >= otvet.length()) break;
	}
	cout << "---------------------------------------------------\n";
//выбор партнера по переписке
	string n_nameTMP;
	while (true)
	{
		cout << "Выберите с кем открыть переписку, 0 - выход\n";
		cin >> tmp;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmp == "0") break;
		n_nameTMP.clear();
		n_nameTMP = client("e" + tmp);
		n_nameTMP.resize(n_nameTMP.find('\0'));
		if (n_nameTMP != "")
		{
			party_ = n_nameTMP;
			cout << endl << party_.size() << endl << party_.find("\0") << endl;
			break;
		}
		cout << "\nВыбор не определен, повторите выбор.\n";
	}
}

/*
	  --- ОСНОВНОЙ МЕТОД класса личной переписки PerCop ---
		showPC   -   вывод   на  экран  переписки  с  выбранным  оппонентом
	с возможностью продолжения переписки.
		В  данном  методе  предоставлен  бесконечный цикл, который  выводит
	переписку  с  оппонентом  и  дает возможность написать новое сообщение,
	обновить переписку,	чтобы проверить новые сообщения от оппонента.
*/
void PerCor::showPC()
{
	string txt;
	/*
	Применение бесконечного цикла обеспечивает непрерывнсть работы
	и возможность обновлять переписку.
	*/
	while (true)
	{
		chat();
		txt.clear();
		cout << "Введите сообщение или: 1 обновить переписку, 0 выйти из переписки.\n";
		cin >> txt;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		cin.ignore(32767, '\n');
		if (txt == "1")continue;
		if (txt == "0")break;
		client("q" + me_ + " " + party_ + " " + txt);
	}
}

/*
	  --- ОСНОВНОЙ МЕТОД класса личной переписки PerCop ---
		loginAdminPC - вход в личную переписку админа из класса Admin.
		В  данном  методе  определяется значение указателя currentUser_ как
	admin, от лица которого происходит общение.
		База   пользователей   загружается   из   файла   User.txt.
*/
void PerCor::loginAdminPC()
{
	string login = "admin";
	me_ = "admin";
}




/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода loginMenuPC ---
		login - вход в прорамму по логину и паролю.
		В  даном  методе  пользователю дается возможность ввести свой логин
	и пароль. Производится их проверка, при наличии такой комбинации в базе
	пользователей     выбирается    текущий    пользователь    currentUser_
	и  присваивается  переменной  me_  имя текущео пользователя. если такой
	логин   отсутсвует   или  пароль  не  соответствует  введеному  логину,
	выводится ошибка, и предложение повториь ввод.
*/
void PerCor::login() {
	string login, password, tmp;
	clear();
	do
	{
		cout << "Для входя введите логин и пароль, или 0 для выхода:\n";
		cout << "Логин: ";
		cin >> login;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (login == "0") break;
		cout << "Пароль: ";
		cin >> password;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (password == "0") break;

		string mes_cl = "l" + login + " " + password;
		tmp = client(mes_cl);
		for (int i = 0; i < size(tmp); ++i)
		{
			if (tmp[i] == 0) break;
			me_ += tmp[i];
		}
		if (me_ == "0")
		{
			me_ = "";
			cout << "Логин или пароль введены не верно\nПовторите ввод.\n";
			continue;
		}
		if (me_ == "b")
		{
			me_ = "";
			cout << "Данный пользователь забанен\nПопробуйте другова пользователя.\n";
			continue;
		}
		if (me_ == "-1")
		{
			me_ = "";
			cout << "Связь с сервером не удалась, попробуйте еще.\n";
			continue;
		}
	} while (me_ == "");
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода loginMenuPC ---
		registration - добавление новогопользователя в базу пользователей.
		В  даном  методе  пользователю  дается  возможность  добавить новую
	учетную запись, путем введения своих логина, пароля и имени.
		Производится  проверка  логина и имени на уникальность, при наличии
	повторов  в  базе  пользователей,  дается  возможность  повторить  ввод
	скорректировав повтор.
		По  результатам ввода вызывается дополнительный метод setUsersFile,
	для   добавления  нового  пользователя  в  базу  и  происходит  возврат
	в предыдущее меню.
*/
void PerCor::registration()
{
	string otvet, login, password, n_name, name, family, email;
	while (true)
	{
		string tmp;
		clear();
		cout << "Для регистрации нового пользователя введите данные. 0 - для выхода в предыдущее меню.:\n";
		cout << "Логин: ";
		cin >> login;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (login == "0") break;
		cout << "\nПароль: ";
		cin >> password;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (password == "0") break;
		cout << "\nИмя под которым будет вестись переписка: ";
		cin >> n_name;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (n_name == "0") break;
		cout << "\nИмя: ";
		cin >> name;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (name == "0") break;
		cout << "\nФамилия: ";
		cin >> family;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (family == "0") break;
		cout << "\nЭлектронная почта: ";
		cin >> email;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (email == "0") break;
		otvet = client("r" + login + " " + password + " " + n_name + " " + name + " " + family + " " + email);
		if (otvet == "1")
		{
			cout << "\nТакой логин занят. Повторите ввод.\n";
			pauses();
			continue;
		}
		if (otvet == "2")
		{
			cout << "\nТакой псевдоним занят. Повторите ввод.\n";
			pauses();
			continue;
		}
		return;
	}
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода showPC ---
		chat  -  вывод  на экран переписки с выбранным пользователем в виде
	таблицы	изходя из вектора messagePC_.
*/
void PerCor::chat()
{
	clear();
	string id, from, to, date, text, status, otvet;
	cout << "Переписка с " << party_ << "\n-----------------------------------------------------------------------\n";
	otvet.clear();
	otvet = client("j" + me_ + " " + party_);
	cout << "| id | id_from | id_to | date                | text         | status |\n";
	int count = 0;
	for (int i = 0; i < otvet.length(); i++)
	{
		if (count == 6)
		{
			if (otvet[i] == '1')
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
		}
		else	cout << otvet[i];
		if (otvet[i] == ' ')
		{
			if (count != 3) cout << "\t";
			count++;
		}
	}
	cout << endl << "------------------------------------------------------------------\n";
}


/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД ---
		expCin - метод отработки ошибки при испльзовании оператора cin.
		В  даном  методе  производится  очистка буфера ввода, игнорирование
	ошибок и выводится сообщение пользователю сообщения об ошибке.
*/
void PerCor::expCin()
{
	cin.clear();
	cin.ignore(32767, '\n');
	cout << "Ошибка ввода, повторите попытку.\n";
	cout << cin.get();//pause
	cin.clear();
	cin.ignore(32767, '\n');
};


void PerCor::pauses()
{
	cin.clear();
	cin.ignore(32767, '\n');
	cout << endl << "Для продолжени нажмите любую клавишу.";
	cout << cin.get();//pause
	cin.clear();
	cin.ignore(32767, '\n');
}

void PerCor::clear()
{
#ifdef __Linux__
	system("clear");
#elif defined(_WIN32)||defined(_WIN64)
	system("cls");
#endif
}



