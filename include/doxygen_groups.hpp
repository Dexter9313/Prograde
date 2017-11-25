/*! \defgroup math Mathematics
 * Contains everything related to mathematics, including algebra or numerical
 * analysis.
 *
 *  # Conventions
 *
 *  - Right-handed coordinate systems will be used.
 *  - *z* coordinate (the third one) points "up" whenever it makes sense to
 * refer to an "up" direction.
 *  - Angles with implicit units are in radians
 *
 *  # Authorized libraries
 *
 *  To better control what uses which library, each module has a set of
 * authorized libraries. This is desired mainly in case any library has to be
 * changed or updated. Hopefully in these cases, the least amount of code will
 * have to be rewritten.
 *
 *  The C++ Standard Library is always considered authorized.
 *
 * For this module, these libraries are :
 *  - GNU Scientific Library
 *
 *  Any other library usage within this module will have to be discussed in an
 * issue and properly documented if accepted.
 *
 */

/*! \defgroup exceptions Exceptions
 * Contains everything related to exceptions definition and handling
 *
 * Typical usage :
 *
 * \code{.cpp}
 *
 * #include "exceptions/Exceptions.hpp"
 *
 * int main(int argc, char* argv[]) //argv is mandatory
 * {
 *  	BEGIN_EXCEPTIONS
 *
 *  	//some code
 *
 *  	CRITICAL("There's a problem")
 *
 *  	//some code
 *
 *  	END_EXCEPTIONS
 *
 *  	return 0;
 * }
 * \endcode
 *
 * Not every function is detailed in this documentation as they are not supposed
 * to be used elsewhere in the project,
 * so for more details please directly read the Exceptions.hpp file's source
 * code.
 *
 * # Authorized libraries
 *
 *  To better control what uses which library, each module has a set of
 * authorized libraries. This is desired mainly in case any library has to be
 * changed or updated. Hopefully in these cases, the least amount of code will
 * have to be rewritten.
 *
 *  The C++ Standard Library is always considered authorized.
 *
 *  For now, this module can only use the C++ standard library.
 *
 */
