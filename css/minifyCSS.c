//
//  minifyCSS.c
//
//
//  Created by Evan Anderson on 7/6/24.
//

#include <stdbool.h>

void minify_css(const char *string, const long length, char *result) {
    long index = 0, i = 0;
    while (string[i] == ' ' || string[i] == '\t' || string[i] == '\n' || string[i] == '\r') {
        i += 1;
    }
    while (i < length) {
        switch (string[i]) {
            case ' ':
            case '\t':
            case '\n':
            case '\r': {
                const char previous = string[i-1];
                const char next = string[i+1];
                if ((previous >= 'a' && previous <= 'z' || previous >= 'A' && previous <= 'Z') && (next == '#' || next == '.' || (next >= '0' && next <= '9') || (next >= 'a' && next <= 'z' || next >= 'A' && next <= 'Z'))) {
                    result[index] = string[i];
                    index += 1;
                }
                break;
            } case '/':
                if (string[i+1] == '*') {
                    i += 2;
                    for (long j = i; j < length; j++) {
                        if (string[j] == '*' && string[j+1] == '/') {
                            i = j+1;
                            break;
                        }
                    }
                } else {
                    result[index] = string[i];
                    index += 1;
                }
                break;
            default:
                result[index] = string[i];
                index += 1;
                break;
        }
        i += 1;
    }
    result[index] = '\0';
}