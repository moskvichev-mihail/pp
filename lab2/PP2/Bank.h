#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <mutex>

#include "BankClient.h"
#include "stdafx.h"

class CBank
{
public:
	CBank(int lockTool);
	CBankClient* CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);
	vector<CBankClient> GetClients();
	int GetTotalBalance();
	void SetClientBalance(CBankClient client, int value);
	int GetClientBalance(CBankClient client);

private:
	std::vector<CBankClient> m_clients;
	int m_totalBalance;

	int GetTotalBalance();
	void SetTotalBalance(int value);
	void SomeLongOperations();

	void ToLockSection();
	void ToUnlockSection();
	map<int, int> m_clientAndBalance;

	LockTool m_lock_tool;

	CRITICAL_SECTION m_criticalSection;
	mutex m_mutex;
};