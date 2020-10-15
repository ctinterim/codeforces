#include <iostream>
#include <set>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <vector>

#define MAX_INPUT_SIZE 5000000
char* input = NULL;
int input_length = 0;
unsigned char* is_k_palindrome = NULL;

int main() {
	std::ios_base::sync_with_stdio(false);

	input = new char[MAX_INPUT_SIZE + 1];
	memset(input, 0, MAX_INPUT_SIZE + 1);

	is_k_palindrome = new unsigned char[MAX_INPUT_SIZE];
	memset(is_k_palindrome, 0, MAX_INPUT_SIZE);

	std::cin >> input;
	input_length = strlen(input);

	int i = 0;
	bool pattern_match;
	bool look_once_more;

	// 1. repeating first character
	while (input[i] == input[0]) {
		is_k_palindrome[i] = 1;
		++i;
	}

	// 2. other case
	while (i <= (input_length / 2)) {
		int pattern_length = i;
		std::cout << pattern_length << std::endl;
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
			is_k_palindrome[i - 1] = 1;
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
			is_k_palindrome[i - 1] = 1;
			continue;
		}

		// No need to look further
		break;
	}

	i = input_length - 1;
	int total_sum = 0;
	while (i >= 0) {
		if (is_k_palindrome[i]) {
		}
		--i;
	}
}