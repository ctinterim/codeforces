#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <utility>

typedef struct _GNode{
	int val;
	int idx;
	struct _GNode* parent;
	struct _GNode* left;
	struct _GNode* right;
	char mode;
} GNode;

void printIntArray(const int* array, const int array_length) {
	for (int i = 0; i < array_length; ++i) {
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

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
		tree[i].idx = i; // only leaf
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
				li = base_idx - lastlvsize + ((i-1)*2) + 1;
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
			std::cout << tree[base_idx - curlvsize + j].val << "(" << tree[base_idx - curlvsize + j].mode << ") ";
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

void printStdPairVector(std::vector<std::pair<int, int>>& vec) {
	for(int i=0; i< vec.size(); ++i){
		std::cout << "( " << vec[i].first << ", " << vec[i].second << ")";
	}
	std::cout << std::endl;
}

void computeSameHeight(const int* chain, const int chain_length, const int* L_hi, int*& L_numsame){
	std::vector<std::pair<int,int>> carr;
	for(int i=0; i<chain_length; ++i){
		carr.push_back(std::pair<int,int>(chain[i], i));
	}

	std::sort(carr.begin(), carr.end(), comparePair);
	// printStdPairVector(carr);

	for(int i=0; i<chain_length; ++i){
		L_numsame[i] = 0;
	}

	char* lns_visited = new char[chain_length];
	memset(lns_visited, 0, sizeof(char)*chain_length);
	lns_visited[0] = 1;
	
	int maxh = carr[0].first;
	for(int i=1; i<carr.size(); ){
		int start = i;
		int end = i;
		int numsame = 0;

		if (lns_visited[carr[i].second]) {
			++i;
			continue;
		}

		while((i < carr.size()-1) && (carr[i].first == carr[i+1].first)){
			++i;
		}
		end = i;

		// at this point [start,end] are same numbers

		numsame = end - start;
		if(numsame > 0){
			if(carr[start].first == maxh){ // Simple case
				for(int j = 0; j <= numsame-1; ++j){
					L_numsame[carr[start+j].second] = numsame-1-j;
					lns_visited[carr[start + j].second] = 1;
				}
			}
			else{ // Complicated case
				for (int s = 0; s <= numsame;) {
					int si = carr[start + s].second;
					L_numsame[si] = 0;
					lns_visited[si] = 1;
					for (int n = 1; s + n <= numsame; ++n) {
						int s_p_ni = carr[start + s + n].second;
						if (s_p_ni < L_hi[si]) {
							L_numsame[si]++;
						}
						else {
							break;
						}
					}

					int ns = s + 1;
					for (int n = 1; s + n <= numsame; ++n) {
						int s_p_ni = carr[start + s + n].second;
						if (s_p_ni < L_hi[si]) {
							ns++;
							L_numsame[s_p_ni] = L_numsame[si] - n;
							lns_visited[s_p_ni] = 1;
						}
						else {
							break;
						}
					}

					s = ns;
				}
			}
			i = end + 1;
		}
		else{
			L_numsame[carr[i].second] = 0;
			lns_visited[carr[i].second] = 1;
			++i;
		}
	}

	/*
	for(int i=0; i<chain_length; ++i){
		std::cout << L_numsame[i] << " "; 
	}
	std::cout << std::endl;
	*/
	
}

int traverse_LtoR(const GNode* tree, int start) {
	const GNode* curNode = &(tree[start]);
	int start_val = tree[start].val;
	const GNode* curParent = curNode->parent;

	// Go up
	while (1) {
		// If curNode is right child, just go up
		if (curNode->mode == 'R') {
			curNode = curParent;
			curParent = curNode->parent;
			continue;
		}
		else {
			if ((curParent->val > start_val) && (curParent->right != NULL) && (curParent->right->val > start_val)) {
				curNode = curParent->right;
				break;
			}
			else {
				curNode = curParent;
				curParent = curNode->parent;
			}
		}
	}

	while (1) {
		if ((curNode->left) == NULL && (curNode->right == NULL)) {
			break;
		}

		if ((curNode->left != NULL) && (curNode->left->val > start_val)) {
			curNode = curNode->left;
		}
		else {
			curNode = curNode->right;
		}
	}

	return curNode->idx;
}

int traverse_RtoL(const GNode* tree, int start) {
	const GNode* curNode = &(tree[start]);
	int start_val = tree[start].val;
	const GNode* curParent = curNode->parent;

	// Go up
	while (1) {
		// If curNode is left child, just go up
		if (curNode->mode == 'L') {
			curNode = curParent;
			curParent = curNode->parent;
			continue;
		}
		else {
			if ((curParent->val > start_val) && (curParent->left != NULL) && (curParent->left->val > start_val)) {
				curNode = curParent->left;
				break;
			}
			else {
				curNode = curParent;
				curParent = curNode->parent;
			}
		}
	}

	while (1) {
		if ((curNode->left) == NULL && (curNode->right == NULL)) {
			break;
		}

		if ((curNode->right != NULL) && (curNode->right->val > start_val)) {
			curNode = curNode->right;
		}
		else {
			curNode = curNode->left;
		}
	}

	return curNode->idx;
}

void compute_hi(const GNode* tree_LtoR, const GNode* tree_RtoL, const int* chain, const int chain_length, const int maxh, int*& L_hi, int*& R_hi) {
	for (int i = 1; i < chain_length -1; ++i) {
		if (chain[i] == maxh) {
			L_hi[i] = chain_length - 1;
		}
		else {
			L_hi[i] = traverse_LtoR(tree_LtoR, i-1) + 1;
		}
	}

	for (int i = chain_length - 2; i > 0; --i) {
		if (chain[i] == maxh) {
			R_hi[i] = 0;
		}
		else {
			R_hi[i] = traverse_RtoL(tree_RtoL, i);
		}
	}
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
	GNode* tree_LtoR = NULL;
	GNode* tree_RtoL = NULL;
	int tree_size_LtoR = 0;
	int tree_size_RtoL = 0;
	int* L = NULL;
	int* L_hi = NULL;
	int* L_numsame = NULL;
	int* R = NULL;
	int* R_hi = NULL;


	std::cin >> n;

	hill = new int[n];
	chain = new int[n + 1];
	chain_length = n + 1;

	L = new int[chain_length]();
	L_hi = new int[chain_length]();
	L_numsame = new int[chain_length]();
	R = new int[chain_length]();
	R_hi = new int[chain_length]();

	for (int i = 0; i < n; ++i) {
		std::cin >> hill[i];
	}

	maxh = hill[0];
	maxhi = 0;
	allsame = true;

	/* stupid...
	for (int i = 1; i < n; ++i) {
		if (hill[i] > maxh) {
			maxh = hill[i];
			maxhi = i;
		}
		if (hill[i] != maxh) {
			allsame = false;
		}
	}
	*/

	for (int i = 1; i < n; ++i) {
		if (hill[i] > maxh) {
			maxh = hill[i];
			maxhi = i;
		}
		if (hill[i] != hill[0]) {
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

	makeTree(&chain[1], chain_length-1, tree_LtoR, tree_size_LtoR);
	//printTree(tree_LtoR, tree_size_LtoR);

	makeTree(&chain[0], chain_length - 1, tree_RtoL, tree_size_RtoL);
	//printTree(tree_RtoL, tree_size_RtoL);

	compute_hi(tree_LtoR, tree_RtoL, chain, chain_length, maxh, L_hi, R_hi);

	//printf("L_hi\n");
	//printIntArray(L_hi, chain_length);
	//printf("R_hi\n");
	//printIntArray(R_hi, chain_length);

	computeSameHeight(chain, chain_length, L_hi, L_numsame);
	//printf("L_numsame\n");
	//printIntArray(L_numsame, chain_length);

	for (int i = 1; i < chain_length - 2; ++i) {
		L[i] = 1 + L_numsame[i] + 1;

		if ((L_numsame[i] > 0) && (chain[i] == chain[i + 1])) {
			L[i] -= 1;
		}
		if ((i + 1 == L_hi[i]) && (chain[i] < chain[L_hi[i]])) {
			L[i] -= 1;
		}
	}
	L[chain_length - 2] = 1;

	
	for (int i = chain_length - 2; i > 0; --i) {
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

	//printf("L\n");
	//printIntArray(L, chain_length);
	//printf("R\n");
	//printIntArray(R, chain_length);

	long long sum = 0;

	for (int i = 0; i < chain_length; ++i) {
		sum += L[i];
		sum += R[i];
	}

	std::cout << sum << std::endl;

	return 0;
}