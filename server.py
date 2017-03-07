import socket as s
import sys
import thread
import time
import threading as td
sock = s.socket(s.AF_INET,s.SOCK_STREAM)
sock.bind(("127.0.0.1",int(sys.argv[1])))
sock.listen(5)
csock,addr = sock.accept()

config = csock.recv(20)
config=config.split("$")
print "configuration recieved "+ `config`
frm=int(config[0])
win=int(config[1])
pct_count=0
RN = 0
rn_lock = td.Lock()

def update(ack):
	global RN,win,pct_count
	rn_lock.acquire()
	if ack >= 0:
		diff = (ack+win-RN)%win
		pct_count += diff
		RN = ack
	rn_lock.release()

def process(csock,addr):
	while True:
		ack = int(input(""))
		update(ack)
		ack = str(ack)+"$"
		l = len(ack)
		ack = ack+"".join(["#" for i in range(frm-l)])
		print "trying to send "+ack
		if csock.send(ack):
			print "sent"

def main_prog():
	global RN,csock
	thread.start_new_thread(process, (csock, addr))
	while True:
		data=csock.recv(frm)
		data=data.split("$")
		if data[0]=="finished":
			return 
		elif int(data[0])==RN:
			rn_lock.acquire()
			RN = (RN+1)%win
			rn_lock.release()
			print data
		else:
			pass
		time.sleep(1)
while not int(input("start? 0/1...")):
	pass
main_prog()
print 'finished'
