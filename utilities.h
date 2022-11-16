

#ifndef UTILITIES_LIB
#define UTILITIES_LIB
enum ColorCode {
    BLUE = 36,
    RED = 31
};
#define CLEAR() printf("\033[2J")
#define CLEARLINE() printf("\033[k")
#define MOVEUP(x) printf("\033[%dA", (x))
#define MOVEDOWN(x) printf("\033[%dB", (x))
#define MOVELEFT(y) printf("\033[%dD", (y))
#define MOVERIGHT(y) printf("\033[%dC",(y))
#define MOVETO(x,y) printf("\033[%d;%dH", (x), (y))
#define HIDE_CURSOR() printf("\033[?25l")
#define SHOW_CURSOR() printf("\033[?25h")
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