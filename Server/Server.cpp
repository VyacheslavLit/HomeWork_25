#include "Server.h"



void Server::miServer()
{
    WSADATA wsData;
    int erStat = WSAStartup(MAKEWORD(2, 2), &wsData);
    if (erStat != 0)
    {
        cout << "Ошибка инициализации версии WinSock #";
        cout << WSAGetLastError();
        return;
    }
    else cout << "WinSock инициализирован.\n";

    //создадим сокет
    sockert_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (sockert_file_descriptor == -1)
    {
        cout << "Создание сокета неудачно!\n";
        exit(1);
    }
    memset(&serveraddress, 0, sizeof(serveraddress));
    serveraddress.sin_addr.s_addr = htonl(2130706433);
    //задаем номер порта для связи
    serveraddress.sin_port = htons(PORT);
    //используем IPv4
    serveraddress.sin_family = AF_INET;
    //привяжем сокет
    bind_status = bind(sockert_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if (bind_status == -1)
    {
        cout << "Не удалось выполнить привязку сокета.!" << endl;
        exit(1);
    }
    //поставим сервер на прием данных
    connection_status = listen(sockert_file_descriptor, 5);
    if (connection_status == -1)
    {
        cout << "Сокет не может прослушивать новые подключения.!" << endl;
        exit(1);
    }
    length = sizeof(client);

    //while (1)
    //{
    //    string tmp, zapros_;
    //    tmp.clear();
    //    cout << "1. Экспорт базы.\n";
    //    cout << "2. Импорт базы.\n";
    //    cout << "3. Работа сервера.\n";
    //    cin >> tmp;
    //    if (tmp == "3") break;
    //    if (tmp != "1" && tmp != "2") break;

    //    MYSQL mysql;
    //    MYSQL_RES* res;
    //    MYSQL_ROW row;

    //    int i = 0;

    //    // Получаем дескриптор соединения
    //    mysql_init(&mysql);
    //    if (&mysql == nullptr) {
    //        // Если дескриптор не получен — выводим сообщение об ошибке
    //        cout << "Error: can't create MySQL-descriptor" << endl;
    //    }

    //    // Подключаемся к серверу
    //    if (!mysql_real_connect(&mysql, "localhost", "root", "1111", "chat", NULL, NULL, 0)) {
    //        // Если нет возможности установить соединение с БД выводим сообщение об ошибке
    //        cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
    //    }
    //    else {
    //        // Если соединение успешно установлено выводим фразу — "Success!"
    //        cout << "Success!" << endl;
    //    }

    //    if (tmp == "1")
    //    {
    //        zapros_.clear();
    //        zapros_ = "mysqldump - u root - p chat > data - dump.sql";
    //        mysql_query(&mysql, const_cast<char*>(zapros_.c_str())); //Делаем запрос к таблице
    //    }
    //        

    //    mysql_set_character_set(&mysql, "utf8");
    //    //Смотрим изменилась ли кодировка на нужную, по умолчанию идёт latin1
    //    cout << "connection characterset: " << mysql_character_set_name(&mysql) << endl;
    //    // Закрываем соединение с сервером базы данных
    //    mysql_close(&mysql);
    //}


    //Communication Establishment - Установление связи
    string pref;
    while (true)
    {
        cout << "Сервер прослушивает новое соединение:" << " " << connection << endl;
        string mes_suf = "", reply = "";
        mes_suf.clear();
        memset(message, 0, MESSAGE_LENGTH);
        connection = accept(sockert_file_descriptor, (struct sockaddr*)&client, &length);
        if (connection == -1)
        {
            cout << "Сервер не может принять данные от клиента.!" << endl;
            exit(1);
        }

        recv(connection, message, sizeof(message), 0);
        pref = message[0];
        for (int i = 1; i < MESSAGE_LENGTH; i++)
        {
            if (message[i] == '~')break;
            mes_suf = mes_suf + message[i];
        }
        if (pref=="l")
        {
            string log;
            log = time() + " Запрос от пользователя на логин."; 
            string zapros = "insert log (log) value ('" + log + "')";
            zaprosMySQL(zapros);
//выделение из запроса логина и пароля
            int i;
            string _login, password;
            for (i = 1; i < sizeof(message); i++)
            {
                if (message[i] == ' ') break;
                _login += message[i];
            }
            i++;
            for (i; i < sizeof(message); i++)
            {
                if (message[i] == '~') break;
                password += message[i];
            }
//запрос и ответ с SQL, n_name, status, pass по логину
            zapros = "select n_name, status, hash from login_pass where login = '"+_login+"';";
            string otvet = zaprosMySQL(zapros);
            string n_name, status, hash;
            for (i = 0; i < otvet.size(); i++) if (otvet[i] != ' ') n_name += otvet[i]; else
            {
                i++;
                break;
            }
            for (i; i < otvet.size(); i++) if (otvet[i] != ' ') status += otvet[i]; else
            {
                i++;
                break;
            }
            for (i; i < otvet.size(); i++) if (otvet[i] != ' ') hash += otvet[i];
//делаем запись в логах
            if (password != hash)
            {
                log = " Логин пользователя не удачен.";
                reply = "0";
            } else
            if (status == "2")
            {
                log = " Пользователь забанен, логин отклонен.";
                reply = "b";
            }
            else
            {
                reply = n_name;
                log = " Логин пользователя " + reply + " одобрен.";
            }
            zapros = "insert log (log) value ('"+log+"');";
            zaprosMySQL(zapros);
        }
//регистрация пользователя
        if (pref=="r") 
        {
            string log;
            log = time() + " Запрос от пользователя на регистрацию.";
            string zapros = "insert log (log) value ('" + log + "');";
            zaprosMySQL(zapros);
            cout << log <<endl;
            reply=reg(mes_suf);
            if (reply=="0")log = time() + " Регистрация пользователя одобрена.";
            if (reply=="1" || reply=="2") log = time() + " Регистрация пользователя не удачна.";
            zaprosMySQL("insert log (log) value ('" + log + "');");
        }
        if (pref == "m")
        {
            string log;
            log = time() + " Запрос от пользователя содержимого файла переписки.";
            string zapros = "insert log (log) value ('" + log + "');";
            zaprosMySQL(zapros);
            cout << log << endl;
            zapros = "select u.n_name, m.date, m.text from global_message m join users u on m.id_from = u.id where m.status = 1;";
            reply = zaprosMySQL(zapros);
        }
        if (pref == "n")
        {
            string log;
            log = time() + " Запрос от админа содержимого файла общей переписки.";
            string zapros = "insert log (log) value ('" + log + "');";
            zaprosMySQL(zapros);
            cout << log << endl;
            zapros = "select m.id, u.n_name, m.date, m.text, m.status from global_message m join users u on m.id_from = u.id order by + m.id";
            reply = zaprosMySQL(zapros);
        }
        if (pref == "u")
        {
            string log;
            log = time() + " Запрос от пользователя содержимого файла пользователей.";
            cout << log << endl;
            zaprosMySQL("insert log (log) value ('" + log + "')");
            reply = zaprosMySQL("select * from users");
        }
        if (pref == "k")
        {
            string log;
            log = time() + " запрос id, n_name всех пользователей.";
            cout << log << endl;
            zaprosMySQL("insert log (log) value ('" + log + "')");
            reply = zaprosMySQL("select id, n_name from users");
        }
        if (pref == "e")
        {
            string log;
            log = time() + " Запрос имени по id пользователя.";
            cout << log << endl;
            zaprosMySQL("insert log (log) value ('" + log + "')");
            reply = zaprosMySQL("select n_name from users where id = '" + mes_suf + "'");
        }
        if (pref == "f")
        {
            string log;
            log = time() + "запрос id по имени пользователя.";
            cout << log << endl;
            zaprosMySQL("insert log (log) value ('" + log + "')");
            reply = zaprosMySQL("select id from users where n_name = '" + mes_suf + "'");
        }
        if (pref == "g")
        {
            string log;
            log = time() + "запрос id по логину пользователя.";
            cout << log << endl;
            zaprosMySQL("insert log (log) value ('" + log + "');");
            reply = zaprosMySQL("select id from users where login = '" + mes_suf + "'; ");
        }
        if (pref == "w")
        {
            string log;
            log = time() + " Запрос статуса пользователя по id.";
            cout << log << endl;
            zaprosMySQL("insert log (log) value ('" + log + "');");
            string zapros = "select status from users where id = '" + mes_suf + "';";
            reply = zaprosMySQL(zapros);
        }
        if (pref == "h")
        {
            string log;
            log = time() + " Запрос id_from, id_to из личной переписки.";
            cout << log << endl;
            zaprosMySQL("insert log (log) value ('" + log + "');");
            reply = zaprosMySQL("select id_from, id_to from message");
        }
        if (pref == "j")
        {
            string log, id_from, n_name_from, id_to, n_name_to;
            int i;
            for (i = 0; i < mes_suf.size(); i++)
            {
                if (mes_suf[i] == ' ')break;
                n_name_from += mes_suf[i];
            }
            i++;
            for (i; i < mes_suf.size(); i++)
            {
                n_name_to += mes_suf[i];
            }
            id_from = zaprosMySQL("select id from users where n_name = '" + n_name_from + "'");
            id_to = zaprosMySQL("select id from users where n_name = '" + n_name_to + "'");
            log = time() + " Запрос личной переписки по 2 пользователям.";
            cout << log << endl;
            zaprosMySQL("insert log (log) value ('" + log + "');");
            reply.clear();
            reply = zaprosMySQL("select id, id_from, id_to, date, text, status from message where (id_from = '" + id_from + "' and id_to = '" + id_to + "') or (id_from = '" + id_to + "' and id_to = '" + id_from + "');");
        }
        if (pref == "b")
        {
            string log;
            log = time() + " Запрос статуса сообщения общей переписки по id.";
            cout << log << endl;
            zaprosMySQL("insert log (log) value ('" + log + "');");
            string zapros = "select status from global_message where id = '" + mes_suf + "';";
            reply = zaprosMySQL(zapros);
        }
        if (pref == "v")
        {
            string log, status, id;
            int i;
            for (i = 1; i < sizeof(message); i++)
            {
                if (message[i] == ' ')break;
                id += message[i];
            }
            i++;
            for (i; i < sizeof(message); i++)
            {
                if (message[i] == '~')break;
                status += message[i];
            }
            log = time() + "запрос смены статуса пользователя по id.";
            cout << log << endl;
            zaprosMySQL("insert log (log) value ('" + log + "');");
            zaprosMySQL("update users set status = " + status + " where id = " + id + ";");
        }
        if (pref == "a")
        {
            string log, status, id;
            int i;
            for (i = 1; i < sizeof(message); i++)
            {
                if (message[i] == ' ')break;
                id += message[i];
            }
            i++;
            for (i; i < sizeof(message); i++)
            {
                if (message[i] == '~')break;
                status += message[i];
            }
            log = time() + "запрос смены статуса сообщения общей переписки по id.";
            cout << log << endl;
            zaprosMySQL("insert log (log) value ('" + log + "');");
            zaprosMySQL("update global_message set status = " + status + " where id = '" + id + "'");
        }
        if (pref == "d")
        {
            string log, id, text, n_name;
            int i;
            char suf = '~';
            mes_suf.push_back(suf);
            for (i = 0; i < sizeof(mes_suf); i++)
            {
                if (mes_suf[i] == '+')break;
                n_name += mes_suf[i];
            }
            i++;
            for (i; i < mes_suf.length(); i++)
            {
                if (mes_suf[i] == '~')break;
                text += mes_suf[i];
            }
            log = time() + "запрос добавление сообщения общей переписки.";
            cout << log << endl;
            zaprosMySQL("insert log (log) value ('" + log + "')");
            id = zaprosMySQL("select id from users where n_name = '" + n_name + "'");
            zaprosMySQL("insert global_message (id_from, text) value ('" + id + "', '" + text + "')");
        }
        if (pref == "q")
        {
            string log, id_from, id_to, text, n_name_from, n_name_to;
            int i;
            mes_suf+= '~';
            for (i = 0; i < sizeof(mes_suf); i++)
            {
                if (mes_suf[i] == ' ')break;
                n_name_from += mes_suf[i];
            }
            i++;
            for (i; i < sizeof(mes_suf); i++)
            {
                if (mes_suf[i] == ' ')break;
                n_name_to += mes_suf[i];
            }
            i++;
            for (i; i < mes_suf.length(); i++)
            {
                if (mes_suf[i] == '~')break;
                text += mes_suf[i];
            }
            log = time() + "запрос добавление сообщения общей переписки.";
            cout << log << endl;
            zaprosMySQL("insert log (log) value ('" + log + "')");
            id_from = zaprosMySQL("select id from users where n_name = '" + n_name_from + "'");
            id_to = zaprosMySQL("select id from users where n_name = '" + n_name_to + "'");
            zaprosMySQL("insert message (id_from, id_to, text) value ('" + id_from + "', '" + id_to + "', '" + text + "')");
        }
        if (pref == "c")
        {
            string log;
            log = time() + " Запрос на смену пароля.";
            cout << log << endl;
            zaprosMySQL("insert log (log) value ('" + log + "')");
            reply = changPassw(mes_suf);
        }
        memset(message, 0, MESSAGE_LENGTH);
        reply.copy(message, reply.length() + 1);
        auto bytes = send(connection, message, sizeof(message), 0);
        // Если передали >= 0 байт, значит пересылка прошла успешно
        if (bytes >= 0)
        {
            cout << "Данные успешно переданы клиенту!" << endl;
        }
    }
    //закрываем сокет, завершаем соединение
    closesocket(sockert_file_descriptor);

    return;
}


string Server::zaprosMySQL(string zapros)
{
    MYSQL mysql;
    MYSQL_RES* res;
    MYSQL_ROW row;

    int i = 0;

    // Получаем дескриптор соединения
    mysql_init(&mysql);
    if (&mysql == nullptr) {
        // Если дескриптор не получен — выводим сообщение об ошибке
        cout << "Error: can't create MySQL-descriptor" << endl;
    }

    // Подключаемся к серверу
    if (!mysql_real_connect(&mysql, "localhost", "root", "1111", "chat", NULL, NULL, 0)) {
        // Если нет возможности установить соединение с БД выводим сообщение об ошибке
        cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
    }
    else {
        // Если соединение успешно установлено выводим фразу — "Success!"
        cout << "Success!" << endl;
    }

    mysql_query(&mysql, "set names utf8mb4");
    //Смотрим изменилась ли кодировка на нужную, по умолчанию идёт latin1
    cout << "connection characterset: " << mysql_character_set_name(&mysql) << endl;


    cout << "Запрос: " << zapros<<endl;
    mysql_query(&mysql, const_cast<char*>(zapros.c_str())); //Делаем запрос к таблице

    //Выводим все что есть в базе через цикл
    string otvet;
    if (res = mysql_store_result(&mysql)) {
        while (row = mysql_fetch_row(res)) {
            for (i = 0; i < mysql_num_fields(res); i++) otvet = otvet + row[i] + " ";
        }
    } 
    if (otvet.size()>0) if (otvet[otvet.size() - 1] == ' ')otvet.pop_back();
    cout << "Ответ: " << otvet << endl;
    // Закрываем соединение с сервером базы данных
    mysql_close(&mysql);

    return otvet;
}

string Server::reg(string message)
{
    int i;
    string login, id_user, password, n_name, name, family, email;
    message += '~';
    for (i=0; i<sizeof(message);i++)
    {
        if (message[i]==' ') break;
        login+=message[i];
    }
    i++;
    for (i; i < sizeof(message); i++)
    {
        if (message[i] == ' ') break;
        password += message[i];
    }
    i++;
    for (i; i < sizeof(message); i++)
    {
        if (message[i] == ' ') break;
        n_name += message[i];
    }
    i++;
    for (i; i < sizeof(message); i++)
    {
        if (message[i] == ' ') break;
        name += message[i];
    }
    i++;
    for (i; i < sizeof(message); i++)
    {
        if (message[i] == ' ') break;
        family += message[i];
    }
    i++;
    for (i;i<sizeof(message);i++)
    {
        if (message[i]=='~') break;
        email += message[i];
    }

//проверка логина на повторы
    string zapros = "select id from users where login = '" + login + "'";
    string otvet = zaprosMySQL(zapros);
    if (otvet!="") return ("1");
//проверка псевдонима на повторы
    zapros = "select id from users where n_name = '" + n_name + "'";
    otvet = zaprosMySQL(zapros);
    if (otvet != "") return ("2");
//сохранение данных пользователя
    zapros = "insert users (login, n_name, name, family, email) value ('" + login + "', '" + n_name + "', '" + name + "', '" + family + "', '" + email + "')";
    zaprosMySQL(zapros);
    zapros = "select id from users where login = '" + login + "'";
    id_user = zaprosMySQL(zapros);
    zapros = "insert pass (id_user, hash) value ('" + id_user + "', '" + password + "')";
    zaprosMySQL(zapros);
    return ("0");
}




string Server::changPassw(string request)
{
    string n_name;
    string password;
    request += '~';
    int i;
    for (i=0;i<sizeof(request);i++)
    {
        if (request[i]==' ')break;
        n_name += request[i];
    }
    i++;
    for (i; i < sizeof(request); i++)
    {
        if (request[i] == '~')break;
        password += request[i];
    }
    zaprosMySQL("update pass p join users u set p.hash = '" + password + "' where p.id_user = (select id from users where n_name = '" + n_name + "')");
    return "0";
}



void expCin()
{
	cin.clear();
	cin.ignore(32767, '\n');
	cout << "Ошибка ввода, повторите попытку.\n";
	cout << cin.get();
	cin.clear();
	cin.ignore(32767, '\n');
};

void Server::pauses()
{
	cin.clear();
	cin.ignore(32767, '\n');
	cout << endl << "Для продолжени нажмите любую клавишу.";
	cout << cin.get();//pause
}