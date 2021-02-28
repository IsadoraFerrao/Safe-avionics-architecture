#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/newmain.o \
	${OBJECTDIR}/src/hamster/HAMSTERCluster.o \
	${OBJECTDIR}/src/hamster/HAMSTERCommon.o \
	${OBJECTDIR}/src/hamster/HAMSTEREntity.o \
	${OBJECTDIR}/src/hamster/HAMSTERModule.o \
	${OBJECTDIR}/src/hamster/HAMSTERObject.o \
	${OBJECTDIR}/src/hamster/HAMSTERObjectDescriptor.o \
	${OBJECTDIR}/src/hamster/HAMSTERSuperEntity.o \
	${OBJECTDIR}/src/hamster/HAMSTERUVComponent.o \
	${OBJECTDIR}/src/hamster/HAMSTERUnitCommInfo.o \
	${OBJECTDIR}/src/hamster/HAMSTERUnitDescriptor.o \
	${OBJECTDIR}/src/hamster/HAMSTERUserEntity.o \
	${OBJECTDIR}/src/hamster/Unit.o \
	${OBJECTDIR}/src/hamster/comm/CommBroker.o \
	${OBJECTDIR}/src/hamster/comm/ConnectionlessDispatcher.o \
	${OBJECTDIR}/src/hamster/comm/HAMSTERObjectPeer.o \
	${OBJECTDIR}/src/hamster/comm/HAMSTERPeer.o \
	${OBJECTDIR}/src/hamster/comm/HAMSTERQueue.o \
	${OBJECTDIR}/src/hamster/comm/MessagePooler.o \
	${OBJECTDIR}/src/hamster/comm/cryptography/CryptographyAlgorithm.o \
	${OBJECTDIR}/src/hamster/comm/cryptography/CryptographyHandler.o \
	${OBJECTDIR}/src/hamster/comm/cryptography/KeyInfo.o \
	${OBJECTDIR}/src/hamster/comm/interface/Acceptor.o \
	${OBJECTDIR}/src/hamster/comm/interface/AcceptorConn.o \
	${OBJECTDIR}/src/hamster/comm/interface/AddressInfo.o \
	${OBJECTDIR}/src/hamster/comm/interface/CommInterface.o \
	${OBJECTDIR}/src/hamster/comm/interface/Connector.o \
	${OBJECTDIR}/src/hamster/comm/interface/Listener.o \
	${OBJECTDIR}/src/hamster/comm/interface/socket/INETSocketAcceptor.o \
	${OBJECTDIR}/src/hamster/comm/interface/socket/INETSocketAddressInfo.o \
	${OBJECTDIR}/src/hamster/comm/interface/socket/INETSocketConnector.o \
	${OBJECTDIR}/src/hamster/comm/interface/socket/INETSocketHandler.o \
	${OBJECTDIR}/src/hamster/comm/interface/socket/INETSocketInterface.o \
	${OBJECTDIR}/src/hamster/comm/messaging/HAMSTERMessage.o \
	${OBJECTDIR}/src/hamster/comm/messaging/MessageField.o \
	${OBJECTDIR}/src/hamster/comm/messaging/MessageLock.o \
	${OBJECTDIR}/src/hamster/identification/HAMSTERID.o \
	${OBJECTDIR}/src/hamster/identification/Registerer.o \
	${OBJECTDIR}/src/hamster/identification/RegistrationStrategy.o \
	${OBJECTDIR}/src/hamster/nci/NCICluster.o \
	${OBJECTDIR}/src/hamster/nci/NCIEntity.o \
	${OBJECTDIR}/src/hamster/nci/NCIModule.o \
	${OBJECTDIR}/src/hamster/nimble/NIMBLE.o \
	${OBJECTDIR}/src/hamster/np/ComponentBehaviour.o \
	${OBJECTDIR}/src/hamster/np/Mission.o \
	${OBJECTDIR}/src/hamster/np/NPAgent.o \
	${OBJECTDIR}/src/hamster/np/NPManager.o \
	${OBJECTDIR}/src/hamster/np/NavigationPhase.o \
	${OBJECTDIR}/src/hamster/np/PhaseBehaviour.o \
	${OBJECTDIR}/src/hamster/sample/AutoPilot.o \
	${OBJECTDIR}/src/hamster/sample/FarashRegistraton.o \
	${OBJECTDIR}/src/hamster/sample/FlightData.o \
	${OBJECTDIR}/src/hamster/sample/MQTTSubscriber.o \
	${OBJECTDIR}/src/hamster/sample/MultispectralCamera.o \
	${OBJECTDIR}/src/hamster/sample/RGBCamera.o \
	${OBJECTDIR}/src/hamster/sample/SensorUnit.o \
	${OBJECTDIR}/src/hamster/sample/Station.o \
	${OBJECTDIR}/src/hamster/sample/StationJINT.o \
	${OBJECTDIR}/src/hamster/sample/UAV.o \
	${OBJECTDIR}/src/hamster/sample/UAVJINT.o \
	${OBJECTDIR}/src/hamster/sphere/CentralSPHERE.o \
	${OBJECTDIR}/src/hamster/sphere/LocalSPHERE.o \
	${OBJECTDIR}/src/hamster/sphere/NCI/CentralNCI.o \
	${OBJECTDIR}/src/hamster/sphere/NCI/LocalNCI.o \
	${OBJECTDIR}/src/hamster/sphere/SPHERE.o \
	${OBJECTDIR}/src/hamster/sphere/SuperSPHERE.o \
	${OBJECTDIR}/src/hamster/sphere/csu/CentralCSU.o \
	${OBJECTDIR}/src/hamster/sphere/csu/LocalCSU.o \
	${OBJECTDIR}/src/hamster/sphere/csu/SuperCSU.o \
	${OBJECTDIR}/src/hamster/sphere/semu/CentralSEMU.o \
	${OBJECTDIR}/src/hamster/sphere/semu/LocalSEMU.o \
	${OBJECTDIR}/src/hamster/sphere/smu/CentralSMU.o \
	${OBJECTDIR}/src/hamster/sphere/smu/LocalSMU.o \
	${OBJECTDIR}/src/hamster/utils/CSVReader.o \
	${OBJECTDIR}/src/hamster/utils/Configurable.o \
	${OBJECTDIR}/src/hamster/utils/Uuid.o \
	${OBJECTDIR}/src/hamster/utils/logger/FileLogger.o \
	${OBJECTDIR}/src/hamster/utils/logger/HAMSTERLogger.o \
	${OBJECTDIR}/src/hamster/utils/logger/TerminalLogger.o \
	${OBJECTDIR}/src/hamster/utils/task/RunningTask.o \
	${OBJECTDIR}/src/tinyXML/tinystr.o \
	${OBJECTDIR}/src/tinyXML/tinyxml.o \
	${OBJECTDIR}/src/tinyXML/tinyxmlerror.o \
	${OBJECTDIR}/src/tinyXML/tinyxmlparser.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lars2020.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lars2020.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lars2020 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/newmain.o: newmain.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/newmain.o newmain.cpp

${OBJECTDIR}/src/hamster/HAMSTERCluster.o: src/hamster/HAMSTERCluster.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/HAMSTERCluster.o src/hamster/HAMSTERCluster.cc

${OBJECTDIR}/src/hamster/HAMSTERCommon.o: src/hamster/HAMSTERCommon.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/HAMSTERCommon.o src/hamster/HAMSTERCommon.cc

${OBJECTDIR}/src/hamster/HAMSTEREntity.o: src/hamster/HAMSTEREntity.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/HAMSTEREntity.o src/hamster/HAMSTEREntity.cc

${OBJECTDIR}/src/hamster/HAMSTERModule.o: src/hamster/HAMSTERModule.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/HAMSTERModule.o src/hamster/HAMSTERModule.cc

${OBJECTDIR}/src/hamster/HAMSTERObject.o: src/hamster/HAMSTERObject.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/HAMSTERObject.o src/hamster/HAMSTERObject.cc

${OBJECTDIR}/src/hamster/HAMSTERObjectDescriptor.o: src/hamster/HAMSTERObjectDescriptor.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/HAMSTERObjectDescriptor.o src/hamster/HAMSTERObjectDescriptor.cc

${OBJECTDIR}/src/hamster/HAMSTERSuperEntity.o: src/hamster/HAMSTERSuperEntity.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/HAMSTERSuperEntity.o src/hamster/HAMSTERSuperEntity.cc

${OBJECTDIR}/src/hamster/HAMSTERUVComponent.o: src/hamster/HAMSTERUVComponent.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/HAMSTERUVComponent.o src/hamster/HAMSTERUVComponent.cc

${OBJECTDIR}/src/hamster/HAMSTERUnitCommInfo.o: src/hamster/HAMSTERUnitCommInfo.cpp
	${MKDIR} -p ${OBJECTDIR}/src/hamster
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/HAMSTERUnitCommInfo.o src/hamster/HAMSTERUnitCommInfo.cpp

${OBJECTDIR}/src/hamster/HAMSTERUnitDescriptor.o: src/hamster/HAMSTERUnitDescriptor.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/HAMSTERUnitDescriptor.o src/hamster/HAMSTERUnitDescriptor.cc

${OBJECTDIR}/src/hamster/HAMSTERUserEntity.o: src/hamster/HAMSTERUserEntity.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/HAMSTERUserEntity.o src/hamster/HAMSTERUserEntity.cc

${OBJECTDIR}/src/hamster/Unit.o: src/hamster/Unit.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/Unit.o src/hamster/Unit.cc

${OBJECTDIR}/src/hamster/comm/CommBroker.o: src/hamster/comm/CommBroker.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/CommBroker.o src/hamster/comm/CommBroker.cc

${OBJECTDIR}/src/hamster/comm/ConnectionlessDispatcher.o: src/hamster/comm/ConnectionlessDispatcher.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/ConnectionlessDispatcher.o src/hamster/comm/ConnectionlessDispatcher.cc

${OBJECTDIR}/src/hamster/comm/HAMSTERObjectPeer.o: src/hamster/comm/HAMSTERObjectPeer.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/HAMSTERObjectPeer.o src/hamster/comm/HAMSTERObjectPeer.cc

${OBJECTDIR}/src/hamster/comm/HAMSTERPeer.o: src/hamster/comm/HAMSTERPeer.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/HAMSTERPeer.o src/hamster/comm/HAMSTERPeer.cc

${OBJECTDIR}/src/hamster/comm/HAMSTERQueue.o: src/hamster/comm/HAMSTERQueue.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/HAMSTERQueue.o src/hamster/comm/HAMSTERQueue.cc

${OBJECTDIR}/src/hamster/comm/MessagePooler.o: src/hamster/comm/MessagePooler.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/MessagePooler.o src/hamster/comm/MessagePooler.cc

${OBJECTDIR}/src/hamster/comm/cryptography/CryptographyAlgorithm.o: src/hamster/comm/cryptography/CryptographyAlgorithm.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm/cryptography
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/cryptography/CryptographyAlgorithm.o src/hamster/comm/cryptography/CryptographyAlgorithm.cc

${OBJECTDIR}/src/hamster/comm/cryptography/CryptographyHandler.o: src/hamster/comm/cryptography/CryptographyHandler.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm/cryptography
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/cryptography/CryptographyHandler.o src/hamster/comm/cryptography/CryptographyHandler.cc

${OBJECTDIR}/src/hamster/comm/cryptography/KeyInfo.o: src/hamster/comm/cryptography/KeyInfo.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm/cryptography
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/cryptography/KeyInfo.o src/hamster/comm/cryptography/KeyInfo.cc

${OBJECTDIR}/src/hamster/comm/interface/Acceptor.o: src/hamster/comm/interface/Acceptor.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm/interface
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/interface/Acceptor.o src/hamster/comm/interface/Acceptor.cc

${OBJECTDIR}/src/hamster/comm/interface/AcceptorConn.o: src/hamster/comm/interface/AcceptorConn.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm/interface
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/interface/AcceptorConn.o src/hamster/comm/interface/AcceptorConn.cc

${OBJECTDIR}/src/hamster/comm/interface/AddressInfo.o: src/hamster/comm/interface/AddressInfo.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm/interface
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/interface/AddressInfo.o src/hamster/comm/interface/AddressInfo.cc

${OBJECTDIR}/src/hamster/comm/interface/CommInterface.o: src/hamster/comm/interface/CommInterface.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm/interface
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/interface/CommInterface.o src/hamster/comm/interface/CommInterface.cc

${OBJECTDIR}/src/hamster/comm/interface/Connector.o: src/hamster/comm/interface/Connector.cpp
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm/interface
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/interface/Connector.o src/hamster/comm/interface/Connector.cpp

${OBJECTDIR}/src/hamster/comm/interface/Listener.o: src/hamster/comm/interface/Listener.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm/interface
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/interface/Listener.o src/hamster/comm/interface/Listener.cc

${OBJECTDIR}/src/hamster/comm/interface/socket/INETSocketAcceptor.o: src/hamster/comm/interface/socket/INETSocketAcceptor.cpp
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm/interface/socket
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/interface/socket/INETSocketAcceptor.o src/hamster/comm/interface/socket/INETSocketAcceptor.cpp

${OBJECTDIR}/src/hamster/comm/interface/socket/INETSocketAddressInfo.o: src/hamster/comm/interface/socket/INETSocketAddressInfo.cpp
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm/interface/socket
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/interface/socket/INETSocketAddressInfo.o src/hamster/comm/interface/socket/INETSocketAddressInfo.cpp

${OBJECTDIR}/src/hamster/comm/interface/socket/INETSocketConnector.o: src/hamster/comm/interface/socket/INETSocketConnector.cpp
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm/interface/socket
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/interface/socket/INETSocketConnector.o src/hamster/comm/interface/socket/INETSocketConnector.cpp

${OBJECTDIR}/src/hamster/comm/interface/socket/INETSocketHandler.o: src/hamster/comm/interface/socket/INETSocketHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm/interface/socket
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/interface/socket/INETSocketHandler.o src/hamster/comm/interface/socket/INETSocketHandler.cpp

${OBJECTDIR}/src/hamster/comm/interface/socket/INETSocketInterface.o: src/hamster/comm/interface/socket/INETSocketInterface.cpp
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm/interface/socket
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/interface/socket/INETSocketInterface.o src/hamster/comm/interface/socket/INETSocketInterface.cpp

${OBJECTDIR}/src/hamster/comm/messaging/HAMSTERMessage.o: src/hamster/comm/messaging/HAMSTERMessage.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm/messaging
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/messaging/HAMSTERMessage.o src/hamster/comm/messaging/HAMSTERMessage.cc

${OBJECTDIR}/src/hamster/comm/messaging/MessageField.o: src/hamster/comm/messaging/MessageField.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm/messaging
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/messaging/MessageField.o src/hamster/comm/messaging/MessageField.cc

${OBJECTDIR}/src/hamster/comm/messaging/MessageLock.o: src/hamster/comm/messaging/MessageLock.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/comm/messaging
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/comm/messaging/MessageLock.o src/hamster/comm/messaging/MessageLock.cc

${OBJECTDIR}/src/hamster/identification/HAMSTERID.o: src/hamster/identification/HAMSTERID.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/identification
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/identification/HAMSTERID.o src/hamster/identification/HAMSTERID.cc

${OBJECTDIR}/src/hamster/identification/Registerer.o: src/hamster/identification/Registerer.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/identification
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/identification/Registerer.o src/hamster/identification/Registerer.cc

${OBJECTDIR}/src/hamster/identification/RegistrationStrategy.o: src/hamster/identification/RegistrationStrategy.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/identification
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/identification/RegistrationStrategy.o src/hamster/identification/RegistrationStrategy.cc

${OBJECTDIR}/src/hamster/nci/NCICluster.o: src/hamster/nci/NCICluster.cpp
	${MKDIR} -p ${OBJECTDIR}/src/hamster/nci
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/nci/NCICluster.o src/hamster/nci/NCICluster.cpp

${OBJECTDIR}/src/hamster/nci/NCIEntity.o: src/hamster/nci/NCIEntity.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/nci
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/nci/NCIEntity.o src/hamster/nci/NCIEntity.cc

${OBJECTDIR}/src/hamster/nci/NCIModule.o: src/hamster/nci/NCIModule.cpp
	${MKDIR} -p ${OBJECTDIR}/src/hamster/nci
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/nci/NCIModule.o src/hamster/nci/NCIModule.cpp

${OBJECTDIR}/src/hamster/nimble/NIMBLE.o: src/hamster/nimble/NIMBLE.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/nimble
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/nimble/NIMBLE.o src/hamster/nimble/NIMBLE.cc

${OBJECTDIR}/src/hamster/np/ComponentBehaviour.o: src/hamster/np/ComponentBehaviour.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/np
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/np/ComponentBehaviour.o src/hamster/np/ComponentBehaviour.cc

${OBJECTDIR}/src/hamster/np/Mission.o: src/hamster/np/Mission.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/np
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/np/Mission.o src/hamster/np/Mission.cc

${OBJECTDIR}/src/hamster/np/NPAgent.o: src/hamster/np/NPAgent.cpp
	${MKDIR} -p ${OBJECTDIR}/src/hamster/np
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/np/NPAgent.o src/hamster/np/NPAgent.cpp

${OBJECTDIR}/src/hamster/np/NPManager.o: src/hamster/np/NPManager.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/np
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/np/NPManager.o src/hamster/np/NPManager.cc

${OBJECTDIR}/src/hamster/np/NavigationPhase.o: src/hamster/np/NavigationPhase.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/np
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/np/NavigationPhase.o src/hamster/np/NavigationPhase.cc

${OBJECTDIR}/src/hamster/np/PhaseBehaviour.o: src/hamster/np/PhaseBehaviour.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/np
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/np/PhaseBehaviour.o src/hamster/np/PhaseBehaviour.cc

${OBJECTDIR}/src/hamster/sample/AutoPilot.o: src/hamster/sample/AutoPilot.cpp
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sample
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sample/AutoPilot.o src/hamster/sample/AutoPilot.cpp

${OBJECTDIR}/src/hamster/sample/FarashRegistraton.o: src/hamster/sample/FarashRegistraton.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sample
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sample/FarashRegistraton.o src/hamster/sample/FarashRegistraton.cc

${OBJECTDIR}/src/hamster/sample/FlightData.o: src/hamster/sample/FlightData.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sample
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sample/FlightData.o src/hamster/sample/FlightData.cc

${OBJECTDIR}/src/hamster/sample/MQTTSubscriber.o: src/hamster/sample/MQTTSubscriber.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sample
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sample/MQTTSubscriber.o src/hamster/sample/MQTTSubscriber.cc

${OBJECTDIR}/src/hamster/sample/MultispectralCamera.o: src/hamster/sample/MultispectralCamera.cpp
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sample
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sample/MultispectralCamera.o src/hamster/sample/MultispectralCamera.cpp

${OBJECTDIR}/src/hamster/sample/RGBCamera.o: src/hamster/sample/RGBCamera.cpp
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sample
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sample/RGBCamera.o src/hamster/sample/RGBCamera.cpp

${OBJECTDIR}/src/hamster/sample/SensorUnit.o: src/hamster/sample/SensorUnit.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sample
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sample/SensorUnit.o src/hamster/sample/SensorUnit.cc

${OBJECTDIR}/src/hamster/sample/Station.o: src/hamster/sample/Station.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sample
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sample/Station.o src/hamster/sample/Station.cc

${OBJECTDIR}/src/hamster/sample/StationJINT.o: src/hamster/sample/StationJINT.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sample
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sample/StationJINT.o src/hamster/sample/StationJINT.cc

${OBJECTDIR}/src/hamster/sample/UAV.o: src/hamster/sample/UAV.cpp
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sample
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sample/UAV.o src/hamster/sample/UAV.cpp

${OBJECTDIR}/src/hamster/sample/UAVJINT.o: src/hamster/sample/UAVJINT.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sample
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sample/UAVJINT.o src/hamster/sample/UAVJINT.cc

${OBJECTDIR}/src/hamster/sphere/CentralSPHERE.o: src/hamster/sphere/CentralSPHERE.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sphere
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sphere/CentralSPHERE.o src/hamster/sphere/CentralSPHERE.cc

${OBJECTDIR}/src/hamster/sphere/LocalSPHERE.o: src/hamster/sphere/LocalSPHERE.cpp
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sphere
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sphere/LocalSPHERE.o src/hamster/sphere/LocalSPHERE.cpp

${OBJECTDIR}/src/hamster/sphere/NCI/CentralNCI.o: src/hamster/sphere/NCI/CentralNCI.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sphere/NCI
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sphere/NCI/CentralNCI.o src/hamster/sphere/NCI/CentralNCI.cc

${OBJECTDIR}/src/hamster/sphere/NCI/LocalNCI.o: src/hamster/sphere/NCI/LocalNCI.cpp
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sphere/NCI
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sphere/NCI/LocalNCI.o src/hamster/sphere/NCI/LocalNCI.cpp

${OBJECTDIR}/src/hamster/sphere/SPHERE.o: src/hamster/sphere/SPHERE.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sphere
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sphere/SPHERE.o src/hamster/sphere/SPHERE.cc

${OBJECTDIR}/src/hamster/sphere/SuperSPHERE.o: src/hamster/sphere/SuperSPHERE.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sphere
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sphere/SuperSPHERE.o src/hamster/sphere/SuperSPHERE.cc

${OBJECTDIR}/src/hamster/sphere/csu/CentralCSU.o: src/hamster/sphere/csu/CentralCSU.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sphere/csu
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sphere/csu/CentralCSU.o src/hamster/sphere/csu/CentralCSU.cc

${OBJECTDIR}/src/hamster/sphere/csu/LocalCSU.o: src/hamster/sphere/csu/LocalCSU.cpp
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sphere/csu
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sphere/csu/LocalCSU.o src/hamster/sphere/csu/LocalCSU.cpp

${OBJECTDIR}/src/hamster/sphere/csu/SuperCSU.o: src/hamster/sphere/csu/SuperCSU.cpp
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sphere/csu
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sphere/csu/SuperCSU.o src/hamster/sphere/csu/SuperCSU.cpp

${OBJECTDIR}/src/hamster/sphere/semu/CentralSEMU.o: src/hamster/sphere/semu/CentralSEMU.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sphere/semu
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sphere/semu/CentralSEMU.o src/hamster/sphere/semu/CentralSEMU.cc

${OBJECTDIR}/src/hamster/sphere/semu/LocalSEMU.o: src/hamster/sphere/semu/LocalSEMU.cpp
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sphere/semu
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sphere/semu/LocalSEMU.o src/hamster/sphere/semu/LocalSEMU.cpp

${OBJECTDIR}/src/hamster/sphere/smu/CentralSMU.o: src/hamster/sphere/smu/CentralSMU.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sphere/smu
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sphere/smu/CentralSMU.o src/hamster/sphere/smu/CentralSMU.cc

${OBJECTDIR}/src/hamster/sphere/smu/LocalSMU.o: src/hamster/sphere/smu/LocalSMU.cpp
	${MKDIR} -p ${OBJECTDIR}/src/hamster/sphere/smu
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/sphere/smu/LocalSMU.o src/hamster/sphere/smu/LocalSMU.cpp

${OBJECTDIR}/src/hamster/utils/CSVReader.o: src/hamster/utils/CSVReader.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/utils/CSVReader.o src/hamster/utils/CSVReader.cc

${OBJECTDIR}/src/hamster/utils/Configurable.o: src/hamster/utils/Configurable.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/utils/Configurable.o src/hamster/utils/Configurable.cc

${OBJECTDIR}/src/hamster/utils/Uuid.o: src/hamster/utils/Uuid.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/utils/Uuid.o src/hamster/utils/Uuid.cc

${OBJECTDIR}/src/hamster/utils/logger/FileLogger.o: src/hamster/utils/logger/FileLogger.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/utils/logger
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/utils/logger/FileLogger.o src/hamster/utils/logger/FileLogger.cc

${OBJECTDIR}/src/hamster/utils/logger/HAMSTERLogger.o: src/hamster/utils/logger/HAMSTERLogger.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/utils/logger
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/utils/logger/HAMSTERLogger.o src/hamster/utils/logger/HAMSTERLogger.cc

${OBJECTDIR}/src/hamster/utils/logger/TerminalLogger.o: src/hamster/utils/logger/TerminalLogger.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/utils/logger
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/utils/logger/TerminalLogger.o src/hamster/utils/logger/TerminalLogger.cc

${OBJECTDIR}/src/hamster/utils/task/RunningTask.o: src/hamster/utils/task/RunningTask.cc
	${MKDIR} -p ${OBJECTDIR}/src/hamster/utils/task
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hamster/utils/task/RunningTask.o src/hamster/utils/task/RunningTask.cc

${OBJECTDIR}/src/tinyXML/tinystr.o: src/tinyXML/tinystr.cpp
	${MKDIR} -p ${OBJECTDIR}/src/tinyXML
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tinyXML/tinystr.o src/tinyXML/tinystr.cpp

${OBJECTDIR}/src/tinyXML/tinyxml.o: src/tinyXML/tinyxml.cpp
	${MKDIR} -p ${OBJECTDIR}/src/tinyXML
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tinyXML/tinyxml.o src/tinyXML/tinyxml.cpp

${OBJECTDIR}/src/tinyXML/tinyxmlerror.o: src/tinyXML/tinyxmlerror.cpp
	${MKDIR} -p ${OBJECTDIR}/src/tinyXML
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tinyXML/tinyxmlerror.o src/tinyXML/tinyxmlerror.cpp

${OBJECTDIR}/src/tinyXML/tinyxmlparser.o: src/tinyXML/tinyxmlparser.cpp
	${MKDIR} -p ${OBJECTDIR}/src/tinyXML
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tinyXML/tinyxmlparser.o src/tinyXML/tinyxmlparser.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
