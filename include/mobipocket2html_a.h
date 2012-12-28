/**
 * mobipocket2html_a.h
 * 
 * (c)2012 mrdragonraaar.com
 */
#ifndef MOBIPOCKET2HTML_A_H
#define MOBIPOCKET2HTML_A_H

#include <mobipocket/mobipocket.h>

#define FILEPOS_SEARCH_STR "filepos="
#define FILEPOS_LEN 10
#define A_HREF_PREFIX "href=\"#"
#define A_ID_PREFIX "<a id=\""
#define A_ID_SUFFIX "\"></a>"

uint32_t mobipocket2html_filepos2href(char *html, const char *text);
uint32_t mobipocket2html_filepos2href_length(const char *text);
int32_t mobipocket2html_filepos2href_length_offset(const char *text);

uint32_t mobipocket2html_filepos2id(char *html, const char *text);
uint32_t mobipocket2html_filepos2id_length(const char *text);
int32_t mobipocket2html_filepos2id_length_offset(const char *text);

#endif /* MOBIPOCKET2HTML_A_H */
