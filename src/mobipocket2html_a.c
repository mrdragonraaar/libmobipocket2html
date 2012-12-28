/**
 * mobipocket2html_a.c
 *
 * (c)2012 mrdragonraaar.com
 */
#include "mobipocket2html_a.h"

uint16_t mobipocket2html_filepos_arr(uint32_t *filepos_arr, const char *text);
uint16_t mobipocket2html_filepos_arr_add(uint32_t filepos, 
   uint32_t *filepos_arr, uint16_t len);
uint32_t compare_filepos(const void *a, const void *b);
uint16_t mobipocket2html_filepos_count(const char *text);
uint32_t mobipocket2html_filepos(const char **text);

/**
 * Convert file position attributes to href attributes in MOBIPocket text.
 * @param *html converted MOBIPocket text.
 * @param *text MOBIPocket text.
 * @return uint32_t new text length.
 */
uint32_t mobipocket2html_filepos2href(char *html, const char *text)
{
	*html = '\0';
	const char *in = text;
	uint32_t textpos = 0;

	uint32_t filepos;
	while ((filepos = mobipocket2html_filepos(&in)))
	{
		uint32_t len = (in - text) - textpos;

		strncat(html, text + textpos, len);

		sprintf(html + strlen(html), 
		   "%s%010d\"", A_HREF_PREFIX, filepos);

		in += (strlen(FILEPOS_SEARCH_STR) + FILEPOS_LEN);
		textpos = in - text;
	}
	strcat(html, text + textpos);

	return strlen(html);
}

/**
 * Get length of text after file position to href attribute conversion.
 * @param *text MOBIPocket text.
 * @return uint32_t new text length.
 */
uint32_t mobipocket2html_filepos2href_length(const char *text)
{
	return strlen(text) +
	   mobipocket2html_filepos2href_length_offset(text);
}

/**
 * Get length offset of text after file position to href attribute conversion.
 * @param *text MOBIPocket text.
 * @return int32_t text length offset.
 */
int32_t mobipocket2html_filepos2href_length_offset(const char *text)
{
	int32_t length_offset = 0;

	uint16_t filepos_count = mobipocket2html_filepos_count(text);
	if (filepos_count)
	{
		length_offset += strlen(A_HREF_PREFIX) + FILEPOS_LEN + 1;
		length_offset -= (strlen(FILEPOS_SEARCH_STR) + FILEPOS_LEN);
		length_offset *= filepos_count;
	}

	return length_offset;
}

/**
 * Insert id attributes at file positions in MOBIPocket text.
 * @param *html converted MOBIPocket text.
 * @param *text MOBIPocket text.
 * @return uint32_t new text length.
 */
uint32_t mobipocket2html_filepos2id(char *html, const char *text)
{
	*html = '\0';
	uint16_t filepos_count = mobipocket2html_filepos_count(text);
	if (filepos_count)
	{
		uint32_t filepos_arr[filepos_count];
		filepos_count = mobipocket2html_filepos_arr(filepos_arr, text);

		uint16_t i;
		for (i = 0; i < filepos_count; i++)
		{
			if (i == 0)
				strncat(html, text, filepos_arr[i]);
			else
				strncat(html, text + filepos_arr[i - 1], 
				   filepos_arr[i] - filepos_arr[i - 1]);

			sprintf(html + strlen(html),
			   "%s%010d%s", A_ID_PREFIX, filepos_arr[i], 
			   A_ID_SUFFIX);
		}
		strcat(html, text + filepos_arr[filepos_count - 1]);
	}
	else
		strncpy(html, text, strlen(text));

	return strlen(html);
}

/**
 * Get length of text after id attribute insertion.
 * @param *text MOBIPocket text.
 * @return uint32_t new text length.
 */
uint32_t mobipocket2html_filepos2id_length(const char *text)
{
	return strlen(text) + 
	   mobipocket2html_filepos2id_length_offset(text);
}

/**
 * Get length offset of text after id attribute insertion.
 * @param *text MOBIPocket text.
 * @return int32_t text length offset.
 */
int32_t mobipocket2html_filepos2id_length_offset(const char *text)
{
	int32_t length_offset = 0;

	uint16_t filepos_count = mobipocket2html_filepos_count(text);
	if (filepos_count)
	{
		uint32_t filepos_arr[filepos_count];
		filepos_count = mobipocket2html_filepos_arr(filepos_arr, text);

		length_offset += strlen(A_ID_PREFIX) + FILEPOS_LEN + 
		   strlen(A_ID_SUFFIX);
		length_offset *= filepos_count;
	}

	return length_offset;
}

/**
 * Get array of unique file positions.
 * @param *filepos_arr array of file positions.
 * @param *text MOBIPocket text.
 * @return uint16_t length of file positions array.
 */
uint16_t mobipocket2html_filepos_arr(uint32_t *filepos_arr, const char *text)
{
	uint16_t len = 0;

	uint32_t filepos;
	while ((filepos = mobipocket2html_filepos(&text)))
	{
		len = mobipocket2html_filepos_arr_add(
		   filepos, filepos_arr, len);

		text += (strlen(FILEPOS_SEARCH_STR) + FILEPOS_LEN);
	}

	if (len)
		qsort(filepos_arr, len, sizeof(uint32_t), 
		   (__compar_fn_t)compare_filepos);

	return len;
}

/**
 * Add file position to array of file positions if unique.
 * @param filepos file position to add.
 * @param *filepos_arr array of file positions.
 * @param len length of file positions array.
 * @return uint16_t new length of file positions array.
 */
uint16_t mobipocket2html_filepos_arr_add(uint32_t filepos, 
   uint32_t *filepos_arr, uint16_t len)
{
	uint16_t i;
	for (i = 0; i < len; i++)
		if (filepos_arr[i] == filepos)
			return len;

	filepos_arr[len] = filepos;
	len++;

	return len;
}

/**
 * Compare two file position attributes.
 * @param *a first filepos.
 * @param *b second filepos.
 * @return uint32_t.
 */
uint32_t compare_filepos(const void *a, const void *b)
{
	const uint32_t *ia = (const uint32_t *)a;
	const uint32_t *ib = (const uint32_t *)b;

	return (*ia > *ib) - (*ia < *ib);
}

/**
 * Get the number of file position attributes in MOBIPocket text.
 * @param *text MOBIPocket text.
 * @return uint16_t file position attribute count.
 */
uint16_t mobipocket2html_filepos_count(const char *text)
{
	uint16_t filepos_count = 0;

	uint32_t filepos;
	while ((filepos = mobipocket2html_filepos(&text)))
	{
		filepos_count++;
		text += (strlen(FILEPOS_SEARCH_STR) + FILEPOS_LEN);
	}

	return filepos_count;
}

/**
 * Find the next file position attribute in MOBIPocket text.
 * @param **text MOBIPocket text.
 * @return uint32_t file position attribute or 0 if not found.
 */
uint32_t mobipocket2html_filepos(const char **text)
{
	if ((*text = strstr(*text, FILEPOS_SEARCH_STR)) != NULL)
	{
                return (uint32_t)strtol(*text + strlen(FILEPOS_SEARCH_STR), 
		   (char**)NULL, 10);
	}

	return 0;
}

