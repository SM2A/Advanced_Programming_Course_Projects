#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){

	int m,n;

	vector<int> row;
	vector<int> column;

	cin>>m>>n;

	vector<vector<int> > zamin(n);

	for(int i=0;i<n;i++){
		for(int j =0;j<m;j++){
			int x=0;
			cin>>x;
			zamin[i].push_back(x);
		}
	}

	for(int i=0;i<m;i++){
		int sum = 0;
		for(int j = 0;j<n;j++){
			sum+=zamin[i][j];
		}
		row.push_back(sum);
	}
	
	for(int i = 0 ; i<n;i++){
		int sum = 0;
		for(int j  =0 ;j<m;j++){
			sum+=zamin[i][j];
		}
		column.push_back(sum);
	}

	for(int i = 0;i<column.size();i++){
		row.push_back(column[i]);
	}

	sort(row.begin(),row.end());

	int print = row.size();

	int output = row[print-1]+row[print-2]+row[print-3]+row[print-4];

	cout<<output<<'\n';

	return 0 ;

}
