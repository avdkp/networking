#include<bits/stdc++.h>
#include<unistd.h>
#define min(a,b) (a<b?a:b)
#define MAX 10000
using namespace std;

void ss(float &cwnd,float &twnd,float &rwnd)
{
	cwnd++;
	twnd=min(cwnd,rwnd);
}
void ca(float &cwnd,float &twnd, float &rwnd,float rtt)
{
	cwnd =cwnd + 1/rtt;
	twnd = min(cwnd,rwnd);
}

int main()
{
	srand(time(NULL));
	float cwnd,twnd,rwnd,threshold;
	rwnd = 30;
	cwnd = 1;
	threshold = rwnd;
	twnd = min(cwnd,rwnd);
	int rtt = 2;
	int it = 50;
	float ack = 0.92,to = 0.04, ack3 = 0.08; 
	FILE *fp = fopen("data","w");
	for(int i=0;i<it;++i)
	{
		char event;
		int r = rand()%MAX;
		float p = (float)(r)/(float)MAX;
		if(p<to)
		{
			event = 't';
			cout<<"timeout"<<endl;
			threshold = cwnd/2;
			cwnd = 1;
	//		for(int j=0;j<cwnd/rtt;++j)
			ss(cwnd,twnd,rwnd);
		}
		else if(p<to+ack3)
		{
			cout<<"3 ack recieved..."<<endl;
			event = '3';
			threshold = cwnd/2;
			cwnd = threshold;
			ca(cwnd,twnd,rwnd,rtt);
		}
		else
		{
			event = 'a';
			cout<<"ok ";
			if(cwnd<threshold)
			{
	//			for(int j=0;j<cwnd/rtt;++j)
				ss(cwnd,twnd,rwnd);
			}
			else if(cwnd>threshold)
				ca(cwnd,twnd,rwnd,rtt);
			else;
		}
		
	//	if(i%rtt==0)
		fprintf(fp,"%d\t%f\n",i,cwnd);
		printf("cwnd:%f threshold:%f\n",cwnd,threshold);
		usleep(500000);
	}
	fclose(fp);
	//system("gnuplot -e \'load \"output\"\'");
	//system("gnome-open a.png");
return 0;
}
