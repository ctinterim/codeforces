import random

# number of alphabet = 26
# number of digits = 10
# total possible chars = 62
# thus appropriate candidate for p are 67, 71, 73, 79

# m should be large prime number number
# somewhere around 10^9 should be appropriate
# candiates = 10^9 + 7, 9, 21, 33, 87

hash_value_1, p_pow_1, p_1, m_1 = 0, 1, 67, int(1e9+7)
hash_value_2, p_pow_2, p_2, m_2 = 0, 1, 71, int(1e9+9)
hash_value_3, p_pow_3, p_3, m_3 = 0, 1, 73, int(1e9+21)
hash_value_4, p_pow_4, p_4, m_4 = 0, 1, 79, int(1e9+33)

def incremental_polynomial_rolling_hash_1(c):
	global hash_value_1, p_pow_1
	hash_value_1 = (hash_value_1 + (c*p_pow_1)) % m_1
	p_pow_1 = (p_pow_1 * p_1) % m_1
	return hash_value_1

def incremental_polynomial_rolling_hash_2(c):
	global hash_value_2, p_pow_2
	hash_value_2 = (hash_value_2 + (c*p_pow_2)) % m_2
	p_pow_2 = (p_pow_2 * p_2) % m_2
	return hash_value_2	

def incremental_polynomial_rolling_hash_3(c):
	global hash_value_3, p_pow_3
	hash_value_3 = (hash_value_3 + (c*p_pow_3)) % m_3
	p_pow_3 = (p_pow_3 * p_3) % m_3
	return hash_value_3	

def incremental_polynomial_rolling_hash_4(c):
	global hash_value_4, p_pow_4
	hash_value_4 = (hash_value_4 + (c*p_pow_4)) % m_4
	p_pow_4 = (p_pow_4 * p_4) % m_4
	return hash_value_4	

if __name__ == '__main__':
	set1 = set([])
	set2 = set([])
	set3 = set([])
	set4 = set([])

	# for i in range(10000):
	# 	c = random.randint(0,61)
	# 	res1 = incremental_polynomial_rolling_hash_1(c)
	# 	res2 = incremental_polynomial_rolling_hash_2(c)

	for i in range(100000000):
		if i % 1000000 == 0:
			print(i,'/',100000000)
		c = random.randint(1,62)
		res1 = incremental_polynomial_rolling_hash_1(c)
		res2 = incremental_polynomial_rolling_hash_2(c)
		res3 = incremental_polynomial_rolling_hash_3(c)
		res4 = incremental_polynomial_rolling_hash_4(c)

		# print(res1)
		# print(res2)

		if (res1 in set1) and (res2 in set2) and (res3 in set3) and (res4 in set4):
			print('collision!',i)

		set1.add(res1)
		set2.add(res2)
		set3.add(res3)
		set4.add(res4)