/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   construct_reply.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/20 11:53:00 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/05/12 13:52:18 by jvisser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "construct_reply.h"

#include <vector>

#include "reply.h"
#include "connection.h"
#include "server.h"

std::string constructNoSuchChannelReply(const std::string& cliNick, const std::string& chanName) {
    std::string reply;
    std::vector<std::string> replyParams;

    replyParams.push_back(cliNick);
    replyParams.push_back(chanName);
    reply = ReplyFactory::newReply(ERR_NOSUCHCHANNEL, replyParams);
    return (reply);
}

std::string constructNoSuchNickReply(const std::string& cliNick, const std::string& targetNick) {
    std::string reply;
    std::vector<std::string> replyParams;

    replyParams.push_back(cliNick);
    replyParams.push_back(targetNick);
    reply = ReplyFactory::newReply(ERR_NOSUCHNICK, replyParams);
    return (reply);
}

std::string constructChanoPrivsNeededReply(
    const std::string& cliNick, const std::string& chanName) {
    std::string reply;
    std::vector<std::string> replyParams;

    replyParams.push_back(cliNick);
    replyParams.push_back(chanName);
    reply = ReplyFactory::newReply(ERR_CHANOPRIVSNEEDED, replyParams);
    return (reply);
}

std::string constructNeedMoreParamsReply(
	const std::string& cliNick, const std::string& command) {
	std::string reply;
	std::vector<std::string> replyParams;

	replyParams.push_back(cliNick);
	replyParams.push_back(command);
	reply = ReplyFactory::newReply(ERR_NEEDMOREPARAMS, replyParams);
	return (reply);
}

std::string constructNoTextToSendReply(
    const std::string& cliNick) {
    std::string reply;
    std::vector<std::string> replyParams;

    replyParams.push_back(cliNick);
    reply = ReplyFactory::newReply(ERR_NOTEXTTOSEND, replyParams);
    return (reply);
}

std::string constructNoRecipientReply(
    const std::string& cliNick, const std::string& command) {
    std::string reply;
    std::vector<std::string> replyParams;

    replyParams.push_back(cliNick);
    replyParams.push_back(command);
    reply = ReplyFactory::newReply(ERR_NORECIPIENT, replyParams);
    return (reply);
}

std::string constructCannotSendToChanReply(
    const std::string& senderNick, const std::string& chanName) {
    std::string reply;
    std::vector<std::string> replyParams;

    replyParams.push_back(senderNick);
    replyParams.push_back(chanName);
    reply = ReplyFactory::newReply(ERR_CANNOTSENDTOCHAN, replyParams);
    return (reply);
}

std::string constructNotRegisteredReply(const std::string& name) {
    std::string reply;
    std::vector<std::string> params;

    params.push_back(name);
    reply = ReplyFactory::newReply(ERR_NOTREGISTERED, params);
    return (reply);
}

std::string constructNewNickBroadcast(const Connection& connection) {
    const Client& client = connection.client;
    std::string reply(":" SERVERNAME " "
        "NICK "
        + client.nickName
        + " 1 "
        + client.userName + " "
        + client.hostName + " "
        SERVERTOKEN
        " + "
        ":" + client.realName + "\r\n");
    return (reply);
}

std::string constructNickChangeBroadcast(const std::string& oldNickName, const std::string& newNickName) {
    std::string reply(":" + oldNickName + " NICK :" + newNickName + "\r\n");
    return (reply);
}

std::string constructServerNickBroadcast(const std::vector<std::string> params) {
    std::string reply(":" SERVERNAME " "
        "NICK "
        + params[0]
        + " 1 "
        + params[2] + " "
        + params[3] + " "
        + params[4] + " "
        + params[5] + " "
        + ":" + params[6] + "\r\n");
    return (reply);
}
