import socket as s
import math as mt
import sys
sock = s.socket(s.AF_INET,s.SOCK_STREAM)
sock.connect((sys.argv[1],int(sys.argv[2])))

#isock.bind((sys.argv[1],int(sys.argv[2])))
#sock.listen(5)
def get_n(m):
	r =0;
	while m+r+1>2**r:
		r=r+1
	return r
def cal_xor(data,i):
	for j in range(i-1,len(data)):
		if ((j+1)/i)%2:
			data[i-1] = data[i-1]^data[j]
sn=0
data = raw_input("Enter the data:")
while(1):
	sock.send(str(sn)+"$"+data)
	try:
		sock.settimeout(5.0)
		data = sock.recv(1024)
		sock.settimeout(None)
	except s.timeout:
		print "timeout"
		print "acknowledgement not recieved"
		continue
	sn+=1
	print "acknowledgement recieved"	
	data = raw_input("Enter the data:")
	
