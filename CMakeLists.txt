CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#---------------------------------------------------------------------------------
# Define path variables
#---------------------------------------------------------------------------------

SET( DIR_1 "basis/include" )
SET( DIR_2 "preconditioner/include" )
SET( DIR_3 "mesh/include" )
SET( DIR_4 "input/include" )
SET( DIR_5 "timestep/include" )
SET( DIR_8 "error_estimator/include" )
SET( DIR_9 "post_process/include" )
SET( DIR_10 "elem_color/include" )
SET( DIR_11 "periodic_bc/include" )
SET( DIR_6 ${TRILINOS_DIR}lib )
SET( DIR_7 ${CMAKE_CURRENT_SOURCE_DIR} )

#---------------------------------------------------------------------------------
# Give access to TrilinosConfig.cmake in order to access its variables
#---------------------------------------------------------------------------------

INCLUDE( ${DIR_6}/cmake/Trilinos/TrilinosConfig.cmake )


#---------------------------------------------------------------------------------
# Give access to all subdirectories ( basis, basis/include, etc. )
#---------------------------------------------------------------------------------

INCLUDE_DIRECTORIES( ${Trilinos_TPL_INCLUDE_DIRS} ${DIR_1} ${DIR_2} ${DIR_3} 
  ${DIR_4} ${DIR_5} ${DIR_8} ${DIR_9} ${DIR_10} ${DIR_11} ${DIR_1}/.. ${DIR_2}/.. 
  ${DIR_3}/.. ${DIR_4}/.. ${DIR_5}/.. ${DIR_8}/.. ${DIR_10}/.. ${DIR_11}/..  )

#---------------------------------------------------------------------------------
# Change compiler. This must be done before PROJECT() specification
# We access the compiler variables from TrilinosConfig.cmake
#---------------------------------------------------------------------------------

SET( CMAKE_C_COMPILER ${Trilinos_C_COMPILER} )
SET( CMAKE_CXX_COMPILER ${Trilinos_CXX_COMPILER} )


#---------------------------------------------------------------------------------
# General information. Specify name and executable. 
# Let all contributing files feed into executable by saving them in SOURCES and 
# feeding the variable directly in ADD_EXECUTABLE()
#---------------------------------------------------------------------------------

SET( SOURCES 
${DIR_7}/tusas.cpp 	      		# Include DIR_7 which is the directory      #
${DIR_7}/mesh/Mesh.C			# that we are working in so that the other  #
${DIR_7}/mesh/include/Mesh.h		# paths can be based out of it              #
${DIR_7}/basis/basis.cpp 		
${DIR_7}/basis/include/basis.hpp 
${DIR_7}/input/ReadInput.cpp 
${DIR_7}/input/include/ReadInput.h 
${DIR_7}/error_estimator/error_estimator.cpp 
${DIR_7}/timestep/include/ModelEvaluatorNEMESIS_def.hpp
${DIR_7}/post_process/post_process.cpp 
${DIR_7}/post_process/include/post_process.h 
${DIR_7}/elem_color/elem_color.cpp 
${DIR_7}/periodic_bc/include/periodic_bc.h 
${DIR_7}/periodic_bc/periodic_bc.cpp 
)


PROJECT( TUSAS )

ADD_EXECUTABLE( tusas ${SOURCES} )


#---------------------------------------------------------------------------------
# Provide access to the Trilinos Libraries. This is done by first linking the 
# directory that holds the libraries, and using TARGET_LINK_LIBRARIES() to show
# the relationship between the executable and the libraries
#---------------------------------------------------------------------------------

INCLUDE_DIRECTORIES( ${Trilinos_INCLUDE_DIRS} )

TARGET_LINK_LIBRARIES( tusas ${Trilinos_LIBRARIES} ${Trilinos_TPL_LIBRARIES} )


  # Include Trilinos_INCLUDE_DIRS because many header files    #
  #  that are called in tusas.cpp exist here.	      	       #


#---------------------------------------------------------------------------------
# Change compiler flags. This must be done after  PROJECT() specification
#---------------------------------------------------------------------------------

SET( CMAKE_C_FLAGS ${Trilinos_C_COMPILER_FLAGS} )
SET( CMAKE_CXX_FLAGS "${Trilinos_CXX_COMPILER_FLAGS} ${TUSAS_CXX_FLAGS}" )


#---------------------------------------------------------------------------------
# Write tusas.h for use with Testing 
#---------------------------------------------------------------------------------

FILE ( WRITE ${DIR_7}/tusas.h "std::string TRILINOS_DIR=\"${TRILINOS_DIR}\"; ")

