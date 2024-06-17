set(TESTSIMROT_NAME testSimulateRot)				#Naziv prvog projekta u solution-u

file(GLOB TESTSIMROT_SOURCES  ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
file(GLOB TESTSIMROT_INCS  ${CMAKE_CURRENT_LIST_DIR}/src/*.h)
set(TESTSIMROT_PLIST  ${CMAKE_CURRENT_LIST_DIR}/src/Info.plist)
file(GLOB TESTSIMROT_INC_TD  ${MY_INC}/td/*.h)
file(GLOB TESTSIMROT_INC_GUI ${MY_INC}/gui/*.h)
file(GLOB TESTSIMROT_INC_GUI_GL ${MY_INC}/gui/gl/*.h)
file(GLOB TESTSIMROT_INC_WINSOCKET ${CMAKE_CURRENT_LIST_DIR}/src/Socket/*.h)

# add executable
add_executable(${TESTSIMROT_NAME} ${TESTSIMROT_INCS} ${TESTSIMROT_SOURCES} ${TESTSIMROT_INC_TD} ${TESTSIMROT_INC_GUI} ${TESTSIMROT_INC_GUI_GL} ${TESTSIMROT_INC_WINSOCKET})

source_group("inc"            FILES ${TESTSIMROT_INCS})
source_group("src"            FILES ${TESTSIMROT_SOURCES})
source_group("inc\\td"        FILES ${TESTSIMROT_INC_TD})
source_group("inc\\gui"        FILES ${TESTSIMROT_INC_GUI})
source_group("inc\\gl"        FILES ${TESTSIMROT_INC_GUI_GL})
source_group("inc\\socket"        FILES ${TESTSIMROT_INC_WINSOCKET})

target_link_libraries(${TESTSIMROT_NAME} debug ${MU_LIB_DEBUG} optimized ${MU_LIB_RELEASE} 
									debug ${NATGUI_LIB_DEBUG} optimized ${NATGUI_LIB_RELEASE} 
								debug ${NATGL_LIB_DEBUG} optimized ${NATGL_LIB_RELEASE})

addMUCompileDefinitions(${TESTSIMROT_NAME})

setApplicationIcon(${TESTSIMROT_NAME} "${WORK_ROOT}/Common/WinIcons/apple.ico" "${CMAKE_CURRENT_LIST_DIR}/Common/Icons/apple128.png")

addOpenGLLibraries(${TESTSIMROT_NAME})

setTargetPropertiesForGUIApp(${TESTSIMROT_NAME} ${TESTSIMROT_PLIST})

setIDEPropertiesForGUIExecutable(${TESTSIMROT_NAME} ${CMAKE_CURRENT_LIST_DIR})

setPlatformDLLPath(${TESTSIMROT_NAME})



