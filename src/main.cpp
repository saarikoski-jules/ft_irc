/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvisser <jvisser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 09:04:39 by jvisser       #+#    #+#                 */
/*   Updated: 2021/04/09 18:49:43 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "start_irc_server.h"

#include "server.h"
#include "logger.h"

int main(int argc, char** argv) {
    try {
        Logger::changeLoggingDestinationTo("./logs/latest.log");
        Logger::log(LogLevelInfo, "Program started");
        startIrcServerFromArguments(argc, argv);
    } catch (const ArgumentException& e) {
        Logger::log(LogLevelFatal, e.what());
    } catch (const ServerException& e) {
        Logger::log(LogLevelFatal, e.what());
    }
    Logger::log(LogLevelInfo, "Program ended gracefully");
    return (0);
}
