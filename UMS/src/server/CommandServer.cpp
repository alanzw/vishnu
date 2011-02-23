/**
* \file CommandServer.hpp
* \brief This file implements the Class which manipulates Commands on server side.
* \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
* \date 31/01/2011
*/

#include "CommandServer.hpp"

/**
* \brief Constructor
* \fn CommandServer(std::string cmd, SessionServer session)
* \param cmd The cmd launched by the user
* \param session The object which encapsulates session data
*/
CommandServer::CommandServer(std::string cmd, SessionServer session):
mcommand(cmd), msessionServer(session) {
  DbFactory factory;
  mdatabaseVishnu = factory.getDatabaseInstance();
}

/**
* \brief Function to get the command description
* \fn    std::string getCommand()
* \return the current command
*/
std::string
CommandServer::getCommand() {
  return mcommand;
}

/**
* \brief Function to record the command on the database
* \fn int save()
* \return raises an exception on error
*/
int
CommandServer::record(std::string cmdType,
                      std::string startTime,
                      std::string endTime) {

  std::string sqlCmd = std::string("insert into command (vsession_numsessionid, starttime,\
  endtime, description, ctype values (");

  std::cout << "SQL COMMAND:" << sqlCmd;

  try {

    sqlCmd.append(msessionServer.getAttribut("WHERE \
    sessionkey='"+msessionServer.getData().getSessionKey()+"'"), "numsessionid");

    sqlCmd.append(","+startTime+ ","+endTime+", "+mcommand+","+cmdType+")");

    mdatabaseVishnu->process(sqlCmd.c_str());
  }
  catch (VishnuException& e) {
    throw;
  }


	return 0;
}

/**
* \brief Destructor
* \fn    ~CommandServer()
*/
CommandServer::~CommandServer() {
}


