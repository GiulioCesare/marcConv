/*
 * Subfield.h
 *
 *  Created on: 3-dic-2008
 *      Author: Arge
 */

#ifndef SUBFIELD_H_
#define SUBFIELD_H_
#include "library/CString.h"
#include "MarcConstants.h"

class Subfield {
private:
	long id;
    char code;
    CString data;
    CString stringed;


public:
	Subfield();
	Subfield(char code);
//	Subfield(char code, char* data);
	Subfield(char code, CString* data);
	Subfield(int id, char code, CString* data);

	Subfield(char code, char* data, int len);

	virtual ~Subfield();

	long getId(); // sfNew->
    void setId(long  id);
    char getCode(); //  const
    void setCode(char code);
    char* getData();
    long getDataLength();
    long getToStringLength();
    CString* toCString();

    long getToXmlLength();


    CString* getDataString();
//    void setData(const char* data);
    void setData(CString *sPtr);
    void setData(char* data, int len);


    void appendData(char* data);

    void appendData(CString* sPtr);
    void appendData(char* ptr, int length);



    bool find(char* pattern);
    char* toString();
    CString* toXml(int indent);

};

#endif /* SUBFIELD_H_ */
