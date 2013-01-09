CdCatXmlToHtml
==============

Parses a catalogue of xml and creates an html page

To build you need CMAKE 2.8 and Qt 5+

quick dirty build(you must have compiler, make, QT5 and cmake bin directory in PATH):
cd CdCatXmlToHtml
cmake . -DQt5Xml_Dir=D:/Sources/qt-src-5.0.0/qtbase/lib/cmake/Qt5Xml
make

Key modules are CdCatTranslator and HtmlWriter

CdCatTranslator reads XML data from file (utilizing QXmlStreamReader) and calls HtmlWriter to write the output. 
HtmlWriter writes the html tags and values into specified output (file in our case).
The logic of HtmlWrite also partially illustrated in output_mockup.html file (see comments there).