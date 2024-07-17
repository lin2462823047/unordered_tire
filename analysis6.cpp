#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <cstdlib>
using namespace std;

#include "list.h"
#include "tire.h"

const int N = 1e5;
const int M1 = 3;
const int M2 = 5;

struct Test {
	int num;
	string str;
};

void umap_test() {
	unordered_map<string, Test> umap;
	for (int i = 0; i < N; ++i) {
		Test test;
		test.num = i + 1;
		test.str = to_string(i + 1);
		umap.insert({ test.str, test });
	};
	for (int i = N * 2; i >= 0; i -= 17) {
		size_t res = umap.erase(to_string(i + 1));
	};
	cout << "umap ";
	system("pause");
}

void tire_test() {
	Tire<Test> tire;
	for (int i = 0; i < N; ++i) {
		Test test;
		test.num = i + 1;
		test.str = to_string(i + 1);
		tire.insert(test.str, test);
	};
	for (int i = N * 2; i >= 0; i -= 17) {
		size_t res = tire.erase(to_string(i + 1));
	};
	cout << "tire ";
	system("pause");
}

void analysis(string name, vector<long long>& nums) {
	const int n = nums.size();
	long long maxn = LLONG_MIN, minn = LLONG_MAX;
	long long sum = 0;
	for (long long& num : nums) {
		maxn = max(maxn, num);
		minn = min(minn, num);
		sum += num;
	}
	cout << name << ": " << "maxn: " << maxn << "ms    " << "minn: " << minn << "ms    " << "avg: " << (1.0 * sum / n) << "ms    " << "sum: " << sum << "ms    " << endl;
}

void print_times(string name, vector<long long>& nums) {
	cout << name << endl;
	for (long long& num : nums) {
		cout << num << " ";
	};
	cout << endl;
}

int main() {
	// group 1
	for (int i = 0; i < M1; ++i) {
		umap_test();
		tire_test();
	}

	// group 2
	for (int i = 0; i < M1; ++i) {
		tire_test();
		umap_test();
	}
	return 0;
}