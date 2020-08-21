/*
 * ControlField.cpp
 *
 *  Created on: 3-dic-2008
 *      Author: Arge
 */

#include "ControlField.h"

ControlField::ControlField() {

}

    /**
     * Creates a new <code>ControlField</code> and sets the tag name.
     */
ControlField::ControlField(char *tag) {
        this->setTag(tag);
    }

    /**
     * Creates a new <code>ControlField</code> and sets the tag name and the
     * data element.
     *
     */
ControlField::ControlField(char* tag, char* data) {
        //this->setTag(tag);
        this->tag.assign(tag, 3);

        //this->setData(data);
        this->data.assign(data);
    }



ControlField::~ControlField() {
}


//char * ControlField::getData() {
//        return data.data();
//    }
CString *ControlField::getData() {
        return &data;
    }


bool ControlField::find(char* pattern) {
//        Pattern p = Pattern.compile(pattern);
//        Matcher m = p.matcher(getData());
//        return m.find();
	// todo ControlField::find
	return false;
}


void ControlField::setId(long id) {
        this->id = id;
    }

long ControlField::getId() {
        return id;
    }

void ControlField::setTag(char * tag) {
        this->tag.assign(tag, 3);
    }

//void ControlField::setTag(const char * tag) {
//    this->tag.assign((char *)tag);
//    }

void ControlField::setTag(CString * tag) {
        this->tag.assign(tag);
    }

char *ControlField::getTag() {
        return this->tag.data();
    }

/**
 * Returns a string representation of this control field.
 *
 * <p>
 * Example:
 *
 * <pre>
 *     001 12883376
 * </pre>
 *
 * @return String - a string representation of this control field
 */
char* ControlField::toString() {
	stringed.assign("\n=", 2);
		stringed.AppendString(&tag);
		stringed.AppendString("  ", 2);
		stringed.AppendString(&data);
        return stringed.data();
    }
CString* ControlField::toCString() {
		stringed.assign("\n=", 2);
		stringed.AppendString(&tag);
		stringed.AppendString("  ", 2);
		stringed.AppendString(&data);
        return &stringed;
    }


char* ControlField::toXml(int indent) {
		stringed = '\n';
		for (int i=0; i< indent; i++)
			stringed.AppendChar('\t');
		stringed.AppendString("<cf t=\"", 7);
		stringed.AppendString(&tag);
		stringed.AppendString("\">", 2);
		stringed.AppendString(&data);
		stringed.AppendString("</cf>", 5);
        return stringed.data();
}


CString* ControlField::toCStringXml(int indent) {
		stringed = '\n';
		for (int i=0; i< indent; i++)
			stringed.AppendChar('\t');
		stringed.AppendString("<cf t=\"", 7);
		stringed.AppendString(&tag);
		stringed.AppendString("\">", 2);
		stringed.AppendString(&data);
		stringed.AppendString("</cf>", 5);
        return &stringed;
}




long ControlField::getToXmlLength() {
    return stringed.Length();
    }

//void ControlField::setData(const char* data) {
//    this->data = data;
//    }

void ControlField::setData(char* data, int len) {
    this->data.assign(data, len);
    }

void ControlField::setData(CString* data) {
    this->data.assign(data);
    }
