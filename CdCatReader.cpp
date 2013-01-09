// CdCatReader.cpp - IReader implementation for parsing CD catalogues.
#include <vector>
#include <QString>
#include <QXmlStreamReader>
#include <QTextStream>
#include <QFile>
#include "HtmlWriter.h"
#include "CdCatReader.h"
#include <qdebug.h>

static const QString rootElementName = "CATALOG";


void CdCatReader::TODO_FUNC() 
{
qDebug() << __FILE__ << ": " << __LINE__ << "Replace this with a proper func";
}
void TODO_FUNC(int ) 
{
qDebug() << __FILE__ << ": " << __LINE__ << "Replace this with a proper func";
}

const QString tags[] = {"TITLE","ARTIST","COMPANY", "COUNTRY", "PRICE", "YEAR"};
std::vector<QString> vtags (tags, tags + (sizeof tags / sizeof tags[0]));

CdCatReader::CdCatReader(void) 
{
//	_htmlText = QSharedPointer<QString>( new QString(BufferSize, '\0'));
	_xml = new QXmlStreamReader();	
	// Most desktop operating systems overcommit memory. This means that malloc() or operator new return a valid pointer,
	//	even though there is not enough memory available at allocation time. On such systems, no exception of type std::bad_alloc is thrown. - Qt4 doc

	//<CD>
	//	<TITLE>Mad Dogs and Englishmen</TITLE>
	//	<ARTIST>Joe Cocker</ARTIST>
	//	<COMPANY>A&amp;M</COMPANY>
	//	<COUNTRY>USA</COUNTRY>
	//	<PRICE>9.80</PRICE>
	//	<YEAR>1970</YEAR>
	//</CD>
	// init the map of parsing functions 
	//QStringRef title = ;

	//std::vector Foo::MyVector(a, a + (sizeof a / sizeof a[0]));

	// so far all except "CD" would have one function
	_nodeNameToFunc[new QString("CD")] = &CdCatReader::readCD;
	_nodeNameToFunc[new QString("TITLE")] = &CdCatReader::readField;
	_nodeNameToFunc[new QString("ARTIST")] = &CdCatReader::TODO_FUNC;
	_nodeNameToFunc[new QString("COMPANY")] = &CdCatReader::TODO_FUNC;
	_nodeNameToFunc[new QString("PRICE")] = &CdCatReader::TODO_FUNC;
	_nodeNameToFunc[new QString("YEAR")] = &CdCatReader::TODO_FUNC;

	_htmlFile = std::auto_ptr<QFile>(new QFile("output.html")); //TODO: init from argv[2]

	if (_htmlFile->open(QFile::WriteOnly | QFile::Truncate))
	{
		_output = QSharedPointer<QTextStream>(new QTextStream(_htmlFile.get()));
		_writer = new HtmlWriter( _output );
	}
}

QTextStream& CdCatReader::output()
{
	return *_output;
}

bool CdCatReader::fitsBuffer()
{
	//if (_xml->characterOffset() > BufferSize)
	//{
	//	//TODO: do someting
	//	// set isFull true
	//	// give result; result final/not
	//	// ... 
	//	_isFull = true;
	//	return;
	//}
	return false;
}

void CdCatReader::read(QIODevice *device)
{
	bool began = false;
	_xml->setDevice(device);

	 while (_xml->readNextStartElement())
	 {
        if (_xml->name() == rootElementName ) //check whether it's our file
		{
			_writer->BeginDoc();
			began = true;
            findCDs(); //start processing
		}
        else
			_xml->skipCurrentElement();
	 }
	 if (!began)
		 _xml->raiseError(QObject::tr("The file is not an CD Catalog file."));
	 else
		 _writer->EndDoc();	 
	 qDebug() <<  _xml->errorString();
}

void CdCatReader::findCDs()
{
	while (_xml->readNextStartElement()) // read every cd and skip all in between
        _xml->name() == "CD" ? readCD() : _xml->skipCurrentElement();
}
void CdCatReader::readCD()
{
	Q_ASSERT(_xml->name() == "CD"); 
	
	{ 
		_writer->CdHead();
		
		while (_xml->readNextStartElement()) // raead fields (artist, album...)
		{
			if(std::find(vtags.begin(), vtags.end(), _xml->name().toString()) != vtags.end()) 
				_writer->Field(_xml->name(), _xml->readElementText()); 
			else
				_xml->skipCurrentElement();
			//it = _nodeNameToFunc.find(_xml->name());
			//it == _nodeNameToFunc.end() ? _xml->skipCurrentElement() : (this->*(it->second))(); // skip or call an appropriate processing function	
		}
		_writer->CdTail();
	}
}


void CdCatReader::readField()
{
	_writer->Field(_xml->name(), _xml->readElementText());
	//_writer->MakeHtmlCDElementRow(_xml->readElementText());
}
//void CdCatReader::readArtist()
//{
//}
//void CdCatReader::readCompany()
//{
//}
//void CdCatReader::readPrice()
//{
//}
//void CdCatReader::readYear()
//{
//}

CdCatReader::~CdCatReader(void)
{
//	_output->flush();
}
