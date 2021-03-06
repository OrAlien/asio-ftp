//
// request_handler.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "request_handler.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/log/trivial.hpp>
#include "mime_types.hpp"
#include "reply.hpp"
#include "request.hpp"
#include "connection.hpp"

namespace ftp {
	namespace server {

		request_handler::request_handler(const std::string& ftp_root)
			: m_strFtpRoot(ftp_root)
		{
		}

		void request_handler::handle_request(const std::string& req, connection *pConnection)
		{
			std::string rep;
			BOOST_LOG_TRIVIAL(info) << "receive message " << req;
			std::stringstream stream(req);
			std::string command;
			stream >> command;
			if (command == "USER") 
			{
				std::string username;
				stream >> username;
				m_strUserName = username;
				rep = "331 please input password";
				pConnection->WriteMessage(rep);
				return;
			}
			else if (command == "PASS") 
			{
				std::string password;
				stream >> password;
				m_strPwd = password;
				if (m_strUserName.length() == 0)
				{
					rep = "503 Login with USER first.";
					pConnection->WriteMessage(rep);
					return;
				}
				//if account and password is right
				if (m_strUserName == "a" && m_strPwd == "a")
				{
					rep = "230 User successfully logged in.";
					pConnection->WriteMessage(rep);
					return;
				}
				else
				{
					rep = "530 Not logged in, user or password incorrect!";
					//disconnected all 
					pConnection->WriteMessage(rep);
					return;
				}
			}
			else if (command == "PWD") 
			{
				//result = session.get_working_directory();
			}
			else if (command == "LIST") //��Ӧ����dir
			{
				rep = "150 Opening ASCII mode data connection for directory list.";
			//	session.list(boost::bind(&write_result, _1, write_message));
				pConnection->WriteMessage(rep);
				//rep = "226 Transfer complete.";
				//	session.list(boost::bind(&write_result, _1, write_message));
				//pConnection->WriteMessage(rep);
				return;
			}
			//
			else
			{
				// dummy instruction
				if (command == "NOOP")
				{
					rep = "200 OK";
				}
				else
				{
					rep = "502 Command not implemented.";
				}
			}






			//// Decode url to path.
			//std::string request_path;
			//if (!url_decode(req.uri, request_path))
			//{
			//	rep = reply::stock_reply(reply::bad_request);
			//	return;
			//}

			//// Request path must be absolute and not contain "..".
			//if (request_path.empty() || request_path[0] != '/'
			//	|| request_path.find("..") != std::string::npos)
			//{
			//	rep = reply::stock_reply(reply::bad_request);
			//	return;
			//}

			//// If path ends in slash (i.e. is a directory) then add "index.html".
			//if (request_path[request_path.size() - 1] == '/')
			//{
			//	request_path += "index.html";
			//}

			//// Determine the file extension.
			//std::size_t last_slash_pos = request_path.find_last_of("/");
			//std::size_t last_dot_pos = request_path.find_last_of(".");
			//std::string extension;
			//if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
			//{
			//	extension = request_path.substr(last_dot_pos + 1);
			//}

			//// Open the file to send back.
			//std::string full_path = doc_root_ + request_path;
			//std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
			//if (!is)
			//{
			//	rep = reply::stock_reply(reply::not_found);
			//	return;
			//}

			//// Fill out the reply to be sent to the client.
			//rep.status = reply::ok;
			//char buf[512];
			//while (is.read(buf, sizeof(buf)).gcount() > 0)
			//	rep.content.append(buf, is.gcount());
			//rep.headers.resize(2);
			//rep.headers[0].name = "Content-Length";
			//rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
			//rep.headers[1].name = "Content-Type";
			//rep.headers[1].value = mime_types::extension_to_type(extension);
		}

		/*bool request_handler::url_decode(const std::string& in, std::string& out)
		{
			out.clear();
			out.reserve(in.size());
			for (std::size_t i = 0; i < in.size(); ++i)
			{
				if (in[i] == '%')
				{
					if (i + 3 <= in.size())
					{
						int value = 0;
						std::istringstream is(in.substr(i + 1, 2));
						if (is >> std::hex >> value)
						{
							out += static_cast<char>(value);
							i += 2;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else if (in[i] == '+')
				{
					out += ' ';
				}
				else
				{
					out += in[i];
				}
			}
			return true;
		}*/

	} // namespace server
} // namespace http
