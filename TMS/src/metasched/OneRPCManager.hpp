/*                                                                             #
# File        : OneRpcManager.hpp                                              #
# Copyright   : Rodrigue Chakode 2010 <rodrigue.chakode@gmail.com>             #
# Description : Class and header to request data from OpenNebula's XML-RPC API #
*/

#ifndef ONERPCMANAGER_HPP_
#define ONERPCMANAGER_HPP_

#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/girerr.hpp>
#include <xmlrpc-c/client_simple.hpp>
#include <openssl/evp.h>
#include <iomanip>
#include <fstream>
#include <vector>
#include <pwd.h>


// Class encapsulating a xmlrpc_c handler
class OneRPCManager : xmlrpc_c::clientSimple
{
public:

  OneRPCManager(std::string url = "http://localhost:2633/RPC2");
  ~OneRPCManager();

  /**
   * @brief initialize the encapsulated xmlrpc_c RPC handler
   */
  void
  initXmlRpcEnvironment(void);

  /**
   * @brief clear the encapsulated xmlrpc_c RPC handler
   */
  void
  finalizeXmlRpcEnvironment(void);

  /**
   * @brief Add a parameter for the subsequent RPC call
   * @param param The parameter as xmlrpc_c::value
   */
  void
  addParam (xmlrpc_c::value param);

  /**
   * @brief Add a string parameter
   * @param param The parameter as xmlrpc_c::value
   */
  void
  addParam(const std::string& param);

  /**
   * @brief Add a int parameter
   * @param param The parameter as xmlrpc_c::value
   */
  void
  addParam(int param);


  /**
   * @brief Add a boolean parameter
   * @param param The parameter as xmlrpc_c::value
   */
  void
  addParam(bool param);

  /**
   * @brief Execute the encapsulated xmlrpc_c request
   */
  void
  execute(void);

  /**
   * @brief Function to set the XML-RPC method to call
   * @param methodName The method name
   */
  void
  setMethod (std::string methodName) {this->method = methodName;}

  /**
   * @brief Return the last error message
   * @return a string
   */
  std::string
  getStringResult(void) const { return mstringResult; }

  /**
   * @brief Return the string used for authenticating again OpenNebula
   * @return
   */
  std::string
  getOneSecretAuthChain() const { return msecretOneAuthChain; }

  /**
   * @brief Return the string used for authenticating again OpenNebula as xmlrpc_c::value_string
   * @return
   */
  xmlrpc_c::value_string
  getOneSecretAuthChainRpcString(void) const { return static_cast<xmlrpc_c::value_string>(msecretOneAuthChain); }

  /**
   * @brief Tell whether the last RPC call failed or succeeded
   * @return bool
   */
  bool
  lastCallSucceeded(void) const { return this->mrpcCallSucceeded; }

  /**
   * @brief Return the output of the last RPC request as integer
   * @return int
   */
  int
  getIntResult(void) const { return this->mintResult; }


private:
  std::string moneRpcUrl;
  std::string msecretOneAuthChain;
  std::string method;
  xmlrpc_c::paramList mrequestParams;
  xmlrpc_env* mrpcEnv;
  int mintResult;
  bool mrpcCallSucceeded;
  std::string mstringResult;

  /**
   * @brief Return the string used for authenticating again OpenNebula
   * @return
   */
  void
  setSecretOneAuthChain(void);

  /**
   * @brief Split a one_auth chain to have the username and the password
   * @param oneAuthChain The one_auth chain in the form of username:password
   * @param username The resulting username
   * @param password The resulting password
   * @return The number of fields separated by colon ':'
   */
  int
  splitOneAuthChain(const std::string oneAuthChain, std::string& username, std::string& password);

  /**
   * @brief Read the one_auth file and to get the authentication chain
   * @param oneAuthChain The resulting auth chain
   * @return
   */
  int
  getOneAuthChain(std::string& oneAuthChain);

  /**
   * @brief sha1Digest
   * @param oneUserPass
   * @return
   */
  std::string
  sha1Digest(const std::string& oneUserPass);

};

#endif /* ONERPCMANAGER_HPP_ */
