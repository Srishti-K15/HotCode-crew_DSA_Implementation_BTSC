#include <iostream>
#include <string>
#include <map>

using namespace std;

struct Stock {
    string id;
    float price;
    int timestamp;
};

map<string, Stock> stockMap;

void createStock(const string& stockId, float price, int timestamp) {
    Stock stock;
    stock.id = stockId;
    stock.price = price;
    stock.timestamp = timestamp;
    stockMap[stockId] = stock;
    cout << "Stock created: " << stockId << " Price: " << price << " Timestamp: " << timestamp << endl;
}

void updateStock(const string& stockId, float newPrice, int newTimestamp) {
    if (stockMap.find(stockId) != stockMap.end()) {
        stockMap[stockId].price = newPrice;
        stockMap[stockId].timestamp = newTimestamp;
        cout << "Stock updated: " << stockId << " Price: " << newPrice << " Timestamp: " << newTimestamp << endl;
    } else {
        cout << "Stock not found: " << stockId << endl;
    }
}

void getAllStocks() {
    for (auto& stock : stockMap) {
        cout << "Stock: " << stock.second.id << " Price: " << stock.second.price << endl;
    }
}

int main() {
    createStock("AAPL", 2495.8, 163704);
    createStock("MSFT", 2000.0, 152758);
    

    getAllStocks();

    updateStock("AAPL", 2630.14, 142115);
    updateStock("MSFT", 2100.0, 152759);

    getAllStocks();

    return 0;
}