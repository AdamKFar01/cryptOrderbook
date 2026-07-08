// Created by Adam Farhat on
// v2 snapchat and update messages link: https://docs.kraken.com/exchange/api-reference/spot-websocket-v2/book

// -- Link to skeleton programs for update, snapshot, subscribing, unsubscribing, asks and bids can be found on
// the web in Kraken book v2 and other:
// Link: https://docs.kraken.com/exchange/api-reference/spot-websocket-v2/book

// Github repos used:
// -- IXWebSocket Machine Zone repo: https://github.com/machinezone/IXWebSocket/blob/master/ws/ws.cpp
// -- WebSocket cpp by zaphoyd: https://github.com/zaphoyd/websocketpp
// -- nlohmann for json : https://github.com/nlohmann/json




#include "include/OrderBook.h"

#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXUserAgent.h>

#include <iostream>
#include <thread>
#include <chrono>
#include <nlohmann/json.hpp>


int main () {

    // Needed for windows, most likely won't be of use for mac
    ix::initNetSystem();

    // Creating WebSocket and address that will be used for connection
    ix::WebSocket webSocket;
    std::string url("wss://ws.kraken.com/v2");
    webSocket.setUrl(url);

    //Declare orderBook
    OrderBook orderBook;

    // Defining what should automatically happen in each upcoming scenario
    // adding webSocket and orderBook to the lambda capture list
    webSocket.setOnMessageCallback([&webSocket, &orderBook](const ix::WebSocketMessagePtr& msg) {

        if (msg->type == ix::WebSocketMessageType::Message)         // if a message arrives
        {
            std::cout << "Received message: " << msg->str << std::endl;

            try {

                nlohmann::json j = nlohmann::json::parse(msg->str); // Parse raw msg in json
                if (j.contains("method")) {
                    return;                                         // Subs/status response
                }
                if (!j.contains("channel")) {
                    return;                                         // Ignore msgs w/out channel
                }

                std::string channel = j["channel"].get<std::string>();
                if (channel == "heartbeat") {
                    return;                                         // Ignore heartbeat msgs
                }
                if (channel != "book") {
                    return;                                         // Book must be next
                }
                if (!j.contains("type")) {
                    return;                                         // Book needs type (snap or up)
                }

                std::string type = j["type"].get<std::string>();
                if (type != "snapshot" && type != "update") {
                    return;                                         // Ignore unknown book msgs
                }
                if (!j.contains("data") || !j["data"].is_array() || j["data"].empty()) {
                    return;                     // Kraken stores the book data inside data[0]
                }

                const auto& bookData = j["data"][0];
                auto parseSide = [](const nlohmann::json& side) {   // Converts bids/ask to
                    std::vector<std::pair<double, double>> levels;  // Vector<pair<price, qty>>

                    for (const auto& level : side) {
                        if (!level.contains("price") || !level.contains("qty")) {
                            continue;       // Skip invalid price levels
                        }

                        double price = level["price"].get<double>();
                        double qty = level["qty"].get<double>();
                        levels.emplace_back(price, qty);
                    }
                    return levels;
                };

                // Parse bids if they exist
                std::vector<std::pair<double, double>> bids =
                        bookData.contains("bids") ? parseSide(bookData["bids"]):std::vector<std::pair<double, double>>{};
                // Parse asks if they exist
                std::vector<std::pair<double, double>> asks =
                        bookData.contains("asks") ? parseSide(bookData["asks"]):std::vector<std::pair<double, double>>{};
                // Apply full snapshot or incremental update
                if (type == "snapshot") {
                    orderBook.applySnapshot(bids, asks);
                }
                else {
                    orderBook.applyUpdate(bids, asks);
                }
            }
            catch (const std::exception& e) {           // Catch json parsing or msg handling errors
                std::cerr << "Message handling error: " << e.what() << std::endl;
            }
            std::cout << "> " << std::flush;
        }

        else if (msg->type == ix::WebSocketMessageType::Open)   // If a connection opens
        {
            std::cout << "Connection established!" << std::endl;

            nlohmann::json subscribeMsg = {
                    {"method", "subscribe"},
                    {"params", {
                                       {"channel", "book"},
                                       {"symbol", {"BTC/USD"}},
                                       {"depth", 10}
                               }}
            };

            // Check subscription status
            webSocket.send(subscribeMsg.dump());

            std::cout << "> " << std::flush; // Display a prompt
        }
        else if (msg->type == ix::WebSocketMessageType::Error)  // If an error occurs
        {
            // Maybe SSL is not configured properly
            std::cout << "Connection error: " << msg->errorInfo.reason << std::endl;
            std::cout << "> " << std::flush; // flush forces the cout output to show immediately
        }

    }
    );

    webSocket.start();                  // Starting session

    //webSocket.send("Yo");               // A message is sent - only needed in project beginning
    std::cout << "> " << std::flush;    // Display a prompt
    std::string text;                   // A string of text


    // Infinite loop to control exit time and avoid crash
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    /*
    while (std::getline(std::cin, text)) {
        webSocket.send(text);
        std::cout << "> " << std::flush;
    }

    // This loop reads what is typed in the terminal, line by line
    // And sends each line as a new message
    // Not needed because we will be reading stuff from Kraken, not user input
    */

    return 0;

}
