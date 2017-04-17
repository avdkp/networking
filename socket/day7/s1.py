import socket as s
import random as r
import sys
import thread
import time
import threading as td
sock = s.socket(s.AF_INET,s.SOCK_STREAM)
sock.bind(("127.0.0.1",int(sys.argv[1])))
sock.listen(5)
charset = ['0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F']
global_table = {}	#dest:sock  sock is eqi. port
buffer_data = []
ports = []
tab_mutex = td.Lock()
buf_mutex = td.Lock()
def fix(a):
	if len(a)<100:
		a += str("$")
	while len(a)<100:
		a += str('#')
	return a
def get_port(dest):
	global global_table
	if dest in global_table:
		return global_table[dest]
	else:
		return None
def process(csock,addr):
	global global_table,charset,tab_mutex
	mac = str(charset[int(r.random()*16)])
	for i in range(1,12):
		mac = mac+str(charset[int(r.random()*16)])
		if i%2 and (not i==11):
			mac += str(':')
	csock.send(fix(mac))
	while True:
		data = csock.recv(100)
		data = data.split("$")
		buf_mutex.acquire()
		print 'updating data is :'+`data`
		global_table[data[0]]=csock
		buffer_data.append(data)
		buf_mutex.release()
		time.sleep(1)
def buff(a):
	global buf_mutex,buffer_data,ports,global_table
	while True:
			buf_mutex.acquire()
			while len(buffer_data)>0:
				data = buffer_data.pop()
				buf_mutex.release()
				print 'global table is :'
				for key in global_table:
					print `key`+'\t'+`global_table[key]`
				print 'done'
				dest = get_port(data[1])
				if dest==None:
					for port in ports:
						data1 = data[0]+"$"+data[1]+"$broadcast$"+data[2]
						port.send(fix(data1))
						print 'sending data='+`data1`+'to port:'+`port`
				else:
					if not data[2]=='ack':
						data1 = "$".join(data)
						dest.send(fix(data1))
						print 'sending data to mac '+`data[1]`+"==>"+`data[2]`
				time.sleep(1)
				buf_mutex.acquire()
			buf_mutex.release()
thread.start_new_thread(buff, tuple(['aaa']))
while 1:
	csock,addr = sock.accept()
	ports.append(csock)
	thread.start_new_thread(process, (csock, addr))
