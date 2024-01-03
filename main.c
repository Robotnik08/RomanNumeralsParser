#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID -1
#define MAX_INPUT 100

// isEven macro
#define isEven(x) (x % 2 == 0)

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

int main (int argc, char** argv) {
    int val = 0;

    if (argc == 2) {
        printf ("Input: %s\n", argv[1]);
        val = getRomanValue(argv[1]);
    } else if (argc == 1) {
        char input[MAX_INPUT];
        printf ("Input: ");
        scanf ("%s", input);
        input[MAX_INPUT - 1] = '\0'; // stop overflow

        val = getRomanValue(input);
    } else {
        printf ("Invalid arguments\n");
        return 0;
    }

    if (val == INVALID) {
        printf ("Invalid roman numeral\n");
    } else {
        printf ("Output: %d\n", val);
    }
    return 0;
}