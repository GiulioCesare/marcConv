/*
 * Subfield.cpp
 *
 *  Created on: 3-dic-2008
 *      Author: Arge
 */

#include "Subfield.h"
#ifdef TRACK_MEMORY_LEAKS
    #include "nvwa/debug_new.h"
#endif



extern void SignalAnError(	const OrsChar *Module, OrsInt Line, const OrsChar * MsgFmt, ...);
extern void SignalAWarning(	const OrsChar *Module, OrsInt Line, const OrsChar * MsgFmt, ...);



Subfield::Subfield() {
}

Subfield::~Subfield() {
}

/**
 * Creates a new <code>Subfield</code> and sets the data element
 * identifier.
 *
 * @param code
 *            the data element identifier
 */
Subfield::Subfield(char code) {
        //this->setCode(code);
		this->code = code;
    }

/**
 * Creates a new <code>Subfield</code> and sets the data element
 * identifier and the data element.
 *
 * @param code
 *            the data element identifier
 * @param data
 *            the data element
 */
//Subfield::Subfield(char code, char* data) {
//        this->setCode(code);
//        this->setData(data, strlen(data));
//    }

Subfield::Subfield(char code, CString* data) {
		this->code = code;
        this->data.assign(data->data(), data->Length());
    }

Subfield::Subfield(char code, char* data, int len) {
	this->code = code;

if (len < 0)
{
	SignalAnError(__FILE__, __LINE__, "Subfield::Subfield len %d < 0, code=%c data=%s", len, code, data);
	return;
}


    this->data.assign(data, len);
    }

Subfield::Subfield(int id, char code, CString* data) {
		this->code = code;
		this->id = id;
        this->data.assign(data->data(), data->Length());
    }




long Subfield::getId() //const
{
    return id;
}

void Subfield::setId(long  id)
{
    this->id = id;
}

char Subfield::getCode() //const
{
    return code;
}

void Subfield::setCode(char code)
{
    this->code = code;
}

char* Subfield::getData()
{
    return data.data();
}

long Subfield::getDataLength()
{
    return data.Length();
}



//void Subfield::appendData(char* data) // const
void Subfield::appendData(CString* sPtr)
{
    this->data.AppendString(sPtr);
}

void Subfield::appendData(char* ptr, int length)
{
    this->data.AppendString(ptr, length);
}

void Subfield::appendData(char* ptr) // TODO To be removed
{
    this->data.AppendString(ptr);
}





bool Subfield::find(char* pattern) {
//        Pattern p = Pattern.compile(pattern);
//        Matcher m = p.matcher(getData());
//        return m.find();
    printf ("TODO");
    return false;
}

/**
 * Returns a string representation of this subfield.
 *
 * <p>
 * Example:
 *
 * <pre>
 * $aSummerland /
 * </pre>
 *
 * @return String - a string representation of this subfield
 */
char* Subfield::toString() {
    stringed = '$';
    stringed.AppendChar(code);

// 14/09/2021
data.ChangeTo("$", "{dollar}");

    stringed.AppendString(&data);
    return stringed.data();
    }

CString* Subfield::toCString()
{

    stringed = '$';
    stringed.AppendChar(code);

// 14/09/2021
data.ChangeTo("$", "{dollar}");

    stringed.AppendString(&data);
    return &stringed;
}


long Subfield::getToStringLength() {
    return stringed.Length();
    }


CString* Subfield::getDataString()
{
// 14/09/2021
data.ChangeTo("$", "{dollar}");

	return &data;
}


CString* Subfield::toXml(int indent) {
	stringed = '\n';
	for (int i=0; i< indent; i++)
		stringed.AppendChar('\t');

	stringed.AppendString("<sf c=\"", 7);
    stringed.AppendChar(code);
    stringed.AppendString("\">", 2);
    stringed.AppendString(&data);
    stringed.AppendString("</sf>", 5);
//    return stringed.data();
    return &stringed;
    }

long Subfield::getToXmlLength() {
    return stringed.Length();
    }

//void Subfield::setData(const char* data)
//{
//    this->data = data;
//}

void Subfield::setData(CString* data)
{
    this->data.assign(data);
}

void Subfield::setData(char* data, int len)
{
    this->data.assign(data, len);
}


