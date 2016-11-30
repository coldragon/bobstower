#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/affichage.o \
	${OBJECTDIR}/src/collision.o \
	${OBJECTDIR}/src/event.o \
	${OBJECTDIR}/src/init.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/object_power.o \
	${OBJECTDIR}/src/other_screen.o \
	${OBJECTDIR}/src/texture.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bobs_tower

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bobs_tower: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bobs_tower ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/affichage.o: src/affichage.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include/SDL -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/affichage.o src/affichage.c

${OBJECTDIR}/src/collision.o: src/collision.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include/SDL -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/collision.o src/collision.c

${OBJECTDIR}/src/event.o: src/event.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include/SDL -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/event.o src/event.c

${OBJECTDIR}/src/init.o: src/init.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include/SDL -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/init.o src/init.c

${OBJECTDIR}/src/main.o: src/main.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include/SDL -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.c

${OBJECTDIR}/src/object_power.o: src/object_power.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include/SDL -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/object_power.o src/object_power.c

${OBJECTDIR}/src/other_screen.o: src/other_screen.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include/SDL -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/other_screen.o src/other_screen.c

${OBJECTDIR}/src/texture.o: src/texture.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include/SDL -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/texture.o src/texture.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
