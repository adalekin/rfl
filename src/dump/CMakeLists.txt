SET (project_LIB lib${PROJECT_NAME}_dump)

FILE (GLOB_RECURSE rfl_dump_SRCS *.cpp *.h *.hpp)
ADD_LIBRARY(${project_LIB} ${rfl_dump_SRCS})

INSTALL(TARGETS ${project_LIB} DESTINATION lib)