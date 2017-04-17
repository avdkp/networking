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
while(1):
	data = raw_input("Enter the data:")
	data = list(data)
	data = [int(a) for a in data]
	l = len(data)
	max_size = get_n(len(data))
	for i in range(max_size+1):
		data.insert(int(2**i-1),0)
	for i in range(max_size+1):
		cal_xor(data,2**i)	
	print data
	bit = int(input("enter bit to corrupt(-ve to none):"))
	if bit>=0 and bit<len(data):
 		data[bit] = 1 if data[bit]==0 else 0
	data = [chr(a+ord('0')) for a in data]
	packet = "".join(data)
	sock.send(packet)

