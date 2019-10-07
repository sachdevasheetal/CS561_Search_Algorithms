#include<bits/stdc++.h>
using namespace std;
typedef struct cell_data
{
	double f;
	double g;
	double h;
}cell_data;

void printpath(vector<pair<int,int> > res)
{
	int len=res.size();
	for(int i=0;i<len;i++)
	{
		cout<<res[i].second<<","<<res[i].first<<" ";
	}
	cout<<endl;
}

double calculateHeuristic(int row, int col, pair<int,int> dest) 
{ 
   /* return ((double)sqrt ((row-dest.first)*(row-dest.first) 
                          + (col-dest.second)*(col-dest.second))*10);     */
	return max(abs(row-dest.first),abs(col-dest.second))*10;                
    
}

void Astar_search_parent_child(pair<int,int> src,int diff,vector<vector<int> > elevation,int row,int col,pair<int,int> target, map<pair<int,int>, pair<int,int> > &parent_child)
{
	
	map<pair<int,int>,cell_data> cell;
	priority_queue<pair<double, pair<int,int> >, vector<pair<double, pair<int,int> > >, greater<pair<double, pair<int,int> > > >q;
	cell_data cell_store;
	cell_store.g=0;
	cell_store.h=calculateHeuristic(src.first,src.second,target);
	cell_store.f=cell_store.g+cell_store.h;
	cell[src]=cell_store;
	q.push(make_pair(0.0,src));
	set<pair<int,int> > visited;
	visited.insert(src);
	set<pair<int,int> > closed;
	double initial_cost=0.0;
	parent_child[src]=src;
	while(q.empty()==false)
	{
	//	cout<<"cost";
		pair<int,int> last=q.top().second;
		initial_cost=cell[last].g;
		q.pop();
		if(closed.find(last)!=closed.end())
		continue;
		closed.insert(last);
		if(target.first==last.first&&target.second==last.second)
		{
			//cout<<initial_cost<<endl;
			return;
		}
		for(int i=max(0,last.first-1);i<=min(last.first+1,row-1);i++)
		{
			for(int j=max(0,last.second-1);j<=min(last.second+1,col-1);j++)
			{
				if(i!=last.first||j!=last.second){
				
				pair<int,int> ele=make_pair(i,j);
				if(visited.find(ele)==visited.end()&&(abs(elevation[i][j]-elevation[last.first][last.second])<=diff))
				{
					if(abs(last.first-i)+abs(last.second-j)==2)
					cell_store.g=initial_cost+14+abs(elevation[i][j]-elevation[last.first][last.second]);
					else
					cell_store.g=initial_cost+10+abs(elevation[i][j]-elevation[last.first][last.second]);
					
					cell_store.h=calculateHeuristic(i,j,target);
					cell_store.f=cell_store.g+cell_store.h;
					cell[ele]=cell_store;
						q.push(make_pair(cell[ele].f,ele));
						visited.insert(ele);
						parent_child[ele]=last;
				}
				else if(closed.find(ele)==closed.end()&&visited.find(ele)!=visited.end()&&(abs(elevation[i][j]-elevation[last.first][last.second])<=diff))
				{
					double heu=calculateHeuristic(i,j,target);
					cell[ele].h=heu;
					if(abs(last.first-i)+abs(last.second-j)==2)
					{
						if(cell[ele].f<initial_cost+14+abs(elevation[i][j]-elevation[last.first][last.second])+heu)
						continue;
						else
						{
							cell[ele].g=initial_cost+14+abs(elevation[i][j]-elevation[last.first][last.second]);
							cell[ele].f=initial_cost+14+abs(elevation[i][j]-elevation[last.first][last.second])+heu;
						}
					}
					else
					{
						if(cell[ele].f<initial_cost+10+abs(elevation[i][j]-elevation[last.first][last.second])+heu)
						continue;
						else
						{
							cell[ele].g=initial_cost+10+abs(elevation[i][j]-elevation[last.first][last.second]);
							cell[ele].f=initial_cost+10+abs(elevation[i][j]-elevation[last.first][last.second])+heu;
						}
					}
					
					q.push(make_pair(cell[ele].f,ele));
					parent_child[ele]=last;
				}
				}
			}
		}
	}
}

void BFS_Search_parent_child(pair<int,int> src,int diff,vector<vector<int> > elevation,int row,int col,pair<int,int> target,map<pair<int,int>, pair<int,int> > &parent_child)
{
	queue<pair<int,int> > q;
	parent_child[src]=src;
	set< pair<int,int> >  visit;
	visit.insert(src);
	q.push(src);
	while(!q.empty())
	{
		pair<int,int> last=q.front();
		q.pop();
		if(target.first==last.first&&target.second==last.second)
		{
			return;
		}
		
		for(int i=max(0,last.first-1);i<=min(last.first+1,row-1);i++)
		{
			for(int j=max(0,last.second-1);j<=min(last.second+1,col-1);j++)
			{
				if(i!=last.first||j!=last.second)
				{
					
					if((visit.find(make_pair(i,j))==visit.end())&&(abs(elevation[i][j]-elevation[last.first][last.second])<=diff))
					{
						pair<int,int> ele=make_pair(i,j);
						q.push(ele);
						visit.insert(ele);
						parent_child[ele]=last;
					}
				}
			}
		}
		
	}
	
}
void UCS_Search_parent_child(pair<int,int> src,int diff,vector<vector<int> > elevation,int row,int col,pair<int,int> target,map<pair<int,int>, pair<int,int> > &parent_child)
{
	priority_queue<pair<int, pair<int,int> >, vector<pair<int, pair<int,int> > >, greater<pair<int, pair<int,int> > > >q;
	q.push(make_pair(0,src));
	map<pair<int,int>,int> visited;
	visited[src]=0;
	vector<pair<int,int> > res;
	int initial_cost=0;
	parent_child[src]=src;
	set<pair<int,int> > closed;
//	closed.insert(src);
	while(q.empty()==false)
	{
		if(q.empty()==true)
		break;
		pair<int,int> last=q.top().second;
		q.pop();
		
		if(closed.find(last)!=closed.end())
		continue;
		
		closed.insert(last);
		initial_cost=visited[last];
	//	cout<<last.first<<" "<<last.second<<" "<<initial_cost<<endl;
	//	cout<<last.first<<" "<<last.second<<" ";
		if(target.first==last.first&&target.second==last.second)
		{
		
		//if(visited[last]>=initial_cost)
		
			visited[last]=initial_cost;
		
	//	cout<<initial_cost<<endl;
		return;
		}
		for(int i=max(0,last.first-1);i<=min(last.first+1,row-1);i++)
		{
			for(int j=max(0,last.second-1);j<=min(last.second+1,col-1);j++)
			{
				if(i!=last.first||j!=last.second){
				
				pair<int,int> ele=make_pair(i,j);
				if(visited.find(ele)==visited.end()&&(abs(elevation[i][j]-elevation[last.first][last.second])<=diff))
				{				
					if(abs(last.first-i)+abs(last.second-j)==2)
					visited[ele]=initial_cost+14;
					else
					visited[ele]=initial_cost+10;
					q.push(make_pair(visited[ele],ele));
					parent_child[ele]=last;
				}
				else if(closed.find(ele)==closed.end()&&visited.find(ele)!=visited.end()&&(abs(elevation[i][j]-elevation[last.first][last.second])<=diff))
				{
					
					if(abs(last.first-i)+abs(last.second-j)==2)
					{
						if(visited[ele]<initial_cost+14)
						continue;
						else
						visited[ele]=initial_cost+14;
					}
					
					else{
						if(visited[ele]<initial_cost+10)
						continue;
						else
						visited[ele]=initial_cost+10;
					}	
						parent_child[ele]=last;
						q.push(make_pair(visited[ele],ele));
				}
				}
			}
		}
	}
}

void print_parent_child(map<pair<int,int>, pair<int,int> > parent_child,pair<int,int> src,pair<int,int> target)
{
		if(parent_child.find(target)==parent_child.end())
		cout<<"FAIL"<<endl;
		else
		{
			vector<pair<int,int> > res;
			pair<int,int> traverse=target;
			
		while(traverse.first!=src.first||traverse.second!=src.second)
		{
			res.push_back(make_pair(traverse.first,traverse.second));
			traverse=parent_child[traverse];
		}
		res.push_back(make_pair(src.first,src.second));
		reverse(res.begin(),res.end());
		int len=res.size();
		//cout<<endl<<"Number of Nodes "<<res.size()<<endl;
		for(int i=0;i<len;i++)
		{
			cout<<res[i].second<<","<<res[i].first<<" ";
		}
		cout<<endl;
		}
		
}

int main()
{
	ios_base::sync_with_stdio(false);
//	clock_t start,end;
//	start=clock();
	string search_type;
	int col,row;
	int start_x,start_y,max_diff,target_num;
    FILE *fp1=freopen("input.txt", "r", stdin);
	cin>>search_type;
	cin>>col>>row;
	cin>>start_y>>start_x;
	cin>>max_diff;
	cin>>target_num;
	vector<pair<int,int> > target_site;
	for(int i=0;i<target_num;i++)
	{
		int target_x,target_y;
		cin>>target_y>>target_x;
		target_site.push_back(make_pair(target_x,target_y));
	}
	
	vector<int> v(col,0);
	vector<vector<int> > elevation(row,v);
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			cin>>elevation[i][j];
		}
	}
	
	FILE* fp=freopen("output.txt", "w", stdout);
	
	if(search_type=="BFS")
	{
	for(int i=0;i<target_num;i++)
		{
			map<pair<int,int>, pair<int,int> > parent_child;
			pair<int,int> src=make_pair(start_x,start_y);
			if(parent_child.find(target_site[i])==parent_child.end())
			BFS_Search_parent_child(src,max_diff,elevation,row,col,target_site[i],parent_child);
			print_parent_child(parent_child,src,target_site[i]);
			
		}
	}
	else if(search_type=="A*")
	{
		
		for(int i=0;i<target_num;i++)
		{
			map<pair<int,int>, pair<int,int> > parent_child;
			pair<int,int> src=make_pair(start_x,start_y);
			Astar_search_parent_child(src,max_diff,elevation,row,col,target_site[i],parent_child);
			print_parent_child(parent_child,src,target_site[i]);
			
		}
	}
	else if(search_type=="UCS")
	{
		for(int i=0;i<target_num;i++)
		{
			map<pair<int,int>, pair<int,int> > parent_child;
			pair<int,int> src=make_pair(start_x,start_y);
			if(parent_child.find(target_site[i])==parent_child.end())
			UCS_Search_parent_child(src,max_diff,elevation,row,col,target_site[i],parent_child);
			print_parent_child(parent_child,src,target_site[i]);
		}
	}
	return 0;
}
