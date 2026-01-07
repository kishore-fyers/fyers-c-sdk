cmake_minimum_required(VERSION 3.15)

# Example: Authentication
add_executable(auth_example auth_example.c)
target_link_libraries(auth_example fyers-api-c)

# Example: Trading
add_executable(trading_example trading_example.c)
target_link_libraries(trading_example fyers-api-c)

# Example: Market Data
add_executable(market_data_example market_data_example.c)
target_link_libraries(market_data_example fyers-api-c)

# Example: Data WebSocket
add_executable(data_ws_example data_ws_example.c)
target_link_libraries(data_ws_example fyers-api-c)

# Example: Order WebSocket
add_executable(order_ws_example order_ws_example.c)
target_link_libraries(order_ws_example fyers-api-c)

