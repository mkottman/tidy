/* HTML Tidy Lua 5.0 Bindings
   Copyright (c) 2006 Promixis, LLC 
   Author: Ron Bessems
   Date: Oct 26, 2006

   Licensed under MIT License.   

   
   Methods for the TidyDocument object.

*/

#include "tdoc.h"

static pTidy toTidy(lua_State *L, int cindex )
{
    pTidy t = (pTidy)luaL_checkudata(L, cindex, LUATIDY_HANDLE);
    if (!t ) luaL_argerror(L, cindex, "Invalid Lua Tidy Object");
    if (!t->tdoc) luaL_error(L, "attempting to use a closed Tidy Object");
        return t;
}


// returns the contents of the error buffer.
int lua_tidy_getErrorBuffer(lua_State *L)
{
    pTidy t = toTidy(L,1);
    lua_pushlstring(L, (char*)t->errbuf.bp,t->errbuf.size);
    return 1;
}

// returns the root node object.
int lua_tidy_getRootNode ( lua_State *L)
{
    pTidy t = toTidy(L,1);
    TidyNode tn = tidyGetRoot(t->tdoc);
    return push_node(L, tn, t);
}


// parses the lua string to a 'dom' like object.
int lua_tidy_parseString( lua_State *L)
{
    pTidy t = toTidy(L,1);
    const char * source = lua_tostring(L,2);
    lua_pushnumber(L, tidyParseString(t->tdoc, source));
    return 1;
}

// cleans up the tree.
int lua_tidy_cleanAndRepair(lua_State *L)
{
    pTidy t = toTidy(L,1);    
    lua_pushnumber(L, tidyCleanAndRepair(t->tdoc));
    return 1;    
}

// returns warnings.
int lua_tidy_runDiagnostics (lua_State *L)
{
    pTidy t = toTidy(L,1);
    lua_pushnumber(L, tidyRunDiagnostics (t->tdoc));
    return 1;    
}

// formats the 'dom' tree into HTML output.
int lua_tidy_saveString(lua_State *L)
{
    pTidy t = toTidy(L,1);
    TidyBuffer output;
    tidyBufInit(&output);
    lua_pushnumber(L, tidySaveBuffer(t->tdoc, &output));
    lua_pushlstring(L, (char*)output.bp, output.size);
    tidyBufFree( &output );
    return 1;        
}

// quick and dirty shortcut function.
int lua_tidy_easyClean ( lua_State *L )
{
    TidyBuffer output;
    TidyBuffer errbuf;
    int rc;
	pTidy t;
	const char * input;

    tidyBufInit(&output);
    tidyBufInit(&errbuf);
    
    rc = -1;
    
    t = toTidy(L,1);
    input = lua_tostring(L,2);
    
    rc = tidySetErrorBuffer( t->tdoc, &errbuf );
    if ( rc >= 0 )
        rc = tidyParseString( t->tdoc, input );
    if ( rc >= 0 )
        rc = tidyCleanAndRepair( t->tdoc );
    if ( rc >= 0 )
        rc = tidyRunDiagnostics( t->tdoc );
    if ( rc >= 0 )
        rc = tidySaveBuffer( t->tdoc, &output );    
    
    lua_pushlstring(L, (char*)output.bp,output.size);
    if ( rc != 0  )
        lua_pushlstring(L, (char*)errbuf.bp,errbuf.size);
    else
        lua_pushnil(L);
    
    lua_pushnumber(L, rc);
    
    tidyBufFree( &output );
    tidyBufFree( &errbuf );
    
    
    return 3;
}

//helper
static int luatotidy_bool( lua_State *L, int cindex)
{
    if ( lua_toboolean(L, cindex) )    
        return yes;
    else
        return no;
}

static int tidytolua_bool ( Bool b )
{
	if ( b==yes ) 
		return TRUE;
	else
		return FALSE;

}

// set option for the tidy object.
int lua_tidy_setOpt ( lua_State *L )
{
    BOOL ok=FALSE;
    pTidy t = toTidy(L,1);
    switch ( lua_type(L,3) ) 
    {
    case LUA_TBOOLEAN:
        ok = tidyOptSetBool(t->tdoc, (int)lua_tonumber(L,2), luatotidy_bool(L, 3));
        break;
    case LUA_TNUMBER:
        ok = tidyOptSetInt(t->tdoc, (int) lua_tonumber(L,2), (int) lua_tonumber(L, 3));
        break;        
    case LUA_TSTRING:
        ok = tidyOptSetValue(t->tdoc, (int) lua_tonumber(L,2), lua_tostring(L, 3));
        break;                
    }
    
    lua_pushboolean(L, ok>=0);
	return 1;
}

// c equivalent of table.insert(<table>, <object>)
// position is not supported.
// It assumes table is on stack position -2
// and object is on position -1.
int lua_tableinsert(lua_State *L)
{
	int n;

    if ( lua_type(L,-2) != LUA_TTABLE ) 
    {
        return 0;
    }
    
    n = luaL_getn(L, -2);
    lua_rawseti(L, -2, ++n);
    return 1;
}


/*lua_tidy_toTable comments.

  This code was translated to c from Lua to so we can include it into the metatable for the 
  tidydoc object. This gave us the additional advantage of speed, a ~17% speedup was realized.
  Also we now do not have to distribute a separate lua file.

  The table returned by this code is very similar to the tree return by luaexpats lom module.
  
  The original lua code was:

local function traverseNodes( t, node )
        
    local function traverseDeeper(t, node)
        
        local cnode
        
        cnode = node:child()
        while cnode do
            traverseNodes(t, cnode);
            cnode = cnode:next()
        end
    
    end    
    
    local nt = node:getType()
    
    if ( nt == htmltidy.nodeType.Text ) then
        if ( node:hasText() ) then
            table.insert(t, node:getText());
        end
        return
    end
    
    if (  nt == htmltidy.nodeType.Start ) or ( nt == htmltidy.nodeType.StartEnd ) then
    
        local tsub = {}
        local cnode;
        
        tsub.attr = node:getAttributes();
        tsub.tag = node:getName();
        if ( node:hasText() ) then
            table.insert(tsub, node:getText());
        end
        
        table.insert(t, tsub);        
        traverseDeeper(tsub, node)
        
        return
    end
    
    if ( nt == htmltidy.nodeType.Root ) then
        traverseDeeper(t, node)
        return
    end
end

function htmltidy.parseToTable ( tidy )
    local t = {}
    local node = tidy:getRoot();
    traverseNodes(t, node);
    return t
end
*/

// forward declaration.
static void traverseNodes(TidyDoc doc, lua_State *L, TidyNode node);

static void traverseDeeper(TidyDoc doc, lua_State *L, TidyNode node)
{
    TidyNode child;
    
    child = tidyGetChild ( node );
    while ( child ) 
    {
        traverseNodes(doc, L, child);
        child = tidyGetNext ( child );
    }
}

static void traverseNodes(TidyDoc doc, lua_State *L, TidyNode node)
{
    TidyNodeType nt = tidyNodeGetType ( node );
    
    switch (nt)
    {
        case TidyNode_Text:
            if ( tidyNodeHasText (doc, node) )
            {
                if ( push_node_text(L, doc, node) == 1 )
                {
                    lua_tableinsert(L);
                }
            }
            break;
        case TidyNode_Start:
        case TidyNode_StartEnd:
            lua_newtable(L);
        
            if ( push_node_attributes(L, node) == 1 )
            {
                lua_pushstring(L, "attr");
                lua_insert(L,-2);
                lua_rawset(L,-3);
            }
            
            lua_pushstring(L,"tag");
            lua_pushstring(L, tidyNodeGetName (node));  
            lua_rawset(L,-3);
            traverseDeeper(doc, L, node);            
            lua_tableinsert(L);            
            break;
        case TidyNode_Root:
            traverseDeeper(doc, L, node);
            break;
        default:
            // ignore. keep gcc compiler happy.
            break;
    }
}

int lua_tidy_toTable(lua_State*L)
{
    pTidy t = toTidy(L,1);

    TidyNode node = tidyGetRoot(t->tdoc);
    if (!node)
        return 0;
    
    lua_newtable(L);
    traverseNodes(t->tdoc, L, node);
    
    return 1;    
}


int lua_tidy_DetectedHtmlVersion(lua_State *L)
{
    pTidy t = toTidy(L,1);

	lua_pushnumber(L, tidyDetectedHtmlVersion (t->tdoc));
	return 1;
}


int lua_tidy_DetectedXhtml(lua_State *L)
{
    pTidy t = toTidy(L,1);

	lua_pushboolean(L, tidytolua_bool( tidyDetectedXhtml (t->tdoc)));
	return 1;
}

int lua_tidy_DetectedGenericXml(lua_State *L)
{
    pTidy t = toTidy(L,1);

	lua_pushboolean(L, tidytolua_bool( tidyDetectedGenericXml (t->tdoc)));
	return 1;
}


int lua_tidy_ErrorCount(lua_State *L)
{
    pTidy t = toTidy(L,1);

	lua_pushnumber(L, tidyErrorCount (t->tdoc));
	return 1;
}

int lua_tidy_WarningCount(lua_State *L)
{
    pTidy t = toTidy(L,1);

	lua_pushnumber(L, tidyWarningCount (t->tdoc));
	return 1;
}


int lua_tidy_AccessWarningCount(lua_State *L)
{
    pTidy t = toTidy(L,1);

	lua_pushnumber(L, tidyAccessWarningCount (t->tdoc));
	return 1;
}
   

int lua_tidy_SetCharEncoding(lua_State *L)
{
    pTidy t = toTidy(L,1);
	const char * enc = lua_tostring(L,2);
	lua_pushnumber(L, tidySetCharEncoding (t->tdoc, enc));
	return 1;
}
    

int lua_tidy_ErrorSummary(lua_State *L)
{
    pTidy t = toTidy(L,1);
	tidyErrorSummary(t->tdoc);
	return 0;
}

int lua_tidy_GeneralInfo(lua_State *L)
{
    pTidy t = toTidy(L,1);
	tidyGeneralInfo(t->tdoc);
	return 0;
}
    
 
// garbage collection, make sure we mark all opened nodes as expired.
int lua_tidy_gc ( lua_State *L )
{   
    pTidy t = toTidy(L,1);
    
    doc_clear_all_nodes(t); // all nodes are marked as expired.
    
    tidyRelease( t->tdoc );    
    
    tidyBufFree( &t->errbuf );        
    t->tdoc = NULL;
	return 0;
}


static const struct luaL_reg luatidy_meths[] =
{
    {"getRoot", lua_tidy_getRootNode},
	{"setOpt", lua_tidy_setOpt},
	{"easyClean", lua_tidy_easyClean},
    {"parse", lua_tidy_parseString},
    {"getError", lua_tidy_getErrorBuffer},
    {"cleanAndRepair", lua_tidy_cleanAndRepair},
    {"runDiagnostics", lua_tidy_runDiagnostics},
    {"saveToString", lua_tidy_saveString},
    {"toTable", lua_tidy_toTable},
	{"detectedHtmlVersion",lua_tidy_DetectedHtmlVersion},
	{"detectedXhtml", lua_tidy_DetectedXhtml},
	{"detectedGenericXml", lua_tidy_DetectedGenericXml},
	{"errorCount", lua_tidy_ErrorCount},
	{"warningCount",lua_tidy_WarningCount},
	{"accessWarningCount",lua_tidy_AccessWarningCount},
	{"setCharEncoding", lua_tidy_SetCharEncoding},
	{"errorSummary", lua_tidy_ErrorSummary},
	{"generalInfo", lua_tidy_GeneralInfo },
	{"__gc", lua_tidy_gc},
	{0, 0}
};


void createDocMetaTable(lua_State *L)
{
    createmeta(L,LUATIDY_HANDLE);    
	luaL_openlib (L, 0, luatidy_meths, 0);    
    lua_pop(L,1);   
}
