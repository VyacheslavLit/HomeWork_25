#include "Chat.h"


/*
	  --- ОСНОВНОЙ МЕТОД класса переписки Chat ---
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
void Chat::loginMenu()
{
	string operation;
	while (true)
	{
		clear();
		cout << "Логин меню:"<<endl;
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
	  --- ОСНОВНОЙ МЕТОД класса переписки Chat ---
		showChat  -  вывод  на  экран  переписки с возможностью продолжения
	переписки.
		В  данном  методе  предоставлен  бесконечный цикл, который  выводит
	переписку   и  дает  возможность  написать  новое  сообщение,  обновить
	переписку, чтобы проверить новые сообщения.
*/
void Chat::showChat()
{
	string txt, tmp, zapros, name;
	clear();
	/*
	Применение бесконечного цикла обеспечивает непрерывнсть работы
	и возможность обновлять переписку.
	*/
	while (true)
	{
		clear();
		string reply = client("m");
		cout << "                --- Общая переписка ---\n";
		cout << "| от кого | date                | text         |\n";
		int count = 0;
		for (int i = 0; i < reply.size(); i++)
		{
			cout << reply[i];
			if (reply[i] == ' ')
			{
				if (count != 1) cout << "\t";
				count++;
				if (count == 4)
				{
					count = 0;
					cout << endl;
				}
			}
		}
		cout << endl << "------------------------------------------------------------------\n";
		cout << "Введите сообщение или: 1 обновить переписку, 0 выйти из переписки.\n";
		cin>> txt;
		cin.ignore(32767, '\n');
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (txt == "1")continue;
		if (txt == "0")break;
		if (txt != "") client("d" + me_ + "+" + txt);
	}
}


/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода LoginMenu ---
		login - вход в прорамму по логину и паролю.
		В  даном  методе  пользователю дается возможность ввести свой логин
	и пароль. Производится их проверка, при наличии такой комбинации в базе
	пользователей     выбирается    текущий    пользователь    currentUser_
	и  присваивается  переменной  me_  имя текущео пользователя. если такой
	логин   отсутсвует   или  пароль  не  соответствует  введеному  логину,
	выводится ошибка, и предложение повториь ввод.
*/
void Chat::login() 
{
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

		string mes_cl ="l"+login+" "+password;
		tmp=client(mes_cl);
		for (int i = 0; i < size(tmp); ++i)
		{
			if (tmp[i] == 0) break;
			me_ += tmp[i];
		}
		if (me_=="0")
		{
			me_ = "";
			cout << "Логин или пароль введены не верно\nПовторите ввод.\n";
			continue;
		}
		if (me_=="b")
		{
			me_ = "";
			cout << "Данный пользователь забанен\nПопробуйте другова пользователя.\n";
			continue;
		}
		if (me_=="-1")
		{
			me_ = "";
			cout << "Связь с сервером не удалась, попробуйте еще.\n";
			continue;
		}
	} while (me_ == "");
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода LoginMenu ---
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
void Chat::registration()
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
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД ---
		expCin - метод отработки ошибки при испльзовании оператора cin.
		В  даном  методе  производится  очистка буфера ввода, игнорирование
	ошибок и выводится сообщение пользователю сообщения об ошибке.
*/
void Chat::expCin()
{
	cin.clear();
	cin.ignore(32767, '\n');
	cout << "Ошибка ввода, повторите попытку.\n";
	cin.get();
};

void Chat::pauses()
{
	cin.clear();
	cin.ignore(32767, '\n');
	cout << endl << "Для продолжени нажмите любую клавишу.";
	cout << cin.get();//pause
	cin.clear();
	cin.ignore(32767, '\n');
}

void Chat::clear()
{
#ifdef __Linux__
	system("clear");
#elif defined(_WIN32)||defined(_WIN64)
	system("cls");
#endif
}
