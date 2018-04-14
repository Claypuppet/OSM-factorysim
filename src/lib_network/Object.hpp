#ifndef OBJECT_HPP_
#define OBJECT_HPP_

/*
 * Copyright (c) 2016 Joost Kraaijeveld. See license.txt for details.
 * For information, bug reports and additions send an e-mail to UnitTest@Askesis.nl.
 *
 * Author: jkr
 */

#include <string>
#include <iostream>

class Object
{
	public:
		Object();
		Object( const std::string& aName);
		virtual ~Object();

		Object& operator=( const Object& anObject);
		bool operator==( const Object& anObject) const;
		bool operator<( const Object& anObject) const;
		friend std::ostream& operator<<(std::ostream& os , const Object& anObject);
	private:
		std::string name;
};

inline std::ostream& operator<<(std::ostream& os , const Object& anObject)
{
	return os << anObject.name;
}

inline void mijnFunctie(){}
inline bool mijnBoolFunctie(){return true;}
#endif // OBJECT_HPP_ 
