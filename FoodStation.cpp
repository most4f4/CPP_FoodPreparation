#include <string>
#include <iomanip>
#include "FoodStation.h"

namespace stdd {

	// Static member initialization
	size_t FoodStation::m_widthField = 0;
	size_t FoodStation::id_generator = 0;

	// Constructor that initializes a station object from a string containing station information
	FoodStation::FoodStation(const std::string& str) {
		Utilities  ut;
		size_t nextPos = 0;
		bool more = true;
		
		try {
			// Extract station information from the string
			m_name = ut.extractToken(str, nextPos, more);
			std::string serialStr = ut.extractToken(str, nextPos, more);
			m_serial = std::stoul(serialStr);
			std::string quantityStr = ut.extractToken(str, nextPos, more);
			m_quantity = std::stoul(quantityStr);

			// Update maximum width field if necessary
			if (ut.getFieldWidth() > FoodStation::m_widthField) {
				FoodStation::m_widthField = ut.getFieldWidth();
			}
			m_desc = ut.extractToken(str, nextPos, more);
			m_id = ++id_generator; // Assign a unique ID to the station
		} 
		catch (std::exception& e) {
			std::cerr << e.what() << std::endl; // Error handling
		}
	}

	// Returns the name of the station
	const std::string& FoodStation::getItemName() const {
		return m_name;
	}

	// Returns the next available serial number for the station
	size_t FoodStation::getNextSerialNumber() {
		return m_serial++;
	}

	// Returns the quantity of items at the station
	size_t FoodStation::getQuantity() const {
		return m_quantity;
	}

	// Decrements the quantity of items at the station
	void FoodStation::updateQuantity() {
		if (m_quantity > 0) m_quantity--;
	}

	// Displays information about the station
	void FoodStation::display(std::ostream& os, bool full) const {
		os << std::right << std::setw(3) << std::setfill('0') << m_id << " | " 
			<< std::left << std::setw(m_widthField + 1) << std::setfill(' ') << m_name << "| " 
			<< std::right << std::setfill('0') << std::setw(6) << m_serial 
			<< std::setfill(' ') << std::left << " | ";

		// Display full information if specified
		if (full) {
			os << std::setw(4) << std::right << m_quantity
				<< " | " << std::left << m_desc;
		}

		os << std::endl;

	}

} // !namespace_stdd
