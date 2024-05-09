#include <iomanip>
#include "FoodOrder.h"
#include "Utilities.h"


namespace stdd {

	// Initialize static member variable
	size_t FoodOrder::m_widthField{};
	
	// Constructor to initialize a CustomerOrder object from a string
	FoodOrder::FoodOrder(const std::string& str) {
		Utilities ut;
		size_t nextPos = 0;
		bool more = true;

		// Extract customer name and product from the input string
		m_name = ut.extractToken(str, nextPos, more);
		m_deliveryAddress = ut.extractToken(str, nextPos, more);

		size_t saveThis = nextPos;
		std::string temp;

		// Count the number of items in the order
		while (more) {
			temp = ut.extractToken(str, nextPos, more);
			if (!temp.empty()) { // Only increment count if the token is not empty
				++m_cntItem;
			}
		}

		// Allocate memory for the list of items
		m_lstItem = new Item * [m_cntItem];

		// Extract and store each item in the order
		for (size_t i = 0; i < m_cntItem; ++i) {
			m_lstItem[i] = new Item(ut.extractToken(str, saveThis, more));
		}

		// Update the width field if necessary
		if (m_widthField < ut.getFieldWidth()) {
			m_widthField = ut.getFieldWidth();
		}
	}

	// Copy constructor - Throws an exception since copying is not allowed
	FoodOrder::FoodOrder(const FoodOrder& src) {
		throw std::string("ERROR: Cannot make copies.");
	}

	// Move constructor
	FoodOrder::FoodOrder(FoodOrder&& src) noexcept {
		// Move member variables from the source object
		m_name = std::move(src.m_name);
		m_deliveryAddress = std::move(src.m_deliveryAddress);
		m_cntItem = src.m_cntItem;
		m_lstItem = src.m_lstItem;
		// Reset the source object
		src.m_cntItem = 0;
		src.m_lstItem = nullptr;
	}

	// Move assignment operator
	FoodOrder& FoodOrder::operator=(FoodOrder&& src) noexcept {
		if (this != &src) {
			// Clean up existing resources
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
				m_lstItem[i] = nullptr;
			}
			delete[] m_lstItem;
			m_lstItem = nullptr;
			// Move member variables from the source object
			m_name = std::move(src.m_name);
			m_deliveryAddress = std::move(src.m_deliveryAddress);
			m_cntItem = src.m_cntItem;
			m_lstItem = src.m_lstItem;
			// Reset the source object
			src.m_cntItem = 0;
			src.m_lstItem = nullptr;

		}
		return *this;
	}

	// Destructor to release allocated memory
	FoodOrder::~FoodOrder() {
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
			m_lstItem[i] = nullptr;
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}

	// Check if all items in the order have been filled
	bool FoodOrder::isOrderFilled() const {
		bool result = true; 

		for (size_t i = 0; i < m_cntItem; ++i) {
			if (!m_lstItem[i]->m_isFilled) {
				result = false; 
				break;
			}
		}

		return result;
	}

	// Check if all items specified by itemName have been filled
	bool FoodOrder::isItemFilled(const std::string& itemName) const {
		bool result = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				if (!m_lstItem[i]->m_isFilled) {
					result = false;
					break;
				}
			}
		}
		return result;
	}

	// Checks if a specific item in the order has been filled
	void FoodOrder::fillItem(FoodStation& station, std::ostream& os) {
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName()) {
				if (!m_lstItem[i]->m_isFilled) {
					if (station.getQuantity() > 0) {
						// Fill the item and update station's inventory
						m_lstItem[i]->m_isFilled = true;
						m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
						station.updateQuantity();
						// Print message indicating the item is filled
						os << "    Filled " << this->m_name << ", "
							<< this->m_deliveryAddress << " ["
							<< m_lstItem[i]->m_itemName << "]" << std::endl;
					}
					else {
						// Print message indicating the item cannot be filled due to empty inventory
						os << "    Unable to fill " << this->m_name << ", "
							<< this->m_deliveryAddress << " ["
							<< m_lstItem[i]->m_itemName << "]" << std::endl;
					}
					break; 
				}
			}
		}
	}

	// Display the state of the current object
	void FoodOrder::display(std::ostream& os) const {
		os << this->m_name << " - " << this->m_deliveryAddress << std::endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std::setw(6) << std::setfill('0') << std::left << m_lstItem[i]->m_serialNumber << "]"
				<< " " << std::setw(this->m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName << " - ";
			if (m_lstItem[i]->m_isFilled) {
				os << "FILLED" << std::endl;
			}
			else {
				os << "TO BE FILLED" << std::endl;
			}
		}
	}

}

