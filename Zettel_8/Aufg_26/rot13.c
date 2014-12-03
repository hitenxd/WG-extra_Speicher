#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "rot13.h"

inline void rot13_str(char *str) {
    int i;
    for (i = 0; i < strlen(str); i++) {
        if (isalpha(str[i])) {
            char alpha = islower(str[i]) ? 'a' : 'A';
            str[i] = (str[i] - alpha + 13) % 26 + alpha;
        }
    }
}

