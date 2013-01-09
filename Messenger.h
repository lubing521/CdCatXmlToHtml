#pragma once

#include <iostream>

class Messenger
{
public:
	Messenger( std::ostream& stream = std::cout); 

	void Usage( char *argv[]);
	void CantOpenForRead(const char* filename);
	void NotExist(const char *filename);
	void WrongFormat(const char *xmlErrorString);
	void Finished(const char *filename);

private:
	std::ostream& _stream;
};