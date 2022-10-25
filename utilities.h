

#ifndef UTILITIES_LIB
#define UTILITIES_LIB
enum ColorCode {
    BLUE = 36,
    RED = 31
};
// Using ANSI escape code to print the text
void printColor(int ColorCode, char *text);
// Use regular expression to check if the text is of correct format.
char Regex(char *textToCheck, const char *regexStr);
// translates char to int(1-9).
char ctoi(char c);
// returns maximum of two chars.
char max(char a, char b);
// append a single char into the existing string.
void append_str(char str[], char c);

#endif  // UTILITIES_LIB