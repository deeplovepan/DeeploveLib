google api
code

import os

noopArray =  [117180.70, 120565.32] 
deadlineArray = [146149.44, 120565.32]
cfqArray = [145194.88, 120565.32]
query = "open 'http://chart.apis.google.com/chart?cht=bvg&chd=t:"
for i in range(0, len(noopArray) ):
	query = query + str(noopArray[i]/146149.44*100)
	if i == len(noopArray)-1:
		query = query + "|"
	else:
		query = query + ","
		
for i in range(0, len(deadlineArray) ):
	query = query + str(deadlineArray[i]/146149.44*100)
	if i == len(deadlineArray)-1:
		query = query + "|"
	else:
		query = query + ","
		
for i in range(0, len(cfqArray) ):
	query = query + str(cfqArray[i]/146149.44*100)
	if i != len(cfqArray)-1:
		query = query + ","

size = 500
query = query + "&chs=" + str(size);
query = query + "&chdl=noop|deadline|cfq"
query = query + "&chco=4D89F9,C6D9FD,8a2be2&chxt=x,y&chxl=0:|non-direct|direct'"
print query
		
os.system(query)

