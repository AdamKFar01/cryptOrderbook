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
#include <string>

//
struct DataValues {
    double price;
    double qty;
    std::string price_str;
    std::string qty_str;
};


class OrderBook {
public:

    // Loads the full starting order book
    void applySnapshot(const std::vector<DataValues>& bids,
                       const std::vector<DataValues>& asks) {

        // Clear bids & asks
        bid_book.clear();
        ask_book.clear();


        // Update BID prices
        for (const auto& bid : bids) {

            //double price = bid.first;
            //double qty = bid.second;

            if (bid.qty == 0) {                      // If qty is 0, remove this price level
                bid_book.erase(bid.price);
            } else {                             // Otherwise, add or update this price level
                bid_book[bid.price] = bid;
            }
        }


        // Update ASK prices
        for (const auto& ask : asks) {

            //double price = ask.first;
            //double qty = ask.second;

            if (ask.qty == 0) {                     // If qty is 0, remove this price level
                ask_book.erase(ask.price);
            } else {
                ask_book[ask.price] = ask;          // Otherwise, add or update this price level
            }
        }

    }


    // Applies changes to the current order book
    void applyUpdate(const std::vector<DataValues>& bids,
                     const std::vector<DataValues>& asks) {


        // Update bid prices
        for (const auto& bid : bids) {

            //double price = bid.price;
            //double qty = bid.second;

            if (bid.qty == 0) {                      // If qty is 0, remove this price level
                bid_book.erase(bid.price);           // e.g. ignoring the bid if qty is 0 bcs it's futile
            } else {                             // Otherwise, add or update this price level
                bid_book[bid.price] = bid;
            }
        }


        // Update ask prices
        for (const auto& ask : asks) {
            //double price = ask.first;
            //double qty = ask.second;

            if (ask.qty == 0) {                     // If qty is 0, remove this price level
                ask_book.erase(ask.price);
            } else {
                ask_book[ask.price] = ask;          // Otherwise, add or update this price level
            }
        }
    }

    // Calculates checksum to check if the book is correct
    // -- Function not complete yet --
    uint32_t calculateChecksum() {
        // to fill

        return 0;
    }


private:
    // Bids sorted from highest price to lowest price
    // std::greater inverts the sorting order (which is originally low -> high)
    // the order is map<key, value>
    std::map<double, DataValues, std::greater<double>> bid_book;


    // Asks sorted from lowest price to highest price
    std::map<double, DataValues> ask_book;
};



#endif //CRYPTORDERBOOK_ORDERBOOK_H