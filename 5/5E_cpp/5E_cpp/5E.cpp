#include <iostream>
#include <vector>

int main() {
	std::ios_base::sync_with_stdio(false);
	
	int n = 0;
	int* hill = NULL;
	int* chain = NULL;

	std::cin >> n;
	hill = new int[n];
	chain = new int[n + 1];
	int chain_length = n + 1;

	for (int i = 0; i < n; ++i) {
		std::cin >> hill[i];
	}

	int maxh = hill[0];
	int maxhi = 0;
	bool allsame = true;
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
		unsigned long long lln = n;
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

	int* L = new int[chain_length];
	int* L_hi = new int[chain_length];
	int* L_numsame = new int[chain_length];

	for (int i = 0; i < chain_length; ++i) {
		L[i] = 0;
		L_hi[i] = 0;
		L_numsame[i] = 0;
	}

	int* R = new int[chain_length];
	int* R_hi = new int[chain_length];

	for (int i = 0; i < chain_length; ++i) {
		R[i] = 0;
		R_hi[i] = chain_length-1;
	}

	std::vector<int> same;
	int higher = 0;
	int L_numsame_s = 0;

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

	return 0;
}