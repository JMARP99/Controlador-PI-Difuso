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
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/ControladorTemperatura.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/ControladorTemperatura.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=lib_pic/adc.c lib_pic/config_mcu.c lib_pic/keypad_4x4.c lib_pic/Control_temperatura_difuso.c lib_pic/eusart.c lib_pic/lcd.c mainControladorTemperatura.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/lib_pic/adc.p1 ${OBJECTDIR}/lib_pic/config_mcu.p1 ${OBJECTDIR}/lib_pic/keypad_4x4.p1 ${OBJECTDIR}/lib_pic/Control_temperatura_difuso.p1 ${OBJECTDIR}/lib_pic/eusart.p1 ${OBJECTDIR}/lib_pic/lcd.p1 ${OBJECTDIR}/mainControladorTemperatura.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/lib_pic/adc.p1.d ${OBJECTDIR}/lib_pic/config_mcu.p1.d ${OBJECTDIR}/lib_pic/keypad_4x4.p1.d ${OBJECTDIR}/lib_pic/Control_temperatura_difuso.p1.d ${OBJECTDIR}/lib_pic/eusart.p1.d ${OBJECTDIR}/lib_pic/lcd.p1.d ${OBJECTDIR}/mainControladorTemperatura.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/lib_pic/adc.p1 ${OBJECTDIR}/lib_pic/config_mcu.p1 ${OBJECTDIR}/lib_pic/keypad_4x4.p1 ${OBJECTDIR}/lib_pic/Control_temperatura_difuso.p1 ${OBJECTDIR}/lib_pic/eusart.p1 ${OBJECTDIR}/lib_pic/lcd.p1 ${OBJECTDIR}/mainControladorTemperatura.p1

# Source Files
SOURCEFILES=lib_pic/adc.c lib_pic/config_mcu.c lib_pic/keypad_4x4.c lib_pic/Control_temperatura_difuso.c lib_pic/eusart.c lib_pic/lcd.c mainControladorTemperatura.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/ControladorTemperatura.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F45K50
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/lib_pic/adc.p1: lib_pic/adc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib_pic" 
	@${RM} ${OBJECTDIR}/lib_pic/adc.p1.d 
	@${RM} ${OBJECTDIR}/lib_pic/adc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lib_pic/adc.p1 lib_pic/adc.c 
	@-${MV} ${OBJECTDIR}/lib_pic/adc.d ${OBJECTDIR}/lib_pic/adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib_pic/adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib_pic/config_mcu.p1: lib_pic/config_mcu.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib_pic" 
	@${RM} ${OBJECTDIR}/lib_pic/config_mcu.p1.d 
	@${RM} ${OBJECTDIR}/lib_pic/config_mcu.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lib_pic/config_mcu.p1 lib_pic/config_mcu.c 
	@-${MV} ${OBJECTDIR}/lib_pic/config_mcu.d ${OBJECTDIR}/lib_pic/config_mcu.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib_pic/config_mcu.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib_pic/keypad_4x4.p1: lib_pic/keypad_4x4.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib_pic" 
	@${RM} ${OBJECTDIR}/lib_pic/keypad_4x4.p1.d 
	@${RM} ${OBJECTDIR}/lib_pic/keypad_4x4.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lib_pic/keypad_4x4.p1 lib_pic/keypad_4x4.c 
	@-${MV} ${OBJECTDIR}/lib_pic/keypad_4x4.d ${OBJECTDIR}/lib_pic/keypad_4x4.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib_pic/keypad_4x4.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib_pic/Control_temperatura_difuso.p1: lib_pic/Control_temperatura_difuso.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib_pic" 
	@${RM} ${OBJECTDIR}/lib_pic/Control_temperatura_difuso.p1.d 
	@${RM} ${OBJECTDIR}/lib_pic/Control_temperatura_difuso.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lib_pic/Control_temperatura_difuso.p1 lib_pic/Control_temperatura_difuso.c 
	@-${MV} ${OBJECTDIR}/lib_pic/Control_temperatura_difuso.d ${OBJECTDIR}/lib_pic/Control_temperatura_difuso.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib_pic/Control_temperatura_difuso.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib_pic/eusart.p1: lib_pic/eusart.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib_pic" 
	@${RM} ${OBJECTDIR}/lib_pic/eusart.p1.d 
	@${RM} ${OBJECTDIR}/lib_pic/eusart.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lib_pic/eusart.p1 lib_pic/eusart.c 
	@-${MV} ${OBJECTDIR}/lib_pic/eusart.d ${OBJECTDIR}/lib_pic/eusart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib_pic/eusart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib_pic/lcd.p1: lib_pic/lcd.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib_pic" 
	@${RM} ${OBJECTDIR}/lib_pic/lcd.p1.d 
	@${RM} ${OBJECTDIR}/lib_pic/lcd.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lib_pic/lcd.p1 lib_pic/lcd.c 
	@-${MV} ${OBJECTDIR}/lib_pic/lcd.d ${OBJECTDIR}/lib_pic/lcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib_pic/lcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mainControladorTemperatura.p1: mainControladorTemperatura.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mainControladorTemperatura.p1.d 
	@${RM} ${OBJECTDIR}/mainControladorTemperatura.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mainControladorTemperatura.p1 mainControladorTemperatura.c 
	@-${MV} ${OBJECTDIR}/mainControladorTemperatura.d ${OBJECTDIR}/mainControladorTemperatura.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mainControladorTemperatura.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/lib_pic/adc.p1: lib_pic/adc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib_pic" 
	@${RM} ${OBJECTDIR}/lib_pic/adc.p1.d 
	@${RM} ${OBJECTDIR}/lib_pic/adc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lib_pic/adc.p1 lib_pic/adc.c 
	@-${MV} ${OBJECTDIR}/lib_pic/adc.d ${OBJECTDIR}/lib_pic/adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib_pic/adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib_pic/config_mcu.p1: lib_pic/config_mcu.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib_pic" 
	@${RM} ${OBJECTDIR}/lib_pic/config_mcu.p1.d 
	@${RM} ${OBJECTDIR}/lib_pic/config_mcu.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lib_pic/config_mcu.p1 lib_pic/config_mcu.c 
	@-${MV} ${OBJECTDIR}/lib_pic/config_mcu.d ${OBJECTDIR}/lib_pic/config_mcu.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib_pic/config_mcu.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib_pic/keypad_4x4.p1: lib_pic/keypad_4x4.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib_pic" 
	@${RM} ${OBJECTDIR}/lib_pic/keypad_4x4.p1.d 
	@${RM} ${OBJECTDIR}/lib_pic/keypad_4x4.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lib_pic/keypad_4x4.p1 lib_pic/keypad_4x4.c 
	@-${MV} ${OBJECTDIR}/lib_pic/keypad_4x4.d ${OBJECTDIR}/lib_pic/keypad_4x4.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib_pic/keypad_4x4.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib_pic/Control_temperatura_difuso.p1: lib_pic/Control_temperatura_difuso.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib_pic" 
	@${RM} ${OBJECTDIR}/lib_pic/Control_temperatura_difuso.p1.d 
	@${RM} ${OBJECTDIR}/lib_pic/Control_temperatura_difuso.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lib_pic/Control_temperatura_difuso.p1 lib_pic/Control_temperatura_difuso.c 
	@-${MV} ${OBJECTDIR}/lib_pic/Control_temperatura_difuso.d ${OBJECTDIR}/lib_pic/Control_temperatura_difuso.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib_pic/Control_temperatura_difuso.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib_pic/eusart.p1: lib_pic/eusart.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib_pic" 
	@${RM} ${OBJECTDIR}/lib_pic/eusart.p1.d 
	@${RM} ${OBJECTDIR}/lib_pic/eusart.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lib_pic/eusart.p1 lib_pic/eusart.c 
	@-${MV} ${OBJECTDIR}/lib_pic/eusart.d ${OBJECTDIR}/lib_pic/eusart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib_pic/eusart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lib_pic/lcd.p1: lib_pic/lcd.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lib_pic" 
	@${RM} ${OBJECTDIR}/lib_pic/lcd.p1.d 
	@${RM} ${OBJECTDIR}/lib_pic/lcd.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lib_pic/lcd.p1 lib_pic/lcd.c 
	@-${MV} ${OBJECTDIR}/lib_pic/lcd.d ${OBJECTDIR}/lib_pic/lcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lib_pic/lcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mainControladorTemperatura.p1: mainControladorTemperatura.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mainControladorTemperatura.p1.d 
	@${RM} ${OBJECTDIR}/mainControladorTemperatura.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mainControladorTemperatura.p1 mainControladorTemperatura.c 
	@-${MV} ${OBJECTDIR}/mainControladorTemperatura.d ${OBJECTDIR}/mainControladorTemperatura.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mainControladorTemperatura.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/ControladorTemperatura.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/ControladorTemperatura.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -mdebugger=pickit3  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto        $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/ControladorTemperatura.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} ${DISTDIR}/ControladorTemperatura.X.${IMAGE_TYPE}.hex 
	
else
${DISTDIR}/ControladorTemperatura.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/ControladorTemperatura.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/ControladorTemperatura.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
