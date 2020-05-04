#pragma once
#include <cstdlib> 
struct loc {
	int locX, locY;
	bool operator == (const loc& obj) {
		if (this->locX == obj.locX and this->locY == obj.locY)
			return true;
		return false;
	}
};

template <class T>
void setLocation(T *obj, int locX = 0, int locY = 0) {
	obj->currentLoc.locX = locX;
	obj->currentLoc.locY = locY;
}

template <class T>
loc getLocation(T *obj) {
	return obj->currentLoc;
}

inline int randNum(int lower, int higher) {
	return rand() % (higher-lower + 1) + lower;
}

inline int minim(int a, int b) {
	if (a < b)
		return a;
	return b;
}

inline int maxim(int a, int b) {
	if (a > b)
		return a;
	return b;
}