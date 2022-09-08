#include <ctype.h>
#include <curl/curl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "mycurl.h"
#include "jsmn.h" //from https://github.com/zserge/jsmn to validate json format

//global variable
bool isVerbose = false, isBasic = false, isBearer = false, isSslChecked = true, isJsonfileFilled = false;

int main(int argc, char *argv[]) {
    //if no url parameter found use the default one httpbin.org
    char url[MAXURLLEN]= "https://httpbin.org/get";
    //default method GET if no method parameter received
    int method = GET;
    int longParam = 0, shortParam = 0, ret = 0, fileOk = 0;
    bool isMethod = false, isUrl = false, isMethodFilled = false, isUrlFilled = false;
    bool isAuth = false, isAuthFilled = false, isCheckParm = false;
    bool isUser = false, isUserFilled = false, isPassword = false, isPasswordFilled = false, isToken = false, isTokenFilled = false;
    bool isJsonfile = false;
    
    //to receive the argument values
    char inputMethod[7] = {0};
    char inputUrl[MAXURLLEN] = {0};
    char inputUser[MAXLEN] = {0};
    char inputPassword[MAXLEN] = {0};
    char inputToken[MAXLEN] = {0};
    char inputJsonfile[MAXLEN] = {0};

    char *s = NULL;
    //to load the MYCURL_* environment variable
    char* mycurl_user = getenv("MYCURL_USER");
    char* mycurl_password = getenv("MYCURL_PASSWORD");
    char* mycurl_token = getenv("MYCURL_TOKEN");

    FILE *fp = NULL;

    //analyze each argument received to determine the action to do : for now only --help -h --version -v are allowed
   for (int i = 0; i < argc ; i++)
    {
        //ignore the first argument always the program itself
        if (i == 0) {
            continue;
        }

        if (strlen(argv[i]) > MAXURLLEN - 1) {
            perror("maximum length parameter overpassed");
            exit(EXIT_FAILURE);
        }
        //check if help asked for
        longParam = strcmp("--help", argv[i]);
        shortParam = strcmp("-h", argv[i]);
        if (longParam == 0 || shortParam == 0) {
            printHelp();
            printUsage();
            return EXIT_SUCCESS;
        }
        //check if version asked for
        longParam = strcmp("--version", argv[i]);
        shortParam = strcmp("-v", argv[i]);        
        if (longParam == 0 || shortParam == 0) {
            printVersion();
            return EXIT_SUCCESS;
        }
        //check if --method parameter passed 
        longParam = strcmp("--method", argv[i]);
        shortParam = strcmp("-m", argv[i]);

        if (longParam == 0 || shortParam == 0) {
            //check if already one method parameter found 
            if (isMethod) {
                printf("More than one method parameter specified! Only one parameter Method is allowed!\n");
                exit(EXIT_FAILURE);
            }           
            isMethod = true;
            continue;
        }

        //the argument that followed the method is stored as method
        if (isMethod && !isMethodFilled) {
            //check if the method is one of allowed method : GET, PUT, DELETE, PATCH, POST
            if (strcmp(argv[i], _GET) != 0 && strcmp(argv[i], _POST) != 0 && strcmp(argv[i], _DELETE) != 0
                && strcmp(argv[i], _PATCH) != 0 && strcmp(argv[i], _PUT) != 0) {
                    printf("Incorrect value for Method parameter: Expecting one \
of GET, PUT, DELETE, PATCH, POST but received '%s'\n", argv[i]);
                exit(EXIT_FAILURE);
                }
            strncpy(inputMethod, argv[i], sizeof(inputMethod) - 1);
            isMethodFilled = true;
            continue;
        }

        //check if URL parameter defined : 
        longParam = strcmp("--url", argv[i]);
        shortParam = strcmp("-u", argv[i]);        
        if (longParam == 0 || shortParam == 0) {
            if (isUrl) {
                printf("More than one url parameter specified! Only one parameter URL is allowed!\n");
                exit(EXIT_FAILURE);
            }    
            isUrl = true;    
            continue;
        }     

        //the argument that followed the url is stored as url
        if (isUrl && !isUrlFilled) {
            if (strlen(argv[i]) > MAXURLLEN - 1) {
                perror("maximum length parameter overpassed");
                exit(EXIT_FAILURE);
            }    
            //store the input URL
            strncpy(inputUrl, argv[i], sizeof(inputUrl) - 1);
            //convert to lowercase
            s = toLower(inputUrl);
            if ((strncmp(s,"http://", 7)) != 0 && (strncmp(s,"https://", 8)) != 0) {
                printf("Incorrect URL should start by http:// or https://\n");
                exit(EXIT_FAILURE);
            }
           
            isUrlFilled = true;             
            continue;
            }
        
        //check for verbose parameter
        longParam = strcmp("--verbose", argv[i]);
        shortParam = strcmp("-V", argv[i]);        
        if (longParam == 0 || shortParam == 0) {
            if (isVerbose) {
                printf("More than one verbose parameter specified! Only one parameter verbose is allowed!\n");
                exit(EXIT_FAILURE);
            }    
            isVerbose = true;
            continue;
        }

        //check for auth parameter 
        longParam = strcmp("--auth", argv[i]);
        shortParam = strcmp("-a", argv[i]);

        if (longParam == 0 || shortParam == 0) {
            //check if already one auth parameter found 
            if (isAuth) {
                printf("More than one auth parameter specified! Only one parameter auth is allowed!\n");
                exit(EXIT_FAILURE);
            }           
            isAuth = true;
            continue;
        }

        //the argument that followed the method is stored as method
        if (isAuth && !isAuthFilled) {
            //check if the auth is one of allowed authentication : basic, bearer
            if (strcmp(argv[i], _BASIC) != 0 && strcmp(argv[i], _BEARER) != 0) {
                    printf("Incorrect value for auth parameter: Expecting one \
of 'basic', 'bearer' but received '%s'\n", argv[i]);
                exit(EXIT_FAILURE);
                }
                if (strcmp(argv[i], _BASIC) == 0) {
                    isBasic = true;
                } else {
                    isBearer = true;
                }
            isAuthFilled = true;
            continue;
        }     

        //check for --no-ssl-check 
        longParam = strcmp("--no-ssl-check", argv[i]);
        shortParam = strcmp("-n", argv[i]);

        if (longParam == 0 || shortParam == 0) {
            //check if already one auth parameter found 
            if (isCheckParm) {
                printf("More than one --no-ssl-check parameter specified! Only one --no-ssl-check parameter is allowed!\n");
                exit(EXIT_FAILURE);
            }           
            isCheckParm = true;
            isSslChecked = false;
            continue;
        }

        //check for user parameter 
        longParam = strcmp("--user", argv[i]);
        shortParam = strcmp("-U", argv[i]);

        if (longParam == 0 || shortParam == 0) {
            //check if already one user parameter found 
            if (isUser) {
                printf("More than one user parameter specified! Only one parameter user is allowed!\n");
                exit(EXIT_FAILURE);
            }           
            isUser = true;
            continue;
        }

        //the argument that followed the user is stored as user
        if (isUser && !isUserFilled) {
            //check if the user length does not exceed the max allowed
            if (strlen(argv[i]) > MAXLEN - 1) {
                perror("maximum length parameter overpassed for user");
                exit(EXIT_FAILURE);
                }
            strncpy(inputUser, argv[i], sizeof(inputUser) - 1);    
            isUserFilled = true;
            continue;
        }     

        //check for password parameter 
        longParam = strcmp("--password", argv[i]);
        shortParam = strcmp("-P", argv[i]);

        if (longParam == 0 || shortParam == 0) {
            //check if already one password parameter found 
            if (isPassword) {
                printf("More than one password parameter specified! Only one parameter password is allowed!\n");
                exit(EXIT_FAILURE);
            }           
            isPassword = true;
            continue;
        }

        //the argument that followed the password is stored as password
        if (isPassword && !isPasswordFilled) {
            //check if the password length does not exceed the max allowed
            if (strlen(argv[i]) > MAXLEN - 1) {
                perror("maximum length parameter overpassed for password");
                exit(EXIT_FAILURE);
                }
            strncpy(inputPassword, argv[i], sizeof(inputPassword) - 1);    
            isPasswordFilled = true;
            continue;
        }     

        //check for token parameter 
        longParam = strcmp("--token", argv[i]);
        shortParam = strcmp("-T", argv[i]);

        if (longParam == 0 || shortParam == 0) {
            //check if already one token parameter found 
            if (isToken) {
                printf("More than one token parameter specified! Only one parameter token is allowed!\n");
                exit(EXIT_FAILURE);
            }           
            isToken = true;
            continue;
        }

        //the argument that followed the token is stored as token
        if (isToken && !isTokenFilled) {
            //check if the token length does not exceed the max allowed
            if (strlen(argv[i]) > MAXLEN - 1) {
                perror("maximum length parameter overpassed for token");
                exit(EXIT_FAILURE);
                }
            strncpy(inputToken, argv[i], sizeof(inputToken) - 1 );    
            isTokenFilled = true;
            continue;
        }     

        //check for jsonfile parameter 
        longParam = strcmp("--jsonfile", argv[i]);
        shortParam = strcmp("-j", argv[i]);

        if (longParam == 0 || shortParam == 0) {
            //check if already one jsonfile parameter found 
            if (isJsonfile) {
                printf("More than one jsonfile parameter specified! Only one parameter jsonfile is allowed!\n");
                exit(EXIT_FAILURE);
            }           
            isJsonfile = true;
            continue;
        }

        //the argument that followed the jsonfile is stored as jsonfile
        if (isJsonfile && !isJsonfileFilled) {
            //check if the user length does not exceed the max allowed
            if (strlen(argv[i]) > MAXLEN - 1) {
                perror("maximum length parameter overpassed for jsonfile");
                exit(EXIT_FAILURE);
                }
            strncpy(inputJsonfile, argv[i], sizeof(inputJsonfile) - 1);    
            isJsonfileFilled = true;
            continue;
        }     


        //unknown parameter or value
        printf("Unknown parameter or value %s!\n", argv[i]);
        exit(EXIT_FAILURE);            

    }
    //other error handling checking if all values are correctly passed. Example if -m is specified isMethodFilled should be true too!
    if (isUrl && !isUrlFilled) {
        printf("url parameter specified without value!\n");
        exit(EXIT_FAILURE);        
    }

    if (isMethod && !isMethodFilled) {
        printf("method parameter specified without value!\n");
        exit(EXIT_FAILURE);        
    }

    if (isAuth && !isBasic && !isBearer) {
        printf("auth parameter specified without value!\n");
        exit(EXIT_FAILURE);        
    }    

    if (isUser && !isUserFilled) {
        printf("user parameter specified without value!\n");
        exit(EXIT_FAILURE);        
    }

    if (isPassword && !isPasswordFilled) {
        printf("password parameter specified without value!\n");
        exit(EXIT_FAILURE);        
    }

    if (isToken && !isTokenFilled) {
        printf("token parameter specified without value!\n");
        exit(EXIT_FAILURE);        
    }

    if (isJsonfile && !isJsonfileFilled) {
        printf("jsonfile parameter specified without value!\n");
        exit(EXIT_FAILURE);        
    }
    //if basic authentication is defined and no inputUser/MYCURL_USER are provided send an error
    if ((isBasic && !isUser && mycurl_user == NULL)){
        printf("user info required for basic authentication! pass --user or define MYCURL_USER environment variable!\n");
        exit(EXIT_FAILURE);     
    }

    //if basic authentication is defined and no inputPassword/MYCURL_PASSWORD are provided send an error
    if ((isBasic && !isPassword && mycurl_password == NULL)){
        printf("password info required for basic authentication! pass --password or define MYCURL_PASSWORD environment variable!\n");
        exit(EXIT_FAILURE);     
    }
    
    //if bearer authentication is defined and no inputUser/MYCURL_USER are provided send an error
    if ((isBearer && !isUser && mycurl_user == NULL)){
        printf("user info required for bearer authentication! pass --user or define MYCURL_USER environment variable!\n");
        exit(EXIT_FAILURE);     
    }

    //if bearer authentication is defined and no inputToken/MYCURL_TOKEN are provided send an error
    if ((isBearer && !isToken && mycurl_token == NULL)){
        printf("token info required for bearer authentication! pass --token or define MYCURL_TOKEN environment variable!\n");
        exit(EXIT_FAILURE);     
    }
    
    //if user or password or token without auth parameter send an error
    if (!isBearer && !isBasic && (isUser || isPassword || isToken)) {
        printf("Incoherent parameters : user or password or token passed without specifying auth parameter!\n");
        exit(EXIT_FAILURE);   
    }

    //passing the url value instead of the default one
    if (isUrlFilled) {
            strcpy(url, inputUrl);
        }

    //passing the method value instead of the default one
    if (isMethodFilled) {
        method = returnMethodInt(inputMethod);
        }


    //filling mycurl structure
    MYCURL *mycurl = malloc (sizeof (MYCURL));
    if (mycurl == NULL) {
        printf("Error trying to allocate memory for MYCURL structure\n");
        exit(EXIT_FAILURE);
    }
    strcpy(mycurl->url, url);
    mycurl->method = method;
    mycurl->jsonfile = NULL;

    //priority to the user info passed
    if(isBasic || isBearer) {
        if (isUser) {
            strcpy(mycurl->user, inputUser);
        } else if(mycurl_user != NULL) {
            strcpy(mycurl->user, mycurl_user);
        } 
        
        if (isPassword) {
            strcpy(mycurl->password, inputPassword);
        }else if(mycurl_password != NULL) {
            strcpy(mycurl->password, mycurl_password);
        } 

        if(isToken) {
            strcpy(mycurl->token, inputToken);
        } else if(mycurl_token != NULL) {
            strcpy(mycurl->token, mycurl_token);
        } 
    } 

    //check if file is a regular one :
    if (isJsonfileFilled) {
        fileOk = test_file_type(inputJsonfile);
        if (fileOk < 0) {
            printf("Select another file! This one is not correct!\n");
            exit(EXIT_FAILURE);   
        }

        fp = fopen(inputJsonfile, "r");
        if (fp == NULL)
        {
            perror("Impossible to open the file");
            exit(EXIT_FAILURE);
        }
        mycurl->jsonfile = fp;
    }

    //executing the REST API call
    ret = restApiCall(mycurl);
    //free the memory
    free(mycurl);

    if (ret != 0 ) {
        printf("Error during restApiCall function %d\n", ret);
        exit(EXIT_FAILURE);
    }

    //close the file
    if (isJsonfileFilled && fp != NULL) {
        fclose(fp);
    }
    return EXIT_SUCCESS;
}

//print the help command line
void printHelp() {
    printf("%s\n", HELP);
}

//print the usage of the command
void printUsage() {
    printf("%s\n", USAGE);
}

//print the version of the command
void printVersion() {
    printf("%s version : %s\n", PRODUCT, VERSION);
}

//execute the REST API call
int restApiCall(const MYCURL * mycurl) {

    CURL *curl;
    CURLcode res;

    char postData[MAXDATA] = {0};
    char *pPostData = &postData[0];
    int jsonOk = 0;

    //define headers to use
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charset: utf-8");

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
        //verbose mode
        if (isVerbose) {
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        }
        //basic authentication
        if (isBasic) {
            curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
            curl_easy_setopt(curl, CURLOPT_USERNAME, mycurl->user);
            curl_easy_setopt(curl, CURLOPT_PASSWORD, mycurl->password);
        }
        //bearer authentication
        if (isBearer) {
            char authBearerMessage[MAXLEN + 22] = "Authorization: Bearer ";
            strcat(authBearerMessage, mycurl->token);
            curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_BEARER);
            curl_easy_setopt(curl, CURLOPT_USERNAME, mycurl->user);
            headers = curl_slist_append(headers, authBearerMessage);
        }
        //deactivate ssl certificate checking (it's not the default needs the --no-ssl-check parameter)
        if (!isSslChecked) {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        }

        //if jsonfile passed, read the content of the file and validate json format before passing to the request
        if (isJsonfileFilled) {
            if (mycurl->jsonfile != NULL) {
                int i = 1;
                while (!feof(mycurl->jsonfile)) {
                    char c = fgetc(mycurl->jsonfile);
                     if (feof(mycurl->jsonfile) || i > MAXDATA - 1) {
                        if (i > MAXDATA - 1) {
                            printf("content of jsonfile > 32000 characters, content truncated!\n");
                        }
                        break ;
                     }
                    *pPostData = c;    
                    pPostData++;
                    i++;
                }
                pPostData = &postData[0];
                jsonOk = validateJson(pPostData);
                if (jsonOk < 0) {
                    printf("Invalid json content!\n");
                    memset(postData, 0, sizeof(postData));
                }
            }
        }
        //set the correct method
        switch (mycurl->method) {
            case PATCH:
                curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, _PATCH);   
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);     
                break;
            case PUT:
                curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, _PUT);  
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);   
                break;
            case DELETE:
                curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, _DELETE);
                break;
            case POST:
                curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, _POST);  
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);          
                break;
            case GET:
                curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, _GET);  
                break;
            default:
                perror("Unknown method");
                return EXIT_FAILURE;
        }
        //execute the request
        curl_easy_setopt(curl, CURLOPT_URL, mycurl->url);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return EXIT_FAILURE;
            }
        //to print a new line after the answer (sometimes missing new line depending the api called)
        printf("\n");
        //clean curl resources
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        }
            return EXIT_SUCCESS;
    }

int returnMethodInt(const char method[7]) {
    if (strcmp(method, _GET) == 0) {
        return GET;
    }
    else if (strcmp(method, _POST) == 0) {
        return POST;
    } 
    else if (strcmp(method, _PATCH) == 0) {
        return PATCH;
    } 
    else if (strcmp(method, _PUT) == 0) {
        return PUT;
    } 
    else if (strcmp(method, _DELETE) == 0) {
        return DELETE;
    } 

    return GET;
}

char* toLower(char* s) {
  for(char *p=s; *p; p++) *p=tolower(*p);
  return s;
}

char* toUpper(char* s) {
  for(char *p=s; *p; p++) *p=toupper(*p);
  return s;
}

/* Return: 0 if file is a regular file, -1 if not */
int test_file_type(const char *file)
    {
        struct stat st;

        if (0 != lstat(file, &st)) {
            fprintf(stderr, "lstat failed, probably no such a file\n");
            perror("lstat");
            return -1;
        }

        if (S_IFREG != (st.st_mode & S_IFMT)) {
            fprintf(stderr, "Error on file [%s] opening: not a regular file, but ", file);
            switch (st.st_mode & S_IFMT) {
            case S_IFSOCK:
                fprintf(stderr, "socket\n");
                break;
            case S_IFLNK:
                fprintf(stderr, "symbolic link\n");
                break;
            case S_IFBLK:
                fprintf(stderr, "block device\n");
                break;
            case S_IFDIR:
                fprintf(stderr, "directory\n");
                break;
            case S_IFCHR:
                fprintf(stderr, "character device\n");
                break;
            case S_IFIFO:
                fprintf(stderr, "FIFO\n");
                break;
            }
            return -1;
        }
        return EXIT_SUCCESS;
    }

int validateJson(const char* jsonData) {

  int r;
  jsmn_parser p;
  jsmntok_t t[MAXTOKEN]; /* We expect no more than 128 tokens */

  jsmn_init(&p);
  //printf("%s\n", jsonData);
  r = jsmn_parse(&p, jsonData, strlen(jsonData), t,
                 sizeof(t) / sizeof(t[0]));
  if (r < 0) {
    printf("Failed to parse JSON: %d\n", r);
    return -1;
  }

  /* Assume the top-level element is an object */
  if (r < 1 || t[0].type != JSMN_OBJECT) {
    printf("Object expected\n");
    return -1;
  }
  return EXIT_SUCCESS;
}