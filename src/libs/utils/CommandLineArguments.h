//
// Created by klei on 4/25/18.
//

#ifndef PRODUCTION_LINE_CONTROL_COMMANDLINEARGUMENTS_H
#define PRODUCTION_LINE_CONTROL_COMMANDLINEARGUMENTS_H

#include <patterns/singleton/Singleton.h>
#include <limits>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>

namespace utils {

	/**
	 * Command line argument class from Robotworld.
	 */
	class CommandlineArgument
	{
	public:
		CommandlineArgument();

		explicit operator bool() const;


		explicit operator const std::string&() const;

		/**
		 * create new command line argument with id, the name (variable) and the value
		 * @param anArgumentNumber
		 * @param aVariable
		 * @param aValue
		 */
		CommandlineArgument( 	uint16_t anArgumentNumber,
								const std::string& aVariable,
								const std::string& aValue);

		/**
		 *copy constructor
		 * @param aCommandlineArgument
		 */
		CommandlineArgument( const CommandlineArgument& aCommandlineArgument);

		/**
		 * destruct
		 */
		virtual ~CommandlineArgument() = default;


		CommandlineArgument& operator=( const CommandlineArgument& aCommandlineArgument);
		bool operator==( uint16_t anArgumentNumber) const;
		bool operator==( const std::string& aVariable) const;
		bool operator==( const CommandlineArgument& other) const;
		bool operator<( const CommandlineArgument& aCommandlineArgument) const;

		/**
		 * get the default empty argument
		 * @return
		 */
		static const CommandlineArgument& getNone();

		uint16_t argumentNumber;	// argument index
		std::string variable;		// argument variable name
		std::string value;			// argument value
	};

	/**
	 * Holds all command line arguments, copied from Robotworld
	 * named:  -x value, -x=value
	 *  Will be stored in CommandLineArgument vector
	 * unnamed:  value
	 * 	Will be stored in string vector
	 */
    class CommandLineArguments : public patterns::Singleton::Singleton<CommandLineArguments> {
	public:
		CommandLineArguments() = default;
		virtual ~CommandLineArguments() = default;

		void setCommandlineArguments(uint16_t argc, char* argv[]);

		/**
		 * Get key worded argument by name
		 * @param aVariable : name of argument
		 * @return : argument value
		 */
		const CommandlineArgument& getKwarg(const std::string& aVariable);

		/**
		 * Get key worded argument by index
		 * @param anArgumentNumber : argument index
		 * @return : argument value
		 */
		const CommandlineArgument& getKwarg( uint16_t anArgumentNumber);

		/**
		 * Get string argument (not key worded)
		 * @param index : argument index
		 * @return : argument value
		 */
		const std::string& getArg( uint16_t index);


		std::vector< std::string >& getAllArgs();


	private:

		std::vector< CommandlineArgument > commandlineArguments;
		std::vector< std::string > commandlineFiles;

	};

} // namespace utils

#endif //PRODUCTION_LINE_CONTROL_COMMANDLINEARGUMENTS_H
