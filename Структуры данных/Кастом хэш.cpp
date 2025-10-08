struct SplitMix64 {
    static uint64_t splitmix64(uint64_t x){
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

struct PairHash {
    size_t operator()(const pair<uint64_t,uint64_t>& p) const {
        SplitMix64 h;
        return h(p.first) ^ (h(p.second) + 0x9e3779b97f4a7c15ULL + (h(p.first)<<6) + (h(p.first)>>2));
    }
};

template<class... Ts>
struct TupleHash {
    size_t operator()(const tuple<Ts...>& t) const {
        return apply([](const auto&... xs){
            SplitMix64 h; size_t res = 0;
            ((res ^= h((uint64_t)xs) + 0x9e3779b97f4a7c15ULL + (res<<6) + (res>>2)), ...);
            return res;
        }, t);
    }
};
