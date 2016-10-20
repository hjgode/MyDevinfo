/******************************************************************************/
// ODAX definitions, etc. for use by all source files
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>

// Expat includes and library
#define XML_STATIC
//#define XML_UNICODE_WCHAR_T

#include "..\\..\\Expat\\include\\expat.h"
#pragma comment (lib, "..\\..\\Expat\\bin\\expat.lib")

//#define throw
//#define Exception

//#define _MAX_PATH   260 /* max. length of full pathname */
#define _MAX_DRIVE  3   /* max. length of drive component */
#define _MAX_DIR    256 /* max. length of path component */
#define _MAX_FNAME  256 /* max. length of file name component */
#define _MAX_EXT    256 /* max. length of extension component */
#define _MAX_BUFF_LEN 2048 /* maximum length of buffer for CSV File Record*/

#include "../../Common/Private/odax/splitpath.h"

// Name of result set file.
#define RESULT_SET_FILENAME			"rset.dat"
#define TEMP_RESULT_SET_FILENAME	"temprset.dat"

// Name of temporary working files..
#define TEMP_XML_FILENAME	"tempxml.xml"
#define TEMP_CSV_FILENAME	"tempcsv.csv"
// (these files get created in the same dir as the db file)

#define EXCEPTION_MSG_BUF_SIZE 512

#include "../../Common/Private/odax/Tokens.h"
#include "../../Common/Private/odax/Exception.h"
#include "../../Common/Private/odax/Errors.h"
#include "../../Common/Private/odax/CString.h"
#include "../../Common/Private/odax/CList.h"
#include "../../Common/Private/odax/Unicode.h"

#define odd(x)		(x % 2 != 0)
#define even(x)	(!odd(x))
#define dim(x) (sizeof (x) / sizeof (x[0]))

enum enumInputType
	{
	XML_INPUT,
	CSV_INPUT
	};

#define DETERMINE_FORMAT_FROM_FILE	-1
#define XML_INPUT_FORMAT	0
#define CSV_INPUT_FORMAT	1

enum enumOutputType
	{
	XML_OUTPUT,
	CSV_OUTPUT,
	RESULT_SET_OUTPUT
	};

enum enumSqlStatementType
	{
	SQL_INSERT,
	SQL_DELETE,
	SQL_UPDATE,
	SQL_SELECT
	};

typedef CList<CString> CStringList;

#include "../../Common/Private/odax/CEvalResult.h"

#include "../../Common/Private/odax/CFile.h"
#include "../../Common/Private/odax/CRecord.h"
#include "../../Common/Private/odax/CExpr.h"

// Turn this into real class
struct CStatementData
	{
	CString SourceDbName;
	enumSqlStatementType StatementType;
	enumOutputType OutputType;
	CExpr *pCondition;
	CRecord *pCurrentResult;
	CRecord NewValues;			// <-- New. Added for UPDATE, may be able to use this for insert
										// also, instead of separate field/value lists.

	CFile TempDb;					// <-- New. TempDB in case of update or delete

	char Delimiter;				// Used by csv only..
	int FirstRow;					// Used by csv only..

	int ErrorNo;
	};

#include "../../Common/Private/odax/Xml.h"
#include "../../Common/Private/odax/Csv.h"
//#include "..\Expat\xmlparse.h"
#include "../../Common/Private/odax/CExpat.h"
#include "../../Common/Private/odax/CResultSet.h"
#include "../../Common/Private/odax/Output.h"
#include "../../Common/Private/odax/SQLParse.h"
