#include "simple_shell.h"

/**
 * **strTokenize - divides a string into words,
 * treating consecutive delimiters as one.
 * @iStr: the input string to be split
 * @dStr: the character used as the delimiter for word separation.
 * Return: pointer to a array of strings else NULL when fail
 */
char **strTokenize(char *iStr, char *dStr)
{
	int i, j, n, o, words = 0;
	char **str;

	if (iStr == NULL || iStr[0] == 0)
		return (NULL);
	if (!dStr)
		dStr = " ";
	for (i = 0; iStr[i] != '\0'; i++)
		if (!isDelimiter(iStr[i], dStr) && (isDelimiter(iStr[i + 1], dStr)
		|| !iStr[i + 1]))
			words++;

	if (words == 0)
		return (NULL);
	str = malloc((1 + words) * sizeof(char *));
	if (!str)
		return (NULL);
	for (i = 0, j = 0; j < words; j++)
	{
		while (isDelimiter(iStr[i], dStr))
			i++;
		n = 0;
		while (!isDelimiter(iStr[i + n], dStr) && iStr[i + n])
			n++;
		str[j] = malloc((n + 1) * sizeof(char));
		if (!str[j])
		{
			for (n = 0; n < j; n++)
				free(str[n]);
			free(str);
			return (NULL);
		}
		for (o = 0; o < n; o++)
			str[j][o] = iStr[i++];
		str[j][o] = 0;
	}
	str[j] = NULL;
	return (str);
}

/**
 * **strTokenizeIR - splits a string into  words based on a delimiter
 * @iStr: the input string to be split.
 * @dStr: the character used as the delimiter for word separation.
 * Return: a pointer to a array of strings, else NULL when fail
 */
char **strTokenizeIR(char *iStr, char dStr)
{
	int i, j, n, o, words = 0;
	char **str;

	if (iStr == NULL || iStr[0] == 0)
		return (NULL);
	for (i = 0; iStr[i] != '\0'; i++)
		if ((iStr[i] != dStr && iStr[i + 1] == dStr) ||
			(iStr[i] != dStr && !iStr[i + 1]) || iStr[i + 1] == dStr)
			words++;
	if (words == 0)
		return (NULL);
	str = malloc((1 + words) * sizeof(char *));
	if (!str)
		return (NULL);
	for (i = 0, j = 0; j < words; j++)
	{
		while (iStr[i] == dStr && iStr[i] != dStr)
			i++;
		n = 0;
		while (iStr[i + n] != dStr && iStr[i + n] && iStr[i + n] != dStr)
			n++;
		str[j] = malloc((n + 1) * sizeof(char));
		if (!str[j])
		{
			for (n = 0; n < j; n++)
				free(str[n]);
			free(str);
			return (NULL);
		}
		for (o = 0; o < n; o++)
			str[j][o] = iStr[i++];
		str[j][o] = 0;
	}
	str[j] = NULL;
	return (str);
}
