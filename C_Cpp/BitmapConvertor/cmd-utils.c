#include "include/cmd-utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *filePathParam = "-f";
static const char *colorParam = "-c";

CmdParams parseCmdParams(int argc, const char **argv) {
    CmdParams params;
    params.filePath = NULL;
    bool isColorFilterSet = false;

    for (int index = 0; index < argc; index++) {
        if (strcmp(argv[index], filePathParam) == 0) {
            params.filePath = argv[index + 1];
        } else if (strcmp(argv[index], colorParam) == 0) {
            if (strcmp(argv[index + 1], "red") == 0) {
                params.colorFilter = Red;
                isColorFilterSet = true;
            } else if (strcmp(argv[index + 1], "green") == 0) {
                params.colorFilter = Green;
                isColorFilterSet = true;
            } else if (strcmp(argv[index + 1], "blue") == 0) {
                params.colorFilter = Blue;
                isColorFilterSet = true;
            } else {
                puts("'-c' (color filter) must be one of the following values - 'red', 'green', 'blue'");
                exit(1);
            }
        }
    }

    if (params.filePath == NULL || !isColorFilterSet) {
        puts("Please provide '-f' (file path) and '-c' (color filter, can be 'red', 'green', 'blue') parameters");
        exit(1);
    }

    return params;
}
