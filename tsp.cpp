/*
* @Author: deepanshu
* @Date:   2016-10-03 22:08:16
* @Last Modified by:   deepanshu
* @Last Modified time: 2016-10-03 22:17:45
*/
#include <bits/stdc++.h>
using namespace std;
#define maxi 1000
double tou[maxi][maxi],eta[maxi][maxi],dis[maxi][maxi];
typedef long long ll;
typedef pair<double,double> dd;
int main()
{
	std::ios::sync_with_stdio(false);
	string type;
	cin>>type;
	int sz;
	cin>>sz;
	std::vector<dd> cordi;
	double x,y;
	for (int i = 0; i < n; ++i)
	{
		cin>>x>>y;
		dd tmp;
		tmp.first = x;
		tmp.second = y;
		cordi.push_back(tmp);
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin>>dis[i][j];
		}
	}

	int count = 1000;
	for (int iter = 0; iter < count; iter++)
	{
		for (int i = 0; i < m; i++)
		{
			findpath();
			update_phenomon();
			calculate_cost();

		}


	}
    return 0;
}