/**
 * mobipocket2html_img.h
 * 
 * (c)2012 mrdragonraaar.com
 */
#ifndef MOBIPOCKET2HTML_IMG_H
#define MOBIPOCKET2HTML_IMG_H

#include <mobipocket/mobipocket.h>
#include "base64.h"

#define RECINDEX_SEARCH_STR "recindex=\""
#define RECINDEX_LEN 5
#define IMG_SRC_PREFIX "src=\"data:image/jpg;base64,"

uint32_t mobipocket2html_recindex2src(char *html, const char *text, 
   const mobipocket_t mobipocket);
uint32_t mobipocket2html_recindex2src_length(const char *text, 
   const mobipocket_t mobipocket);
int32_t mobipocket2html_recindex2src_length_offset(const char *text, 
   const mobipocket_t mobipocket);

uint32_t mobipocket_image_base64(char *image, const mobipocket_t mobipocket,
   uint16_t offset);
uint32_t mobipocket_image_base64_length(const mobipocket_t mobipocket, 
   uint16_t offset);

#endif /* MOBIPOCKET2HTML_IMG_H */
