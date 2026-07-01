vector<Tree*> roots;

roots.push_back(new Segtree(0, n));

void add(int k, int x, int v) {
    Tree *root = new Tree(*roots[v]);
    root->add(k, x);
    roots.push_back(root);
}