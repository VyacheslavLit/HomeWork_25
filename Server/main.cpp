#include "Server.h"
#include <filesystem>
#include <locale>
#include <iostream>
#include <Windows.h>
using namespace std;



int main()
{
#ifdef __Linux__
	locale ru("ru_RU.utf8");
   	auto permissions=std::filesystem::perms::group_all | std::filesystem::perms::others_all;
	std::filesystem::permissions("./Messages.txt", permissions, std::filesystem::perm_options::remove);
   	std::filesystem::permissions("./Users.txt", permissions, std::filesystem::perm_options::remove);
	std::filesystem::permissions("./MessagesPC.txt", permissions, std::filesystem::perm_options::remove);
#elif defined(_WIN32)||defined(_WIN64)
	//system ("chcp 1251");

	//setlocale(LC_ALL, "Rus");
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
#endif


	Server server;
	server.miServer();
	return 0;
}

