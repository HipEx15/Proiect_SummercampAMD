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

enum states {
	homescreen,
	login,
	reg,
	clientMenu,
	adminMenu,
	filtersMenu
};

int main(void)
{
	std::vector<Inventory*> temp = inventory;

	vector<User> users = initiateMembers("Register.txt", (string)" ");
	vector<Inventory*> inventory = ReadInventory("Inventory.txt", (string)" ");

	unsigned short int optionMenu, optionReg, optionLog, optionAdmin, optionClient, optionFilters;
	unsigned int t = 0;

	string itemtoRemove;
	string clientRoletochange;

	states state = homescreen;

	vector<string> userData;
	string Filename = "";


	int isValid;
	roleType role = client;
	Client user;
	Administrator admin;

	do {
		system("cls");
		//homescreen
		if (state == homescreen) {
			Menu();
			cin >> optionMenu;
			switch (optionMenu) {
			case 1:
				state = login;
				break;
			case 2:
				state = reg;
				break;
			case 3:
				flag = 1;
				break;
			}
		}
		else
			//login
			if (t > 2)
			{
				cin.get();
				cout << "Invalid username or password. Press enter to continue.";
				cin.get();
				state = homescreen;
				t = 0;
			}
			else if (state == login) {
				LoginMenu();
				userData = readUserData();

				//check validity of user data
				isValid = 0;
				for (User u : users)
				{
					if (u.getUsername() == userData[0] && u.getPassword() == userData[1])
					{
						isValid = 1;
						role = u.getRole();
						if (role == client)
						{
							user = Client(u.getID(), u.getUsername(), u.getPassword(), u.getRole());
						}
						else if (role == administrator)
						{
							admin = Administrator(u.getID(), u.getUsername(), u.getPassword(), u.getRole());
						}
					}
				}

				if (isValid == 1)
				{
					if (role == client)
						state = clientMenu;
					else
						state = adminMenu;
				}
				else
				{
					t++;
				}

			}
			else
				//register
				if (state == reg) {
					if (users.size() == 0) {
						RegisterMenuEmpty();
						userData = readUserData();
						ofstream reg("Register.txt", ios::app);
						Administrator admin(1, userData[0], userData[1], administrator);
						users.push_back(admin);
						reg << admin.getRole() << " " << admin.getNumberId() << " " << admin.getUsername() << " " << admin.getPassword() << "\n";
						reg.close();
					}
					else
					{
						RegisterMenu();
						cin >> optionReg;
						if (optionReg == 1)
						{
							system("cls");
							RegisterClientMenu();
							userData = readUserData();
							isValid = 0;
							for (User u : users)
							{

								if (u.getUsername() == userData[0])
								{
									isValid = 1;
									break;
								}
							}

							if (isValid)
								cout << "Invalid username or password";
							else
							{
								ofstream reg("Register.txt", ios::app);
								Client customer(users[users.size() - 1].getID() + 1, userData[0], userData[1], client);
								users.push_back(customer);
								reg << customer.getRole() << " " << customer.getNumberId() << " " << customer.getUsername() << " " << customer.getPassword() << "\n";
								reg.close();

							}
						}
						else if (optionReg == 2)
						{
							RegisterAdminMenu();
							userData = readUserData();
							isValid = 0;
							for (User u : users)
							{
								if (u.getUsername() == userData[0])
								{
									isValid = 1;
									break;
								}
							}

							if (isValid)
								cout << "Invalid username or password";
							else
							{
								ofstream reg("Register.txt", ios::app);
								Administrator admin(users[users.size() - 1].getID() + 1, userData[0], userData[1], administrator);
								users.push_back(admin);
								reg << admin.getRole() << " " << admin.getNumberId() << " " << admin.getUsername() << " " << admin.getPassword() << "\n";
								reg.close();

							}
						}

					}

					if (isValid == 0)
						state = homescreen;

				}
				else
					//client
					if (state == clientMenu) {
						ClientMenu();
						cin >> optionClient;
						Filename = "Basket" + user.getUsername() + ".txt";
						string name;
						Type type;

						switch (optionClient) {
						case 0:
							state = homescreen;
							break;
						case 1:
						{
							system("cls");
							type = whichType();
							cout << "\nName of product: ";
							cin >> name;
							cin.get();
							ofstream out("Basket" + user.getUsername() + ".txt", ios::app);

							user.addItem("Inventory.txt", Filename.c_str(), name);
							temp = ReadInventory(Filename.c_str(), (string)" ");
							out.close();
							user.setBasket(temp);
							break;
						}
						case 2:
						{
							system("cls");
							cout << "\nThe list of items in basket: \n";
							for (auto i : user.getBasket())
								i->Print();
							std::cout << "\nEnter item name to remove: ";
							cin >> itemtoRemove;
							user.removeItem(itemtoRemove, Filename.c_str());
							user.setBasket(ReadInventory(Filename.c_str(), (string)" "));
							break;
							break;
						}
						case 3:
						{
							system("cls");
							temp = ReadInventory(Filename.c_str(), (string)" ");
							user.setBasket(temp);
							cout << "\nThe list of items in basket: \n";
							user.printBasket();
							cin.get();
							cout << "\nPress enter to return to the menu.\n";
							cin.get();
							break;
						}
						case 4:
							system("cls");
							cout << "\nThe list of items in shop: \n";
							for (auto i : inventory)
								i->Print();
							cin.get();
							cout << "\nPress enter to return to the menu.\n";
							cin.get();
							break;
						case 5:
							system("cls");
							state = filtersMenu;
							break;
						case 6:
							system("cls");
							user.printTotalPrice();
							cin.get();
							cout << "\nPress enter to return to the menu.\n";
							cin.get();
							state = clientMenu;
							break;
						case 9:
							flag = 1;
							break;
						}
					}
					else
						//admin
						if (state == adminMenu) {
							AdminMenu();
							cin >> optionAdmin;
							switch (optionAdmin)
							{
							case 0:
								state = homescreen;
								break;
							case 9:
								flag = 1;
								break;

							case 1:
								system("cls");
								admin.addItem(inventory, "Inventory.txt");
								break;
							case 2:
								system("cls");
								cout << "\nThe list of items in shop: \n";
								for (auto i : inventory)
									i->Print();
								std::cout << "\nEnter item name to remove: ";
								cin >> itemtoRemove;
								admin.removeItem(itemtoRemove, "Inventory.txt");
								inventory = ReadInventory("Inventory.txt", (string)" ");
								break;
							case 3:
								system("cls");
								cout << "\nThe list of clients: \n";
								for (auto i : users)
									if (i.getRole() == client)
										i.print();
								std::cout << "\nEnter client name to change his role: ";
								cin >> clientRoletochange;
								admin.modifyRoleType(clientRoletochange, users, administrator);
								break;
							case 4:
								system("cls");
								cout << "\nThe list of items in shop: \n";
								for (auto i : inventory)
									i->Print();
								cin.get();
								cout << "\nPress enter to return to the menu.\n";
								cin.get();
								break;
							default:
								break;
							}
						}
						else
							if (state == filtersMenu) {
								FiltersMenu();
								user.setBasket(ReadInventory(Filename.c_str(), (string)" "));
								cin >> optionFilters;
								switch (optionFilters) {
								case 0:
									state = homescreen;
									break;

								case 1:
									user.sortByName(inventory, 1);
									cin.get();
									cout << "\nPress enter to return to the menu.\n";
									cin.get();
									break;
								case 2:
									user.sortByName(inventory, 0);
									cin.get();
									cout << "\nPress enter to return to the menu.\n";
									cin.get();
									break;

								case 3:
									user.sortByRelease(inventory, 1);
									cin.get();
									cout << "\nPress enter to return to the menu.\n";
									cin.get();
									break;
								case 4:
									user.sortByRelease(inventory, 0);
									cin.get();
									cout << "\nPress enter to return to the menu.\n";
									cin.get();
									break;

								case 5:
									user.sortByPrice(inventory, 1);
									cin.get();
									cout << "\nPress enter to return to the menu.\n";
									cin.get();
									break;
								case 6:
									user.sortByPrice(inventory, 0);
									cin.get();
									cout << "\nPress enter to return to the menu.\n";
									cin.get();
									break;

								case 8:
									state = clientMenu;
									break;

								case 9:
									flag = 1;
									break;

								}

							}

	} while (flag == 0);


	return 0;
}