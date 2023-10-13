g++ src/build.cpp -c -Wall -Werror -Wpedantic -o build/obj/build.o -O0 -ggdb
ar rcs build/lib/libuild.a build/obj/build.o
