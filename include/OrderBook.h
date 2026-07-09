// Created by Adam Farhat on
// -- v2 snapchat and update messages link: https://docs.kraken.com/exchange/api-reference/spot-websocket-v2/book

// -- Link to skeleton programs for update, snapshot, subscribing, unsubscribing, asks and bids can be found on
// the web in Kraken book v2 and other:
// Link: https://docs.kraken.com/exchange/api-reference/spot-websocket-v2/book

// Github repos used:
// -- IXWebSocket Machine Zone repo: https://github.com/machinezone/IXWebSocket/blob/master/ws/ws.cpp
// -- WebSocket cpp by zaphoyd: https://github.com/zaphoyd/websocketpp
// -- nlohmann for json : https://github.com/nlohmann/json
// -- Kraken checksum: https://docs.kraken.com/exchange/guides/websockets/book-checksum-v2


#ifndef CRYPTORDERBOOK_ORDERBOOK_H
#define CRYPTORDERBOOK_ORDERBOOK_H

#include <map>
#include <vector>
#include <cstdint>
#include <functional>

class OrderBook {
public:

    // Loads the full starting order book
    void applySnapshot(const std::vector<std::pair<double, double>>& bids,
                       const std::vector<std::pair<double, double>>& asks) {

        // Clear bids & asks
        bid_book.clear();
        ask_book.clear();

        // Update BID prices
        for (const auto& bid : bids) {
            double price = bid.first;
            double qty = bid.second;

            if (qty == 0) {                      // If qty is 0, remove this price level
                bid_book.erase(price);
            } else {                             // Otherwise, add or update this price level
                bid_book[price] = qty;
            }
        }

        // Update ASK prices
        for (const auto& ask : asks) {
            double price = ask.first;
            double qty = ask.second;

            if (qty == 0) {                     // If qty is 0, remove this price level
                ask_book.erase(price);
            } else {
                ask_book[price] = qty;          // Otherwise, add or update this price level
            }
        }

    }


    // Applies changes to the current order book
    void applyUpdate(const std::vector<std::pair<double, double>>& bids,
                     const std::vector<std::pair<double, double>>& asks) {

        // Update bid prices
        for (const auto& bid : bids) {
            double price = bid.first;
            double qty = bid.second;

            if (qty == 0) {                      // If qty is 0, remove this price level
                bid_book.erase(price);           // e.g. ignoring the bid if qty is 0 bcs it's futile
            } else {                             // Otherwise, add or update this price level
                bid_book[price] = qty;
            }
        }

        // Update ask prices
        for (const auto& ask : asks) {
            double price = ask.first;
            double qty = ask.second;

            if (qty == 0) {                     // If qty is 0, remove this price level
                ask_book.erase(price);
            } else {
                ask_book[price] = qty;          // Otherwise, add or update this price level
            }
        }
    }

    // Calculates checksum to check if the book is correct
    // -- Function not complete yet --
    uint32_t calculateChecksum() {

        return 0;
    }


private:
    // Bids sorted from highest price to lowest price
    // std::greater inverts the sorting order (which is originally low -> high)
    std::map<double, double, std::greater<double>> bid_book;

    // Asks sorted from lowest price to highest price
    std::map<double, double> ask_book;
};



#endif //CRYPTORDERBOOK_ORDERBOOK_H