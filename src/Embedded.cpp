/*
 * Embedded.cpp
 *
 *  Created on: 5-feb-2010
 *      Author: Arge
 */

#include "Embedded.h"
#include "DataField.h"

Embedded::Embedded() {
}

Embedded::~Embedded() {
	stop();
}


void Embedded::stop() {
	controlFieldsVector.DeleteAndClear();

	//	dataFieldsVector.DeleteAndClear(); // Non funziona con i void pointers
	DataField * df;
	for (int i=0; i < dataFieldsVector.length(); i++)
	{
		df = (DataField *)dataFieldsVector.Entry(i);
		delete (df);
	}
}


void Embedded::addControlField(ControlField *controlField) {
	controlFieldsVector.Add(controlField);
    }

ATTValVector<ControlField*> * Embedded::getControlFieldsVector() {
        return &controlFieldsVector;
    }

void Embedded::addDataField(void *dataField) { // DataField
	dataFieldsVector.Add(dataField);
    }

ATTValVector<void *> * Embedded::getDataFieldsVector() { // DataField
        return &dataFieldsVector;
    }




char* Embedded::toXml() {
	return "";
    }

