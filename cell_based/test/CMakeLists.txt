project(testcell_based)
if(MSVC)
set(HAS_OWN_LINKER_FLAGS TRUE)
set(LINKER_FLAGS "/NODEFAULTLIB:LIBCMT /NODEFAULTLIB:MSVCRT /NODEFAULTLIB:MSVCRTD")
#set(LINKER_FLAGS "/NODEFAULTLIB:LIBCMT /NODEFAULTLIB:LIBCMTD /NODEFAULTLIB:LIBCPMT")#unresolved externals getcwd etc.
endif()
chaste_do_test_component(cell_based)
