Lua htmltidy bindings
---------------------

Copyright 2006(c) Promixis, LLC
Author Ron Bessems
Licensed under the MIT License.

This library provides lua bindings for the HTML Tidy library.
http://tidy.sourceforge.net/

Tested on Windows and Linux.

To compile you'll probably have to change include and library paths
both on Windows and Linux. If you do not know how to do this do not 
email me.

Ron

History
-------
October 27 Project start.
October 28 Moved parseToTable from lua to c and named it toTable.
October 29 Split project into multiple files added additional functions
           to the document object.

Version information
--------------------

On windows I used source code obtained from
http://dev.int64.org/tidy.html
compiled with MSVC6 reports.
HTMLTidy reports: 24 October 2006

On Linux, Ubuntu Dapper Drake
I used the HTMLTidy that comes with the distro 
which reports as 1 September 2005

Documentation
-------------

<tidy object> = htmltidy.new()
  on Windows with the new Hashing routines best to use 1 object
  per parse.
    
Tidy Object
-----------
<node object> = <tidy>:getRoot ()
    returns the root node of this document
    
num = <tidy>:setOpt( <option>, <value> )
    the options are listed under htmltidy.opt
    documentation for them can be found here
    http://tidy.sourceforge.net/docs/api/tidyenum_8h.html#a395

<cleaned html>, <error text>, <error value> = <tidy>:easyClean( <html string> )
    error value: 0 = ok , 1 = warning, 2= error, < 0 severe error.

<error value> = <tidy>:parse( <html string> )
    error value: 0 = ok , 1 = warning, 2= error, < 0 severe error.
    
<error value> = <tidy>:cleanAndRepair ( )
    error value: 0 = ok , 1 = warning, 2= error, < 0 severe error.
    
<error value> = <tidy>:runDiagnostics( )
    error value: 0 = ok , 1 = warning, 2= error, < 0 severe error.
    
<string> = <tidy>:saveToString( )
    saves the dom tree as HTML

<table> = <tidy>:toTable()
    exports the dom tree as a lua table. Very similar to luaexpats lom module but
	more forgiving to bad html thanks to the HTMLTidy Library

<string> = <tidy>:getError()
	returns the error and warning information.

<number> = <tidy>:detectedHtmlVersion()
	returns the HTML version that was detected.

<bool> = <tidy>:detectedXhtml()
	true if the document was found to be an XHTML document.

<bool> = <tidy>:detectedGenericXml()
	true if the document was found to be an Generic XHTML document.

<number> = <tidy>:errorCount()
	number of errors detected.

<number> = <tidy>:warningCount()
	number of warnings.

<number> = <tidy>:accessWarningCount()
	number of accessibility warnings.

<number> = <tidy>:setCharEncoding( <char encoding string> )
	sets the character encoding for in and output.
	Values include: ascii, latin1, raw, utf8, iso2022, mac, win1252, utf16le, utf16be, utf16, big5 and shiftjis. Case in-sensitive.

<tidy>:errorSummary()
	outputs a detailed summary to the Error buffer.

<tidy>:generalInfo()
	outputs general information to the error buffer.


Node Object
-----------

<node object> = <node object>:next()
<node object> = <node object>:prev()
<node object> = <node object>:child()
<node object> = <node object>:parent()
    tree traversal functions
    
<boolean> = <node object>:hasText()
    returns true if the current node has text
    
<string> = <node object>:getText()    
    returns nil or the text of the current node
    
<number> = <node object>:getType()
    returns the type of node. The values can be found in
    htmltidy.nodeType
    http://tidy.sourceforge.net/docs/api/tidyenum_8h.html#a402
    
<string> = <node object>:getName()
    returns the name of the tag (e.g. <html> returns html)
    
<table> = <node object>:getAttributes()
    returns the attributes of that node as follows:
    {
        [1] = "name",
        [2] = "classname",
        ["classname"] = "funny",
        ["name"] = "test",
    }



