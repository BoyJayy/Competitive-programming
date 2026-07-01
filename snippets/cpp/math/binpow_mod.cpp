template <typename T, typename E>
T fpowmod(T a, E b, T m){
    T ans=1%m; a%=m;
    while(b>0){
        if(b & 1) ans=(ans*a)%m;
        a=(a*a)%m; b>>=1;
    }
    return ans;
}
