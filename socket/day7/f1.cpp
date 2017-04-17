#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;

#define F first
#define S second
#define pb push_back
#define mp make_pair

struct dist_vector{
  int cost;
  int via;
};
typedef pair<int,int> pii;
typedef vector<vector<dist_vector> > table;
typedef vector<vector<pii> > graph;

void print(table &t){
  for(int i=0;i<t.size();i++){
    printf("\n\nRouting Table of node :%d \n",i);
    printf("(%s,%s,%s)\n","To","cost","next hop");
    for(int j = 0; j<t[i].size();j++){
      printf("(%d,%d,%d) ",j, t[i][j].cost,t[i][j].via);
    }
  }
}

void uprint(table &t, int node){
  printf("(%s,%s,%s) ","To","Cost","next hop");
  for(int i=0;i<t[node].size();i++){
    printf("(%d,%d,%d) ",i, t[node][i].cost,t[node][i].via);
  }
}


int main(){
  FILE *fp = fopen("input","r");
  int n; //No of nodes...
  fscanf(fp,"%d\n",&n);
  table t(n,vector<dist_vector>(n));
  graph g(n);
  //Scan edges...
  while(!feof(fp)){
    int u,v,w;
    fscanf(fp,"(%d,%d,%d)\n",&u,&v,&w);
    g[u].pb(mp(v,w));
    g[v].pb(mp(u,w));
    printf("%d %d %d\n",u,v,w);
  }
  cout<<"intput done..."<<endl;
  //Initialse routing table for each node...
  for(int i=0;i<n;i++)for(int j=0;j<n;j++){
      if(i==j){
        t[i][j].cost = 0;
        t[i][j].via = i;
        continue;
      }
      t[i][j].via  = -1;
      t[i][j].cost = 99999999;
  }
  for(int i=0;i<n;i++)
  {
    for(auto node : g[i])
    {
      t[i][node.F].cost  = node.S;
      t[i][node.F].via = node.F;
    }
  }
  print(t);

  int flag = true;
  int count = 1;
  while(flag){
    flag = false;
    printf("\n\niteration: %d",count);
    for(int i=0;i<n;i++){
      //ith node will send his dist_vector to all neighbouring node...

      for(int j=0;j<g[i].size();j++){
        int node = g[i][j].F;
        //printf("%d node is sending his table to %d node\n",i,node);
        //Try to update node's routing table with i's routing table..
        for(int k = 0;k<n;k++){
          int initial_cost = t[node][k].cost;
          int new_cost = t[i][k].cost; //+ dist(node,i)...
          for(int t = 0;t<g[node].size();t++) if(g[node][t].F == i)
          {
              new_cost+= g[node][t].S;
              break;
          }
          if(new_cost < initial_cost)
          {
            t[node][k].cost  = new_cost;
            t[node][k].via = i;
            flag = true;
          }
        }
      }
    }
    if(count == 1){
      t[1][2].cost = 1;
      t[2][1].cost = 1;
      for(int i=0;i<g[1].size();i++)
        if(g[1][i].F == 2)
          g[1][i].S = 1;

      for(int i=0;i<g[2].size();i++)
       if(g[1][i].F == 1)
        g[1][i].S = 1;
    }
    print(t);
    //sleep(3);
    count++;
    cout<<endl;
  }
  return 0;
}
