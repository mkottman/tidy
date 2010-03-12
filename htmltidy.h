#ifndef __HTML_TIDY_H__
#define __HTML_TIDY_H__



#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <tidy.h>
#include <buffio.h>

#ifndef BOOL 
#define BOOL int
#endif
    
#ifndef FALSE
#define FALSE (0)
#endif
    
#ifndef TRUE
#define TRUE (!FALSE)
#endif
    
#define LUATIDY_API	extern

#define LUATIDY_LIBNAME	"htmltidy"
#define LUATIDY_HANDLE	"htmltidymeta"
#define LUATIDY_NODE_HANDLE	    "htmltidymetanode"
#define LUATIDY_ATTRIB_HANDLE	"htmltidymetaattrib"
#define LUATIDY_VERSION "1.0.1"


struct tidy;    // forward declaration

// the structure that Lua uses to access the tidy Nodes.
typedef struct tidyNode {
    struct tidy * tidy;   
    TidyNode node;
} sTidyNode, *pTidyNode;

// bookkeeping 
typedef struct nodeListItem {
    pTidyNode node;
    struct nodeListItem *next;
} sNodeListItem, *pNodeListItem;

// the structure that lua uses to access the tidy Document.
typedef struct tidy {
	TidyDoc tdoc;    
    TidyBuffer errbuf;
    pNodeListItem nodeList;
} sTidy, *pTidy;


#include "support.h"
#include "tconst.h"
#include "tnode.h"
#include "tdoc.h"


#endif
