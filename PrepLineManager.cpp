#include <fstream>
#include <string>
#include <sstream>
#include <algorithm> // for for_each
#include "PrepLineManager.h"
#include "Utilities.h"


namespace stdd {

    /*
    * this constructor receives the name of the file that identifies the active preparation stations on the 
    preparation line and the collection of preparation stations available for configuring the preparation line.

     The format of each record in the file is FOODSTATION|NEXT_FOODSTATION

     This function stores the preparation stations in the order received from the file in the m_activeLine 
     instance variable. 
     It loads the contents of the file, stores the address of the next preparation station in each element 
     of the collection, 
     identifies the first station in the preparation line and stores its address in the m_firstStation
     attribute. 
     This function also updates the attribute that holds the total number of orders in the g_pending queue.
     If something goes wrong, this constructor reports an error.
    */  
    PrepLineManager::PrepLineManager(const std::string& file, const std::vector<PreparationStation*>& stations) {
        // Create a Utilities object for token extraction
        Utilities utility;
        utility.setDelimiter('|');

        // Open the file for reading
        std::ifstream fs(file);
        if (!fs.is_open()) {
            throw std::string("Unable to open file: ") + file;
        }

        std::string line;

        // Read each line from the file
        while (std::getline(fs, line)) {

            size_t nextPos = 0;
            bool more = true;

            // Extract current preparation station name from the line
            std::string currentStationName = utility.extractToken(line, nextPos, more);

            // Define lambda expression to find the current preparation station
            auto findCurrent = [&](PreparationStation* station) {
                return station->getItemName() == currentStationName;
            };

            // Find the current preparation station in the vector of stations
            auto currentStationIt = std::find_if(stations.begin(), stations.end(), findCurrent);

            // Store the current station in the active line
            m_activeLine.push_back(*currentStationIt);

            if (more) {
                // Extract the next preparation station names from the line
                std::string nextStationName = utility.extractToken(line, nextPos, more);

                // Define lambda expression to find the next preparation station
                auto findNext = [&](PreparationStation* station) {
                    return station->getItemName() == nextStationName;
                };

                // Find the next preparation station in the vector of stations
                auto nextStationIt = std::find_if(stations.begin(), stations.end(), findNext);

                (*currentStationIt)->setNextStation(*nextStationIt);

            }
  
        }

        // Close the file
        fs.close();

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [=](PreparationStation* first_src) {
            auto start = any_of(stations.begin(), stations.end(), [=](PreparationStation* sec_src) {
                return sec_src->getNextStation() == first_src; 
            });

        if (!start)
            m_firstStation = first_src;
            });

        // Calculate the total number of orders in the g_pending queue
        m_cntCustomerOrder = g_pending.size();
	}

    void PrepLineManager::reorderStations() {
        
        // Create a temporary vector to hold the reordered stations
        std::vector<PreparationStation*> reorderedLine; 

        // Start with the first station
        PreparationStation* currentStation = m_firstStation;

        // Traverse the preparation line and append stations to reorderedLine
        while (currentStation) {

            // Add the current station to the reordered line
            reorderedLine.push_back(currentStation); 

            // Move to the next station
            currentStation = currentStation->getNextStation(); 
        }

        // Update m_activeLine with the reordered stations
        m_activeLine = reorderedLine;
    }

    bool PrepLineManager::run(std::ostream& os) {

        // Track the current iteration number
        static int iterationCount = 0; 

        // Increment the iteration count
        iterationCount++; 

        // Output the iteration count
        os << "Line Manager Iteration: " << iterationCount << std::endl; 

        // Move an order from g_pending to the first station in the line
        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        // Perform one fill operation for each station on the line
        for (auto station : m_activeLine) {
            station->fill(os);
        }

        // Attempt to move an order down the line for each station
        for (auto station : m_activeLine) {
            station->attemptToMoveOrder();
        }

        // Check if all food orders have been filled or cannot be filled
        return m_cntCustomerOrder == g_completed.size() + g_incomplete.size();

    }

    void PrepLineManager::display(std::ostream& os) const {
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](PreparationStation* ws)
            {
                ws->display(os);
            });
    }

} // !namespace_stdd

