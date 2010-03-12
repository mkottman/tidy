#ifndef __SUPPORT_H__
#define __SUPPOPT_H__

#include "htmltidy.h"

void createmeta (lua_State *L, const char * name);

void doc_register_node ( pTidy t, pTidyNode n );
void doc_unregister_node ( pTidyNode n );
void doc_clear_all_nodes (pTidy t);

int push_node( lua_State *L , TidyNode Node, pTidy t);
int push_node_attributes(lua_State *L, TidyNode node);
int push_node_text(lua_State *L, TidyDoc doc, TidyNode node );

#endif
