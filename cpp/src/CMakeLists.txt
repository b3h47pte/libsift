ADD_EXECUTABLE(detectSift "detect_sift.cpp")
LIBSIFTCPP_ADD_DEPS(detectSift)
INSTALL(TARGETS detectSift
        RUNTIME DESTINATION bin)
