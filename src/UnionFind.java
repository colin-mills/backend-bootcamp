public class UnionFind {
    int[] parent;
    int[] rank;

    public UnionFind(int n) {
        rank = new int[n];
        parent = new int[n];

        for (int i = 0; i < n; i++) {
            parent[i] = i; //they will each start as their own set
        }
    }

    public void union (int a, int b) {
        int aRoot = find(a);
        int bRoot = find(b);

        if (aRoot == bRoot) return; //already same set

        if(rank[aRoot] > rank[bRoot]) {
            parent[bRoot] = aRoot;
        } else if (rank[aRoot] < rank[bRoot]) {
            parent[aRoot] = bRoot;
        } else {
            //pick one and increase rank
            parent[bRoot] = aRoot;
            rank[aRoot]++;
        }

    }

    public int find (int a) {
        int root = a;
        if (a != parent[a]) {
            //if not the parent, recurse
            root = find(parent[a]);
            //this path compression actually gets them to point to the top, not just grandparent
        }
        return root;
    }

    public boolean isConnected (int a, int b) {
        return find(a) == find(b);
    }

}
