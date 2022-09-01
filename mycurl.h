#define PRODUCT "MYCURL"
#define VERSION "1.0.0"

#define MAXURLLEN 201
#define MAXLEN 101
#define MAXDATA 32001
#define MAXTOKEN 128   //Do not change this value it's the limit defined by jsmn. 

#define _GET "GET"
#define _POST "POST"
#define _PUT "PUT"
#define _DELETE "DELETE"
#define _PATCH "PATCH"

#define _BASIC "basic"
#define _BEARER "bearer"

#define HELP PRODUCT " is a small CLI tool that does REST API calls using libcurl.\n \
For now few features exist: disabling or not ssl verification, verbose mode, basic and bearer authentication\n \
Enjoy!"

#define USAGE PRODUCT " usage :\n \
--help or -h print the help\n \
--version or -v print the version of " PRODUCT "\n \
--url or -u url to connect to\n \
--method or -m method to use default is GET. Allowed methods are GET, PUT, PATCH, POST, DELETE\n \
--verbose or -V to print verbose output\n \
--auth or -a to define the authentication to use : basic or bearer\n \
--no-ssl-check or -n to disable SSL verification by default SSL verification is activated\n \
--user or -U to pass the user or define MYCURL_USER environment variable\n \
--password or -P to pass the password or define MYCURL_PASSWORD environment variable\n \
--token or -T to pass the token or define MYCURL_PASSWORD environment variable\n \
--jsonfile or -j to specify json file to pass into the body part to the request"

typedef struct {
    char url[MAXURLLEN];
    int method;
    char user[MAXLEN];
    char password[MAXLEN];
    char token[MAXLEN]; 
    FILE *jsonfile;
}MYCURL;

enum METHOD { 
    GET, 
    POST,
    PUT,
    DELETE,
    PATCH
};

void printHelp(void);
void printUsage(void);
void printVersion(void);
int restApiCall(const MYCURL *);
int returnMethodInt(const char[7]);
char* toLower(char*);
char* toUpper(char*);
int test_file_type(const char *);
int validateJson(const char *);

