import socket as s
import sys
import thread as t
import time
sock = s.socket(s.AF_INET,s.SOCK_STREAM)
sock.connect((sys.argv[1],int(sys.argv[2])))
c_mac = sock.recv(100)
c_mac = c_mac.split("$")
def fix(a):
	if len(a)<100:
		a += str("$")
	while len(a)<100:
		a += str('#')
	return a
def recieve(sock):
	global c_mac
	while True:
		data = sock.recv(100)
		data1 = data.split("$")
		if not data1[1]==c_mac[0]:
			continue
		if data1[2]=='broadcast':
			aa = `c_mac[0]`+"$"+`c_mac[0]`+"$ack"
			sock.send(fix(aa))
			print 'ac='+`aa`
			print `data1[0]`+"===>"+`data1[1]`+"{"+`data1[3]`+"}"
		else:
			print `data1[0]`+"===>"+`data1[1]`+"{"+`data1[2]`+"}"

print "packet format = [destination,message]"
t.start_new_thread(recieve,tuple([sock]))

while True:
	data = input("["+str(c_mac[0])+"]> ")
	data = [`c_mac[0]`]+data
	data = "$".join(data)
	sock.send(fix(data))
	time.sleep(0.01)
