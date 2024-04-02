#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <list>
#include <algorithm>

using namespace std;

// IMPLEMENTATION OF FULLY ASSOCIATIVE CACHE ALGORITHMS

// FIFO Cache Replacement Algorithm
tuple<int, int, int> FIFO(const vector<int>& arr, int n) {
    int misses = 0, hits = 0, evictions = 0;
    unordered_map<int, bool> cache;
    list<int> fifoQueue;

    for (int i = 0; i < arr.size(); ++i) {
        if (cache.find(arr[i]) != cache.end()) {
            ++hits;
        } else {
            ++misses;
            if (fifoQueue.size() == n) {
                cache.erase(fifoQueue.front());
                fifoQueue.pop_front();
                ++evictions;
            }
            fifoQueue.push_back(arr[i]);
            cache[arr[i]] = true;
        }
    }

    return make_tuple(misses, hits, evictions);
}

// LRU Cache Replacement Algorithm
tuple<int, int, int> LRU(const vector<int>& arr, int n) {
    int misses = 0, hits = 0, evictions = 0;
    unordered_map<int, list<int>::iterator> cache;
    list<int> lruList;

    for (int i = 0; i < arr.size(); ++i) {
        if (cache.find(arr[i]) != cache.end()) {
            ++hits;
            lruList.erase(cache[arr[i]]);
        } else {
            ++misses;
            if (lruList.size() == n) {
                cache.erase(lruList.front());
                lruList.pop_front();
                ++evictions;
            }
        }
        lruList.push_back(arr[i]);
        cache[arr[i]] = prev(lruList.end());
    }

    return make_tuple(misses, hits, evictions);
}

// LFU Cache Replacement Algorithm
tuple<int, int, int> LFU(const vector<int>& arr, int n) {
    int misses = 0, hits = 0, evictions = 0;
    unordered_map<int, pair<int, list<int>::iterator>> cache;
    unordered_map<int, int> frequency;
    list<int> lfuList;

    for (int i = 0; i < arr.size(); ++i) {
        if (cache.find(arr[i]) != cache.end()) {
            ++hits;
            int freq = ++frequency[arr[i]];
            lfuList.erase(cache[arr[i]].second);
            auto it = lfuList.begin();
            while (it != lfuList.end() && frequency[*it] < freq) ++it;
            cache[arr[i]] = make_pair(freq, lfuList.insert(it, arr[i]));
        } else {
            ++misses;
            if (lfuList.size() == n) {
                cache.erase(lfuList.front());
                frequency.erase(lfuList.front());
                lfuList.pop_front();
                ++evictions;
            }
            frequency[arr[i]] = 1;
            lfuList.push_back(arr[i]);
            cache[arr[i]] = make_pair(1, prev(lfuList.end()));
        }
    }

    return make_tuple(misses, hits, evictions);
}

// MRU Cache Replacement Algorithm
tuple<int, int, int> MRU(const vector<int>& arr, int n) {
    int misses = 0, hits = 0, evictions = 0;
    unordered_map<int, list<int>::iterator> cache;
    list<int> mruList;

    for (int i = 0; i < arr.size(); ++i) {
        if (cache.find(arr[i]) != cache.end()) {
            ++hits;
            mruList.erase(cache[arr[i]]);
        } else {
            ++misses;
            if (mruList.size() == n) {
                cache.erase(mruList.back());
                mruList.pop_back();
                ++evictions;
            }
        }
        mruList.push_front(arr[i]);
        cache[arr[i]] = mruList.begin();
    }

    return make_tuple(misses, hits, evictions);
}

int main() {
    // vector<int> arr = {2, 3, 4, 7, 6, 3, 4, 7, 5, 4, 7, 8}; // original
        vector<int> arr = {2, 3, 4, 7, 6, 3, 4, 7, 5, 4, 7, 8, 10, 11, 2, 3, 4, 6, 1, 3, 7, 8}; // duplicate

    int n = 8; 
    // FIFO
    int fifo_misses, fifo_hits, fifo_evictions;
    tie(fifo_misses, fifo_hits, fifo_evictions) = FIFO(arr, n);
    cout << "FIFO Misses: " << fifo_misses << ", Hits: " << fifo_hits << ", Evictions: " << fifo_evictions << endl;

    // LRU
    int lru_misses, lru_hits, lru_evictions;
    tie(lru_misses, lru_hits, lru_evictions) = LRU(arr, n);
    cout << "LRU Misses: " << lru_misses << ", Hits: " << lru_hits << ", Evictions: " << lru_evictions << endl;

    // LFU
    int lfu_misses, lfu_hits, lfu_evictions;
    tie(lfu_misses, lfu_hits, lfu_evictions) = LFU(arr, n);
    cout << "LFU Misses: " << lfu_misses << ", Hits: " << lfu_hits << ", Evictions: " << lfu_evictions << endl;

    // MRU
    int mru_misses, mru_hits, mru_evictions;
    tie(mru_misses, mru_hits, mru_evictions) = MRU(arr, n);
    cout << "MRU Misses: " << mru_misses << ", Hits: " << mru_hits << ", Evictions: " << mru_evictions << endl;

    return 0;
}
