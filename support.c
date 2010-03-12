/* HTML Tidy Lua 5.0 Bindings
   Copyright (c) 2006 Promixis, LLC 
   Author: Ron Bessems
   Date: Oct 26, 2006

   Licensed under MIT License.   

   Supporting functions.
*/

#include "support.h"


void createmeta (lua_State *L, const char * name) 
{
	luaL_newmetatable(L, name);
	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -2);
	lua_rawset(L, -3);
}


/* ******************************************************************************************* */
/* Book keeping of nodes referenced from Lua */
/* we'll need to keep track of all the nodes handed out to Lua
   this is because when the tidyDoc gets garbage collected all 
   the nodes are no longer valid, however lua might still have
   references to them. So at that point we'll go through that
   list and NULL them out. */
/* ******************************************************************************************* */
void doc_register_node ( pTidy t, pTidyNode n )
{
    pNodeListItem i;

	if ( (!n) || ( !t ) )    
        return;

    i = (pNodeListItem)malloc ( sizeof ( sNodeListItem ));
    if (!i) 
        return;
    i->node = n;
    i->next = t->nodeList;
    t->nodeList = i;
}

// removes the node from the list and frees the storage
void doc_unregister_node ( pTidyNode n )
{
	pNodeListItem prev;
	pNodeListItem i;

    if ( !n ) 
        return;
    if ( !n->tidy)
        return;
       
    prev = NULL;
    i = n->tidy->nodeList;
    while ( i )
    {    
        if ( i->node == n ) 
        {
            if (prev)
            {
                prev->next = i->next;
            }
            else
            {
                n->tidy->nodeList = i->next;
            }
            free(i);
            return;
        }
        prev = i;
        i = i->next;
    }
    
}

// this goes through all the nodes and sets them to NULL so
// that subsequent access from Lua will simply error out instead of
// crash. This does NOT free the nodes!
void doc_clear_all_nodes (pTidy t)
{
    pNodeListItem next,i;

	if ( !t )
        return;
    
    
    i = t->nodeList;
    while ( i )
    {        
        next = i->next;
        
        i->node->node=NULL;
        free(i);
        
        i = next;
    }
}



/* Node operations ***********/
// this creates a new node object inside Lua.
int push_node( lua_State *L , TidyNode Node, pTidy t)
{
    pTidyNode n;

	if ( Node == 0 ) 
        return 0;
    
    n = (pTidyNode)lua_newuserdata(L, sizeof(sTidyNode));
	n->node = Node;
    n->tidy = t;
	luaL_getmetatable(L, LUATIDY_NODE_HANDLE);
	lua_setmetatable(L,-2);	    
    doc_register_node(t,n);
    return 1;
}

/* inserts the attributes into the table on top of stack
   if it returns 1, if it returns 0 there where no
   attributes and nothing was pushed onto the stack.
*/
int push_node_attributes(lua_State *L, TidyNode node)
{
    TidyAttr t;
    t = tidyAttrFirst ( node );
    if ( !t ) return 0;
    
    while ( t ) 
    {
        lua_pushstring(L, tidyAttrName (t));
        lua_pushstring(L, tidyAttrValue (t));
        lua_settable(L,-3);
        t = tidyAttrNext ( t );
    }
    return 1;
}

/* This function pushes the text of a tidynode onto the stack, if any.
   returns 1 if it pushed the text onto the stack and zero if not.
*/
int push_node_text(lua_State *L, TidyDoc doc, TidyNode node )
{
    int ret;
    TidyBuffer output;
    tidyBufInit(&output);
        
    if ( tidyNodeGetText (doc,node , &output) )
    {
        lua_pushlstring(L, (char*)output.bp, output.size );        
        ret = 1;
    }
    else
    {
        ret = 0;
    }
        
    tidyBufFree( &output );        
    return ret;
}
