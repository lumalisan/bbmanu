#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../Librerias/libSalvo/salvohook_interrupt_MCC30_IRQ.c ../Librerias/libSalvo/salvohook_wdt_MCC30_clrwdt.c ../Librerias/libSalvo/salvomem.c ../Librerias/libEncastats/delay.s ../Librerias/libEncastats/libCAD.c ../Librerias/libEncastats/libCAN.c ../Librerias/libEncastats/libKEYB.c ../Librerias/libEncastats/libLCD.c ../Librerias/libEncastats/libLEDs.c ../Librerias/libEncastats/libTIMER.c ../main_placa1.c ../main_placa2.c ../Librerias/libEncastats/putsUART1.c ../Librerias/libEncastats/CloseUART1.c ../Librerias/libEncastats/BusyUART1.c ../Librerias/libEncastats/ConfigIntUART1.c ../Librerias/libEncastats/ReadUART1.c ../Librerias/libEncastats/WriteUART1.c ../Librerias/libEncastats/DataRdyUART1.c ../Librerias/libEncastats/OpenUART1.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/2142485135/salvohook_interrupt_MCC30_IRQ.o ${OBJECTDIR}/_ext/2142485135/salvohook_wdt_MCC30_clrwdt.o ${OBJECTDIR}/_ext/2142485135/salvomem.o ${OBJECTDIR}/_ext/564672080/delay.o ${OBJECTDIR}/_ext/564672080/libCAD.o ${OBJECTDIR}/_ext/564672080/libCAN.o ${OBJECTDIR}/_ext/564672080/libKEYB.o ${OBJECTDIR}/_ext/564672080/libLCD.o ${OBJECTDIR}/_ext/564672080/libLEDs.o ${OBJECTDIR}/_ext/564672080/libTIMER.o ${OBJECTDIR}/_ext/1472/main_placa1.o ${OBJECTDIR}/_ext/1472/main_placa2.o ${OBJECTDIR}/_ext/564672080/putsUART1.o ${OBJECTDIR}/_ext/564672080/CloseUART1.o ${OBJECTDIR}/_ext/564672080/BusyUART1.o ${OBJECTDIR}/_ext/564672080/ConfigIntUART1.o ${OBJECTDIR}/_ext/564672080/ReadUART1.o ${OBJECTDIR}/_ext/564672080/WriteUART1.o ${OBJECTDIR}/_ext/564672080/DataRdyUART1.o ${OBJECTDIR}/_ext/564672080/OpenUART1.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/2142485135/salvohook_interrupt_MCC30_IRQ.o.d ${OBJECTDIR}/_ext/2142485135/salvohook_wdt_MCC30_clrwdt.o.d ${OBJECTDIR}/_ext/2142485135/salvomem.o.d ${OBJECTDIR}/_ext/564672080/delay.o.d ${OBJECTDIR}/_ext/564672080/libCAD.o.d ${OBJECTDIR}/_ext/564672080/libCAN.o.d ${OBJECTDIR}/_ext/564672080/libKEYB.o.d ${OBJECTDIR}/_ext/564672080/libLCD.o.d ${OBJECTDIR}/_ext/564672080/libLEDs.o.d ${OBJECTDIR}/_ext/564672080/libTIMER.o.d ${OBJECTDIR}/_ext/1472/main_placa1.o.d ${OBJECTDIR}/_ext/1472/main_placa2.o.d ${OBJECTDIR}/_ext/564672080/putsUART1.o.d ${OBJECTDIR}/_ext/564672080/CloseUART1.o.d ${OBJECTDIR}/_ext/564672080/BusyUART1.o.d ${OBJECTDIR}/_ext/564672080/ConfigIntUART1.o.d ${OBJECTDIR}/_ext/564672080/ReadUART1.o.d ${OBJECTDIR}/_ext/564672080/WriteUART1.o.d ${OBJECTDIR}/_ext/564672080/DataRdyUART1.o.d ${OBJECTDIR}/_ext/564672080/OpenUART1.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/2142485135/salvohook_interrupt_MCC30_IRQ.o ${OBJECTDIR}/_ext/2142485135/salvohook_wdt_MCC30_clrwdt.o ${OBJECTDIR}/_ext/2142485135/salvomem.o ${OBJECTDIR}/_ext/564672080/delay.o ${OBJECTDIR}/_ext/564672080/libCAD.o ${OBJECTDIR}/_ext/564672080/libCAN.o ${OBJECTDIR}/_ext/564672080/libKEYB.o ${OBJECTDIR}/_ext/564672080/libLCD.o ${OBJECTDIR}/_ext/564672080/libLEDs.o ${OBJECTDIR}/_ext/564672080/libTIMER.o ${OBJECTDIR}/_ext/1472/main_placa1.o ${OBJECTDIR}/_ext/1472/main_placa2.o ${OBJECTDIR}/_ext/564672080/putsUART1.o ${OBJECTDIR}/_ext/564672080/CloseUART1.o ${OBJECTDIR}/_ext/564672080/BusyUART1.o ${OBJECTDIR}/_ext/564672080/ConfigIntUART1.o ${OBJECTDIR}/_ext/564672080/ReadUART1.o ${OBJECTDIR}/_ext/564672080/WriteUART1.o ${OBJECTDIR}/_ext/564672080/DataRdyUART1.o ${OBJECTDIR}/_ext/564672080/OpenUART1.o

# Source Files
SOURCEFILES=../Librerias/libSalvo/salvohook_interrupt_MCC30_IRQ.c ../Librerias/libSalvo/salvohook_wdt_MCC30_clrwdt.c ../Librerias/libSalvo/salvomem.c ../Librerias/libEncastats/delay.s ../Librerias/libEncastats/libCAD.c ../Librerias/libEncastats/libCAN.c ../Librerias/libEncastats/libKEYB.c ../Librerias/libEncastats/libLCD.c ../Librerias/libEncastats/libLEDs.c ../Librerias/libEncastats/libTIMER.c ../main_placa1.c ../main_placa2.c ../Librerias/libEncastats/putsUART1.c ../Librerias/libEncastats/CloseUART1.c ../Librerias/libEncastats/BusyUART1.c ../Librerias/libEncastats/ConfigIntUART1.c ../Librerias/libEncastats/ReadUART1.c ../Librerias/libEncastats/WriteUART1.c ../Librerias/libEncastats/DataRdyUART1.c ../Librerias/libEncastats/OpenUART1.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=30F4011
MP_LINKER_FILE_OPTION=,--script="../Librerias/gld/p30F4011.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/2142485135/salvohook_interrupt_MCC30_IRQ.o: ../Librerias/libSalvo/salvohook_interrupt_MCC30_IRQ.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2142485135" 
	@${RM} ${OBJECTDIR}/_ext/2142485135/salvohook_interrupt_MCC30_IRQ.o.d 
	@${RM} ${OBJECTDIR}/_ext/2142485135/salvohook_interrupt_MCC30_IRQ.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libSalvo/salvohook_interrupt_MCC30_IRQ.c  -o ${OBJECTDIR}/_ext/2142485135/salvohook_interrupt_MCC30_IRQ.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2142485135/salvohook_interrupt_MCC30_IRQ.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/2142485135/salvohook_interrupt_MCC30_IRQ.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2142485135/salvohook_wdt_MCC30_clrwdt.o: ../Librerias/libSalvo/salvohook_wdt_MCC30_clrwdt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2142485135" 
	@${RM} ${OBJECTDIR}/_ext/2142485135/salvohook_wdt_MCC30_clrwdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/2142485135/salvohook_wdt_MCC30_clrwdt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libSalvo/salvohook_wdt_MCC30_clrwdt.c  -o ${OBJECTDIR}/_ext/2142485135/salvohook_wdt_MCC30_clrwdt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2142485135/salvohook_wdt_MCC30_clrwdt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/2142485135/salvohook_wdt_MCC30_clrwdt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2142485135/salvomem.o: ../Librerias/libSalvo/salvomem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2142485135" 
	@${RM} ${OBJECTDIR}/_ext/2142485135/salvomem.o.d 
	@${RM} ${OBJECTDIR}/_ext/2142485135/salvomem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libSalvo/salvomem.c  -o ${OBJECTDIR}/_ext/2142485135/salvomem.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2142485135/salvomem.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/2142485135/salvomem.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/libCAD.o: ../Librerias/libEncastats/libCAD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/libCAD.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/libCAD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/libCAD.c  -o ${OBJECTDIR}/_ext/564672080/libCAD.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/libCAD.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/libCAD.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/libCAN.o: ../Librerias/libEncastats/libCAN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/libCAN.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/libCAN.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/libCAN.c  -o ${OBJECTDIR}/_ext/564672080/libCAN.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/libCAN.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/libCAN.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/libKEYB.o: ../Librerias/libEncastats/libKEYB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/libKEYB.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/libKEYB.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/libKEYB.c  -o ${OBJECTDIR}/_ext/564672080/libKEYB.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/libKEYB.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/libKEYB.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/libLCD.o: ../Librerias/libEncastats/libLCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/libLCD.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/libLCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/libLCD.c  -o ${OBJECTDIR}/_ext/564672080/libLCD.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/libLCD.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/libLCD.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/libLEDs.o: ../Librerias/libEncastats/libLEDs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/libLEDs.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/libLEDs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/libLEDs.c  -o ${OBJECTDIR}/_ext/564672080/libLEDs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/libLEDs.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/libLEDs.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/libTIMER.o: ../Librerias/libEncastats/libTIMER.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/libTIMER.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/libTIMER.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/libTIMER.c  -o ${OBJECTDIR}/_ext/564672080/libTIMER.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/libTIMER.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/libTIMER.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/main_placa1.o: ../main_placa1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main_placa1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main_placa1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main_placa1.c  -o ${OBJECTDIR}/_ext/1472/main_placa1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/main_placa1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main_placa1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/main_placa2.o: ../main_placa2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main_placa2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main_placa2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main_placa2.c  -o ${OBJECTDIR}/_ext/1472/main_placa2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/main_placa2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main_placa2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/putsUART1.o: ../Librerias/libEncastats/putsUART1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/putsUART1.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/putsUART1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/putsUART1.c  -o ${OBJECTDIR}/_ext/564672080/putsUART1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/putsUART1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/putsUART1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/CloseUART1.o: ../Librerias/libEncastats/CloseUART1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/CloseUART1.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/CloseUART1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/CloseUART1.c  -o ${OBJECTDIR}/_ext/564672080/CloseUART1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/CloseUART1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/CloseUART1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/BusyUART1.o: ../Librerias/libEncastats/BusyUART1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/BusyUART1.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/BusyUART1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/BusyUART1.c  -o ${OBJECTDIR}/_ext/564672080/BusyUART1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/BusyUART1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/BusyUART1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/ConfigIntUART1.o: ../Librerias/libEncastats/ConfigIntUART1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/ConfigIntUART1.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/ConfigIntUART1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/ConfigIntUART1.c  -o ${OBJECTDIR}/_ext/564672080/ConfigIntUART1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/ConfigIntUART1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/ConfigIntUART1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/ReadUART1.o: ../Librerias/libEncastats/ReadUART1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/ReadUART1.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/ReadUART1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/ReadUART1.c  -o ${OBJECTDIR}/_ext/564672080/ReadUART1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/ReadUART1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/ReadUART1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/WriteUART1.o: ../Librerias/libEncastats/WriteUART1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/WriteUART1.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/WriteUART1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/WriteUART1.c  -o ${OBJECTDIR}/_ext/564672080/WriteUART1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/WriteUART1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/WriteUART1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/DataRdyUART1.o: ../Librerias/libEncastats/DataRdyUART1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/DataRdyUART1.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/DataRdyUART1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/DataRdyUART1.c  -o ${OBJECTDIR}/_ext/564672080/DataRdyUART1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/DataRdyUART1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/DataRdyUART1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/OpenUART1.o: ../Librerias/libEncastats/OpenUART1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/OpenUART1.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/OpenUART1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/OpenUART1.c  -o ${OBJECTDIR}/_ext/564672080/OpenUART1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/OpenUART1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/OpenUART1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/2142485135/salvohook_interrupt_MCC30_IRQ.o: ../Librerias/libSalvo/salvohook_interrupt_MCC30_IRQ.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2142485135" 
	@${RM} ${OBJECTDIR}/_ext/2142485135/salvohook_interrupt_MCC30_IRQ.o.d 
	@${RM} ${OBJECTDIR}/_ext/2142485135/salvohook_interrupt_MCC30_IRQ.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libSalvo/salvohook_interrupt_MCC30_IRQ.c  -o ${OBJECTDIR}/_ext/2142485135/salvohook_interrupt_MCC30_IRQ.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2142485135/salvohook_interrupt_MCC30_IRQ.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/2142485135/salvohook_interrupt_MCC30_IRQ.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2142485135/salvohook_wdt_MCC30_clrwdt.o: ../Librerias/libSalvo/salvohook_wdt_MCC30_clrwdt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2142485135" 
	@${RM} ${OBJECTDIR}/_ext/2142485135/salvohook_wdt_MCC30_clrwdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/2142485135/salvohook_wdt_MCC30_clrwdt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libSalvo/salvohook_wdt_MCC30_clrwdt.c  -o ${OBJECTDIR}/_ext/2142485135/salvohook_wdt_MCC30_clrwdt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2142485135/salvohook_wdt_MCC30_clrwdt.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/2142485135/salvohook_wdt_MCC30_clrwdt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2142485135/salvomem.o: ../Librerias/libSalvo/salvomem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2142485135" 
	@${RM} ${OBJECTDIR}/_ext/2142485135/salvomem.o.d 
	@${RM} ${OBJECTDIR}/_ext/2142485135/salvomem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libSalvo/salvomem.c  -o ${OBJECTDIR}/_ext/2142485135/salvomem.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2142485135/salvomem.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/2142485135/salvomem.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/libCAD.o: ../Librerias/libEncastats/libCAD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/libCAD.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/libCAD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/libCAD.c  -o ${OBJECTDIR}/_ext/564672080/libCAD.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/libCAD.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/libCAD.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/libCAN.o: ../Librerias/libEncastats/libCAN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/libCAN.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/libCAN.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/libCAN.c  -o ${OBJECTDIR}/_ext/564672080/libCAN.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/libCAN.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/libCAN.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/libKEYB.o: ../Librerias/libEncastats/libKEYB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/libKEYB.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/libKEYB.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/libKEYB.c  -o ${OBJECTDIR}/_ext/564672080/libKEYB.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/libKEYB.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/libKEYB.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/libLCD.o: ../Librerias/libEncastats/libLCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/libLCD.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/libLCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/libLCD.c  -o ${OBJECTDIR}/_ext/564672080/libLCD.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/libLCD.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/libLCD.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/libLEDs.o: ../Librerias/libEncastats/libLEDs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/libLEDs.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/libLEDs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/libLEDs.c  -o ${OBJECTDIR}/_ext/564672080/libLEDs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/libLEDs.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/libLEDs.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/libTIMER.o: ../Librerias/libEncastats/libTIMER.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/libTIMER.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/libTIMER.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/libTIMER.c  -o ${OBJECTDIR}/_ext/564672080/libTIMER.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/libTIMER.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/libTIMER.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/main_placa1.o: ../main_placa1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main_placa1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main_placa1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main_placa1.c  -o ${OBJECTDIR}/_ext/1472/main_placa1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/main_placa1.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main_placa1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/main_placa2.o: ../main_placa2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main_placa2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main_placa2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main_placa2.c  -o ${OBJECTDIR}/_ext/1472/main_placa2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/main_placa2.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main_placa2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/putsUART1.o: ../Librerias/libEncastats/putsUART1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/putsUART1.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/putsUART1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/putsUART1.c  -o ${OBJECTDIR}/_ext/564672080/putsUART1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/putsUART1.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/putsUART1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/CloseUART1.o: ../Librerias/libEncastats/CloseUART1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/CloseUART1.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/CloseUART1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/CloseUART1.c  -o ${OBJECTDIR}/_ext/564672080/CloseUART1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/CloseUART1.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/CloseUART1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/BusyUART1.o: ../Librerias/libEncastats/BusyUART1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/BusyUART1.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/BusyUART1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/BusyUART1.c  -o ${OBJECTDIR}/_ext/564672080/BusyUART1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/BusyUART1.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/BusyUART1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/ConfigIntUART1.o: ../Librerias/libEncastats/ConfigIntUART1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/ConfigIntUART1.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/ConfigIntUART1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/ConfigIntUART1.c  -o ${OBJECTDIR}/_ext/564672080/ConfigIntUART1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/ConfigIntUART1.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/ConfigIntUART1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/ReadUART1.o: ../Librerias/libEncastats/ReadUART1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/ReadUART1.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/ReadUART1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/ReadUART1.c  -o ${OBJECTDIR}/_ext/564672080/ReadUART1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/ReadUART1.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/ReadUART1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/WriteUART1.o: ../Librerias/libEncastats/WriteUART1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/WriteUART1.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/WriteUART1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/WriteUART1.c  -o ${OBJECTDIR}/_ext/564672080/WriteUART1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/WriteUART1.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/WriteUART1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/DataRdyUART1.o: ../Librerias/libEncastats/DataRdyUART1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/DataRdyUART1.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/DataRdyUART1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/DataRdyUART1.c  -o ${OBJECTDIR}/_ext/564672080/DataRdyUART1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/DataRdyUART1.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/DataRdyUART1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/564672080/OpenUART1.o: ../Librerias/libEncastats/OpenUART1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/OpenUART1.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/OpenUART1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Librerias/libEncastats/OpenUART1.c  -o ${OBJECTDIR}/_ext/564672080/OpenUART1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/564672080/OpenUART1.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../Librerias/libEncastats" -I"../Librerias/libSalvo" -I"../Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/gld" -I"../Y:/Downloads/bbmanu/Librerias/libEncastats" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo" -I"../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30" -I"../Y:/Downloads/bbmanu/Librerias/newLibCAD" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/OpenUART1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/564672080/delay.o: ../Librerias/libEncastats/delay.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/delay.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../Librerias/libEncastats/delay.s  -o ${OBJECTDIR}/_ext/564672080/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -I"." -Wa,-MD,"${OBJECTDIR}/_ext/564672080/delay.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/delay.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/564672080/delay.o: ../Librerias/libEncastats/delay.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/564672080" 
	@${RM} ${OBJECTDIR}/_ext/564672080/delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/564672080/delay.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../Librerias/libEncastats/delay.s  -o ${OBJECTDIR}/_ext/564672080/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -I"." -Wa,-MD,"${OBJECTDIR}/_ext/564672080/delay.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/564672080/delay.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../Librerias/libSalvo/MCC30/libsalvofmcc30s-t.a  ../Librerias/gld/p30F4011.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}    ../Librerias/libSalvo/MCC30/libsalvofmcc30s-t.a  -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)      -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="../Librerias/gld",--library-path="../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30",--library-path=".",--no-force-link,--smart-io,-Map="${DISTDIR}/final.X.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../Librerias/libSalvo/MCC30/libsalvofmcc30s-t.a ../Librerias/gld/p30F4011.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/final.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}    ../Librerias/libSalvo/MCC30/libsalvofmcc30s-t.a  -mcpu=$(MP_PROCESSOR_OPTION)        -omf=coff -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="../Librerias/gld",--library-path="../Y:/Downloads/bbmanu/Librerias/libSalvo/MCC30",--library-path=".",--no-force-link,--smart-io,-Map="${DISTDIR}/final.X.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/final.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=coff   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
