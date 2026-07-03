// Created by Adam Farhat on 03/07/2026.
// v2 snapchat and update messages link: https://docs.kraken.com/exchange/api-reference/spot-websocket-v2/book


#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXUserAgent.h>
#include <iostream>
#include <thread>
#include <chrono>

int main () {

    // Needed for windows, probably won't be of use for mac
    ix::initNetSystem();

    // Creating WebSocket and address that will be used for connection
    ix::WebSocket webSocket;
    std::string url("wss://ws.kraken.com/v2");
    webSocket.setUrl(url);

    // Defining what should automatically happen in each upcoming scenario
    webSocket.setOnMessageCallback([](const ix::WebSocketMessagePtr& msg) {

        if (msg->type == ix::WebSocketMessageType::Message)     // if a message arrives
        {
            std::cout << "Received message: " << msg->str << std::endl;
            std::cout << "> " << std::flush;
        }
        else if (msg->type == ix::WebSocketMessageType::Open)   // if a connection opens
        {
            std::cout << "Connection established!" << std::endl;
            std::cout << "> " << std::flush;
        }
        else if (msg->type == ix::WebSocketMessageType::Error)  // If an error occurs
        {
            // Maybe SSL is not configured properly
            std::cout << "Connection error: " << msg->errorInfo.reason << std::endl;
            std::cout << "> " << std::flush; // flush forces the cout output to show immediately
        }

    }
    );

    webSocket.start();                  // A session is started
    //webSocket.send("Yo");               // A message is sent
    std::cout << "> " << std::flush;    // Display a prompt
    std::string text;                   // A string of text


    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    /*
    // This loop reads what is typed in the terminal, line by line
    // And sends each line as a new message
    // Not needed because we will be reading stuff from Kraken, not user input
    while (std::getline(std::cin, text)) {

        webSocket.send(text);
        std::cout << "> " << std::flush;

    }
    */

    return 0;

}
