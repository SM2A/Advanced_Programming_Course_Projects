#include <iostream>
#include<vector>

using namespace std;

int main(){

	vector<int> input;
	int x=0;
	int counter = 0;

	while(cin>>x){
		input.push_back(x);
		counter++;
	}

	int temp_count=0;
	int times = 0;

	for(int i=0;i<counter;i++){
		for (int j = 0; j < counter; j++){
			if(input[j]==input[i]) temp_count++;
		}
		if((temp_count%2)==1) {
			cout<<input[i]<<'\n';
			times++;
		}
		temp_count=0;
	}

	if(times==0) cout<<"0\n";

	return 0;
}