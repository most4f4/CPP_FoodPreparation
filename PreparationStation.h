#ifndef STDD_PREPARATIONSTATION_H
#define STDD_PREPARATIONSTATION_H

#include <iostream>
#include <deque>
#include "FoodOrder.h"
#include "FoodStation.h"

namespace stdd {

	extern std::deque<FoodOrder> g_pending;
	extern std::deque<FoodOrder> g_completed;
	extern std::deque<FoodOrder> g_incomplete;

	class PreparationStation : public FoodStation {
		std::deque<FoodOrder> m_orders;
		PreparationStation* m_pNextStation{ nullptr };
	public:
		PreparationStation(const std::string& str);
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(PreparationStation* station);
		PreparationStation* getNextStation() const;
		void display(std::ostream& os) const;
		PreparationStation& operator+=(FoodOrder&& newOrder);
		PreparationStation(const PreparationStation& other) = delete;
		PreparationStation& operator=(const PreparationStation& other) = delete;
		PreparationStation(PreparationStation&& other) = delete;
		PreparationStation& operator=(PreparationStation&& other) = delete;
	};

} // !namespace_stdd


#endif // !STDD_PREPARATIONSTATION_H

