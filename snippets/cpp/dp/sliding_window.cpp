long long longest_subarray_sum_leq_S(const vector<long long>& a,long long S){
    long long ans=0,s=0; int l=0;
    for(int r=0;r<(int)a.size();r++){
        s+=a[r];
        while(s>S && l<=r){ s-=a[l++]; }
        ans=max(ans, (long long)r-l+1);
    }
    return ans;
}
