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

class CommandlineArgument
{
public:
	static const CommandlineArgument None;
	/**
	 * @name Constructors and destructor
	 */
	//@{
	CommandlineArgument()
			: argumentNumber(-1)
			, variable()
			, value()
	{
	}

	explicit operator bool()  const  {
		return argumentNumber >=0 && !variable.empty();
	}


	explicit operator const std::string&() const {
		return value;
	}

	/**
	 *
	 * @param anArgumentNumber
	 * @param aVariable
	 * @param aValue
	 */
	CommandlineArgument( 	unsigned long anArgumentNumber,
							const std::string& aVariable,
							const std::string& aValue) :
			argumentNumber( anArgumentNumber),
			variable( aVariable),
			value( aValue)
	{
	}
	/**
	 *
	 * @param aCommandlineArgument
	 */
	CommandlineArgument( const CommandlineArgument& aCommandlineArgument) :
			argumentNumber( aCommandlineArgument.argumentNumber),
			variable( aCommandlineArgument.variable),
			value( aCommandlineArgument.value)
	{
	}
	/**
	 *
	 */
	virtual ~CommandlineArgument()
	{
	}
	//@}

	/**
	 * @name Operators
	 */
	//@{
	/**
	 *
	 */
	CommandlineArgument& operator=( const CommandlineArgument& aCommandlineArgument)
	{
		if(this != &aCommandlineArgument)
		{
			argumentNumber = aCommandlineArgument.argumentNumber;
			variable = aCommandlineArgument.variable;
			value = aCommandlineArgument.value;
		}
		return *this;
	}
	/**
	 *
	 */
	bool operator==( int anArgumentNumber) const {
		return argumentNumber == anArgumentNumber;
	}
	/**
	 *
	 */
	bool operator==( const std::string& aVariable) const {
		return variable == aVariable;
	}
	/**
	 *
	 */
	bool operator==( const CommandlineArgument& other) const {
		return &other == this ||
			   (argumentNumber == other.argumentNumber &&
				variable == other.variable &&
				value == other.value);
	}
	/**
	 *	Only compares the argument number.
	 */
	bool operator<( const CommandlineArgument& aCommandlineArgument) const
	{
		return argumentNumber < aCommandlineArgument.argumentNumber;
	}
	//@}

	int argumentNumber;
	std::string variable;
	std::string value;

protected:


private:
};

class CommandLineArguments : public Patterns::Singleton::Singleton<CommandLineArguments> {
public:
	CommandLineArguments() = default;
	virtual ~CommandLineArguments() = default;

	void setCommandlineArguments(int argc, char* argv[])
	{
		// argv[0] contains the executable name as one types on the command line (with or without extension)
		commandlineArguments.push_back( CommandlineArgument( 0, "Executable", argv[0]));

		for (int i = 1; i < argc; ++i)
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
						commandlineArguments.push_back( CommandlineArgument( i, variable, value));
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
				commandlineArguments.push_back( CommandlineArgument( i, variable1, value1));
			} else // file argument
			{
				commandlineFiles.push_back( currentArg);
			}
		}
	}


	const CommandlineArgument& getArg(const std::string& aVariable)
	{
		auto i = std::find( commandlineArguments.begin(), commandlineArguments.end(), aVariable);
		return i == commandlineArguments.end() ? CommandlineArgument::None : *i;
	}


	const CommandlineArgument& getArg( int anArgumentNumber)
	{
		if((unsigned)anArgumentNumber >= commandlineArguments.size())
			return CommandlineArgument::None;
		return commandlineArguments[anArgumentNumber];
	}


	std::vector< std::string >& getCommandlineFiles()
	{
		return commandlineFiles;
	}

private:

	static std::vector< CommandlineArgument > commandlineArguments;
	static std::vector< std::string > commandlineFiles;

};


#endif //PRODUCTION_LINE_CONTROL_COMMANDLINEARGUMENTS_H
