#include "Client.h"

string client(string mes_cl)
{
	//�������� ���������
	const char SERVER_IP[] = "127.0.0.1";					// IPv4 ������ �������
	const short SERVER_PORT_NUM = 7777;				// ���� �������
	const short BUFF_SIZE = 1024;					// ������������ ������ ������������ ���������� ���������

	// �������� ���������� ��� ���� ���������
	int erStat;										// ��� �������� ������ � �������� �������

	//IP-����� � ��������� ������� ������������� � �������� ������ ��� ������� ������. ������ ��������� � "ip_to_num"
	in_addr ip_to_num;
	inet_pton(AF_INET, SERVER_IP, &ip_to_num);


	// ������������� WinSock
	WSADATA wsData;
	erStat = WSAStartup(MAKEWORD(2, 2), &wsData);

	if (erStat != 0) {
		cout << "Error WinSock version initializaion #";
		cout << WSAGetLastError();
		return 0;
	}

	// ������������� Socket 
	SOCKET ClientSock = socket(AF_INET, SOCK_STREAM, 0);

	if (ClientSock == INVALID_SOCKET) {
		cout << "������ ������������� ������ # " << WSAGetLastError() << endl;
		closesocket(ClientSock);
		WSACleanup();
	}

	// ������������ ���������� � ��������
	sockaddr_in servInfo;

	ZeroMemory(&servInfo, sizeof(servInfo));

	servInfo.sin_family = AF_INET;
	servInfo.sin_addr = ip_to_num;
	servInfo.sin_port = htons(SERVER_PORT_NUM);

	erStat = connect(ClientSock, (sockaddr*)&servInfo, sizeof(servInfo));

	if (erStat != 0) {
		cout << "�� ������� ������������ � �������. Error # " << WSAGetLastError() << endl;
		closesocket(ClientSock);
		WSACleanup();
		return 0;
	}



	while (true) {
		vector <char> servBuff(BUFF_SIZE);// ����� ��� ��������� ������
		short packet_size = 0;// ������ �������������/������������ ������ � ������
		vector<char> clientBuff; //����� ��� �������� ������
		int i;
		for (i = 0; i < mes_cl.size(); ++i)clientBuff.push_back(mes_cl[i]);
		clientBuff.push_back('~');

		packet_size = send(ClientSock, clientBuff.data(), clientBuff.size(), 0);
		if (packet_size == SOCKET_ERROR) {
			cout << "�� ������� ��������� ��������� �� ������. Error # " << WSAGetLastError() << endl;
			closesocket(ClientSock);
			WSACleanup();
			return 0;
		}

		packet_size = recv(ClientSock, servBuff.data(), 1024, 0);
		if (packet_size == SOCKET_ERROR) {
			cout << "�� ������� �������� ��������� � �������. Error # " << WSAGetLastError() << endl;
			closesocket(ClientSock);
			WSACleanup();
			return 0;
		}
		else
		{
			string otvet(servBuff.begin(), servBuff.end());
			closesocket(ClientSock);
			WSACleanup();
			return otvet;
		}
	}
}