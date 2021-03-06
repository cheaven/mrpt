INCLUDE(../../cmakemodules/AssureCMakeRootFile.cmake) # Avoid user mistake in CMake source directory

#-----------------------------------------------------------------
# CMake file for the MRPT application:  vOdometry
#
#  Run with "cmake ." at the root directory
#
#  October 2007, Jose Luis Blanco <jlblanco@ctima.uma.es>
#-----------------------------------------------------------------
PROJECT(vOdometry)

#MESSAGE(STATUS "Makefile for application: /apps/vOdometry")

if(0) # **Ey!** This app is unmaintaned? (JLBC 1-sep-2012)

# ---------------------------------------------
# TARGET:
# ---------------------------------------------
# Define the executable target:
ADD_EXECUTABLE(vOdometry Main.cpp ${MRPT_VERSION_RC_FILE})

SET(TMP_TARGET_NAME "vOdometry")



# Add the required libraries for linking:
TARGET_LINK_LIBRARIES(${TMP_TARGET_NAME} ${MRPT_LINKER_LIBS})

# Dependencies on MRPT libraries:
#  Just mention the top-level dependency, the rest will be detected automatically, 
#  and all the needed #include<> dirs added (see the script DeclareAppDependencies.cmake for further details)
DeclareAppDependencies(${TMP_TARGET_NAME} mrpt-vision mrpt-stereoslam mrpt-hwdrivers mrpt-slam)

IF(CMAKE_COMPILER_IS_GNUCXX)
	TARGET_LINK_LIBRARIES(${TMP_TARGET_NAME} mrpt-stereoslam${MRPT_LINKER_LIBS_POSTFIX})
ENDIF(CMAKE_COMPILER_IS_GNUCXX)


DeclareAppForInstall(${TMP_TARGET_NAME})

endif(0)
