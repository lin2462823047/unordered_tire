#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
using namespace std;

#include "tire.h"
#include "tire.cpp"

const int N = 1e5;
const int M1 = 3;
const int M2 = 5;

struct Test {
	int num;
	string str;
};

vector<long long> umap_times;
vector<long long> tire_times;

const string table[16] = { "12345", "99999", "97282", "1", "2","3","7", "2222", "22", "3422", "7482", "9374", "000" };
void umap_test(unordered_map<string, Test>& umap) {
	auto start = chrono::high_resolution_clock::now();
	for (int j = 0; j < 1e4; ++j) {
		for (int i = 0; i < 16; ++i) {
			umap.find(table[i]);
		}
	}
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
	umap_times.push_back(duration.count());
}

void tire_test(Tire<Test>& tire) {
	auto start = chrono::high_resolution_clock::now();
	for (int j = 0; j < 1e4; ++j) {
		for (int i = 0; i < 16; ++i) {
			tire.find(table[i]);
		}
	}
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
	tire_times.push_back(duration.count());
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
	Tire<Test> tire;
	unordered_map<string, Test> umap;

	for (int i = 0; i < N; ++i) {
		Test test;
		test.num = i + 1;
		test.str = to_string(i + 1);
		tire.insert(test.str, test);
	};
	for (int i = 0; i < N; ++i) {
		Test test;
		test.num = i + 1;
		test.str = to_string(i + 1);
		umap.insert({ test.str, test });
	};

	// group 1
	for (int i = 0; i < M1; ++i) {
		umap_test(umap);
		tire_test(tire);
	}

	// group 2
	for (int i = 0; i < M1; ++i) {
		tire_test(tire);
		umap_test(umap);
	}

	// group 3
	for (int i = 0; i < M2; ++i) {
		umap_test(umap);
	}
	for (int i = 0; i < M2; ++i) {
		tire_test(tire);
	}

	// group 4
	for (int i = 0; i < M2; ++i) {
		tire_test(tire);
	}
	for (int i = 0; i < M2; ++i) {
		umap_test(umap);
	}

	// 分析
	print_times("umap", umap_times);
	print_times("tire", tire_times);
	analysis("umap", umap_times);
	analysis("tire", tire_times);
	return 0;
}