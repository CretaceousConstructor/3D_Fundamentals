#pragma once


class Indexes {
public:
	Indexes(size_t i, size_t j, size_t k) {
		index[0] = i;
		index[1] = j;
		index[2] = k;
	}
	size_t index[3];
	size_t operator[](size_t i) const {
		return index[i];
	}
};