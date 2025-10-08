
#include <iostream>

int main()
{
	// Flow Control If Else If Else 
	// if ( bool expression / Logical statement ) - Always required
	// { what ever we want done }
	// else if ( bool expression )
	// { what ever we want done }
	// else
	// { what ever we want done }

	// Bool Expression Comparison Operators
	// >, <. <=, >=, ==, !=
	// Logical Operators 
	// && (and) - both conditions must be true
	// || (or) - one condition must be true
	// ! (not) - negates the condition
	
	
	float accountBalance = 150;
	float fee = 0.10;

	uint32_t feeBalance = 150;

	bool hasEnoughMoney = true;

	if (accountBalance < feeBalance) // only  enters statement when true
	{
		hasEnoughMoney = false; // sets hasEnoughMoney to false
		std::cout << "Changing hasEnoughMoney to false" << std::endl;
	}
	
	if (!hasEnoughMoney) // if hasEnoughMoney is true
	{
		std::cout << "account fee." << std::endl;
	}
	else // if hasEnoughMoney is false
	{
		std::cout << "No account fee." << std::endl;
	}
	
	if (accountBalance < feeBalance && hasEnoughMoney == false)
	{
		std::cout << "Account Balance before fee: " << accountBalance << std::endl;
		accountBalance -= accountBalance * fee;
		std::cout << "Account Balance after fee: " << accountBalance << std::endl;
	}
	else if (accountBalance == feeBalance) 
	{
		std::cout << "Account balance is nearing the fee limit." << std::endl;
	}
	else {
		std::cout << "Has Enough Money" << std::endl;
	}

	/*
	// Switch Statements: 

	char yes = 'y';
	char no = 'n';

	char choice = 'y';
	switch (choice) // expression must be some value - Reuqired 
	{
		case 'y': // required 
			std::cout << "You chose yes";
			break; // breaks out of the switch statement
		case 'n':
			std::cout << "You chose no";
			break; // breaks out of the switch statement
		default: // optional - if no case matches
			std::cout << "You chose something else";
			break; // breaks out of the switch statement
			// no break here will continue to next case
	}
	*/

	return 0;
}