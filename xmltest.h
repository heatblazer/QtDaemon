#ifndef XMLTEST_H
#define XMLTEST_H

#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/xmlversion.h>
#include <libxml2/libxml/xmlexports.h>
#include <stdio.h>
#include <libxml2/libxml/xmlreader.h>

#include "DList.h"

DList* main_xml(int, char**);

void parseDirectoryAddToList(DList*, xmlDocPtr, xmlNodePtr);

#endif // XMLTEST_H
