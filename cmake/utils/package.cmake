
set(CPACK_PACKAGE_CONTACT aiglestiven@gmail.com)
if(UNIX )
    set(CPACK_GENERATOR TGZ)
elseif(WIN32)
    set(CPACK_GENERATOR ZIP)
endif()
set(CPACK_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME})
include(CPack)



