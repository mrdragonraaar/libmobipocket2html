/**
 * mobipocket2html.c
 *
 * (c)2012 mrdragonraaar.com
 */
#include "mobipocket2html.h"

/**
 * Convert MOBIPocket text to html.
 * @param *html converted MOBIPocket text.
 * @param mobipocket MOBIPocket.
 * @return uint32_t new text length.
 */
uint32_t mobipocket2html(char *html, const mobipocket_t mobipocket)
{
	*html = '\0';

	uint32_t text_length = mobipocket_text_length(mobipocket);
	if (text_length)
	{
		/* Text */
		char *t1 = malloc(text_length * sizeof(char));
		char *t2 = malloc(text_length * sizeof(char));
		text_length = mobipocket_text(t1, mobipocket);
		strcpy(t2, t1);

		/* Links: id */
		text_length = mobipocket2html_filepos2id_length(t2);
		t1 = realloc(t1, text_length * sizeof(char));
		text_length = mobipocket2html_filepos2id(t1, t2);
		t2 = realloc(t2, text_length * sizeof(char));
		strcpy(t2, t1);

		/* Links: href */
		text_length = mobipocket2html_filepos2href_length(t2);
		t1 = realloc(t1, text_length * sizeof(char));
		text_length = mobipocket2html_filepos2href(t1, t2);
		t2 = realloc(t2, text_length * sizeof(char));
		strcpy(t2, t1);

		/* Images */
		text_length = mobipocket2html_recindex2src_length(t2, 
		   mobipocket);
		t1 = realloc(t1, text_length * sizeof(char));
		text_length = mobipocket2html_recindex2src(t1, t2, mobipocket);
		t2 = realloc(t2, text_length * sizeof(char));
		strcpy(t2, t1);

		strcpy(html, t2);
		free(t1);
		free(t2);
	}

	return text_length;
}

/**
 * Get length of html after conversion.
 * @param mobipocket MOBIPocket.
 * @return uint32_t new text length.
 */
uint32_t mobipocket2html_length(const mobipocket_t mobipocket)
{
	uint32_t text_length = mobipocket_text_length(mobipocket);
	if (text_length)
	{
		char html[text_length];
		text_length = mobipocket_text(html, mobipocket);
		text_length += mobipocket2html_filepos2id_length_offset(html);
		text_length += mobipocket2html_filepos2href_length_offset(html);
		text_length += mobipocket2html_recindex2src_length_offset(html, 
		   mobipocket);
	}

	return text_length;
}

