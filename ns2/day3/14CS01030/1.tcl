set ns [new Simulator] 

set nf [open out.nam w]
$ns namtrace-all $nf   

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
$ns duplex-link $n0 $n2   2Mb  10ms DropTail
$ns duplex-link $n1 $n2   2Mb  10ms DropTail
$ns duplex-link $n2 $n3 0.3Mb 200ms DropTail
$ns duplex-link $n3 $n4   2Mb  40ms DropTail
$ns duplex-link $n3 $n5   2Mb  30ms DropTail


$ns queue-limit $n2 $n3 4
$ns duplex-link-op $n2 $n3 queuePos 0.5


# change TCP agent here

#set tcp1 [new Agent/TCP]
set tcp1 [new Agent/TCP/Reno]
#set tcp1 [new Agent/TCP/Newreno]
#set tcp1 [new Agent/TCP/Sack1]
#set tcp1 [new Agent/TCP/Vegas]

$ns attach-agent $n0 $tcp1
set sink1 [new Agent/TCPSink]
$ns attach-agent $n4 $sink1
$ns connect $tcp1 $sink1
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ftp1 set type_ FTP    

    
set tcp2 [new Agent/TCP/Vegas]
$ns attach-agent $n1 $tcp2
set sink2 [new Agent/TCPSink]
$ns attach-agent $n5 $sink2
$ns connect $tcp2 $sink2
set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2
$ftp2 set type_ FTP         

set trace_file0 [open  "oute.tr"  w]
  $ns  trace-queue  $n2  $n3  $trace_file0



$ns at 0.1   "$ftp1 start"
$ns at 0.1   "$ftp2 start"
$ns at 40.0 "$ftp2 stop"
$ns at 40.0 "$ftp1 stop"
$ns at 50.0 "finish"            

proc plotWindow {tcpSource outfile} {
   global ns
   set now [$ns now]
   set cwnd [$tcpSource set cwnd_]
   puts  $outfile  "$now $cwnd"
   $ns at [expr $now+0.1] "plotWindow $tcpSource  $outfile"
}

set outfile [open  "congestion.xg"  w]
$ns  at  0.0  "plotWindow $tcp1  $outfile"
proc finish {} {
	global ns nf
	$ns flush-trace
	close $nf
	exec nam out.nam &
 exec xgraph congestion.xg -geometry 300x300 &
   exit 0
}
$ns run
