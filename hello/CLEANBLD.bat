rem ######################################################
rem # Clean & Build                                      #
rem # Deletes all .obj and all executables and recreates #
rem # them usin wmake. Assumes openWatcom in PATH        #
rem ######################################################
del *.obj
del *.exe
wmake
