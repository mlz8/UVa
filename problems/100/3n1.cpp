#include <iostream>
#include <vector>
#include <algorithm>
// #include <time.h>
#include <utility>
#include <unordered_map>

using namespace std;

#define MAX 10000

#define METHOD 0 // 0=using vector, 1=using unordered_map, 2=no caching

#if METHOD == 0 // 0.130 sec
vector<int> cache;
int get_depth(unsigned int aux) {	
	if(aux < cache.size() && cache[aux] != -1) { 
		return cache[aux];
	}
	int next;

	if ((aux & 1) == 0) {
		next = aux / 2; 
	} else {
		next = 3*aux+1; 
	}
	int length = get_depth(next) + 1;
	if (aux < cache.size())
		cache[aux] = length;
	return length;
}

#elif METHOD == 1 // 0.050 sec
std::unordered_map<int, int> cache;
int get_depth(unsigned int aux) {
	int k = 1;
	vector<pair<int, int> > vec;
	while (aux != 1) {
		if ((aux & 1) == 0) {
			aux >>= 1; k++;
		} else {
			aux += ((aux + 1) >> 1); k += 2;
		}

		std::unordered_map<int, int>::iterator it = cache.find(aux);
		if (it == cache.end()) {
			vec.push_back(make_pair(aux, k));
		} else {
			k += it->second;		
			break;
		}
	}

	for(pair<int, int> &v:vec) {
		cache.insert(make_pair(v.first, k - v.second));
	}
	
	return k;
}

#elif METHOD == 2 // 0.240 sec
unsigned int get_depth(unsigned int aux) {
	unsigned int k = 1;
	while (aux != 1) {
		if ((aux & 1) == 0) {
			aux >>= 1; k++;
		} else {
			aux += ((aux + 1) >> 1); k += 2;
		}
	}
	return k;
}


#endif

int main() {
	// clock_t tStart = clock();
	unsigned int x, y;
    unsigned int rem_x, rem_y;
    
#if METHOD == 0
    cache.resize(MAX, -1);
    cache[0] = 0;
    cache[1] = 1;
#endif


    while (scanf("%d %d\n", &x, &y) == 2) {
		rem_x = x; rem_y = y;
		if (x > y) {
			swap(x, y);
		}

		unsigned int max = 0;
		for(; x <= y; x++) {
		    unsigned int aux = get_depth(x);
		    if (aux > max)
				max = aux;
		}


		printf("%d %d %d\n", rem_x, rem_y, max);
    }
	// printf("Time taken: %.4fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	return 0;
}