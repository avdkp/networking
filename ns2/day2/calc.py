import os
fp = open("out.tr")
lines=[]

os.system("ns 2.tcl")
for line in fp:
	line =  line.replace("\n",'')
	lines.append(line.split(" "))
	
fp.close()
data=0
ti = {}
tf={}
initial = float(lines[0][1])
final = float(lines[len(lines)-1][1])
for l in lines:
	if l[0]=='r' and not 'A' in l[6]:
		data += int(l[5]) 
	
fp = open("final.txt","a")
print `initial`+' '+`final`
print data
fp.write(`data/(final-initial)`+'\n')
fp.close()
