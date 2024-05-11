#ifndef STDD_PREPLINEMANAGER_H
#define STDD_PREPLINEMANAGER_H

#include <iostream>
#include <vector>
#include "PreparationStation.h"

namespace stdd {

	class PrepLineManager {

		// the collection of preparation stations for the current line.
		std::vector<PreparationStation*> m_activeLine;

		// the total number of FoodOrder objects
		size_t m_cntCustomerOrder{};

		// points to the first active preparation station on the current line
		PreparationStation* m_firstStation{};

	public:

		PrepLineManager(const std::string& file, const std::vector<PreparationStation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;

	};


} // !namespace_stdd

#endif // !STDD_PREPLINEMANAGER_H
