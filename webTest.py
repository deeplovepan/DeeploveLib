import urllib, urllib2, time
import json

url = 'http://127.0.0.1/deeploveLib.php' # write ur URL here

values = {'tag' : 'database', 
		  'title' : 'sqlite'
          }

try:
    data = urllib.urlencode(values)          
    req = urllib2.Request(url, data)
    response = urllib2.urlopen(req)
    the_page = response.read() 
    print the_page 

    jsonData = json.loads(the_page)
    print json.loads(the_page) 

    for data in jsonData:
	print data['title']
except Exception, detail: 
    print "Err ", detail 
