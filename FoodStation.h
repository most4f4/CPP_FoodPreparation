#ifndef STDD_STATION_H
#define STDD_STATION_H

#include <iostream>
#include "Utilities.h"

namespace stdd {

	class FoodStation {
		size_t m_id;				// the id of the food station
		std::string m_name;			// the name of the food handled by the station
		std::string m_desc;			// the description of the food station
		size_t m_serial;			// the next serial number to be assigned to a food package at this station
		size_t m_quantity;			// the number of food packages currently in stock
		static size_t m_widthField;
		static size_t id_generator;
	public:
		FoodStation(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};

} // !namespace_stdd

#endif // !STDD_STATION_H
