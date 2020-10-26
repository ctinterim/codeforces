#include <stdio.h>
#include <vector>
#include <algorithm>

#define MAX_LEAF_LENGTH 1024
#define MAX_PARTIAL_MIN_MATRIX_LENGTH (MAX_LEAF_LENGTH * 2)
#define MAX_N 1000

typedef struct _PMNode {
	int val;
	int lowerend;
	int upperend;
} PMNode;

typedef struct _CNode {
	long long cost;
	int row;
	int col;
} CNode;

int inputMatrix[MAX_N][MAX_N];                            //  (4MB)
PMNode pmRCTree1D[MAX_N][MAX_PARTIAL_MIN_MATRIX_LENGTH];  // (24MB) DS for partial min 1D (col)
int min1DMatrix[MAX_N][MAX_N];                            //  (4MB) minimum value in 1*b window starting from left

PMNode pmCRTree2D[MAX_N][MAX_PARTIAL_MIN_MATRIX_LENGTH];  // (24MB) DS for partial min 2D where column length is always b (row*col)
int min2DMatrix[MAX_N][MAX_N];                            //  (4MB) minimum value in a*b window starting from upper left

long long bSum[MAX_N][MAX_N];                                   //  (4MB) 1Xb sum starting at left
long long abSum[MAX_N][MAX_N];                                  //  (4MB) aXb sum starting at upper left

char minMap[MAX_N][MAX_N] = { 0 };

CNode costList[MAX_N*MAX_N + 100];
int costListLength;
CNode resultList[MAX_N*MAX_N + 100];
int resultListLength;

bool compareCNode(const CNode& a, const CNode& b) {
	if (a.cost == b.cost) {
		if (a.row == b.row) {
			return a.col < b.col;
		}
		return a.row < b.row;
	}
	return a.cost < b.cost;
}

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

	while (start > 1) {
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
	int start = leaflength + startingposition;    // must add leaflength!!!
	int iend = start + windowsize - 1; // inclusive end
	int minval = tree[start].val;
	int curpos = start;
	bool goup = true;

	if (windowsize <= 10) {
		for (int i = start + 1; i <= iend; ++i) {
			if (tree[i].val < minval) {
				minval = tree[i].val;
			}
		}
		return minval;
	}

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

void calculateBSum(const int n, const int m, const int b) {
	for (int row = 0; row < n; ++row) {
		bSum[row][0] = 0;
		for (int col = 0; col < b; ++col) {
			bSum[row][0] += inputMatrix[row][col];
		}
		for (int col = 1; col <= m - b; ++col) {
			bSum[row][col] = bSum[row][col - 1] - inputMatrix[row][col - 1] + inputMatrix[row][col + b - 1];
		}
	}
}

void calculateABSum(const int n, const int m, const int a, const int b) {
	for (int col = 0; col <= m - b; ++col) {
		abSum[0][col] = 0;
		for (int row = 0; row < a; ++row) {
			abSum[0][col] += bSum[row][col];
		}
		for (int row = 1; row <= n - a; ++row) {
			abSum[row][col] = abSum[row - 1][col] - bSum[row - 1][col] + bSum[row + a - 1][col];
		}
	}
}

int main() {
	int n, m, a, b; //n,a = row, m,b = col
	int treeend_col, treeend_row;

	scanf_s("%d %d %d %d", &n, &m, &a, &b);

	treeend_row = nearestPowerOf2(n);
	treeend_col = nearestPowerOf2(m);

	for (int row = 0; row < n; ++row) {
		for (int col = 0; col < m; ++col) {
			scanf_s("%d", &inputMatrix[row][col]);
			pmRCTree1D[row][treeend_col + col].val = inputMatrix[row][col];
			pmRCTree1D[row][treeend_col + col].lowerend = treeend_col + col;
			pmRCTree1D[row][treeend_col + col].upperend = treeend_col + col;
		}
		for (int col = m; col < treeend_col; ++col) {
			pmRCTree1D[row][treeend_col + col].val = 2000000000;
			pmRCTree1D[row][treeend_col + col].lowerend = treeend_col + col;
			pmRCTree1D[row][treeend_col + col].upperend = treeend_col + col;
		}
	}

	for (int row = 0; row < n; ++row) {
		buildPartialMinTree(pmRCTree1D[row], treeend_col);
	}

	for (int row = 0; row < n; ++row) {
		for (int col = 0; col <= m - b; ++col) {
			min1DMatrix[row][col] = partialMin(pmRCTree1D[row], treeend_col, col, b);
		}
	}

	//Note that we are swapping row and column at this point
	for (int col = 0; col <= m - b; ++col) {
		for (int row = 0; row < n; ++row) {
			pmCRTree2D[col][treeend_row + row].val = min1DMatrix[row][col];
			pmCRTree2D[col][treeend_row + row].lowerend = treeend_row + row;
			pmCRTree2D[col][treeend_row + row].upperend = treeend_row + row;
		}
		for (int row = n; row < treeend_row; ++row) {
			pmCRTree2D[col][treeend_row + row].val = 2000000000;
			pmCRTree2D[col][treeend_row + row].lowerend = treeend_row + row;
			pmCRTree2D[col][treeend_row + row].upperend = treeend_row + row;
		}
	}
	for (int col = 0; col <= m - b; ++col) {
		buildPartialMinTree(pmCRTree2D[col], treeend_row);
	}
	for (int col = 0; col <= m - b; ++col) {
		for (int row = 0; row <= n - a; ++row) {
			min2DMatrix[row][col] = partialMin(pmCRTree2D[col], treeend_row, row, a);
		}
	}

	/*for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			printf("%d ", min2DMatrix[r][c]);
		}
		printf("\n");
	}
	printf("\n");*/

	calculateBSum(n, m, b);
	/*for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			printf("%d ", bSum[r][c]);
		}
		printf("\n");
	}
	printf("\n");*/

	calculateABSum(n, m, a, b);
	/*for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			printf("%d ", abSum[r][c]);
		}
		printf("\n");
	}
	printf("\n");*/

	costListLength = 0;
	for (int row = 0; row <= n - a; ++row) {
		for (int col = 0; col <= m - b; ++col) {
			int curidx = costListLength;
			long long curmin2d = min2DMatrix[row][col];
			costList[curidx].cost = abSum[row][col] - (curmin2d * a * b);
			costList[curidx].row = row;
			costList[curidx].col = col;

			++costListLength;
		}
	}

	std::sort(&costList[0], &costList[costListLength], compareCNode);

	resultListLength = 0;
	for (int i = 0; i < costListLength; ++i) {
		CNode& curr = costList[i];

		int u_lr = curr.row;
		int u_lc = curr.col;

		int u_rr = curr.row;
		int u_rc = curr.col + (b - 1);

		int d_lr = curr.row + (a - 1);
		int d_lc = curr.col;

		int d_rr = curr.row + (a - 1);
		int d_rc = curr.col + (b - 1);

		if ((minMap[u_lr][u_lc] + minMap[u_rr][u_rc] + minMap[d_lr][d_lc] + minMap[d_rr][d_rc]) == 0) {
			int ri = resultListLength;
			resultList[ri] = curr;
			for (int row = u_lr; row <= d_lr; ++row) {
				for (int col = u_lc; col <= u_rc; ++col) {
					minMap[row][col] = 1;
				}
			}
			++resultListLength;
		}
	}

	printf("%d\n", resultListLength);
	for (int i = 0; i < resultListLength; ++i) {
		printf("%d %d %lld\n", resultList[i].row + 1, resultList[i].col + 1, resultList[i].cost);
	}


	return 0;
}