#pragma once

#include "InputInterfacingUWP.h"

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <iostream>
#include <thread>

typedef websocketpp::client<websocketpp::config::asio_client> client;
typedef client::connection_ptr connection_ptr;
typedef client::message_ptr message_ptr;

class CommunicationManager {
public:
    CommunicationManager();
    void run();
    void on_message(websocketpp::connection_hdl hdl, message_ptr msg);
    void createConnection(const std::string& uri);
    void startThread();
    void stopThread();
    void updateData(Wheel::wheelData newData);
private:
    std::string messageFormater();

    client                 client_;
    connection_ptr         connection_ptr_;
    Wheel::wheelData       data;
    std::string            uri;
    std::thread            webSocketThread;

};