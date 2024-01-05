#include "pch.h"
#include "CommunicationManager.h"
#include <sstream>

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

CommunicationManager::CommunicationManager(){
    // Set logging to be pretty verbose (everything except message payloads)
    client_.set_access_channels(websocketpp::log::alevel::all);
    client_.clear_access_channels(websocketpp::log::alevel::frame_payload);

    // Initialize ASIO
    client_.init_asio();

    // Register our message handler
    client_.set_message_handler(bind(&CommunicationManager::on_message, this, ::_1, ::_2));
    this->data = { 0,0,0,0 };
}

void CommunicationManager::createConnection(const std::string& uri) {
    // Create connection
    websocketpp::lib::error_code ec;
    connection_ptr_ = client_.get_connection(uri, ec);
    if (ec) {
        std::cout << "Could not create connection because: " << ec.message() << std::endl;
        return;
    }
}

void CommunicationManager::run() {
    // Note that connect here only requests a connection. No network messages are
    // exchanged until the event loop starts running in the next line.
    client_.connect(connection_ptr_);

    // Start the ASIO io_service run loop
    // this will cause a single connection to be made to the server. client_.run()
    // will exit when this connection is closed.
    client_.run();
}

void CommunicationManager::on_message(websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << "on_message called with hdl: " << hdl.lock().get()
        << " and message: " << msg->get_payload()
        << std::endl;

    websocketpp::lib::error_code ec;

    client_.send(hdl, this->messageFormater(), msg->get_opcode(), ec);
    if (ec) {
        std::cout << "Echo failed because: " << ec.message() << std::endl;
    }
}

void CommunicationManager::startThread(){
    this->webSocketThread = std::thread(&CommunicationManager::run, this);
}

void CommunicationManager::stopThread() {
    this->webSocketThread.join();
}

void CommunicationManager::updateData(Wheel::wheelData newData) {
    this->data = newData;
}

std::string CommunicationManager::messageFormater() {
    std::stringstream trame;
    int direction, speed, x, y;
    double percentages[7] = { 0.05, 0.1, 0.2, 0.4, 0.6, 0.8, 1.0 };
    x = 0;
    y = 0;
    direction = (int)(this->data.angle * (255.0 / 0.34) + 127);
    if (direction > 255) {
        direction = 255;
    }
    else if (direction < 0) {
        direction = 0;
    }
    speed = (int)((-this->data.brake + this->data.throttle) * (255.0/2.0) * percentages[this->data.gear - 1] + 127);

    trame << "D" << direction << "P" << speed << "X" << this->data.x << "Y" << this->data.y;
    return trame.str();
}