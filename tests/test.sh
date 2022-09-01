result=$1
if [[ -z $result ]] 
then
   result="./tests/result.txt"
fi
echo Test001---------------------------------- > $result
echo test without arguments >> $result
echo ./mycurl >> $result
./mycurl >> $result
echo =================================== >> $result
echo Test002---------------------------------- >> $result
echo test with help parameter long --help >> $result
echo ./mycurl --help >> $result
./mycurl --help >> $result
echo =================================== >> $result
echo Test003---------------------------------- >> $result
echo test with help parameter short -h >> $result
echo ./mycurl -h >> $result
./mycurl -h >> $result
echo =================================== >> $result
echo Test004---------------------------------- >> $result
echo test with version parameter long --version >> $result
echo ./mycurl --version >> $result
./mycurl --version >> $result
echo =================================== >> $result
echo Test005---------------------------------- >> $result
echo test with version parameter short -v >> $result
echo ./mycurl -v >> $result
./mycurl -v >> $result
echo =================================== >> $result
echo Test006---------------------------------- >> $result
echo test with method parameter long --method but no value >> $result
echo ./mycurl --method >> $result
./mycurl --method >> $result
echo =================================== >> $result
echo Test007---------------------------------- >> $result
echo test with method parameter short -m but no value >> $result
echo ./mycurl -m >> $result
./mycurl -m >> $result
echo =================================== >> $result
echo Test008---------------------------------- >> $result
echo test with multiple method parameter long -m but no value >> $result
echo ./mycurl --method --method >> $result
./mycurl --method --method >> $result
echo =================================== >> $result
echo Test009---------------------------------- >> $result
echo test with multiple method parameter long and short >> $result
echo ./mycurl --method GET -m PUT >> $result
./mycurl --method GET -m PUT >> $result
echo =================================== >> $result
echo Test010---------------------------------- >> $result
echo test with url parameter long without value >> $result
echo ./mycurl --url >> $result
./mycurl --url >> $result
echo =================================== >> $result
echo Test011---------------------------------- >> $result
echo test with url parameter short without value >> $result
echo ./mycurl -u >> $result
./mycurl -u >> $result
echo =================================== >> $result
echo Test012---------------------------------- >> $result
echo test with multiple url parameter long and short without value >> $result
echo ./mycurl --url -u >> $result
./mycurl --url -u >> $result
echo =================================== >> $result
echo Test013---------------------------------- >> $result
echo test with correct method GET >> $result
echo ./mycurl --method GET >> $result
./mycurl --method GET >> $result
echo =================================== >> $result
echo Test014---------------------------------- >> $result
echo test with lowercase or unknown method get >> $result
echo ./mycurl --method get >> $result
./mycurl --method get >> $result
echo =================================== >> $result
echo Test015---------------------------------- >> $result
echo test with correct method POST >> $result
echo ./mycurl -m POST >> $result
./mycurl -m POST >> $result
echo =================================== >> $result
echo Test016---------------------------------- >> $result
echo test with incorrect short method value >> $result
echo ./mycurl -m POST >> $result
./mycurl -m xxx >> $result
echo =================================== >> $result
echo Test017---------------------------------- >> $result
echo test with correct url >> $result
echo ./mycurl --url https://httpbin.org/get >> $result
./mycurl --url https://httpbin.org/get >> $result
echo =================================== >> $result
echo Test018---------------------------------- >> $result
echo test with correct url but wrong method >> $result
echo ./mycurl --url https://httpbin.org/get -m POST >> $result
./mycurl --url https://httpbin.org/get -m POST >> $result
echo =================================== >> $result
echo Test019---------------------------------- >> $result
echo test with correct url and correct method POST >> $result
echo ./mycurl --url https://httpbin.org/post -m POST >> $result
./mycurl --url https://httpbin.org/post -m POST >> $result
echo =================================== >> $result
echo Test020---------------------------------- >> $result
echo test with correct url and correct method PATCH >> $result
echo ./mycurl --url https://httpbin.org/patch -m PATCH >> $result
./mycurl --url https://httpbin.org/patch -m PATCH >> $result
echo =================================== >> $result
echo Test021---------------------------------- >> $result
echo test with correct url and correct method PUT >> $result
echo ./mycurl --url https://httpbin.org/put -m PUT >> $result
./mycurl --url https://httpbin.org/put -m PUT >> $result
echo =================================== >> $result
echo Test022---------------------------------- >> $result
echo test with correct url and correct method DELETE >> $result
echo ./mycurl --url https://httpbin.org/put -m DELETE >> $result
./mycurl --url https://httpbin.org/delete -m DELETE >> $result
echo =================================== >> $result
echo Test023---------------------------------- >> $result
echo test with correct short url and long method DELETE >> $result
echo ./mycurl -u https://httpbin.org/put --method DELETE >> $result
./mycurl -u https://httpbin.org/delete --method DELETE >> $result
echo =================================== >> $result              
echo Test024---------------------------------- >> $result
echo test with incorrect value and no parameters >> $result
echo ./mycurl zzzzz >> $result
./mycurl zzzzz >> $result
echo =================================== >> $result      
echo Test025---------------------------------- >> $result
echo test with verbose long parameter >> $result
echo ./mycurl --verbose >> $result
./mycurl --verbose >> $result
echo =================================== >> $result      
echo Test026---------------------------------- >> $result
echo test with -V short parameter >> $result
echo ./mycurl -V >> $result
./mycurl -V >> $result
echo =================================== >> $result      
echo Test027---------------------------------- >> $result
echo test with auth short parameter with no value >> $result
echo ./mycurl -a >> $result
./mycurl -a >> $result
echo =================================== >> $result      
echo Test028---------------------------------- >> $result
echo test with auth long parameter with no value >> $result
echo ./mycurl --auth >> $result
./mycurl --auth >> $result
echo =================================== >> $result      
echo Test029---------------------------------- >> $result
echo test with auth short parameter with incorrect value >> $result
echo ./mycurl -a ZZZ >> $result
./mycurl -a ZZZ >> $result
echo =================================== >> $result      
echo Test029---------------------------------- >> $result
echo test with auth long parameter with incorrect value >> $result
echo ./mycurl --auth ZZZ >> $result
./mycurl --auth ZZZ >> $result
echo =================================== >> $result      
echo Test030---------------------------------- >> $result
echo test with auth short parameter with correct value basic but other missing parameters >> $result
echo ./mycurl -a basic >> $result
./mycurl -a basic >> $result
echo =================================== >> $result      
echo Test031---------------------------------- >> $result
echo test with auth short parameter with correct value bearer but other missing parameters >> $result
echo ./mycurl -a bearer >> $result
./mycurl -a bearer >> $result
echo =================================== >> $result      
echo Test032---------------------------------- >> $result
echo test with no ssl check  >> $result
echo ./mycurl --no-ssl-check >> $result
./mycurl --no-ssl-check >> $result
echo =================================== >> $result      
echo Test033---------------------------------- >> $result
echo test with multiple auth parameters >> $result
echo ./mycurl --auth basic -a bearer >> $result
./mycurl --auth basic -a bearer >> $result
echo =================================== >> $result  
echo Test034---------------------------------- >> $result
echo test with user long parameter without value  >> $result
echo ./mycurl --user >> $result
./mycurl --user >> $result
echo =================================== >> $result  
echo Test035---------------------------------- >> $result
echo test with user short parameter without value  >> $result
echo ./mycurl -u >> $result
./mycurl -u >> $result
echo =================================== >> $result  
echo Test036---------------------------------- >> $result
echo test with user short parameter with value  >> $result
echo ./mycurl -u toto >> $result
./mycurl -u toto >> $result
echo =================================== >> $result  
echo Test037---------------------------------- >> $result
echo test with password long parameter without value  >> $result
echo ./mycurl --password >> $result
./mycurl --password >> $result
echo =================================== >> $result  
echo Test038---------------------------------- >> $result
echo test with password short parameter without value  >> $result
echo ./mycurl -P >> $result
./mycurl -P >> $result
echo =================================== >> $result  
echo Test039---------------------------------- >> $result
echo test with password short parameter with value  >> $result
echo ./mycurl -P toto >> $result
./mycurl -P toto >> $result
echo =================================== >> $result  
echo Test040---------------------------------- >> $result
echo test with user password short parameter with basic auth  >> $result
echo ./mycurl -u https://httpbin.org/basic-auth/toto/toto -U toto -P toto  -a basic >> $result
./mycurl -u https://httpbin.org/basic-auth/toto/toto -U toto -P toto -a basic >> $result
echo Test040B---------------------------------- >> $result
echo test with user without password short parameter with basic auth  >> $result
echo ./mycurl -u https://httpbin.org/basic-auth/toto/toto -U toto -a basic >> $result
./mycurl -u https://httpbin.org/basic-auth/toto/toto -U toto -a basic >> $result
echo =================================== >> $result  
echo =================================== >> $result  
echo Test041---------------------------------- >> $result
echo test with user password short parameter with basic auth but incorrect value passed >> $result
echo ./mycurl -u https://httpbin.org/basic-auth/toto/toto -U toto -P titi  -a basic >> $result
./mycurl -u https://httpbin.org/basic-auth/toto/toto -U toto -P titi -a basic >> $result
echo =================================== >> $result  
echo Test041B---------------------------------- >> $result
echo test with basic auth but without user setting MYCURL_USER env variable >> $result
echo export MYCURL_USER=toto
echo ./mycurl -u https://httpbin.org/basic-auth/toto/toto -P titi -a basic >> $result
export MYCURL_USER=toto
./mycurl -u https://httpbin.org/basic-auth/toto/toto -P titi -a basic >> $result
echo =================================== >> $result  
echo Test042---------------------------------- >> $result
echo test with basic auth but without password setting MYCURL_PASSWORD env variable >> $result
echo export MYCURL_PASSWORD=toto
echo ./mycurl -u https://httpbin.org/basic-auth/toto/toto -U toto -a basic >> $result
export MYCURL_PASSWORD=toto
./mycurl -u https://httpbin.org/basic-auth/toto/toto -U toto -a basic >> $result
echo =================================== >> $result  
echo Test043---------------------------------- >> $result
echo test with basic auth but without user and password setting MYCURL_USER and MYCURL_PASSWORD env variable >> $result
echo export MYCURL_USER=toto
echo export MYCURL_PASSWORD=toto
echo ./mycurl -u https://httpbin.org/basic-auth/toto/toto -a basic >> $result
export MYCURL_USER=toto
export MYCURL_PASSWORD=toto
./mycurl -u https://httpbin.org/basic-auth/toto/toto -a basic >> $result
echo =================================== >> $result  
echo Test044---------------------------------- >> $result
echo test with token long parameter without value >> $result
echo ./mycurl --token >> $result
./mycurl --token >> $result
echo =================================== >> $result  
echo Test045---------------------------------- >> $result
echo test with token short parameter without value >> $result
echo ./mycurl -T >> $result
./mycurl -T >> $result
echo =================================== >> $result  
echo Test046---------------------------------- >> $result
echo test with token short parameter with value but without auth >> $result
echo ./mycurl -T mytoken123 >> $result
./mycurl -T mytoken123 >> $result
echo =================================== >> $result  
echo Test047---------------------------------- >> $result
echo test with token short parameter with value with auth basic >> $result
echo ./mycurl -T mytoken123 -a basic >> $result
./mycurl -T mytoken123 -a basic >> $result
echo =================================== >> $result  
echo Test048---------------------------------- >> $result
echo test with token short parameter with value with auth bearer >> $result
echo ./mycurl -T mytoken123 -a bearer >> $result
./mycurl -T mytoken123 -a bearer >> $result
echo =================================== >> $result  
echo Test048B---------------------------------- >> $result
echo test without token short parameter with value with auth bearer >> $result
echo ./mycurl -a bearer >> $result
./mycurl -a bearer >> $result
echo =================================== >> $result  
echo Test049---------------------------------- >> $result
echo test with token short parameter with value with auth bearer and correct url but without user info >> $result
echo ./mycurl -u https://httpbin.org/bearer -T mytoken123 -a bearer >> $result
./mycurl -u https://httpbin.org/bearer -T mytoken123 -a bearer >> $result
echo =================================== >> $result  
echo Test050---------------------------------- >> $result
echo test with token short parameter with value with auth bearer and correct url but with user info >> $result
echo ./mycurl -u https://httpbin.org/bearer -T mytoken123 -a bearer -U toto >> $result
./mycurl -u https://httpbin.org/bearer -T mytoken123 -a bearer -U toto >> $result
echo =================================== >> $result  
echo Test051---------------------------------- >> $result
echo test without token BUT with MYCURL_TOKEN envvariable >> $result
echo export MYCURL_TOKEN=mytoken123
echo ./mycurl -u https://httpbin.org/bearer -a bearer -U toto >> $result
export MYCURL_TOKEN=mytoken123
./mycurl -u https://httpbin.org/bearer -a bearer -U toto >> $result
echo =================================== >> $result  
echo Test052---------------------------------- >> $result
echo test with jsonfile long parameter without value  >> $result
echo ./mycurl -u https://httpbin.org/get --jsonfile >> $result
./mycurl -u https://httpbin.org/get --jsonfile >> $result
echo =================================== >> $result  
echo Test053---------------------------------- >> $result
echo test with jsonfile short parameter without value  >> $result
echo ./mycurl -u https://httpbin.org/get -j >> $result
./mycurl -u https://httpbin.org/get -j >> $result
echo =================================== >> $result  
echo Test054---------------------------------- >> $result
echo test with jsonfile short parameter with file that does not exist  >> $result
echo ./mycurl -u https://httpbin.org/get -j xtetz >> $result
./mycurl -u https://httpbin.org/get -j xtetz >> $result
echo =================================== >> $result  
echo Test055---------------------------------- >> $result
echo test with jsonfile short parameter with file that exists and contain incorrect json content  >> $result
echo ./mycurl -u https://httpbin.org/get -j test1.json >> $result
./mycurl -u https://httpbin.org/get -j test1.json >> $result
echo =================================== >> $result  
echo Test056---------------------------------- >> $result
echo test with jsonfile short parameter with file that exists and correct json content  >> $result
echo ./mycurl -u https://httpbin.org/POST -m POST -j test.json >> $result
./mycurl -u https://httpbin.org/POST -m POST -j test.json >> $result
echo =================================== >> $result  
echo Test056---------------------------------- >> $result
echo test with multiple jsonfile parameter  >> $result
echo ./mycurl -j test1.json -j test.json >> $result
./mycurl -j test1.json -j test.json >> $result
echo =================================== >> $result  
echo Test057---------------------------------- >> $result
echo test with multiple user parameter  >> $result
echo ./mycurl --user titi -U toto >> $result
./mycurl --user titi -U toto >> $result
echo =================================== >> $result  
echo Test058---------------------------------- >> $result
echo test with multiple password parameter  >> $result
echo ./mycurl --password titi -P toto >> $result
./mycurl  --password titi -P toto >> $result
echo =================================== >> $result  
echo Test059---------------------------------- >> $result
echo test with multiple token parameter  >> $result
echo ./mycurl --token titi -T toto >> $result
./mycurl  --token titi -T toto >> $result
echo =================================== >> $result  
echo Test060---------------------------------- >> $result
echo test with multiple no ssl check parameter  >> $result
echo ./mycurl --no-ssl-check --no-ssl-check >> $result
./mycurl --no-ssl-check --no-ssl-check >> $result
echo =================================== >> $result  
echo Test061---------------------------------- >> $result
echo test with multiple no ssl check parameter and verbose >> $result
echo ./mycurl -u https://httpbin.org/get --no-ssl-check --verbose --verbose --no-ssl-check >> $result
./mycurl -u https://httpbin.org/get --no-ssl-check --verbose --verbose --no-ssl-check >> $result
echo =================================== >> $result  
echo Test062---------------------------------- >> $result
echo test with overpass parameter user length >> $result
echo ./mycurl -U 111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111 >> $result
./mycurl -U 111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111 >> $result
echo =================================== >> $result 
echo Test063---------------------------------- >> $result
echo test with overpass parameter method length >> $result
echo ./mycurl -m 111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111 >> $result
./mycurl -m 111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111 >> $result
echo =================================== >> $result 
echo Test064---------------------------------- >> $result
echo test with overpass parameter method length >> $result
echo ./mycurl -a 111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111 >> $result
./mycurl -a 111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111 >> $result
echo =================================== >> $result 
echo Test065---------------------------------- >> $result
echo test with overpass parameter password length >> $result
echo ./mycurl -P 111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111s >> $result
./mycurl -P 111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111 >> $result
echo =================================== >> $result 
echo Test066---------------------------------- >> $result
echo test with overpass parameter token length >> $result
echo ./mycurl -T 111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111 >> $result
./mycurl -T 111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111 >> $result
echo =================================== >> $result 
echo Test067---------------------------------- >> $result
echo test with overpass parameter token length >> $result
echo ./mycurl -j 111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111 >> $result
./mycurl -j 111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111 >> $result
echo =================================== >> $result 
echo Test068---------------------------------- >> $result
echo test with overpass parameter url length >> $result
echo ./mycurl -u 11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111 >> $result
./mycurl -u 11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111 >> $result
echo =================================== >> $result 