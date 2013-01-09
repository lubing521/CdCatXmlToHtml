
#include <QtCore/QCoreApplication>
#include <QFile>
#include "CdCatReader.h"
int main(int argc, char *argv[])
{
	//QCoreApplication a(argc, argv);
	
	IReader *reader = new CdCatReader;
    QString fileName = "D:/Sources/CdCatXmlToHtml/cd_catalog.xml"; //TODO: get it from argv[1]
	if (fileName.isEmpty() || (!QFile::exists(fileName)) )
		return -1;
    QFile file(fileName);
	if ( file.open(QFile::ReadOnly | QFile::Text) )
		reader->read(&file);
	delete reader;
	return 0;

}
