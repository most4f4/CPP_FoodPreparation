#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FoodStation.h"
#include "FoodOrder.h"
#include "Utilities.h"


template<typename T>
static void loadFromFile(const char*, std::vector<T>&);

int main(int argc, char** argv)
{
	std::cout << "Command Line: " << argv[0];
	for (int i = 1; i < argc; ++i)
		std::cout << " " << argv[i];
	std::cout << std::endl << std::endl;
	if (argc < 4) {
		std::cerr << "ERROR: Insufficient number of arguments\n";
		std::exit(1);
	}

	std::vector<stdd::FoodStation>       theStations;
	std::vector<stdd::FoodOrder> theOrders;

	{
		// Milestone 1
		try
		{
			stdd::Utilities::setDelimiter(',');
			::loadFromFile<stdd::FoodStation>(argv[1], theStations);
			stdd::Utilities::setDelimiter('|');
			::loadFromFile<stdd::FoodStation>(argv[2], theStations);
		}
		catch (const std::string & err)
		{
			std::cerr << err << '\n';
			std::exit(2);
		}

		std::cout << "========================================" << std::endl;
		std::cout << "=         Stations (summary)           =" << std::endl;
		std::cout << "========================================" << std::endl;
		for (const auto& station : theStations)
			station.display(std::cout, false);
		std::cout << std::endl << std::endl;

		std::cout << "========================================" << std::endl;
		std::cout << "=          Stations (full)             =" << std::endl;
		std::cout << "========================================" << std::endl;
		for (const auto& station : theStations)
			station.display(std::cout, true);
		std::cout << std::endl << std::endl;

		//Select an object and verify all the functionality it working
		std::cout << "========================================" << std::endl;
		std::cout << "=          Manual Validation           =" << std::endl;
		std::cout << "========================================" << std::endl;
		std::cout << "getItemName(): " << theStations[0].getItemName() << std::endl;
		std::cout << "getNextSerialNumber(): " << theStations[0].getNextSerialNumber() << std::endl;
		std::cout << "getNextSerialNumber(): " << theStations[0].getNextSerialNumber() << std::endl;
		std::cout << "getQuantity(): " << theStations[0].getQuantity() << std::endl;
		theStations[0].updateQuantity();
		std::cout << "getQuantity(): " << theStations[0].getQuantity() << std::endl;
		std::cout << std::endl << std::endl;

		std::cout << "========================================" << std::endl;
		std::cout << "=              Utilities               =" << std::endl;
		std::cout << "========================================" << std::endl;
		// create & initialize an array of input data
		const struct { char delim; std::string data; } input[]
		{
			{ 'a', "a"},
			{ 'b', "a" },
			{ 'l', "Hello"},
			{ ',', "apple,orange,banana,kiwi,strawberry,yellow watermellon" },
			{ '|', "Gengar|Arcanine|Bulbasaur|Blaziken|C h a r i z a r d|Umbreon|Lucario|Eevee"}
		};

		for (const auto& item : input)
		{
			stdd::Utilities::setDelimiter(item.delim);
			stdd::Utilities util;
			bool more = true; // if there are more tokens in the input string
			size_t pos = 0u; // position of the next token in the input string
			std::cout << "Data: [" << item.data << "]    Delimiter: [" << item.delim << "]\n";
			while (more)
			{
				try
				{
					auto token = util.extractToken(item.data, pos, more);
					std::cout << "   Token: [" << token << "] [" << util.getFieldWidth() << "]\n";
				}
				catch (...) { std::cout << "   ERROR: No token.\n"; }
			}
		}
	}

	{
		// Milestone 2
		::loadFromFile<stdd::FoodOrder>(argv[3], theOrders);

		std::cout << "========================================" << std::endl;
		std::cout << "=                Orders                =" << std::endl;
		std::cout << "========================================" << std::endl;
		for (const auto& order : theOrders)
			order.display(std::cout);
		std::cout << std::endl << std::endl;

		//Select an object and verify all the functionality it working
		std::cout << "========================================" << std::endl;
		std::cout << "=          Manual Validation           =" << std::endl;
		std::cout << "========================================" << std::endl;
		std::cout << "CustomerOrders::display(): "; // Test #1
		theOrders[theOrders.size() - 1].display(std::cout);
		std::cout << std::endl;

		try
		{
			// copy constructor
			std::cout << "CustomerOrders::CustomerOrders(&): "; // Test #2
			stdd::FoodOrder anOrder(theOrders[0]);
		}
		catch (...)
		{
			std::cout << "----> ERROR: Cannot make copies.";
			std::cout << std::endl << std::endl;
		}

		// move constructor
		std::cout << "CustomerOrders::CustomerOrders(&&): "; // Test #3
		stdd::FoodOrder tmp(std::move(theOrders[theOrders.size() - 1]));
		theOrders.pop_back();
		tmp.display(std::cout);
		std::cout << std::endl;

		std::cout << "CustomerOrders::CustomerOrders(string): "; // Test #4
		std::string strRecord = "Chloe/Flight PC/CPU/GPU/Power Supply";
		stdd::Utilities::setDelimiter('/');
		stdd::FoodOrder tmp2(strRecord);
		tmp2.display(std::cout);
		std::cout << std::endl;

		std::cout << "CustomerOrders::operator=(&&): "; // Test #5
		tmp2 = std::move(theOrders[theOrders.size() - 1]);
		theOrders.pop_back();
		tmp2.display(std::cout);
		std::cout << std::endl;

		std::cout << "CustomerOrders::fillItem()" << std::endl; // Test #6
		std::cout << "isOrderFilled(): "
		          << (tmp2.isOrderFilled() ? "FILLED" : "MISSING")
		          << std::endl;

		tmp2.fillItem(theStations[0], std::cout);
		std::cout << "isItemFilled(\"CPU\"): "
			      << (tmp2.isItemFilled("CPU") ? "FILLED" : "MISSING")
		          << std::endl;

		std::cout << "isOrderFilled(): "
		          << (tmp2.isOrderFilled() ? "FILLED" : "MISSING")
		          << std::endl;

		for (size_t i = 0u; i < theStations.size(); ++i)
			tmp2.fillItem(theStations[i], std::cout);

		std::cout << "isOrderFilled(): "
		          << (tmp2.isOrderFilled() ? "FILLED" : "MISSING")
		          << std::endl;
	}
	return 0;
}

template<typename T>
static void loadFromFile(const char* filename, std::vector<T>& theCollection)
{
	std::ifstream file(filename);
	if (!file)
		throw std::string("Unable to open [") + filename + "] file.";

	std::string record;
	while (!file.eof())
	{
		std::getline(file, record);
		T elem(record);
		theCollection.push_back(std::move(elem));
	}

	file.close();
}
