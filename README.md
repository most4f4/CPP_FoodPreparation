# Food Preparation Line Management System


## Overview
The Food Preparation Line Management System is a software solution designed to streamline the process of managing food preparation orders in a kitchen or restaurant setting. The system automates the flow of food orders through various preparation stations, ensuring efficient handling and timely completion of customer orders.

The food preparation line management system consists of a series of preparation stations, each equipped with specific stock items required for food preparation. A preparation line oversees the movement of customer food orders along the line, ensuring that orders are filled at each station according to the requested items.

Each food order comprises a list of items that need to be prepared. At each station, orders are processed from a queue, with the station filling the next order in the queue if it requests items available at that station and those items are in stock.

The preparation line continuously moves food orders from station to station until all orders have been processed. If a station exhausts its stock inventory, it cannot fill any further orders. At the end of the line, orders are categorized as either completed or incomplete, depending on whether all requested items have been successfully prepared.

Once the preparation line manager has finished processing all orders, the simulator displays a list of completed orders as well as those that are incomplete due to insufficient inventory at one or more stations.

## Modules

### `Utilities` Module

- The `Utilities` module supports the parsing of input files, which contain information used to setup and configure the preparation line. Parsing string data from input files into tokens is performed uniformly for all objects within the simulation system.  The `Utilities` type provides the basic functionality required for all objects in the system.


### `FoodStation` Module

- A `FoodStation` object manages a single station on the preparation line. Each station handles a specific item for filling customer food orders.


## `FoodOrder` Module

- The `FoodOrder` module contains all the functionality for processing food orders as they move from `Station` to `Station` along the preparation line. The `Station` where a given order currently rests fills a request for one item of that station, if there is any such request. 

## `PreparationStation` Module

- The `PreparationStation` class defines the structure of an active station on the assembly line and contains all the functionality for filling food orders with station items.  Each `PreparationStation` is-a-kind-of `FoodStation`. A `PreparationStation` object manages order processing for a single `Item` on the assembly line. Since `PreparationStation` object represents a single location on the assembly line for filling customer orders with items, the object cannot be copied or moved. Once an order has reached the end of the line, it is either complete or incomplete. An order is incomplete if one or more stations had an insufficient number of items in stock to cover that order's requests.


## `PreparationLine` Module

- The `PreparationLine` module first configures the preparation line and then moves `FoodOrders` along it (from start to finish).  The `PreparationLine` object configures the `PreparationStation` objects identified by the user, and moves orders along the line one step at a time.

