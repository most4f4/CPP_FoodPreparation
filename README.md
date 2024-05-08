# C-_FoodPreparation


### `Utilities` Module

- The `Utilities` module supports the parsing of input files, which contain information used to setup and configure the preparation line. Parsing string data from input files into tokens is performed uniformly for all objects within the simulation system.  The `Utilities` type provides the basic functionality required for all objects in the system.

The `Utilities` class has the following structure:

***Instance Variable***

-  `m_widthField` -- specifies the length of the token extracted; used for display purposes; default value is `0`.

***Class Variable***

-  `m_delimiter` -- separates the tokens in any given `std::string` object. All `Utilities` objects in the system **share the same delimiter**.

***Member Functions***

- `void setFieldWidth(size_t newWidth)` -- sets the field width of the current object to the value of parameter `newWidth`

- `size_t getFieldWidth() const` -- returns the field width of the current object

- `std::string extractToken(const std::string& str, size_t& next_pos, bool& more)` -- extracts a token from string `str` referred to by the first parameter.

    This function:

    -  uses the delimiter to extract the next token from `str` starting at position `next_pos`.
        -  If successful, return a copy of the extracted token found (without spaces at the beginning/end), update `next_pos` with the position of the next token, and set `more` to `true` (`false` otherwise).
    -  reports an exception if a delimiter is found at `next_pos`.
    -  updates the current object's `m_widthField` data member if its current value is less than the size of the token extracted.

    - In this application, `str` represents a single line that has been read from an input file.


***Class Functions***

-  `static void setDelimiter(char newDelimiter)` -- sets the delimiter for this class to the character received
-  `static char getDelimiter()` -- returns the delimiter for this class.