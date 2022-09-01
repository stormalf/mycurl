# mycurl

mycurl is a small cli tool to do REST API call using libcurl developed in C.
This tool used "jasmine" from https://github.com/zserge/jsmn to validate json format.
I used also pvs-studio https://pvs-studio.com/en/pvs-studio/ to help to find vulnerabilites and commons mistakes.
It generates a report.tasks with issues found.

By default if no url is passed, it uses https://httpbin.org/get and default method GET and no authentication.
It manages basic authentication and bearer authentication.

Libcurl can send more information if you use --verbose parameter (including headers).

It runs on linux. Tested on wsl Ubuntu.

## compile

Just need to execute :

    make

If you have pvs-studio installed and configured (free licence available for open source projects), you can execute :

    ./pvs.sh

## usage

./mycurl -h

    MYCURL is a small CLI tool that does REST API calls using libcurl.
    For now few features exist: disabling or not ssl verification, verbose mode, basic and bearer authentication
    Enjoy!
    MYCURL usage :
    --help or -h print the help
    --version or -v print the version of MYCURL
    --url or -u url to connect to
    --method or -m method to use default is GET. Allowed methods are GET, PUT, PATCH, POST, DELETE
    --verbose or -V to print verbose output
    --auth or -a to define the authentication to use : basic or bearer
    --no-ssl-check or -n to disable SSL verification by default SSL verification is activated
    --user or -U to pass the user or define MYCURL_USER environment variable
    --password or -P to pass the password or define MYCURL_PASSWORD environment variable
    --token or -T to pass the token or define MYCURL_PASSWORD environment variable
    --jsonfile or -j to specify json file to pass into the body part to the request

## limits

Tests done can be found in tests directory and results.txt.
To launch tests, you can do ./tests/test.sh it generates the results in results.txt.
I haven't test the POST with jsonfile in real API call neither any method that uses jsonfile in real API except GET.
I tested successfully the --no-ssl-check with self-signed certificate, no more issue after disabling.
Note that it's not recommended to deactivate ssl, that's why it's not the default behaviour.

Only 128 tokens can be managed in json see "jasmine" github for help about it.
Other limits are :

    - max url length sets to 200
    - max length for each argument value sets to 100
    - max data content retrieved from json file is limited to 32000

## examples

./mycurl -u https://httpbin.org/get --verbose

    *   Trying 52.87.105.151:443...
    * Connected to httpbin.org (52.87.105.151) port 443 (#0)
    * found 403 certificates in /etc/ssl/certs
    * GnuTLS ciphers: NORMAL:-ARCFOUR-128:-CTYPE-ALL:+CTYPE-X509:-VERS-SSL3.0
    * ALPN, offering h2
    * ALPN, offering http/1.1
    * SSL connection using TLS1.2 / ECDHE_RSA_AES_128_GCM_SHA256
    *   server certificate verification OK
    *   server certificate status verification SKIPPED
    *   common name: httpbin.org (matched)
    *   server certificate expiration date OK
    *   server certificate activation date OK
    *   certificate public key: RSA
    *   certificate version: #3
    *   subject: CN=httpbin.org
    *   start date: Sun, 21 Nov 2021 00:00:00 GMT
    *   expire date: Mon, 19 Dec 2022 23:59:59 GMT
    *   issuer: C=US,O=Amazon,OU=Server CA 1B,CN=Amazon
    * ALPN, server accepted to use h2
    * Using HTTP2, server supports multiplexing
    * Connection state changed (HTTP/2 confirmed)
    * Copying HTTP/2 data in stream buffer to connection buffer after upgrade: len=0
    * Using Stream ID: 1 (easy handle 0x55c11f90bfa0)
    > GET /get HTTP/2
    Host: httpbin.org
    accept: application/json
    content-type: application/json
    charset: utf-8

    * Connection state changed (MAX_CONCURRENT_STREAMS == 128)!
    < HTTP/2 200
    < date: Thu, 01 Sep 2022 05:14:25 GMT
    < content-type: application/json
    < content-length: 300
    < server: gunicorn/19.9.0
    < access-control-allow-origin: *
    < access-control-allow-credentials: true
    <
    {
    "args": {},
    "headers": {
        "Accept": "application/json",
        "Charset": "utf-8",
        "Content-Type": "application/json",
        "Host": "httpbin.org",
        "X-Amzn-Trace-Id": "Root=1-63103fb1-284908bd3a2f6eeb442f1634"
    },
    "origin": "77.111.246.40",
    "url": "https://httpbin.org/get"
    }
    * Connection #0 to host httpbin.org left intact

## release notes

1.0.0 - Initial version
