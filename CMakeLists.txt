cmake_minimum_required(VERSION 3.8)
project(Lab6)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        linkedlist/linkedList.c
        linkedlist/linkedList.h
        linkedlist/listUtils.c
        linkedlist/listUtils.h
        linkedlist/requiredIncludes.h
        pipes/pipes.c
        pipes/pipes.h
        process/process.c
        process/process.h
        tokenize/makeArgs.c
        tokenize/makeArgs.h
        cscd340Lab6.c
        utils/myUtils.c
        utils/myUtils.h
        utils/fileUtil.c
        utils/fileUtil.h
        alias/alias.h
        alias/alias.c
        history/history.h
        history/history.c)

add_executable(Lab6 ${SOURCE_FILES})