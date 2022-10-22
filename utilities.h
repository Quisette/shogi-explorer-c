

#ifndef UTILITIES_LIB
#define UTILITIES_LIB
enum ColorCode {
    BLUE = 36,
    RED = 31
};
void printColor(int ColorCode, char *text);
char Regex(char *textToCheck, const char *regexStr);
char ctoi(char c);
char max(char a, char b);
void append_str(char str[], char c);

#endif  // UTILITIES_LIB