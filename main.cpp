// main.cpp (CdCatXmlToHtml) - main entry and argument processing
#include <iostream>
#include <QFile>
#include "CdCatTranslator.h"
#include "Messenger.h"

using namespace std;

int main(int argc, char *argv[])
{
	Messenger messenger;
	// display usage info if we are having wrong number of arguments
	if (argc != 3 )
	{	
		messenger.Usage(argv);
		return 0;
	}
 
	const QString fileName (argv[1]); 
	const QString outputFileName (argv[2]);

	if (fileName.isEmpty() || (!QFile::exists(fileName)) )
	{
		messenger.NotExist(argv[1]);
		return -1;
	}
    QFile file(fileName);
	if ( file.open(QFile::ReadOnly | QFile::Text) )
		Translator::CdCatTranslator().translate(&file, outputFileName);
	else
	{
		messenger.CantOpenForRead(argv[1]);
		return -1;
	}
	return 1;
}
