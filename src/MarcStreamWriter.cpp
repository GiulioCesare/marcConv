/*
 * MarcStreamWriter.cpp
 *
 *  Created on: 7-dic-2008
 *      Author: Arge
 */

#include "MarcStreamWriter.h"
#include "MarcRecord.h"
#include "MarcConstants.h"
#include "MarcGlobals.h"
#ifdef TRACK_MEMORY_LEAKS
    #include "nvwa/debug_new.h"
#endif


MarcStreamWriter::MarcStreamWriter() {
	init();
}


    /**
     * Constructs an instance and creates a <code>Writer</code> object with
     * the specified output stream.
     */
MarcStreamWriter::MarcStreamWriter(CFile * out) {
	init();
    this->out = out;
    encoding = "ISO8859_1";
    }
void MarcStreamWriter::init()
{
	fieldData = new CBufferedData();

	recordData = new CBufferedData();
	directoryData = new CBufferedData();
}

    /**
     * Constructs an instance and creates a <code>Writer</code> object with
     * the specified output stream and character encoding.
     */
MarcStreamWriter::MarcStreamWriter(CFile *out, char* encoding) {
	MarcStreamWriter();
	this->encoding = encoding;
    this->out = out;
    }

MarcStreamWriter::~MarcStreamWriter() {
	if (recordData)
		delete recordData;
	if (directoryData)
		delete directoryData;
	if (fieldData)
		delete fieldData;
}

//	void setConverter(CharConverter converter);
//	CharConverter getConverter();
//void MarcStreamWriter::close()
//{
//}


/**
 * Returns the character converter.
 *
 * @return CharConverter the character converter
 */
/*
  CharConverter MarcStreamWriter::getConverter() {
        return converter;
    }
*/
/**
 * Sets the character converter.
 *
 * @param converter
 *            the character converter
 */
/*
void MarcStreamWriter::setConverter(CharConverter converter) {
        this->converter = converter;
    }
*/








/**
 * Writes a <code>Record</code> object to the writer.
 *
 * @param record -
 *            the <code>Record</code> object
 */
bool MarcStreamWriter::write(MarcRecord* marcRecord) {
	bool retb;
//    long previous = 0;
//    ControlField *cf;
//    DataField *df; //, *df1
//    recordData->Reset();
//    directoryData->Reset();
//    CString dataElement; // entry,
//    CString directoryEntry;
//    char chr;
//
//        // Prepare CONTROL FIELDS
//        ATTValVector <ControlField*> *controlFields = marcRecord->getControlFieldsVector();
//        for (int i=0;i< controlFields->Length(); i++ )
//        {
//			cf = controlFields->Entry(i);
//			recordData->AddString(cf->getData());
//			recordData->AddChar(FIELD_TERMINATOR);
//
//			getEntry(cf->getTag(), (recordData->GetUsedBytes())- previous, previous, directoryEntry);
//			directoryData->AddString(directoryEntry.Data());
//			previous = recordData->GetUsedBytes();
//        }
//
//
//        // Prepare DATA FIELDS
//
//        ATTValVector <DataField*> *dataFields = marcRecord->getDataFieldsVector();
//        for (int i=0;i< dataFields->Length(); i++ )
//        {
//        	fieldData->Reset();
//
//			df = dataFields->Entry(i);
//			if (!df)
//				continue;
//			fieldData->AddChar(df->getIndicator1());
//			fieldData->AddChar(df->getIndicator2());
//
//
//
//			// Get SUBFIELDS
//            ATTValVector <Subfield*> *subfields =  df->getSubfields();
//            for (int j=0;j< subfields->Length(); j++ )
//            {
//                Subfield *sf = subfields->Entry(j);
//                getDataElement(sf->getData(), dataElement);
//				if (dataElement.Length() > 9999)
//				{
//					//printf ("\nCAMPO Troppo lungo (verra' escluso ESCLUSO) per aver superato max len di 9.999 bytes: Field %s, BID=%s, length=%ld", df->getTag(), controlFields->Entry(0)->getData(), dataElement.Length());
//					printf ("\nSUBFIELD Troppo lungo (viene troncato a max len di 9.999 bytes: Field %s, BID=%s, length=%ld", df->getTag(), controlFields->Entry(0)->getData(), dataElement.Length());
//					dataElement.Resize(9999); // 29/01/2010 12.33
//					// continue;
//				}
//   				if (fieldData->GetUsedBytes()+dataElement.Length() > 9990)
//				{
//					printf ("\nFIELD TRONCATO per aver superato max len di 9999 bytes: Field %s, BID=%s, length=%ld", df->getTag(), controlFields->Entry(0)->getData(), recordData->GetUsedBytes()+dataElement.Length());
//					break;
//				}
//                fieldData->AddChar(SUBFIELD_DELIMITER);
//                fieldData->AddChar(sf->getCode());
//				fieldData->AddBinaryData((OrsUChar*)dataElement.data(), dataElement.Length());
//            } // End for subfields
//            fieldData->AddChar(FIELD_TERMINATOR);
//
//			// Stiamo sforando?
//            getEntry(df->getTag(), recordData->GetUsedBytes()+fieldData->GetUsedBytes() - previous, previous, directoryEntry);
//			if ((directoryEntry.Length() % 12) != 0)
//			{
//				cf = controlFields->Entry(0);
//				printf ("\nRECORD TROPPO LUNGO. VIENE TRONCATO. SKIP OTHER RECORD FIELDS: invalid directory length: %ld instead of 12: Field %s, Record %s", directoryEntry.Length(), df->getTag(), cf->getData());
//				// return false;
//				break; // 29/01/2010 12.28 Scriviamo comunque un record parziale
//			}
//
//            // Aggiungiamo il campo al record
//            recordData->AddBinaryData((OrsUChar*)fieldData->Data(), fieldData->GetUsedBytes());
//
//            // Ricalcoliamo la directory entry
//            getEntry(df->getTag(), recordData->GetUsedBytes() - previous, previous, directoryEntry);
//
//			directoryData->AddString(directoryEntry.Data());
//			previous = recordData->GetUsedBytes();
//
//
//        } // End for datafields
//        directoryData->AddChar(FIELD_TERMINATOR);
//
//
//        // Prepare il LEADER
//        Leader *ldr = marcRecord->getLeader();
//        ldr->setBaseAddressOfData(24 + directoryData->GetUsedBytes());
//        ldr->setRecordLength(ldr->getBaseAddressOfData() + recordData->GetUsedBytes() + 1);
//        ldrStr = ldr->getLeader();


        retb = prepareRecordTowrite(marcRecord);
        if (!retb)
        	return retb;


//        //write(ldr);
//        out->Write(ldrStr->data(), ldrStr->Length());
//        out->Write(directoryData->Data(), directoryData->GetUsedBytes());
//        out->Write(recordData->Data(), recordData->GetUsedBytes());
//        chr = RECORD_TERMINATOR;
//        out->Write(chr);

        return writeToFile();
} // End write






long MarcStreamWriter::getWriteToFileRecordLength() {
	long length = ldrStr->Length();
	length += directoryData->GetUsedBytes();
	length += recordData->GetUsedBytes();
	length ++; // RECORD_TERMINATOR

	if (RECORDUNIMARCSUSINGOLARIGA == 1)
		length ++; // Linefeed

	return length;
}





//void MarcStreamWriter::getDataElement(char * data, CString & dataElement) { //  throws IOException
//	dataElement = data;
//} // End getDataElement


//
//void MarcStreamWriter::getEntry(char* tag, int length, int start, CString &entry) // throws IOException
//	{
//    char buf[20];
//	//return (tag + format4.format(length) + format5.format(start)).getBytes(encoding);
////    sprintf (buf, "%s%04d%05d", tag, length, start);
//
//    //entry= buf;
//    entry.assign (buf, 12);
//	} // End getEntry




bool MarcStreamWriter::prepareRecordTowrite(MarcRecord* marcRecord) {
    long previous = 0;
    const int leaderLength = 24;
    const int directoryEntryLength = 12;

    ControlField *cf;
    DataField *df; //, *df1
    Subfield *sf;
    recordData->Reset();
    directoryData->Reset();
    //CString dataElement; // entry,
    CString directoryEntry;
//    char *bid;
//    char chr;
    CString *sPtr;


    int len;
        // Prepare CONTROL FIELDS
        ATTValVector <ControlField*> *controlFields = marcRecord->getControlFieldsVector();
        for (int i=0;i< controlFields->Length(); i++ )
        {
			cf = controlFields->Entry(i);
//			if (!i)
//				bid = cf->getData()->Data();
			recordData->AddString(cf->getData());
			recordData->AddChar(FIELD_TERMINATOR);

			//getEntry(cf->getTag(), (recordData->GetUsedBytes())- previous, previous, directoryEntry);
			//directoryData->AddString(directoryEntry.Data());

			sprintf (buf, "%3s%04d%05d", cf->getTag(), recordData->GetUsedBytes() - previous, previous);
			//directoryEntry.assign (buf, 12);
			directoryData->AddBinaryData(buf, 12);

			previous = recordData->GetUsedBytes();
        }


        // Prepare DATA FIELDS

        ATTValVector <DataField*> *dataFields = marcRecord->getDataFieldsVector();

//printf ("\ndataFields->Length() = %d", dataFields->Length());

        for (int i=0;i< dataFields->Length(); i++ )
        {
        	fieldData->Reset();

			df = dataFields->Entry(i);
			if (!df)
				continue;
			fieldData->AddChar(df->getIndicator1());
			fieldData->AddChar(df->getIndicator2());



			// Get SUBFIELDS
            ATTValVector <Subfield*> *subfields =  df->getSubfields();
            for (int j=0;j< subfields->Length(); j++ )
            {
                sf = subfields->Entry(j);
                //getDataElement(sf->getData(), dataElement);
                sPtr = sf->getDataString();

				if (sPtr->Length() > 9999)
				{
					//printf ("\nCAMPO Troppo lungo (verra' escluso ESCLUSO) per aver superato max len di 9.999 bytes: Field %s, BID=%s, length=%ld", df->getTag(), controlFields->Entry(0)->getData(), dataElement.Length());
					fprintf (stderr, "\nSUBFIELD Troppo lungo (viene troncato a max len di 9.999 bytes: Field %s, BID=%s, length=%ld", df->getTagString()->data(), controlFields->Entry(0)->getData()->data(), sPtr->Length());
					sPtr->Resize(9999); // 29/01/2010 12.33
					// continue;
				}

   				if (fieldData->GetUsedBytes()+sPtr->Length() > 9990)
				{
					fprintf (stderr, "\nBID=%s - Field %s:  FIELD TRONCATO per aver superato max len di 9999 bytes,  length=%ld", controlFields->Entry(0)->getData()->data(), df->getTagString()->data(), recordData->GetUsedBytes()+sPtr->Length());
					break;
				}

                fieldData->AddChar(SUBFIELD_DELIMITER);
                fieldData->AddChar(sf->getCode());

				fieldData->AddBinaryData(sPtr->data(), sPtr->Length());

            } // End for subfields

            fieldData->AddChar(FIELD_TERMINATOR);

            // Stiamo sforando?
            // FIX per bug BVE PAL0040043 14/03/2011
            len = leaderLength + recordData->GetUsedBytes() + fieldData->GetUsedBytes() + directoryData->GetUsedBytes() + directoryEntryLength +1;
			if (len > 99900)
			{
				cf = controlFields->Entry(0);
				fprintf (stderr, "\nRECORD TROPPO LUNGO (Max 99999) per bid %s. VIENE TRONCATO!! Scaricati %d campi dati su %d. I %d campi rimanenti vanno persi.", cf->getData()->data(), i, dataFields->Length(), dataFields->Length()-i);
				break; // 14/03/2011
			}


            // Aggiungiamo il campo al record
            recordData->AddBinaryData(fieldData->Data(), fieldData->GetUsedBytes());

            // Ricalcoliamo la directory entry
//            getEntry(df->getTagString()->data(), recordData->GetUsedBytes() - previous, previous, directoryEntry);
//			directoryData->AddString(directoryEntry.Data());

			sprintf (buf, "%3s%04d%05d", df->getTagString()->data(), recordData->GetUsedBytes() - previous, previous);
//			directoryEntry.assign (buf, 12);
			directoryData->AddBinaryData(buf, 12);

			previous = recordData->GetUsedBytes();



//printf ("\nRecord data = %d", previous);

        } // End for datafields


        directoryData->AddChar(FIELD_TERMINATOR);

        // Prepare il LEADER
        Leader *ldr = marcRecord->getLeader();
        ldr->setBaseAddressOfData(leaderLength + directoryData->GetUsedBytes());
        ldr->setRecordLength(ldr->getBaseAddressOfData() + recordData->GetUsedBytes() + 1);
        ldrStr = ldr->getLeader();

        return true;
} // End prepareRecordTowrite



bool MarcStreamWriter::writeToFile() {
	bool retb;

	// 14/03/2011
	int recordLen = getWriteToFileRecordLength();
	if (recordLen > 99999)
	{
		fprintf (stderr, "\nRecord troppo lungo %d. Scartato!!", recordLen);
		return false;
	}

	retb = out->Write(ldrStr->data(), ldrStr->Length());
	if (!retb)
		return retb;
	retb = out->Write(directoryData->Data(), directoryData->GetUsedBytes());
	if (!retb)
		return retb;
	retb = out->Write(recordData->Data(), recordData->GetUsedBytes());
	if (!retb)
		return retb;
    char chr = RECORD_TERMINATOR;
    retb = out->Write(chr);


	if (RECORDUNIMARCSUSINGOLARIGA == 1)
	    retb = out->Write('\n');



    return retb;
}
