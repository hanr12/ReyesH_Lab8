//Hannah Reyes
//CSCN 112 - Dynamic Allocation of Memory
// 11/1/2025
#pragma once

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>

class Date 
{
	friend std::ostream& operator<<(std::ostream& output, Date d);
	
public:
	Date(int =0, int =0, int = 0);
	~Date();
	void setDate(int, int, int);
	
private:
	int month;
	int day;
	int year;
};
