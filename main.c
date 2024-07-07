//
//  main.c
//
//
//  Created by Evan Anderson on 7/6/24.
//

#include <stdio.h>
#include <stdlib.h>
#include "css/minifyCSS.c"

int main(int argc, char *argv[]) {
    FILE *file = fopen("/Users/randomhashtags/GitProjects/swift-league-scheduling/Public/css/defaults.css", "r");
    if (file) {
        fseek(file, 0L, SEEK_END);
        const long size = ftell(file);
        fseek(file, 0L, SEEK_SET);

        char string[size + 1];
        fread(string, 1, size, file);
        string[size] = '\0';
        fclose(file);

        char minified[size + 1];
        minify_css(string, size, minified);
        printf("%s\n", minified);
    }
}