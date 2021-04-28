/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.h                                          :+:    :+:             */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 10:00:11 by jvisser       #+#    #+#                 */
/*   Updated: 2021/04/27 12:17:24 by jules        ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H_
#define SERVER_H_

#include <string>
#include <vector>
#include <queue>
#include <cinttypes>
#include <exception>
#include <map>
#include <utility>

#include "socket.h"
#include "connection.h"
#include "message_parser.h"
#include "iserver_action.h"
#include "channel.h"

class Server {
 public:
    Server(const uint16_t& port, const std::string& password);
    Server(Connection* startingServer, const uint16_t& port, const std::string& password);
    ~Server();
    void sendAuthenticationTo(const int& fd, const std::string& password);
    void run();
    void sendMessage(const int& fd, const std::string& message);
    void sendReplyToClient(const int& clientFd, const std::string& message);
    Connection* getClientByNick(const std::string& nick);
    void acceptNewConnection(const int& fd);
    void deleteConnection(const int& fd);
    Connection* getConnectionByFd(const int& fd);
    bool nicknameExists(const std::string& nickName);
    bool usernameExists(const std::string& userName);
    void addNewAction(IServerAction* action);
    Channel* createNewChannel(const std::string& name, const int& clientFd);
    Channel* findChannel(const std::string& name);
    void delayFirstAction();
 protected:
    std::map<const int, Connection> connections;
 private:
    Server();
    std::queue<IServerAction*> actions;
    std::queue<IServerAction*> delayedActions;
    std::map<std::string, Channel> channels;
    Socket serverSocket;
    MessageParser parser;
    void validatePassword(std::string const& password) const;
    void openSocket(const uint16_t& port);
    void listenOnSocket();
    void handleAction();
};

class ServerException : public std::exception {
 public:
    ServerException(std::string const& what, const bool& fatal);
    ~ServerException() throw();
    const bool& isFatal() const;
    const char* what() const throw();
 private:
    const bool fatal;
    const std::string message;
    std::string fullMessage;
};

#endif  // SERVER_H_
