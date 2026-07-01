template <typename T>
int longest_subarray_sum_leq_S(const vector<T>& a, T S){
    int ans=0,l=0;
    T s=0;
    for(int r=0;r<(int)a.size();r++){
        s+=a[r];
        while(s>S && l<=r){ s-=a[l++]; }
        ans=max(ans, r-l+1);
    }
    return ans;
}
