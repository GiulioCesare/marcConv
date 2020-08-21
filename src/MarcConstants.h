/****************************************************************************
* Module  : MarcCostants.h                                                  *
* Author  : Argentino Trombin                                               *
* Desc.   :                                                                 *
* Date    :                                                                 *
****************************************************************************/
#ifndef __MARC_CONSTANTS_H__
#define __MARC_CONSTANTS_H__


#define RECORD_TERMINATOR 		0x1D		// GS Group Separator
#define FIELD_TERMINATOR 		0x1E		// RS Record Separator
#define SUBFIELD_DELIMITER 		0x1F		// US Unit Separator
#define BLANK 					0x20		// BLANK
#define NS_URI 					"http://www.loc.gov/MARC21/slim" // MARCXML_NS_URI
#define MARC_8_ANSEL_ENCODING 	"MARC8" 		// MARC_8_ENCODING
#define ISO5426 ENCODING 		"ISO5426" 	// ISO5426_ENCODING
#define ISO6937 ENCODING 		"ISO6937" 	// ISO6937_ENCODING

#define INDICATOR_UNDEFINED    ' '
#define INDICATOR_FILLER    '|'
#define FILLER    '|'
#define BID_LENGTH	10


// Valido per NON UTF
//#define NSB "\033H"// "{esc}H" // Not Sort Beginning
//#define NSE	"\033I" // "{esc}I" // No Sort Ending

// UNICODE
// 0xC298 NSB
// 0xC29C NSE
//#define NSB "\302\230"// "{esc}H" // Not Sort Beginning
//#define NSE	"\302\234" // "{esc}I" // No Sort Ending




#define ENCODING_ISO8859_1 '#'
#define ENCODING_UTF8 'a'


#define TP_MATERIALE_CARTOGRAFICO_C 	'C'
#define TP_MATERIALE_GRAFICO_G		'G'
#define TP_MATERIALE_ANTICO_E			'E'
#define TP_MATERIALE_MODERNO_M		'M'
#define TP_MATERIALE_MUSICA_U			'U'


// Codici natura
#define NATURA_A_TITOLO_DI_RAGGRUPPAMENTO_CONTROLLATO       'A' // Titolo uniforme
#define NATURA_B_TITOLO_DI_RAGGRUPPAMENTO_NON_CONTROLLATO   'B'
#define NATURA_C_COLLANA                                    'C'
#define NATURA_D_TITOLO_SVILUPPATO_O_ESTRAPOLATO            'D'
#define NATURA_M_MONOGRAFIA                                 'M'
#define NATURA_N_TITOLO_ANALITICO                           'N' // Spoglio?
#define NATURA_P_TITOLO_PARALLELO                           'P'
#define NATURA_S_PERIODICO                                  'S'
#define NATURA_T_TITOLO_SUBORDINATO                         'T'
#define NATURA_W_VOLUME_PRIVO_DI_TITOLO_SIGNIFICATIVO       'W'


#define AUTHORITY_DOCUMENTO	1
#define AUTHORITY_AUTORI	2
#define AUTHORITY_SOGGETTI	3
#define AUTHORITY_CLASSI	4
#define _TITOLO_UNIFORME	5

// CODICI COLLEGAMENTI (LEGAMI) Pag. 112 del Verdone
#define CD_LEGAME_01_FA_PARTE_DI										"01"
#define CD_LEGAME_02_SUPPLEMENTO_DI										"02"
#define CD_LEGAME_03_CONTIENE_ANCHE										"03"
#define CD_LEGAME_04_CONTINUAZIONE_DI									"04"
#define CD_LEGAME_4_CONTINUAZIONE_DI									'4'
#define CD_LEGAME_05_EDIZIONE_SUCCESSIVA_DI								"05"
#define CD_LEGAME_06_HA_PER_TITOLO_DI_RAGGRUPPAMENTO_NON_CONTROLLATO	"06" // Titolo uniforme
#define CD_LEGAME_07_ALTRA_EDIZIONE_DI									"07"
#define CD_LEGAME_08_HA_PER_ALTRO_TITOLO								"08"
#define CD_LEGAME_09_HA_PER_TITOLO_DI_RAGGRUPPAMENTO_CONTROLLATO		"09" // Titolo uniforme
#define CD_LEGAME_41_ASSORBE											"41"
#define CD_LEGAME_42_SI_FONDE_CON										"42"
#define CD_LEGAME_43_CONTINUAZIONE_PARZIALE_DI							"43"
#define CD_LEGAME_51_COMPRENDE											"51" // M comprende W si legge W 01 M


// Codice del numero standard o identificativo
// Da tb_codici.tp_tabella NSTD
#define TP_NUMERO_STANDARD_B_BNI 							'B'
#define TP_NUMERO_STANDARD_C_CATALOGHI_COLLETTIVI_STRANIERI 'C'
#define TP_NUMERO_STANDARD_D_BIBLIOGRAFIE_STRANIER 			'D'
#define TP_NUMERO_STANDARD_E_NUMERO_EDITORIALE 				'E'
#define TP_NUMERO_STANDARD_G_N_PUBBLICAZIONE_GOVERNATIVA	'G'
#define TP_NUMERO_STANDARD_I_ISBN 							'I'
#define TP_NUMERO_STANDARD_J_ISSN 							'J'

#define TP_NUMERO_STANDARD_K_ISBN_978 						'K'

#define TP_NUMERO_STANDARD_L_NUMERO_DI_LASTRA 				'L'
#define TP_NUMERO_STANDARD_M_ISMN 							'M'

#define TP_NUMERO_STANDARD_N_ISBN_979 						'N'

#define TP_NUMERO_STANDARD_P_ACNP 							'P'
#define TP_NUMERO_STANDARD_R_CRP 							'R'
#define TP_NUMERO_STANDARD_S_BOMS 							'S'
#define TP_NUMERO_STANDARD_U_CUBI 							'U'
#define TP_NUMERO_STANDARD_X_RISM 							'X'
#define TP_NUMERO_STANDARD_Y_SARTORI 						'Y'


#define LIVELLO_GERARCHICO_0_SENZA_LIVELLI_E_PERIODICI	'0'
#define LIVELLO_GERARCHICO_1_SUPERIORE					'1'
#define LIVELLO_GERARCHICO_2_INTERMEDIA_O_INFERIORE		'2'

// CODICI GENERE GEPU


// CODICI di RESPONSABILITA'
#define TP_RESP_0_NOME_CITATO_NEL_DOCUMENTO					'0'
#define TP_RESP_1_RESPONSABILITA_PRINCIPALE					'1'
#define TP_RESP_2_RESPONSABILITA_ALTERNATIVA				'2'
#define TP_RESP_3_RESPONSABILITA_SECONDARIA					'3'
#define TP_RESP_4_RESPONSABILITA_NELLA_PRODUZIONE_MATERIALE	'4'


// LEGAMI TITOLO AUTORE (indice LETA)


// Punteggiatura ISBD
#define PUNTEGGIATURA_AREA_TITOLO_INIZIO_TITOLO_PARALLELO " = "
#define PUNTEGGIATURA_AREA_TITOLO_INIZIO_COMPLEMENTO_TITOLO " : "
#define PUNTEGGIATURA_AREA_TITOLO_INIZIO_PRIMA_FORMULAZIONE_RESPONSABILITA " / "
#define PUNTEGGIATURA_AREA_TITOLO_INIZIO_SUCCESSIVA_FORMULAZIONE_RESPONSABILITA " ; "
#define PUNTEGGIATURA_AREA_TITOLO_INIZIO_DESIGANZIONE_MATERIALE " ["
#define PUNTEGGIATURA_AREA_TITOLO_FINE_DESIGANZIONE_MATERIALE "]"
#define PUNTEGGIATURA_AREA_TITOLO_INIZIO_TITOLO_AUTORE_DIVERSO " . "
#define PUNTEGGIATURA_AREA_TITOLO_INIZIO_ALTRO_TITOLO_STESSO_AUTORE " ; "

#define PUNTEGGIATURA_AREA_TITOLO_INIZIO_QUALIFICAZIONE "<"
#define PUNTEGGIATURA_AREA_TITOLO_FINE_QIALIFICAZIONE ">"

#define STATO_INIZIO_TITOLO								1
#define STATO_IN_DESIGANZIONE_MATERIALE					2
#define STATO_IN_TITOLO_PARALLELO 						3
#define STATO_IN_COMPLEMENTO_TITOLO 					4
#define STATO_IN_PRIMA_FORMULAZIONE_RESPONSABILITA		5
#define STATO_IN_SUCCESSIVA_FORMULAZIONE_RESPONSABILITA	6
#define STATO_IN_QUALIFICAZIONE							7


// Tipo di digitalizzazione della copia (tb_codici.tp_abella CDIG)
#define TIPO_DIGITALIZZAZIONE_PARZIALE 		0
#define TIPO_DIGITALIZZAZIONE_COMPLETA 		1
#define TIPO_DIGITALIZZAZIONE_BORN_DIGITAL	2
#define TIPO_DIGITALIZZAZIONE_SCONOSCIUTA 	?



// POLI
#define POLO_SCONOSCIUTO	0
#define POLO_AQ1        1
#define POLO_BA1        2
#define POLO_BIA        3
#define POLO_BVE        4
#define POLO_CAM        5
#define POLO_CFI        6
#define POLO_CSA        7
#define POLO_IEI        8
#define POLO_INDICE     9
#define POLO_LIG        10
#define POLO_MIL        11
#define POLO_MO1        12
#define POLO_PA1        13
#define POLO_PAL        14
#define POLO_RML        15
#define POLO_RMR        16
#define POLO_SBR        17
#define POLO_SBW        18
#define POLO_SNT        19
#define POLO_TER        20
#define POLO_TO3        21 // 09/03/2011
#define POLO_UM1        22
#define POLO_UM2        23
#define POLO_TEL        24 // 16/06/2015



// DATABASE DA DOVE SONO STATI ESTRATTI I DATI
#define DATABASE_SBNWEB	1
#define DATABASE_INDICE	2

#define TIPO_SCARICO_UNIMARC 1
#define TIPO_SCARICO_OPAC 2

#define TIPO_UNIMARC_STANDARD 1
#define TIPO_UNIMARC_RIDOTTO 2



#endif // __MARC_CONSTANTS_H__

