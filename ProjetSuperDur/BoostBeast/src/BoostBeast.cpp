//
// Copyright (c) 2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

//------------------------------------------------------------------------------
//
// Example: HTTP server, small
//
//------------------------------------------------------------------------------

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/json.hpp> // Include Boost.JSON for JSON handling
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <span>
#include <string>

namespace beast = boost::beast;   // from <boost/beast.hpp>
namespace http = beast::http;     // from <boost/beast/http.hpp>
namespace net = boost::asio;      // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

namespace my_program_state
{
std::size_t request_count()
{
    static std::size_t count = 0;
    return ++count;
}

std::time_t now()
{
    return std::time(nullptr);
}
} // namespace my_program_state

class http_connection : public std::enable_shared_from_this<http_connection>
{
  public:
    http_connection(tcp::socket socket) : socket_(std::move(socket))
    {
    }

    // Initiate the asynchronous operations associated with the connection.
    void start()
    {
        read_request();
        check_deadline();
    }

  private:
    // The socket for the currently connected client.
    tcp::socket socket_;

    // The buffer for performing reads.
    static constexpr std::size_t ullBufferSize = 8192;
    beast::flat_buffer buffer_{ullBufferSize};

    // The request message.
    http::request<http::dynamic_body> request_;

    // The response message.
    http::response<http::dynamic_body> response_;

    // The timer for putting a deadline on connection processing.
    static constexpr int nDeadlineSeconds = 60;
    net::steady_timer deadline_{socket_.get_executor(), std::chrono::seconds(nDeadlineSeconds)};

    // Asynchronously receive a complete request message.
    void read_request()
    {
        auto self = shared_from_this();

        http::async_read(socket_, buffer_, request_, [self](beast::error_code err, std::size_t bytes_transferred) {
            boost::ignore_unused(bytes_transferred);
            if (!err)
            {
                self->process_request();
            }
        });
    }

    // Determine what needs to be done with the request message.
    void process_request()
    {
        response_.version(request_.version());
        response_.keep_alive(false);

        switch (request_.method())
        {
        case http::verb::get:
            response_.result(http::status::ok);
            response_.set(http::field::server, "Beast");
            create_response_get();
            break;

        case http::verb::post:
            response_.result(http::status::ok);
            response_.set(http::field::server, "Beast");
            create_response_post();
            break;

        default:
            // We return responses indicating an error if
            // we do not recognize the request method.
            response_.result(http::status::bad_request);
            response_.set(http::field::content_type, "text/plain");
            beast::ostream(response_.body())
                << "Invalid request-method '" << std::string(request_.method_string()) << "'";
            break;
        }

        write_response();
    }

    // Construct a response message based on the program state.
    void create_response_get()
    {
        if (request_.target() == "/count")
        {
            response_.set(http::field::content_type, "text/html");
            beast::ostream(response_.body())
                << "<html>\n"
                << "<head><title>Request count</title></head>\n"
                << "<body>\n"
                << "<h1>Request count</h1>\n"
                << "<p>There have been " << my_program_state::request_count() << " requests so far.</p>\n"
                << "</body>\n"
                << "</html>\n";
        }
        else if (request_.target() == "/time")
        {
            response_.set(http::field::content_type, "text/html");
            beast::ostream(response_.body())
                << "<html>\n"
                << "<head><title>Current time</title></head>\n"
                << "<body>\n"
                << "<h1>Current time</h1>\n"
                << "<p>The current time is " << my_program_state::now() << " seconds since the epoch.</p>\n"
                << "</body>\n"
                << "</html>\n";
        }
        else if (request_.target() == "/json")
        {
            response_.set(http::field::content_type, "application/json");

            // Créer un objet JSON simple
            boost::json::object root;
            root["message"] = "Bonjour depuis Boost.JSON";
            root["timestamp"] = my_program_state::now(); // Un entier, typiquement time_t

            boost::json::object test;
            const int nNumber1 = 42;
            const double fNumber2 = 3.14;
            test["number1"] = nNumber1;
            test["number2"] = fNumber2;

            root["test"] = test;

            root["list"] = {1, 0, 2};
            const double fValue = 42.99;
            root["object"] = {{"currency", "USD"}, {"value", fValue}};

            // Écrire le JSON dans le corps de la réponse
            beast::ostream(response_.body()) << boost::json::serialize(root);
        }
        else
        {
            response_.result(http::status::not_found);
            response_.set(http::field::content_type, "text/plain");
            beast::ostream(response_.body()) << "File not found\r\n";
        }
    }

    void create_response_post()
    {
        if (request_.target() == "/echo")
        {
            response_.set(http::field::content_type, "text/plain");

            // Copier le contenu du corps de la requête dans la réponse
            auto body_data = request_.body().data();
            for (auto const &buffer : body_data)
            {
                beast::ostream(response_.body()) << beast::make_printable(buffer);
            }
        }
        else if (request_.target() == "/json")
        {
            try
            {
                // Parser le JSON à partir du corps de la requête
                std::string body_string = boost::beast::buffers_to_string(request_.body().data());
                boost::json::value parsed = boost::json::parse(body_string);

                // Extraire les champs
                const boost::json::object &obj = parsed.as_object();

                auto user = boost::json::value_to<std::string>(obj.at("user"));
                auto password = boost::json::value_to<std::string>(obj.at("password"));
                const boost::json::object &nested = obj.at("object").as_object();
                auto value = boost::json::value_to<double>(nested.at("value"));
                // Pour l’exemple, on renvoie une réponse avec les infos extraites
                boost::json::object res_json;
                res_json["status"] = "ok";
                res_json["received_user"] = user;
                res_json["received_password"] = password;
                res_json["received_value"] = value;

                response_.result(http::status::ok);
                response_.set(http::field::content_type, "application/json");
                beast::ostream(response_.body()) << boost::json::serialize(res_json);
            }
            catch (const std::exception &e)
            {
                // Erreur de parsing ou champs manquants
                response_.result(http::status::bad_request);
                response_.set(http::field::content_type, "text/plain");
                beast::ostream(response_.body()) << "Erreur JSON: " << e.what();
            }
        }
        else
        {
            response_.result(http::status::not_found);
            response_.set(http::field::content_type, "text/plain");
            beast::ostream(response_.body()) << "POST endpoint not found\r\n";
        }
    }

    // Asynchronously transmit the response message.
    void write_response()
    {
        auto self = shared_from_this();

        response_.prepare_payload();

        http::async_write(socket_, response_, [self](beast::error_code err, std::size_t) {
            err = self->socket_.shutdown(tcp::socket::shutdown_send, err);

            self->deadline_.cancel();
        });
    }

    // Check whether we have spent enough time on this connection.
    void check_deadline()
    {
        auto self = shared_from_this();

        deadline_.async_wait([self](beast::error_code err) {
            if (!err)
            {
                // Close socket to cancel any outstanding operation.
                err = self->socket_.close(err);
            }
        });
    }
};

// "Loop" forever accepting new connections.
void http_server(tcp::acceptor &acceptor, tcp::socket &socket)
{
    acceptor.async_accept(socket, [&](beast::error_code err) {
        if (!err)
        {
            std::make_shared<http_connection>(std::move(socket))->start();
        }
        http_server(acceptor, socket);
    });
}

int main(int argc, char *argv[])
{
    try
    {
        std::span<char *> args(argv, argc);
        // Check command line arguments.
        if (args.size() != 3)
        {
            std::cerr << "Usage: " << args[0] << " <address> <port>\n";
            std::cerr << "  For IPv4, try:\n";
            std::cerr << "    receiver 0.0.0.0 80\n";
            std::cerr << "  For IPv6, try:\n";
            std::cerr << "    receiver 0::0 80\n";
            return EXIT_FAILURE;
        }

        auto const address = net::ip::make_address(args[1]);
        auto port = static_cast<unsigned short>(std::atoi(args[2]));

        net::io_context ioc{1};

        tcp::acceptor acceptor{ioc, {address, port}};
        tcp::socket socket{ioc};
        http_server(acceptor, socket);

        ioc.run();
    }
    catch (std::exception const &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (...)
    {
        return EXIT_FAILURE;
    }
}