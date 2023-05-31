#ifndef __NEAT_MAP_VECTOR_HPP__
#define __NEAT_MAP_VECTOR_HPP__

template <typename T, typename dType, typename T2>
class MapVector final {
public:
    MapVector();
    void push(T2 key, T value);
    T pop();
    T2 popKey();
    bool empty();
    int size();

private:
    std::map<T2, T&> map;
    std::vector<std::pair<T2, T>> queue;
};

#endif // __NEAT_MAP_VECTOR_HPP__
