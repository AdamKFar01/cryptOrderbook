
# CryptOrderbook

<hr height="15px" style="background-color: white;">


### **Introduction:**

- Main language & tools used: C++, CMake (4.3.4 used, 3.15 minimum)

- CryptOrderbook is an orderbook that connects to Kraken's live market data and builds a real-time crypto order book.

- The Websocket channel and stream used are Kraken (v2, newer version than v1 and recommended).


			{ The references and links can be found at the bottom }


<hr height="15px" style="background-color: white;">


## **Details:**

This project connects to Kraken's WebSocket API and keeps a live order book of bids and asks for BTC/USD. It reads the snapshot and update messages sent by Kraken, keeps the book updated in memory, and checks it against Kraken's checksum to make sure it is correct.


### **main.cpp**

Sets up the WebSocket connection to Kraken and subscribes to the book channel for BTC/USD. When a message comes in, it is parsed as JSON and passed to the order book as either a snapshot or an update.


### **include/OrderBook.h**

Defines the `OrderBook` class. It stores bids and asks in sorted maps, applies snapshots and updates, and calculates a checksum of the top 10 levels to compare against Kraken's checksum.


<hr height="15px" style="background-color: white;">


## **Requirements:**

- C++17 compiler
- CMake, 3.15 minimum (4.3.4 used)
- nlohmann_json: https://github.com/nlohmann/json
- IXWebSocket: https://github.com/machinezone/IXWebSocket
- ZLIB: https://github.com/luvit/zlib


<hr height="15px" style="background-color: white;">


## **How to run:**

1. Install the dependencies listed above.

2. Build the project with CMake:
```
mkdir build
cd build
cmake ..
cmake --build .
```

3. Run the program:
```
./cryptOrderbook
```

The program will connect to Kraken and start printing the live order book for BTC/USD.


<hr height="15px" style="background-color: white;">


## **References:**

- Websocket channel and stream choice: Kraken v2, advised to use as it is newer than v1
  - Link: https://docs.kraken.com/exchange/api-reference/spot-websocket-v2/book


- WebSocket used: IXWebSocket
  - Github repo link: https://github.com/machinezone/IXWebSocket/blob/master/ws/ws.cpp


- Other tools and resources links:
  - WebSocket cpp by zaphoyd: https://github.com/zaphoyd/websocketpp
  - nlohmann for json: https://github.com/nlohmann/json
  - Kraken checksum: https://docs.kraken.com/exchange/guides/websockets/book-checksum-v2
  - CRC32 from ZLIB: https://github.com/luvit/zlib/tree/master


<hr height="15px" style="background-color: white;">


## **License:**

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.





