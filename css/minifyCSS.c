//
//  minifyCSS.c
//
//
//  Created by Evan Anderson on 7/6/24.
//

#include <stdbool.h>
#include <ctype.h>

void minify_css(const char *string, const long length, char *result) {
    long index = 0;
    bool looking_for_head = false, head = true, value = false, is_comment = false;
    for (long i = 0; i < length; i++) {
        const char character = string[i];
        switch (character) {
            case ' ':
            case '\t':
            case '\n':
            case '\v':
            case '\f':
            case '\r':
                if (!is_comment && (head && !looking_for_head && string[i-1] != ',' && string[i-1] != ':') && (i != length && (string[i+1] != '{' && string[i+1] != '(')) || value) {
                    result[index] = character;
                    index += 1;
                }
                break;
            case '/':
                if (string[i+1] == '*') {
                    is_comment = true;
                } else if (string[i-i] == '*') {
                    is_comment = false;
                } else {
                    result[index] = character;
                    index += 1;
                }
                break;
            default:
                if (!is_comment) {
                    switch (character) {
                        case '{':
                            head = false;
                            value = false;
                            break;
                        case '}':
                            looking_for_head = true;
                            break;
                        case ':':
                            if (!head) {
                                value = true;
                            }
                            break;
                        case ';':
                            head = false;
                            value = false;
                            break;
                        default:
                            looking_for_head = false;
                            head = true;
                            break;
                    }
                    result[index] = character;
                    index += 1;
                }
                break;
        }
    }
    result[index] = '\0';
}