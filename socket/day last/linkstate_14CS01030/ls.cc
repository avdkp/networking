#include<bits/stdc++.h>
#include<unistd.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define INF 9999999
#define dbg cout<<"hi"<<endl;
using namespace std;
typedef pair<int,int> link_data;		//to,wt


int main()
{
	int no_nodes,no_edges;
	FILE *fp = fopen("input","r");
	fscanf(fp,"%d",&no_nodes);
	fscanf(fp,"%d",&no_edges);
//cout<<"V="<<no_nodes<<" E="<<no_edges<<endl;
	vector<link_data > adj_list[no_nodes];	
	int from,to,wt;
	for(int i=0;i<no_edges;++i)
	{
		fscanf(fp,"\nedge(%d,%d,%d)",&from,&to,&wt);
		//printf("(%d,%d,%d)\n",from,to,wt);
		adj_list[from].pb(mp(to,wt));
		adj_list[to].pb(mp(from,wt));
	}
	//dijkestra
	fclose(fp);
	do
	{
		
		cout<<"flooding..."<<endl;
		sleep(3);
		for(int i=0;i<no_nodes;++i)
			{
				// for i th source node
				int cost[no_nodes],done[no_nodes],parent[no_nodes];
				for(int j=0;j<no_nodes;++j)	
				{
					cost[j]=INF;
					parent[j]=-1;
					done[j]=0;
				}
				cost[i]=0;
				parent[i] = i;
				priority_queue<pair<int,int>, vector<pair<int,int> >, std::greater<pair<int,int> > > q;
				q.push(mp(0,i));
				while(!q.empty())
				{
					auto a = q.top();
					q.pop();
					if(cost[a.S]<a.F)
						continue;

					for(int j=0;j<adj_list[a.S].size();++j)
					{
		//printf("%d %d %d %d",done[adj_list[a.S][j].F],cost[adj_list[a.S][j].F],cost[a.S],adj_list[a.S][j].S);
						if(done[adj_list[a.S][j].F]==0&&cost[adj_list[a.S][j].F]>cost[a.S]+adj_list[a.S][j].S)
						{
							cost[adj_list[a.S][j].F] = cost[a.S]+adj_list[a.S][j].S;
							parent[adj_list[a.S][j].F] = a.S;
							q.push(mp(cost[adj_list[a.S][j].F],adj_list[a.S][j].F));
						//	cout<<"("<<cost[adj_list[a.S][j].F]<<","<<adj_list[a.S][j].F<<") pushed"<<endl;
						}
					}
					//cout<<"done "<<a.S<<endl;
					done[a.S] = 1;
				}
				cout<<"Calculating..."<<endl;
				cout<<"Routing table of "<<i<<endl;
				sleep(1);
				cout<<"To\t"<<"Cost\t"<<"Next Hop"<<endl;
				for(int j=0;j<no_nodes;++j)
				{
					cout<<j<<"\t"<<cost[j]<<"\t";
					int next=j;
					int p = j;
					while(p!=parent[p])
					{
						next = p;
						p = parent[p];
					}
					cout<<next<<"\t"<<endl;
				}
				cout<<"\n\n";
			}

		int ch;
		cout<<"1.add a link\n2.disconnect a link\n3.update a link\n4.exit"<<endl;
		cin>>ch;
		switch(ch)
		{
			case 1:	no_edges++;
					cout<<"n1 n2 wt"<<endl;
					cin>>from>>to>>wt;
					adj_list[from].pb(mp(to,wt));
					adj_list[to].pb(mp(from,wt));
				break;
			case 2:	no_edges--;
					cout<<"n1 n2"<<endl;
					cin>>from>>to;
					for(vector<link_data>::iterator it=adj_list[from].begin();it!=adj_list[from].end();it++)
						if(it->F==to)
						{
							adj_list[from].erase(it);
							break;
						}
					for(vector<link_data>::iterator it=adj_list[to].begin();it!=adj_list[to].end();it++)
						if(it->F==from)
						{
							adj_list[to].erase(it);
							break;
						}
				break;
			case 3:	cout<<"n1 n2 wt"<<endl;
					cin>>from>>to>>wt;
					for(vector<link_data>::iterator it=adj_list[from].begin();it!=adj_list[from].end();it++)
						if(it->F==to)
						{
							it->S = wt;
							break;
						}
					for(vector<link_data>::iterator it=adj_list[to].begin();it!=adj_list[to].end();it++)
						if(it->F==from)
						{
							it->S = wt;
							break;
						}

				break;
			case 4:
			default:	return 0;
		}
	}while(1);
return 0;
}
