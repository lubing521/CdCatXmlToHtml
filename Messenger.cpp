
#include "Messenger.h"
#include <string>
using namespace std;

Messenger::Messenger( std::ostream& stream ) : _stream(stream)
{
}

string extractFilename (const string& str )
{
  const size_t found = str.find_last_of("/\\");
  return str.substr(found+1) ;
}

void Messenger::Usage( char *argv[])
{
	const string& filename = extractFilename (argv[0]);
	_stream << endl << filename << " - converts xml cd catalog file to html page" << endl <<
		"Usage: " << filename << " <source> <destination>" << endl <<
		"Ex.: " << filename << " /home/User/cd_catalog.xml catalog_page.html" << endl;
}
void Messenger::CantOpenForRead(const char* filename)
{
	_stream << "Could not open file " << filename << " for reading" << std::endl;
}
void Messenger::NotExist(const char *filename)
{
	_stream << "Error: file " << filename << "does not exist or empty" << std::endl;
}
void Messenger::WrongFormat(const char *xmlErrorString)
{
	_stream << xmlErrorString;
}
void Messenger::Finished(const char *filename)
{
	std::cout << std::endl << "Translation finished." << std::endl <<
		"Output is in: " << filename << std::endl;
}