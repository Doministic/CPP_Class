

#include <iostream>

/*
struct BankAccount
{
	double balance;
	BankAccount(double initBalance)
	{
		balance = initBalance;
	}

	void deposit(double amount)
	{
		if (amount > 0)
		{
			balance += amount;
		}
		return;
	}

	void withdraw(double amount)
	{
		if (amount > 0 && amount <= balance)
		{
			balance -= amount;
		}
		else
		{
			std::cout << "Invalid: Not enough cash...\n";
			return;
		}
	}

	double GetBalance() const
	{
		return balance;
	}
};

int main()
{
	BankAccount account(100);
	account.balance = 1000;
	std::cout << account.GetBalance() << "\n";

	account.withdraw(1000);
	std::cout << account.GetBalance() << "\n";

	account.balance = 1000000;
	std::cout << account.GetBalance() << "\n";


	return 0;
}


class BankAccount
{
private: 
	double balance = 0;
	
protected:
	struct Card
	{
		const std::string name = "Canada Express";
		const std::string owner = "My Name";
		double number = 4012345678901245;
		int pin = 1234;
		double expiration = 10012029;
	};

public: 
	BankAccount(double initBalance)
	{
		balance = initBalance;
	}

	void deposit(double amount)
	{
		if (amount > 0)
		{
			balance += amount;
		}
		return;
	}

	void withdraw(double amount)
	{
		if (amount > 0 && amount <= balance)
		{
			balance -= amount;
		}
		else
		{
			std::cout << "Invalid: Not enough cash...\n";
			return;
		}
	}

	double GetBalance() const 
	{
		return balance;
	}
};

int main()
{
	BankAccount account(100);

	std::cout << account.GetBalance() << "\n";
	account.withdraw(50);
	std::cout << account.GetBalance() << "\n";
	account.deposit(250);
	std::cout << account.GetBalance() << "\n";
	account.withdraw(10000);
	std::cout << account.GetBalance() << "\n";

	return 0;
}
*/