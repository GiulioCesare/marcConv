/*
 * ReadMarcExample.h
 *
 *  Created on: 10-dic-2008
 *      Author: Arge
 */

#ifndef READMARCEXAMPLE_H_
#define READMARCEXAMPLE_H_

#include "library/CFile.h"

class ReadMarcExample {
public:
	ReadMarcExample();
	virtual ~ReadMarcExample();
	void read(char *filename);

};

#endif /* READMARCEXAMPLE_H_ */
