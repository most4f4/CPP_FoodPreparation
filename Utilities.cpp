#include "Utilities.h"

namespace stdd {

    // Initialize static member
    char Utilities::m_delimiter{};

    // Sets the width of the output field to the value of newWidth
	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

    // Returns the field width
	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

    // Sets the delimiter to the specified character
    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    // Returns the current delimiter character
    char Utilities::getDelimiter() {
        return m_delimiter;
    }

    /*
        Extracts tokens from a string.
        str: The string from which to extract the token.
        next_pos: The position from which to start the extraction. 
                  Will be updated to the position after the extracted token.
        more: A flag indicating if there are more tokens to extract after the current one.
        Returns: The extracted token.
        Throw a logical errorIf when the next character is the delimiter.
    */
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        std::string tok;

        // Lambda function to trim whitespace from both ends of a string
        auto trim = [](std::string& org) {
            org.erase(0, org.find_first_not_of(' '));
            org.erase(org.find_last_not_of(' ') + 1);
        };

        // If the next character is the delimiter, throw a logical error
        if (str[next_pos] == m_delimiter) {
            more = false; // end the loop
            throw std::logic_error("   ERROR: No token.\n");
        }

        // Find the next delimiter position
        size_t nextDel = str.find(m_delimiter, next_pos);

        if (nextDel != std::string::npos) {
            // Extract token from next_pos to nextDel
            tok = str.substr(next_pos, nextDel - next_pos);
            trim(tok);
            next_pos = nextDel + 1;
            more = true; // More tokens are expected

            // Update width field if necessary
            if (m_widthField < tok.size()) {
                m_widthField = tok.size();
            }
        }
        else {
            // If delimiter not found, get the token from next_pos to the end of the string
            more = false; // No more tokens after this one
            tok = str.substr(next_pos);
            trim(tok);

            // Update width field if necessary
            if (m_widthField < tok.size()) {
                m_widthField = tok.size();
            }
        }
        return tok;
    }

} // !namespace_stdd

