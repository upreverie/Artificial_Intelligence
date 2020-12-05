#include<bits/stdc++.h>
using namespace std;
typedef  pair<pair<int,string>, vector<vector<int>> > pi;
typedef  vector<queue<int>> vq;
typedef vector<vector<int>> vofv;
int heuristic(vofv &v, vofv &goal,int n)
{
    int count=0;
    for(int i=0;i<n;i++)
    {
        set<int> ss;
        for(int j=0;j<v[i].size();j++)
        {
            ss.insert(v[i][j]);
        }
        for(int j=0;j<goal[i].size();j++)
        {
            if(ss.find(goal[i][j])==ss.end())
            {
               count=count+2;
            }
        }
    }
    return count;

}
void bfs(vofv &v,vofv &goal,int n)
{
    priority_queue<pi, vector<pi>, greater<pi> > open; 

    set<vofv> closed;
    map<vofv,int> g_fun;
    map<vofv,int> h_fun;
    map<vofv,int> f_fun;
    int found=0;

    map<vofv,string> path;
    // f function 
    g_fun[v]=0;
    h_fun[v]= heuristic(v,goal,n);
    f_fun[v]=g_fun[v]+h_fun[v];
   // cout<<g_fun[v] +h_fun[v]<<"\n";
    path[v]="";
    open.push(make_pair(make_pair(f_fun[v],path[v]),v));

    // map<vofv,vofv> parent;
    // parent[v]=v;

   while(!open.empty())
   {
       int fval=open.top().first.first;
       string pth=open.top().first.second;
       vofv state=open.top().second;
       open.pop();

       if(state==goal)
       {
           //cout<<g_fun[state]<<"\n";
           cout<<path[state]<<"\n";
           
           found=1;
           break;
       }

      closed.insert(state);

       vofv tempstate;
       for(int i=0;i<n;i++)
       {
           tempstate=state;
           int flag=0;
           int x;
           if(tempstate[i].size()!=0)
           {
               vector<int> rod=tempstate[i];
               x=rod[0];
               flag=1;
               tempstate[i].erase(tempstate[i].begin());
           }
           if(flag==1)
           {
               for(int j=0;j<n;j++)
               {
                   vector<vector<int>> nextstate;
                   nextstate=tempstate;
                   nextstate[j].push_back(x);

                    if((closed.find(nextstate)==closed.end()))
                   {
                       int g,h,f;
                       g=g_fun[state]+2;
                       h=heuristic(nextstate,goal,n);
                       f=g+h;

                        string s="";
                        if(path.find(state)!=path.end())
                        {
                            s=path[state];
                        }
                        s=s+"\n"+"remove out "+to_string(x)+" from "+to_string(i)                                       +"\n"+"insert "+to_string(x)+" in "+to_string(j);

                       if( (f_fun.find(nextstate)==f_fun.end()) || f_fun[nextstate]>f)
                       {
                          
                           g_fun[nextstate]=g;
                           h_fun[nextstate]=h;
                           f_fun[nextstate]=f;
                            path[nextstate]=s;
                           open.push(make_pair(make_pair(f_fun[nextstate],s),nextstate));
                          
                          // parent[nextstate]=state;
                       }
                       else if(f_fun[nextstate]==f)
                       {
                           if(path[nextstate]>s)
                           {
                                g_fun[nextstate]=g;
                                h_fun[nextstate]=h;
                                f_fun[nextstate]=f;
                                path[nextstate]=s;
                                open.push(make_pair(make_pair(f_fun[nextstate],s),nextstate));
                               // parent[nextstate]=state;
                           }
                       }
                   }
               }
               
           }
          
       }
   }
    // if(found==0) cout<<"-1\n";
}
int main()
{
// refernce ->  https://www.geeksforgeeks.org/a-search-algorithm/
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<vector<int>> vv;
        for(int i=0;i<n;i++)
        {
            int x;
            cin>>x;
            vector<int> v;

            for(int j=0;j<x;j++)
            {
                int y;
                cin>>y;
                v.push_back(y);
            }
            vv.push_back(v);
        }
        vector<vector<int>> goal;
        for(int i=0;i<n;i++)
        {
            int x;
            cin>>x;
            vector<int> v;
            for(int j=0;j<x;j++)
            {
                int y;
                cin>>y;
                v.push_back(y);
 
            }
            goal.push_back(v);
        }

        bfs(vv,goal,n);

    }
}

