template<class T>
void sort_unique(vector<T>& a) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
}
