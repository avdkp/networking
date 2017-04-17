import os


dict = {}
drop = {}

os.system("ns 2.tcl")
fp = open("out.tr")
for l in fp:
	l = l.replace('\n','')
	l = l.split(" ")
	if l[0]== 'd':
		drop[l[0]]=1
fp.close()
fp = open("out_1.tr")
for l in fp:
	l = l.replace('\n','')
	l = l.split(" ")
	if l[0] == 'd':
		drop[l[0]]=1
fp.close()
fp = open("out_2.tr")
for l in fp:
	l = l.replace('\n','')
	l = l.split(" ")
	if l[0] == 'd':
		drop[l[0]]=1
fp.close()
fp1 = open("newout.tr","w")
fp = open("out.tr")
for l in fp:
	l = l.replace("\n"," ")
	l = l.split(" ")
	if not float(l[11]) in drop:
		fp1.write(" ".join(l)+"\n")
fp.close()
fp = open("out_1.tr")
for l in fp:
	l = l.replace("\n"," ")
	l = l.split(" ")
	if not float(l[11]) in drop:
		fp1.write(" ".join(l)+"\n")
fp.close()
fp = open("out_2.tr")
for l in fp:
	l = l.replace("\n"," ")
	l = l.split(" ")
	if not float(l[11]) in drop:
		fp1.write(" ".join(l)+"\n")
fp.close()
fp1.close()

'''

for line in fp:
	line =  line.replace("\n",'')
	line = line.split(" ")
	if l[0] in drop:
		continue
	if not line[11] in dict:
		if line[0]=="+":
			dict[line[11]] = float(line[1])
	else:
		if line[0]=="+":
			dict[line[11]] += float(line[1])
		elif line[0]=="-":
			dict[line[11]] -= float(line[1])
		else:
			pass
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
'''
