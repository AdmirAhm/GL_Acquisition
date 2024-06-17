#pragma once
#include "td/String.h"

static td::String _message;
int nMeasures = 0;
bool close_server = true;
bool isconnected = false;
td::String port = "44201";
td::String ip = "192.nesto";

std::mutex _message_mutex;

void setMessage(td::String message) {
	_message_mutex.lock();
	_message = message;
	_message_mutex.unlock();
}

td::String getMessage() {
	_message_mutex.lock();
	td::String message = _message;
	_message_mutex.unlock();
	return message;
}