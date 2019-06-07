#pragma once


#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"
#include <string>

#include "LandmarkExtractor.h"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class HTTPServer {
public:
	HTTPServer(){}
	HTTPServer(utility::string_t url);
	pplx::task<void> open() { return m_listener.open(); }
	pplx::task<void> close() { return m_listener.close();  }
private:
	void handle_get(http_request message);
	void handle_post(http_request message);
	void display_json(json::value const &jvalue, utility::string_t const & prefix);
	http_listener m_listener;
	LandmarkExtractor *extractor;
};