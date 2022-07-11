#include <iostream>
#include <vector>
#include <fstream>

#include "Director.h"
#include "User.h"
#include "Administrator.h"
#include "Client.h"
#include "Menus.h"

using namespace std;

int flag = 0;
std::vector<Inventory*> inventory;

//// TO DO : o multime de id-uri {1,2,3,4,5,6} si sterg 3 si adaug 1 => {1,2,4,5,6,7}

int main(void)
{
	vector<User> users = initiateMembers("Register.txt", (string)" ");
	vector<Inventory*> inventory = ReadInventory("Inventory.txt", (string)" ");
	//for (User u : users)
	//	u.print();

	for (Inventory* i : inventory)
		i->Print();

	//unsigned short int optionMenu, optionReg, optionLog;

	//system("cls");
	//Menu();
	//cin >> optionMenu;
	//system("cls");

	//vector<string> userData;

	//int isValid;
	//roleType role;

	//do {
	//	if (optionMenu == 1 || optionMenu == 2
	//		|| optionMenu == 3)
	//	{
	//		switch (optionMenu)
	//		{
	//		case 1:
	//			LoginMenu();
	//			userData = readUserData();
	//			isValid = 0;
	//			for (User u : users)
	//			{

	//				if (u.getUsername() == userData[0] && u.getPassword() == userData[1])
	//				{
	//					isValid = 1;
	//					role = u.getRole();
	//					break;
	//				}
	//			}

	//			if (isValid)
	//			{
	//				if (role == client)
	//					//cout << "Welcome mr client";
	//					ClientMenu();
	//				else if (role == administrator)
	//					//cout << "Welcome mr admin";
	//					AdminMenu();
	//			}
	//			else
	//			{
	//				cout << "Invalid username or password";
	//				main();
	//			}
	//			cin.get();
	//			break;
	//			
	//		case 2:
	//			if (users.size() == 0)
	//			{
	//				system("cls");
	//				RegisterMenuEmpty();
	//				userData = readUserData();
	//				ofstream reg("Register.txt", ios::app);
	//				Administrator admin(1, userData[0], userData[1], administrator);
	//				users.push_back(admin);
	//				reg << admin.getRole() << " " << admin.getNumberId() << " " << admin.getUsername() << " " << admin.getPassword() << "\n";
	//				reg.close();
	//				
	//			}
	//			else
	//			{
	//				RegisterMenu();
	//				cin >> optionReg;
	//				if (optionReg == 1)
	//				{
	//					system("cls");
	//					RegisterClientMenu();
	//					userData = readUserData();
	//					isValid = 0;
	//					for (User u : users)
	//					{

	//						if (u.getUsername() == userData[0])
	//						{
	//							isValid = 1;
	//							break;
	//						}
	//					}

	//					if (isValid)
	//						cout << "Invalid username or password";
	//					else
	//					{
	//						ofstream reg("Register.txt", ios::app);
	//						Client customer(users[users.size() - 1].getID() + 1, userData[0], userData[1], client);
	//						users.push_back(customer);
	//						reg << customer.getRole() << " " << customer.getNumberId() << " " << customer.getUsername() << " " << customer.getPassword() << "\n";
	//						reg.close();
	//					}
	//				}
	//				else if (optionReg == 2)
	//				{
	//					system("cls");
	//					RegisterAdminMenu();
	//					userData = readUserData();
	//					isValid = 0;
	//					for (User u : users)
	//					{
	//						if (u.getUsername() == userData[0])
	//						{
	//							isValid = 1;
	//							break;
	//						}
	//					}

	//					if (isValid)
	//						cout << "Invalid username or password";
	//					else
	//					{
	//						ofstream reg("Register.txt", ios::app);
	//						Administrator admin(users[users.size() - 1].getID() + 1, userData[0], userData[1], administrator);
	//						users.push_back(admin);
	//						reg << admin.getRole() << " " << admin.getNumberId() << " " << admin.getUsername() << " " << admin.getPassword() << "\n";
	//						reg.close();
	//					}
	//				}
	//				if (optionReg == 1 || optionReg == 2)
	//				{
	//					optionMenu = 4;
	//					main();
	//				}
	//			}
	//			break;
	//		case 3:
	//			return 0;
	//			break;
	//		default:
	//			system("cls");
	//			main();
	//			break;
	//		}
	//	}
	//	else
	//	{
	//		flag = 1;
	//	}

	//} while (flag == 0);


	return 0;
}