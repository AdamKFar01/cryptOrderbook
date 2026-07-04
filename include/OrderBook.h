// Created by Adam Farhat

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
        // Clear bids and asks
        bid_book.clear();
        ask_book.clear();

        // Update bid prices
        for (const auto& bid : bids) {
            double price = bid.first;
            double qty = bid.second;

            if (qty == 0) {                      // If qty is 0, remove this price level
                bid_book.erase(price);
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


    // Applies changes to the current order book
    void applyUpdate(const std::vector<std::pair<double, double>>& bids,
                     const std::vector<std::pair<double, double>>& asks) {

        // Update bid prices
        for (const auto& bid : bids) {
            double price = bid.first;
            double qty = bid.second;

            if (qty == 0) {                      // If qty is 0, remove this price level
                bid_book.erase(price);
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
    uint32_t calculateChecksum() {
        // empty for now
        return 0;
    }


private:
    // Bids sorted from highest price to lowest price
    std::map<double, double, std::greater<double>> bid_book;

    // Asks sorted from lowest price to highest price
    std::map<double, double> ask_book;
};

#endif //CRYPTORDERBOOK_ORDERBOOK_H