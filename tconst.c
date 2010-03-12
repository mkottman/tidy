/* HTML Tidy Lua 5.0 Bindings
   Copyright (c) 2006 Promixis, LLC 
   Author: Ron Bessems
   Date: Oct 26, 2006

   Licensed under MIT License.   

   Constants exported to Lua.
*/

#include "tconst.h"


/* Fast set table macro */
#define LUA_SET_TABLE(context, key_type, key, value_type, value) \
	lua_push##key_type(context, key); \
	lua_push##value_type(context, value); \
	lua_settable(context, -3);


/* ******************************************************************************************* */
/* Constants */
/* ******************************************************************************************* */

void export_tidy_info(lua_State *L)
{
    LUA_SET_TABLE(L, string, "_COPYRIGHT", string, "Copyright (c) 2006 Promixis, LLC");
    LUA_SET_TABLE(L, string, "_DESCRIPTION", string, "HTML Tidy Bindings for Lua");
    LUA_SET_TABLE(L, string, "_NAME", string, LUATIDY_LIBNAME);
    LUA_SET_TABLE(L, string, "_VERSION", string, LUATIDY_VERSION);
    LUA_SET_TABLE(L, string, "_TIDYVERSION", string, tidyReleaseDate());
}

void export_tidy_nodeType ( lua_State * L)
{
    lua_pushstring(L, "nodeType");
    lua_newtable(L);
    
    LUA_SET_TABLE(L, string, "Root", number,TidyNode_Root );
    LUA_SET_TABLE(L, string, "DocType", number,TidyNode_DocType );
    LUA_SET_TABLE(L, string, "Comment", number,TidyNode_Comment );
    LUA_SET_TABLE(L, string, "ProcIns", number, TidyNode_ProcIns);
    LUA_SET_TABLE(L, string, "Text", number, TidyNode_Text);
    LUA_SET_TABLE(L, string, "Start", number, TidyNode_Start);
    LUA_SET_TABLE(L, string, "End", number, TidyNode_End);
    LUA_SET_TABLE(L, string, "StartEnd", number, TidyNode_StartEnd);
    LUA_SET_TABLE(L, string, "CDATA", number, TidyNode_CDATA);
    LUA_SET_TABLE(L, string, "Section", number, TidyNode_Section);
    LUA_SET_TABLE(L, string, "Asp", number, TidyNode_Asp);
    LUA_SET_TABLE(L, string, "Jste", number,TidyNode_Jste );
    LUA_SET_TABLE(L, string, "Php", number, TidyNode_Php);
    LUA_SET_TABLE(L, string, "XmlDecl", number, TidyNode_XmlDecl);
    
    lua_settable(L,-3);    
}

void export_tidy_options(lua_State *L)
{
    lua_pushstring(L, "opt");
    lua_newtable(L);
    LUA_SET_TABLE(L, string, "IndentSpaces", number, TidyIndentSpaces);
    LUA_SET_TABLE(L, string, "WrapLen", number, TidyWrapLen);
    LUA_SET_TABLE(L, string, "TabSize", number, TidyTabSize);    
    LUA_SET_TABLE(L, string, "CharEncoding", number, TidyCharEncoding);
    LUA_SET_TABLE(L, string, "InCharEncoding", number, TidyInCharEncoding);
    LUA_SET_TABLE(L, string, "OutCharEncoding", number, TidyOutCharEncoding);
    LUA_SET_TABLE(L, string, "Newline", number, TidyNewline);
    LUA_SET_TABLE(L, string, "DoctypeMode", number, TidyDoctypeMode);
    LUA_SET_TABLE(L, string, "Doctype", number, TidyDoctype);
    LUA_SET_TABLE(L, string, "DuplicateAttrs", number, TidyDuplicateAttrs);
    LUA_SET_TABLE(L, string, "AltText", number, TidyAltText);
    LUA_SET_TABLE(L, string, "SlideStyle", number, TidySlideStyle);
    LUA_SET_TABLE(L, string, "ErrFile", number, TidyErrFile);
    LUA_SET_TABLE(L, string, "OutFile", number, TidyOutFile);
    LUA_SET_TABLE(L, string, "WriteBack", number, TidyWriteBack );
    LUA_SET_TABLE(L, string, "ShowMarkup", number, TidyShowMarkup);
    LUA_SET_TABLE(L, string, "ShowWarnings", number,TidyShowWarnings );
    LUA_SET_TABLE(L, string, "Quiet", number, TidyQuiet);
    LUA_SET_TABLE(L, string, "IndentContent", number, TidyIndentContent);
    LUA_SET_TABLE(L, string, "HideEndTags", number, TidyHideEndTags);
    LUA_SET_TABLE(L, string, "XmlTags", number, TidyXmlTags);
    LUA_SET_TABLE(L, string, "XmlOut", number, TidyXmlOut);
    LUA_SET_TABLE(L, string, "XhtmlOut", number, TidyXhtmlOut);
    LUA_SET_TABLE(L, string, "HtmlOut", number,TidyHtmlOut );
    LUA_SET_TABLE(L, string, "XmlDecl", number,TidyXmlDecl );
    LUA_SET_TABLE(L, string, "UpperCaseTags", number,TidyUpperCaseTags );
    LUA_SET_TABLE(L, string, "UpperCaseAttrs", number,TidyUpperCaseAttrs );
    LUA_SET_TABLE(L, string, "MakeBare", number, TidyMakeBare);
    LUA_SET_TABLE(L, string, "MakeClean", number, TidyMakeClean);
    LUA_SET_TABLE(L, string, "LogicalEmphasis", number, TidyLogicalEmphasis);
    LUA_SET_TABLE(L, string, "DropPropAttrs", number, TidyDropPropAttrs);
    LUA_SET_TABLE(L, string, "DropFontTags", number, TidyDropFontTags);
    LUA_SET_TABLE(L, string, "DropEmptyParas", number, TidyDropEmptyParas);    
    LUA_SET_TABLE(L, string, "FixComments", number, TidyFixComments);
    LUA_SET_TABLE(L, string, "BreakBeforeBR", number, TidyBreakBeforeBR);
    LUA_SET_TABLE(L, string, "BurstSlides", number, TidyBurstSlides);
    LUA_SET_TABLE(L, string, "NumEntities", number,TidyNumEntities );
    LUA_SET_TABLE(L, string, "QuoteMarks", number, TidyQuoteMarks);
    LUA_SET_TABLE(L, string, "QuoteNbsp", number, TidyQuoteNbsp);
    LUA_SET_TABLE(L, string, "QuoteAmpersand", number, TidyQuoteAmpersand);
    LUA_SET_TABLE(L, string, "WrapAttVals", number, TidyWrapAttVals);  
    LUA_SET_TABLE(L, string, "WrapScriptlets", number,TidyWrapScriptlets );
    LUA_SET_TABLE(L, string, "WrapSection", number,TidyWrapSection );
    LUA_SET_TABLE(L, string, "WrapAsp", number, TidyWrapAsp);
    LUA_SET_TABLE(L, string, "WrapJste", number, TidyWrapJste);
    LUA_SET_TABLE(L, string, "WrapPhp", number, TidyWrapPhp);
    LUA_SET_TABLE(L, string, "FixBackslash", number, TidyFixBackslash);   
    LUA_SET_TABLE(L, string, "IndentAttributes", number, TidyIndentAttributes);
    LUA_SET_TABLE(L, string, "XmlPIs", number, TidyXmlPIs);
    LUA_SET_TABLE(L, string, "XmlSpace", number, TidyXmlSpace);
    LUA_SET_TABLE(L, string, "EncloseBodyText", number,TidyEncloseBodyText );
    LUA_SET_TABLE(L, string, "EncloseBlockText", number,TidyEncloseBlockText );
    LUA_SET_TABLE(L, string, "KeepFileTimes", number, TidyKeepFileTimes);   
    LUA_SET_TABLE(L, string, "Word2000", number, TidyWord2000);
    LUA_SET_TABLE(L, string, "Mark", number, TidyMark);
    LUA_SET_TABLE(L, string, "Emacs", number, TidyEmacs);
    LUA_SET_TABLE(L, string, "EmacsFile", number, TidyEmacsFile);
    LUA_SET_TABLE(L, string, "LiteralAttribs", number,TidyLiteralAttribs );
    LUA_SET_TABLE(L, string, "BodyOnly", number, TidyBodyOnly);   
    LUA_SET_TABLE(L, string, "FixUri", number, TidyFixUri);
    LUA_SET_TABLE(L, string, "LowerLiterals", number,TidyLowerLiterals );  
    LUA_SET_TABLE(L, string, "HideComments", number, TidyHideComments);
    LUA_SET_TABLE(L, string, "IndentCdata", number, TidyIndentCdata);  
    LUA_SET_TABLE(L, string, "ForceOutput", number, TidyForceOutput);
    LUA_SET_TABLE(L, string, "ShowErrors", number, TidyShowErrors);  
    LUA_SET_TABLE(L, string, "AsciiChars", number, TidyAsciiChars);
    LUA_SET_TABLE(L, string, "JoinClasses", number,TidyJoinClasses );   
    LUA_SET_TABLE(L, string, "JoinStyles", number, TidyJoinStyles);
    LUA_SET_TABLE(L, string, "EscapeCdata", number, TidyEscapeCdata);  
    LUA_SET_TABLE(L, string, "ReplaceColor", number, TidyReplaceColor);      
    LUA_SET_TABLE(L, string, "CSSPrefix", number, TidyCSSPrefix);
    LUA_SET_TABLE(L, string, "InlineTags", number, TidyInlineTags);     
    LUA_SET_TABLE(L, string, "BlockTags", number, TidyBlockTags);
    LUA_SET_TABLE(L, string, "EmptyTags", number, TidyEmptyTags); 
    LUA_SET_TABLE(L, string, "PreTags", number, TidyPreTags);
    LUA_SET_TABLE(L, string, "AccessibilityCheckLevel", number, TidyAccessibilityCheckLevel); 
    LUA_SET_TABLE(L, string, "VertSpace", number, TidyVertSpace);    
    LUA_SET_TABLE(L, string, "MergeDivs", number, TidyMergeDivs);    
    lua_settable(L,-3);
}

