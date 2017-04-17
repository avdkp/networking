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
	exec nam out.nam &
	exit 0
	}

set n0 [$ns node]
set n1 [$ns node]

#Create links between the nodes

$ns duplex-link $n0 $n2 1Mb 10ms DropTail

#Set Queue Size of link (n2-n3) to 10
$ns queue-limit $n2 $n3 10
#Give node position (for NAM)
$ns duplex-link-op $n0 $n1 orient right


set tcp1 [new Agent/TCP]
$tcp1 set class_ 2
$ns attach-agent $n0 $tcp1
set sink1 [new Agent/TCPSink]
$ns attach-agent $n1 $sink1


$ns connect $tcp1 $sink1
$tcp1 set fid_ 1

set cbr [new Application/CBR]
$cbr attach-agent $tcp1
$cbr set type_ CBR

#Schedule events for the CBR and FTP agents
$ns at 0.1 "$cbr start"

$ns at 4.5 "$cbr stop"
#Detach tcp and sink agents (not really necessary)
#$ns at 4.5 "$ns detach-agent $n0 $tcp1; $ns detach-agent $n0 $tcp2 ; $ns detach-agent $n1 $sink1; $ns detach-agent $n4 $sink2"
#Call the finish procedure after 5 seconds of simulation time
$ns at 5.0 "finish"
#Print CBR packet size and interval
#puts "CBR packet size = [$cbr set packet_size_]"

#puts "CBR interval = [$cbr set interval_]"

#Run the simulation

$ns run
