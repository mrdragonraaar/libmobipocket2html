/**
 * mobipocket2html_img.c
 *
 * (c)2012 mrdragonraaar.com
 */
#include "mobipocket2html_img.h"

uint16_t mobipocket2html_recindex(const char **text);

/**
 * Convert record index attributes to src attributes in MOBIPocket text.
 * @param *html converted MOBIPocket text.
 * @param *text MOBIPocket text.
 * @param mobipocket MOBIPocket.
 * @return uint32_t new text length.
 */
uint32_t mobipocket2html_recindex2src(char *html, const char *text, 
   const mobipocket_t mobipocket)
{
	*html = '\0';
	const char *in = text;
	uint32_t textpos = 0;

	uint16_t recindex;
	while ((recindex = mobipocket2html_recindex(&in)))
	{
		uint32_t len = (in - text) - textpos;

		strncat(html, text + textpos, len);

		uint32_t image_length = mobipocket_image_base64_length(
		   mobipocket, recindex - 1);
		char image[image_length];
		mobipocket_image_base64(image, mobipocket, recindex - 1);

		strncat(html, IMG_SRC_PREFIX, strlen(IMG_SRC_PREFIX));
		strncat(html, image, image_length);
		strncat(html, "\"", 1);

		in += (strlen(RECINDEX_SEARCH_STR) + RECINDEX_LEN + 1);
		textpos = in - text;
	}
	strcat(html, text + textpos);

	return strlen(html);
}

/**
 * Get length of text after record index to src attribute conversion.
 * @param *text MOBIPocket text.
 * @param mobipocket MOBIPocket.
 * @return uint32_t new text length.
 */
uint32_t mobipocket2html_recindex2src_length(const char *text, 
   const mobipocket_t mobipocket)
{
	return strlen(text) + 
	   mobipocket2html_recindex2src_length_offset(text, mobipocket);
}

/**
 * Get length offset of text after record index to src attribute conversion.
 * @param *text MOBIPocket text.
 * @param mobipocket MOBIPocket.
 * @return int32_t text length offset.
 */
int32_t mobipocket2html_recindex2src_length_offset(const char *text, 
   const mobipocket_t mobipocket)
{
	int32_t length_offset = 0;

	uint16_t recindex;
	while ((recindex = mobipocket2html_recindex(&text)))
	{
		uint32_t image_length = mobipocket_image_base64_length(
		   mobipocket, recindex - 1);
		length_offset += strlen(IMG_SRC_PREFIX) + 1;
		length_offset += image_length;
		length_offset -= (strlen(RECINDEX_SEARCH_STR) + 
		   RECINDEX_LEN + 1);

		text += (strlen(RECINDEX_SEARCH_STR) + RECINDEX_LEN + 1);
	}

	return length_offset;
}

/**
 * Find the next record index attribute in MOBIPocket text.
 * @param **text MOBIPocket text.
 * @return uint16_t record index attribute or 0 if not found.
 */
uint16_t mobipocket2html_recindex(const char **text)
{
	if ((*text = strstr(*text, RECINDEX_SEARCH_STR)) != NULL)
        {
                return (uint16_t)strtol(*text + strlen(RECINDEX_SEARCH_STR), 
		   (char**)NULL, 10);
        }

	return 0;
}

/**
 * Get MOBIPocket base64 encoded image.
 * @param *image base64 encoded image.
 * @param mobipocket MOBIPocket.
 * @param offset image record offset.
 * @return uint32_t base64 encoded image length.
 */
uint32_t mobipocket_image_base64(char *image, const mobipocket_t mobipocket,
   uint16_t offset)
{
        uint32_t len = mobipocket_image_base64_length(mobipocket, offset);
        if (len)
        {
                int index = mobipocket_image_record_offset2index(mobipocket,
                   offset);
                Base64encode(image,
                   mobipocket_image_record(mobipocket, index),
                   mobipocket_image_record_length(mobipocket, index));
        }

        return len;
}

/**
 * Get length of MOBIPocket base64 encoded image.
 * @param mobipocket MOBIPocket.
 * @param offset image record offset.
 * @return uint32_t base64 encoded image length.
 */
uint32_t mobipocket_image_base64_length(const mobipocket_t mobipocket, 
   uint16_t offset)
{
        uint16_t index = mobipocket_image_record_offset2index(mobipocket,
           offset);
	return Base64encode_len(mobipocket_image_record_length(mobipocket, 
	   index));
}

