# CMakeList.txt : CMake project for SECundum_WebshopParser, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (SECundum_WebshopParser "SECundum_WebshopParser.cpp" "SECundum_WebshopParser.h" "CIFF/CIFFHeader.h" "CIFF/CIFFContent.h" "CIFF/CIFFContent.cpp" "CIFF/CIFFHeader.cpp" "CIFF/CIFFObject.cpp"   "Helper/CImg.h" "CAFF/CAFFHeader.h" "CAFF/CAFFCredits.h" "CAFF/CAFFAnimation.h" "CAFF/CAFFObject.h" "CAFF/CAFFObject.cpp" "CAFF/CAFFHeader.cpp" "CAFF/CAFFCredits.cpp" "CAFF/CAFFAnimation.cpp")

# TODO: Add tests and install targets if needed.
