/*
 * I realise that this solution is in dire need of refactoring.
 * Writing esoteric code is part of the learning process.
 * The solution works, and performs well; that is good enough for now.
 * To be continued...
 */

#include <vector>
#include <utility>
#include <cmath>
#include <stdexcept>
#include <algorithm>

class Solution {
public:
	typedef struct subvec {
		std::vector<int>* supervec;
		std::vector<int>::iterator start, finish;
		inline size_t size() const {
			return finish - start + 1;
		}
	} subvec;

	std::pair<std::vector<int>::iterator, std::vector<int>::iterator>
	recursiveSolution(subvec &s1, subvec& s2, size_t const& ss) {
		size_t const b1 = (s1.start - s1.supervec->begin()) + 1;
		size_t const b2 = (s2.start - s2.supervec->begin()) + 1;
		size_t const r = (ss - b1 - b2);
		size_t si = std::floor(r / 2.0);
		size_t gi = std::ceil(r / 2.0);
		size_t i1 = 0, i2 = 0;
		if (s1.size() < s2.size()) {
			i1 = (s1.size() > si) ? si : s1.size() - 1;
			si -= i1;
			i2 = si + gi;
		} else {
			i2 = (s2.size() > si) ? si : s2.size() - 1;
			si -= i2;
			i1 = si + gi;
		}

		if (s1.start[i1] >= s2.start[i2]) {
			if (s2.start + i2 == s2.supervec->end() - 1 ||
				s2.start[i2 + 1] >= s1.start[i1]) {
				return std::make_pair(s1.start + i1, s2.start + i2);
			} else {
				if (i1 == 0)
					return std::make_pair(s2.start + i2 + 1,
						s2.start + i2 + 1);
				s2.start = (i2 != 0) ? s2.start + i2 : s2.finish;
				s1.finish = s1.start + i1;
			}
		} else {
			if (s1.start + i1 == s1.supervec->end() - 1 ||
				s1.start[i1 + 1] >= s2.start[i2]) {
				return std::make_pair(s1.start + i1, s2.start + i2);
			} else {
				if (i2 == 0)
					return std::make_pair(s1.start + i1 + 1,
						s1.start + i1 + 1);
				s1.start = (i1 != 0) ? s1.start + i1 : s1.finish;
				s2.finish = s2.start + i2;
			}
		}

		return recursiveSolution(s1, s2, ss);
	}

	double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
		// Edge cases: one or both of the vectors are empty
		if (nums1.empty() && nums2.empty())
			throw std::invalid_argument("nums1 and nums2 are both empty");

		if (nums1.empty() || nums2.empty()) {
			auto& v = nums1.empty() ? nums2 : nums1;
			if (v.size() % 2) {
				return v.at(v.size() / 2);
			} else {
				size_t upper_median_index = v.size() / 2;
				size_t lower_median_index = upper_median_index - 1;
				return (v.at(lower_median_index) +
						v.at(upper_median_index)) / 2.0;
			}
		}
		// ------------------------------------------------

		// Average case:
		subvec s1{ &nums1, nums1.begin(), nums1.end() - 1 };
		subvec s2{ &nums2, nums2.begin(), nums2.end() - 1 };
		size_t const m = nums1.size(), n = nums2.size();
		size_t const ss = ((m + n) / 2) + 1;
		auto const p = recursiveSolution(s1, s2, ss);
		double ret = 0.0;
		if ((m + n) % 2) {
			if (&(*p.first) != &(*p.second))
				ret = *p.first > *p.second ? *p.first : *p.second;
			else
				ret = *p.first;
		} else {
			if (&(*p.first) != &(*p.second)) {
				std::vector<int> temp{ *p.first, *p.second };
				if (p.first != nums1.begin()) temp.push_back(p.first[-1]);
				if (p.second != nums2.begin()) temp.push_back(p.second[-1]);
				std::sort(temp.begin(), temp.end());
				ret = (temp.end()[-2] + temp.end()[-1]) / 2.0;
			} else {
				ret = (*p.first + p.first[-1]) / 2.0;
			}
		}
		return ret;
		// -------------
	}
};
