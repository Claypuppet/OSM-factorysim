//
// Created by klei on 5/4/18.
//

#include "CommandLineArguments.h"

namespace utils {

	CommandlineArgument::CommandlineArgument()
			: argumentNumber()
			, variable()
			, value()
	{
	}

	CommandlineArgument::CommandlineArgument( 	uint16_t anArgumentNumber,
												 const std::string& aVariable,
												 const std::string& aValue) :
			argumentNumber( anArgumentNumber),
			variable( aVariable),
			value( aValue)
	{
	}

	CommandlineArgument::CommandlineArgument( const CommandlineArgument& aCommandlineArgument) :
			argumentNumber( aCommandlineArgument.argumentNumber),
			variable( aCommandlineArgument.variable),
			value( aCommandlineArgument.value)
	{
	}

	CommandlineArgument::operator bool()  const  {
		return argumentNumber >=0 && !variable.empty();
	}


	CommandlineArgument::operator const std::string&() const {
		return value;
	}

	CommandlineArgument& CommandlineArgument::operator=( const CommandlineArgument& aCommandlineArgument)
	{
		if(this != &aCommandlineArgument)
		{
			argumentNumber = aCommandlineArgument.argumentNumber;
			variable = aCommandlineArgument.variable;
			value = aCommandlineArgument.value;
		}
		return *this;
	}

	bool CommandlineArgument::operator==( uint16_t anArgumentNumber) const {
		return argumentNumber == anArgumentNumber;
	}

	bool CommandlineArgument::operator==( const std::string& aVariable) const {
		return variable == aVariable;
	}

	bool CommandlineArgument::operator==( const CommandlineArgument& other) const {
		return &other == this ||
			   (argumentNumber == other.argumentNumber &&
				variable == other.variable &&
				value == other.value);
	}

	bool CommandlineArgument::operator<( const CommandlineArgument& aCommandlineArgument) const
	{
		return argumentNumber < aCommandlineArgument.argumentNumber;
	}

	const CommandlineArgument &CommandlineArgument::getNone() {
		static CommandlineArgument c;
		return c;
	}


	void CommandLineArguments::setCommandlineArguments(uint16_t argc, char* argv[])
	{
		// argv[0] contains the executable name as one types on the command line (with or without extension)
		commandlineArguments.emplace_back(0, "Executable", argv[0]);

		for (uint16_t i = 1; i < argc; ++i)
		{
			char* currentArg = argv[i];
			size_t argLength = std::strlen( currentArg);


			// If the first char of the argument is not a "-" we assume that is is
			// a filename otherwise it is an ordinary argument

			if (currentArg[0] == '-') // ordinary argument
			{
				bool inserted = false;

				// First handle the arguments in the form of "variable=value", and find the "="

				for (size_t j = 0; j < argLength; ++j)
				{
					if (currentArg[j] == '=')
					{
						std::string variable( currentArg, j);
						std::string value( &currentArg[j + 1]);
						commandlineArguments.emplace_back(i, variable, value);
						inserted = true;
					}
				}

				// Second handle the stand alone arguments.

				// If inserted is

				// It is assumed that they are actually booleans.
				// If given on the command line than the variable will be set to true as if
				// variable=true is passed
				if (inserted)
					continue;
				std::string variable1( currentArg);
				std::string value1( "true");
				commandlineArguments.emplace_back(i, variable1, value1);
			} else // file argument
			{
				commandlineFiles.emplace_back(currentArg);
			}
		}
	}


	const CommandlineArgument& CommandLineArguments::getKwarg(const std::string& aVariable)
	{
		auto i = std::find( commandlineArguments.begin(), commandlineArguments.end(), aVariable);
		return i == commandlineArguments.end() ? CommandlineArgument::getNone() : *i;
	}


	const CommandlineArgument& CommandLineArguments::getKwarg( uint16_t anArgumentNumber)
	{
		if((unsigned)anArgumentNumber >= commandlineArguments.size())
			return CommandlineArgument::getNone();
		return commandlineArguments[anArgumentNumber];
	}


	const std::string& CommandLineArguments::getArg( uint16_t index)
	{
		if(index >= commandlineFiles.size())
			return CommandlineArgument::getNone().value;
		return commandlineFiles[index];
	}


	std::vector< std::string >& CommandLineArguments::getAllArgs()
	{
		return commandlineFiles;
	}
}