/*
* @Author: deepanshu
* @Date:   2016-10-03 22:08:16
* @Modified by: Amitkumar05
* @Last Modified by:   Deepanshu Sapra
* @Last Modified time: 2016-10-04 14:21:18
*/
#include <bits/stdc++.h>
using namespace std;
#define maxi 1000
#define mod 1000000000
typedef long long ll;
typedef pair<double,double> dd;
int sz, m = 20;
double Q,tmpMax,alpha = 1.0,beta = 2.0, lambda = 0.3;
double tou[maxi][maxi],delta[maxi][maxi],dis[maxi][maxi];
std::vector<double> FindTour(int src)
{
	int visited[maxi];
	memset(visited,0,sizeof visited);
	std::vector<double> tour;
	tour.push_back(src);
	for (int iter = 1; iter < sz; ++iter)
	{
		visited[src] = 1;
		std::vector<double> probability;
		std::vector<int> index;
		for (int i = 0; i < sz; ++i)
		{
			if(visited[i] == 0)
			{
				double t1 = pow(tou[src][i],alpha) != 0  ? pow(tou[src][i],alpha) : 1;
				double val = t1*pow(tmpMax/dis[src][i],beta);
				probability.push_back(val);
				index.push_back(i);
			}
		}
		int k = probability.size();
		for (int i = 1; i < k; ++i)
			probability[i] += probability[i-1];
		for (int i = 0; i < k; ++i)
			probability[i] = probability[i]/probability[k - 1];
		ll random = rand()%mod;
		double prob = double(random)/(double)mod;
		int indi = lower_bound(probability.begin(), probability.end(),prob) - probability.begin();
		src = index[indi]; 
		tour.push_back(src);
	}	 
	return tour;
}

double CalculateCost(vector<double> path)
{
	double tourCost = 0;
	int k = path.size();
	for(int i = 1; i < k; i++)
	{
		int u = path[i-1];
		int v = path[i];
		tourCost += dis[u][v];
	}
	return tourCost;
}

void UpdateDelta(vector<double> path)
{
	double tourCost = CalculateCost(path);
	int k = path.size();
	for(int i = 1; i < k; i++)
	{
		int u = path[i-1];
		int v = path[i];
		delta[u][v] += Q/tourCost;
	}
}

void UpdateTou()
{
	for(int i = 0; i < sz; i++)
	{
		for(int j = 0; j < sz; j++)
		{
			tou[i][j] = (1 - lambda)*tou[i][j] + delta[i][j];
		}
	}
}

int main()
{
	clock_t beg = clock();
	std::ios::sync_with_stdio(false);
	srand(time(NULL));
	string type;
	cin>>type;
	cin>>sz;
	std::vector<dd> cordi;
	double x,y;
	for (int i = 0; i < sz; ++i)
	{
		cin>>x>>y;
		dd tmp;
		tmp.first = x;
		tmp.second = y;
		cordi.push_back(tmp);
	}
	Q = 0.0;
	tmpMax = 0.0;
	for (int i = 0; i < sz; ++i)
	{
		for (int j = 0; j < sz; ++j)
		{
			cin>>dis[i][j];
			tmpMax = max(tmpMax,dis[i][j]);
		}
	}
	Q = tmpMax*(sz - 1);
	int count = 5000;
	double mini = (double)mod;
	memset(tou,0,sizeof tou);
	for (int iter = 0; iter < count; iter++)
	{
		memset(delta,0,sizeof delta);
		for (int i = 0; i < m; i++)
		{
			int src = rand()%sz;
			vector<double >path = FindTour(src);
			UpdateDelta(path);
			mini = min(CalculateCost(path),mini);
		}
		UpdateTou();
	}
	cout<<mini<<endl;
	clock_t end = clock();
	double time = (double)(end -beg)/(double)(CLOCKS_PER_SEC);
	fprintf(stderr, "%.10lf\n",time);
    return 0;
}