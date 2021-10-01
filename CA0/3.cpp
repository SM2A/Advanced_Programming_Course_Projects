#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){

	long m,n;
	vector<long> max;
	vector<long> temp;

	cin>>m>>n;

	vector<vector<long> > zamin(n);

	for(long i=0;i<n;i++){
		for(long j =0;j<m;j++){
			long x=0;
			cin>>x;
			zamin[i].push_back(x);
		}
	}

	vector<long> row;
	vector<long> column;

	for(int i = 0 ; i < n ; i++){
		int sum = 0;
		for(int j = 0 ; j < m ; j++){
			sum+=zamin[i][j];
		}
		row.push_back(sum);
	}

	for(int i = 0 ; i < n ; i++){
		int sum = 0;
		for(int j = 0 ; j < m ; j++){
			sum+=zamin[j][i];
		}
		column.push_back(sum);
	}

	sort(row.begin(),row.end());
	sort(column.begin(),column.end());

	int row_size = row.size();
	int column_size = column.size();

	int row_out = row[row_size-1]+row[row_size-2]+row[row_size-3]+row[row_size-4];
	int column_out = column[column_size-1]+column[column_size-2]+column[column_size-3]+column[column_size-4];

	max.push_back(row_out);
	max.push_back(column_out);

	row.clear();
	column.clear();

	for(int i = 0 ; i < n ; i++){
		int sum = 0;
		for(int j = 0 ; j < m ; j++){
			sum+=zamin[i][j];
		}
		row.push_back(sum);
	}

	for(long i = 0 ; i<n;i++){
		long sum = 0;
		for(long j  =0 ;j<m;j++){
			sum+=zamin[j][i];
		}
		for(int k = 0 ; k<m;k++){
			for(int l = 0 ; l < m ; l++){
				for(int p =0 ;p<m;p++){
					sum-=zamin[k][i];
					sum-=zamin[l][i];
					sum-=zamin[p][i];
					temp.push_back(sum);
					sum+=zamin[k][i];
					sum+=zamin[l][i];
					sum+=zamin[p][i];
				}
			}
		}
	}
	sort(temp.begin(),temp.end());
	sort(row.begin(),row.end());

	row_size = row.size();
	row_out = row[row_size-1]+row[row_size-2]+row[row_size-3];
	max.push_back((row_out+(temp[(temp.size()-1)])));
	row.clear();
	temp.clear();

	/*for(int i = 0 ; i < n ; i++){
		int sum = 0;
		for(int j = 0 ; j < m ; j++){
			sum+=zamin[j][i];
		}
		column.push_back(sum);
	}

	for(long i = 0 ; i<n;i++){
		long sum = 0;
		for(long j  =0 ;j<m;j++){
			sum+=zamin[i][j];
		}
		for(int k = 0 ; k<m;k++){
			sum-=zamin[i][k];
			temp.push_back(sum);
			sum+=zamin[k][i];
		}
	}
	sort(temp.begin(),temp.end());
	column.push_back(temp[(temp.size())-1]);
	temp.clear();

	sort(column.begin(),column.end());

	column_size = column.size();
	column_out = column[column_size-1]+column[column_size-2]+column[column_size-3]+column[column_size-4];
	max.push_back(column_out);
	column.clear();*/

	sort(max.begin(),max.end());
	cout<<max[(max.size())-1]<<endl;

	return 0;
}