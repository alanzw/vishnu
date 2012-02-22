/**
 * \file LSFServer.hpp
 * \brief This file contains the VISHNU LSFServer class.
 * \author Daouda Traore (daouda.traore@sysfera.com)
 * \date April 2011
 */


#include <vector>
#include <sstream>
#include <algorithm>
#include <limits>

#include <boost/algorithm/string.hpp>

#include <lsf/lsbatch.h>

#include "LSFServer.hpp"
#include "BatchServer.hpp"
#include "TMSVishnuException.hpp"
#include "UMSVishnuException.hpp"
#include "utilVishnu.hpp"

using namespace std;
using namespace vishnu;

/**
 * \brief Constructor
 */
LSFServer::LSFServer():BatchServer() {
}

/**
 * \brief Function to submit LSF job
 * \param scriptPath the path to the script containing the job characteristique
 * \param options the options to submit job
 * \param job The job data structure
 * \param envp The list of environment variables used by LSF submission function 
 * \return raises an exception on error
 */
int 
LSFServer::submit(const char* scriptPath, 
    const TMS_Data::SubmitOptions& options, 
    TMS_Data::Job& job, char** envp) {

  std::vector<std::string> cmdsOptions;
  //processes the vishnu options
  processOptions(scriptPath, options, cmdsOptions);

  int argc = cmdsOptions.size()+2;
  char* argv[argc];
  argv[0] = (char*) "vishnu_submit_job";
  argv[argc-1] = const_cast<char*>(scriptPath);
  for(int i=0; i < cmdsOptions.size(); i++) {
    argv[i+1] = const_cast<char*>(cmdsOptions[i].c_str());
  }

  struct submit  req;
  struct submitReply  reply;
  LS_LONG_INT  batchJobId;
  int  i;

  if (lsb_init(NULL) < 0) {
    lsb_perror((char*)"vishnu_submit_job: lsb_init() failed");
    return -1;//error messages are written to stderr, VISHNU redirects these messages into a file
  }

  /* Initialize 0 in req */
  memset(&req, 0, sizeof(struct submit));

  req.options = 0;
  req.resReq = NULL;
  
  for (i = 0; i < LSF_RLIM_NLIMITS; i++)
    req.rLimits[i] = DEFAULT_RLIMIT;

  req.hostSpec = NULL;
  req.numProcessors = 1;
  req.maxNumProcessors = 1;
  req.beginTime = 0;
  req.termTime  = 0;
  req.command = const_cast<char*>(scriptPath);;
  req.nxf = 0;
  req.delOptions = 0;

  batchJobId = lsb_submit(&req, &reply);

  if (batchJobId < 0) {
    switch (lsberrno) {
      case LSBE_QUEUE_USE:
      case LSBE_QUEUE_CLOSED:
        lsb_perror(reply.queue);
        return -1;//error messages are written to stderr, VISHNU redirects these messages into a file
      default:
        lsb_perror(NULL);
        return -1;//error messages are written to stderr, VISHNU redirects these messages into a file
     }
  }

  //Fill the vishnu job structure 
  fillJobInfo(job, batchJobId);

  return 0;
}


/**
 * \brief Function to treat the submission options
 * \param scriptPath The job script path
 * \param options the object which contains the SubmitOptions options values
 * \param cmdsOptions The list of the option value
 * \return raises an exception on error
 */
void 
LSFServer::processOptions(const char* scriptPath,
                            const TMS_Data::SubmitOptions& options, 
                            std::vector<std::string>&cmdsOptions) {

  if(!options.getNbNodesAndCpuPerNode().empty() && options.getNbCpu()!=-1) {
    throw UserException(ERRCODE_INVALID_PARAM, "Conflict: You can't use the NbCpu option and NbNodesAndCpuPerNode option together.\n");
  }

  if(options.isSelectQueueAutom() && !options.getQueue().empty() ) {
    throw UserException(ERRCODE_INVALID_PARAM, "Conflict: You can't use the SelectQueueAutom (-Q) and getQueue (-q) options together.\n");
  }

  if(options.getName().size()!=0){
    cmdsOptions.push_back("-J");
    cmdsOptions.push_back(options.getName());
  }
  if(options.getQueue().size()!=0) {
    cmdsOptions.push_back("-p");
    cmdsOptions.push_back(options.getQueue());
  }
  if(options.getOutputPath().size()!=0) {
    cmdsOptions.push_back("-o");
    cmdsOptions.push_back(options.getOutputPath());
  }
  if(options.getErrorPath().size()!=0) {
    cmdsOptions.push_back("-e");
    cmdsOptions.push_back(options.getErrorPath());
  }
  if(options.getWallTime()!=-1) {
    cmdsOptions.push_back("-t"); 
    std::string timeStr = vishnu::convertWallTimeToString(options.getWallTime());
    size_t pos = timeStr.rfind(":");
    int i=0;
    while(pos!=std::string::npos){
      i++;
      if(i==3) {
        timeStr = timeStr.replace(pos, 1, "-");
        break;
      }
      if(pos==0) {
        break;
      } else {
        pos = timeStr.rfind(":", pos-1);
      }
    }
    cmdsOptions.push_back(timeStr);
  }
  if(options.getNbCpu()!=-1) {
    std::ostringstream os_str;
    os_str << options.getNbCpu();
    cmdsOptions.push_back("--mincpus="+os_str.str());
  }
  if(options.getMemory()!=-1) {
    std::ostringstream os_str;
    os_str << options.getMemory();
    cmdsOptions.push_back("--mem="+os_str.str());
  }
  if(options.getNbNodesAndCpuPerNode()!="") {
    std::string NbNodesAndCpuPerNode = options.getNbNodesAndCpuPerNode();
    size_t posNbNodes = NbNodesAndCpuPerNode.find(":");
    if(posNbNodes!=std::string::npos) {
      std::string nbNodes = NbNodesAndCpuPerNode.substr(0, posNbNodes);
      std::string cpuPerNode = NbNodesAndCpuPerNode.substr(posNbNodes+1); 
      cmdsOptions.push_back("--nodes="+nbNodes);
      cmdsOptions.push_back("--mincpus="+cpuPerNode);
    }
  }

  if(options.getMailNotification()!="") {
    std::string notification = options.getMailNotification();
    if(notification.compare("BEGIN")==0) {
      cmdsOptions.push_back("--mail-type=BEGIN");
    } else if(notification.compare("END")==0) {
      cmdsOptions.push_back("--mail-type=END");
    } else if(notification.compare("ERROR")==0) {
      cmdsOptions.push_back("--mail-type=FAIL");
    } else if(notification.compare("ALL")==0) {
      cmdsOptions.push_back("--mail-type=ALL");
    } else {
      throw UserException(ERRCODE_INVALID_PARAM, notification+" is an invalid notification type:"+" consult the vishnu user manuel");
    }
  }

  if(options.getMailNotifyUser()!="") {
    cmdsOptions.push_back("--mail-user="+options.getMailNotifyUser());
  }

  if(options.getGroup()!="") {
    cmdsOptions.push_back("--gid="+options.getGroup());
  }

  if(options.getWorkingDir()!="") {
    cmdsOptions.push_back("-D");
    cmdsOptions.push_back(options.getWorkingDir());
  }

  if(options.getCpuTime()!="") {
    cmdsOptions.push_back("-t");
    cmdsOptions.push_back(options.getCpuTime());
  }

  if(options.isSelectQueueAutom()) {
    int node = 0;
    int cpu = -1;
    istringstream isNode;
    std::string optionNodesValue = options.getNbNodesAndCpuPerNode();
    if(optionNodesValue.empty()) {
      std::string nodeStr = ""/*getLSFResourceValue(scriptPath, "-N", "--nodes")*/;
      std::string cpuStr =  ""/*getLSFResourceValue(scriptPath, "", "--mincpus")*/;
      if(!nodeStr.empty()) {
        if(nodeStr.find('-')!=std::string::npos) {
          istringstream isNodeStr(nodeStr);
          int minnode;
          int maxNode;
          char sparator;
          isNodeStr >> minnode;
          isNodeStr >> sparator;
          isNodeStr >> maxNode;
          node = maxNode; 
        } else {
          node = vishnu::convertToInt(nodeStr);
        }
      }
      if(!cpuStr.empty()) {
        cpu = vishnu::convertToInt(cpuStr);
      }
      if(options.getNbCpu()!=-1) {
        cpu=options.getNbCpu();
      } 
    } else {
      isNode.str(optionNodesValue);
      isNode >> node;
      char colon;
      isNode >> colon;
      isNode >> cpu;
    }
    if(node <=0) {
      node = 1;
    }
    TMS_Data::ListQueues* listOfQueues = listQueues();
    if(listOfQueues != NULL) {
      for(unsigned int i = 0; i < listOfQueues->getNbQueues(); i++) {
        TMS_Data::Queue* queue =  listOfQueues->getQueues().get(i);
        if(queue->getNode()>=node){
          std::string queueName = queue->getName();

          std::string walltimeStr = ""/*getLSFResourceValue(scriptPath, "-t", "--time")*/;
          long walltime = options.getWallTime()==-1?vishnu::convertStringToWallTime(walltimeStr):options.getWallTime();
          long qwalltimeMax = queue->getWallTime();
          int qCpuMax = queue->getMaxProcCpu();

          if((walltime <= qwalltimeMax || qwalltimeMax==0) &&
              (cpu <= qCpuMax)){
            cmdsOptions.push_back("-p");
            cmdsOptions.push_back(queueName);
            break;
          }
        };
      }
    }
  }

}

/**
 * \brief Function To convert vishnu job Id to LSF job Id 
 * \param jobId: vishnu job Id
 * \return the converted LSF job id
 */
LS_LONG_INT LSFServer::convertToLSFJobId(const std::string& jobId) {

  LS_LONG_INT lsfJobId;
  std::istringstream is(jobId);
  is >> lsfJobId;

return lsfJobId;
}

/**
 * \brief Function to cancel job
 * \param jobId the identifier of the job to cancel
 * \return raises an exception on error
 */
int
LSFServer::cancel(const char* jobId) {
  
  LS_LONG_INT lsfJobId = convertToLSFJobId(jobId); 

  int res = lsb_deletejob(lsfJobId, NULL, 0);
  if(res) {
    lsb_perror(NULL);
    return res;//error messages are written to stderr, VISHNU redirects these messages into a file
  }

  return 0;
}

/**
 * \brief Function to get the status of the job
 * \param jobId the identifier of the job 
 * \return -1 if the job is unknown or server not  unavailable 
 */
int 
LSFServer::getJobState(const std::string& jobId) {

  int state = 5; //TERMINATED 
  LS_LONG_INT lsfJobId = convertToLSFJobId(jobId);

  struct jobInfoEnt *jobInfo;
  int numJobs = 0;

  if (lsb_init(NULL) < 0) {
    return -1;
  }

  jobInfo = lsb_readjobinfo(&numJobs);

  if (jobInfo == NULL) {
    return -1;
  }

  bool jobIsFound=false;
  int i;
  for (i = 0; i < numJobs; i++) {
    if(jobInfo[i].jobId==lsfJobId) {
      state = convertLSFStateToVishnuState(jobInfo[i].status);
      break;
    }
  }

  return state;
}

/**
 * \brief Function to get the start time of the job
 * \param jobId the identifier of the job 
 * \return 0 if the job is unknown
 */
time_t 
LSFServer::getJobStartTime(const std::string& jobId) {

  time_t startTime = 0; 

  LS_LONG_INT lsfJobId = convertToLSFJobId(jobId);
  struct jobInfoEnt *jobInfo;
  int numJobs = 0;

  if (lsb_init(NULL) < 0) {
    return startTime;
  }

  jobInfo = lsb_readjobinfo(&numJobs);

  if (jobInfo == NULL) {
    return startTime;
  }

  bool jobIsFound=false;
  int i;
  for (i = 0; i < numJobs; i++) {
    if(jobInfo[i].jobId==lsfJobId) {
      startTime = convertLSFStateToVishnuState(jobInfo[i].startTime);
      break;
    }
  }

  return startTime;
} 

/**
 * \brief Function to convert the LSF state into VISHNU state 
 * \param state the state to convert
 * \return VISHNU state 
 */
int 
LSFServer::convertLSFStateToVishnuState(const unsigned int& state) {

  int res = 0;
  switch(state) {
    case JOB_STAT_PEND:case JOB_STAT_PSUSP:case JOB_STAT_SSUSP:case JOB_STAT_USUSP:case JOB_STAT_WAIT:
      res = 3;//WAITING
      break;
    case JOB_STAT_RUN:
      res = 4;//RUNNING
      break;
    case JOB_STAT_DONE:case JOB_STAT_PDONE:case JOB_STAT_PERR: case JOB_STAT_UNKWN:
      res = 5; //TERMINATED
      break;
    case JOB_STAT_EXIT:
      res = 6; //CANCELLED
      break;
    default:
      res = 5;
      break;
  }
  return res;
}

/**
 * \brief Function to convert the LSF priority into VISHNU priority
 * \param prio the priority to convert
 * \return VISHNU state 
 */
int 
LSFServer::convertLSFPrioToVishnuPrio(const uint32_t& prio) {
  if(prio < -512) {
    return 1;
  } else if(prio >= -512 && prio < 0) {
    return 2;
  } else if(prio >= 0 && prio < 512) {
    return 3;
  } else if(prio >= 512 && prio < 1023) {
    return 4;
  } else if(prio >= 1023) {
    return 5;
  }
  return 1; 
}

/**
 * \brief Function To fill the info concerning a job
 * \fn void fillJobInfo(TMS_Data::Job_ptr job, struct batch_status *p)
 * \param job: The job to fill
 * \param jobId: The identifier of the job to load
 */
void
LSFServer::fillJobInfo(TMS_Data::Job &job, const LS_LONG_INT& jobId){

  struct jobInfoEnt *jobInfo;
  int numJobs = 0;

  if (lsb_init(NULL) < 0) {
    //error messages are written to stderr, VISHNU redirects these messages into a file
    lsb_perror((char*)"LSFServer::fillJobInfo: lsb_init() failed");
    return;
  }

  jobInfo = lsb_readjobinfo(&numJobs);

  if (jobInfo == NULL) {
    //error messages are written to stderr, VISHNU redirects these messages into a file
    lsb_perror((char*)"LSFServer::fillJobInfo: lsb_redjobinfo() failed");
    return;
  }

  bool jobIsFound=false;
  int i;
  for (i = 0; i < numJobs; i++) {
    if(jobInfo[i].jobId==jobId) {
      jobIsFound=true; 
      break;
    }
  }

  if(jobIsFound) {
    job.setJobId(lsb_jobid2str(jobId));
    job.setOutputPath(jobInfo[i].submit.outFile) ;
    job.setErrorPath(jobInfo[i].submit.errFile);
    job.setStatus(convertLSFStateToVishnuState(jobInfo[i].status));
    job.setJobName(jobInfo[i].submit.jobName);
    job.setSubmitDate(jobInfo[i].submitTime);
    job.setOwner(jobInfo[i].user);
    job.setJobQueue(jobInfo[i].submit.queue);
    job.setWallClockLimit(jobInfo[i].submit.runtimeEstimation);
    job.setEndDate(jobInfo[i].endTime);
    job.setGroupName(jobInfo[i].submit.userGroup);
    job.setJobDescription(jobInfo[i].submit.jobDescription);
    job.setJobPrio(convertLSFPrioToVishnuPrio(jobInfo[i].jobPriority));

    job.setMemLimit(jobInfo[i].submit.rLimits[LSF_RLIMIT_RSS]);
    int nbCpu = jobInfo[i].submit.numProcessors;
    job.setNbCpus(nbCpu);
    int node = jobInfo[i].submit.numAskedHosts;
    job.setNbNodes(node);
    if(node!=-1) {
      job.setNbNodesAndCpuPerNode(vishnu::convertToString(node)+":"+vishnu::convertToString(nbCpu));
    }
    //To fill the job working dir
    job.setJobWorkingDir(jobInfo[i].cwd);
  } else {
    throw TMSVishnuException(ERRCODE_BATCH_SCHEDULER_ERROR, "LSF ERROR: problem to fill the submitted job information");
  }

}

/**
 * \brief Function to request the status of queues 
 * \param optQueueName (optional) the name of the queue to request 
 * \return The requested status in to ListQueues data structure 
 */
TMS_Data::ListQueues*
LSFServer::listQueues(const std::string& OptqueueName) { 

    struct queueInfoEnt *queueInfo;
    char **queues = NULL;
    int numQueues = 0;
    char *host = NULL;
    char *user = NULL;
    int options = 0;

   if (lsb_init(NULL) < 0) {
      //error messages are written to stderr, VISHNU redirects these messages into a file
      lsb_perror((char*)"listQueues: lsb_init() failed");
      return mlistQueues;
    }

    queueInfo = lsb_queueinfo(queues, &numQueues, host, user, options);

    if (queueInfo == NULL) {
      //error messages are written to stderr, VISHNU redirects these messages into a file
      lsb_perror((char*)"listQueues: lsb_queueinfo() failed");
      return mlistQueues;
    }

    TMS_Data::TMS_DataFactory_ptr ecoreFactory = TMS_Data::TMS_DataFactory::_instance();
    mlistQueues = ecoreFactory->createListQueues();
    
    for (int i = 0; i < numQueues; i++, queueInfo++) {

      TMS_Data::Queue_ptr queue = ecoreFactory->createQueue();

      if (queueInfo->qStatus & QUEUE_STAT_ACTIVE) {
        if (!queueInfo->qStatus & QUEUE_STAT_OPEN) {
          queue->setState(0);
        } 
        if (queueInfo->qStatus & QUEUE_STAT_RUN) {
          queue->setState(2);
        } else {
          queue->setState(1);
        }
      } else {
        queue->setState(1);
      }

      queue->setName(queueInfo->queue);
      queue->setPriority(convertLSFPrioToVishnuPrio(queueInfo->priority));
      queue->setNbRunningJobs(queueInfo->numRUN);
      queue->setNbJobsInQueue(queueInfo->numJobs-queueInfo->numRUN);
      queue->setDescription(queueInfo->description);
      queue->setMemory(queueInfo->rLimits[LSF_RLIMIT_RSS]);
      queue->setMaxProcCpu(queueInfo->rLimits[LSF_RLIMIT_CPU]);
      queue->setMaxJobCpu(-1);//Undefined
      queue->setNode(queueInfo->procLimit);

      // Adding created queue to the list
      mlistQueues->getQueues().push_back(queue);
    }

    mlistQueues->setNbQueues(mlistQueues->getQueues().size());

    return mlistQueues;

}

/**
 * \brief Function to get a list of submitted jobs
 * \param listOfJobs the ListJobs structure to fill
 * \param ignoredIds the list of job ids to ignore 
 */
void LSFServer::fillListOfJobs(TMS_Data::ListJobs*& listOfJobs,
    const std::vector<string>& ignoredIds) {

  if (lsb_init(NULL) < 0) {
    lsb_perror((char*)"LSFServer::fillListOfJobs: lsb_init() failed");
    return;
  }

  int numJobs = 0;
  struct jobInfoEnt *jobInfo = lsb_readjobinfo(&numJobs);

  if (jobInfo == NULL) {
    lsb_perror((char*)"LSFServer::fillListOfJobs: lsb_readjobinfo failed");
    return;
  }

  int jobStatus;
  long nbRunningJobs = 0;
  long nbWaitingJobs = 0;
  for(int i=0; i < numJobs; i++) {
    std::vector<std::string>::const_iterator iter;
    iter = std::find(ignoredIds.begin(), ignoredIds.end(), convertToString(jobInfo[i].jobId));
    if(iter==ignoredIds.end()) {
      TMS_Data::Job_ptr job = new TMS_Data::Job();
      fillJobInfo(*job, jobInfo[i].jobId);
      jobStatus = job->getStatus();
      if(jobStatus==4) {
        nbRunningJobs++;
      } else if(jobStatus >= 1 && jobStatus <= 3) {
        nbWaitingJobs++;
      }
      listOfJobs->getJobs().push_back(job);
    }
  }
  listOfJobs->setNbJobs(listOfJobs->getJobs().size());
  listOfJobs->setNbRunningJobs(listOfJobs->getNbRunningJobs()+nbRunningJobs);
  listOfJobs->setNbWaitingJobs(listOfJobs->getNbWaitingJobs()+nbWaitingJobs);

}

/**
 * \brief Destructor
 */
LSFServer::~LSFServer() {
}

