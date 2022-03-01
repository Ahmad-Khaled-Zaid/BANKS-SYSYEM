//***************************************************************
//                   HEADER FILE USED IN PROJECT
//***************************************************************

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>  

//***************************************************************
//                   CLASS USED IN PROJECT
//***************************************************************

class Account {
private:
	int accountNumber;
	std::string fName;
	std::string sName;
	std::string lName;
	int deposite;
	char type;
	friend void write_account(Account);

public:

	void create_account();

}; // CLASS ENDS HERE


const int size = 17;
const int alpSize = 27;
std::string converter;
char alphapet[alpSize] = { 'a','b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w','x','y','z' };
std::string lowerCase(std::string& name);
void checkName(std::string&, int, std::string);
void check_ID(int&);


//***************************************************************
//                  MEMBERS FUNCTIONS DEFENITIONS
//***************************************************************
void Account::create_account() {

	std::cout << "Enter Account Number (9 digits) : ";

	check_ID(accountNumber);

	system("cls");
	std::cout << "Account ID : " << accountNumber << std::endl;
	std::cout << "Enter The name of the account holder " << std::endl;

	std::cout << "Enter The First Name: ";
	checkName(fName, accountNumber, "First");
	std::cout << "Enter The Second Name : ";
	checkName(sName, accountNumber, "Second");
	std::cout << "Enter The Last Name : ";
	checkName(lName, accountNumber, "Last");

	std::cout << "Enter the account Type : ";
	std::cin >> type;
	type = toupper(type);
	std::cout << "Enter the initial deposite amount" << std::endl;
	std::cin >> deposite;
	std::cout << "\n\nAccount Created ...";

}

//***************************************************************
//                   FUCNTIONS DECLARATION
//***************************************************************

void mainMenu() {
	system("cls");
	std::cout << "\n\n\n\tMAIN MENU";
	std::cout << "\n\n\t01. CREATE NEW ACCOUNT";
	std::cout << "\n\n\t02. DEPOSIT AMOUNT";
	std::cout << "\n\n\t03. WITHDRAW AMOUNT";
	std::cout << "\n\n\t04. BALANCE ENQUIRY";
	std::cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
	std::cout << "\n\n\t06. CLOSE AN ACCOUNT";
	std::cout << "\n\n\t07. MODIFY AN ACCOUNT";
	std::cout << "\n\n\t08. EXIT";
	std::cout << "\n\n\tSelect Your Option (1-8) ";
}

void write_account(Account ac) {
	std::ofstream outFile("account.txt", std::ios::app);
	ac.create_account();
	outFile << ac.accountNumber << " " << ac.fName << " " << ac.sName << " " << ac.lName << " " << ac.type << " " << ac.deposite << std::endl;

}

std::string lowerCase(std::string& name) {
	for (int i = 0; i < name.size(); i++)
	{
		name[i] = tolower(name[i]);
	}
	return name;
}

void checkName(std::string& name, int accountNumber, std::string order) {
	while (true)
	{

		int breaks = 0;
		std::cin >> name;
		lowerCase(name);

		for (int i = 0; i < name.size(); i++)
		{
			for (int j = 0; j < alpSize; j++)
			{
				if (name[i] == alphapet[j])
				{
					break;
				}
				else if (name[i] != alphapet[j] && j == alpSize - 1) {
					system("cls");
					breaks++;
					std::cout << "Account Number : " << accountNumber << std::endl;
					std::cout << "Invalid Input , Please Enter The " << order << " Name : ";
					break;
				}


				else  continue;


			}

			if (breaks == 1) break;
		}
		if (breaks == 0) break;

	}
}

// restrict user to enter only integers data type and integer length is 9 digits only

void check_ID(int& accountNumber) {
	while (true)
	{

		std::cin >> accountNumber;
		std::stringstream ss;
		ss << accountNumber;
		ss >> converter;

		if (!std::cin)
		{

			system("cls");
			std::cout << "Invaild input,Enter Only Numbers" << std::endl;
			std::cout << "Enter Account Number :  ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			continue;
		}

		else if (converter.length() != 9) {
			system("cls");
			std::cout << "Invaild input,Please Enter 9 digits" << std::endl;
			std::cout << "Enter Account Number :  ";
			continue;
		}

		else
			break;
	}
}



int main() {
	Account ac;
	int choice = 0;
	do {
		mainMenu();
		std::cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:
			write_account(ac);
			break;

		case 2:
			break;

		case 3:
			break;

		case 4:
			break;

		case 5:
			break;

		case 6:
			break;

		case 7:
			break;

		case 8:
			break;

		default:
			break;
		}
	} while (choice != 8);
}