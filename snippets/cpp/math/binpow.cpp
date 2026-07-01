template <typename T, typename E>
T fpow(T a, E b){
    T ans=1;
    while(b>0){
        if(b & 1) ans*=a;
        a*=a; b>>=1;
    }
    return ans;
}
