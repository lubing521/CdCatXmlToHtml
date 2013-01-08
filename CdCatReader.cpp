// CdCatReader.cpp - IReader implementation for parsing CD catalogues.
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

CdCatReader::CdCatReader(void)
{
	_htmlText = QSharedPointer<QString>( new QString(BufferSize, '\0'));
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
	_nodeNameToFunc[new QString("TITLE")] = &CdCatReader::readTitle;
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
	_xml->setDevice(device);
	 while (_xml->readNextStartElement())
	 {
        if (_xml->name() == rootElementName ) //check whether it's our file
		{
			_writer->MakeBeginTable();
            readCdCat(); //start processing
		}
        else
            _xml->raiseError(QObject::tr("The file is not an CD Catalog file."));
	 }
	 _writer->MakeEndTable();
	 qDebug() << _xml->error();
}

void CdCatReader::readCdCat()
{
	while (_xml->readNextStartElement()) {

        if (_xml->name() == "CD")
            readCD();
        else
            _xml->skipCurrentElement();
    }
}
void CdCatReader::readCD()
{
	Q_ASSERT(_xml->name() == "CD"); 
	
	{ // protect iterator from being used by smth else
		std::map<QStringRef, CdCatFunction>::iterator it;
		while (_xml->readNextStartElement())
		{
			it = _nodeNameToFunc.find(_xml->name());
			it == _nodeNameToFunc.end() ? _xml->skipCurrentElement() : (this->*(it->second))(); // skip or call an appropriate processing function
		}
	}
}


void CdCatReader::readTitle()
{
	_writer->MakeHtmlCDElementRow(_xml->readElementText());
}
void CdCatReader::readArtist()
{
}
void CdCatReader::readCompany()
{
}
void CdCatReader::readPrice()
{
}
void CdCatReader::readYear()
{
}


QSharedPointer<QString> CdCatReader::htmlText() const
{
	return _htmlText;
}

bool CdCatReader::isFull() const
{
	return _isFull;
}
	
CdCatReader::~CdCatReader(void)
{
}
