#ifndef _PCH_H
#define _PCH_H

// IO Libraries
#include <iostream>     /*!< @note: Header that defines the standard input/output stream objects */
#include <iomanip>      /*!< @note: Header providing parametric manipulators */
#include <io.h>         /*!< @note: Access to declarations for the low-level I/O primitives */
#include <ostream>
#include <conio.h>

// Other Utilities
#include <stdlib.h>     /*!< @note: C Standard General Utilities Library */
#include <time.h>       /*!< @note: C Time Library */
#include <stdexcept>    /*!< @note: This header defines a set of standard exceptions that both the library and programs can use to report common errors */
#include <chrono>       /*!< @note: The elements in this header deal with time */
#include <thread>       /*!< @note: Header that declares the thread class and the this_thread namespace */
#include <fcntl.h>      /*!< @note: File control options */
#include <list>         /*!< @note: Header that defines the list container class */
#include <thread>

// Datatypes
#include <string>       /*!< @note: This header introduces string types, character traits and a set of converting functions */
#include <vector>       /*!< @note: Header that defines the vector container class */

// Windows Libraries
#include <Windows.h>

// User defined
enum EXIT : bool
{
	FAILURE = 0,
	SUCCESS
};

#endif // !_PCH_H
