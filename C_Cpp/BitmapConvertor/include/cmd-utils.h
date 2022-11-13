
typedef enum ColorFilter {
    Red,
    Green,
    Blue
} ColorFilter;

typedef struct CmdParams {
    const char *filePath;
    ColorFilter colorFilter;
} CmdParams;

CmdParams parseCmdParams(int argc, const char **argv);