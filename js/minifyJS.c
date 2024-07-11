//
//  minifyJS.c
//
//
//  Created by Evan Anderson on 7/6/24.
//

#include <stdbool.h>

void minify_js(const char *string, const long length, char *result) {
    long index = 0;
    int end_string_token = 0, keep_const = 0;
    bool keep = false, is_comment = false, in_string = false;
    for (long i = 0; i < length; i++) {
        const char character = string[i];
        switch (character) {
            case ' ':
            case '\t':
            case '\n':
            case '\v':
            case '\f':
            case '\r':
                is_comment = is_comment && character == ' ';

                bool is_const = false;
                switch (string[i-1]) {
                    case 'r':
                        is_const = string[i-2] == 'a' && string[i-3] == 'v';
                        break;
                    case 't':
                        is_const = (string[i-2] == 'e' && string[i-3] == 'l') || (string[i-2] == 's' && string[i-3] == 'n' && string[i-4] == 'o' && string[i-5] == 'c');
                        break;
                    case 'n':
                        is_const = (string[i-2] == 'o' && string[i-3] == 'i' && string[i-4] == 't' && string[i-5] == 'c' && string[i-6] == 'n' && string[i-7] == 'u' && string[i-8] == 'f') || (string[i-2] == 'r' && string[i-3] == 'u' && string[i-4] == 't' && string[i-5] == 'e' && string[i-6] == 'r');
                        break;
                    case 'f':
                        is_const = string[i-2] == 'o' && (string[i-3] == ' ' || string[i-3] == 'e' && string[i-4] == 'p' && string[i-5] == 'y' && string[i-6] == 't');
                        break;
                    case 'w':
                        is_const = string[i-2] == 'e' && string[i-3] == 'n';
                        break;
                    case 'e':
                        is_const = false;
                        const char next = string[i+1];
                        is_const = (string[i-2] == 's' && string[i-3] == 'l' && string[i-4] == 'e') && next == 'i' && string[i+2] == 'f' || (string[i-2] == 's' && string[i-3] == 'a' && string[i-4] == 'c' && next >= '0' && next <= '9');
                        break;
                    default:
                        break;
                }
                if (!is_const) {
                    is_const = string[i+1] == 'o' && string[i+2] == 'f' && string[i+3] == ' ';
                }
                keep = in_string || is_const;
                break;
            case '/':
                is_comment = is_comment || string[i+1] == '/';
                keep = in_string || !is_comment;
                if (is_comment) {
                    i += 1;
                }
                break;
            default:
                keep = !is_comment;
                if (keep) {
                    switch (character) {
                        case '`':
                        case '"':
                        case '\'':
                            if (!in_string) {
                                in_string = true;
                                end_string_token = character;
                            } else if (in_string && character == end_string_token && string[i-1] != '\\') {
                                in_string = false;
                            }
                            break;
                        default:
                            break;
                    }
                }
                break;
        }
        if (keep) {
            result[index] = character;
            index += 1;
        }
    }
}