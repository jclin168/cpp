class RangeModule {
    typedef std::map<int, bool> MapType;
    MapType _map;
    
public:
    RangeModule() {
        _map.insert(_map.begin(), std::make_pair(std::numeric_limits<int>::lowest(), false));
    }
    void addRange(int left, int right) {
        insert(left, right, true);
    }
    bool queryRange(int left, int right) {
        auto last = _map.lower_bound(right);
        if (last == _map.begin()) return false;
        last = std::prev(last);
        if (last->first <= left && last->second != false)
            return true;
        return false;
    }
    void removeRange(int left, int right) {
        insert(left, right, false);
    }
private:
    void insert(int left, int right, int val) {
        _insert(left, right, val);
    }
    auto do_insert(int n) {
        std::pair<MapType::iterator, bool> result;
        result = _map.insert(std::make_pair(n, false));
        if (result.second) {
            if (result.first != _map.begin())
                result.first->second = std::prev(result.first)->second;
        }
        return result.first;
    }
    void remove_dup(auto i) {
        if (i == _map.end()) return;
        auto first = i;
        auto second = i;
        if (i != _map.begin()) {
            --first;
            if (first->second == second->second) {
                _map.erase(second);
                second = first;
            } else
                first = second;
        }
        ++second;
        if (second != _map.end() && first->second == second->second)
            _map.erase(second);
    }
    void _insert (int left, int right, int val) {
        if (left >= right) return;
        auto a = do_insert(left);
        auto b = do_insert(right);
        a->second = val;
        while (true) {
            auto c = std::next(a);
            if (c == b) break;
            _map.erase(c);
        }
        remove_dup(a);
        remove_dup(_map.lower_bound(right));
    }

};
