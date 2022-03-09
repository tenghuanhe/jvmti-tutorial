#!/usr/bin/env bash
gcc -Wl, -g -fno-strict-aliasing -fPIC -fno-omit-frame-pointer -W -Wall  -Wno-unused -Wno-parentheses -I '/usr/lib/jvm/java-1.8.0-openjdk-1.8.0.322.b06-1.el7_9.x86_64/include/' -I '/usr/lib/jvm/java-1.8.0-openjdk-1.8.0.322.b06-1.el7_9.x86_64/include/linux' -c -o load_agent.o load_agent.c
gcc -shared -o libload_agent.so load_agent.o
LD_LIBRARY_PATH=`pwd` java -agentlib:load_agent Hello
