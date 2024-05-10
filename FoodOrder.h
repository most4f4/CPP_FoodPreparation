#ifndef STDD_FOODORDER_H
#define STDD_FOODORDER_H

#include <iostream>
#include "FoodStation.h"

namespace stdd {

	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };
		Item(const std::string& src) : m_itemName(src) {};
	};

	class FoodOrder {
		std::string m_name{};
		std::string m_deliveryAddress{};
		size_t m_cntItem{};
		Item** m_lstItem;
		static size_t m_widthField;
	public:
		FoodOrder() = default;
		FoodOrder(const std::string& str);
		FoodOrder(const FoodOrder& src);
		FoodOrder& operator=(const FoodOrder& src) = delete;
		FoodOrder(FoodOrder&& src) noexcept;
		FoodOrder& operator=(FoodOrder&& src) noexcept;
		virtual ~FoodOrder();
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(FoodStation& station, std::ostream& os);
		void display(std::ostream& os) const;
	};

} // !namespace_stdd

#endif // !STDD_FOODORDER_H

