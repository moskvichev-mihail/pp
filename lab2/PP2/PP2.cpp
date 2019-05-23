#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"
#include <string>

void ShowHelp()
{
	std::cout << "To launch the application, you need to pass 2 arguments: " << std::endl;
	std::cout << "	1) count of the Bank Client object" << std::endl;
	std::cout << "	2)primitive type: " << std::endl;
	std::cout << "		0 - mutex" << std::endl;
	std::cout << "		1 - critical section" << std::endl;
}

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		std::string command = argv[1];
		if (command == "/?")
		{
			ShowHelp();
			return 1;
		}
	}

	if (argc != 3)
	{
		return 1;
	}

	int lockTool = atoi(argv[2]);

	if (lockTool != 0 && lockTool != 1)
	{
		return 1;
	}
	CBank* bank = new CBank(lockTool);
	for (int i = 0; i < atoi(argv[1]); i++)
	{
		bank->CreateClient();
	}

	// TODO: WaitForMultipleObjects
	std::string command = "";
	while (true)
	{
		std::cin >> command;
		if (command == "exit" || command == "quit")
		{
			break;
		}
	}

	int totalBalanceOfClients = 0;
	int clientBalance = 0;

	for (CBankClient client : bank->GetClients())
	{
		clientBalance = bank->GetClientBalance(client);
		std::cout << "Client: " << client.GetId() << " balance: " << clientBalance << std::endl;
		totalBalanceOfClients += clientBalance;
	}

	std::cout << "Balance of all clients: " << totalBalanceOfClients << std::endl;
	std::cout << "Bank balance: " << bank->GetTotalBalance() << std::endl;

    return 0;
}