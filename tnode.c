/* HTML Tidy Lua 5.0 Bindings
   Copyright (c) 2006 Promixis, LLC 
   Author: Ron Bessems
   Date: Oct 26, 2006

   Licensed under MIT License.   

   Methods for the Tidy Node Object.
*/

#include "tnode.h"

static pTidyNode toTidyNode(lua_State *L, int cindex )
{
    pTidyNode t = (pTidyNode)luaL_checkudata(L, cindex, LUATIDY_NODE_HANDLE);
    if (!t ) luaL_argerror(L, cindex, "Invalid Lua Tidy Node Object");
    if (!t->node) luaL_error(L, "attempting to use a closed Tidy Object");
        return t;
}


// returns a table containing the attributes.
// returns nothing if there are no attributes.
int lua_tidy_node_getAttribute(lua_State *L)
{    
    pTidyNode n = toTidyNode(L,1);    
    return push_node_attributes(L, n->node);
}

// cleanup.
int lua_tidy_node_gc(lua_State *L)
{    
    pTidyNode n = toTidyNode(L,1);    
    doc_unregister_node(n);
    n->node = NULL;
    return 0;
}

// node navigation routines.
int lua_tidy_node_next(lua_State *L)
{
    pTidyNode n = toTidyNode(L,1);
    return push_node(L, tidyGetNext(n->node), n->tidy);
}

int lua_tidy_node_prev(lua_State *L)
{
    pTidyNode n = toTidyNode(L,1);
    return push_node(L, tidyGetPrev(n->node), n->tidy);
}

int lua_tidy_node_child(lua_State *L)
{
    pTidyNode n = toTidyNode(L,1);
    return push_node(L, tidyGetChild(n->node), n->tidy);
}

int lua_tidy_node_parent(lua_State *L)
{
    pTidyNode n = toTidyNode(L,1);
    return push_node(L, tidyGetParent(n->node), n->tidy);
}

int lua_tidy_node_getType(lua_State *L)
{
    pTidyNode n = toTidyNode(L,1);
    lua_pushnumber(L, tidyNodeGetType (n->node));    
    return 1;
}

int lua_tidy_node_getName(lua_State *L)
{
    pTidyNode n = toTidyNode(L,1);
    lua_pushstring(L, tidyNodeGetName (n->node));    
    return 1;
}
 
int lua_tidy_node_hasText(lua_State *L)
{
    pTidyNode n = toTidyNode(L,1);
    lua_pushboolean(L,tidyNodeHasText (n->tidy->tdoc, n->node));
    return 1;
}


int lua_tidy_node_getText(lua_State *L)
{
    pTidyNode n = toTidyNode(L,1);
    return push_node_text(L, n->tidy->tdoc,n->node);    
}

static const struct luaL_reg luatidy_node_meths[] =
{
    {"getAttributes", lua_tidy_node_getAttribute},
    {"getName", lua_tidy_node_getName},
    {"getType", lua_tidy_node_getType},
    {"getText", lua_tidy_node_getText},
    {"hasText", lua_tidy_node_hasText},
    {"next", lua_tidy_node_next},
    {"prev", lua_tidy_node_prev},
    {"child", lua_tidy_node_child},
    {"parent", lua_tidy_node_parent},    
	{"__gc", lua_tidy_node_gc},
	{0, 0}
};


void createNodeMetaTable(lua_State *L)
{
    createmeta(L,LUATIDY_NODE_HANDLE);    
	luaL_openlib (L, 0, luatidy_node_meths, 0);    
    lua_pop(L,1);  
}
