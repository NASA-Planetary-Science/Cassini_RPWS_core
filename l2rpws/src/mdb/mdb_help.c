#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/****************************************************************************/
/* Compiled in config file directory locations */


static char *help_text[] = {
  "MDB_help() V1.0",
  "  ",
  "mY dATA bASE, routine to access the Cassini/RPWS",
  " level-1 data archive at the University of Iowa",
  "  ",
  "  This library consists of a set of routines that",
  "may be used to selectively access RPWS science and",
  "housekeeping telemetry.  The basic function is to",
  "access data from a selected time range.  Additional",
  "entry points are provided to narrow data selection.",
  "  ",
  "  Sample code for using the library may be ",
  "found in the source code to the mdb wrapper.",
  "See the help text for that routine for the",
  "path/filename to find the sample code.",
  "",
  "  This code attempts to get time right.  It uses SPICE",
  "(and friends) to convert a time string into SCLK that",
  "is then used to find the requested data through the database.",
  "This (we hope) makes these routines insensitive to where",
  "data is located; records can be place any file as long as",
  "the database has correct SCLK start/stop (i.e. errors in.",
  "the way time is decoded when the initial files are created",
  "(i.e. the r-files and the u-files) does not affect the way",
  "the mbd library retrieves them.",
  "",
  "\f",
  "Routines: (mdb.h)",
  "  ",
  "       struct MDB *MDB_open(char *start_time, ",
  "                             char *stop_time, ",
  "                             char *path, ",
  "                             char *name, ",
  "                             int packet_type);",
  "       struct MDB *MDB_rewind(struct MDB *mdb,",
  "                             int packet_type);",
  "       int MDB_close(struct MDB *mdb);",
  "     ",
  "       struct RPWS_buffer *MDB_read_all(struct MDB *mdb);",
  "       struct RPWS_buffer *MDB_read(struct MDB *mdb);",
  "       struct RPWS_buffer *MDB_read_stream(struct MDB *mdb, ",
  "                                           int stream);",
  "     ",
  "       int MDB_stat(struct MDB *mdb,",
  "                                           struct stat *stat_buf,",
  "                                           char *filename);",
  "     ",
  "       int MDB_time(char *time_string);",
  "       char *MDB_time_SCET(char *time_string);",
  "       double MDB_time_et(char *time_string);",
  "       int MDB_time_ver(void);",
  "       int MDB_time_verify(char *time_string);",
  "     ",
  "       int MDB_help(FILE *output);",
  "",
  "\f",
  "Data Definitions: (mdb.h)",
  "  ",
  "        There are several external data definitions",
  "      in the mdb library that are defined in the ",
  "      header file.",
  " ",
  "    extern char *MDB_Version",
  "        Version number string",
  "              MDB_VERSION",
  "                  #define that should match MDB_Version",
  "                  a mismatch indicates that the header file",
  "                  and the library file do not match (bad!!!)",
  " ",
  "    extern int   MDB_debug",
  "        Debug flag (enumerations follow)",
  "",
  "\f",
  "Data Structures: (mdb.h)",
  "  ",
  "        This is the MDB data structure as treated by user code.",
  "      In particular, only the link field at the begining of the",
  "      structure should be written.",
  " ",
  "    struct MDB {",
  "                       struct MDB         *link;",
  "                 const char               *database_name;",
  "                 const FILE               *database_file;",
  "                 const char               *database_detail_line;",
  "                 const char               *database_detail_line_previous;",
  "                 const char               *database_line;",
  "                 const char               *database_line_tokens[MDB_TOKENS];",
  "                 const char               *datafile_name;",
  "                 const FILE               *datafile_file;",
  "                 const int                mdb_packet_type;",
  "                 const int                database_start_sclk;",
  "                 const int                database_stop_sclk;",
  "                 const int                requested_start_sclk;",
  "                 const int                requested_stop_sclk;",
  "                 const int                current_sclk;",
  "                 short                    fine;",
  "                 unsigned char            part;",
  "                 unsigned char            RTI;",
  "                 const struct RPWS_BUFFER *buffer;",
  "                 const struct stat        status_buffer;",
  "                 const struct timeval     open_time;",
  "                 const struct timeval     read_time;",
  "                 int                      database_line_count;",
  "                }",
  " ",
  "    struct MDB_DETAIL {",
  "                 double   start_et;",
  "                 double   stop_et;",
  "                 int      start_sclk;",
  "                 int      stop_sclk;",
  "                 int      flags;",
  "                 char    *pathname;",
  "                 char    *filename;",
  "                 char    *detail_line;",
  "                 };",
  "",
  "\f",
  "File Select Enumerations: (mdb.h)",
  "        ",
  "          This set of enumerations are used to select the ",
  "        files that will be accessed by the read routines.",
  "        ",
  "          The R_FILE contains CDS packets as handled by the",
  "        spacecraft data system.  All of the other files",
  "        are instrument minipackets that have been decompressed",
  "        and resegmented for use by data analysis software.",
  "        ",
  "          Housekeeping telemetry resides exclusively within ",
  "        the R_FILE",
  "        ",
  "                MDB_R_FILE",
  "                MDB_U_FILE",
  "                MDB_H_FILE",
  "                MDB_S_FILE",
  "                MDB_L_FILE",
  "",
  "\f",
  "MDB_DETAIL flags definitions: (mdb.h)",
  "  ",
  "          These are the definitions for the bits in the",
  "        flags fields of the MDB_DETAIL data structure.",
  "        These may be used to determine what data is present",
  "        in each data file.",
  "  ",
  "                MDB_FLAGS_Stim",
  "                MDB_FLAGS_MFR",
  "                MDB_FLAGS_HFR",
  "                MDB_FLAGS_LP",
  "                MDB_FLAGS_LFDR",
  "                MDB_FLAGS_WFR",
  "                MDB_FLAGS_Dust",
  "                MDB_FLAGS_MRO",
  "                MDB_FLAGS_WBR",
  "                MDB_FLAGS_Fill",
  "",
  "\f",
  "Debugging enumerations: (mdb.h)",
  " ",
  "          These enumerations may be or-ed together into",
  "        the MDB_debug variable to control what debug",
  "        information is displayed (to <stderr>).  As you",
  "        might expect, loading MDB_debug with a zero ",
  "        disables the dispaly of debugging information.",
  " ",
  "                MDB_DEBUG_DATABASE     Database file open/clode",
  "                MDB_DEBUG_DATAFILE     Datafile file open/close",
  "",
  "          The version string that appears in the header file",
  "        matches the version string that appears in the library.",
  "        Application code can check that it is using matched ",
  "        header and library using the external variable and this",
  "        string.",
  " ",
  "                MDB_VERSION",
  "\f",
  "Record Select Enumerations: (rpws_status.h)",
  "  ",
  "          Within the U_FILE, the enumerations allow selection of",
  "        data from a particular receiver within the instrument.",
  "        If required, several streams may be open at the same time",
  "        to access the individual data streams to make accessing",
  "        concurrent data streams a littl easier.  (Note that individual",
  "        data streams always occur in increasing time order, multiple ",
  "        streams do not mantain this realtion ship.  See the RPWS UG/SOM",
  "        for the gory details.",
  "        ",
  "                DUST_packet_ID_value",
  "                HFR_packet_ID_value",
  "                LFDR_packet_ID_value",
  "                LP_packet_ID_value",
  "                MFR_packet_ID_value",
  "                MRO_packet_ID_value",
  "                STIM_packet_ID_value",
  "                WBR_packet_ID_value",
  "                WFR_packet_ID_value",
  "",
  "Include files:",
  "  ",
  "          These are the include files that contain the routine ",
  "        definitions and enumerations required to make use of",
  "        the MDB routines.",
  "        ",
  "             mdb.h",
  "             rtiu.h",
  "             util.h",
  "             rpws_status.h",
  "             cds_status.h",
  "             hsk_status.h",
  "             dcp_status.h",
  "             dust_status.h",
  "             hfr_status.h",
  "             lfdr_status.h",
  "             lp_status.h",
  "             mfr_status.h",
  "             mp_status.h",
  "             mro_status.h",
  "             stim_status.h",
  "             wbr_status.h",
  "             wfr_status.h",
  "",
  "\f",
  "Routines in detail:",
  "  ",
  "        Specifics and prerequisites on the use of the MDB routines.",
  "      ",
  "  spice initilization  <----------==========********** SPICE SPICE SPICE",
  "      ",
  "        The spice routines are used to convert SCET strings into",
  "      SCLK values used for searching the file.  We need spice in",
  "      order to be able to operate with both SCLK and SCET.  This",
  "      also results in time specifications returning data based on",
  "      current best estimate of time, so errors in SCLK/SCET that",
  "      may have been introduced when the data was received do not",
  "      affect data selection.",
  "      ",
  "        The user application is responsible for intializing the",
  "      spice routines with the current leap-seconds and the current",
  "      sclk kernels.",
  "      ",
  "        Also, note that the FORTRAN routines are used, due to a",
  "      problem with the c routines, so the appropriate linker",
  "      must be used as well as the appropriate spice library.",
  "      ",
  "        This example shows the use of ldpool, also consider",
  "      using the spice routine \"furnish\".",
  "      ",
  "      Sample SPICE initialization",
  "          ",
  "          static char *metafile = {\"$CAS_TIME_KERNELS\"};",
  "          ",
  "          furnsh_c(metafile);",
  "          ",
  "          MDB_open(start, stop, NULL, NULL, 0);",
  "  ",
  "\f",
  "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
  "  struct MDB *MDB_open(char *start_time, ",
  "                       char *stop_time, ",
  "                       char *path, ",
  "                       char *name, ",
  "                       int packet_type);",
  "      ",
  "    Purpose:",
  "      ",
  "        Allocate and intialize the data structures required",
  "      to access the instrument data.",
  "      ",
  "        This is the initilization call that establishes the ",
  "      start and stop times as well as the file that will be",
  "      selected for reading (i.e. RPWS minipackets or CDS packets).",
  "      ",
  "        Multiple streams may be open at any time.  Simply",
  "      call the open routine while keeping track of the the ",
  "      additional MDB structures.",
  "  ",
  "    Arguments:",
  "      ",
  "        The 1st. argument, 'start_time' is required and may be",
  "      either a SCET string that is acceptable to spice or a SCLK",
  "      string that is acceptable to spice or a hexadecimal SCLK string.",
  "      The hexadecimal SCLK string must be exactly 8 characters long.",
  "      ",
  "        The 2nd. argument is optional, supply a NULL if it is not used.",
  "      This is the stop time and is in the same format as the start time.",
  "      When this argument is not supplied, all data after the specified",
  "      start time is returned.",
  "      ",
  "        The 3rd. argument 'path' is the path name for the database ",
  "      index file.  This argument is optional, supply a NULL if it",
  "      is not used.  There is an appropriate defualt that is used",
  "      if nothing is supplied by the user.",
  "        This string must NOT have a trailing slash (i.e. it will ",
  "      be appended by the open function).",
  "      ",
  "        The 4th. argument 'name' is the name of the database index file.",
  "      As with the path, this argument is optional and must be a NULL",
  "      if it is not used.",
  "      ",
  "        The 5th argument is the 'file select enumeration' using ",
  "      one of the selections listed above.  If a ZERO is supplied",
  "      in this field, the selection will default to  returning",
  "      records from a U-file.",
  "      ",
  "    Return Value",
  "      ",
  "        The MDB structure is returned with most of the fields filled",
  "      in.  No data has been read yet so there is no data available.",
  " ",
  "        An invalid argument will result in the program terminating",
  "      (malformed start/stop time, for example).",
  "      ",
  " ",
  "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
  "  struct MDB *MDB_rewind(struct MDB *mdb,",
  "                       int packet_type);",
  "      ",
  "    Purpose:",
  "      ",
  "        Reset everything to the begining, same as close/open",
  "      was called.  This is to allow repeated reading of the files",
  "      to allow, for example, comparison of new version of files.",
  "  ",
  "    Arguments:",
  "      ",
  "        The 1st argument is the MDB structure.",
  "      ",
  "        The 2nd argument if the 'file select enumeration' using ",
  "      one of the selections listed above.  If a ZERO is supplied",
  "      in this field, the selection will default to  returning",
  "      records from a U-file.",
  "      ",
  "    Return Value",
  "      ",
  "        The MDB structure is returned with most of the fields filled",
  "      in.  No data has been read yet so there is no data available.",
  " ",
  "        An invalid argument (or other problem) will return",
  "      a NULL pointer.",
  "      ",
  " ",
  "\f",
  "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
  "  int MDB_close(struct MDB *mdb);",
  "      ",
  "    Purpose:",
  "      ",
  "        Deallocate the data structures used to access data.",
  "      ",
  "    Arguments:",
  "      ",
  "        The MDB structure of the stream that is no longer",
  "      to be used is supplied as the only argument to the",
  "      close routine.",
  "      ",
  "    Return Value",
  "      ",
  "        Always returns a zero.",
  "        Error condirtions are ignored (i.e. supplying an",
  "        invalid MDB structure).",
  " ",
  "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
  "  int MDB_time(char *time_string);",
  "      ",
  "    Purpose:",
  "      ",
  "        Convert SCLK/SCET string to binary SCLK.",
  "      ",
  "    Arguments:",
  "      ",
  "        Time String, a SCLK or SCET in appropriate format (i.e.",
  "      same format as with the MDB_open).",
  "      ",
  "    Return Value",
  "      ",
  "        Converted SCLK.",
  " ",
  "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
  "  char *MDB_time_ver(void);",
  "      ",
  "    Purpose:",
  "      ",
  "        Obtain mdb_time version.",
  "      ",
  "    Arguments:",
  "      ",
  "        None.",
  "      ",
  "    Return Value",
  "      ",
  "        Version string.",
  " ",
  "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
  "  char *MDB_time_SCET(char *time_string);",
  "      ",
  "    Purpose:",
  "      ",
  "        Return SCET for supplied time string.",
  "      ",
  "    Arguments:",
  "      ",
  "        See MDB_time_verify for valid time strings.",
  "      ",
  "    Return Value",
  "      ",
  "        SCET time string yyyy-dddThh:mm:ss.mmm",
  " ",
  "\f",
  "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
  "  double MDB_time_et(char *time_string);",
  "      ",
  "    Purpose:",
  "      ",
  "        Return et for supplied time string.",
  "        (SPICE uses thes time internally, it is",
  "         epoch J2000).",
  "      ",
  "    Arguments:",
  "      ",
  "        See MDB_time_verify for valid time strings.",
  "      ",
  "    Return Value",
  "      ",
  "        seconds since J2000 epoch (may be negative).",
  " ",
  "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
  "  int MDB_time_verify(char *time_string);",
  "      ",
  "    Purpose:",
  "      ",
  "        Check that the supplied time string is ",
  "      in the correct format (yyyy-dddThh:mm:ss).",
  "      ",
  "    Arguments:",
  "      ",
  "        Time string; UT, or SCLK:",
  "              yyyy-dddT                Minimum UT string",
  "              yyyy-dddThh:mm:ss.mmm    ",
  "              xxxxxxxx                 hex SCLK",
  "              1/dddddddddd:mmm         decimal SCLK",
  "      ",
  "    Return Value",
  "      ",
  "        If argument is valid, converts to SCLK seconds.",
  "        Invalid argument returns a ZERO.",
  "      ",
  " ",
  "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
  "  struct RPWS_buffer *MDB_read(struct MDB *mdb);",
  "  struct RPWS_buffer *MDB_read_all(struct MDB *mdb);",
  "  struct RPWS_buffer *MDB_read_stream(struct MDB *mdb, int stream);",
  "      ",
  "    Purpose:",
  "      ",
  "        Read the next data record in the selected time period.",
  "      There are currently no estimate of the time a data acquisition ",
  "      requires, selection being based solely on the event time ",
  "      contained in the CDS packet of minipacket.",
  "      ",
  "        MDB_read returns the data from the selected files that",
  "      is between the specified start and stop times.",
  "      ",
  "        MDB_read_all return all the data in the selected files.  Files",
  "      being selected based on the start and stop times.  Data that",
  "      appears before and after the selected period is returned.",
  "      For processed files, this results in up to 1 hour of extra",
  "      records at the begining and up to 1 hour of data at the end.",
  "      For real-time files, the files are collected in 6 hour",
  "      periods so the worst case rises to 6 hours.",
  "      ",
  "        MDB_read_stream is similar to MDB_read in that only those",
  "      records that are between start and stop are returned.",
  "      In addition, this routine returns only those records that",
  "      match the 'record select enumeration' supplied as the",
  "      2nd. argument.",
  "      ",
  "    Arguments:",
  "      ",
  "        The 1st. argument is an MDB structure.  This is the data",
  "      structure returned from MDB_open.",
  "      ",
  "        The 2nd. argument, used only in the MDB_read_stream, specifies",
  "      the type of data record to be returned.  The value used here",
  "      is from the list of 'record select enumerations' from above.",
  "      The MDB_read_stream then returns only the data of the selected",
  "      type only for the selected period.  Note that it is possible to",
  "      change the selection with each call, but there is no way to ",
  "      backup the data pointers to scan discarded data.",
  "      ",
  "    Return Value",
  "      ",
  "        The address of an RPWS_buffer data structure if there is",
  "      data available.  NULL if no more data is available.",
  "      ",
  "        Note that there is a single RPWS_buffer allocated and",
  "      addressed through the MDB structure.  Each successive call",
  "      to read data overwrite previous data.",
  " ",
  "\f",
  "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
  "  int MDB_stat(struct MDB *mdb,",
  "               struct stat *stat_buf,",
  "               char *filename);",
  "      ",
  "    Purpose:",
  "      ",
  "        Obtain a stat buffer for the next file.  This is ",
  "      intended to provide a method to scan files that cover",
  "      the period prescribed in the MDB_open call.  This entry",
  "      should be called repeatedly to obtain status on each",
  "      succeding file.",
  "        Calling this routine advances the file pointer",
  "      to the next record in the database (it should not",
  "      be called on the same stream used by any of the",
  "      read routines.",
  "      ",
  "    Arguments:",
  "      ",
  "        The 1st. argument is an MDB structure.  This is the data",
  "      structure returned from MDB_open.",
  "      ",
  "        The 2nd. argument is the address of a status buffer",
  "      returned by the system call 'stat' (man -s2 stat).",
  "      The calling program is responsible for allocating",
  "      sufficient space to hold the data as it is copied into",
  "      the calling routines buffer.",
  "      ",
  "        The 3rd. argument, also allocated by the calling routine",
  "      will receive the filename this status buffer refers to.",
  "      This fielname has all of the path information stripped",
  "      (although all of the information stored in the MDB structure",
  "      may still be accessed.",
  "      ",
  "    Return Value",
  "      ",
  "        A value of 1 is returned as long as files remain to",
  "      be scanned.  A value of 0 is returned when no more",
  "      files remain to be processed.",
  "        Calling this routine advances the file pointer",
  "      to the next record in the database (it should not",
  "      be called on the same stream used by any of the",
  "      read routines.",
  " ",
  "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
  "  struct MDB_DETAIL *MDB_detail(struct MDB *mdb);",
  "      ",
  "    Purpose:",
  "      ",
  "        Obtain detail line from database, decoded and",
  "      ready to use.  As with MDB_stat, this provides a",
  "      method to access the detail lines of the database.",
  "  ",
  "    Arguments:",
  "      ",
  "        The 1st. argument is an MDB structure.  This is the data",
  "      structure returned from MDB_open.",
  "      ",
  "    Return Value",
  "      ",
  "        A pointer to an MDB_DETAIL structure that has",
  "      been allocated and loaded with the information from",
  "      the next detail line in the database file.",
  "        A NULL pointer is returned when no more data is",
  "      available in the requested time period.",
  "      ",
  "        Note that there is only a single MDB_DETAIL structure",
  "      allocated.  Subsequent calls overwrite/update the",
  "      MDB_DETAIL structure with new data.",
  " ",
  "\f",
  "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
  "  int MDB_help(FILE *output);",
  "      ",
  "    Purpose:",
  "      ",
  "        Dump the text you see here.",
  "      This documentation baggage is carried with the",
  "      program if you add a call to this module.",
  "  " "        you can always leave the call to MDB_help() out",
  "      an obtain a copy of this text from the mdb utility.",
  "  ",
  "    Arguments:",
  "      ",
  "        File descriptor, typically <stdout>).",
  "      ",
  "    Return Value",
  "      ",
  "        Line count.  The number of lines of text in this",
  "      help file.",
  "      ",
  "",
  "\f",
  "MDB structure in detail:",
  "      ",
  "        This is a description of the fields within the MDB data",
  "      structure.  User code should treat all of these fields",
  "      as read-only.  Altering the FILE structures can cause",
  "      catastrophic problems.  Altering other fields will probably",
  "      not affect processing as they are updated and used as needed",
  "      with each call to the read routines.",
  "        The fields may become read-only in a future update to the",
  "      mdb.h file.",
  "      ",
  "    struct MDB         *link;",
  "      ",
  "        Reserved for user code.  Provided to allow",
  "      creation of linked lists of MDB structures.",
  "        This pointer is cleared (set to NULL) when the",
  "      MDB_open call allocates memory for the data structure.",
  "      ",
  "    char               *database_name;",
  "      ",
  "        Full filename of the database index file.",
  "      User code should not modify this string.  There",
  "      are provisions in the MDB_open to provide user",
  "      supplied strings for this filename.",
  "      ",
  "    FILE               *database_file;",
  "      ",
  "        File handle for the database index file.",
  "      ",
  "    char               *database_detail_line;",
  "      ",
  "        Storage area for each line of the database file.  This",
  "      string is complete (unaltered by tokenizing).",
  "      ",
  "    char               *database_detail_line_previous;",
  "      ",
  "        Previous line from database.  Used for debugging problems",
  "      in the database.",
  "      ",
  "    char               *database_line;",
  "      ",
  "        Storage are for each line of the database file.  This",
  "      string may be broken into tokens.",
  "      ",
  "    char               *database_line_tokens[MDB_TOKENS];",
  "      ",
  "        String pointers to the tokens that make up the detail",
  "      line from the database index file.",
  "              [0]        SCLK start",
  "              [1]        SCLK stop",
  "              [2]        SCET start",
  "              [3]        SCET stop",
  "              [4]        Filename of U-File",
  "              [5]        Receiver flags",
  "        Note that the filname in the database index is that of the",
  "      U-File with other filenames being derived from this (i.e. ",
  "      substitute \"r00\" for \"u00\" to get CDS records)."
    "        This substitution will fail if the other files do not reside"
    "      in the same directory as the u-file, or if they aren't named",
  "      \"r00\", \"s00\", \"h00\"... etc.",
  "      ",
  "        Receiver flags is an indication of what type of data is",
  "      present in this U-File.",
  "      Bit definitions for these flags may be found in the",
  "      header file 'CasTlmDef.h.  They all start with CasSci",
  "      ",
  "    char               *datafile_name;",
  "      ",
  "        Full filename of the currently open data file.  This filename",
  "      has been modified to reflect the 'file select'.",
  "      ",
  "    FILE               *datafile_file;",
  "      ",
  "        File handle for the data file.  This is the file from which",
  "      the data records are obtained.",
  "      ",
  "    int                mdb_packet_type;",
  "      ",
  "        This is the 5th. argument to the MDB_open routine.  It is",
  "      used internally to control the method used to extract the",
  "      event SCLK from the data records (CDS packets and MP packets",
  "      require slightly different methods to arrive at the event",
  "      SCLK).",
  "      ",
  "    int                database_start_sclk;",
  "      ",
  "        From the database index detail line, database_line_tokens[0]",
  "      converted to an integer.",
  "      ",
  "    int                database_stop_sclk;",
  "      ",
  "        From the database index detail line, database_line_tokens[1]",
  "      converted to an integer.",
  "      ",
  "    int                requested_start_sclk;",
  "      ",
  "        From MDB_open, the selected start time is converted to",
  "      an integer and store here.",
  "      ",
  "    int                requested_stop_sclk;",
  "      ",
  "        Zero indicates no stop time selected, otherwise stop time",
  "      converted to an integer.",
  "      ",
  "    int                current_sclk;",
  "      ",
  "        Event clock from current data record.  For CDS packets this",
  "      is the upper 32 bits of SCLK.  For MP records, the 40 bit SCLK",
  "      and the 16 bit RTI number are combined to arrive at the 35",
  "      bit event SCLK (i.e. 32 bits of second and 3 bits of RTI, the).",
  "      upper 32 bit of which are stored here).",
  "      ",
  "    short              current_fine;",
  "      ",
  "        Event clock from current data record.  This is the sub-seconds",
  "      field of the SCLK.  RTI number is in bits 7..5 so this number",
  "      runs from 0 through 255 (in steps of 32).",
  "      ",
  "    unsigned char      current_part;",
  "      ",
  "        Event clock partition from current data record.  Clock",
  "      Partition number increments if the spacecraft clock is",
  "      restarted.  Nominally this contains a value of 1.",
  "      ",
  "    unsigned char      current_RTI;",
  "      ",
  "        Event clock from current data record.  RTI number.",
  "      The RTI counter runs from 0 through 7, incrementing",
  "      once every 125 mSec.",
  "      ",
  "    struct RPWS_BUFFER *buffer;",
  "      ",
  "        Pointer to an area of memory allocated by MDB_open to hold",
  "      the data that is read from the data file.  Enough space is",
  "      allocated to hold the largest minipacket that we can encounter.",
  "      ",
  "    struct stat        status_buffer;",
  "      ",
  "        Result of 'stat' system call performed on the data file.",
  "      This contains thgings such as file size and last access.",
  "      See 'man -s2 stat' for details.",
  "      ",
  "    struct timeval     open_time;",
  "      ",
  "        Storage are for 'gettimeofday(&open_time)' call performed",
  "      when MDB_open called.",
  "      ",
  "    struct timeval     read_time;",
  "      ",
  "        Storage are for 'gettimeofday(&open_time)' call performed",
  "      when any of the MDB_read* routines are called the first time.",
  "      ",
  "        The difference 'read_time - open_time' may be used to asses",
  "      the speed with which we are accessing the database index file.",
  "      ",
  "",
  "\f",
  "MDB_DETAIL structure in detail:",
  "      ",
  "        This is a description of the fields within the MDB_DETAIL",
  "      data structure.  User code should treat all of these fields",
  "      as read-only, although altering the fields is benign.",
  "        These fields may become read-only in a future update to the",
  "      mdb.h file.",
  "      ",
  "    double             start_et;",
  "      ",
  "        Time of first record in the indicated file.",
  "      SCET expressed in seconds since J2000 epoch",
  "      ",
  "    double             stop_et;",
  "      ",
  "        Time of last record in the indicated file.",
  "      SCET expressed in seconds since J2000 epoch",
  "      ",
  "    int                start_sclk;",
  "      ",
  "        Time of first record in the indicated file.",
  "      SCLK expressed in seconds.",
  "      ",
  "    int                stop_sclk;",
  "      ",
  "        Time of last record in the indicated file.",
  "      SCLK expressed in seconds.",
  "      ",
  "    int                flags;",
  "      ",
  "        File contents flag.  ",
  "      Bits are set to indicate which type of packets are",
  "      present in the U-FILE.",
  "      ",
  "    char               *pathname;",
  "      ",
  "        Path to data file.",
  "      No trailing slash.",
  "      ",
  "    char               *filename;",
  "      ",
  "        Data File name.",
  "      ",
  "    char               *detail_line;",
  "      ",
  "        Detail line from database file.",
  "      ",
  "",
  NULL
};

int MDB_help (FILE * output)
{
  int i = 0;

  while (help_text[i]) {
    if (help_text[i][0])
      fputs (help_text[i], output);
    fputc ('\n', output);
    i++;
  }
  return i;
}
