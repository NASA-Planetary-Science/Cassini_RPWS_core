
/*
 * autils.h  - audio utilities definitions for audio examples 
 */

#define USER_FORMAT_BASE    0x1000
#define USER_FORMAT_spl     USER_FORMAT_BASE + 1

/* STEP 1. ADD USER-DEFINED FORMAT CODES HERE */

/* search name table for match with name string */
extern int searchNameTable (

#ifdef __STDC__
                             char *pName, char *pTable[]
#endif

  );

/*   findFormat - convert file format string to file format code */
extern AFileFormat findFormat (

#ifdef __STDC__
                                char *pString
#endif

  );

/*   findDataFormat - convert data format string to data format code */
extern ADataFormat findDataFormat (

#ifdef __STDC__
                                    char *pString
#endif

  );

/* rate2num - convert sampling rate string to unsigned integer sampling rate */
extern unsigned long rate2num (

#ifdef __STDC__
                                char *rate
#endif

  );

/*   name2format - get sample rate & data format from filename */
extern int name2format (

#ifdef __STDC__
                         char *afile,
                         AFileFormat * pFormat, unsigned long *pSampleRate
#endif

  );

/*  printAudioError - print audio error text given error code */
extern void printAudioError (

#ifdef __STDC__
                              Audio * audio, char *message, int errorCode
#endif

  );
