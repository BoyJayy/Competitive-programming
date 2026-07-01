template<class T>
vector<vector<T>> all_permutations(vector<T> a) {
    sort(a.begin(), a.end());
    vector<vector<T>> ans;
    do {
        ans.push_back(a);
    } while (next_permutation(a.begin(), a.end()));
    return ans;
}
