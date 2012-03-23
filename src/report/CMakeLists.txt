SET (project_LIB lib${PROJECT_NAME}_report)
SET (project_LIBS lib${PROJECT_NAME}_smtp)

FILE (GLOB_RECURSE rfl_report_SRCS *.cpp *.h *.hpp)
ADD_LIBRARY(${project_LIB} ${rfl_report_SRCS})
TARGET_LINK_LIBRARIES(${project_LIB} ${project_LIBS})

INSTALL(TARGETS ${project_LIB} DESTINATION lib)