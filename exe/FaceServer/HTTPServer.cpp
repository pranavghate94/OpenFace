#include "HTTPServer.h"
#include "stdafx.h"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

HTTPServer::HTTPServer(utility::string_t url) : m_listener(url) {
	m_listener.support(methods::GET, std::bind(&HTTPServer::handle_get, this, std::placeholders::_1));
	m_listener.support(methods::POST, std::bind(&HTTPServer::handle_post, this, std::placeholders::_1));
	extractor = new LandmarkExtractor();
	extractor->SetupExtractor();
}

void HTTPServer::display_json(json::value const & jvalue, utility::string_t const & prefix) {
	std::wcout << prefix << jvalue.serialize() << std::endl;
}

void HTTPServer::handle_get(http_request message) {
	ucout << message.to_string() << std::endl;
	message.reply(status_codes::OK);
}

// Gets the JSON Value from Post Message Body and sends it to Landmark Extractor for extracting Feature Points;
void HTTPServer::handle_post(http_request message) {
	ucout << "Handling POST Request" << std::endl;
	message.extract_json().then([this](pplx::task<json::value> json_message) {
		try {
			auto const & jvalue = json_message.get();
			auto encoded_string = jvalue.at(conversions::to_string_t("image")).as_string();
			extractor->SetImage(conversions::to_utf8string(encoded_string));
			extractor->ExtractFeatures();
		}
		catch (http_exception const & e) {
			std::wcout << e.what() << std::endl;
		}
	}).wait();
	message.reply(status_codes::OK);
}