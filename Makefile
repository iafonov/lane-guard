#
#  Makefile for lane-guard
#  Created by Mustafa Ozcelikors on 12/22/20.
#
#  Lane Guard
#  Copyright © 2016 Igor Afonov. All rights reserved.
#

#======== Variables ==========
CC = g++
RM = rm -f
CFLAGS = -fPIC -I./LaneDetection -I./Console

#========= LaneGuard App ============
TARGET_APP ?= LaneGuard
SRCS_APP ?= LaneDetection/Configuration.cpp LaneDetection/State.cpp LaneDetection/LaneDepartureTracker.cpp LaneDetection/ProbePoint.cpp LaneDetection/ProbeLine.cpp LaneDetection/PerspectiveHelper.cpp LaneDetection/Detector.cpp LaneDetection/DetectedLane.cpp ./Console/EventsDelegate.cpp ./LaneDetection.cpp
OBJS_APP = $(SRCS_APP:.cpp=.o)
LDLIBS_APP = $(shell pkg-config opencv --libs)

$(TARGET_APP): $(OBJS_APP)
	$(CC) -o $@ $^ ${LDFLAGS} ${LDFLAGS_APP} ${LDLIBS_APP}

$(SRCS_APP:.cpp=.d):%.d:%.cpp
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS_APP:.cpp=.d)

#=========== Other targets ============
.PHONY: all clean
all: ${TARGET_APP}

clean:
	-${RM} ${TARGET_APP} ${OBJS_APP}
	${RM} -rf *.d
	${RM} -rf LaneDetection/*.d
