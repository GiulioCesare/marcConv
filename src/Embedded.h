/*
 * Embedded.h
 *
 *  Created on: 5-feb-2010
 *      Author: Arge
 */

#ifndef EMBEDDED_H_
#define EMBEDDED_H_

//#include "DataField.h"
#include "ControlField.h"

class Embedded {
	ATTValVector <ControlField *> controlFieldsVector;
	ATTValVector < void *> dataFieldsVector; // DataField
	void stop();

public:
	Embedded();
	virtual ~Embedded();

	void addControlField(ControlField *controlField);
	ATTValVector<ControlField*> * getControlFieldsVector();
	void addDataField(void  *dataField); // DataField
	ATTValVector<void *> * getDataFieldsVector(); // DataField
	char* toXml();

};

#endif /* EMBEDDED_H_ */
