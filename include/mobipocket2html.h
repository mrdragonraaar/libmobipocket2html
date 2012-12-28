/**
 * mobipocket2html.h
 * 
 * (c)2012 mrdragonraaar.com
 */
#ifndef MOBIPOCKET2HTML_H
#define MOBIPOCKET2HTML_H

#include <mobipocket/mobipocket.h>
#include "mobipocket2html_a.h"
#include "mobipocket2html_img.h"

uint32_t mobipocket2html(char *html, const mobipocket_t mobipocket);
uint32_t mobipocket2html_length(const mobipocket_t mobipocket);

#endif /* MOBIPOCKET2HTML_H */
