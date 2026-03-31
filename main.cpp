#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <climits>

using namespace std;

const int MAXN = 1005;
int grid[MAXN][MAXN];
int dist[MAXN][MAXN];
int n, m;

// Direction vectors for moving up, down, left, right
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

struct Point {
    int x, y;
};

// BFS to find shortest distances from a starting point to all reachable points
void bfs(int startX, int startY) {
    // Initialize all distances to -1 (unreachable)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = -1;
        }
    }

    queue<Point> q;
    q.push({startX, startY});
    dist[startX][startY] = 0;

    while (!q.empty()) {
        Point curr = q.front();
        q.pop();

        // Try all 4 directions
        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            // Check bounds
            if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
                continue;
            }

            // Check if already visited
            if (dist[nx][ny] != -1) {
                continue;
            }

            // Check if it's a blocked building (1)
            if (grid[nx][ny] == 1) {
                continue;
            }

            // Valid move
            dist[nx][ny] = dist[curr.x][curr.y] + 1;
            q.push({nx, ny});
        }
    }
}

int main() {
    cin >> n >> m;

    int startX = -1, startY = -1;
    int homeX = -1, homeY = -1;
    vector<Point> shops;

    // Read the grid and find special positions
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];

            if (grid[i][j] == 2) {
                startX = i;
                startY = j;
            } else if (grid[i][j] == 3) {
                homeX = i;
                homeY = j;
            } else if (grid[i][j] == 4) {
                shops.push_back({i, j});
            }
        }
    }

    // BFS from starting position
    bfs(startX, startY);

    // Store distances from start to each shop
    vector<int> distToShops;
    for (const auto& shop : shops) {
        if (dist[shop.x][shop.y] != -1) {
            distToShops.push_back(dist[shop.x][shop.y]);
        } else {
            distToShops.push_back(INT_MAX);
        }
    }

    // Find minimum total distance
    int minDist = INT_MAX;

    for (size_t i = 0; i < shops.size(); i++) {
        if (distToShops[i] == INT_MAX) {
            continue; // Can't reach this shop
        }

        // BFS from this shop to find distance to home
        bfs(shops[i].x, shops[i].y);

        if (dist[homeX][homeY] != -1) {
            int totalDist = distToShops[i] + dist[homeX][homeY];
            minDist = min(minDist, totalDist);
        }
    }

    cout << minDist << endl;

    return 0;
}
