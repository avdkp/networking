#Create a simulator object
set ns [new Simulator]
#Define different colors for data flows (for NAM)
$ns color 1 Blue
$ns color 2 Red
$ns color 3 Green
#Open the NAM trace file
set nf [open out.nam w]
$ns namtrace-all $nf
#Define a &#39;finish&#39; procedure
proc finish {} {
	global ns nf
	$ns flush-trace
	#Close the NAM trace file
	close $nf
	#Execute NAM on the trace file
	#exec nam out.nam &
	exit 0
	}
#Create four nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
#Create links between the nodes

$ns simplex-link $n0 $n1 2Mb 10ms DropTail
$ns duplex-link $n1 $n2 2Mb 10ms DropTail
$ns duplex-link $n2 $n3 2Mb 10ms DropTail
$ns duplex-link $n3 $n4 2Mb 10ms DropTail
$ns simplex-link $n4 $n0 2Mb 10ms DropTail
#Set Queue Size of link (n2-n3) to 10
$ns queue-limit $n2 $n3 10
#Give node position (for NAM)
$ns simplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n1 $n2 orient down
$ns duplex-link-op $n2 $n3 orient left
$ns duplex-link-op $n3 $n4 orient left-up
$ns simplex-link-op $n4 $n0 orient right-up

#Monitor the queue for link (n2-n3). (for NAM)
$ns duplex-link-op $n2 $n3 queuePos 0.5
#Setup a TCP connection
set tcp1 [new Agent/TCP]
$tcp1 set class_ 2
set tcp2 [new Agent/TCP]
$tcp2 set class_ 2
$ns attach-agent $n0 $tcp1
$ns attach-agent $n0 $tcp2
set sink1 [new Agent/TCPSink]
set sink2 [new Agent/TCPSink]

$ns attach-agent $n1 $sink1
$ns attach-agent $n4 $sink2

$ns connect $tcp1 $sink1
$ns connect $tcp2 $sink2
$tcp1 set fid_ 1
$tcp2 set fid_ 3
#Setup a FTP over TCP connection
set ftp1 [new Application/FTP]
set ftp2 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ftp2 attach-agent $tcp2
$ftp1 set type_ FTP
$ftp2 set type_ FTP
#Setup a UDP connection
set udp [new Agent/UDP]
$ns attach-agent $n3 $udp
set null [new Agent/Null]
$ns attach-agent $n2 $null
$ns connect $udp $null
$udp set fid_ 2
#Setup a CBR over UDP connection
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_ CBR
$cbr set packet_size_ 1000
$cbr set rate_ 1mb
$cbr set random_ false
#Schedule events for the CBR and FTP agents
$ns at 0.1 "$cbr start"
$ns at 1.0 "$ftp1 start"
$ns at 1.5 "$ftp2 start"
$ns at 4.0 "$ftp2 stop"
$ns at 5.0 "$ftp1 stop"
$ns at 4.5 "$cbr stop"
#Detach tcp and sink agents (not really necessary)
$ns at 4.5 "$ns detach-agent $n0 $tcp1; $ns detach-agent $n0 $tcp2 ; $ns detach-agent $n1 $sink1; $ns detach-agent $n4 $sink2"
#Call the finish procedure after 5 seconds of simulation time
$ns at 5.0 "finish"
#Print CBR packet size and interval
#puts "CBR packet size = [$cbr set packet_size_]"

#puts "CBR interval = [$cbr set interval_]"

#Run the simulation

$ns run
