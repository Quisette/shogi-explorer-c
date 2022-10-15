#include<stdio.h>
#include<regex.h>
#include<stdlib.h>
#include"utilities.h"


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
void printColor(int colorCode, char* text){
        printf("%c[%dm%s%c[0m", 0x1B, colorCode,text,0x1B);
    }