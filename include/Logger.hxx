#ifndef LOGGER_H
#define LOGGER_H

#include <string.h>
#include <iostream>

/**
 * prints a newline in std out
 */
inline void log_ln(){
	std::cout << "\n";
}

/**
 * prints a newline in std err
 */
inline void log_ln_err(){
	std::cerr << "\n";
}

/**
 * Prints a single message into std out and includes new line.
 */
template<typename T>
void log_info(T &&info){
	std::cout << info << "\n";
}

/**
 * Prints a single message into std out and without new line.
 */
template<typename T>
void log_info_noln(T &&info){
	std::cout << info;
}

/**
 * Prints to std out. Function handles variadic arguments of any type and adds new line at end.
 * NOTE, each argument is automaticly seperate by a SINGLE space " ".
 */
template<typename T, typename ... args>
void log_info(T &&first, args ... rest){
	std::cout << first << ' ';
	log_info(std::forward<args>(rest) ...);
}

/**
 * Prints a single message into std err and includes new line.
 */
template<typename T>
void log_error(T &&error){
	std::cerr << error << "\n";
}

/**
 * Prints to std err. Function handles variadic arguments of any type and adds new line at end.
 * NOTE, each argument is automaticly seperate by a SINGLE space " ".
 */
template<typename T, typename ...args>
void log_error(T &&first, args ...rest){
	std::cerr << first << ' ';
	log_error(std::forward<args>(rest)...);
}

/**
 * Prints to std err. Function handles variadic arguments of any type and adds new line at end.
 * Afterwards the function Exits the program with EXIT_FAILURE.
 * NOTE, each argument is automaticly seperate by a SINGLE space " ".
 */
template<typename T, typename ...args>
void log_error_and_exit(T &&first, args ...rest){
	std::cerr << first << ' ';
	log_error(std::forward<args>(rest)...);
	exit(EXIT_FAILURE);
}

/**
 * Prints a single message into std err and includes new line.
 * Afterwards the function Exits the program with EXIT_FAILURE.
 */
template<typename T>
void log_error_and_exit(T &&first){
	std::cerr << first << '\n';
	exit(EXIT_FAILURE);
}

/**
 * Prints a single message into std err.
 * The function also prints the current errno.
 * Adds a new line at the end.
 */
template<typename T>
void log_error_and_sterror(T &&first){
	std::cerr << first << ' ' << strerror(errno) << '\n';
}

/**
 * Prints a single message into std err.
 * The function also prints the current errno.
 * Adds a new line at the end.
 * Afterwards the function Exits the program with EXIT_FAILURE.
 */
template<typename T>
void log_error_and_sterror_and_exit(T &&first){
	std::cerr << first << ' ' << strerror(errno) << '\n';
	exit(EXIT_FAILURE);
}
/**
 * quick function that removes any ostream formatting from std out and err.
 */
void inline log_clear_formatting(){
	std::cout.unsetf(std::ios::adjustfield);
	std::cout.unsetf(std::ios::basefield);
	std::cout.unsetf(std::ios::floatfield);
	std::cout.fill(' ');          // reset fill character
	std::cout.width(0);           // reset width
	std::cout.precision(6);       // reset precision (default is 6)
								  //
	std::cerr.unsetf(std::ios::adjustfield);
	std::cerr.unsetf(std::ios::basefield);
	std::cerr.unsetf(std::ios::floatfield);
	std::cerr.fill(' ');          // reset fill character
	std::cerr.width(0);           // reset width
	std::cerr.precision(6);       // reset precision (default is 6)
}

#endif
