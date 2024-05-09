#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class VEBTree {
private:
    int u; // Universe size
    int min, max;
    VEBTree* summary;
    vector<VEBTree*> cluster;

    // Helper functions
    int high(int x) {
        return x / sqrt(u);
    }

    int low(int x) {
        return x % (int)sqrt(u);
    }

    int index(int x, int y) {
        return x * sqrt(u) + y;
    }

    void insertEmpty(int x) {
        min = max = x;
    }

public:
    // Constructor
    VEBTree(int size) {
        u = size;
        min = -1;
        max = -1;

        // Create summary and clusters
        if (u <= 2)
            return;
        int clusterSize = ceil(sqrt(u));
        summary = new VEBTree(clusterSize);
        for (int i = 0; i < clusterSize; ++i)
            cluster.push_back(new VEBTree(clusterSize));
    }

    // Destructor
    ~VEBTree() {
        delete summary;
        for (auto c : cluster)
            delete c;
    }

    // Insertion operation
    void insert(int x) {
        if (min == -1)
            insertEmpty(x);
        else {
            if (x < min)
                swap(x, min);
            if (u > 2) {
                int h = high(x);
                int l = low(x);
                if (cluster[h]->min == -1)
                    summary->insert(h);
                cluster[h]->insert(l);
            }
            if (x > max)
                max = x;
        }
    }

    // Deletion operation
    void erase(int x) {
        if (min == max) {
            min = max = -1;
            return;
        }
        if (u == 2) {
            if (x == 0)
                min = 1;
            else
                min = 0;
            max = min;
        } else {
            if (x == min) {
                int firstCluster = summary->min;
                x = index(firstCluster, cluster[firstCluster]->min);
                min = x;
            }
            cluster[high(x)]->erase(low(x));
            if (cluster[high(x)]->min == -1) {
                summary->erase(high(x));
                if (x == max) {
                    int summaryMax = summary->max;
                    if (summaryMax == -1)
                        max = min;
                    else
                        max = index(summaryMax, cluster[summaryMax]->max);
                }
            } else if (x == max)
                max = index(high(x), cluster[high(x)]->max);
        }
    }

    // Successor operation
    int successor(int x) {
        if (u == 2) {
            if (x == 0 && max == 1)
                return 1;
            else
                return -1;
        } else if (min != -1 && x < min)
            return min;
        else {
            int h = high(x);
            int l = low(x);
            int maxlow = cluster[h]->max;
            if (maxlow != -1 && l < maxlow) {
                int offset = cluster[h]->successor(l);
                return index(h, offset);
            } else {
                int succCluster = summary->successor(h);
                if (succCluster == -1)
                    return -1;
                else {
                    int offset = cluster[succCluster]->min;
                    return index(succCluster, offset);
                }
            }
        }
    }

    // Predecessor operation
    int predecessor(int x) {
       if (u == 2) {
            if (x == 1 && min == 0)
                return 0;
            else
                return -1;
        } else if (max != -1 && x > max)
            return max;
        else {
            int h = high(x);
            int l = low(x);
            int minlow = cluster[h]->min;
            if (minlow != -1 && l > minlow) {
                int offset = cluster[h]->predecessor(l);
                return index(h, offset);
            } else {
                int predCluster = summary->predecessor(h);
                if (predCluster == -1) {
                    if (min != -1 && x > min)
                        return min;
                    else
                        return -1;
                } else {
                    int offset = cluster[predCluster]->max;
                    return index(predCluster, offset);
                }
            }
        }
    }

    // Maximum operation
    int maximum() {
        return max;
    }

    // Minimum operation
    int minimum() {
        return min;
    }

    // Print operation
    void print() {
        cout << "VEB Tree: ";
        if (min == -1) {
            cout << "Empty";
        } else {
            printHelper();
        }
        cout << endl;
    }

private:
void printHelper(int depth = 0, int offset = 0) {
    if (u == 2) {
        if (min != -1) cout << min + offset;
        if (max != -1 && max != min) cout << " " << max + offset;
    } else {
        if (min == -1) {
            cout << "[Empty]";
            return;
        }
        cout << "Node " << depth << " [" << min + offset << "-" << max + offset << "]" << endl;
        for (int i = 0; i < sqrt(u); ++i) {
            if (cluster[i]->min != -1) {
                for (int j = 0; j < depth + 1; ++j)
                    cout << "    ";
                cluster[i]->printHelper(depth + 1, offset + i * sqrt(u));
            }
        }
    }
}



};

int main() {
    VEBTree veb(16); // Example with universe size 16
    veb.insert(5);
    veb.insert(3);
    veb.insert(7);
    veb.insert(2);
    veb.insert(10);

    cout << "After insertion: ";
    veb.print();

    veb.erase(3);
    cout << "After deletion of 3: ";
    veb.print();

    cout << "Successor of 5: " << veb.successor(5) << endl;
    cout << "Predecessor of 7: " << veb.predecessor(7) << endl;
    cout << "Maximum: " << veb.maximum() << endl;
    cout << "Minimum: " << veb.minimum() << endl;

    return 0;
}
