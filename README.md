# C-_FoodPreparation


### `Utilities` Module

- The `Utilities` module supports the parsing of input files, which contain information used to setup and configure the preparation line. Parsing string data from input files into tokens is performed uniformly for all objects within the simulation system.  The `Utilities` type provides the basic functionality required for all objects in the system.

The `Utilities` class has the following structure:

***Instance Variable***

-  `m_widthField` -- specifies the length of the token extracted; used for display purposes; default value is `1`.

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


### `FoodStation` Module

A `FoodStation` object manages a single station on the preparation line. Each station handles a specific item for filling customer orders.

The `FoodStation` class has the following structure:

***Instance Variables***

- the id of the station (integer)
- the name of the food handled by the station (string)
- the description of the station (string)
- the next serial number to be assigned to a food package at this station (non-negative integer)
- the number of food packages currently in stock (non-negative integer)

***Class Variables***

- `m_widthField` -- the maximum number of characters required to print to the screen the *item name* for any object of type `Station`.  Initial value is 0.
- `id_generator` -- a variable used to generate IDs for new instances of type `Station`. Every time a new instance is created, the current value of the `id_generator` is stored in that instance, and `id_generator` is incremented.  Initial value is 0.


***Public Functions***

-  custom 1-argument constructor
    - upon instantiation, a `FoodStation` object receives a reference to an unmodifiable `std::string`.  This string contains a single record (one line) that has been retrieved from the input file specified by the user.
    - this constructor uses a `Utilities` object (defined locally) to extract each token from the record and populates the `Station` object accordingly.
    - this constructor assumes that the string contains 4 fields separated by the delimiter, in the following order:
        - name of the food
        - starting serial number
        - quantity in stock
        - description
    - the token delimiter is a single character, specified by the client and previously stored into the `Utilities` class of objects.
    - this constructor extracts *name*, *starting serial number*, and *quantity* from the string first
    - before extracting *description*, it updates `Station::m_widthField` to the maximum value of `Station::m_widthField` and `Utilities::m_widthField`.
        - the `display(...)` member function uses this field width to align the output across all the records retrieved from the file.

-  `const std::string& getItemName() const` - returns the name of the current `Station` object
-  `size_t getNextSerialNumber()` – returns the next serial number to be used on the assembly line and increments `m_serialNumber`
-  `size_t getQuantity() const` – returns the remaining quantity of items in the `Station` object
-  `void updateQuantity()` – subtracts 1 from the available quantity; should not drop below 0.
-  `void display(std::ostream& os, bool full) const` -- inserts information about the current object into stream `os`.
    - if the second parameter is `false`, this function inserts only the ID, name, and serial number in the format: `ID | NAME | SERIAL | `
    - if the second parameter if `true`, this function inserts the information in the following format: `ID | NAME | SERIAL | QUANTITY | DESCRIPTION`
    - the `ID` field uses 3 characters, the `NAME` field uses `m_widthField` characters, the `QUANTITY` field uses 4 characters, the `SERIAL` field uses 6 characters; the `DESCRIPTION` has no formatting options (see the sample output for other formatting options)
    - this function terminates the printed message with an endline


