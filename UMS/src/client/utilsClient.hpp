/**
 * \file utilsClient.hpp
 * \brief This file contains client utils functions for VISHNU client Proxy classes
 * \author Daouda Traore (daouda.traore@sysfera.com)
 * \date February 2011
 */
#ifndef  _utilsClient_H_
#define  _utilsClient_H_

#include <string>
#include <cstring>
#include <iostream>
#include <sstream>

//EMF
#include <ecore.hpp> // Ecore metamodel
#include <ecorecpp.hpp> // EMF4CPP utils
#include "UMS_Data.hpp"

#include "SystemException.hpp"
#include "UMSVishnuException.hpp"

/**
 * \brief Function to print an error message and the line and file where this error has been occured
 * \fn  inline void errMsg(const std::string& msg)
 * \param msg to print
 */
inline void errMsg(const std::string& msg) {
  std::cerr << "Error line " << __LINE__-1  << " in file " << __FILE__ << " with message: ";
  std::cerr << std::endl;
  std::cerr << msg << std::endl;
}

/**
 * \brief Function to spread error message to C++ API, Python API, Web service API and command line program
 * \fn void raiseDietMsgException(const std::string& msg)
 * \param msg to spread
 */
void raiseDietMsgException(const std::string& msg);

/**
 * \brief Function to split the receiving message into error code and message error
 * \fn void raiseExceptionIfNotEmptyMsg(const std::string& msg)
 * \param msg to split
 */
void raiseExceptionIfNotEmptyMsg(const std::string& msg);

/**
 * \brief Function to check if a text is empty
 * \param text The text to check
 * \param compMsg The complementary message to print
 * \param execpetionType The type of exception to raise
 * \exception raises an exception on error
 */
void checkIfTextIsEmpty(const std::string& text, const std::string& compMsg, const int& execpetionType);

/**
 * \brief Function to check if an email is valid
 * \param mail The email to check
 * \return raises an exception on error
 */
void checkEmail(const std::string& mail);

/**
 * \brief Function to parse the EMF object
 * \param objectSerialized the EMF object serialized
 * \param object_ptr the object build with the objectSerialized
 * \param msgComp an exception message
 * \return raises an exception on error
 */
template<class T>
void parseEmfObject(const std::string& objectSerialized, T*& object_ptr, const std::string msgComp=std::string()) {

  object_ptr = NULL;
  try {
    //CREATE DATA MODEL
    T tmpObject;
    ecore::EPackage_ptr ecorePackage = tmpObject._eClass()->getEPackage();
    ecorecpp::MetaModelRepository::_instance()->load(ecorePackage);

    //Parse the model
    ecorecpp::parser::parser parser;
    object_ptr = parser.load(objectSerialized)->as< T >();
  }
  catch (std::exception& e) {
    throw SystemException(ERRCODE_INVDATA, msgComp);
  }

}
#endif
