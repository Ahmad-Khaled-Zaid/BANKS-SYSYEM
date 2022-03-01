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

public:
	friend void write_account(Account);
	friend void display(int Account_Number);
	void create_account();
	int return_account_number() const;
	void show_account() const;
	//int depe();

}; // CLASS ENDS HERE


const int alpSize = 27;
std::string converter;
char alphapet[alpSize] = { 'A','B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W','X','Y','Z' };

//***************************************************************
//                   FUCNTIONS DECLARATION
//***************************************************************
std::string upperCase(std::string& name);
void checkName(std::string&, int, std::string);
void check_ID(int&);
void mainMenu();
void display(int);
void deposite_darw(int, int);



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






std::string upperCase(std::string& name) {
	for (int i = 0; i < name.size(); i++)
	{
		name[i] = toupper(name[i]);
	}
	return name;
}







int main() {
	Account ac;
	int choice = 0;
	int Account_Number;
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
			std::cout << "Enter Account Number : ";
			std::cin >> Account_Number;
			deposite_darw(1, Account_Number);
			break;

		case 3:
			std::cout << "Enter Account Number : ";
			std::cin >> Account_Number;
			deposite_darw(2, Account_Number);
			break;

		case 4:
			std::cout << "Enter Account Number" << std::endl;
			std::cin >> Account_Number;
			display(Account_Number);
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






//***************************************************************
//              FUCNTION TO CREATE NEW ACCOUNT
//***************************************************************

void write_account(Account ac) {
	std::ofstream outFile("account.txt", std::ios::app);
	ac.create_account();
	outFile << ac.accountNumber << " " << ac.fName << " " << ac.sName << " " << ac.lName << " " << ac.type << " " << ac.deposite << std::endl;
	outFile.close();
}



//***************************************************************
//              FUCNTION TO PRESENT THE BANK SEVIES  
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


//***************************************************************
//        FUCNTION TO DISPLAY ACCOUNT DETAILS  
//***************************************************************

void display(int Account_Number) {
	bool checker = false;
	Account ac;
	std::ifstream displayObject("account.txt", std::ios::in);
	if (!displayObject) {
		std::cout << "File Couldn't Be Open .. Press Any Key" << std::endl;
	}

	while (displayObject >> ac.accountNumber >> ac.fName >> ac.sName >> ac.lName >> ac.type >> ac.deposite) {
		if (Account_Number == ac.accountNumber) {
			checker = true;
			ac.show_account();
		}
	}

	if (checker == false) {
		std::cout << "Account not found!..." << std::endl;

		std::cin.get();
		std::cin.ignore();
	}


}



//***************************************************************
//        FUCNTION TO CHECK THE ACCOUNT HOLDER NAME  
//***************************************************************


// restrict users to enter only letters 
void checkName(std::string& name, int accountNumber, std::string order) {
	while (true)
	{

		bool breaks = false;
		std::cin >> name;
		upperCase(name);

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
					breaks = true;
					std::cout << "Account Number : " << accountNumber << std::endl;
					std::cout << "Invalid Input , Please Enter The " << order << " Name : ";
					break;
				}


				else  continue;


			}

			if (breaks) break;
		}
		if (!breaks) break;

	}
}


//***************************************************************
//        FUCNTION TO CHECK THE ACCOUNT NUMBER
//***************************************************************




// restrict users to enter only integer data type and integer length is 9 digits only
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


//***************************************************************
//        FUCNTION TO PRINT ACCOUNT INFO.
//***************************************************************

void Account::show_account() const {
	system("cls");
	std::cout << "\n Account Number : " << accountNumber << std::endl;
	std::cout << " Account Name : " << fName << " " << sName[0] << "." << lName << std::endl;
	std::cout << " Account Type : " << type << std::endl;
	std::cout << " Account Balance : " << deposite << std::endl;
	std::cout << "\nPress Enter Key ...";

	std::cin.get();
	std::cin.ignore();
}


//***************************************************************
//        FUCNTION TO DEPOSITE AMOUNT TO EXIST ACCOUNT.
//***************************************************************

void deposite_darw(int option, int Account_Number) {
	switch (option)
	{
	case 1:
		display(Account_Number);
	case 2:

	default:
		break;
	}
}
