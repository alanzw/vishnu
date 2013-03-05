/**
 * \file UtilsProxy.cpp
 * \brief This file contains the VISHNU UtilsProxy class.
 * \author Daouda Traore (daouda.traore@sysfera.com)
 * \date February 2011
 */
#include "UtilsProxy.hpp"

#include <string>

#include "SystemException.hpp"
#include "DIET_client.h"

/**
 * \fn  UtilsProxy()
 * \brief Constructor, default constructor
 */
UtilsProxy::UtilsProxy() {
  mcfg  = NULL;
  margc = 0;
  margv = NULL;
}

/**
 * \fn UtilsProxy(char* cfg,
 *                int argc,
 char** argv)
 * \param cfg The SYSFERA-DS configuration file
 * \param argc The number of arguments of the program
 * \param argv The list of arguments
 * \brief Constructor
 */
UtilsProxy::UtilsProxy(char* cfg, int argc, char** argv):
  mcfg(cfg), margc(argc), margv(argv) {
}

/**
 * \fn UtilsProxy(const std::string& filePath)
 * \param filePath The SYSFERA-DS configuration file
 * \brief Constructor
 */
UtilsProxy::UtilsProxy(const std::string& filePath):
  mfilePath(filePath) {
  mcfg = NULL;
  margc = 0;
  margv = NULL;
}

/**
 * \brief Function to initialize the SYSFERA-DS configuration
 * \fn  int initialize()
 * \return 0 or GRPC code if success else raises an exception if error
 */
int
UtilsProxy::initialize() {
  int res = 0;
  try {
    res = diet_initialize(mcfg, margc, margv);
  } catch (...) {
    throw SystemException(ERRCODE_DIET, "Internal communication exception");
  }
  if (res == -1) {
    throw SystemException(ERRCODE_DIET, "Bus initialization failure");
  }
  return res;
}


/**
 * \fn ~UtilsProxy()
 * \brief Destructor, raises an exception on error
 */
UtilsProxy::~UtilsProxy() {}
