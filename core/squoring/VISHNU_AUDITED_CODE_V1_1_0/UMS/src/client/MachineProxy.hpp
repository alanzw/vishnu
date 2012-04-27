/**
 * \file MachineProxy.hpp
 * \brief This file contains the VISHNU MachineProxy class.
 * \author Daouda Traore (daouda.traore@sysfera.com)
 * \date February 2011
 */
#ifndef _MACHINE_PROXY_H_
#define _MACHINE_PROXY_H_

#include <string>
#include <iostream>

#include "SessionProxy.hpp"
#include "Machine.hpp"

/**
 * \class MachineProxy 
 * \brief MachineProxy class implementation 
 */
class MachineProxy
{

  public:

    /**
     * \fn MachineProxy(const UMS_Data::Machine& machine,
     *                       const SessionProxy& session)
     * \param machine The object which encapsulates the information of the machine 
     * \param session The object which encapsulates the session information (ex: identifier of the session)
     * \brief Constructor, raises an exception on error
     */
    MachineProxy(const UMS_Data::Machine& machine, const SessionProxy& session);
    /**
     * \brief Function to add a new machine 
     * \fn  int add()
     * \return raises an exception on error
     */
    int add();
    /**
     * \brief Function to update machine description 
     * \fn  int update()
     * \return raises an exception on error
     */
    int update();
    /**
     * \brief Function to remove a machine 
     * \fn  int deleteMachine()
     * \return raises an exception on error
     */
    int deleteMachine();
    /**
     * \brief Function get SessionProxy object which contains the VISHNU session identifier 
     * \fn SessionProxy getSessionProxy() 
     * \return a SessionProy object which contains the VISHNU session information 
     * \return raises an exception on error
     */
    SessionProxy getSessionProxy();
    /**
     * \brief Function get machine information 
     * \fn  UMS_Data::Machine getData()
     * \return Machine object encapsulates the information of the machine 
     * \return raises an exception on error
     */ 
    UMS_Data::Machine getData();
    /**
     * \fn ~MachineProxy()
     * \brief Destructor, raises an exception on error
     */
    ~MachineProxy();

  private:

    /////////////////////////////////
    // Attributes
    /////////////////////////////////

    /**
     * \brief The object which encapsulates the machine information 
     */
    UMS_Data::Machine mmachine;
    /**
     * \brief The SessionProxy object containing the encrypted identifier of the session
     *  generated by VISHNU
     */
    SessionProxy msessionProxy;

};
#endif