// FaceServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "HTTPServer.h"
#include "LandmarkExtractor.h"


#define LOG(msg) \
    std::cout << __FILE__ << "(" << __LINE__ << "): " << msg << std::endl 

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

std::unique_ptr<HTTPServer> g_http;

void on_initialize(const string_t& address) {
	uri_builder uri(address);
	auto addr = uri.to_uri().to_string();
	g_http = std::unique_ptr<HTTPServer>(new HTTPServer(addr));
	g_http->open().wait();
	std::cout << "Listening for Requests!" << std::endl;
	return;
}

void on_shutdown() {
	g_http->close().wait();
	return;
}

int wmain(int argc, wchar_t* argv[]) {

	std::string port = "3030";
	std::string address = "http://localhost:";
	address.append(port);
	on_initialize(utility::conversions::to_string_t(address));
	std::cout << "Press Enter to Exit" << std::endl;
	std::string line;
	std::getline(std::cin, line);
	on_shutdown();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
