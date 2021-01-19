/*
	Directory Opus 9 VFS Plugins
	Header File

	(c) Copyright 2009 GP Software
	All Rights Reserved
*/

#ifndef DOPUS_VFSPLUGINS
#define DOPUS_VFSPLUGINS

// Current version - define VFSPLUGINVERSION when including this file to use an older version
// of the SDK
// Version 1 of the SDK corresponds to Directory Opus 8
// Version 2 corresponds to Directory Opus 9
// Version 3 corresponds to 9.1
#ifndef VFSPLUGINVERSION
#define VFSPLUGINVERSION	3
#endif


// Plugin information (VFS_Identify)
typedef struct DOpusVFSPluginInfoW
{
	UINT		cbSize;						// Structure size
	GUID		idPlugin;					// Unique identifier for this plugin
	DWORD		dwVersionHigh;				// Version (high)
	DWORD		dwVersionLow;				// Version (low)
	DWORD		dwFlags;					// Flags
	DWORD		dwCapabilities;				// Plugin capabilities
	LPWSTR		lpszHandlePrefix;			// File path prefix the plugin handles, eg "http://"
	LPWSTR		lpszHandleExts;				// File extensions the plugin handles, eg ".xxx;.yyy;.zzz"
	LPWSTR		lpszName;					// Plugin name
	LPWSTR		lpszDescription;			// Plugin description string, eg "Directory Opus RAR Handler"
	LPWSTR		lpszCopyright;				// Copyright string, eg "(c) 2001 GP Software"
	LPWSTR		lpszURL;					// Reference URL, eg "http://www.gpsoft.com.au"
	UINT		cchHandlePrefixMax;			// Max. length of buffer
	UINT		cchHandleExtsMax;			// Max. length of buffer
	UINT		cchNameMax;					// Max. length of buffer
	UINT		cchDescriptionMax;			// Max. length of buffer
	UINT		cchCopyrightMax;			// Max. length of buffer
	UINT		cchURLMax;					// Max. length of buffer
#if ( VFSPLUGINVERSION >= 2 )
	DWORD		dwOpusVerMajor;				// Opus major version
	DWORD		dwOpusVerMinor;				// Opus minor version
	DWORD		dwInitFlags;				// Initialisation flags
	HICON		hIconSmall;					// Small icon (Opus will call DestroyIcon on this)
	HICON		hIconLarge;					// Large icon (Opus will call DestroyIcon on this)
#endif
} VFSPLUGININFOW, * LPVFSPLUGININFOW;

typedef struct DOpusVFSPluginInfoA
{
	UINT		cbSize;
	GUID		idPlugin;
	DWORD		dwVersionHigh;
	DWORD		dwVersionLow;
	DWORD		dwFlags;
	DWORD		dwCapabilities;
	LPSTR		lpszHandlePrefix;
	LPSTR		lpszHandleExts;
	LPSTR		lpszName;
	LPSTR		lpszDescription;
	LPSTR		lpszCopyright;
	LPSTR		lpszURL;
	UINT		cchHandlePrefixMax;
	UINT		cchHandleExtsMax;
	UINT		cchNameMax;
	UINT		cchDescriptionMax;
	UINT		cchCopyrightMax;
	UINT		cchURLMax;
#if ( VFSPLUGINVERSION >= 2 )
	DWORD		dwOpusVerMajor;
	DWORD		dwOpusVerMinor;
	DWORD		dwInitFlags;
	HICON		hIconSmall;
	HICON		hIconLarge;
#endif
} VFSPLUGININFOA, * LPVFSPLUGININFOA;

#ifdef UNICODE
#define VFSPLUGININFO	VFSPLUGININFOW
#define LPVFSPLUGININFO	LPVFSPLUGININFOW
#else
#define VFSPLUGININFO	VFSPLUGININFOA
#define LPVFSPLUGININFO	LPVFSPLUGININFOA
#endif


// VFSPLUGININFO initialisation flags
#if ( VFSPLUGINVERSION >= 2 )
#define VFSINITF_FIRSTTIME						(1<<0)	// First time this plugin has been initialised
#define VFSINITF_USB							(1<<1)	// Opus is running in USB mode
#define VFSINITF_NOINIT							(1<<2)	// VFS_Init *may not* have been called for the plugin. Set when VFS_Identify called to get plugin's name for list of plugins available for USB export.
#define VFSINITF_NOSUPPORT						(1<<3)	// The plugin support API is unavailable. (Exception: GetString *may* still be available.) Set when VFS_Identify called to get 32-bit plugin's name for 64-bit Opus. The call comes via a simple proxy process which does not provide the plugin support API. This situation occurs when 64-bit Opus is building the list of available plugins for a 32-bit USB export.
#endif


// Plugin flags
#define VFSF_CANCONFIGURE						(1<<0)
#define VFSF_CANSHOWABOUT						(1<<1)
#define VFSF_MULTIPLEFORMATS					(1<<2)
#if ( VFSPLUGINVERSION >= 2 )
#define VFSF_NONREENTRANT						(1<<3)
#endif

// Capabilities flags
// Note that not all values in the 32-bit bitmask are used here, however
// they are used internally by Opus and so must NOT be set. They may be
// documented in a future version of this API.
#define VFSCAPABILITY_MOVEBYRENAME				(1<<0)
#define VFSCAPABILITY_COPYINDEFINITESIZES		(1<<5)
#define VFSCAPABILITY_CANRESUMECOPIES			(1<<6)
#define VFSCAPABILITY_TRIGGERRESUME				(1<<7)
#define VFSCAPABILITY_POSTCOPYREREAD			(1<<8)
#define VFSCAPABILITY_CASESENSITIVE				(1<<9)
#define VFSCAPABILITY_RANDOMSEEK				(1<<11)
#define VFSCAPABILITY_FILEDESCRIPTIONS			(1<<13)
#define VFSCAPABILITY_ALLOWMUSICCOLUMNS			(1<<14)
#define VFSCAPABILITY_ALLOWIMAGECOLUMNS			(1<<15)
#define VFSCAPABILITY_ALLOWEXTRADATECOLUMNS		(1<<16)
#define VFSCAPABILITY_LETMEDOPARENTS			(1<<17)
#define VFSCAPABILITY_COMBINEDPROPERTIES		(1<<19)
#define VFSCAPABILITY_COMPARETIMENOSECONDS		(1<<21)
#define VFSCAPABILITY_GETBATCHFILEINFO			(1<<23)
#define VFSCAPABILITY_SLOW						(1<<24)
#define VFSCAPABILITY_MULTICREATEDIR			(1<<26)
#define VFSCAPABILITY_ALLOWFILEHASH				(1<<28)
#define VFSCAPABILITY_READONLY					(1<<29)
#define VFSCAPABILITY_CHECKAVAILONDIRCHANGE		(1<<30)


// Data structure passed to several functions
typedef void * LPVFSFUNCDATA;


// Values for vfsReadOp in DOpusVFSReadDirDataA
enum vfsReadType
{
	VFSREAD_CHANGEDIR,						// Change directory only, don't read directory
	VFSREAD_NORMAL,							// Read directory as normal
	VFSREAD_REFRESH,						// Refresh current directory
	VFSREAD_PARENT,							// Go to parent
	VFSREAD_ROOT,							// Go to root
	VFSREAD_BACK,							// Go back
	VFSREAD_FORWARD,						// Go forward
	VFSREAD_PRINTDIR,						// Print Directory function
	VFSREAD_FREEDIR,						// Free any cached directory information
	VFSREAD_FREEDIRCLOSE,					// Free any cached directory information, lister is closing
};


// File data returned by VFS_ReadDirectory function (MUST be allocated using HeapAlloc() with supplied memory heap)
typedef struct DOpusVFSFileDataHeader
{
	UINT					cbSize;				// Size of this structure
	DOpusVFSFileDataHeader*	lpNext;				// Optional pointer to next file data structure
	int						iNumItems;			// Number of items in this structure
	UINT					cbFileDataSize;		// Size of each item data structure
} VFSFILEDATAHEADER, * LPVFSFILEDATAHEADER;


// VFSFILEDATA flags
#define VFSFDF_INDEFINITESIZE		(1<<0)		// only used for VFS_GetFileInformation
#define VFSFDF_BOLD					(1<<1)		// display file in bold
#define VFSFDF_SELECTED				(1<<2)		// file is initially selected

typedef struct DOpusVFSFileDataColumnA
{
	int					iColumnId;				// Column ID number
	LPSTR				lpszValue;				// String for column (allocate using HeapAlloc())
} VFSFILEDATACOLUMNA, * LPVFSFILEDATACOLUMNA;

typedef struct DOpusVFSFileDataColumnW
{
	int					iColumnId;
	LPWSTR				lpszValue;
} VFSFILEDATACOLUMNW, * LPVFSFILEDATACOLUMNW;

#ifdef UNICODE
#define VFSFILEDATACOLUMN		VFSFILEDATACOLUMNW
#define LPVFSFILEDATACOLUMN		LPVFSFILEDATACOLUMNW
#else
#define VFSFILEDATACOLUMN		VFSFILEDATACOLUMNA
#define LPVFSFILEDATACOLUMN		LPVFSFILEDATACOLUMNA
#endif

// Array of DOpusVFSFileData follows DOpusVFSFileDataHeader in memory
typedef struct DOpusVFSFileDataA
{
	WIN32_FIND_DATAA		wfdData;			// Basic file data
	DWORD					dwFlags;			// Custom flags
	LPSTR					lpszComment;		// File comment (allocate using HeapAlloc())
	int						iNumColumns;		// Number of custom column values supplied
	LPVFSFILEDATACOLUMNA	lpvfsColumnData;	// Custom column values array (allocate using HeapAlloc())
} VFSFILEDATAA, * LPVFSFILEDATAA;

typedef struct DOpusVFSFileDataW
{
	WIN32_FIND_DATAW		wfdData;
	DWORD					dwFlags;
	LPWSTR					lpszComment;
	int						iNumColumns;
	LPVFSFILEDATACOLUMNW	lpvfsColumnData;
} VFSFILEDATAW, * LPVFSFILEDATAW;


#ifdef UNICODE
#define VFSFILEDATA		VFSFILEDATAW
#define LPVFSFILEDATA	LPVFSFILEDATAW
#else
#define VFSFILEDATA		VFSFILEDATAA
#define LPVFSFILEDATA	LPVFSFILEDATAA
#endif


// Data structure for VFS_ReadDirectory function
typedef struct DOpusVFSReadDirDataA
{
	UINT				cbSize;						// Structure size
	HWND				hwndParent;					// Parent window (for displaying error dialogs, etc)
	LPSTR				lpszPath;					// Path
	vfsReadType			vfsReadOp;					// Read operation
	HANDLE				hAbortEvent;				// Abort event (for read-dir only)
	HANDLE				hMemHeap;					// Memory heap to allocate file data on (use HeapAlloc())
	LPVFSFILEDATAHEADER	lpFileData;					// File data pointer
} VFSREADDIRDATAA, * LPVFSREADDIRDATAA;

typedef struct DOpusVFSReadDirDataW
{
	UINT				cbSize;
	HWND				hwndParent;
	LPWSTR				lpszPath;
	vfsReadType			vfsReadOp;
	HANDLE				hAbortEvent;
	HANDLE				hMemHeap;
	LPVFSFILEDATAHEADER	lpFileData;
} VFSREADDIRDATAW, * LPVFSREADDIRDATAW;

#ifdef UNICODE
#define VFSREADDIRDATA		VFSREADDIRDATAW
#define LPVFSREADDIRDATA	LPVFSREADDIRDATAW
#else
#define VFSREADDIRDATA		VFSREADDIRDATAA
#define LPVFSREADDIRDATA	LPVFSREADDIRDATAA
#endif


// VFSPROP_FUNCAVAILABILITY flags
#define BM64(l)	(((unsigned __int64)1)<<(l))

#define VFSFUNCAVAIL_COPY						BM64(0)
#define VFSFUNCAVAIL_MOVE						BM64(1)
#define VFSFUNCAVAIL_DELETE						BM64(2)
#define VFSFUNCAVAIL_GETSIZES					BM64(3)
#define VFSFUNCAVAIL_MAKEDIR					BM64(4)
#define VFSFUNCAVAIL_PRINT						BM64(5)
#define VFSFUNCAVAIL_PROPERTIES					BM64(6)
#define VFSFUNCAVAIL_RENAME						BM64(7)
#define VFSFUNCAVAIL_SETATTR					BM64(8)
#define VFSFUNCAVAIL_SHORTCUT					BM64(9)
#define VFSFUNCAVAIL_SELECTALL					BM64(10)
#define VFSFUNCAVAIL_SELECTNONE					BM64(11)
#define VFSFUNCAVAIL_SELECTINVERT				BM64(12)
#define VFSFUNCAVAIL_VIEWLARGEICONS				BM64(13)
#define VFSFUNCAVAIL_VIEWSMALLICONS				BM64(14)
#define VFSFUNCAVAIL_VIEWLIST					BM64(15)
#define VFSFUNCAVAIL_VIEWDETAILS				BM64(16)
#define VFSFUNCAVAIL_VIEWTHUMBNAIL				BM64(17)
#define VFSFUNCAVAIL_CLIPCOPY					BM64(18)
#define VFSFUNCAVAIL_CLIPCUT					BM64(19)
#define VFSFUNCAVAIL_CLIPPASTE					BM64(20)
#define VFSFUNCAVAIL_CLIPPASTESHORTCUT			BM64(21)
#define VFSFUNCAVAIL_UNDO						BM64(22)
#define VFSFUNCAVAIL_SHOW						BM64(23)
#define VFSFUNCAVAIL_DUPLICATE					BM64(24)
#define VFSFUNCAVAIL_SPLITJOIN					BM64(25)
#define VFSFUNCAVAIL_SELECTRESELECT				BM64(26)
#define VFSFUNCAVAIL_SELECTALLFILES				BM64(27)
#define VFSFUNCAVAIL_SELECTALLDIRS				BM64(28)
#define VFSFUNCAVAIL_PLAY						BM64(29)
#define VFSFUNCAVAIL_SETTIME					BM64(30)
#define VFSFUNCAVAIL_VIEWTILE					BM64(31)
#define VFSFUNCAVAIL_SETCOMMENT					BM64(32)


// Properties
enum vfsProperty
{
	VFSPROP_ISEXTRACTABLE,
	VFSPROP_USEFULLRENAME,
	VFSPROP_SHOWFULLPROGRESSBAR,
	VFSPROP_CANDELETETOTRASH,
	VFSPROP_CANDELETESECURE,
	VFSPROP_COPYBUFFERSIZE,
	VFSPROP_DRAGEFFECTS,
	VFSPROP_SHOWTHUMBNAILS,
	VFSPROP_SHOWFILEINFO,
	VFSPROP_ALLOWTOOLTIPGETSIZES,
	VFSPROP_CANSHOWSUBFOLDERS,
	VFSPROP_FUNCAVAILABILITY,
	VFSPROP_SUPPORTFILEHASH,
	VFSPROP_GETFOLDERICON,
	VFSPROP_SUPPORTPATHCOMPLETION,
#if ( VFSPLUGINVERSION >= 2 )
	VFSPROP_BATCHOPERATION,
	VFSPROP_GETVALIDACTIONS,
	VFSPROP_SHOWPICTURESDIRECTLY,
#endif
};


// Custom column flags
#define VFSCCF_LEFTJUSTIFY		0
#define VFSCCF_RIGHTJUSTIFY		(1<<0)
#define VFSCCF_CENTERJUSTIFY	(1<<2)
#define VFSCCF_NUMBER			(1<<4)
#define VFSCCF_PERCENT			(1<<5)
#define VFSCCF_SIZE				(1<<6)

// VFS_GetCustomColumns data
typedef struct DOpusVFSCustomColumnA
{
	UINT					cbSize;
	DOpusVFSCustomColumnA*	lpNext;
	LPSTR					lpszLabel;
	LPSTR					lpszKey;
	DWORD					dwFlags;
	int						iID;
} VFSCUSTOMCOLUMNA, * LPVFSCUSTOMCOLUMNA;

typedef struct DOpusVFSCustomColumnW
{
	UINT					cbSize;
	DOpusVFSCustomColumnW*	lpNext;
	LPWSTR					lpszLabel;
	LPWSTR					lpszKey;
	DWORD					dwFlags;
	int						iID;
} VFSCUSTOMCOLUMNW, * LPVFSCUSTOMCOLUMNW;

#ifdef UNICODE
#define VFSCUSTOMCOLUMN			VFSCUSTOMCOLUMNW
#define LPVFSCUSTOMCOLUMN		LPVFSCUSTOMCOLUMNW
#else
#define VFSCUSTOMCOLUMN			VFSCUSTOMCOLUMNA
#define LPVFSCUSTOMCOLUMN		LPVFSCUSTOMCOLUMNA
#endif


// Context verb flags
#define DOPUSCVF_ISDIR			(1<<3)

// VFS_ContextVerb data
typedef struct DOpusVFSContextVerbDataA
{
	UINT		cbSize;					// Structure size
	HWND		hwndParent;				// Parent window
	LPSTR		lpszVerb;				// Verb, null=double-click
	LPSTR		lpszPath;				// Path
	LPSTR		lpszNewPath;			// New path for VFSCVRES_CHANGE result
	int			cchNewPathMax;			// Maximum size of new path
	UINT		uMsg;					// Double-click message
	WPARAM		fwKeys;					// Qualifier keys
	DWORD		dwFlags;				// Flags
	int			iRotateAngle;			// Thumbnail rotation angle (if any)
} VFSCONTEXTVERBDATAA, * LPVFSCONTEXTVERBDATAA;

typedef struct DOpusVFSContextVerbDataW
{
	UINT		cbSize;
	HWND		hwndParent;
	LPWSTR		lpszVerb;
	LPWSTR		lpszPath;
	LPWSTR		lpszNewPath;
	int			cchNewPathMax;
	UINT		uMsg;
	WPARAM		fwKeys;
	DWORD		dwFlags;
	int			iRotateAngle;
} VFSCONTEXTVERBDATAW, * LPVFSCONTEXTVERBDATAW;

#ifdef UNICODE
#define VFSCONTEXTVERBDATA		VFSCONTEXTVERBDATAW
#define LPVFSCONTEXTVERBDATA	LPVFSCONTEXTVERBDATAW
#else
#define VFSCONTEXTVERBDATA		VFSCONTEXTVERBDATAA
#define LPVFSCONTEXTVERBDATA	LPVFSCONTEXTVERBDATAA
#endif

// Return values from VFS_ContextVerb
#define VFSCVRES_FAIL		0
#define VFSCVRES_HANDLED	1
#define VFSCVRES_DEFAULT	2
#define VFSCVRES_EXTRACT	3
#define VFSCVRES_CHANGE		4
#define VFSCVRES_CHANGEDIR	5


// VFS_GetContextMenu data
typedef struct DOpusVFSContextMenuItemA
{
	UINT		cbSize;
	DWORD		dwFlags;
	LPSTR		lpszLabel;
	LPSTR		lpszCommand;
} VFSCONTEXTMENUITEMA, * LPVFSCONTEXTMENUITEMA;

typedef struct DOpusVFSContextMenuItemW
{
	UINT		cbSize;
	DWORD		dwFlags;
	LPWSTR		lpszLabel;
	LPWSTR		lpszCommand;
} VFSCONTEXTMENUITEMW, * LPVFSCONTEXTMENUITEMW;

#ifdef UNICODE
#define VFSCONTEXTMENUITEM		VFSCONTEXTMENUITEMW
#define LPVFSCONTEXTMENUITEM	LPVFSCONTEXTMENUITEMW
#else
#define VFSCONTEXTMENUITEM		VFSCONTEXTMENUITEMA
#define LPVFSCONTEXTMENUITEM	LPVFSCONTEXTMENUITEMA
#endif

// VFSCONTEXTMENUITEM flags
#define VFSCMF_CHECKED					(1<<0)	// Item appears checked
#define VFSCMF_RADIOCHECK				(1<<1)	// Checkmark uses a radio button
#define VFSCMF_DISABLED					(1<<2)	// Item is disabled
#define VFSCMF_SEPARATOR				(1<<3)	// Item is a separator
#define VFSCMF_BEGINSUBMENU				(1<<4)	// Item is a submenu
#define VFSCMF_ENDSUBMENU				(1<<5)	// Item is the last in a submenu


typedef struct DOpusVFSContextMenuDataA
{
	UINT					cbSize;
	BOOL					fAllowContextMenu;
	BOOL					fDefaultContextMenu;
	BOOL					fCustomItemsBelow;
	LPVFSCONTEXTMENUITEMA	lpCustomItems;
	int						iNumCustomItems;
	BOOL					fFreeCustomItems;
} VFSCONTEXTMENUDATAA, * LPVFSCONTEXTMENUDATAA;

typedef struct DOpusVFSContextMenuDataW
{
	UINT					cbSize;
	BOOL					fAllowContextMenu;
	BOOL					fDefaultContextMenu;
	BOOL					fCustomItemsBelow;
	LPVFSCONTEXTMENUITEMW	lpCustomItems;
	int						iNumCustomItems;
	BOOL					fFreeCustomItems;
} VFSCONTEXTMENUDATAW, * LPVFSCONTEXTMENUDATAW;

#ifdef UNICODE
#define VFSCONTEXTMENUDATA		VFSCONTEXTMENUDATAW
#define LPVFSCONTEXTMENUDATA	LPVFSCONTEXTMENUDATAW
#else
#define VFSCONTEXTMENUDATA		VFSCONTEXTMENUDATAA
#define LPVFSCONTEXTMENUDATA	LPVFSCONTEXTMENUDATAA
#endif

// VFS_ExtractFiles data
typedef struct DOpusVFSExtractFilesDataA
{
	UINT		cbSize;					// Structure size
	HWND		hwndParent;				// Parent window (for dialogs, etc)
	LPSTR		lpszDestPath;			// Destination path for extraction
	LPSTR		lpszFiles;				// Files to extract, double-null terminated list
	DWORD		dwFlags;				// Flags
} VFSEXTRACTFILESDATAA, * LPVFSEXTRACTFILESDATAA;

typedef struct DOpusVFSExtractFilesDataW
{
	UINT		cbSize;
	HWND		hwndParent;
	LPWSTR		lpszDestPath;
	LPWSTR		lpszFiles;
	DWORD		dwFlags;
} VFSEXTRACTFILESDATAW, * LPVFSEXTRACTFILESDATAW;

#ifdef UNICODE
#define VFSEXTRACTFILESDATA		VFSEXTRACTFILESDATAW
#define LPVFSEXTRACTFILESDATA	LPVFSEXTRACTFILESDATAW
#else
#define VFSEXTRACTFILESDATA		VFSEXTRACTFILESDATAA
#define LPVFSEXTRACTFILESDATA	LPVFSEXTRACTFILESDATAA
#endif


// VFS_CreateFile flags
#define VFSCREATEF_MODEMASK			0xf
#define VFSCREATEF_RESUME			0x01000
#define VFSCREATEF_RECURSIVECOPY	0x02000
#define VFSCREATEF_THUMBNAIL		0x04000
#define VFSCREATEF_IGNOREIFSLOW		0x10000
#define VFSCREATEF_BUFFERED			0x20000

// VFS_CreateDirectory flags
#define VFSCREATEDIRF_COPY			(1<<0)
#define VFSCREATEDIRF_MULTIPLE		(1<<1)

// VFS_DeleteFile flags
#define VFSDELETEF_FORCE			(1<<0)
#define VFSDELETEF_RECYCLE			(1<<1)
#define VFSDELETEF_REPLACE			(1<<2)
#define VFSDELETEF_COPYFAILED		(1<<3)
#define VFSDELETEF_SOURCERESUME		(1<<5)

// VFS_SeekFile flags
#define VFSSEEKF_RESUME				(1<<0)


#if ( VFSPLUGINVERSION >= 2 )

// VFS_BatchOperation data

typedef struct DOpusVFSBatchDataA
{
	UINT		cbSize;					// Structure size
	HWND		hwndParent;				// Parent window
	HANDLE		hAbortEvent;			// Abort event
	UINT		uiOperation;			// Operation code
	int			iNumFiles;				// Number of files involved
	LPSTR		pszFiles;				// Double-null terminated list file paths
	int*		piResults;				// Array to return individual file results (0 = success or error code)
	LPSTR		pszDestPath;			// Destination path
	DWORD		dwFlags;				// Flags
	LPVOID		lpFuncData;				// Used in several calls to exported Opus functions
} VFSBATCHDATAA, * LPVFSBATCHDATAA;

typedef struct DOpusVFSBatchDataW
{
	UINT		cbSize;					// Structure size
	HWND		hwndParent;				// Parent window
	HANDLE		hAbortEvent;			// Abort event
	UINT		uiOperation;			// Operation code
	int			iNumFiles;				// Number of files involved
	LPWSTR		pszFiles;				// Double-null terminated list file paths
	int*		piResults;				// Array to return individual file results (0 = success or error code)
	LPTSTR		pszDestPath;			// Destination path
	DWORD		dwFlags;				// Flags
	LPVOID		lpFuncData;				// Used in several calls to exported Opus functions
} VFSBATCHDATAW, * LPVFSBATCHDATAW;

#ifdef UNICODE
#define VFSBATCHDATA	VFSBATCHDATAW
#define LPVFSBATCHDATA	LPVFSBATCHDATAW
#else
#define VFSBATCHDATA	VFSBATCHDATAA
#define LPVFSBATCHDATA	LPVFSBATCHDATAA
#endif

#define VFSBATCHOP_ADD			1		// Add files to an archive
#define VFSBATCHOP_EXTRACT		2		// Extract files from an archive
#define VFSBATCHOP_DELETE		3		// Delete files from an archive

#define VFSBATCHRES_DODEFAULT	0		// Do default operation
#define VFSBATCHRES_SKIP		1		// Skip this file
#define VFSBATCHRES_HANDLED		2		// File has been handled by the batch operation
#define VFSBATCHRES_ABORT		3		// Abort the function
#define VFSBATCHRES_COMPLETE	4		// Operation has been completed for all files
#define VFSBATCHRES_CALLFOREACH	(1<<12)	// Call batch operation for each file

// Batch operation flags
#define BATCHF_COPY_PRESERVE_ATTR		(1<<0)	// Preserve file attributes
#define BATCHF_COPY_PRESERVE_DATE		(1<<1)	// Preserve file dates
#define BATCHF_COPY_PRESERVE_COMMENTS	(1<<2)	// Preserve comments
#define BATCHF_COPY_PRESERVE_SECURITY	(1<<3)	// Preserve security info
#define BATCHF_COPY_ASK_REPLACE			(1<<4)	// Ask to overwrite existing files
#define BATCHF_COPY_ASK_REPLACE_RO		(1<<5)	// Ask to overwrite read only files
#define BATCHF_COPY_RENAME				(1<<6)	// Copy/Move As
#define BATCHF_DELETE_ASK				(1<<7)	// Ask to begin delete
#define BATCHF_DELETE_ASK_FILES			(1<<8)	// Ask to delete files
#define BATCHF_DELETE_ASK_FOLDERS		(1<<9)	// Ask to delete folders
#define BATCHF_DELETE_UNPROTECT			(1<<10)	// Unprotect automatically
#define BATCHF_DELETE_ALL				(1<<11)	// Delete all without prompting for each
#define BATCHF_DELETE_QUIET				(1<<12)	// Don't prompt to begin
#define BATCHF_DELETE_FORCE				(1<<13)	// Force deletion
#define BATCHF_DELETE_SECURE			(1<<14)	// Secure delete
#define BATCHF_FILTER					(1<<15)	// A filter is in force
#define BATCHF_FILTER_FOLDERS			(1<<16)	// A filter is in force for folders
#define BATCHF_PROGRESS_SUBFOLDERS		(1<<17)	// Progress bar knows about sub-folder contents
#define BATCHF_COPY_DELETE_ORIGINAL		(1<<18)	// Operation is a 'Move' - delete original files


// Data structure passed to VFS_Init
typedef struct VFSInitData
{
	UINT			cbSize;					// Size of this structure
	HWND			hwndDOpusMsgWindow;		// Plugin manager message window
	DWORD			dwOpusVerMajor;			// Opus major version
	DWORD			dwOpusVerMinor;			// Opus minor version
	LPWSTR			pszLanguageName;		// Current language in use
} VFSINITDATA, * LPVFSINITDATA;


// Structure passed to VFS_USBSafe function
#ifndef DEF_OPUSUSBSAFEDATA
#define DEF_OPUSUSBSAFEDATA

typedef struct OpusUSBSafeData
{
	UINT		cbSize;						// Size of this structure
	LPWSTR		pszOtherExports;			// Fill with double-null terminated list of additional files to export
	UINT		cchOtherExports;			// Size of provided buffer
} OPUSUSBSAFEDATA, * LPOPUSUSBSAFEDATA;

#endif

#endif

#if ( VFSPLUGINVERSION >= 3 )

// Operations for VFS_GetErrorMsg
#define VFSERROP_READDDIR	1

#endif


// Exported plugin DLL functions
#define VFSFUNCNAME_IDENTIFYA			"VFS_IdentifyA"
#define VFSFUNCNAME_IDENTIFYW			"VFS_IdentifyW"
#define VFSFUNCNAME_QUERYPATHA			"VFS_QueryPathA"
#define VFSFUNCNAME_QUERYPATHW			"VFS_QueryPathW"
#define VFSFUNCNAME_GETCAPABILITIES		"VFS_GetCapabilities"
#define VFSFUNCNAME_GETCUSTOMCOLUMNSA	"VFS_GetCustomColumnsA"
#define VFSFUNCNAME_GETCUSTOMCOLUMNSW	"VFS_GetCustomColumnsW"
#define VFSFUNCNAME_GETPREFIXLISTA		"VFS_GetPrefixListA"
#define VFSFUNCNAME_GETPREFIXLISTW		"VFS_GetPrefixListW"
#define VFSFUNCNAME_CREATE				"VFS_Create"
#define VFSFUNCNAME_CLONE				"VFS_Clone"
#define VFSFUNCNAME_DESTROY				"VFS_Destroy"
#define VFSFUNCNAME_GETLASTERROR		"VFS_GetLastError"
#define VFSFUNCNAME_READDIRECTORYA		"VFS_ReadDirectoryA"
#define VFSFUNCNAME_READDIRECTORYW		"VFS_ReadDirectoryW"
#define VFSFUNCNAME_GETPATHDISPLAYNAMEA	"VFS_GetPathDisplayNameA"
#define VFSFUNCNAME_GETPATHDISPLAYNAMEW	"VFS_GetPathDisplayNameW"
#define VFSFUNCNAME_GETPATHPARENTROOTA	"VFS_GetPathParentRootA"
#define VFSFUNCNAME_GETPATHPARENTROOTW	"VFS_GetPathParentRootW"
#define VFSFUNCNAME_GETFILEINFORMATIONA	"VFS_GetFileInformationA"
#define VFSFUNCNAME_GETFILEINFORMATIONW	"VFS_GetFileInformationW"
#define VFSFUNCNAME_GETFILEDESCRIPTIONA	"VFS_GetFileDescriptionA"
#define VFSFUNCNAME_GETFILEDESCRIPTIONW	"VFS_GetFileDescriptionW"
#define VFSFUNCNAME_GETFILEICONA		"VFS_GetFileIconA"
#define VFSFUNCNAME_GETFILEICONW		"VFS_GetFileIconW"
#define VFSFUNCNAME_CREATEFILEA			"VFS_CreateFileA"
#define VFSFUNCNAME_CREATEFILEW			"VFS_CreateFileW"
#define VFSFUNCNAME_READFILE			"VFS_ReadFile"
#define VFSFUNCNAME_WRITEFILE			"VFS_WriteFile"
#define VFSFUNCNAME_SEEKFILE			"VFS_SeekFile"
#define VFSFUNCNAME_CLOSEFILE			"VFS_CloseFile"
#define VFSFUNCNAME_MOVEFILEA			"VFS_MoveFileA"
#define VFSFUNCNAME_MOVEFILEW			"VFS_MoveFileW"
#define VFSFUNCNAME_DELETEFILEA			"VFS_DeleteFileA"
#define VFSFUNCNAME_DELETEFILEW			"VFS_DeleteFileW"
#define VFSFUNCNAME_SETFILETIMEA		"VFS_SetFileTimeA"
#define VFSFUNCNAME_SETFILETIMEW		"VFS_SetFileTimeW"
#define VFSFUNCNAME_SETFILEATTRA		"VFS_SetFileAttrA"
#define VFSFUNCNAME_SETFILEATTRW		"VFS_SetFileAttrW"
#define VFSFUNCNAME_GETFILEATTRA		"VFS_GetFileAttrA"
#define VFSFUNCNAME_GETFILEATTRW		"VFS_GetFileAttrW"
#define VFSFUNCNAME_SETFILECOMMENTA		"VFS_SetFileCommentA"
#define VFSFUNCNAME_SETFILECOMMENTW		"VFS_SetFileCommentW"
#define VFSFUNCNAME_GETFILECOMMENTA		"VFS_GetFileCommentA"
#define VFSFUNCNAME_GETFILECOMMENTW		"VFS_GetFileCommentW"
#define VFSFUNCNAME_CREATEDIRECTORYA	"VFS_CreateDirectoryA"
#define VFSFUNCNAME_CREATEDIRECTORYW	"VFS_CreateDirectoryW"
#define VFSFUNCNAME_REMOVEDIRECTORYA	"VFS_RemoveDirectoryA"
#define VFSFUNCNAME_REMOVEDIRECTORYW	"VFS_RemoveDirectoryW"
#define VFSFUNCNAME_GETFILESIZEA		"VFS_GetFileSizeA"
#define VFSFUNCNAME_GETFILESIZEW		"VFS_GetFileSizeW"
#define VFSFUNCNAME_FINDFIRSTFILEA		"VFS_FindFirstFileA"
#define VFSFUNCNAME_FINDFIRSTFILEW		"VFS_FindFirstFileW"
#define VFSFUNCNAME_FINDNEXTFILEA		"VFS_FindNextFileA"
#define VFSFUNCNAME_FINDNEXTFILEW		"VFS_FindNextFileW"
#define VFSFUNCNAME_FINDCLOSE			"VFS_FindClose"
#define VFSFUNCNAME_PROPGETA			"VFS_PropGetA"
#define VFSFUNCNAME_PROPGETW			"VFS_PropGetW"
#define VFSFUNCNAME_CONTEXTVERBA		"VFS_ContextVerbA"
#define VFSFUNCNAME_CONTEXTVERBW		"VFS_ContextVerbW"
#define VFSFUNCNAME_EXTRACTFILESA		"VFS_ExtractFilesA"
#define VFSFUNCNAME_EXTRACTFILESW		"VFS_ExtractFilesW"
#define VFSFUNCNAME_PROPERTIESA			"VFS_PropertiesA"
#define VFSFUNCNAME_PROPERTIESW			"VFS_PropertiesW"
#define VFSFUNCNAME_GETCONTEXTMENUA		"VFS_GetContextMenuA"
#define VFSFUNCNAME_GETCONTEXTMENUW		"VFS_GetContextMenuW"
#define VFSFUNCNAME_GETDROPMENUA		"VFS_GetDropMenuA"
#define VFSFUNCNAME_GETDROPMENUW		"VFS_GetDropMenuW"
#define VFSFUNCNAME_GETFREEDISKSPACEA	"VFS_GetFreeDiskSpaceA"
#define VFSFUNCNAME_GETFREEDISKSPACEW	"VFS_GetFreeDiskSpaceW"
#define VFSFUNCNAME_CONFIGURE			"VFS_Configure"
#define VFSFUNCNAME_ABOUT				"VFS_About"

#if ( VFSPLUGINVERSION >= 2 )
#define VFSFUNCNAME_BATCHOPERATIONA		"VFS_BatchOperationA"
#define VFSFUNCNAME_BATCHOPERATIONW		"VFS_BatchOperationW"
#define VFSFUNCNAME_USBSAFE				"VFS_USBSafe"
#define VFSFUNCNAME_INIT				"VFS_Init"
#define VFSFUNCNAME_UNINIT				"VFS_Uninit"
#endif

#if ( VFSPLUGINVERSION >= 3 )
#define VFSFUNCNAME_GETERRORMSGA		"VFS_GetErrorMsgA"
#define VFSFUNCNAME_GETERRORMSGW		"VFS_GetErrorMsgW"
#endif

#ifdef UNICODE
#define VFSFUNCNAME_IDENTIFY			VFSFUNCNAME_IDENTIFYW
#define VFSFUNCNAME_GETCUSTOMCOLUMNS	VFSFUNCNAME_GETCUSTOMCOLUMNSW
#define VFSFUNCNAME_QUERYPATH			VFSFUNCNAME_QUERYPATHW
#define VFSFUNCNAME_GETPREFIXLIST		VFSFUNCNAME_GETPREFIXLISTW
#define VFSFUNCNAME_READDIRECTORY		VFSFUNCNAME_READDIRECTORYW
#define VFSFUNCNAME_GETPATHDISPLAYNAME	VFSFUNCNAME_GETPATHDISPLAYNAMEW
#define VFSFUNCNAME_GETPATHPARENTROOT	VFSFUNCNAME_GETPATHPARENTROOTW
#define VFSFUNCNAME_GETFILEINFORMATION	VFSFUNCNAME_GETFILEINFORMATIONW
#define VFSFUNCNAME_GETFILEDESCRIPTION	VFSFUNCNAME_GETFILEDESCRIPTIONW
#define VFSFUNCNAME_GETFILEICON			VFSFUNCNAME_GETFILEICONW
#define VFSFUNCNAME_CREATEFILE			VFSFUNCNAME_CREATEFILEW
#define VFSFUNCNAME_MOVEFILE			VFSFUNCNAME_MOVEFILEW
#define VFSFUNCNAME_DELETEFILE			VFSFUNCNAME_DELETEFILEW
#define VFSFUNCNAME_SETFILETIME			VFSFUNCNAME_SETFILETIMEW
#define VFSFUNCNAME_SETFILEATTR			VFSFUNCNAME_SETFILEATTRW
#define VFSFUNCNAME_GETFILEATTR			VFSFUNCNAME_GETFILEATTRW
#define VFSFUNCNAME_GETFILECOMMENT		VFSFUNCNAME_GETFILECOMMENTW
#define VFSFUNCNAME_SETFILECOMMENT		VFSFUNCNAME_SETFILECOMMENTW
#define VFSFUNCNAME_CREATEDIRECTORY		VFSFUNCNAME_CREATEDIRECTORYW
#define VFSFUNCNAME_REMOVEDIRECTORY		VFSFUNCNAME_REMOVEDIRECTORYW
#define VFSFUNCNAME_GETFILESIZE			VFSFUNCNAME_GETFILESIZEW
#define VFSFUNCNAME_FINDFIRSTFILE		VFSFUNCNAME_FINDFIRSTFILEW
#define VFSFUNCNAME_FINDNEXTFILE		VFSFUNCNAME_FINDNEXTFILEW
#define VFSFUNCNAME_PROPGET				VFSFUNCNAME_PROPGETW
#define VFSFUNCNAME_CONTEXTVERB			VFSFUNCNAME_CONTEXTVERBW
#define VFSFUNCNAME_EXTRACTFILES		VFSFUNCNAME_EXTRACTFILESW
#define VFSFUNCNAME_PROPERTIES			VFSFUNCNAME_PROPERTIESW
#define VFSFUNCNAME_GETCONTEXTMENU		VFSFUNCNAME_GETCONTEXTMENUW
#define VFSFUNCNAME_GETDROPMENU			VFSFUNCNAME_GETDROPMENUW
#define VFSFUNCNAME_GETFREEDISKSPACE	VFSFUNCNAME_GETFREEDISKSPACEW
#if ( VFSPLUGINVERSION >= 2 )
#define VFSFUNCNAME_BATCHOPERATION		VFSFUNCNAME_BATCHOPERATIONW
#endif
#if ( VFSPLUGINVERSION >= 3 )
#define VFSFUNCNAME_GETERRORMSG			VFSFUNCNAME_GETERRORMSGW
#endif
#else
#define VFSFUNCNAME_IDENTIFY			VFSFUNCNAME_IDENTIFYA
#define VFSFUNCNAME_GETCUSTOMCOLUMNS	VFSFUNCNAME_GETCUSTOMCOLUMNSA
#define VFSFUNCNAME_QUERYPATH			VFSFUNCNAME_QUERYPATHA
#define VFSFUNCNAME_GETPREFIXLIST		VFSFUNCNAME_GETPREFIXLISTA
#define VFSFUNCNAME_READDIRECTORY		VFSFUNCNAME_READDIRECTORYA
#define VFSFUNCNAME_GETPATHDISPLAYNAME	VFSFUNCNAME_GETPATHDISPLAYNAMEA
#define VFSFUNCNAME_GETPATHPARENTROOT	VFSFUNCNAME_GETPATHPARENTROOTA
#define VFSFUNCNAME_GETFILEINFORMATION	VFSFUNCNAME_GETFILEINFORMATIONA
#define VFSFUNCNAME_GETFILEDESCRIPTION	VFSFUNCNAME_GETFILEDESCRIPTIONA
#define VFSFUNCNAME_GETFILEICON			VFSFUNCNAME_GETFILEICONA
#define VFSFUNCNAME_CREATEFILE			VFSFUNCNAME_CREATEFILEA
#define VFSFUNCNAME_MOVEFILE			VFSFUNCNAME_MOVEFILEA
#define VFSFUNCNAME_DELETEFILE			VFSFUNCNAME_DELETEFILEA
#define VFSFUNCNAME_SETFILETIME			VFSFUNCNAME_SETFILETIMEA
#define VFSFUNCNAME_SETFILEATTR			VFSFUNCNAME_SETFILEATTRA
#define VFSFUNCNAME_GETFILEATTR			VFSFUNCNAME_GETFILEATTRA
#define VFSFUNCNAME_SETFILECOMMENT		VFSFUNCNAME_SETFILECOMMENTA
#define VFSFUNCNAME_GETFILECOMMENT		VFSFUNCNAME_GETFILECOMMENTA
#define VFSFUNCNAME_CREATEDIRECTORY		VFSFUNCNAME_CREATEDIRECTORYA
#define VFSFUNCNAME_REMOVEDIRECTORY		VFSFUNCNAME_REMOVEDIRECTORYA
#define VFSFUNCNAME_GETFILESIZE			VFSFUNCNAME_GETFILESIZEA
#define VFSFUNCNAME_FINDFIRSTFILE		VFSFUNCNAME_FINDFIRSTFILEA
#define VFSFUNCNAME_FINDNEXTFILE		VFSFUNCNAME_FINDNEXTFILEA
#define VFSFUNCNAME_PROPGET				VFSFUNCNAME_PROPGETA
#define VFSFUNCNAME_CONTEXTVERB			VFSFUNCNAME_CONTEXTVERBA
#define VFSFUNCNAME_EXTRACTFILES		VFSFUNCNAME_EXTRACTFILESA
#define VFSFUNCNAME_PROPERTIES			VFSFUNCNAME_PROPERTIESA
#define VFSFUNCNAME_GETCONTEXTMENU		VFSFUNCNAME_GETCONTEXTMENUA
#define VFSFUNCNAME_GETDROPMENU			VFSFUNCNAME_GETDROPMENUA
#define VFSFUNCNAME_GETFREEDISKSPACE	VFSFUNCNAME_GETFREEDISKSPACEA
#if ( VFSPLUGINVERSION >= 2 )
#define VFSFUNCNAME_BATCHOPERATION		VFSFUNCNAME_BATCHOPERATIONA
#endif
#if ( VFSPLUGINVERSION >= 3 )
#define VFSFUNCNAME_GETERRORMSG			VFSFUNCNAME_GETERRORMSGA
#endif
#endif


// Function prototypes
typedef HANDLE (*PFNVFSCREATE)(LPGUID pGUID,HWND hwndMsgWindow);
typedef HANDLE (*PFNVFSCLONE)(HANDLE hVFSData);
typedef void (*PFNVFSDESTROY)(HANDLE hVFSData);
typedef DWORD (*PFNVFSGETCAPABILITIES)(HANDLE hVFSData);
typedef long (*PFNVFSGETLASTERROR)(HANDLE hVFSData);
typedef BOOL (*PFNVFSREADFILE)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,HANDLE hFile,LPVOID lpData,DWORD dwSize,LPDWORD lpdwReadSize);
typedef BOOL (*PFNVFSWRITEFILE)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,HANDLE hFile,LPVOID lpData,DWORD dwSize,BOOL fFlush,LPDWORD lpdwWriteSize);
typedef BOOL (*PFNVFSSEEKFILE)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,HANDLE hFile,__int64 iPos,DWORD dwMethod,DWORD dwFlags,unsigned __int64* piNewPos);
typedef void (*PFNVFSCLOSEFILE)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,HANDLE hFile);
typedef void (*PFNVFSFINDCLOSE)(HANDLE hVFSData,HANDLE hFind);
typedef HWND (*PFNVFSCONFIGURE)(HWND hWndParent,HWND hWndNotify,DWORD dwNotifyData);
typedef HWND (*PFNVFSABOUT)(HWND hWndParent);

typedef BOOL (*PFNVFSIDENTIFYA)(LPVFSPLUGININFOA lpVFSInfo);
typedef BOOL (*PFNVFSIDENTIFYW)(LPVFSPLUGININFOW lpVFSInfo);
typedef LPVFSCUSTOMCOLUMNA (*PFNVFSGETCUSTOMCOLUMNSA)(HANDLE hVFSData);
typedef LPVFSCUSTOMCOLUMNW (*PFNVFSGETCUSTOMCOLUMNSW)(HANDLE hVFSData);
typedef BOOL (*PFNVFSQUERYPATHA)(LPSTR lpszPath,BOOL fPrefix,LPGUID pGUID);
typedef BOOL (*PFNVFSQUERYPATHW)(LPWSTR lpszPath,BOOL fPrefix,LPGUID pGUID);
typedef BOOL (*PFNVFSGETPREFIXLISTA)(LPSTR lpszPrefix,int cbPrefixMax);
typedef BOOL (*PFNVFSGETPREFIXLISTW)(LPWSTR lpszPrefix,int cbPrefixMax);
typedef int (*PFNVFSREADDIRECTORYA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPVFSREADDIRDATAA lpReadDirData);
typedef int (*PFNVFSREADDIRECTORYW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPVFSREADDIRDATAW lpReadDirData);
typedef BOOL (*PFNVFSGETPATHDISPLAYNAMEA)(HANDLE hVFSData,LPSTR lpszPath,LPSTR lpszDisplayName,int cbDisplayNameMax);
typedef BOOL (*PFNVFSGETPATHDISPLAYNAMEW)(HANDLE hVFSData,LPWSTR lpszPath,LPWSTR lpszDisplayName,int cbDisplayNameMax);
typedef BOOL (*PFNVFSGETPATHPARENTROOTA)(HANDLE hVFSData,LPSTR lpszPath,BOOL fRoot,LPSTR lpszNewPath,int cbNewPathMax);
typedef BOOL (*PFNVFSGETPATHPARENTROOTW)(HANDLE hVFSData,LPWSTR lpszPath,BOOL fRoot,LPWSTR lpszNewPath,int cbNewPathMax);
typedef LPVFSFILEDATAHEADER (*PFNVFSGETFILEINFORMATIONA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPSTR lpszPath,HANDLE hHeap,DWORD dwFlags);
typedef LPVFSFILEDATAHEADER (*PFNVFSGETFILEINFORMATIONW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPWSTR lpszPath,HANDLE hHeap,DWORD dwFlags);
typedef int (*PFNVFSGETFILEDESCRIPTIONA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPSTR lpszFile,LPSTR lpszDescription,int cchDescriptionMax);
typedef int (*PFNVFSGETFILEDESCRIPTIONW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPWSTR lpszFile,LPWSTR lpszDescription,int cchDescriptionMax);
typedef BOOL (*PFNVFSGETFILEICONA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPSTR lpszFile,LPINT lpiSysIconIndex,HICON* phLargeIcon,HICON* phSmallIcon,LPBOOL lpfDestroyIcons,LPSTR lspzCacheName,int cchCacheNameMax,LPINT lpiCacheIndex);
typedef BOOL (*PFNVFSGETFILEICONW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPWSTR lpszFile,LPINT lpiSysIconIndex,HICON* phLargeIcon,HICON* phSmallIcon,LPBOOL lpfDestroyIcons,LPWSTR lspzCacheName,int cchCacheNameMax,LPINT lpiCacheIndex);
typedef HANDLE (*PFNVFSCREATEFILEA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPSTR lpszFile,DWORD dwMode,DWORD dwFlagsAndAttr,DWORD dwFlags,LPFILETIME lpFT);
typedef HANDLE (*PFNVFSCREATEFILEW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPWSTR lpszFile,DWORD dwMode,DWORD dwFlagsAndAttr,DWORD dwFlags,LPFILETIME lpFT);
typedef BOOL (*PFNVFSMOVEFILEA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPSTR lpszOldPath,LPSTR lpszNewName);
typedef BOOL (*PFNVFSMOVEFILEW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPWSTR lpszOldPath,LPWSTR lpszNewName);
typedef BOOL (*PFNVFSDELETEFILEA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPSTR lpszPath,DWORD dwFlags,int iSecurePasses);
typedef BOOL (*PFNVFSDELETEFILEW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPWSTR lpszPath,DWORD dwFlags,int iSecurePasses);
typedef BOOL (*PFNVFSSETFILETIMEA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPSTR lpszPath,HANDLE hFile,LPFILETIME lpCreateTime,LPFILETIME lpAccessTime,LPFILETIME lpModifyTime);
typedef BOOL (*PFNVFSSETFILETIMEW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPWSTR lpszPath,HANDLE hFile,LPFILETIME lpCreateTime,LPFILETIME lpAccessTime,LPFILETIME lpModifyTime);
typedef BOOL (*PFNVFSSETFILEATTRA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPSTR lpszPath,DWORD dwAttr,BOOL fForDelete);
typedef BOOL (*PFNVFSSETFILEATTRW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPWSTR lpszPath,DWORD dwAttr,BOOL fForDelete);
typedef BOOL (*PFNVFSGETFILEATTRA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPSTR lpszPath,LPDWORD ldpwAttr);
typedef BOOL (*PFNVFSGETFILEATTRW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPWSTR lpszPath,LPDWORD ldpwAttr);
typedef BOOL (*PFNVFSSETFILECOMMENTA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPSTR lpszPath,LPSTR lpszComment);
typedef BOOL (*PFNVFSSETFILECOMMENTW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPWSTR lpszPath,LPWSTR lpszComment);
typedef BOOL (*PFNVFSGETFILECOMMENTA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPSTR lpszPath,LPSTR lpszComment,int cchCommentMax);
typedef BOOL (*PFNVFSGETFILECOMMENTW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPWSTR lpszPath,LPWSTR lpszComment,int cchCommentMax);
typedef BOOL (*PFNVFSCREATEDIRECTORYA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPSTR lpszPath,DWORD dwFlags);
typedef BOOL (*PFNVFSCREATEDIRECTORYW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPWSTR lpszPath,DWORD dwFlags);
typedef BOOL (*PFNVFSREMOVEDIRECTORYA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPSTR lpszPath,DWORD dwFlags);
typedef BOOL (*PFNVFSREMOVEDIRECTORYW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPWSTR lpszPath,DWORD dwFlags);
typedef BOOL (*PFNVFSGETFILESIZEA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPSTR lpszPath,HANDLE hFile,unsigned __int64* piFileSize);
typedef BOOL (*PFNVFSGETFILESIZEW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPWSTR lpszPath,HANDLE hFile,unsigned __int64* piFileSize);
typedef HANDLE (*PFNVFSFINDFIRSTFILEA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPSTR lpszPath,LPWIN32_FIND_DATAA lpwfdData,HANDLE hAbortEvent);
typedef HANDLE (*PFNVFSFINDFIRSTFILEW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPWSTR lpszPath,LPWIN32_FIND_DATAW lpwfdData,HANDLE hAbortEvent);
typedef BOOL (*PFNVFSFINDNEXTFILEA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,HANDLE hFind,LPWIN32_FIND_DATAA lpwfdData);
typedef BOOL (*PFNVFSFINDNEXTFILEW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,HANDLE hFind,LPWIN32_FIND_DATAW lpwfdData);
typedef BOOL (*PFNVFSPROPGETA)(HANDLE hVFSData,vfsProperty propId,LPVOID lpPropData,LPVOID lpData1,LPVOID lpData2,LPVOID lpData3);
typedef BOOL (*PFNVFSPROPGETW)(HANDLE hVFSData,vfsProperty propId,LPVOID lpPropData,LPVOID lpData1,LPVOID lpData2,LPVOID lpData3);
typedef int (*PFNVFSCONTEXTVERBA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPVFSCONTEXTVERBDATAA lpVerbData);
typedef int (*PFNVFSCONTEXTVERBW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPVFSCONTEXTVERBDATAW lpVerbData);
typedef BOOL (*PFNVFSEXTRACTFILESA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPVFSEXTRACTFILESDATAA lpExtractData);
typedef BOOL (*PFNVFSEXTRACTFILESW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPVFSEXTRACTFILESDATAW lpExtractData);
typedef HWND (*PFNVFSPROPERTIESA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,HWND hwndParent,LPSTR lpszFiles);
typedef HWND (*PFNVFSPROPERTIESW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,HWND hwndParent,LPWSTR lpszFiles);
typedef BOOL (*PFNVFSGETFREEDISKSPACEA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPSTR lpszPath,unsigned __int64* piFreeBytesAvailable,unsigned __int64* piTotalBytes,unsigned __int64* piTotalFreeBytes);
typedef BOOL (*PFNVFSGETFREEDISKSPACEW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPWSTR lpszPath,unsigned __int64* piFreeBytesAvailable,unsigned __int64* piTotalBytes,unsigned __int64* piTotalFreeBytes);
typedef BOOL (*PFNVFSGETCONTEXTMENUA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPSTR lpszFiles,LPVFSCONTEXTMENUDATAA lpMenuData);
typedef BOOL (*PFNVFSGETCONTEXTMENUW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPWSTR lpszFiles,LPVFSCONTEXTMENUDATAW lpMenuData);
typedef BOOL (*PFNVFSGETDROPMENUA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPSTR lpszFiles,LPVFSCONTEXTMENUDATAA lpMenuData,DWORD dwEffects);
typedef BOOL (*PFNVFSGETDROPMENUW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPWSTR lpszFiles,LPVFSCONTEXTMENUDATAW lpMenuData,DWORD dwEffects);
#if ( VFSPLUGINVERSION >= 2 )
typedef UINT (*PFNVFSBATCHOPERATIONA)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPSTR lpszPath,LPVFSBATCHDATAA lpBatchData);
typedef UINT (*PFNVFSBATCHOPERATIONW)(HANDLE hVFSData,LPVFSFUNCDATA lpFuncData,LPWSTR lpszPath,LPVFSBATCHDATAW lpBatchData);
typedef BOOL (*PFNVFSUSBSAFE)(LPOPUSUSBSAFEDATA pUSBSafeData);
typedef BOOL (*PFNVFSINIT)(LPVFSINITDATA pInitData);
typedef void (*PFNVFSUNINIT)(void);
#endif
#if ( VFSPLUGINVERSION >= 3 )
typedef BOOL (*PFNVFSGETERRORMSGA)(HANDLE hVFSData,UINT uiOperation,UINT uiError,LPSTR lpszMsg,UINT cchMsgMax);
typedef BOOL (*PFNVFSGETERRORMSGW)(HANDLE hVFSData,UINT uiOperation,UINT uiError,LPWSTR lpszMsg,UINT cchMsgMax);
#endif

#ifdef UNICODE
#define PFNVFSIDENTIFY				PFNVFSIDENTIFYW
#define PFNVFSGETCUSTOMCOLUMNS		PFNVFSGETCUSTOMCOLUMNSW
#define PFNVFSQUERYPATH				PFNVFSQUERYPATHW
#define PFNVFSGETPREFIXLIST			PFNVFSGETPREFIXLISTW
#define PFNVFSREADDIRECTORY			PFNVFSREADDIRECTORYW
#define PFNVFSGETPATHDISPLAYNAME	PFNVFSGETPATHDISPLAYNAMEW
#define PFNVFSGETPATHPARENTROOT		PFNVFSGETPATHPARENTROOTW
#define PFNVFSGETFILEINFORMATION	PFNVFSGETFILEINFORMATIONW
#define PFNVFSGETFILEDESCRIPTION	PFNVFSGETFILEDESCRIPTIONW
#define PFNVFSGETFILEICON			PFNVFSGETFILEICONW
#define PFNVFSCREATEFILE			PFNVFSCREATEFILEW
#define PFNVFSMOVEFILE				PFNVFSMOVEFILEW
#define PFNVFSDELETEFILE			PFNVFSDELETEFILEW
#define PFNVFSSETFILETIME			PFNVFSSETFILETIMEW
#define PFNVFSSETFILEATTR			PFNVFSSETFILEATTRW
#define PFNVFSGETFILEATTR			PFNVFSGETFILEATTRW
#define PFNVFSSETFILECOMMENT		PFNVFSSETFILECOMMENTW
#define PFNVFSGETFILECOMMENT		PFNVFSGETFILECOMMENTW
#define PFNVFSCREATEDIRECTORY		PFNVFSCREATEDIRECTORYW
#define PFNVFSREMOVEDIRECTORY		PFNVFSREMOVEDIRECTORYW
#define PFNVFSGETFILESIZE			PFNVFSGETFILESIZEW
#define PFNVFSFINDFIRSTFILE			PFNVFSFINDFIRSTFILEW
#define PFNVFSFINDNEXTFILE			PFNVFSFINDNEXTFILEW
#define PFNVFSPROPGET				PFNVFSPROPGETW
#define PFNVFSCONTEXTVERB			PFNVFSCONTEXTVERBW
#define PFNVFSEXTRACTFILES			PFNVFSEXTRACTFILESW
#define PFNVFSPROPERTIES			PFNVFSPROPERTIESW
#define PFNVFSGETFREEDISKSPACE		PFNVFSGETFREEDISKSPACEW
#define PFNVFSGETCONTEXTMENU		PFNVFSGETCONTEXTMENUW
#define PFNVFSGETDROPMENU			PFNVFSGETDROPMENUW
#if ( VFSPLUGINVERSION >= 2 )
#define PVNVFSBATCHOPERATION		PVNVFSBATCHOPERATIONW
#endif
#if ( VFSPLUGINVERSION >= 3 )
#define PFNVFSGETERRORMSG			PFNVFSGETERRORMSGW
#endif
#else
#define PFNVFSIDENTIFY				PFNVFSIDENTIFYA
#define PFNVFSGETCUSTOMCOLUMNS		PFNVFSGETCUSTOMCOLUMNSA
#define PFNVFSQUERYPATH				PFNVFSQUERYPATHA
#define PFNVFSGETPREFIXLIST			PFNVFSGETPREFIXLISTA
#define PFNVFSREADDIRECTORY			PFNVFSREADDIRECTORYA
#define PFNVFSGETPATHDISPLAYNAME	PFNVFSGETPATHDISPLAYNAMEA
#define PFNVFSGETPATHPARENTROOT		PFNVFSGETPATHPARENTROOTA
#define PFNVFSGETFILEINFORMATION	PFNVFSGETFILEINFORMATIONA
#define PFNVFSGETFILEDESCRIPTION	PFNVFSGETFILEDESCRIPTIONA
#define PFNVFSGETFILEICON			PFNVFSGETFILEICONA
#define PFNVFSCREATEFILE			PFNVFSCREATEFILEA
#define PFNVFSMOVEFILE				PFNVFSMOVEFILEA
#define PFNVFSDELETEFILE			PFNVFSDELETEFILEA
#define PFNVFSSETFILETIME			PFNVFSSETFILETIMEA
#define PFNVFSSETFILEATTR			PFNVFSSETFILEATTRA
#define PFNVFSGETFILEATTR			PFNVFSGETFILEATTRA
#define PFNVFSSETFILECOMMENT		PFNVFSSETFILECOMMENTA
#define PFNVFSGETFILECOMMENT		PFNVFSGETFILECOMMENTA
#define PFNVFSCREATEDIRECTORY		PFNVFSCREATEDIRECTORYA
#define PFNVFSREMOVEDIRECTORY		PFNVFSREMOVEDIRECTORYA
#define PFNVFSGETFILESIZE			PFNVFSGETFILESIZEA
#define PFNVFSFINDFIRSTFILE			PFNVFSFINDFIRSTFILEA
#define PFNVFSFINDNEXTFILE			PFNVFSFINDNEXTFILEA
#define PFNVFSPROPGET				PFNVFSPROPGETA
#define PFNVFSCONTEXTVERB			PFNVFSCONTEXTVERBA
#define PFNVFSEXTRACTFILES			PFNVFSEXTRACTFILESA
#define PFNVFSPROPERTIES			PFNVFSPROPERTIESA
#define PFNVFSGETFREEDISKSPACE		PFNVFSGETFREEDISKSPACEA
#define PFNVFSGETCONTEXTMENU		PFNVFSGETCONTEXTMENUA
#define PFNVFSGETDROPMENU			PFNVFSGETDROPMENUA
#if ( VFSPLUGINVERSION >= 2 )
#define PVNVFSBATCHOPERATION		PVNVFSBATCHOPERATIONA
#endif
#if ( VFSPLUGINVERSION >= 3 )
#define PFNVFSGETERRORMSG			PFNVFSGETERRORMSGW
#endif
#endif

// Custom Directory Opus file errors
#define VFSERR_COPY_INTO_ITSELF			-2
#define VFSERR_NOT_SUPPORTED			-3
#define VFSERR_MOVE_INTO_SAMEDIR		-4
#define VFSERR_DIR_ALREADY_EXISTS		-5
#define VFSERR_FILE_IS_DIR				-6
#define VFSERR_BADLINK					-7
#define VFSERR_NOTEXPORTFILE			-8
#define VFSERR_NORECYCLEBIN				-9
#define VFSERR_RECYCLETOOBIG			-10
#define VFSERR_NOPRINTHANDLER			-11
#define VFSERR_BADZIPFILE				-12
#define VFSERR_GENERALERRMSG			-13
#define VFSERR_WRITEPROTECTED			-14
#define VFSERR_WRITEPROTECTEDZIP		-15
#define VFSERR_ZIPISDIR					-16
#define VFSERR_CANTRENAMEFOLDERS		-17
#define VFSERR_SHARINGVIOLATION			-18
#define VFSERR_ALREADYINCOLL			-19
#define VFSERR_CANTCOPYTOCOLLROOT		-20
#define VFSERR_NOMOVETOCOLLECTION		-21
#define VFSERR_NOJOINTOCOLLECTION		-22
#define VFSERR_NODROPDATATOCOLLECTION	-23
#define VFSERR_NOCOLLINCOLL				-24
#define VFSERR_FEATURENOTENABLED		-25
#define VFSERR_UNKNOWNERROR				-26
#define VFSERR_CANTCOPYFILEOVERITSELF	-27
#define VFSERR_CANTCHANGEZIPCASE		-28
#if ( VFSPLUGINVERSION >= 2 )
#define VFSERR_NOT_EXTRACTABLE			-29
#endif


// Reinitialise message for VFS_Configure function
#define DVFSPLUGINMSG_REINITIALIZE		(WM_APP + 0xfff)

#endif

