//
//  main.c
//
//
//  Created by Evan Anderson on 7/6/24.
//

#include <stdio.h>

#include "css/minifyCSS.c"
#include "js/minifyJS.c"

void test_minify(const char *file_path, const bool css) {
    FILE *file = fopen(file_path, "r");
    if (file) {
        fseek(file, 0L, SEEK_END);
        const long size = ftell(file);
        fseek(file, 0L, SEEK_SET);

        char string[size + 1];
        fread(string, 1, size, file);
        string[size] = '\0';
        fclose(file);

        char minified[size + 1];
        if (css) {
            minify_css(string, size, minified);
        } else {
            minify_js(string, size, minified);
        }
        printf("%s\n", minified);
    } else {
        printf("No file for path: %s\n", file_path);
    }
}

int main(int argc, char *argv[]) {
    //test_minify("/Users/randomhashtags/GitProjects/swift-league-scheduling/Public/css/defaults.css", true);
    test_minify("/Users/randomhashtags/GitProjects/swift-league-scheduling/Resources/js/defaults.js", false);
    return 0;
}