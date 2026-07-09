
# CryptoOrderbook 

----
## **Details:**

- CryptOrderbook is an orderbook that connects Kraken's live market data and build a real-time crypto order book.

- The Websocket channel and stream used are Kraken (v2, newer version than v1 and recommended).


			{ The references and links can be found at the bottom }


----
### **main.cpp**




----
### **include/OrderBook.h**



----

## **How to run:**



----

## **References:**

Websocket channel and stream choice:
Kraken v2. Advised to use as it is newer than v1
Link: https://docs.kraken.com/exchange/api-reference/spot-websocket-v2/book


-- WebSocket used: IXWebSocket
Github repo link: https://github.com/machinezone/IXWebSocket/blob/master/ws/ws.cpp

Other tools and resources links:
-- WebSocket cpp by zaphoyd: https://github.com/zaphoyd/websocketpp
-- nlohmann for json : https://github.com/nlohmann/json
-- Kraken checksum: https://docs.kraken.com/exchange/guides/websockets/book-checksum-v2
-- CRC32 from ZLIB: https://github.com/luvit/zlib/tree/master





