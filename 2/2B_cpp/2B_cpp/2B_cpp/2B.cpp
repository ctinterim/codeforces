#include <iostream>

typedef struct _Path {
	unsigned int sum2;
	unsigned int sum5;
	char next;

	void Set(unsigned int _sum2, unsigned int _sum5, char _next) {
		sum2 = _sum2;
		sum5 = _sum5;
		next = _next;
	}
} Path;

unsigned char numDiv(unsigned int num, unsigned int div) {
	unsigned char res = 0;
	while (num > 1) {
		if (num % div > 0) { break; }
		res++;
		num /= div;
	}
	return res;
}

int main() {
	int n = 0;
	unsigned char** mat2 = NULL;
	unsigned char** mat5 = NULL;
	Path** path2 = NULL;
	Path** path5 = NULL;
	bool there_is_zero = false;
	int zr = 0;
	int zc = 0;

	std::ios_base::sync_with_stdio(false);

	std::cin >> n;

	mat2 = new unsigned char*[n];
	mat5 = new unsigned char*[n];
	path2 = new Path*[n];
	path5 = new Path*[n];
	for (int i = 0; i < n; ++i) {
		mat2[i] = new unsigned char[n];
		mat5[i] = new unsigned char[n];
		path2[i] = new Path[n];
		path5[i] = new Path[n];
	}

	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			unsigned int inum = 0;
			std::cin >> inum;
			if (inum == 0) {
				there_is_zero = true;
				zr = r;
				zc = c;
			}
			mat2[r][c] = numDiv(inum, 2);
			mat5[r][c] = numDiv(inum, 5);
		}
	}

	// RD is trivial
	path2[n - 1][n - 1].Set(mat2[n - 1][n - 1], mat5[n - 1][n - 1], '\0');
	path5[n - 1][n - 1].Set(mat2[n - 1][n - 1], mat5[n - 1][n - 1], '\0');

	// Last row is trivial
	for (int c = n - 2; c >= 0; c--) {
		Path& right = path2[n - 1][c + 1];
		path2[n - 1][c].Set(right.sum2 + mat2[n - 1][c], right.sum5 + mat5[n - 1][c], 'R');
		path5[n - 1][c].Set(right.sum2 + mat2[n - 1][c], right.sum5 + mat5[n - 1][c], 'R');
	}

	// Last column is trivial
	for (int r = n - 2; r >= 0; r--) {
		Path& down = path2[r + 1][n - 1];
		path2[r][n - 1].Set(down.sum2 + mat2[r][n - 1], down.sum5 + mat5[r][n - 1], 'D');
		path5[r][n - 1].Set(down.sum2 + mat2[r][n - 1], down.sum5 + mat5[r][n - 1], 'D');
	}

	// Non-trivial cases
	for (int r = n - 2; r >= 0; r--) {
		for (int c = n - 2; c >= 0; c--) {
			unsigned int cur2 = mat2[r][c];
			unsigned int cur5 = mat5[r][c];
			// For 2
			Path& right2 = path2[r][c + 1];
			Path& down2 = path2[r + 1][c];
			if (right2.sum2 < down2.sum2) {
				path2[r][c].Set(right2.sum2 + cur2, right2.sum5 + cur5, 'R');
			}
			else {
				path2[r][c].Set(down2.sum2 + cur2, down2.sum5 + cur5, 'D');
			}
			// For 5
			Path& right5 = path5[r][c + 1];
			Path& down5 = path5[r + 1][c];
			if (right5.sum5 < down5.sum5) {
				path5[r][c].Set(right5.sum2 + cur2, right5.sum5 + cur5, 'R');
			}
			else {
				path5[r][c].Set(down5.sum2 + cur2, down5.sum5 + cur5, 'D');
			}
		}
	}

	unsigned int res2 = (path2[0][0].sum2 < path2[0][0].sum5) ? path2[0][0].sum2 : path2[0][0].sum5;
	unsigned int res5 = (path5[0][0].sum2 < path5[0][0].sum5) ? path5[0][0].sum2 : path5[0][0].sum5;

	Path** rpath = (res2 < res5) ? path2 : path5;
	unsigned int res = (res2 < res5) ? res2 : res5;
	int r = 0;
	int c = 0;

	if (there_is_zero && res > 1) {
		printf("1\n");
		for (int r = 0; r < zr; ++r) {
			printf("D");
		}
		for (int c = 0; c < zc; ++c) {
			printf("R");
		}
		for (int r = zr; r < n - 1; ++r) {
			printf("D");
		}
		for (int c = zc; c < n - 1; ++c) {
			printf("R");
		}
		printf("\n");
	}
	else {
		printf("%d\n", res);
		while (1) {
			printf("%c", rpath[r][c].next);
			if (rpath[r][c].next == 'R') {
				c += 1;
			}
			else {
				r += 1;
			}
			if (r == n - 1 && c == n - 1) { break; }
		}
		printf("\n");
	}

	return 0;
}