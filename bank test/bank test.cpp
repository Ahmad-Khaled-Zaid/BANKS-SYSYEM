//***************************************************************
//                   HEADER FILE USED IN PROJECT
//***************************************************************
#define NOMINMAX

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cctype>
#include<cstring>
#include <conio.h> // for _getch() function
#include <windows.h>



//***************************************************************
//                   CLASS USED IN PROJECT
//***************************************************************

class Account {
private:
	int accountNumber;
	std::string fName;
	std::string sName;
	std::string tName;
	std::string lName;
	int balance;
	std::string type;
	int accounts_counter = 0;

public:
	friend void write_account(Account);
	friend void display(int);
	void create_account();
	void show_account() const;
	void updateAccount(int, int, int);
	void depo(int);
	void draw(int);
	void print_all_accounts();
	void adjust(int);
	bool Unique(int);
	int count_accounts();
	std::string pass_word{};


}; //END OF ACCOUNT CLASS 

bool checker = false;
std::string converter;
char alphapet[27] = { 'A','B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W','X','Y','Z' };



//***************************************************************
//                   FUCNTIONS DECLARATIONS
//***************************************************************
std::string upperCase(std::string& name);
void checkName(std::string&, int, std::string);
int check_ID(int);
void mainMenu();
void display(int);
void deposite_darw(int, int);
void delete_account(int);
void modify_account(int);
void print_accounts();
//char check_type(char);
std::string check_type(std::string);
bool match(int);
int check_operations_input(int);
std::string password();
bool _is_Number(std::string);
bool _is_CAPITAL(std::string);
bool _is_special(std::string);
bool _is_small(std::string);
void print_massege(int, std::string, std::string, std::string, std::string);
std::string enctyptPass();

//***************************************************************
//                  MEMBERS FUNCTIONS DEFENITIONS
//***************************************************************
void Account::create_account() {
	std::cout << "Enter Account Number (9 digits) : ";
	accountNumber = check_ID(accountNumber);
	system("cls");

	print_massege(accountNumber, "", "", "", "");
	std::cout << "Enter The First Name: ";
	checkName(fName, accountNumber, "First");
	system("cls");
	print_massege(accountNumber, fName, "", "", "");

	std::cout << "Enter The Second Name : ";
	checkName(sName, accountNumber, "Second");
	system("cls");
	print_massege(accountNumber, fName, sName, "", "");
	std::cout << "Enter The Third Name : ";
	checkName(tName, accountNumber, "Third");
	system("cls");
	print_massege(accountNumber, fName, sName, tName, "");

	std::cout << "Enter The Last Name : ";
	checkName(lName, accountNumber, "Last");
	system("cls");
	print_massege(accountNumber, fName, sName, tName, lName);
	std::cout << "Enter the account Type (C/S) : ";
	std::cin >> type;
	type = check_type(upperCase(type));
	system("cls");
	print_massege(accountNumber, fName, sName, tName, lName);
	std::cout << "Account Type : " << type << std::endl;

	std::cout << "Enter the initial deposite amount : ";
	std::cin >> balance;
	system("cls");
	print_massege(accountNumber, fName, sName, tName, lName);
	std::cout << "Account Type : " << type << std::endl;
	std::cout << "Account Balance : " << balance << std::endl;
	std::cout << "Enter password : ";
	pass_word = password();
	std::cout << "\n\nAccount is being created...please wait";
	Sleep(1);
	std::cout << "\n\nAccount Created ...";
}


void Account::depo(int deposite) {
	balance += deposite;
	std::cout << "Your New balance is " << balance << std::endl;
	std::cout << "\n\nEnter -> Main Menu" << std::endl;
}

void Account::draw(int draw) {
	if (balance - draw < 0) {
		std::cout << "Insufficient Balance" << std::endl;
	}
	else {
		balance -= draw;
		std::cout << "Your New balance is " << balance << std::endl;
	}

	std::cout << "\n\nEnter -> Main Menu" << std::endl;
}




void Account::updateAccount(int operation, int Account_Number, int Case) {
	std::fstream inFile;
	std::fstream outFile;
	bool fileStatues = true;
	char decision = 'Y';
	inFile.open("account.txt", std::ios::in);
	outFile.open("newAccount.txt", std::ios::out);
	if (!inFile.is_open() || !outFile.is_open())
	{
		std::cout << "File Couldn't Be Open , Please Check File Status" << std::endl;

		fileStatues = false;
	}
	if (fileStatues)
	{
		while (inFile >> accountNumber >> fName >> sName >> tName >> lName >> type >> balance >> pass_word)
		{
			if (accountNumber == Account_Number) {
				switch (Case)
				{
				case 1:
					depo(operation);
					break;
				case 2:
					draw(operation);
					break;
				case 3:
					std::cout << " \n\n Are You sure You Want To Close Your Account?(Press y if you're sure) :  ";
					std::cin >> decision;
					decision = tolower(decision);
					if (decision == 'y') {
						std::cout << "\n\nAccount " << Account_Number << " Has Been Deleted..." << std::endl;
						continue;
					}
					else {
						std::cout << "\n\n Operation Canceled..." << std::endl;
						std::cout << "\n\n Enter-> Main Menu..." << std::endl;
						break;
					}

					break;
				case 4:
					adjust(accountNumber);
					break;

				default:
					break;
				}
			}

			outFile << accountNumber << " " << fName << " " << sName << " " << tName << " " << lName << " " << type << " " << balance << " " << pass_word << std::endl;

		}
		inFile.close();
		outFile.close();
		outFile.open("newAccount.txt", std::ios::in);
		inFile.open("account.txt", std::ios::out);
		while (outFile >> accountNumber >> fName >> sName >> tName >> lName >> type >> balance >> pass_word)
		{
			inFile << accountNumber << " " << fName << " " << sName << " " << tName << " " << lName << " " << type << " " << balance << " " << pass_word << std::endl;
		}
	}
	inFile.close();
	outFile.close();
}


void Account::adjust(int account_Number) {
	int change = 0;
	int number = 0;
	std::string agree = "y";
	std::string temName;
	std::cout << "1. Account Number" << std::endl;
	std::cout << "2. First Name" << std::endl;
	std::cout << "3. Second Name" << std::endl;
	std::cout << "4. Third Name" << std::endl;
	std::cout << "5. Last Name" << std::endl;
	std::cout << "6. Account Type" << std::endl;
	std::cout << "What Info You Want to change? : ";
	std::cin >> change;
	switch (change)
	{
	case 1:
		std::cout << "Enter New Account Number : ";
		accountNumber = check_ID(account_Number);
		std::cout << "Your Account Number Has Been Changed" << std::endl;
		break;
	case 2:
		temName = fName;
		std::cout << "Enter New First Name : ";
		checkName(fName, account_Number, "First");
		std::cout << "Are You sure You Want to change The First Name from " << temName << " To " << fName << " ? (Press y If you are Agree) : ";
		std::cin >> agree;
		upperCase(agree);
		if (agree == "Y") {
			std::cout << "First Name has been changed..." << std::endl;
		}
		else {
			fName = temName;
			std::cout << "Operation Canceled..." << std::endl;
		}
		break;
	case 3:
		std::cout << "Enter New Second Name : ";
		temName = sName;

		checkName(sName, account_Number, "Second");
		std::cout << "Are You sure You Want to change The Second Name from " << temName << " To " << sName << " ? (Press y If you are Agree) : ";
		std::cin >> agree;
		upperCase(agree);
		if (agree == "Y") {
			std::cout << "Second Name has been changed..." << std::endl;
		}
		else {
			sName = temName;
			std::cout << "Operation Canceled..." << std::endl;
		}
		break;
	case 4:
		std::cout << "Enter New Third Name : ";
		temName = tName;

		checkName(tName, account_Number, "Third");
		std::cout << "Are You sure You Want to change The Third Name from " << temName << " To " << tName << " ? (Press y If you are Agree) : ";
		std::cin >> agree;
		upperCase(agree);
		if (agree == "Y") {
			std::cout << "Last Name has been changed..." << std::endl;
		}
		else {
			tName = temName;
			std::cout << "Operation Canceled..." << std::endl;
		}

		break;

	case 5:
		std::cout << "Enter New Last Name : ";
		temName = lName;

		checkName(lName, account_Number, "Last");
		std::cout << "Are You sure You Want to change The Last Name from " << temName << " To " << lName << " ? (Press y If you are Agree) : ";
		std::cin >> agree;
		upperCase(agree);
		if (agree == "Y") {
			std::cout << "Last Name has been changed..." << std::endl;
		}
		else {
			lName = temName;
			std::cout << "Operation Canceled..." << std::endl;
		}
		break;
	case 6:
		std::cout << "Enter New Account Type : ";
		std::cin >> type;
		break;
	default:
		break;
	}
}

void Account::print_all_accounts() {
	std::cout << "showing accounts in progress...please wait" << std::endl;
	Sleep(1500);
	system("CLS");
	std::cout << "Number Of Account registered is " << count_accounts() << std::endl;

	std::ifstream Read_Accounts("account.txt", std::ios::in);
	while (Read_Accounts >> accountNumber >> fName >> sName >> tName >> lName >> type >> balance >> pass_word)
	{
		show_account();
	}
	std::cout << "\n\nEnter -> Main Menu...";

}

bool Account::Unique(int Account_Number) {
	count_accounts();
	int number = 0;
	std::ifstream Records;
	Records.open("account.txt", std::ios::in);
	if (accounts_counter == 0) {
		return false;
	}
	else {
		while (Records >> accountNumber >> fName >> sName >> tName >> lName >> type >> balance >> pass_word) {
			number++;
			if (accountNumber == Account_Number) {
				Records.close();
				return true;
			}
			else {
				if (number == accounts_counter) {
					Records.close();
					return false;
				}

			}
		}
	}

}


int Account::count_accounts() {
	accounts_counter = 0;
	std::ifstream counterObject("account.txt", std::ios::in);
	while (counterObject >> accountNumber >> fName >> sName >> tName >> lName >> type >> balance >> pass_word) {
		accounts_counter++;
	}
	counterObject.close();
	return accounts_counter;
}




int main() {
	Account ac;
	int choice;
	int Account_Number = 0;
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
			deposite_darw(1, check_operations_input(Account_Number));
			break;

		case 3:
			std::cout << "Enter Account Number : ";
			deposite_darw(2, check_operations_input(Account_Number));
			break;

		case 4:
			std::cout << "Enter Account Number: ";
			display(check_operations_input(Account_Number));
			break;

		case 5:
			print_accounts();
			break;

		case 6:
			std::cout << "Enter Account Number : ";
			delete_account(check_operations_input(Account_Number));
			break;

		case 7:
			std::cout << "Enter Account Number : ";
			modify_account(check_operations_input(Account_Number));
			break;

		case 8:
			std::cout << "\n\n\n\n\n\n\n\n\t\t\tTHANK YOU FOR USE OUT SERVIES...PRESS ENTER TO CLOSE THE PROGRAM";
			std::cin.get();
			std::cin.ignore();
			return 0;
			break;

		default:
			if (std::cin.fail()) {

			}
		}
		std::cin.get();
		std::cin.ignore();
	} while (choice != '8');
}






//***************************************************************
//              FUCNTION TO CREATE NEW ACCOUNT
//***************************************************************s

void write_account(Account ac) {
	std::ofstream outFile("account.txt", std::ios::app);
	ac.create_account();
	outFile << ac.accountNumber << " " << ac.fName << " " << ac.sName << " " << ac.tName << " " << ac.lName << " " << ac.type << " " << ac.balance << " " << ac.pass_word << std::endl;
	outFile.close();
}



//***************************************************************
//          FUCNTION TO PRESENT THE BANK SERVIES  
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
	std::cout << "\n\n\tSelect Your Option <1-8> ";
}


//***************************************************************
//        FUCNTION TO DISPLAY ACCOUNT DETAILS  
//***************************************************************

void display(int Account_Number) {
	Account ac;
	std::ifstream displayObject("account.txt", std::ios::in);
	if (!displayObject) {
		std::cout << "File Couldn't Be Open .. Press Any Key" << std::endl;
	}

	while (displayObject >> ac.accountNumber >> ac.fName >> ac.sName >> ac.tName >> ac.lName >> ac.type >> ac.balance >> ac.pass_word) {
		if (Account_Number == ac.accountNumber) {
			checker = true;
			ac.show_account();
			displayObject.close();
			break;
		}
	}

	if (checker == false) {
		std::cout << "Account not found!..." << std::endl;

	}
}




//***************************************************************
//        FUCNTION TO CHECK THE ACCOUNT HOLDER NAME  
//***************************************************************

	// restrict users to enter only letters 
void checkName(std::string& name, int accountNumber, std::string order) {

	int counter = 0;
	std::string letter_x;

	while (true)
	{
		std::cin >> name;
		upperCase(name);
		for (int i = 0; i < name.size(); i++)
		{
			letter_x = name[i];
			if (_is_CAPITAL(letter_x)) {
				counter++;
			}
		}
		if (counter == name.size()) {
			break;
		}
		else {
			std::cout << "Invalid Input, Please Enter The " << order << " Name : ";
		}
		counter = 0;
	}

}





//***************************************************************
//        FUCNTION TO CHECK THE ACCOUNT NUMBER
//***************************************************************

// restrict users to enter only integer data type and integer length is 9 digits only
int check_ID(int accountNumber) {

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
		else if (match(accountNumber)) {
			std::cout << "You can't choose this number, Please choose anouther number : ";
			continue;
		}

		else {
			return accountNumber;
		}
	}
}


//***************************************************************
//        FUCNTION TO PRINT ACCOUNT INFO.
//***************************************************************

void Account::show_account() const {

	std::cout << "\n Account Number : " << accountNumber << std::endl;
	std::cout << " Account Name : " << fName << " " << sName << " " << tName << " " << lName << std::endl;
	std::cout << " Account Type : " << type << std::endl;
	std::cout << " Account Balance : " << balance << std::endl;
}


//***************************************************************
//    FUCNTION TO DEPOSITE AND DRAW AMOUNT TO EXIST ACCOUNT.
//***************************************************************

void deposite_darw(int option, int Account_Number) {
	Account ac;
	int deposite = 0;
	int draw = 0;

	switch (option)
	{
	case 1:
		system("cls");
		display(Account_Number);
		if (checker == true) {
			checker = false;
			std::cout << "\nEnter Deposite Amount : ";
			std::cin >> deposite;
			ac.updateAccount(deposite, Account_Number, 1);

		}

		break;

	case 2:
		system("cls");
		display(Account_Number);
		if (checker == true) {
			checker = false;
			std::cout << "\nEnter Draw Amount : ";
			std::cin >> draw;
			ac.updateAccount(draw, Account_Number, 2);
		}

		break;

	default:
		break;
	}
}


//***************************************************************
//         FUCNTION TO PRINT ALL REGISTERD ACCOUNTS
//***************************************************************

void print_accounts() {
	Account ac;
	std::ifstream Read_Accounts("account.txt", std::ios::in);
	ac.print_all_accounts();
}

//***************************************************************
//             FUCNTION TO DELETE ACCOUNT.
//***************************************************************

void delete_account(int Account_Number) {
	Account ac;

	system("cls");
	display(Account_Number);
	if (checker == true) {
		checker = false;
		ac.updateAccount(0, Account_Number, 3);

	}
}

//***************************************************************
//             FUCNTION TO MODIFY ACCOUNT.
//***************************************************************
void modify_account(int Account_Number) {
	Account ac;

	system("cls");
	display(Account_Number);
	if (checker == true) {
		checker = false;
		ac.updateAccount(0, Account_Number, 4);
	}
}


//***************************************************************
//           FUCNTION TO CONVER NAMES TO UPPER CASE.
//***************************************************************

std::string upperCase(std::string& name) {
	for (int i = 0; i < name.size(); i++)
	{
		name[i] = toupper(name[i]);
	}
	return name;

}

//***************************************************************
//           FUCNTION TO CHECK THE ACCOUNT TYPE
//***************************************************************

std::string check_type(std::string type) {

	while (type != "C" && type != "S" && type.size() != 1) {
		std::cout << "Please choose S type or C type : ";
		std::cin >> type;
		type = upperCase(type);
	}
	return type;
}
//***************************************************************
//           FUCNTION TO REGISTERED ACCOUNTS
//***************************************************************
bool match(int Account_Number) {
	Account ac;
	return ac.Unique(Account_Number);

}

//***************************************************************
//          FUCNTION TO CHECK THE INPUT TYPE 
//***************************************************************
int check_operations_input(int Account_Number) {
	while (true)
	{

		std::cin >> Account_Number;

		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return 0;
		}


		else {
			return Account_Number;
		}
	}
}

//***************************************************************
//                FUCNTION TO CREATE PASSWORD
//***************************************************************

std::string password() {
	std::string pass;
	std::string pass2;
	while (true) {
		pass = enctyptPass();
		if (pass.size() < 8) {
			std::cout << "You Should Enter 8 characters at least : ";;
			continue;
		}

		else if (!_is_CAPITAL(pass) || !_is_special(pass) || !_is_Number(pass) || !_is_small(pass)) {
			std::cout << "Password should contain at least one symbole,one CAPITAL letter, one number : ";
			continue;
		}

		std::cout << "Enter the password again : ";
		pass2 = enctyptPass();
		if (pass == pass2) {
			return pass;
		}

		else {
			std::cout << "passwords not matching \nEnter the password  : ";
			continue;
		}
	}
}

//***************************************************************
//              FUCNTION TO CHECK CAPITAL LETTERS
//***************************************************************

bool _is_CAPITAL(std::string pass) {
	for (int i = 0; i < pass.size(); i++)
	{
		for (int j = 0; j < 27; j++)
		{
			if (pass[i] == alphapet[j]) {
				return true;
			}
		}

	}
	return false;
}

//***************************************************************
//            FUCNTION TO CHECK SPECIAL CHARACTERS
//***************************************************************
bool _is_special(std::string pass) {

	char symbolesArray[33] = { '!','@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+', '`', '~', '[', ']', '{', '}', '\'','|','\\','"',':',';','/','?','>','<',',' ,'.' };
	for (int i = 0; i < pass.size(); i++)
	{
		for (int j = 0; j < 33; j++)
		{
			if (pass[i] == symbolesArray[j]) {
				return true;
			}
		}
	}
	return false;

}

//***************************************************************
//            FUCNTION TO CHECK INTEGER NUMBERS
//***************************************************************
bool _is_Number(std::string pass) {
	std::string numbersString = "0123456789";

	for (int i = 0; i < pass.size(); i++)
	{
		for (int j = 0; j < numbersString.size(); j++)
		{
			if (pass[i] == numbersString[j]) {
				return true;
			}

		}

	}
	return false;

}

//***************************************************************
//            FUCNTION TO CHECK SMALL LETTERS
//***************************************************************
bool _is_small(std::string pass) {
	std::string smallLetterString = "abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < pass.size(); i++)
	{
		for (int j = 0; j < smallLetterString.size(); j++)
		{
			if (pass[i] == smallLetterString[j]) {
				return true;
			}

		}

	}
	return false;

}


//***************************************************************
//            FUCNTION TO CHECK PRINT NAMES 
//***************************************************************
void print_massege(int accountNumber, std::string fName, std::string sName = "", std::string tName = "", std::string lName = "") {
	std::cout << "Account ID : " << accountNumber << std::endl;
	std::cout << "Name : " << fName << " " << sName << " " << tName << " " << lName << std::endl;
}

//***************************************************************
//            FUCNTION TO ENCERPTION PASSWORD
//***************************************************************
std::string enctyptPass() {
	char ch = '-';
	std::string password = "";
	std::string empty;
	while (ch != '\r')
	{
		ch = _getch();
		empty = ch;
		if (_is_CAPITAL(empty) || _is_small(empty) || _is_special(empty) || _is_Number(empty)) {
			password = password + ch;
			std::cout << "*";

		}
		else continue;

	}
	std::cout << std::endl;
	return password;
}