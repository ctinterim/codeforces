#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <utility>

typedef struct _GNode{
	int val;
	struct _GNode* parent;
	struct _GNode* left;
	struct _GNode* right;
	char mode;
} GNode;

void makeTree(const int* chain, const int chain_length, GNode*& tree_output, int& tree_size_output){
	int lastlvsize = 0;
	int base_idx = 0;
	int curi, li, ri = 0;

	int curlvsize = chain_length;
	int totalsize = curlvsize;

	while(curlvsize > 1){
		curlvsize = (curlvsize & 1) ? (curlvsize / 2) + 1 : (curlvsize / 2);
		totalsize += curlvsize;
	}

	GNode* tree = new GNode[totalsize];
	memset(tree, 0, sizeof(GNode)*totalsize);

	for(int i=0; i<chain_length; ++i){
		tree[i].val = chain[i];
	}

	lastlvsize = chain_length;
	base_idx = lastlvsize;
	while(lastlvsize > 1){
		if(lastlvsize & 1){
			curlvsize = (lastlvsize / 2) + 1;

			curi = base_idx;
			li = (base_idx - lastlvsize);
			tree[curi].left = &(tree[li]);
			tree[curi].left->parent = &(tree[curi]);
			tree[curi].left->mode = 'L';
			tree[curi].val = tree[curi].left->val;

			//std::cout << curi << " " << li << " " << -1 << std::endl;

			for(int i=1; i<curlvsize; ++i){
				li = base_idx - lastlvsize + (i*2) + 1;
				ri = li + 1;
				curi = base_idx+i;

				//std::cout << curi << " " << li << " " << ri << std::endl;

				tree[curi].left = &(tree[li]);
				tree[curi].left->parent = &(tree[curi]);
				tree[curi].left->mode = 'L';

				tree[curi].right = &(tree[ri]);
				tree[curi].right->parent = &(tree[curi]);
				tree[curi].right->mode = 'R';

				tree[curi].val = ( tree[curi].left->val > tree[curi].right->val ) ? tree[curi].left->val : tree[curi].right->val;
			}
		}
		else{
			curlvsize = (lastlvsize / 2);

			for(int i=0; i<curlvsize; ++i){
				li = base_idx - lastlvsize + (i*2);
				ri = li + 1;
				curi = base_idx+i;

				//std::cout << curi << " " << li << " " << ri << std::endl;

				tree[curi].left = &(tree[li]);
				tree[curi].left->parent = &(tree[curi]);
				tree[curi].left->mode = 'L';

				tree[curi].right = &(tree[ri]);
				tree[curi].right->parent = &(tree[curi]);
				tree[curi].right->mode = 'R';

				tree[curi].val = ( tree[curi].left->val > tree[curi].right->val ) ? tree[curi].left->val : tree[curi].right->val;
			}
		}
		
		lastlvsize = curlvsize;
		base_idx += curlvsize;
	}

	tree_output = tree;
	tree_size_output = totalsize;
}


void printTree(GNode* tree, int tree_size){
	int base_idx = tree_size;
	int curlvsize = 1;
	int nextlvsize;

	while(base_idx > 0){
		for(int j = 0; j < curlvsize; ++j){
			std::cout << tree[base_idx - curlvsize + j].val << " ";
		}
		std::cout << std::endl;

		if(tree[base_idx - curlvsize].right == NULL){
			nextlvsize = (curlvsize*2)-1;
		}
		else{
			nextlvsize = (curlvsize*2);
		}

		base_idx -= curlvsize;
		curlvsize = nextlvsize;
	}
}

bool comparePair(const std::pair<int,int>& a, const std::pair<int,int>& b){
	if(a.first == b.first){
		return a.second < b.second;
	}
	return a.first > b.first;
}

void computeSameHeight(const int* chain, const int chain_length, int*& L_numsame){
	std::vector<std::pair<int,int>> carr;
	for(int i=0; i<chain_length; ++i){
		carr.push_back(std::pair<int,int>(chain[i], i));
	}

	std::sort(carr.begin(), carr.end(), comparePair);

	/*
	for(int i=0; i<carr.size(); ++i){
		std::cout << "( " << carr[i].first << ", " << carr[i].second << ")"; 
	}
	std::cout << std::endl;
	*/

	L_numsame = new int[chain_length];
	for(int i=0; i<chain_length; ++i){
		L_numsame[i] = -1;
	}
	L_numsame[0] = 0;
	L_numsame[chain_length-1] = 0;

	int maxh = carr[0].first;
	for(int i=1; i<carr.size(); ){
		int start = i;
		int end = i;
		int numsame = 0;

		while((i < carr.size()-1) && (carr[i].first == carr[i+1].first)){
			++i;
		}
		end = i;

		numsame = end - start;
		if(numsame > 0){
			if(carr[start].first == maxh){
				for(int j = 0; j <= numsame-1; ++j){
					std::cout << carr[start+j].second << " ";
					L_numsame[carr[start+j].second] = numsame-1-j;
				}
				std::cout << std::endl;
			}
			else{
				for(int j = 0; j <= numsame; ++j){
					std::cout << carr[start+j].second << " ";
					L_numsame[carr[start+j].second] = numsame-j;
				}
				std::cout << std::endl;
			}
			i = end;
		}
		else{
			L_numsame[carr[i].second] = 0;
			++i;
		}
		
	}

	/*
	for(int i=0; i<chain_length; ++i){
		std::cout << L_numsame[i] << " "; 
	}
	*/

	std::cout << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	
	int n = 0;
	unsigned long long lln = 0;
	int* hill = NULL;
	int* chain = NULL;
	int chain_length = 0;
	int maxh = 0;
	int maxhi = 0;
	bool allsame = false;
	GNode* tree = NULL;
	int tree_size = 0;
	int* L = NULL;
	int* L_hi = NULL;
	int* L_numsame = NULL;
	int* R = NULL;
	int* R_hi = NULL;


	std::cin >> n;

	hill = new int[n];
	chain = new int[n + 1];
	chain_length = n + 1;

	for (int i = 0; i < n; ++i) {
		std::cin >> hill[i];
	}

	maxh = hill[0];
	maxhi = 0;
	allsame = true;

	for (int i = 1; i < n; ++i) {
		if (hill[i] > maxh) {
			maxh = hill[i];
			maxhi = i;
		}
		if (hill[i] != maxh) {
			allsame = false;
		}
	}

	if (allsame) {
		lln = n;
		std::cout << (lln*(lln - 1)) / 2 << std::endl;
		return 0;
	}

	chain[0] = maxh;
	for (int i = 1; i < chain_length - maxhi; ++i) {
		chain[i] = hill[maxhi + i];
	}
	for (int i = 0; i <= maxhi; ++i) {
		chain[chain_length - maxhi + i - 1] = hill[i];
	}

	/*
	for (int i = 0; i < chain_length; ++i) {
		std::cout << chain[i] << " ";
	}
	std::cout << std::endl;
	*/

	makeTree(chain, chain_length, tree, tree_size);
	//printTree(tree, tree_size);

	computeSameHeight(chain, chain_length, L_numsame);

	L = new int[chain_length];
	R = new int[chain_length];
	
	for (int i = 1; i < chain_length - 1; ++i) {
		if (i == chain_length - 2) {
			L[i] = 1;
			L_hi[i] = chain_length - 1;
			L_numsame[i] = 0;
			continue;
		}

		if (L_hi[i] == 0) {
			same.clear();
			higher = chain_length - 1;
			for (int j = i + 1; j < chain_length; ++j) {
				if ((j != chain_length - 1) && (chain[i] == chain[j])) {
					same.push_back(j);
				}
				else if (chain[i] < chain[j]) {
					higher = j;
					break;
				}
			}
			L_hi[i] = higher;
			L_numsame[i] = same.size();
			L_numsame_s = L_numsame[i] - 1;

			for (int vi = 0; vi < same.size(); ++vi) {
				int s = same[vi];
				L_hi[s] = higher;
				L_numsame[s] = L_numsame_s;
				L_numsame_s -= 1;
			}
		}

		L[i] = 1 + L_numsame[i] + 1;

		if ((L_numsame[i] > 0) && (chain[i] == chain[i + 1])) {
			L[i] -= 1;
		}
		if ((i + 1 == L_hi[i]) && (chain[i] < chain[L_hi[i]])) {
			L[i] -= 1;
		}
	}

	for (int i = chain_length - 2; i > 0; --i) {
		if (R_hi[i] == chain_length - 1) {
			same.clear();
			higher = 0;
			for (int j = i - 1; j >-1; --j) {
				if ((j != 0) && (chain[i] == chain[j])) {
					same.push_back(j);
				}
				else if (chain[i] < chain[j]) {
					higher = j;
					break;
				}
			}

			R_hi[i] = higher;
			for (int vi = 0; vi < same.size(); ++vi) {
				int s = same[vi];
				R_hi[s] = higher;
			}
		}

		R[i] = 1;

		if (chain[i] == maxh) {
			R[i] = 0;
		}
		else if ((R_hi[i] == 0) && (L_hi[i] == chain_length - 1)) {
			R[i] = 0;
		}
		else if ((i > 1) && (R_hi[i] == i - 1)) {
			R[i] = 0;
		}
	}

	long long sum = 0;

	for (int i = 0; i < chain_length; ++i) {
		sum += L[i];
		sum += R[i];
	}

	std::cout << sum << std::endl;
	*/

	return 0;
}