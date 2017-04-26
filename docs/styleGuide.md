# Style Guide

## Structure

### Typical structure

```
.
├── LICENSE
├── Makefile
├── README.md
├── bin
├── docs
├── logs
└── src
    ├── libs
    ├── log


```
* Both a header and .c / .cpp file must be supplied (ie: no combined prototypes and implementation in the same file)
* For c++ each class must be in a seperate directory

## Preprocessor
* use include guards of the form 
```
#ifndef __HEADFILENAME_H
#define __HEADFILENAME_H

...

#endif __HEADFILENAME_H
```

* use extern "C" wrappers around C headers (but within the include guards), e.g.
```C
	#ifdef __cplusplus
	extern "C" {
	#endif

	...

	#ifdef __cplusplus
	}
	#endif
```
**Note** This is not required for C++ headers.



## White Space
* spaces (4), not tabs
* one space before opening bracket, none after
* one space after separating "," in argument lists
* block delimiters K&R style, e.g.
```C

void some_function()
{
  if (frobnicator_enabled) {
  	 do_stuff();
	 then_more_stuff();
  }
  else {
  	 uh_oh();
	 bail();
  }
}
```
  
* try to keep line width <= 90 characters (definitely less that 120)
* when using **OS X** the use of a ```.clang-format``` file is useful.


## Naming Conventions
### C
* function names and regular variables (include) function arguments should be lower case, name components separated by underbar character
* statiic variables
* typenames should be regular names with "_t" appended to them

### C++
* Class names camel case, proper case
* non-static member variables should have leading underbar ("_") with regular camel case after that

### Example
#### Header File
```C++
#ifndef INC_EXAMPLES_H
#define INC_EXAMPLES_H

#include <string>
#include <iostream>

/**
 * Class summary documentation - this class demonstrates the basic
 * pattern of what is considered acceptable core c++ style.
 *
 * NOTE:
 *  - order of protected/public sections
 *  - naming convention
 *  - use of 'virtual' keyword
 *  - use of newline to logically group sections of methods
 */
class BaseClass
{
protected:
	 //! this is a trivial inline method without an interesting name...note the inline doxygen comment style
	 virtual void trivialInlineMethod(void) { std::cout << "this doesn't do much" << std::endl; };

	 std::string _protectedStringAttribute;
	 static char _StaticCharacterAttribute; //! note the _CapitalisationOfTheName
	 
public:
	 //! you may think this is because we have a derived class
	 virtual ~BaseClass(void);
	 BaseClass(void);

	 //! note newline above to separate constructors/desstructors from other methods
	 virtual void setProtectedStringAttribute(std::string attributeValue);
	 virtual std::string getProtectedStringAttribute(void);

	 static int32_t SomeStaticMethod() { return 42; }; //! use explicit size types
	 static char GetStaticCharacterAttribute(void);
};

class DerivedClass : public BaseClass
{
public:
	 virtual ~DerivedClass(void);
	 DerivedClass(void);

	 virtual void setProtectedStringAttribute(std::string attributeValue);
};

/**
 * This class exists to show that even without known descendent
 * classes, you should always (always) make destructors virtual.
 */
class UnrelatedClass
{
public:
	void UnrelatedClass();
	virtual ~UnrelatedClass(void);
};

#endif
```

#### Implementation File
```C++
#include "examples.h"

// -- BaseClass

char BaseClass::_StaticCharacterAttribute = 'A';

BaseClass::BaseClass(void) : _protectedStringAttribute("boo!")
{
}

BaseClass::~BaseClass(void)
{
	std::cout << "I'm melting!" << std::endl;
}

void BaseClass::setProtectedStringAttribute(std::string attributeValue)
{
	_protectedStringAttribute = attributeValue;
}

std::string BaseClass::getProtectedStringAttribute(void)
{
	return _protectedStringAttribute;
}

char BaseClass::GetStaticCharacterAttribute(void)
{
	return _StaticCharacterAttribute;
}

// -- DerivedClass

DerivedClass::DerivedClass(void)
{
}

DerivedClass::~DerivedClass(void)
{
}

void DerivedClass::setProtectedStringAttribute(std::string attributeValue)
{
	BaseClass::setProtectedStringAttribute(attributeValue);
	std::cout << "just called super implementation of " << __FUNCTION__ << std::endl;
}

// -- UnrelatedClass

UnrelatedClass::UnrelatedClass()
{
}

UnrelatedClass::~UnrelatedClass()
{
}

```