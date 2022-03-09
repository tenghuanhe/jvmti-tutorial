#!/usr/bin/env bash
gcc -Wl, -g -fno-strict-aliasing -fPIC -fno-omit-frame-pointer -W -Wall  -Wno-unused -Wno-parentheses -I '/usr/lib/jvm/java-1.8.0-openjdk-1.8.0.322.b06-1.el7_9.x86_64/include/' -I '/usr/lib/jvm/java-1.8.0-openjdk-1.8.0.322.b06-1.el7_9.x86_64/include/linux' -c -o attach_agent.o attach_agent.c
gcc -shared -o libattach_agent.so attach_agent.o
