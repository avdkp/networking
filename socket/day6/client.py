import socket as s
import sys
import thread as t
import time
sock = s.socket(s.AF_INET,s.SOCK_STREAM)
sock.connect((sys.argv[1],int(sys.argv[2])))
ack = -1
frm = 10#int(input("frame size?: "))
win = 10#int(input("window size?: "))
timer = 10#int(input("timeout (in sec): "))
pckt = 10#int(input("number of packets?:"))
st=0
en=win-2
st1 = st
en1 = en
p=0
tok=0
def start_timer(sock,timer):
	global ack,st,tok,st1,en,en1,pckt
	try:
		sock.settimeout(timer)
		data = sock.recv(1024)
		ack = int(data)
		if ack>st1:
			pckt = pckt - (ack - st1)
		else:
			pckt = pckt -(ack+win-st1)
		st = ack
		en = (st+win-1)%win
		sock.settimeout(None)
	except s.timeout:
		print "timeout..."
		tok=1
		st1=st
		en1=en
def do_something():
	global st,st1,en,en1,ack,timer
	a = ack
	if ack<st:
		ack +=win
	en = (en + ack-st)%win
	st = a
	st1 = st
	en1 = en
def getdata(frm):
	global p,pckt
	if pckt>0:
		return "this is packet\n"	
	else:
		print "transmission complete..."
		sys.exit(1)
def do_it():
	global st,tok,st1,en,en1,pckt,win,frm
	while(1):
		time.sleep(1)
		data = getdata(frm)
		data = `st1`+"$"+data
		print "sending data...: "+`data`
		sock.send(data)
		st1 = (st1+1)%win
		t.start_new_thread(start_timer,(sock,timer))
		while st1<=en1:
			time.sleep(1)
			data = getdata(frm)
			data = `st1`+"$"+data
			sock.send(data)
			print "sent :" +`data`
			st1 = (st1+1)%win
			if ack>-1:
				print "doing something"
				do_something()
				break
			if tok>0:
				time.sleep(10)
				tok=0
				st1=st
				en1 = en
				break
while not int(input("start? 0/1")):
	pass
while pckt>0:
	do_it()
