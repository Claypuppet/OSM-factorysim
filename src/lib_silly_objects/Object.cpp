/*
 * Copyright (c) 2016 Joost Kraaijeveld. See license.txt for details.
 * For information, bug reports and additions send an e-mail to UnitTest@Askesis.nl.
 *
 * Author: jkr
 */

#include "Object.hpp"

Object::Object()
{
}

Object::Object( const std::string& aName) : name (aName)
{

}

Object::~Object()
{
}

Object& Object::operator=( const Object& anObject)
{
	if(this != &anObject)
	{
		name = anObject.name;
	}
	return *this;
}

bool Object::operator==( const Object& anObject) const
{
	return name == anObject.name;
}

bool Object::operator<( const Object& anObject) const
{
	return name < anObject.name;
}
