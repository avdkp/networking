import os


dict = {}
drop = {}

#os.system("ns 2.tcl ")
fp = open("oute.tr")
total = 0
time=0
for l in fp:
	l = l.replace('\n','')
	l = l.split(" ")
	if l[0]== 'r':
		total += int(l[5])
		time = float(l[1])


print "throughput = "+`float(total/time)`+" bytes/sec"
fp.close()
