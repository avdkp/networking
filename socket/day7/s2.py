import socket as s
import random as r
import sys
import thread as t
import time
import threading as td
import copy
sock = s.socket(s.AF_INET,s.SOCK_STREAM)
sock.bind(("127.0.0.1",int(sys.argv[1])))
sock.listen(5)
pckt_size = 100
def fix(a):
	global pckt_size
	if len(a)<pckt_size:
		a += str("$")
	while len(a)<pckt_size:
		a += str('#')
	return a
def str_to_dict(a):
	a = a.replace("{",'').replace('}','').replace(' ','').replace('\n','')
	b = dict([tuple(x.split(":")) for x in a.split(",")])
	aa = {}
	for x in b:
		aa[int(x)] = copy.deepcopy(b[x])
	return aa
def process(csock,addr):
	global port
	while True:
		data = csock.recv(pckt_size)
		data = data.split("$")
		if len(port)>=int(data[0]):
			port[int(data[0])].send(fix(data[1]+"$"+data[2]))

no_cli = 0
port = []
while True:
	csock,addr = sock.accept()
	csock.send(fix(`no_cli`))
	port.append(csock)
	no_cli += 1
	t.start_new_thread(process, (csock, addr))
