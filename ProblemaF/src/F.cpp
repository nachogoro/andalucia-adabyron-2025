#include <bits/stdc++.h>

using namespace std;

class Fraction {
	public:
		Fraction(int num, int den)
		{
			int g = gcd(abs(num), abs(den));
			this->num = num / g;
			this->den = den / g;

			if (this->den < 0) {
				this->num *= -1;
				this->den *= -1;
			}
		}

		bool operator<(Fraction o) const {
			auto d = lcm(den, o.den);

			auto a = num*d / den;
			auto b = o.num*d / o.den;
			return a < b;
		}

		bool is_int() const { return den == 1; }

		int as_int() const { return num; }

		int gcd(int a, int b) const {
			if (b == 0) return a;
			return gcd(b, a % b);
		}

		int lcm(int a, int b) const {
			return a*b / gcd(a, b);
		}

		Fraction plus(Fraction o) {
			auto d = lcm(den, o.den);
			return {(num * d) / den + (o.num * d) / o.den, d};
		}

		Fraction minus(Fraction o) {
			return plus({-1 * o.num, o.den});
		}

		Fraction mult(Fraction o) {
			return {num * o.num, den * o.den};
		}

		Fraction div(Fraction o) {
			return mult({o.den, o.num});
		}

		int num;
		int den;
};

std::set<Fraction> combine(const std::vector<Fraction>& v) {
	if(v.size() == 0) { return {}; }
	if(v.size() == 1) { return {v[0]}; }

	std::set<Fraction> results;

	for (int n = 1; n <= (1 << (v.size() - 1)) - 1; ++n) {
		std::vector<Fraction> a;
		std::vector<Fraction> b;

		for (int bit = 0; bit < v.size(); ++bit) {
			if ((n & (1 << bit)) == 0) {
				a.push_back(v[bit]);
			} else {
				b.push_back(v[bit]);
			}
		}

		auto left = combine(a);
		auto right = combine(b);

		for (auto l : left) {
			for (auto r : right) {
				auto s = l.plus(r);
				auto m = l.minus(r);
				auto mu = l.mult(r);
				auto di = l.div(r);

				results.insert(l.plus(r));
				results.insert(l.minus(r));
				results.insert(l.mult(r));

				if (r.num != 0)
					results.insert(l.div(r));
				results.insert(r.minus(l));

				if (l.num != 0)
					results.insert(r.div(l));
			}
		}
	}

	return results;
}

int main() {
	int n;
	cin >> n;

	string line;
	// Skip trailing \n
	getline(cin, line);
	while (n--) {
		getline(cin, line);
		istringstream iss(line);
		vector<Fraction> nums;

		int num;
		while (iss >> num) {
			nums.push_back({num, 1});
		}

		std::set<Fraction> all_possibilities = combine(nums);
		cout << count_if(
				all_possibilities.begin(),
				all_possibilities.end(),
				[](Fraction f){ return f.is_int() && f.as_int() > 0; })
			<< "\n";
	}
}
