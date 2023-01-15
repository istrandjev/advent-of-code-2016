#include <iostream>
#include <string>
#include <cstdio>
#include <set>
#include <map>
#include <vector>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <regex>

#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;

const int n = 3004953;
template<class T>
struct TieredVector {
    struct cyclicQueue {
        int from, to;
        int head, tail;
        int size;
        vector<T>* container;
        cyclicQueue(vector<T>* _container, int _from = 0, int _to = 0,
                int _size = 0)
                : from(_from), to(_to), head(_from), tail(_from), size(_size), container(
                        _container) {
        }
        inline bool empty() const {
            return size == 0;
        }
        inline bool full() const {
            return size == to - from + 1;
        }

        void push_back(const T& val) {
            (*container)[head] = val;
            increase(head);
            size++;
        }

        void push_front(const T& val) {
            decrease(tail);
            (*container)[tail] = val;
            size++;
            return;
        }

        void insert(int index, const T& val) {
            if (index == size) {
                push_back(val);
                return;
            }

            if (index == 0) {
                push_front(val);
                return;
            }

            index = convert_index(index);
            shift_section_forward(head, index);
            (*container)[index] = val;
            increase(head);
            size++;
        }

        const T& operator[](int index) const {
            index = convert_index(index);
            return (*container)[index];
        }

        T& operator[](int index) {
            index = convert_index(index);
            return (*container)[index];
        }

        T remove(int index) {
            if (index == 0) {
                return pop_front();
            }
            if (index == size - 1) {
                return pop_back();
            }

            index = convert_index(index);
            T res = (*container)[index];
            shift_section_forward(index, tail);
            increase(tail);
            size--;
            return res;
        }

        T pop_front() {
            const T& res = (*container)[tail];
            size--;
            increase(tail);
            return res;
        }

        T pop_back() {
            decrease(head);
            size--;
            return (*container)[head];
        }

        void rotateToCannonical() {
            if (size == 0 || tail == from) {
                return;
            }
            rotate(container->begin() + from, container->begin() + tail,
                    container->begin() + to + 1);
            tail = from;
            head = tail + size;
            if (head > to) {
                head = from;
            }
        }
    private:
        inline int convert_index(int index) const {
            index = tail + index;
            if (index > to) {
                index = from + index - to - 1;
            }
            return index;
        }

        void shift_section_forward(int index, int end) {
            while (index != end) {
                int prev = index;
                decrease(prev);
                (*container)[index] = (*container)[prev];
                index = prev;
            }
        }

        void increase(int& index) const {
            index = index + 1;
            if (index > to) {
                index = from;
            }
        }

        void decrease(int& index) const {
            index = index - 1;
            if (index < from) {
                index = to;
            }
        }
    };

    TieredVector(int requested_capacity)
            : _size(0) {
        int val = (int)sqrt(requested_capacity);
        if (val * val < requested_capacity) {
            val++;
        }

        changeCapacity(val);
        _size = 0;
    }

    void insert(int index, const T& val) {
        if (full()) {
            grow();
        }
        int queuei = index / currentCap;
        if (queues[queuei].full()) {
            T element_to_shift = queues[queuei].pop_back();
            for (int i = queuei + 1; i < currentCap; ++i) {
                if (!queues[i].full()) {
                    queues[i].push_front(element_to_shift);
                    break;
                } else {
                    T temp = queues[i].pop_back();
                    queues[i].push_front(element_to_shift);
                    element_to_shift = temp;
                }
            }
        }

        queues[queuei].insert(index % currentCap, val);
        _size++;
    }

    void push_back(const T& val) {
        if (full()) {
            grow();
        }
        insert(_size, val);
    }

    T pop_back() {
        T res = remove(_size - 1);
        // shrink_if_needed();
        return res;
    }

    T remove(int index) {
        int queuei = index / currentCap;
        int lasti = (_size - 1) / currentCap;
        T res = queues[queuei].remove(index % currentCap);
        if (lasti != queuei) {
            T element_to_shift = queues[lasti].pop_front();
            for (int j = lasti - 1; j > queuei; --j) {
                T temp = queues[j].pop_front();
                queues[j].push_back(element_to_shift);
                element_to_shift = temp;
            }
            queues[queuei].push_back(element_to_shift);
        }

        _size--;
        // shrink_if_needed();
        return res;
    }

    const T& operator[](int index) const {
        int queuei = index / currentCap;
        return queues[queuei][index % currentCap];
    }

    T& operator[](int index) {
        int queuei = index / currentCap;
        return queues[queuei][index % currentCap];
    }

    int size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

    bool full() const {
     return _size == currentCap * currentCap;
    }

    vector<T> values;
    vector<cyclicQueue> queues;
    int currentCap;
    int _size;

private:
    void grow_if_needed() {
        if (full()) {
            grow();
        }
    }

    void shrink_if_needed() {
        if (currentCap > 2 && _size * 8 <= currentCap * currentCap) {
            shrink();
        }
    }

    void grow() {
        for (int i = 0; i < (int)queues.size(); ++i) {
            if (queues[i].empty()) {
                break;
            }
            queues[i].rotateToCannonical();
        }

        changeCapacity(2 * currentCap);
    }

    void shrink() {
        for (int i = 0; i < (int)queues.size(); ++i) {
            if (queues[i].empty()) {
                break;
            }
            queues[i].rotateToCannonical();
        }

        changeCapacity(currentCap / 2);
    }

    void changeCapacity(int newCapacity) {
        currentCap = newCapacity;
        values.resize(currentCap * currentCap);
        queues.resize(currentCap, cyclicQueue(&values));
        for (int i = 0; i < currentCap; ++i) {
            queues[i].from = i * currentCap;
            queues[i].to = (i + 1) * currentCap - 1;
            queues[i].tail = queues[i].from;
            queues[i].size = max(0, _size - queues[i].from + 1);

            if (queues[i].size >= currentCap) {
                queues[i].head = queues[i].tail;
                queues[i].size = currentCap;
            } else {
                queues[i].head = queues[i].from + queues[i].size;
            }
        }
    }
};

int main() {
    vector<int> a(n);
    iota(all(a), 1);
    while (a.size() > 1) {
        vector<int> b;
        for (int i = 0; i + 1 < a.size(); i += 2) {
            b.push_back(a[i]);
        }
        if (a.size() % 2) {
            int temp = a.back();
            a.clear();
            a.push_back(temp);
            for (auto v : b) {
                a.push_back(v);
            }
        } else {
            a = b;
        }
    }
    cout << "Part 1 " << a.back() << endl;
    TieredVector<int> tv(n);
    for (int i = 1 ; i <= n; ++i) {
        tv.push_back(i);
    }
    int index = 0;
    while (tv.size() >  1) {
        int m = tv.size();
        int to_remove = (index + m / 2) % m;
        tv.remove(to_remove);

        if (to_remove > index) {
            index += 1;
        }
        index %= tv.size();
    }
    cout << "Part 2 " << tv[0] << endl;
    return 0;
}