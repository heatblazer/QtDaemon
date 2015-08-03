#include "xmltest.h"

void parseDirectoryAddToList(DList* list, xmlDocPtr doc, xmlNodePtr cur) {
    xmlChar* key;
    cur = cur->xmlChildrenNode;
    while ( cur != NULL ) {
        if ( (!xmlStrcmp(cur->name, (const xmlChar*) "directory"))) {
            key= xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            printf("keyword: %s\n", key);
            xmlFree(key);
        } else {
            addFront((char*)cur->content, list);
        }
        cur = cur->next;
    }
    return ;
}

DList* main_xml(int argc, char **argv) {
    xmlDocPtr doc;
    xmlNodePtr cur;
    DList* list = createList("new list for xml");
    doc = xmlParseFile(argv[1]);
    if ( doc == NULL ) {
        fprintf(stdout, "ERROR - no file \n");
        return NULL;
    }
    cur = xmlDocGetRootElement(doc);
    if ( cur == NULL ) {
        fprintf(stdout, "ERROR - no root document \n");
        return NULL;
    }

    if ( xmlStrcmp(cur->name, (const xmlChar*) "DirectoryEntry") ) {
        fprintf(stdout, "Document format wrong!\n");
        xmlFreeDoc(doc);
        return NULL;
    }

    cur = cur->xmlChildrenNode;
    while ( cur != NULL ) {
        if ( (!xmlStrcmp(cur->name, (const xmlChar*) "directory"))) {
            parseDirectoryAddToList(list, doc, cur);
        }
        cur = cur->next;
    }
    return list;
}
