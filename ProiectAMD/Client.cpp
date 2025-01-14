#include "Client.h"
#include "User.h"
#include "Builder.h"
#include "Director.h"
#include <algorithm>
#include "Menus.h"
#include <fstream>

Client::Client(void) : User()
{}

Client::Client(int ID, std::string username, std::string password, roleType role) : User(username, password, role, ID)
{}

void Client::setRole(roleType role)
{
	this->role = role;
}

void Client::addItem(std::string fileName, std::string newFileName, std::string Name)
{
	std::ifstream file(fileName);
	std::ofstream newFile(newFileName, ios::app);
	std::string line;
	while (std::getline(file, line))
	{
		if (line.find(Name) != std::string::npos)
		{
			newFile << line << std::endl;
		}
	}
	file.close();
	newFile.close();
}

vector<Inventory*> ReadBasket(string filepath, string del)
{
	vector<string> tokens = readFile(filepath);

	vector<Inventory*> inventory;

	for (string token : tokens)
	{
		FinalCPU* C;
		FinalGPU* G;
		FinalAPU* A;

		BuildCPU BC;
		BuildGPU BG;
		BuildAPU BA;

		Director Dir;

		vector<string> items;

		int start = 0;
		int end = token.find(del);
		while (end != -1)
		{
			items.push_back(token.substr(start, end - start));
			start = end + del.size();
			end = token.find(del, start);
		}

		items.push_back(token.substr(start, end - start));

		if (items[1] == "CPU")
		{
			float weight = stof(items[2]);
			float height = stof(items[3]);
			unsigned short int tdp = stoi(items[4]);
			unsigned short int nms = stoi(items[5]);
			unsigned short int memory = stoi(items[7]);
			float frequency = stof(items[7]);
			float priceTag = stof(items[8]);
			string name = items[9];
			string date = items[10];

			unsigned short int cores = stoi(items[11]);
			unsigned short int threads = stoi(items[12]);
			string socket = items[13];

			Dir.setBuilder(&BC);
			C = Dir.getFC(weight, height, tdp, nms, memory, frequency, priceTag, name, date, cores, threads, socket);
			inventory.push_back(C);
		}
		else if (items[1] == "GPU")
		{
			float weight = stof(items[2]);
			float height = stof(items[3]);
			unsigned short int tdp = stoi(items[4]);
			unsigned short int nms = stoi(items[5]);
			unsigned short int memory = stoi(items[6]);
			float frequency = stof(items[7]);
			float priceTag = stof(items[8]);
			string name = items[9];
			string date = items[10];
			string resolution = items[11];
			if (items[12] == "1")
			{
				Dir.setBuilder(&BG);
				G = Dir.getFG(weight, height, tdp, nms, memory, frequency, priceTag, name, date, resolution, OpenGL);
				inventory.push_back(G);
			}
			else if (items[12] == "2")
			{
				Dir.setBuilder(&BG);
				G = Dir.getFG(weight, height, tdp, nms, memory, frequency, priceTag, name, date, resolution, DirectX);
				inventory.push_back(G);
			}
		}
		else if (items[1] == "APU")
		{
			float weight = stof(items[2]);
			float height = stof(items[3]);
			unsigned short int tdp = stoi(items[4]);
			unsigned short int nms = stoi(items[5]);
			unsigned short int memory = stoi(items[6]);
			float frequency = stof(items[7]);
			float priceTag = stof(items[8]);
			string name = items[9];
			string date = items[10];

			unsigned short int cores = stoi(items[11]);
			unsigned short int threads = stoi(items[12]);
			string socket = items[13];

			string resolution = items[14];
			if (items[15] == "1")
			{
				Dir.setBuilder(&BA);
				A = Dir.getFA(weight, height, tdp, nms, memory, frequency, priceTag, name, date, cores, threads, socket, resolution, OpenGL);
				inventory.push_back(A);
			}
			else if (items[15] == "2")
			{
				Dir.setBuilder(&BA);
				A = Dir.getFA(weight, height, tdp, nms, memory, frequency, priceTag, name, date, cores, threads, socket, resolution, OpenGL);
				inventory.push_back(A);
			}
		}
		else
		{
			cout << "Invalid items type" << endl;
		}
	}
	return inventory;
}

void Client::removeItem(std::string Name, std::string filePath)
{
	string line;
	fstream fin;
	fstream fout;

	string Filename = "Basket" + this->getUsername() + ".txt";

	fin.open(filePath, ios::in);
	fout.open("Temp.txt", ios::out | ios::app);

	vector<string> lines;
	while (getline(fin, line))
	{
		if (line.find(Name) == string::npos)
			fout << line << endl;

	}
	fout.close();
	fin.close();

	remove(Filename.c_str());
	rename("Temp.txt", Filename.c_str());
}

void Client::printBasket(void)
{
	for (auto i : this->basket)
		i->Print();
}

void Client::printTotalPrice(void) {
	float finalPrice = 0;

	for (auto i : this->basket)
		finalPrice += i->getProduct()->GetPriceTag();

	std::cout << "Price: " << finalPrice;
}

void Client::sortByName(std::vector<Inventory*>& inventory, int asc) {
	
	for (int i = 0; i < inventory.size() - 1; i++)
	{
		for (int j = i + 1; j < inventory.size(); j++) {
			Products* a1 = inventory[i]->getProduct();
			Products* a2 = inventory[j]->getProduct();


			if (asc != 0) {
				if (strcmp(a1->GetName().c_str(), a2->GetName().c_str()) > 0) {
					std::swap(inventory[i], inventory[j]);
				}
			}
			else
				if (strcmp(a1->GetName().c_str(), a2->GetName().c_str()) < 0) {
					std::swap(inventory[i], inventory[j]);
				}

		}
	}

	for (int i = 0; i < inventory.size(); i++)
		inventory[i]->Print();

}

void Client::sortByRelease(std::vector<Inventory*>& inventory, int asc) {

	for (int i = 0; i < inventory.size() - 1; i++)
		for (int j = i + 1; j < inventory.size(); j++) {
			Products* a1 = inventory[i]->getProduct();
			Products* a2 = inventory[j]->getProduct();

			if (asc != 0) {
				if (strcmp(a1->GetDate().c_str(), a2->GetDate().c_str()) > 0) {
					std::swap(inventory[i], inventory[j]);
				}
			}
			else
				if (strcmp(a1->GetDate().c_str(), a2->GetDate().c_str()) < 0) {
					std::swap(inventory[i], inventory[j]);
				}

		}

	for (int i = 0; i < inventory.size(); i++)
		inventory[i]->Print();

}

void Client::sortByPrice(std::vector<Inventory*>& inventory, int asc) {

	for (int i = 0; i < inventory.size() - 1; i++)
		for (int j = i + 1; j < inventory.size(); j++) {
			Products* a1 = inventory[i]->getProduct();
			Products* a2 = inventory[j]->getProduct();

			if (asc != 0) {
				if (a1->GetPriceTag() > a2->GetPriceTag()) {
					std::swap(inventory[i], inventory[j]);
				}
			}
			else
				if (a1->GetPriceTag() < a2->GetPriceTag()) {
					std::swap(inventory[i], inventory[j]);
				}

		}

	for (int i = 0; i < inventory.size(); i++)
		inventory[i]->Print();

}


int Client::getNumberId(void)
{
	return this->numberID;
}

std::string Client::getUsername(void)
{
	return this->username;
}

std::string Client::getPassword(void)
{
	return this->password;
}

roleType Client::getRole(void)
{
	return this->role;
}

void Client::setBasket(std::vector<Inventory*> basket)
{
	this->basket = basket;
}

std::vector<Inventory*> Client::getBasket(void)
{
	return this->basket;
}

Type whichType(void)
{
	std::string type;
	cout << "\nType: ";
	cin >> type;

	if (type == "CPU")
		return cpu;
	else if (type == "GPU")
		return gpu;
	else if (type == "APU")
		return apu;
}
