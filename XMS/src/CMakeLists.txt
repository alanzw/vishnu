include_directories(
  ${CONFIG_SOURCE_DIR}
  ${EMF4CPP_INCLUDE_DIR}
  ${EMF_DATA_DIR}
  ${UMS_EMF_DATA_DIR}
  ${TMS_EMF_DATA_DIR}
  ${FMS_EMF_DATA_DIR}
  ${VISHNU_EXCEPTION_INCLUDE_DIR}
  ${UTILVISHNU_SOURCE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${PROJECT_BINARY_DIR}
  ${VERSION_MANAGER_SOURCE_DIR}
  ${ZMQ_INCLUDE_DIR}
  ${COMMUNICATION_INCLUDE_DIR}
  ${VISHNU_SOURCE_DIR}/UMS/src/sed
  ${LIBJANSSON_INCLUDE_DIR}
  ${REGISTRY_SOURCE_DIR}
  ${UMS_API_SOURCE_DIR}
  ${TMS_API_SOURCE_DIR}
  ${DATA_BASE_INCLUDE_DIR}
  ${UMS_SERVER_SOURCE_DIR}
  ${TMS_SERVER_SOURCE_DIR}
  ${FMS_SERVER_SOURCE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${REGISTRY_SOURCE_DIR}
  ${AUTHENTICATOR_INCLUDE_DIR}
  ${XMS_SED_SOURCE_DIR})

if(NOT COMPILE_ONLY_LIBBATCH)

  set(sed_SRCS xmssed.cpp
    MonitorXMS.cpp
    ServerXMS.cpp
    internalApiUMS.cpp
    internalApiTMS.cpp
    internalApiFMS.cpp
    ${COMMUNICATION_INCLUDE_DIR}/CommServer.cpp)
  
  add_executable(xmssed ${sed_SRCS})
  target_link_libraries(xmssed vishnu-core vishnu-core-server
    vishnu-ums-server
    vishnu-tms-server
    vishnu-fms-server
    )
  install(TARGETS xmssed DESTINATION ${SBIN_INSTALL_DIR})

endif(NOT COMPILE_ONLY_LIBBATCH)

