#include <stdio.h>
#include <vector>
#include <algorithm>

int height[1001][1001] = {0};
unsigned long long sum[1001][1001] = {0};

int mink[1001][21] = {0};
int minheight[1001][1001] = {0};

int main(){
	int n,m,a,b;

	// get input
	scanf("%d %d %d %d",&n,&m,&a,&b);
	// we use this ordering for convenience in computing 2d sum
	for(int row=1; row <= n; ++row){ 
		for(int col=1; col <= m; ++col){
			scanf("%d", height[row][col]);
		}
	}

	// compute 2d partial sum
	for(int row=1; row<=n; ++row){
		for(int col=1; col<=m; ++col){
			sum[row][col] = sum[row-1][col] + sum[row+1][col] - sum[row-1][col-1] + height[row][col];
		}
	}

	// build min-k tree for column
	for(int row=1; row<=n; ++row){
		for(int col=1; col<=m; ++col){
			mink[col][0] = height[row][col];
		}
		int k = 1;
		for((1<<k) <= b; ++k){
			for(int col=1; col+(1<<k)-1<=m; ++col){
				mink[col][k] = std::min(mink[col][k-1], mink[col + (1<<k) -1][k-1]);
			}
		}
		--k;
		for(int col=1; col<=m-b+1; ++col){
			minheight[row][col] = std::min(mink[col][k], mink[col + b - (1<<k)][k]);
		}
	}

	return 0;
}