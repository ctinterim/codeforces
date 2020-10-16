#include <iostream>
#include <set>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <vector>

#define MAX_INPUT_SIZE 5000000
char* input = NULL;
int input_length = 0;
unsigned int* rabin_fingerprint_lr = NULL;
unsigned int* rabin_fingerprint_rl = NULL;
unsigned int* is_k_palindrome = NULL;

unsigned int p = 131;   // 127, 131, 137, 139, 149, 151
unsigned int m = 1e9+9; // 9, 21, 33, 87, 93, 97

void kPalindrome(int start_index, unsigned int last_is_k_palindrome){
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

// Rabin Fingerprint of [start,end] ( NOT [start,end)! )
unsigned int getRabinFingerprint(int start, int end){
	if(start == 0){
		return rabin_fingerprint[end];
	}
	else{
		unsigned long long rightend = rabin_fingerprint[end];
		unsigned long long leftend = rabin_fingerprint[start-1];
		
		rightend = (rightend < leftend) ? rightend + m : rightend;
		return rightend - leftend;
	}
}

// Check if [0,end] is really palindrome
bool isReallyPrefixPalindrome(int end){
	int i = 0;
	int j = end;
	bool is_palindrome = true;
	while(i < j){
		if(input[i] != input[j]){
			is_palindrome = false;
			break;
		}
	}
	return is_palindrome;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	input = new char[MAX_INPUT_SIZE + 1];
	memset(input, 0, MAX_INPUT_SIZE + 1);

	is_k_palindrome = new unsigned int[MAX_INPUT_SIZE];
	for(int i=0; i<MAX_INPUT_SIZE; ++i){
		is_k_palindrome[i] = -1;
	}

	rabin_fingerprint = new unsigned int[MAX_INPUT_SIZE];
	memset(rabin_fingerprint, 0, sizeof(unsigned int)*MAX_INPUT_SIZE);

	std::cin >> input;
	input_length = strlen(input);

	int i = 0;
	unsigned int last_is_k_palindrome = 0;
	// 1. repeating first character
	while (input[i] == input[0]) {
		is_k_palindrome[i] = ((i+1)/2)+1;
		last_is_k_palindrome = is_k_palindrome[i];
		++i;
	}
	// 2. calculate k-palindrome based on first repeating section
	kPalindrome(i, last_is_k_palindrome);

	// 3. calculate rabin-karp
	unsigned long long power_of_p = 1;
	unsigned long long hash_val = 0;
	for(int i=0; i<input_length; ++i){
		hash_val = (hash_val + input[i]*power_of_p) % m;
		power_of_p = (power_of_p * p) % m;
		rabin_fingerprint[i] = hash_val;
	}

	// 4. check palindrome
	for(int i=0; i<input_length; ++i){
		if(is_k_palindrome[i] != -1){
			continue;
		}
		int ll,lr,rl,rr;
		ll = 0;
		lr = (i&1) ? i/2 : (i/2)-1;
		rl = (i&1) ? lr+1 : lr+2;
		rr = i;

		unsigned int rfl = getRabinFingerprint(ll,lr);
		unsigned int rfr = getRabinFingerprint(rl,rr);

		printf("%d %u %u %d %d %d %d\n",i,rfl,rfr,ll,lr,rl,rr);

		if(rfl == rfr && isReallyPrefixPalindrome(i)){
			is_k_palindrome[i] = 1;
			kPalindrome(i,1);
		}
		else{
			is_k_palindrome[i] = 0;
		}
	}

	unsigned long long total_sum = 0;
	for(int i=0; i<input_length; ++i){
		total_sum += is_k_palindrome[i];
	}

	std::cout << total_sum << std::endl;
}