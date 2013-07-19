#include "sessionUtils.hpp"


//  Boost archives
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

// To serialize a std::list
#include <boost/serialization/list.hpp>
#include <boost/serialization/nvp.hpp>

#include <cstdlib>
#include <iostream>
#include <boost/interprocess/sync/file_lock.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "UMSVishnuException.hpp"
#include "VishnuException.hpp"
#include "UserException.hpp"

namespace bfs = boost::filesystem;
namespace bs = boost::serialization;
namespace bi = boost::interprocess;
using namespace boost::archive;



/**
 * \brief A default constructor
 *\param session is an object containing the encrypted identifier of the session generated by VISHNU
 */

SessionEntry::SessionEntry(const UMS_Data::Session& session): msession(session) {}


/**
 * \brief A default constructor
 * \param closePolicy: the close session type with default value equal to 0
 */

SessionEntry::SessionEntry( int closePolicy_) {

msession.setClosePolicy(closePolicy_);
}


/**
 * \brief Another constructor taking parameters
 * \param sessionKey_: the key of the session
 * \param closePolicy_: the session close type with 0 as default value
 */

SessionEntry::SessionEntry(const std::string& sessionKey_, int closePolicy_) {

  msession.setSessionKey(sessionKey_);
  msession.setClosePolicy(closePolicy_);

}


/**
 * \brief To get the key of the session
 * \return The key of the session
 */


std::string
SessionEntry::getSessionKey()const{
  return msession.getSessionKey();
}


/**
 * \brief To get the session close type
 * \return The session close type
 */


int
SessionEntry::getClosePolicy()const{
  return msession.getClosePolicy();
}

/**
 * \brief To get the session id
 * \return The session id
 */

std::string
SessionEntry::getSessionId()const{
  return msession.getSessionId();
}

/**
 * \brief The serializer function
 * \param ar: An archive type which can be text type or xml type
 * \param version: The version of serialized class
 */


template<class Archive>
void
SessionEntry::serialize(Archive& ar, const unsigned int version){

  std::string sessionKey(msession.getSessionKey());
  int closePolicy (msession.getClosePolicy());
  std::string sessionId (msession.getSessionId());
  ar & bs::make_nvp("sessionKey", sessionKey) & bs::make_nvp("closePolicy",closePolicy) & bs::make_nvp("sessionId",sessionId) ;
  if ( typename Archive::is_loading()) {
    msession.setSessionKey(sessionKey);
    msession.setSessionId(sessionId);
    msession.setClosePolicy(closePolicy);
  }
}


/**
 * \brief A helper to display a session parameters
 * \param os: A stream where the session parameters will be printed
 * \param session:The session to print
 * \return The stream where the session parameters have been printed
 */
std::ostream&
operator <<(std::ostream& os, const SessionEntry& session){
  std::cout << "sessionKey: " << session.getSessionKey() << "  closePolicy: "<< session.getClosePolicy()
   << "  sessionId "<< session.getSessionId() << std::endl;
  return os;
}



/**
 * \brief To record  sessions in a file
 * \param allSessions: A set of sessions which will be stored in the file
 * \param file       : the path of the file
 * \exception        : raises a Boost archive exception
 */

template <class T>
void
saveIntoFile(SessionContainer& allSessions, const char* file){
  bi::file_lock sessionLock(file);
  bi::scoped_lock<bi::file_lock> lock(sessionLock);
  std::ofstream ofile (file);

  T ar(ofile);

  ar << bs::make_nvp("sessions",allSessions);

  ofile.close();
}


/**
 * \brief  To load all sessions stored in a file
 * \param allSessions: The sessions stored in the file
 * \param file       : The file storing the sessions
 * \exception        : raises a Boost archive exception
 */


template <class T>
void
getFromFile(SessionContainer& allSessions, const char* file){

  std::ifstream ifile(file);

  T ar(ifile);

  ar >> bs::make_nvp("sessions",allSessions);

  ifile.close();
}


/**
 * \brief To store a the current session running in a terminal in the file
 * \param session : the current session
 * \param terminal: The terminal in which the session is running
 */

void
storeLastSession(const SessionEntry& session,const std::string& terminal){

  SessionContainer allSessions;


  allSessions=getAllSessions(terminal);


  allSessions.push_back(session);

  saveIntoFile<binary_oarchive>(allSessions, terminal.c_str());

}


/**
 * \brief helper function  which wrappes getFromFile function
 * and ensures that all error exception is catched .
 * \param terminal: the file corresponding to the terminal which launched the
 * serialization process
 * \return all sessions stored into the file or an empty container
 */


SessionContainer
getAllSessions(const std::string& terminal){

  SessionContainer allSessions;

  bfs::path pid_file(terminal);

  if( bfs::exists(pid_file) && !bfs::is_empty(pid_file)){

    getFromFile<binary_iarchive>(allSessions, terminal.c_str());

  }
  return allSessions;

}


/**
 * To get the last open session corrseponding to the last session stored in the
 * file
 * \param terminal : The terminal in which the session was running
 * \return The last stored session
 */


SessionEntry
getLastSession(const std::string& terminal){

  SessionContainer allSessions;


  allSessions=getAllSessions(terminal);

  if(allSessions.empty()){

    //std::cerr <<"There is no open session in this terminal\n";

    //exit (CLI_ERROR_NO_SESSION);
    throw UserException (ERRCODE_CLI_ERROR_NO_SESSION,"There is no open session in this terminal");

  }


  return allSessions.back();


}


/**
 * \brief To remove the last entry of session from the file
 * \param terminal : The terminal in which the session was running
 */

void
removeLastSession(const std::string & terminal){

  SessionContainer allSessions;


  allSessions=getAllSessions(terminal);



  if (!allSessions.empty()){


    allSessions.pop_back();


    saveIntoFile<binary_oarchive>(allSessions, terminal.c_str());

  }
  else{// all session have been closed

    std::ofstream file(terminal.c_str(), std::ios::out | std::ios::trunc);

    if (file){

      file.close();
    }
    throw UserException (ERRCODE_CLI_ERROR_NO_SESSION,"all sessions in this terminal have been closed");
  }

}


/**
 * \brief To get the path of the file in which the sessions open from a terminal
 * had been stored
 * \param tpid : the identifier of the terminal as process
 * \return the path of the file in which the sessions open from the terminal had
 * been stored
 */



std::string
getSessionLocation(int tpid){

  // change current directory
  bfs::path home_dir = getenv("HOME");
  bfs::path  session_dir = home_dir;
  bfs::path  session_file ;
  session_dir /= ".vishnu";

  session_dir /= "sessions";

  std::ostringstream ss;
  ss<<tpid;
  session_file=session_dir;
  session_file/=ss.str();

  if(!bfs::exists(session_dir)){
    bfs::create_directories(session_dir);
  }


  return session_file.string();


}

/**
 * \brief Another function to store last session open
 * \param sessionKey: The key of the session which will be stored
 * \param closePolicy: The session close type
 * \param ppid: The identifier of the terminal as process
 */


void
storeLastSession(const std::string& sessionKey ,int closePolicy,int ppid){

  std::string sessionFile=getSessionLocation(ppid);

  SessionEntry session(sessionKey,closePolicy);

  storeLastSession(session,sessionFile.c_str());


}

/**
 * \brief Another function to store last session open
 * \param session_: The  session which will be stored
 * \param ppid: The identifier of the terminal as process
 */


void
storeLastSession(const UMS_Data::Session& session_,int ppid){

  std::string sessionFile=getSessionLocation(ppid);

  SessionEntry session(session_);

    storeLastSession(session,sessionFile.c_str());

}

/**
 * \brief To get the last session key
 * \param ppid: The identifier of the terminal as process in which the session
 * had been open
 * \return The key of the last session open from the terminal
 */

std::string
getLastSessionKey(int ppid){

  std::string sessionFile=getSessionLocation(ppid);


  SessionEntry session=getLastSession(sessionFile);


  return(session.getSessionKey());


}

/**
 * \brief To get the last session identifier
 * \param ppid: The identifier of the terminal as process in which the session
 * had been open
 * \return The identifier of the last session open from the terminal
 */

std::string
getLastSessionId(int ppid){

  std::string sessionFile=getSessionLocation(ppid);


  SessionEntry session=getLastSession(sessionFile);


  return(session.getSessionId());


}




/**
 * \brief To remove the bad session keys stored in the session file
 * \param ppid : The process identifier of the terminal in which the session had
 * been open.
 */
void
removeBadSessionKeyFromFile(int ppid){

    std::string sessionFile=getSessionLocation(ppid); // get the path of the session file

    removeLastSession(sessionFile);// remove from the file

}



/**
 * \brief A helper function which check if an given exception represents a bad
 * sessionKey
 *\param e: a given VishnuException
 *\return   : true if it's a bad session key or false otherwhise
 */
bool
checkBadSessionKeyError(const VishnuException& e){

return( (e.getMsgI()==ERRCODE_SESSIONKEY_NOT_FOUND) || e.getMsgI()==ERRCODE_SESSIONKEY_EXPIRED   );

}
