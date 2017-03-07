import socket as s
import sys
import thread as t
import threading as td
import time
sock = s.socket(s.AF_INET,s.SOCK_STREAM)
sock.connect((sys.argv[1],int(sys.argv[2])))

frm = int(input("frame size?: "))
win = int(input("window size?: "))
timer = int(input("timeout (in sec>= transmission time of window): "))
pckt = int(input("number of packets?:"))
sock.send(`frm`+"$"+`win`)
done=False
start=0
start1=0
end=win-1
end1=win-1
sent = []
pckt1=pckt
ctr=0
mutex_done = td.Lock()
mutex_window = td.Lock()
mutex_pkct_ctr = td.Lock()

def update(ack):
	global sent,start,start1,end,end1,win,pckt,done,ctr
	mutex_window.acquire()
	#if ack="all":
	#	start=end
	#	return	
	if ack != -1:
		if (not ack in sent) and (not ack == end):
			print "invalid acknowledgement..."+`end`
			mutex_window.release()
			return 
		diff = (ack+win-start)%win
		start = ack
		end = (ack+win-1)%win
		pckt -= diff
		sent=[]
		if pckt<win:
			end = (start+pckt)%win
		if pckt==0:
			#mutex_done.acquire()
			done=True
			#mutex_done.release()
		print "packets left : "+`pckt`
	start1=start
	end1=end
	mutex_pkct_ctr.acquire()
	ctr=0
	mutex_pkct_ctr.release()
	mutex_window.release()

def start_timer(sock,timer):
	global done
	while True:
		try:
			sock.settimeout(timer)
			data = sock.recv(frm)
			data = data.split('$')
			ack = int(data[0])
			print `ack`+" recieved..."
			update(ack)
			sock.settimeout(None)
		except s.timeout:
			print "timeout..."
			update(-1)
		if done:
			return
def send_data(sock):
	global frm,start1,end1,start,end,win,sent,ctr,pckt1,pckt
	temp = "$this is packet$"+`pckt1-pckt+ctr`+"$"
	mutex_pkct_ctr.acquire()
	ctr+=1
	mutex_pkct_ctr.release()
	data=""
	if not start1==end1:
		mutex_window.acquire()
		data = str(start1)+temp
		l = len(data)
		data = data+"".join(["#" for i in range(frm-l)])
		data = data[:frm]
		sent.append(start1)
		if sock.send(data):
			start1 = (start1+1)%win
		mutex_window.release()
	else:
		update(-1)
	print data
while not int(input("start? 0/1...")):
	pass
t.start_new_thread(start_timer,(sock,timer))
while not done:
	send_data(sock)
	time.sleep(1)
sock.send("finished")
