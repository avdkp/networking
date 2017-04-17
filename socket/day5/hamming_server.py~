import socket as s
import math as mt
import sys
import thread
sock = s.socket(s.AF_INET,s.SOCK_STREAM)
sock.bind(("127.0.0.1",int(sys.argv[1])))
sock.listen(5)
def cal_xor(data,i):
	for j in range(i,len(data)):
		if ((j+1)/i)%2:
			#print `data[j]`+'^'+`data[i-1]`
			data[i-1] = data[i-1]^data[j]
			#print data[i-1]
	##print "\n\n"

def get_int(a):
	num=0;
	for i in range(len(a)):
		num += (2**i) * a[i]
	return num
def process(csock,addr):
	while 1:
		data = csock.recv(1024)
		data = list(data)
		num = []
		data = [int(a) for a in data]
		print data
		for i in range(int(mt.log(len(data),2))+1):
			cal_xor(data,2**i)
			num.append(data[(2**i) - 1])
		print num
		if get_int(num)==0:
			print "data is fine"
		else:
			print "data is corrupt and error is at bit "+`get_int(num)`
		

#isock.bind((sys.argv[1],int(sys.argv[2])))
#sock.listen(5)


while 1:
	csock,addr = sock.accept()
	thread.start_new_thread(process, (csock, addr))
