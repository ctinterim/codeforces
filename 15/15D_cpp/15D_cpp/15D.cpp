#include <iostream>

#define MAX_LEAF_LENGTH 1024
#define MAX_PARTIAL_MIN_MATRIX_LENGTH (MAX_LEAF_LENGTH * 2)
#define MAX_N 1000

typedef struct _PMNode {
	int val = 2000000000;
	int lowerend = -1;
	int upperend = -1;
} PMNode;

PMNode pmRCTree1D[MAX_N][MAX_PARTIAL_MIN_MATRIX_LENGTH];  // (24MB) DS for partial min 1D (col)
int min1DMatrix[MAX_N][MAX_N] = { 2000000000 };  //  (4MB) minimum value in 1*b window starting from left

PMNode pmCRTree2D[MAX_N][MAX_PARTIAL_MIN_MATRIX_LENGTH];  // (24MB) DS for partial min 2D where column length is always b (row*col)
int min2DMatrix[MAX_N][MAX_N] = { 2000000000 };  //  (4MB) minimum value in a*b window starting from upper left

int bSum[MAX_N][MAX_N] = { 2000000000 };         //  (4MB) 1Xb sum starting at left
int abSum[MAX_N][MAX_N] = { 2000000000 };        //  (4MB) aXb sum starting at upper left

int nearestPowerOf2(int val) {
	int ret = 1;
	while (ret < val) {
		ret *= 2;
	}
	return ret;
}

void buildPartialMinTree(PMNode* tree, const int leaflength) {
	int start = leaflength;
	int end = leaflength * 2;

	while (start > 0) {
		for (int i = start; i < end; i += 2) {
			PMNode& lower = tree[i];
			PMNode& upper = tree[i + 1];
			PMNode& parent = tree[i / 2];
			
			parent.val = (lower.val < upper.val) ? lower.val : upper.val;
			parent.lowerend = lower.lowerend;
			parent.upperend = upper.upperend;
		}

		end = start;
		start = start / 2;
	}
}

int partialMin(PMNode* tree, const int leaflength, int startingposition, int windowsize) {
	int minval = tree[startingposition].val;
	int start = leaflength + startingposition; // must add leaflength!!!
	// inclusive end
	int iend = startingposition + windowsize - 1;
	int curpos = start;
	bool goup = true;

	while (curpos != iend) {
		// Have not found parent whose upperend contains iend yet
		if (goup) {
			int parentpos = curpos / 2;
			int rightchildpos = (parentpos * 2) + 1;
			PMNode& parent = tree[parentpos];
			PMNode& rightchild = tree[rightchildpos];
			
			if (curpos & 1) { //If current possition is right side, just go up
				curpos = parentpos;
			}
			else {
				if (iend >= parent.upperend) { //iend is over parent's upperend. go up
					// parent's right child = (parentpos*2) + 1
					minval = (minval < rightchild.val) ? minval : rightchild.val;
					if (iend == parent.upperend) {
						break;
					}
					else {
						curpos = parentpos;
					}
				}
				else { // iend < parent.upperend
					goup = false;
					curpos = rightchildpos;
				}
			}
		}
		else { // Found a parent whose upperend is strictly higher than iend
			int leftchildpos = (curpos * 2);
			int rightchildpos = leftchildpos + 1;
			PMNode& leftchild = tree[leftchildpos];
			PMNode& rightchild = tree[rightchildpos];

			if (iend >= leftchild.upperend) {
				minval = (minval < leftchild.val) ? minval : leftchild.val;
				if (iend == leftchild.upperend) {
					break;
				}
				else {
					curpos = rightchildpos;
				}
			}
			else {
				curpos = leftchildpos;
			}
		}
	}
	// Last comparison
	minval = (minval < tree[iend].val) ? minval : tree[iend].val;

	return minval;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int n, m, a, b; //n,a = row, m,b = col
	int treeend_col, treeend_row;

	std::cin >> n >> m >> a >> b;

	treeend_row = nearestPowerOf2(n);
	treeend_col = nearestPowerOf2(m);

	for (int row = 0; row < n; ++row) {
		for (int col = 0; col < m; ++col) {
			std::cin >> pmRCTree1D[row][treeend_col + col].val;
			pmRCTree1D[row][treeend_col + col].lowerend = treeend_col + col;
			pmRCTree1D[row][treeend_col + col].upperend = treeend_col + col;
		}
	}
	for (int row = 0; row < n; ++row) {
		buildPartialMinTree(pmRCTree1D[row], treeend_col);
	}
	for (int row = 0; row < n; ++row) {
		for (int col = 0; col <= m-b; ++col) {
			min1DMatrix[row][col] = partialMin(pmRCTree1D[row], treeend_col, col, b);
		}
	}

	//Note that we are swapping row and column at this point
	for (int col = 0; col <= m-b; ++col) {
		for (int row = 0; row < n; ++row) {
			pmCRTree2D[col][treeend_row + row].val = min1DMatrix[row][col];
			pmCRTree2D[col][treeend_row + row].lowerend = treeend_row + row;
			pmCRTree2D[col][treeend_row + row].upperend = treeend_row + row;
		}
	}
	for (int col = 0; col <= m-b; ++col) {
		buildPartialMinTree(pmCRTree2D[col], treeend_row);
	}
	for (int col = 0; col <= m-b; ++col) {
		for (int row = 0; row <= n-a; ++row) {
			min2DMatrix[row][col] = partialMin(pmCRTree2D[col], treeend_row, row, a);
		}
	}

	return 0;
}