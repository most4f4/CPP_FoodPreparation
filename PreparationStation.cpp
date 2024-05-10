#include "PreparationStation.h"

namespace stdd {

	std::deque<FoodOrder> g_pending{};
	std::deque<FoodOrder> g_completed{};
	std::deque<FoodOrder> g_incomplete{};

	// Custom constructor for PreparationStation, initializing it with a string
	PreparationStation::PreparationStation(const std::string& str): FoodStation(str) {}

	// Fill function fills the order at the front of the queue, if any
	void PreparationStation::fill(std::ostream& os) {
		// Checks if there are FoodOrders in the queue
		if (!m_orders.empty()) {
			// Fill the order at the front of the queue
			m_orders.front().fillItem(*this, os);
		}
	}

	// Attempt to move order to the next station or completion queue
	bool PreparationStation::attemptToMoveOrder() {

		bool result = false;

		// Checks if there are FoodOrders in the queue
		if (!m_orders.empty()) {

			// if the order at the front requires no more servise or cannot be filled (not enough inventory)
			if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0) {
				
				// if there is a next station
				if (m_pNextStation != nullptr) {
					// Move the order to the next station
					m_pNextStation->m_orders.push_back(std::move(m_orders.front()));
				}
				else {
					if (m_orders.front().isOrderFilled()) {
						// Move the order to the g_completed deque if it is completed
						g_completed.push_back(std::move(m_orders.front()));
					}
					else {
						// Move the order to the g_incomplete deque if it is completed
						g_incomplete.push_back(std::move(m_orders.front()));
					}
				}
				// Order moved successfully
				result = true;
				// Remove the order from this station's queue
				m_orders.pop_front();
			}
		}
		return result;
	}

	// Set the next station in the assembly line
	void PreparationStation::setNextStation(PreparationStation* station) {
		m_pNextStation = station; 
	}

	// Get the address of the next station
	PreparationStation* PreparationStation::getNextStation() const {
		return m_pNextStation;
	}

	// Display the name of the item and the next station's name
	void PreparationStation::display(std::ostream& os) const {
		// Checks if there is a next station
		if (m_pNextStation != nullptr) {
			os << getItemName() << " --> " << m_pNextStation->getItemName() << std::endl;
		}
		else {
			os << getItemName() << " --> End of Line" << std::endl;
		}
	}

	// Operator+= adds a new order to the back of the queue
	PreparationStation& PreparationStation::operator+=(FoodOrder&& newOrder) {
		// Add the newOrder to the back of the queue using move semantics
		m_orders.push_back(std::move(newOrder));
		return *this;
	}

} // !namespace_stdd

