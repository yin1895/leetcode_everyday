#include <bits/stdc++.h>
using namespace std;

struct Item {
    int price, shop, movie;
    bool operator<(const Item& other) const {
        if (price != other.price) return price < other.price;
        if (shop != other.shop) return shop < other.shop;
        return movie < other.movie;
    }
};

class MovieRentingSystem {
private:
    unordered_map<int, set<Item>> available; // movie -> 可租集合
    set<Item> rented;                        // 已租集合
    unordered_map<long long, int> priceMap;  // (shop,movie) -> price
    
    long long encode(int shop,int movie){
        return (long long)shop * 100000 + movie;
    }

public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        for (auto &e : entries) {
            int shop = e[0], movie = e[1], price = e[2];
            Item it{price, shop, movie};
            available[movie].insert(it);
            priceMap[encode(shop,movie)] = price;
        }
    }
    
    vector<int> search(int movie) {
        vector<int> ans;
        auto &s = available[movie];
        int cnt = 0;
        for (auto it = s.begin(); it != s.end() && cnt < 5; ++it, ++cnt) {
            ans.push_back(it->shop);
        }
        return ans;
    }
    
    void rent(int shop, int movie) {
        int price = priceMap[encode(shop,movie)];
        Item it{price, shop, movie};
        available[movie].erase(it);
        rented.insert(it);
    }
    
    void drop(int shop, int movie) {
        int price = priceMap[encode(shop,movie)];
        Item it{price, shop, movie};
        rented.erase(it);
        available[movie].insert(it);
    }
    
    vector<vector<int>> report() {
        vector<vector<int>> ans;
        int cnt = 0;
        for (auto it = rented.begin(); it != rented.end() && cnt < 5; ++it, ++cnt) {
            ans.push_back({it->shop, it->movie});
        }
        return ans;
    }
};
