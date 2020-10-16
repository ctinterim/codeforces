#include <iostream>
#include <set>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <vector>

#define MAX_INPUT_SIZE 5000000
char* input = NULL;
int input_length = 0;
unsigned int* left_rk_hash = NULL;
unsigned int* left_rk_power = NULL;
unsigned int* right_rk_hash = NULL;
unsigned int* rk_power = NULL;
unsigned int* is_k_palindrome = NULL;

unsigned int p = 131;   // 127, 131, 137, 139, 149, 151
unsigned int m = 1e9 + 9; // 9, 21, 33, 87, 93, 97

void kPalindrome(int start_index, unsigned int last_is_k_palindrome) {
	int i = start_index;

	while (i <= (input_length / 2)) {
		int pattern_length = i;
		//std::cout << pattern_length << std::endl;
		// case 1
		int l = 0;
		int r = (pattern_length * 2) - 1;
		bool pattern_match = true;
		while (l < r) {
			if (input[l] != input[r]) {
				pattern_match = false;
				break;
			}
			++l;
			--r;
		}
		if (pattern_match) {
			i += pattern_length;
			is_k_palindrome[i - 1] = last_is_k_palindrome + 1;
			++last_is_k_palindrome;
			continue;
		}

		// case 2
		l = 0;
		r = (pattern_length * 2);
		pattern_match = true;
		while (l < r) {
			if (input[l] != input[r]) {
				pattern_match = false;
				break;
			}
			++l;
			--r;
		}
		if (pattern_match) {
			i += pattern_length + 1;
			is_k_palindrome[i - 1] = last_is_k_palindrome + 1;
			++last_is_k_palindrome;
			continue;
		}

		// No need to look further
		break;
	}
}

//compare [ll,lr] and [rl,rr] where l is l->r and r is l <- r
bool compareRabinKarpPalindrome(int ll, int lr, int rl, int rr) {
	unsigned long long left_hash = 0;
	if (ll == 0) {
		left_hash = left_rk_hash[lr];
	}
	else {
		unsigned long long ll_hash = left_rk_hash[ll-1];
		unsigned long long lr_hash = left_rk_hash[lr];
		lr_hash = (ll_hash > lr_hash) ? lr_hash + m : lr_hash;
		left_hash = lr_hash - ll_hash;
	}

	unsigned long long right_hash = 0;
	if (rr == input_length - 1) {
		right_hash = right_rk_hash[rl];
	}
	else {
		unsigned long long rr_hash = right_rk_hash[rr+1];
		unsigned long long rl_hash = right_rk_hash[rl];
		rl_hash = (rr_hash > rl_hash) ? rl_hash + m : rl_hash;
		right_hash = rl_hash - rr_hash;
	}

	int left_power = lr;
	int right_power = (input_length - 1) - rl;

	//printf("%d %d %d %d %llu %llu\n", ll, lr, rl, rr, left_hash, right_hash);

	if (left_power < right_power) {
		left_hash = (left_hash * rk_power[right_power - left_power]) % m;
	}
	else {
		right_hash = (right_hash * rk_power[left_power - right_power]) % m;
	}

	//printf("%d %d %d %d %llu %llu\n", ll, lr, rl, rr, left_hash, right_hash);

	return left_hash == right_hash;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	input = new char[MAX_INPUT_SIZE + 1];
	memset(input, 0, MAX_INPUT_SIZE + 1);

	is_k_palindrome = new unsigned int[MAX_INPUT_SIZE];
	for (int i = 0; i < MAX_INPUT_SIZE; ++i) {
		is_k_palindrome[i] = -1;
	}

	left_rk_hash = new unsigned int[MAX_INPUT_SIZE];
	memset(left_rk_hash, 0, sizeof(unsigned int)*MAX_INPUT_SIZE);

	right_rk_hash = new unsigned int[MAX_INPUT_SIZE];
	memset(right_rk_hash, 0, sizeof(unsigned int)*MAX_INPUT_SIZE);

	rk_power = new unsigned int[MAX_INPUT_SIZE];
	memset(rk_power, 0, sizeof(unsigned int)*MAX_INPUT_SIZE);

	std::cin >> input;
	input_length = strlen(input);

	int i = 0;
	unsigned int last_is_k_palindrome = 0;
	int is_k_palindrome_log_val = 1;
	int cur_log = 1;
	int cur_count = 1;
	// 1. repeating first character
	while (input[i] == input[0]) {
		is_k_palindrome[i] = is_k_palindrome_log_val;
		last_is_k_palindrome = is_k_palindrome[i];

		--cur_count;
		if (cur_count == 0) {
			++is_k_palindrome_log_val;
			cur_log *= 2;
			cur_count = cur_log;
		}

		++i;
	}
	// 2. calculate k-palindrome based on first repeating section
	kPalindrome(i, last_is_k_palindrome);

	// 3. calculate rabin-karp left -> right
	unsigned long long power_of_p = 1;
	unsigned long long hash_val = 0;
	for (int i = 0; i < input_length; ++i) {
		hash_val = (hash_val + input[i] * power_of_p) % m;
		left_rk_hash[i] = hash_val;
		rk_power[i] = power_of_p;
		power_of_p = (power_of_p * p) % m;
	}
	// 4. calculate rabin-karp right -> left
	power_of_p = 1;
	hash_val = 0;
	for (int i = input_length - 1; i > -1; --i) {
		hash_val = (hash_val + input[i] * power_of_p) % m;
		right_rk_hash[i] = hash_val;
		power_of_p = (power_of_p * p) % m;
	}

	// 4. check palindrome
	for (int i = 0; i < input_length; ++i) {
		if (is_k_palindrome[i] != -1) {
			continue;
		}
		int ll, lr, rl, rr;
		ll = 0;
		lr = (i & 1) ? i / 2 : (i / 2) - 1;
		rl = (i & 1) ? lr + 1 : lr + 2;
		rr = i;

		if (compareRabinKarpPalindrome(ll,lr,rl,rr)) {
			is_k_palindrome[i] = 1;
			kPalindrome(i, 1);
		}
		else {
			is_k_palindrome[i] = 0;
		}
	}

	unsigned long long total_sum = 0;
	for (int i = 0; i < input_length; ++i) {
		total_sum += is_k_palindrome[i];
	}

	std::cout << total_sum << std::endl;
}