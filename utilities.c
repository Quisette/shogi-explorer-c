#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include "utilities.h"
#include <ctype.h>
#include <string.h>

char Regex(char *textToCheck, const char *regexStr)
{
    regex_t compiledRegex;
    int reti;
    int actualReturnValue = -1;
    char messageBuffer[100];

    /* Compile regular expression */
    reti = regcomp(&compiledRegex, regexStr, REG_EXTENDED | REG_ICASE);
    if (reti)
    {
        fprintf(stderr, "Could not compile regex\n");
        return -2;
    }

    /* Execute compiled regular expression */
    reti = regexec(&compiledRegex, textToCheck, 0, NULL, 0);
    if (!reti)
    {
        // puts("Match");
        actualReturnValue = 0;
    }
    else if (reti == REG_NOMATCH)
    {
        // puts("No match");
        actualReturnValue = 1;
    }
    else
    {
        regerror(reti, &compiledRegex, messageBuffer, sizeof(messageBuffer));
        fprintf(stderr, "Regex match failed: %s\n", messageBuffer);
        actualReturnValue = -3;
    }

    /* Free memory allocated to the pattern buffer by regcomp() */
    regfree(&compiledRegex);
    return actualReturnValue;
}
void printColor(int colorCode, char *text)
{
    printf("%c[%dm%s%c[0m", 0x1B, colorCode, text, 0x1B);
}
char ctoi(char c)
{
    if (isdigit(c))
        return c - '0';
    else
        return '!';
}

char max(char a, char b)
{
    return a > b ? a : b;
}

void append_str(char str[], char c)
{
    auto char arr[2] = {c, '\0'};
    strcat(str, arr);
}
