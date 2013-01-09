#pragma once

#include <QSharedPointer>

class QIODevice;
class QString;
class QTextStream;

namespace Translator
{

class ITranslator
{
public:
	/*IReader(void);*/
	virtual void translate(QIODevice *device, const QString& outputFileName) = 0; 
	virtual QTextStream& output() = 0;
	virtual ~ITranslator(void);
};

} // namespace Translator
