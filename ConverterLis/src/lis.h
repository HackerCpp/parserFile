#ifndef LIS_H_
#define LIS_H_

#include "common.h"

/* TIF block data write in usual byte order (low bite first), all other block inverted (high byte first) */

#pragma pack(push, 1)

typedef struct _TIFBlock
{
	uint32		tif_type;				/* (0) - record, (1) - end of file */
	uint32		prev_adr;				/* offset from the file begin for previous TIF block */
	uint32 		next_adr;				/* offset from the file begin for next TIF block */
} TIFBlock;

typedef struct _PhysicalRecordHeader
{
	uint16	length;						/* length of physical record per bytes */
	uint16	header;						/* see LIS documentation, it is 0 for us */
} PhRecHead;

typedef struct _LogicalRecordHeader
{
	uint8		type;					/* logical record type: for FileRecord (128) - header, (129) - trailer */
	uint8		reserved;				/* always zero */
} LRecHead;


#define CHAR2(c0, c1)     ((c0) | ((c1)<<8))

/* values of field Type of FileHeader structure */
	enum _FileType{
		LL		= CHAR2('L', 'L'),		/* Label */
		LO		= CHAR2('L', 'O'),		/* Log Data */
		LD		= CHAR2('L', 'D'),
		CA		= CHAR2('C', 'A'),		/* Calibration */
		SE		= CHAR2('S', 'E'),
		DE		= CHAR2('D', 'E'),
		BL		= CHAR2('B', 'L')
		};

typedef struct _FileRecord
{
	LRecHead	logic_rec_head;			/* logical record header */

	/* file header data */
	char8		file_name[10];			/* Service_Name[6] + '.' + File_Namber[3] */
	char8		space2[2];
	char8		sub_level[6];			/* Service Sub Level Name */
	char8		vers_soft[8];			/* Version number for the software that wrote the original data */
	char8		date_soft[8];			/* Date of generation for the software: Year[2]+'/'+Month[2]+'/'+Day[2] */
	char8		space;
	char8		max_rec_length[5];		/* Maximum physical record length */
	char8		space3[2];
	uint16		file_type;				/* see type _FileType above */
	char8		space4[2];
	char8		opt_file_name[10];		/* file name is optional : previous for header type, next for trailer if present */
} FileRecord;

typedef union _Datum{
	uint16		__1;	/* '1'(49) - 16-bit Floating Point (not working yet) */
	uint32		__2;	/* '2'(50) - 32-bit Low Resolution Floating Point (not working yet) */
	int8		_8;		/* '8'(56) - 8-bit signed integer */
	char8		A[4];	/* 'A'(65) - alphanumeric */
	uint8		B;		/* 'B'(66) - 8-bit unsigned integer */
	float32		D;		/* 'D'(68) - 32-bit Floating Point */
	uint32		__F;	/* 'F'(70) - 32-bit Fixed Point (not working yet) */
	int32		I;		/* 'I'(73) - 32-bit signed integer */
	int16		O;		/* 'O'(79) - 16-bit signed integer */

	char8		*str;	/* string pointer for some purpose */
} Datum;

typedef struct _ComponentBlock{
	uint8		type_number;				/* Type Number is number indicating the type of datum represented */
	char8		repr_code;					/* Representation Code is a number indicating a type of the datum */
	uint8		size;						/* Size is a number indicating the size in bytes reserved for the datum */
	uint8		category;					/* Category is undefined field */
	char8		mnemonic[4];				/* Mnemonic is the name of the datum */
	char8		units[4];					/* Units indicate the units of measurement for the datum */
	Datum		datum;						/* Datum is actual datum, represented in the Representation Code */
} ComponBlock;

typedef struct _EntryBlock{
	uint8		entry_type;					/* Entry Type is defined in special table, some values can be found in program code */
	uint8		size;						/* Size is a number indicating the size in bytes reserved for the datum */
	char8		repr_code;					/* Representation Code is a number indicating a type of the datum */
	Datum		datum;						/* Datum is actual datum, represented in the Representation Code */
} EntryBlock;

typedef struct _SpecBlock
{
	union{
	struct{
		char8	mnemonic[4];				/* Mnemonic is the name of channel */
		char8	service_id[6];				/* Service ID identified the tool (used to measured the datum) or the name of computed product */
		char8	serv_order_num[8];			/* Service Order Number is unique number which identifiers the logging trip to the well-site */
		char8	units[4];					/* Units indicate the unit measurement for the datum */
	};
		char8	str_data[22];
	};

	union{
	struct{
		char8	API_log_type;
		char8	API_curve_type;
		char8	API_curve_class;
		char8	API_modifier;
	};
		int32	API_code;
	};

	int16		file_number;
	int16		size;						/* Size is the number of bytes reserved for the datum in the frame */
	int16		zero;						/* reserved */
	char8		process_level;
	char8		number_samples;				/* Number Samples indicates the number of datum samples per frame (if it measured amount of times) */
	char8		repr_code;					/* Representation Code is a number indicating a type of the datum */
	uint8		process_indicators[5];		/* Process Indicators are used to designate the processing or corresponds performed of the datum (each bit - different computation) */
} SpecBlock;

#pragma pack(pop)

/* library version */
EXPORT_API const char8* version();
EXPORT_API const char8* init( GetFunction func );

#endif /* LIS_H_ */
