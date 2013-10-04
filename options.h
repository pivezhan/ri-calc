#ifndef	RTS_OPTIONS_H
#define RTS_OPTIONS_H

#include <string>

enum opt_type {optInt, optDouble, optStr, optFlag};

struct opt
{
	//long name for the option
	std::string _lname;

	//short name for the option
	char _sname;

	//help string
	std::string _help;

	//store the type
	opt_type _type;

	//data is stored in a vector of void pointers
	std::vector<void*> _data;
};

class rtOptions
{
	std::vector<opt> optArray;

	int addOption(char sname, std::string lname, std::string help, opt_type type = optStr)
	{


	}

};




#endif