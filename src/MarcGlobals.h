/*
 * MarcGlobals.h
 *
 *  Created on: 22-gen-2010
 *      Author: Arge
 *
 *
 *      Variabili globali contenenti parametrizzazioni
 *      NMB: Queste variabili vanno inizializzate una volta sola!!
 */

#ifndef MARCGLOBALS_H_
#define MARCGLOBALS_H_

// Valido per NON UTF
//#define NSB "\033H"// "{esc}H" // Not Sort Beginning
//#define NSE	"\033I" // "{esc}I" // No Sort Ending

// UNICODE
// 0xC298 NSB
// 0xC29C NSE
//#define NSB "\302\230"// "{esc}H" // Not Sort Beginning
//#define NSE	"\302\234" // "{esc}I" // No Sort Ending

extern CString NSB, NSE;
//		AUTHORITY,
//        IDXUNIMARC,
//        RETICOLO_OUT,
//        POLO,
//        DESCPOLO,
//        BIBLIOTECARICHIEDENTESCARICO,
//        MARKFILEOUT,
//        MARKFILEOUTTXT,
//        PROCESSLOG;
extern int	ISBN_CON_TRATTINI;
extern int 	RECORDUNIMARCSUSINGOLARIGA;
//extern long INIZIAELABORAZIONEDARIGA;
//extern bool POSITIONBYOFFSET;
//extern long ELABORANRIGHE=0;
//extern int 	LOGOGNIXRIGHE=0;
extern int 	DATABASE_ID;
extern int 	TIPO_SCARICO;
extern int 	TIPO_UNIMARC;
extern long	MARKFILEOUT_BUFFER_SIZE;
extern long	MARKFILEOUT_BUFFER_RESIZE_BY;

extern char *paddingZeroes [];
extern CString	BIBLIOTECARICHIEDENTESCARICO;
extern CString	FixedLengthLine;

//extern CString titoliErrati; // titoliCancellati, titoliFusi, titoliLocDaCanc, titoliUnimarc, titoliVariati, titoliUnimarcRidotto
//extern CFile *titoliErratiOut; //*titoliCancellatiOut, *titoliFusiOut, *titoliLocDaCancOut, *titoliUnimarcOut, *titoliUnimarcRidottoOut

// PER PROFILING
//extern long tbAppendStringCtr;

extern char *descTipoPeriodicita [];


extern char *tagsToGenerateBufferPtr;
#define IS_TAG_TO_GENERATE(tag) *(tagsToGenerateBufferPtr + tag)

#endif /* MARCGLOBALS_H_ */
