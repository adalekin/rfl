SET (project_LIB lib${PROJECT_NAME}_smtp)

FILE (GLOB_RECURSE rfl_smtp_SRCS *.cpp *.h *.hpp)
ADD_LIBRARY(${project_LIB} ${rfl_smtp_SRCS})

INSTALL(TARGETS ${project_LIB} DESTINATION lib)