SET (project_BIN ${PROJECT_NAME}_acceptance_report)
SET (project_LIBS lib${PROJECT_NAME}_report lib${PROJECT_NAME}_dump)

FILE (GLOB_RECURSE rfl_acceptance_report_SRCS *.cpp *.h *.hpp)

ADD_EXECUTABLE(${project_BIN} ${rfl_acceptance_report_SRCS})
TARGET_LINK_LIBRARIES(${project_BIN} ${project_LIBS})

INSTALL(TARGETS ${project_BIN} DESTINATION bin)