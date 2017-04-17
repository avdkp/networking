import socket as s
import sys
import thread as t
import time
import threading as td
import copy
sock = s.socket(s.AF_INET,s.SOCK_STREAM)
sock.connect((sys.argv[1],int(sys.argv[2])))
pckt_size = 100
table = {} #id:cost
tab_lock = td.Lock()

def fix(a):
	global pckt_size
	if len(a)<pckt_size:
		a += str("$")
	while len(a)<pckt_size:
		a += str('#')
	return a
def str_to_dict(a):
	a = a.replace("{",'').replace('}','').replace(' ','').replace('\n','')
	print a
	b = dict([tuple(map(int,x.split(":"))) for x in a.split(",")])
	aa = {}
	for x in b:
		aa[int(x)] = copy.deepcopy(b[x])
	return aa
def broadcast():
	global table,link
	for key in link:
		sock.send(fix(`key`+"$"+`table`+"$"+`my_id`))
def update(data,frm):
	global table
	flag = 0
	for key,val in data.iteritems():
		if key in table:
			if val+table[frm]<table[key]:
				table[key]=val+table[frm]
				flag = 1
			else:
				pass
		else:
			#print table
			table[key] = val+table[frm]
			flag = 1
	return flag
def update1(data):
	global table
	for key,val in data.iteritems():
		table[key]=val
def recieve(sock):
	global table
	while True:
		try:
			queue = []
			sock.settimeout(5)
			while True:
				data = sock.recv(pckt_size)
				data = data.split("$")
				data1 = str_to_dict(data[0])
				queue.append([data1,int(data[1])])
		except s.timeout:
			pass
		for data in queue:
			flag = update(data[0],data[1])
			if flag==1:
				broadcast()
		print table
t.start_new_thread(recieve,tuple([sock]))
data = sock.recv(pckt_size)
data = data.split("$")
my_id = int(data[0])
print 'my id = '+ `my_id`
fp = open("input")
lines = fp.readlines()
fp.close()
link =  str_to_dict(lines[my_id])
print 'link = '+`link`
time.sleep(5)
update1(link)
#print table
broadcast()
recieve(sock)
