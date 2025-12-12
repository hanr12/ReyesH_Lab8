//Hannah Reyes
//CSCN 112 - Dynamic Allocation of Memory
// 11/1/2025
#include "Date.h"

std::ostream& operator<<(std::ostream& output, Date d)
{
	output << std::to_string(d.month) + "/" + std::to_string(d.day) + "/" + std::to_string(d.year);
	return output;
}


Date::Date(int m, int d, int yyyy)
	{
		setDate(m, d, yyyy);
	}

Date::~Date() {}

void Date::setDate(int  m, int d, int yyyy)
{
	month = m;
	day = d;
	year = yyyy;
}


