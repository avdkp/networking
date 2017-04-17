import socket as s
import sys
import thread
import time
sock = s.socket(s.AF_INET,s.SOCK_STREAM)
sock.bind(("127.0.0.1",int(sys.argv[1])))
sock.listen(5)
win = 10#int(input("window size?:"))
frm = 10#int(input("frame size?:"))
timer = 10#int(input("time?"))
pckt = 10#int(input("number of packets?"))
st=0
st1=st
en=win-2
en1=en
n=0
def do_it(ack):
	global st,st1,en,en1,pckt,n
	st = ack
	en = st+win
	st1=st
	en1 = en
	csock.send(`ack`)
	pckt =pckt - (ack-n+win)%win
	n=pckt
	
def process(csock,addr):
	global pckt
	while pckt>0:
		ack = int(input())
		do_it(ack)
		#n = ack

while int(input("start? 0/1")):
	pass
while 1:
	csock,addr = sock.accept()
	time.sleep(1)
	data = csock.recv(1024)
	print data.split("$")
	st1 += 1
	thread.start_new_thread(process, (csock, addr))
	while pckt>0:
		data = csock.recv(1024)
		data = data.split("$")
		if int(data[0])==st1:
			print "data : "+`data`
			st1 = (st1+1)%win
			print "st1="+`st1`
		time.sleep(1)
	print "transmission complete..."
	sys.exit(1)
