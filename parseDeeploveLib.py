# parseDeeploveLib.py
# code 
# python testWeb

import os
from sqlite3 import *

def isIncludeFile():
	if root.find(".git") == -1 and root.find(".xcodeproj") == -1 and root.find("DeeploveLib.build") == -1:
		return	1
	else:
		return 0

location = "/var/root/Documents/DeeploveLib"

databaseName = "DeeploveLib.db"
conn = connect(databaseName)
cursor = conn.cursor()
try:
	cursor.execute('''create table DeeploveLibTable USING fts3
		(id integer primary key, title text unique,
		tag text, subtag text, content text)''')
except:
	print "table exist"

for root, dirs, files in os.walk(location):
	if len(files):
		if isIncludeFile():
			for file in files:
				if file.find("DeeploveLib") != -1:
					continue
				openFile = open(location + "/" + file, "r")
				lineNumber = 0
				array = openFile.readlines()
				for line in array:
					if lineNumber == 0:
						title = line[:len(line)-1]
					elif lineNumber == 1:
						tag = line[:len(line)-1]
					lineNumber = lineNumber + 1	
				if tag.find("code") == -1 and tag.find("lib") == -1 and tag.find("ift") == -1:
					content = "".join(array[2:])
					subtag = ""
					cursor.execute('INSERT or Replace INTO DeeploveLibTable VALUES (NULL,?,?,?,?)', [title, tag, subtag, content])
					conn.commit()	
					
cursor.execute('select * from DeeploveLibTable')
for row in cursor:
    print row


cursor.close()
					
					
						