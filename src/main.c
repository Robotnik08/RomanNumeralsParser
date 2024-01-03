#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID -1
#define MAX_INPUT 100

// macro functions
#define isEven(x) (x % 2 == 0)
#define isNum(x) (x >= '0' && x <= '9')

int isNumber (char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isNum(str[i])) {
            return 0;
        }
    }
    return 1;
}

// simple pair struct
typedef struct {
    char symbol;
    int val;
} roman_t;

// roman numerals
roman_t roman[] = {
    {'I', 1},
    {'V', 5},
    {'X', 10},
    {'L', 50},
    {'C', 100},
    {'D', 500},
    {'M', 1000},
};

// the max index of the roman array (the highest tier)
#define MAXTIER 6

// the index of the numeral in the roman array
int getTier (char symbol) {
    for (int r = 0; r < sizeof(roman) / sizeof(roman_t); r++) {
        if (roman[r].symbol == symbol) {
            return r;
        }
    }
    return -1;
}

// the value of the numeral in the roman array
int getRomanValueBySymbol(char symbol) {
    for (int r = 0; r < sizeof(roman) / sizeof(roman_t); r++) {
        if (roman[r].symbol == symbol) {
            return roman[r].val;
        }
    }
    return -1;
}

// get the value of a roman numeral
int getRomanValue(char* symbol) {
    int val = 0;
    for (int s = 0; s < strlen(symbol); s++) {

        // get values
        int current = getRomanValueBySymbol(symbol[s]);

        int currenttier = getTier(symbol[s]);
        int nexttier = 0;
        
        // check if the next symbol exists
        if (s + 1 < strlen(symbol)) {
            nexttier = getTier(symbol[s + 1]);
        }

        // check if the symbol is valid
        if (currenttier == INVALID || nexttier == INVALID || current == INVALID) {
            return INVALID;
        }

        // check if 4 in a row (except for the highest tier)
        if (currenttier != MAXTIER) {
            int c = 0;
            for (c = s; c < strlen(symbol); c++) {
                if (symbol[c] != symbol[s]) {
                    break;
                }
            }
            if (c - s > 3) return INVALID;
        }

        // check if subtractive notation (only tens, hundreds, thousands can subtract, you can only subtract with the next two tiers)
        if ((currenttier == nexttier - 2 || currenttier == nexttier - 1) && isEven(currenttier)) {
            val -= current;
        } else if (currenttier > nexttier) {
            val += current; // if the current tier is greater than the next tier, add it to the value
        } else if (currenttier == nexttier) {
            // if the current tier is equal to the next tier, check if the tier after that is greater than the next tier
            if (s + 2 < strlen(symbol)) {
                int nextnexttier = getTier(symbol[s + 2]);
                if (nextnexttier > nexttier) {
                    return INVALID; // if it is, then it's invalid
                }
            }
            // all good, add it to the value
            val += current;
        } else {
            return INVALID;
        }
    }
    return val;
}

char* intToRoman (int num) {
    char* roman = malloc(sizeof(char) * 1);
    roman[0] = '\0';

    if (num <= 0) {
        roman = realloc(roman, sizeof(char) * (strlen(roman) + 15));
        strcat(roman, "Invalid number");
        return roman;
    } 
    while (num > 0) {
        if (num >= 1000) {
            roman = realloc(roman, sizeof(char) * (strlen(roman) + 2));
            strcat(roman, "M");
            num -= 1000;
        } else if (num >= 900) {
            roman = realloc(roman, sizeof(char) * (strlen(roman) + 3));
            strcat(roman, "CM");
            num -= 900;
        } else if (num >= 500) {
            roman = realloc(roman, sizeof(char) * (strlen(roman) + 2));
            strcat(roman, "D");
            num -= 500;
        } else if (num >= 400) {
            roman = realloc(roman, sizeof(char) * (strlen(roman) + 3));
            strcat(roman, "CD");
            num -= 400;
        } else if (num >= 100) {
            roman = realloc(roman, sizeof(char) * (strlen(roman) + 2));
            strcat(roman, "C");
            num -= 100;
        } else if (num >= 90) {
            roman = realloc(roman, sizeof(char) * (strlen(roman) + 3));
            strcat(roman, "XC");
            num -= 90;
        } else if (num >= 50) {
            roman = realloc(roman, sizeof(char) * (strlen(roman) + 2));
            strcat(roman, "L");
            num -= 50;
        } else if (num >= 40) {
            roman = realloc(roman, sizeof(char) * (strlen(roman) + 3));
            strcat(roman, "XL");
            num -= 40;
        } else if (num >= 10) {
            roman = realloc(roman, sizeof(char) * (strlen(roman) + 2));
            strcat(roman, "X");
            num -= 10;
        } else if (num >= 9) {
            roman = realloc(roman, sizeof(char) * (strlen(roman) + 3));
            strcat(roman, "IX");
            num -= 9;
        } else if (num >= 5) {
            roman = realloc(roman, sizeof(char) * (strlen(roman) + 2));
            strcat(roman, "V");
            num -= 5;
        } else if (num >= 4) {
            roman = realloc(roman, sizeof(char) * (strlen(roman) + 3));
            strcat(roman, "IV");
            num -= 4;
        } else if (num >= 1) {
            roman = realloc(roman, sizeof(char) * (strlen(roman) + 2));
            strcat(roman, "I");
            num -= 1;
        }
    }
    return roman;
}

int main (int argc, char** argv) {
    int val = 0;
    char* roman = NULL;
    if (argc == 3) {
        if (strcmp(argv[2], "-s") == 0 || strcmp(argv[2], "--silent") == 0) {
            if (isNumber(argv[1])) {
                printf ("%s", intToRoman(atoi(argv[1]))); // print only the value
            } else {
                printf ("%d", getRomanValue(argv[1])); // print only the value
            }
            return 0;
        } else if (strcmp(argv[2], "-c") == 0 || strcmp(argv[2], "--code") == 0) {
            return getRomanValue(argv[1]); // return the value
        } else {
            printf ("Invalid arguments\n");
            return 0;
        }
    } else if (argc == 2) {
        printf ("Input: %s\n", argv[1]);

        if (isNumber(argv[1])) {
            roman = intToRoman(atoi(argv[1]));
        } else {
            val = getRomanValue(argv[1]);
        }
    } else if (argc == 1) {
        char input[MAX_INPUT];
        printf ("Input: ");
        scanf ("%s", input);
        input[MAX_INPUT - 1] = '\0'; // stop overflow

        if (isNumber(input)) {
            roman = intToRoman(atoi(input));
        } else {
            val = getRomanValue(input);
        }
    } else {
        printf ("Invalid arguments\n");
        return 0;
    }

    if (val == INVALID) {
        printf ("Invalid roman numeral\n");
    } else if (roman != NULL) {
        printf ("Output: %s\n", roman);
        free (roman);
    } else {
        printf ("Output: %d\n", val);
    }
    return 0;
}