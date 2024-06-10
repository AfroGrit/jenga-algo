#include <iostream>
#include <vector>
#include <cstring>
#include <cassert>

using namespace std;

#define MAXN 100
int nx, ny;
int cx[MAXN], cy[MAXN];
int mk[MAXN];

// Function to find an augmenting path
int path(int u, const vector<vector<bool>>& adj_matrix) {
    for (int v = 0; v < ny; ++v) {
        if (adj_matrix[u][v] && !mk[v]) {
            mk[v] = 1;
            if (cy[v] == -1 || path(cy[v], adj_matrix)) {
                cx[u] = v;
                cy[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

// Function to compute maximum matching
int maxMatch(const vector<vector<bool>>& adj_matrix) {
    int res = 0;
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    for (int i = 0; i < nx; ++i) {
        if (cx[i] == -1) {
            memset(mk, 0, sizeof(mk));
            res += path(i, adj_matrix);
        }
    }
    return res;
}

// Function to read input data
vector<vector<bool>> ReadData() {
    int num_left, num_right;
    cin >> num_left >> num_right;
    vector<vector<bool>> adj_matrix(num_left, vector<bool>(num_right));
    for (int i = 0; i < num_left; ++i) {
        for (int j = 0; j < num_right; ++j) {
            int bit;
            cin >> bit;
            adj_matrix[i][j] = (bit == 1);
        }
    }
    return adj_matrix;
}

// Test function for maxMatch
void test_maxMatch() {
    // Define a simple bipartite graph with an expected matching
    vector<vector<bool>> adj_matrix = {
        {1, 0, 0, 0, 1},
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0}
    };

    nx = adj_matrix.size();
    ny = adj_matrix[0].size();

    int result = maxMatch(adj_matrix);
    assert(result == 4); // Expected maximum matching

    // Check individual matches
    vector<int> expected_cx = {4, 1, 2, 3, 0};
    for (int i = 0; i < nx; ++i) {
        assert(cx[i] == expected_cx[i]);
    }

    cout << "All tests passed!" << endl;
}

int main() {
    // Assuming the functions from the previous code are already defined above this line
    
    vector<vector<bool>> adj_matrix = ReadData();
    nx = adj_matrix.size();
    ny = adj_matrix[0].size();
    int num = maxMatch(adj_matrix);

    for (int i = 0; i < nx; ++i) {
        if (cx[i] != -1) {
            cout << cx[i] + 1 << ' ';
        } else {
            cout << -1 << ' ';
        }
    }
    cout << endl;

    // Run the test function
    test_maxMatch();

    return 0;
}
