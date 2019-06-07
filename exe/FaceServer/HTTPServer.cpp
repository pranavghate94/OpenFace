#include "HTTPServer.h"
#include "stdafx.h"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

HTTPServer::HTTPServer(utility::string_t url) : m_listener(url) {
	m_listener.support(methods::GET, std::bind(&HTTPServer::handle_get, this, std::placeholders::_1));
	m_listener.support(methods::POST, std::bind(&HTTPServer::handle_post, this, std::placeholders::_1));
}

void HTTPServer::handle_get(http_request message) {
	ucout << message.to_string() << std::endl;
	message.reply(status_codes::OK);
}

void HTTPServer::handle_post(http_request message) {
	ucout << message.to_string() << std::endl;
	message.reply(status_codes::OK);
}