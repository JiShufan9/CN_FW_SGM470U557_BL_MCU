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
ifeq "$(wildcard nbproject/Makefile-local-SGM_C21N17A_BL_CONFIG.mk)" "nbproject/Makefile-local-SGM_C21N17A_BL_CONFIG.mk"
include nbproject/Makefile-local-SGM_C21N17A_BL_CONFIG.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=SGM_C21N17A_BL_CONFIG
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SGM_C21N17A_BL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SGM_C21N17A_BL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/app/src/ClockApp.c ../src/app/src/CrcApp.c ../src/app/src/FlashRwApp.c ../src/app/src/FunApp.c ../src/app/src/I2c0SlaveApp.c ../src/app/src/MainApp.c ../src/app/src/PinIOApp.c ../src/app/src/SysTickApp.c ../src/app/src/Uart1App.c ../src/app/src/WatchDogApp.c ../src/app/src/InitApp.c ../src/app/src/AdcApp.c ../src/app/src/I2cMasterApp.c ../src/app/src/WakeCtrlApp.c ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/clock/plib_clock.c ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/evsys/plib_evsys.c ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/nvic/plib_nvic.c ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/nvmctrl/plib_nvmctrl.c ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/port/plib_port.c ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/sercom/usart/plib_sercom1_usart.c ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/systick/plib_systick.c ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/tcc/plib_tcc2.c ../src/config/SGM_C21N17A_BL_CONFIG/stdio/xc32_monitor.c ../src/config/SGM_C21N17A_BL_CONFIG/initialization.c ../src/config/SGM_C21N17A_BL_CONFIG/interrupts.c ../src/config/SGM_C21N17A_BL_CONFIG/exceptions.c ../src/config/SGM_C21N17A_BL_CONFIG/startup_xc32.c ../src/config/SGM_C21N17A_BL_CONFIG/libc_syscalls.c ../src/hal/plib_auo/src/adcon.c ../src/hal/plib_auo/src/Clock.c ../src/hal/plib_auo/src/I2CCommon.c ../src/hal/plib_auo/src/I2CSlave.c ../src/hal/plib_auo/src/NvmCtrl.c ../src/hal/plib_auo/src/ll_wdt.c ../src/hal/plib_auo/src/ll_port.c ../src/hal/src/ADCDriver.c ../src/hal/src/ClockDriver.c ../src/hal/src/FmcDriver.c ../src/hal/src/I2CSDriver.c ../src/hal/src/RegsAccessDriver.c ../src/hal/src/hal_wdt.c ../src/hal/src/PortDriver.c ../src/hal/plib_auo/src/Sercom2MasterI2C.c ../src/hal/plib_auo/src/ll_eic.c ../src/hal/plib_auo/src/ll_pm.c ../src/hal/src/EicDriver.c ../src/hal/src/I2CMDriver.c ../src/hal/src/PMDriver.c ../src/hal/src/PwmDriver.c ../src/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1075956228/ClockApp.o ${OBJECTDIR}/_ext/1075956228/CrcApp.o ${OBJECTDIR}/_ext/1075956228/FlashRwApp.o ${OBJECTDIR}/_ext/1075956228/FunApp.o ${OBJECTDIR}/_ext/1075956228/I2c0SlaveApp.o ${OBJECTDIR}/_ext/1075956228/MainApp.o ${OBJECTDIR}/_ext/1075956228/PinIOApp.o ${OBJECTDIR}/_ext/1075956228/SysTickApp.o ${OBJECTDIR}/_ext/1075956228/Uart1App.o ${OBJECTDIR}/_ext/1075956228/WatchDogApp.o ${OBJECTDIR}/_ext/1075956228/InitApp.o ${OBJECTDIR}/_ext/1075956228/AdcApp.o ${OBJECTDIR}/_ext/1075956228/I2cMasterApp.o ${OBJECTDIR}/_ext/1075956228/WakeCtrlApp.o ${OBJECTDIR}/_ext/609943780/plib_clock.o ${OBJECTDIR}/_ext/607794294/plib_evsys.o ${OBJECTDIR}/_ext/257756180/plib_nvic.o ${OBJECTDIR}/_ext/583357666/plib_nvmctrl.o ${OBJECTDIR}/_ext/257809331/plib_port.o ${OBJECTDIR}/_ext/297074231/plib_sercom1_usart.o ${OBJECTDIR}/_ext/348882568/plib_systick.o ${OBJECTDIR}/_ext/1377153438/plib_tcc2.o ${OBJECTDIR}/_ext/1856207816/xc32_monitor.o ${OBJECTDIR}/_ext/2139064974/initialization.o ${OBJECTDIR}/_ext/2139064974/interrupts.o ${OBJECTDIR}/_ext/2139064974/exceptions.o ${OBJECTDIR}/_ext/2139064974/startup_xc32.o ${OBJECTDIR}/_ext/2139064974/libc_syscalls.o ${OBJECTDIR}/_ext/1822170596/adcon.o ${OBJECTDIR}/_ext/1822170596/Clock.o ${OBJECTDIR}/_ext/1822170596/I2CCommon.o ${OBJECTDIR}/_ext/1822170596/I2CSlave.o ${OBJECTDIR}/_ext/1822170596/NvmCtrl.o ${OBJECTDIR}/_ext/1822170596/ll_wdt.o ${OBJECTDIR}/_ext/1822170596/ll_port.o ${OBJECTDIR}/_ext/408470894/ADCDriver.o ${OBJECTDIR}/_ext/408470894/ClockDriver.o ${OBJECTDIR}/_ext/408470894/FmcDriver.o ${OBJECTDIR}/_ext/408470894/I2CSDriver.o ${OBJECTDIR}/_ext/408470894/RegsAccessDriver.o ${OBJECTDIR}/_ext/408470894/hal_wdt.o ${OBJECTDIR}/_ext/408470894/PortDriver.o ${OBJECTDIR}/_ext/1822170596/Sercom2MasterI2C.o ${OBJECTDIR}/_ext/1822170596/ll_eic.o ${OBJECTDIR}/_ext/1822170596/ll_pm.o ${OBJECTDIR}/_ext/408470894/EicDriver.o ${OBJECTDIR}/_ext/408470894/I2CMDriver.o ${OBJECTDIR}/_ext/408470894/PMDriver.o ${OBJECTDIR}/_ext/408470894/PwmDriver.o ${OBJECTDIR}/_ext/1360937237/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1075956228/ClockApp.o.d ${OBJECTDIR}/_ext/1075956228/CrcApp.o.d ${OBJECTDIR}/_ext/1075956228/FlashRwApp.o.d ${OBJECTDIR}/_ext/1075956228/FunApp.o.d ${OBJECTDIR}/_ext/1075956228/I2c0SlaveApp.o.d ${OBJECTDIR}/_ext/1075956228/MainApp.o.d ${OBJECTDIR}/_ext/1075956228/PinIOApp.o.d ${OBJECTDIR}/_ext/1075956228/SysTickApp.o.d ${OBJECTDIR}/_ext/1075956228/Uart1App.o.d ${OBJECTDIR}/_ext/1075956228/WatchDogApp.o.d ${OBJECTDIR}/_ext/1075956228/InitApp.o.d ${OBJECTDIR}/_ext/1075956228/AdcApp.o.d ${OBJECTDIR}/_ext/1075956228/I2cMasterApp.o.d ${OBJECTDIR}/_ext/1075956228/WakeCtrlApp.o.d ${OBJECTDIR}/_ext/609943780/plib_clock.o.d ${OBJECTDIR}/_ext/607794294/plib_evsys.o.d ${OBJECTDIR}/_ext/257756180/plib_nvic.o.d ${OBJECTDIR}/_ext/583357666/plib_nvmctrl.o.d ${OBJECTDIR}/_ext/257809331/plib_port.o.d ${OBJECTDIR}/_ext/297074231/plib_sercom1_usart.o.d ${OBJECTDIR}/_ext/348882568/plib_systick.o.d ${OBJECTDIR}/_ext/1377153438/plib_tcc2.o.d ${OBJECTDIR}/_ext/1856207816/xc32_monitor.o.d ${OBJECTDIR}/_ext/2139064974/initialization.o.d ${OBJECTDIR}/_ext/2139064974/interrupts.o.d ${OBJECTDIR}/_ext/2139064974/exceptions.o.d ${OBJECTDIR}/_ext/2139064974/startup_xc32.o.d ${OBJECTDIR}/_ext/2139064974/libc_syscalls.o.d ${OBJECTDIR}/_ext/1822170596/adcon.o.d ${OBJECTDIR}/_ext/1822170596/Clock.o.d ${OBJECTDIR}/_ext/1822170596/I2CCommon.o.d ${OBJECTDIR}/_ext/1822170596/I2CSlave.o.d ${OBJECTDIR}/_ext/1822170596/NvmCtrl.o.d ${OBJECTDIR}/_ext/1822170596/ll_wdt.o.d ${OBJECTDIR}/_ext/1822170596/ll_port.o.d ${OBJECTDIR}/_ext/408470894/ADCDriver.o.d ${OBJECTDIR}/_ext/408470894/ClockDriver.o.d ${OBJECTDIR}/_ext/408470894/FmcDriver.o.d ${OBJECTDIR}/_ext/408470894/I2CSDriver.o.d ${OBJECTDIR}/_ext/408470894/RegsAccessDriver.o.d ${OBJECTDIR}/_ext/408470894/hal_wdt.o.d ${OBJECTDIR}/_ext/408470894/PortDriver.o.d ${OBJECTDIR}/_ext/1822170596/Sercom2MasterI2C.o.d ${OBJECTDIR}/_ext/1822170596/ll_eic.o.d ${OBJECTDIR}/_ext/1822170596/ll_pm.o.d ${OBJECTDIR}/_ext/408470894/EicDriver.o.d ${OBJECTDIR}/_ext/408470894/I2CMDriver.o.d ${OBJECTDIR}/_ext/408470894/PMDriver.o.d ${OBJECTDIR}/_ext/408470894/PwmDriver.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1075956228/ClockApp.o ${OBJECTDIR}/_ext/1075956228/CrcApp.o ${OBJECTDIR}/_ext/1075956228/FlashRwApp.o ${OBJECTDIR}/_ext/1075956228/FunApp.o ${OBJECTDIR}/_ext/1075956228/I2c0SlaveApp.o ${OBJECTDIR}/_ext/1075956228/MainApp.o ${OBJECTDIR}/_ext/1075956228/PinIOApp.o ${OBJECTDIR}/_ext/1075956228/SysTickApp.o ${OBJECTDIR}/_ext/1075956228/Uart1App.o ${OBJECTDIR}/_ext/1075956228/WatchDogApp.o ${OBJECTDIR}/_ext/1075956228/InitApp.o ${OBJECTDIR}/_ext/1075956228/AdcApp.o ${OBJECTDIR}/_ext/1075956228/I2cMasterApp.o ${OBJECTDIR}/_ext/1075956228/WakeCtrlApp.o ${OBJECTDIR}/_ext/609943780/plib_clock.o ${OBJECTDIR}/_ext/607794294/plib_evsys.o ${OBJECTDIR}/_ext/257756180/plib_nvic.o ${OBJECTDIR}/_ext/583357666/plib_nvmctrl.o ${OBJECTDIR}/_ext/257809331/plib_port.o ${OBJECTDIR}/_ext/297074231/plib_sercom1_usart.o ${OBJECTDIR}/_ext/348882568/plib_systick.o ${OBJECTDIR}/_ext/1377153438/plib_tcc2.o ${OBJECTDIR}/_ext/1856207816/xc32_monitor.o ${OBJECTDIR}/_ext/2139064974/initialization.o ${OBJECTDIR}/_ext/2139064974/interrupts.o ${OBJECTDIR}/_ext/2139064974/exceptions.o ${OBJECTDIR}/_ext/2139064974/startup_xc32.o ${OBJECTDIR}/_ext/2139064974/libc_syscalls.o ${OBJECTDIR}/_ext/1822170596/adcon.o ${OBJECTDIR}/_ext/1822170596/Clock.o ${OBJECTDIR}/_ext/1822170596/I2CCommon.o ${OBJECTDIR}/_ext/1822170596/I2CSlave.o ${OBJECTDIR}/_ext/1822170596/NvmCtrl.o ${OBJECTDIR}/_ext/1822170596/ll_wdt.o ${OBJECTDIR}/_ext/1822170596/ll_port.o ${OBJECTDIR}/_ext/408470894/ADCDriver.o ${OBJECTDIR}/_ext/408470894/ClockDriver.o ${OBJECTDIR}/_ext/408470894/FmcDriver.o ${OBJECTDIR}/_ext/408470894/I2CSDriver.o ${OBJECTDIR}/_ext/408470894/RegsAccessDriver.o ${OBJECTDIR}/_ext/408470894/hal_wdt.o ${OBJECTDIR}/_ext/408470894/PortDriver.o ${OBJECTDIR}/_ext/1822170596/Sercom2MasterI2C.o ${OBJECTDIR}/_ext/1822170596/ll_eic.o ${OBJECTDIR}/_ext/1822170596/ll_pm.o ${OBJECTDIR}/_ext/408470894/EicDriver.o ${OBJECTDIR}/_ext/408470894/I2CMDriver.o ${OBJECTDIR}/_ext/408470894/PMDriver.o ${OBJECTDIR}/_ext/408470894/PwmDriver.o ${OBJECTDIR}/_ext/1360937237/main.o

# Source Files
SOURCEFILES=../src/app/src/ClockApp.c ../src/app/src/CrcApp.c ../src/app/src/FlashRwApp.c ../src/app/src/FunApp.c ../src/app/src/I2c0SlaveApp.c ../src/app/src/MainApp.c ../src/app/src/PinIOApp.c ../src/app/src/SysTickApp.c ../src/app/src/Uart1App.c ../src/app/src/WatchDogApp.c ../src/app/src/InitApp.c ../src/app/src/AdcApp.c ../src/app/src/I2cMasterApp.c ../src/app/src/WakeCtrlApp.c ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/clock/plib_clock.c ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/evsys/plib_evsys.c ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/nvic/plib_nvic.c ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/nvmctrl/plib_nvmctrl.c ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/port/plib_port.c ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/sercom/usart/plib_sercom1_usart.c ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/systick/plib_systick.c ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/tcc/plib_tcc2.c ../src/config/SGM_C21N17A_BL_CONFIG/stdio/xc32_monitor.c ../src/config/SGM_C21N17A_BL_CONFIG/initialization.c ../src/config/SGM_C21N17A_BL_CONFIG/interrupts.c ../src/config/SGM_C21N17A_BL_CONFIG/exceptions.c ../src/config/SGM_C21N17A_BL_CONFIG/startup_xc32.c ../src/config/SGM_C21N17A_BL_CONFIG/libc_syscalls.c ../src/hal/plib_auo/src/adcon.c ../src/hal/plib_auo/src/Clock.c ../src/hal/plib_auo/src/I2CCommon.c ../src/hal/plib_auo/src/I2CSlave.c ../src/hal/plib_auo/src/NvmCtrl.c ../src/hal/plib_auo/src/ll_wdt.c ../src/hal/plib_auo/src/ll_port.c ../src/hal/src/ADCDriver.c ../src/hal/src/ClockDriver.c ../src/hal/src/FmcDriver.c ../src/hal/src/I2CSDriver.c ../src/hal/src/RegsAccessDriver.c ../src/hal/src/hal_wdt.c ../src/hal/src/PortDriver.c ../src/hal/plib_auo/src/Sercom2MasterI2C.c ../src/hal/plib_auo/src/ll_eic.c ../src/hal/plib_auo/src/ll_pm.c ../src/hal/src/EicDriver.c ../src/hal/src/I2CMDriver.c ../src/hal/src/PMDriver.c ../src/hal/src/PwmDriver.c ../src/main.c

# Pack Options 
PACK_COMMON_OPTIONS=-I "${CMSIS_DIR}/CMSIS/Core/Include"



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

# The following macros may be used in the pre and post step lines
Device=ATSAMC21N17A
ProjectDir="C:\sgm\temp_v3\214\TM_FW_SGMBootloader_MCU\SGM_C21N17A_BL.X"
ProjectName=SGM_C21N17A_BL
ConfName=SGM_C21N17A_BL_CONFIG
ImagePath="dist\SGM_C21N17A_BL_CONFIG\${IMAGE_TYPE}\SGM_C21N17A_BL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\SGM_C21N17A_BL_CONFIG\${IMAGE_TYPE}"
ImageName="SGM_C21N17A_BL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-SGM_C21N17A_BL_CONFIG.mk dist/${CND_CONF}/${IMAGE_TYPE}/SGM_C21N17A_BL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: [${MP_CC_DIR}/xc32-objcopy -I ihex -O binary ${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.hex ${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.bin]"
	@${MP_CC_DIR}/xc32-objcopy -I ihex -O binary ${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.hex ${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.bin
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=ATSAMC21N17A
MP_LINKER_FILE_OPTION=,--script="..\src\config\SGM_C21N17A_BL_CONFIG\ATSAMC21N17A.ld"
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
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1075956228/ClockApp.o: ../src/app/src/ClockApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/ClockApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/ClockApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/ClockApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/ClockApp.o ../src/app/src/ClockApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/ClockApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/CrcApp.o: ../src/app/src/CrcApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/CrcApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/CrcApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/CrcApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/CrcApp.o ../src/app/src/CrcApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/CrcApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/FlashRwApp.o: ../src/app/src/FlashRwApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/FlashRwApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/FlashRwApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/FlashRwApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/FlashRwApp.o ../src/app/src/FlashRwApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/FlashRwApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/FunApp.o: ../src/app/src/FunApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/FunApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/FunApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/FunApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/FunApp.o ../src/app/src/FunApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/FunApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/I2c0SlaveApp.o: ../src/app/src/I2c0SlaveApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/I2c0SlaveApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/I2c0SlaveApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/I2c0SlaveApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/I2c0SlaveApp.o ../src/app/src/I2c0SlaveApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/I2c0SlaveApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/MainApp.o: ../src/app/src/MainApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/MainApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/MainApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/MainApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/MainApp.o ../src/app/src/MainApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/MainApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/PinIOApp.o: ../src/app/src/PinIOApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/PinIOApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/PinIOApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/PinIOApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/PinIOApp.o ../src/app/src/PinIOApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/PinIOApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/SysTickApp.o: ../src/app/src/SysTickApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/SysTickApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/SysTickApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/SysTickApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/SysTickApp.o ../src/app/src/SysTickApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/SysTickApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/Uart1App.o: ../src/app/src/Uart1App.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/Uart1App.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/Uart1App.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/Uart1App.o.d" -o ${OBJECTDIR}/_ext/1075956228/Uart1App.o ../src/app/src/Uart1App.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/Uart1App.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/WatchDogApp.o: ../src/app/src/WatchDogApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/WatchDogApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/WatchDogApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/WatchDogApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/WatchDogApp.o ../src/app/src/WatchDogApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/WatchDogApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/InitApp.o: ../src/app/src/InitApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/InitApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/InitApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/InitApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/InitApp.o ../src/app/src/InitApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/InitApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/AdcApp.o: ../src/app/src/AdcApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/AdcApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/AdcApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/AdcApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/AdcApp.o ../src/app/src/AdcApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/AdcApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/I2cMasterApp.o: ../src/app/src/I2cMasterApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/I2cMasterApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/I2cMasterApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/I2cMasterApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/I2cMasterApp.o ../src/app/src/I2cMasterApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/I2cMasterApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/WakeCtrlApp.o: ../src/app/src/WakeCtrlApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/WakeCtrlApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/WakeCtrlApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/WakeCtrlApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/WakeCtrlApp.o ../src/app/src/WakeCtrlApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/WakeCtrlApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/609943780/plib_clock.o: ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/clock/plib_clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/609943780" 
	@${RM} ${OBJECTDIR}/_ext/609943780/plib_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/609943780/plib_clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/609943780/plib_clock.o.d" -o ${OBJECTDIR}/_ext/609943780/plib_clock.o ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/clock/plib_clock.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/609943780/plib_clock.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/607794294/plib_evsys.o: ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/evsys/plib_evsys.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/607794294" 
	@${RM} ${OBJECTDIR}/_ext/607794294/plib_evsys.o.d 
	@${RM} ${OBJECTDIR}/_ext/607794294/plib_evsys.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/607794294/plib_evsys.o.d" -o ${OBJECTDIR}/_ext/607794294/plib_evsys.o ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/evsys/plib_evsys.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/607794294/plib_evsys.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/257756180/plib_nvic.o: ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/nvic/plib_nvic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/257756180" 
	@${RM} ${OBJECTDIR}/_ext/257756180/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/257756180/plib_nvic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/257756180/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/257756180/plib_nvic.o ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/nvic/plib_nvic.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/257756180/plib_nvic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/583357666/plib_nvmctrl.o: ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/nvmctrl/plib_nvmctrl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/583357666" 
	@${RM} ${OBJECTDIR}/_ext/583357666/plib_nvmctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/583357666/plib_nvmctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/583357666/plib_nvmctrl.o.d" -o ${OBJECTDIR}/_ext/583357666/plib_nvmctrl.o ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/nvmctrl/plib_nvmctrl.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/583357666/plib_nvmctrl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/257809331/plib_port.o: ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/port/plib_port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/257809331" 
	@${RM} ${OBJECTDIR}/_ext/257809331/plib_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/257809331/plib_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/257809331/plib_port.o.d" -o ${OBJECTDIR}/_ext/257809331/plib_port.o ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/port/plib_port.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/257809331/plib_port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/297074231/plib_sercom1_usart.o: ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/sercom/usart/plib_sercom1_usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/297074231" 
	@${RM} ${OBJECTDIR}/_ext/297074231/plib_sercom1_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/297074231/plib_sercom1_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/297074231/plib_sercom1_usart.o.d" -o ${OBJECTDIR}/_ext/297074231/plib_sercom1_usart.o ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/sercom/usart/plib_sercom1_usart.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/297074231/plib_sercom1_usart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/348882568/plib_systick.o: ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/systick/plib_systick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/348882568" 
	@${RM} ${OBJECTDIR}/_ext/348882568/plib_systick.o.d 
	@${RM} ${OBJECTDIR}/_ext/348882568/plib_systick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/348882568/plib_systick.o.d" -o ${OBJECTDIR}/_ext/348882568/plib_systick.o ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/systick/plib_systick.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/348882568/plib_systick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1377153438/plib_tcc2.o: ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/tcc/plib_tcc2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1377153438" 
	@${RM} ${OBJECTDIR}/_ext/1377153438/plib_tcc2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1377153438/plib_tcc2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1377153438/plib_tcc2.o.d" -o ${OBJECTDIR}/_ext/1377153438/plib_tcc2.o ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/tcc/plib_tcc2.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1377153438/plib_tcc2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1856207816/xc32_monitor.o: ../src/config/SGM_C21N17A_BL_CONFIG/stdio/xc32_monitor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1856207816" 
	@${RM} ${OBJECTDIR}/_ext/1856207816/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1856207816/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1856207816/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/1856207816/xc32_monitor.o ../src/config/SGM_C21N17A_BL_CONFIG/stdio/xc32_monitor.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1856207816/xc32_monitor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2139064974/initialization.o: ../src/config/SGM_C21N17A_BL_CONFIG/initialization.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139064974" 
	@${RM} ${OBJECTDIR}/_ext/2139064974/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/2139064974/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2139064974/initialization.o.d" -o ${OBJECTDIR}/_ext/2139064974/initialization.o ../src/config/SGM_C21N17A_BL_CONFIG/initialization.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2139064974/initialization.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2139064974/interrupts.o: ../src/config/SGM_C21N17A_BL_CONFIG/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139064974" 
	@${RM} ${OBJECTDIR}/_ext/2139064974/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/2139064974/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2139064974/interrupts.o.d" -o ${OBJECTDIR}/_ext/2139064974/interrupts.o ../src/config/SGM_C21N17A_BL_CONFIG/interrupts.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2139064974/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2139064974/exceptions.o: ../src/config/SGM_C21N17A_BL_CONFIG/exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139064974" 
	@${RM} ${OBJECTDIR}/_ext/2139064974/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/2139064974/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2139064974/exceptions.o.d" -o ${OBJECTDIR}/_ext/2139064974/exceptions.o ../src/config/SGM_C21N17A_BL_CONFIG/exceptions.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2139064974/exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2139064974/startup_xc32.o: ../src/config/SGM_C21N17A_BL_CONFIG/startup_xc32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139064974" 
	@${RM} ${OBJECTDIR}/_ext/2139064974/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/2139064974/startup_xc32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2139064974/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/2139064974/startup_xc32.o ../src/config/SGM_C21N17A_BL_CONFIG/startup_xc32.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2139064974/startup_xc32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2139064974/libc_syscalls.o: ../src/config/SGM_C21N17A_BL_CONFIG/libc_syscalls.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139064974" 
	@${RM} ${OBJECTDIR}/_ext/2139064974/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/2139064974/libc_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2139064974/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/2139064974/libc_syscalls.o ../src/config/SGM_C21N17A_BL_CONFIG/libc_syscalls.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2139064974/libc_syscalls.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1822170596/adcon.o: ../src/hal/plib_auo/src/adcon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1822170596" 
	@${RM} ${OBJECTDIR}/_ext/1822170596/adcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1822170596/adcon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1822170596/adcon.o.d" -o ${OBJECTDIR}/_ext/1822170596/adcon.o ../src/hal/plib_auo/src/adcon.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1822170596/adcon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1822170596/Clock.o: ../src/hal/plib_auo/src/Clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1822170596" 
	@${RM} ${OBJECTDIR}/_ext/1822170596/Clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1822170596/Clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1822170596/Clock.o.d" -o ${OBJECTDIR}/_ext/1822170596/Clock.o ../src/hal/plib_auo/src/Clock.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1822170596/Clock.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1822170596/I2CCommon.o: ../src/hal/plib_auo/src/I2CCommon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1822170596" 
	@${RM} ${OBJECTDIR}/_ext/1822170596/I2CCommon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1822170596/I2CCommon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1822170596/I2CCommon.o.d" -o ${OBJECTDIR}/_ext/1822170596/I2CCommon.o ../src/hal/plib_auo/src/I2CCommon.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1822170596/I2CCommon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1822170596/I2CSlave.o: ../src/hal/plib_auo/src/I2CSlave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1822170596" 
	@${RM} ${OBJECTDIR}/_ext/1822170596/I2CSlave.o.d 
	@${RM} ${OBJECTDIR}/_ext/1822170596/I2CSlave.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1822170596/I2CSlave.o.d" -o ${OBJECTDIR}/_ext/1822170596/I2CSlave.o ../src/hal/plib_auo/src/I2CSlave.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1822170596/I2CSlave.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1822170596/NvmCtrl.o: ../src/hal/plib_auo/src/NvmCtrl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1822170596" 
	@${RM} ${OBJECTDIR}/_ext/1822170596/NvmCtrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1822170596/NvmCtrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1822170596/NvmCtrl.o.d" -o ${OBJECTDIR}/_ext/1822170596/NvmCtrl.o ../src/hal/plib_auo/src/NvmCtrl.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1822170596/NvmCtrl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1822170596/ll_wdt.o: ../src/hal/plib_auo/src/ll_wdt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1822170596" 
	@${RM} ${OBJECTDIR}/_ext/1822170596/ll_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1822170596/ll_wdt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1822170596/ll_wdt.o.d" -o ${OBJECTDIR}/_ext/1822170596/ll_wdt.o ../src/hal/plib_auo/src/ll_wdt.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1822170596/ll_wdt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1822170596/ll_port.o: ../src/hal/plib_auo/src/ll_port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1822170596" 
	@${RM} ${OBJECTDIR}/_ext/1822170596/ll_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1822170596/ll_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1822170596/ll_port.o.d" -o ${OBJECTDIR}/_ext/1822170596/ll_port.o ../src/hal/plib_auo/src/ll_port.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1822170596/ll_port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/ADCDriver.o: ../src/hal/src/ADCDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/ADCDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/ADCDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/ADCDriver.o.d" -o ${OBJECTDIR}/_ext/408470894/ADCDriver.o ../src/hal/src/ADCDriver.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/ADCDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/ClockDriver.o: ../src/hal/src/ClockDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/ClockDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/ClockDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/ClockDriver.o.d" -o ${OBJECTDIR}/_ext/408470894/ClockDriver.o ../src/hal/src/ClockDriver.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/ClockDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/FmcDriver.o: ../src/hal/src/FmcDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/FmcDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/FmcDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/FmcDriver.o.d" -o ${OBJECTDIR}/_ext/408470894/FmcDriver.o ../src/hal/src/FmcDriver.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/FmcDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/I2CSDriver.o: ../src/hal/src/I2CSDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/I2CSDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/I2CSDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/I2CSDriver.o.d" -o ${OBJECTDIR}/_ext/408470894/I2CSDriver.o ../src/hal/src/I2CSDriver.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/I2CSDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/RegsAccessDriver.o: ../src/hal/src/RegsAccessDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/RegsAccessDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/RegsAccessDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/RegsAccessDriver.o.d" -o ${OBJECTDIR}/_ext/408470894/RegsAccessDriver.o ../src/hal/src/RegsAccessDriver.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/RegsAccessDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/hal_wdt.o: ../src/hal/src/hal_wdt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/hal_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/hal_wdt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/hal_wdt.o.d" -o ${OBJECTDIR}/_ext/408470894/hal_wdt.o ../src/hal/src/hal_wdt.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/hal_wdt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/PortDriver.o: ../src/hal/src/PortDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/PortDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/PortDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/PortDriver.o.d" -o ${OBJECTDIR}/_ext/408470894/PortDriver.o ../src/hal/src/PortDriver.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/PortDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1822170596/Sercom2MasterI2C.o: ../src/hal/plib_auo/src/Sercom2MasterI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1822170596" 
	@${RM} ${OBJECTDIR}/_ext/1822170596/Sercom2MasterI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1822170596/Sercom2MasterI2C.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1822170596/Sercom2MasterI2C.o.d" -o ${OBJECTDIR}/_ext/1822170596/Sercom2MasterI2C.o ../src/hal/plib_auo/src/Sercom2MasterI2C.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1822170596/Sercom2MasterI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1822170596/ll_eic.o: ../src/hal/plib_auo/src/ll_eic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1822170596" 
	@${RM} ${OBJECTDIR}/_ext/1822170596/ll_eic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1822170596/ll_eic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1822170596/ll_eic.o.d" -o ${OBJECTDIR}/_ext/1822170596/ll_eic.o ../src/hal/plib_auo/src/ll_eic.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1822170596/ll_eic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1822170596/ll_pm.o: ../src/hal/plib_auo/src/ll_pm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1822170596" 
	@${RM} ${OBJECTDIR}/_ext/1822170596/ll_pm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1822170596/ll_pm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1822170596/ll_pm.o.d" -o ${OBJECTDIR}/_ext/1822170596/ll_pm.o ../src/hal/plib_auo/src/ll_pm.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1822170596/ll_pm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/EicDriver.o: ../src/hal/src/EicDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/EicDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/EicDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/EicDriver.o.d" -o ${OBJECTDIR}/_ext/408470894/EicDriver.o ../src/hal/src/EicDriver.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/EicDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/I2CMDriver.o: ../src/hal/src/I2CMDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/I2CMDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/I2CMDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/I2CMDriver.o.d" -o ${OBJECTDIR}/_ext/408470894/I2CMDriver.o ../src/hal/src/I2CMDriver.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/I2CMDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/PMDriver.o: ../src/hal/src/PMDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/PMDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/PMDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/PMDriver.o.d" -o ${OBJECTDIR}/_ext/408470894/PMDriver.o ../src/hal/src/PMDriver.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/PMDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/PwmDriver.o: ../src/hal/src/PwmDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/PwmDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/PwmDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/PwmDriver.o.d" -o ${OBJECTDIR}/_ext/408470894/PwmDriver.o ../src/hal/src/PwmDriver.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/PwmDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1075956228/ClockApp.o: ../src/app/src/ClockApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/ClockApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/ClockApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/ClockApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/ClockApp.o ../src/app/src/ClockApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/ClockApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/CrcApp.o: ../src/app/src/CrcApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/CrcApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/CrcApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/CrcApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/CrcApp.o ../src/app/src/CrcApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/CrcApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/FlashRwApp.o: ../src/app/src/FlashRwApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/FlashRwApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/FlashRwApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/FlashRwApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/FlashRwApp.o ../src/app/src/FlashRwApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/FlashRwApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/FunApp.o: ../src/app/src/FunApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/FunApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/FunApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/FunApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/FunApp.o ../src/app/src/FunApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/FunApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/I2c0SlaveApp.o: ../src/app/src/I2c0SlaveApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/I2c0SlaveApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/I2c0SlaveApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/I2c0SlaveApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/I2c0SlaveApp.o ../src/app/src/I2c0SlaveApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/I2c0SlaveApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/MainApp.o: ../src/app/src/MainApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/MainApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/MainApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/MainApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/MainApp.o ../src/app/src/MainApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/MainApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/PinIOApp.o: ../src/app/src/PinIOApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/PinIOApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/PinIOApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/PinIOApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/PinIOApp.o ../src/app/src/PinIOApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/PinIOApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/SysTickApp.o: ../src/app/src/SysTickApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/SysTickApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/SysTickApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/SysTickApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/SysTickApp.o ../src/app/src/SysTickApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/SysTickApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/Uart1App.o: ../src/app/src/Uart1App.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/Uart1App.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/Uart1App.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/Uart1App.o.d" -o ${OBJECTDIR}/_ext/1075956228/Uart1App.o ../src/app/src/Uart1App.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/Uart1App.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/WatchDogApp.o: ../src/app/src/WatchDogApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/WatchDogApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/WatchDogApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/WatchDogApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/WatchDogApp.o ../src/app/src/WatchDogApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/WatchDogApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/InitApp.o: ../src/app/src/InitApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/InitApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/InitApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/InitApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/InitApp.o ../src/app/src/InitApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/InitApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/AdcApp.o: ../src/app/src/AdcApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/AdcApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/AdcApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/AdcApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/AdcApp.o ../src/app/src/AdcApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/AdcApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/I2cMasterApp.o: ../src/app/src/I2cMasterApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/I2cMasterApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/I2cMasterApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/I2cMasterApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/I2cMasterApp.o ../src/app/src/I2cMasterApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/I2cMasterApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1075956228/WakeCtrlApp.o: ../src/app/src/WakeCtrlApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1075956228" 
	@${RM} ${OBJECTDIR}/_ext/1075956228/WakeCtrlApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1075956228/WakeCtrlApp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1075956228/WakeCtrlApp.o.d" -o ${OBJECTDIR}/_ext/1075956228/WakeCtrlApp.o ../src/app/src/WakeCtrlApp.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1075956228/WakeCtrlApp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/609943780/plib_clock.o: ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/clock/plib_clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/609943780" 
	@${RM} ${OBJECTDIR}/_ext/609943780/plib_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/609943780/plib_clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/609943780/plib_clock.o.d" -o ${OBJECTDIR}/_ext/609943780/plib_clock.o ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/clock/plib_clock.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/609943780/plib_clock.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/607794294/plib_evsys.o: ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/evsys/plib_evsys.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/607794294" 
	@${RM} ${OBJECTDIR}/_ext/607794294/plib_evsys.o.d 
	@${RM} ${OBJECTDIR}/_ext/607794294/plib_evsys.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/607794294/plib_evsys.o.d" -o ${OBJECTDIR}/_ext/607794294/plib_evsys.o ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/evsys/plib_evsys.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/607794294/plib_evsys.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/257756180/plib_nvic.o: ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/nvic/plib_nvic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/257756180" 
	@${RM} ${OBJECTDIR}/_ext/257756180/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/257756180/plib_nvic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/257756180/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/257756180/plib_nvic.o ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/nvic/plib_nvic.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/257756180/plib_nvic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/583357666/plib_nvmctrl.o: ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/nvmctrl/plib_nvmctrl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/583357666" 
	@${RM} ${OBJECTDIR}/_ext/583357666/plib_nvmctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/583357666/plib_nvmctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/583357666/plib_nvmctrl.o.d" -o ${OBJECTDIR}/_ext/583357666/plib_nvmctrl.o ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/nvmctrl/plib_nvmctrl.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/583357666/plib_nvmctrl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/257809331/plib_port.o: ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/port/plib_port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/257809331" 
	@${RM} ${OBJECTDIR}/_ext/257809331/plib_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/257809331/plib_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/257809331/plib_port.o.d" -o ${OBJECTDIR}/_ext/257809331/plib_port.o ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/port/plib_port.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/257809331/plib_port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/297074231/plib_sercom1_usart.o: ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/sercom/usart/plib_sercom1_usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/297074231" 
	@${RM} ${OBJECTDIR}/_ext/297074231/plib_sercom1_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/297074231/plib_sercom1_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/297074231/plib_sercom1_usart.o.d" -o ${OBJECTDIR}/_ext/297074231/plib_sercom1_usart.o ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/sercom/usart/plib_sercom1_usart.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/297074231/plib_sercom1_usart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/348882568/plib_systick.o: ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/systick/plib_systick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/348882568" 
	@${RM} ${OBJECTDIR}/_ext/348882568/plib_systick.o.d 
	@${RM} ${OBJECTDIR}/_ext/348882568/plib_systick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/348882568/plib_systick.o.d" -o ${OBJECTDIR}/_ext/348882568/plib_systick.o ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/systick/plib_systick.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/348882568/plib_systick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1377153438/plib_tcc2.o: ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/tcc/plib_tcc2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1377153438" 
	@${RM} ${OBJECTDIR}/_ext/1377153438/plib_tcc2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1377153438/plib_tcc2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1377153438/plib_tcc2.o.d" -o ${OBJECTDIR}/_ext/1377153438/plib_tcc2.o ../src/config/SGM_C21N17A_BL_CONFIG/peripheral/tcc/plib_tcc2.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1377153438/plib_tcc2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1856207816/xc32_monitor.o: ../src/config/SGM_C21N17A_BL_CONFIG/stdio/xc32_monitor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1856207816" 
	@${RM} ${OBJECTDIR}/_ext/1856207816/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1856207816/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1856207816/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/1856207816/xc32_monitor.o ../src/config/SGM_C21N17A_BL_CONFIG/stdio/xc32_monitor.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1856207816/xc32_monitor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2139064974/initialization.o: ../src/config/SGM_C21N17A_BL_CONFIG/initialization.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139064974" 
	@${RM} ${OBJECTDIR}/_ext/2139064974/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/2139064974/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2139064974/initialization.o.d" -o ${OBJECTDIR}/_ext/2139064974/initialization.o ../src/config/SGM_C21N17A_BL_CONFIG/initialization.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2139064974/initialization.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2139064974/interrupts.o: ../src/config/SGM_C21N17A_BL_CONFIG/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139064974" 
	@${RM} ${OBJECTDIR}/_ext/2139064974/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/2139064974/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2139064974/interrupts.o.d" -o ${OBJECTDIR}/_ext/2139064974/interrupts.o ../src/config/SGM_C21N17A_BL_CONFIG/interrupts.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2139064974/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2139064974/exceptions.o: ../src/config/SGM_C21N17A_BL_CONFIG/exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139064974" 
	@${RM} ${OBJECTDIR}/_ext/2139064974/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/2139064974/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2139064974/exceptions.o.d" -o ${OBJECTDIR}/_ext/2139064974/exceptions.o ../src/config/SGM_C21N17A_BL_CONFIG/exceptions.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2139064974/exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2139064974/startup_xc32.o: ../src/config/SGM_C21N17A_BL_CONFIG/startup_xc32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139064974" 
	@${RM} ${OBJECTDIR}/_ext/2139064974/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/2139064974/startup_xc32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2139064974/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/2139064974/startup_xc32.o ../src/config/SGM_C21N17A_BL_CONFIG/startup_xc32.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2139064974/startup_xc32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2139064974/libc_syscalls.o: ../src/config/SGM_C21N17A_BL_CONFIG/libc_syscalls.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139064974" 
	@${RM} ${OBJECTDIR}/_ext/2139064974/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/2139064974/libc_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2139064974/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/2139064974/libc_syscalls.o ../src/config/SGM_C21N17A_BL_CONFIG/libc_syscalls.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2139064974/libc_syscalls.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1822170596/adcon.o: ../src/hal/plib_auo/src/adcon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1822170596" 
	@${RM} ${OBJECTDIR}/_ext/1822170596/adcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1822170596/adcon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1822170596/adcon.o.d" -o ${OBJECTDIR}/_ext/1822170596/adcon.o ../src/hal/plib_auo/src/adcon.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1822170596/adcon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1822170596/Clock.o: ../src/hal/plib_auo/src/Clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1822170596" 
	@${RM} ${OBJECTDIR}/_ext/1822170596/Clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1822170596/Clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1822170596/Clock.o.d" -o ${OBJECTDIR}/_ext/1822170596/Clock.o ../src/hal/plib_auo/src/Clock.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1822170596/Clock.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1822170596/I2CCommon.o: ../src/hal/plib_auo/src/I2CCommon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1822170596" 
	@${RM} ${OBJECTDIR}/_ext/1822170596/I2CCommon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1822170596/I2CCommon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1822170596/I2CCommon.o.d" -o ${OBJECTDIR}/_ext/1822170596/I2CCommon.o ../src/hal/plib_auo/src/I2CCommon.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1822170596/I2CCommon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1822170596/I2CSlave.o: ../src/hal/plib_auo/src/I2CSlave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1822170596" 
	@${RM} ${OBJECTDIR}/_ext/1822170596/I2CSlave.o.d 
	@${RM} ${OBJECTDIR}/_ext/1822170596/I2CSlave.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1822170596/I2CSlave.o.d" -o ${OBJECTDIR}/_ext/1822170596/I2CSlave.o ../src/hal/plib_auo/src/I2CSlave.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1822170596/I2CSlave.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1822170596/NvmCtrl.o: ../src/hal/plib_auo/src/NvmCtrl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1822170596" 
	@${RM} ${OBJECTDIR}/_ext/1822170596/NvmCtrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1822170596/NvmCtrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1822170596/NvmCtrl.o.d" -o ${OBJECTDIR}/_ext/1822170596/NvmCtrl.o ../src/hal/plib_auo/src/NvmCtrl.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1822170596/NvmCtrl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1822170596/ll_wdt.o: ../src/hal/plib_auo/src/ll_wdt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1822170596" 
	@${RM} ${OBJECTDIR}/_ext/1822170596/ll_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1822170596/ll_wdt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1822170596/ll_wdt.o.d" -o ${OBJECTDIR}/_ext/1822170596/ll_wdt.o ../src/hal/plib_auo/src/ll_wdt.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1822170596/ll_wdt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1822170596/ll_port.o: ../src/hal/plib_auo/src/ll_port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1822170596" 
	@${RM} ${OBJECTDIR}/_ext/1822170596/ll_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1822170596/ll_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1822170596/ll_port.o.d" -o ${OBJECTDIR}/_ext/1822170596/ll_port.o ../src/hal/plib_auo/src/ll_port.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1822170596/ll_port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/ADCDriver.o: ../src/hal/src/ADCDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/ADCDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/ADCDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/ADCDriver.o.d" -o ${OBJECTDIR}/_ext/408470894/ADCDriver.o ../src/hal/src/ADCDriver.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/ADCDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/ClockDriver.o: ../src/hal/src/ClockDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/ClockDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/ClockDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/ClockDriver.o.d" -o ${OBJECTDIR}/_ext/408470894/ClockDriver.o ../src/hal/src/ClockDriver.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/ClockDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/FmcDriver.o: ../src/hal/src/FmcDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/FmcDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/FmcDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/FmcDriver.o.d" -o ${OBJECTDIR}/_ext/408470894/FmcDriver.o ../src/hal/src/FmcDriver.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/FmcDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/I2CSDriver.o: ../src/hal/src/I2CSDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/I2CSDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/I2CSDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/I2CSDriver.o.d" -o ${OBJECTDIR}/_ext/408470894/I2CSDriver.o ../src/hal/src/I2CSDriver.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/I2CSDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/RegsAccessDriver.o: ../src/hal/src/RegsAccessDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/RegsAccessDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/RegsAccessDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/RegsAccessDriver.o.d" -o ${OBJECTDIR}/_ext/408470894/RegsAccessDriver.o ../src/hal/src/RegsAccessDriver.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/RegsAccessDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/hal_wdt.o: ../src/hal/src/hal_wdt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/hal_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/hal_wdt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/hal_wdt.o.d" -o ${OBJECTDIR}/_ext/408470894/hal_wdt.o ../src/hal/src/hal_wdt.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/hal_wdt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/PortDriver.o: ../src/hal/src/PortDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/PortDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/PortDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/PortDriver.o.d" -o ${OBJECTDIR}/_ext/408470894/PortDriver.o ../src/hal/src/PortDriver.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/PortDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1822170596/Sercom2MasterI2C.o: ../src/hal/plib_auo/src/Sercom2MasterI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1822170596" 
	@${RM} ${OBJECTDIR}/_ext/1822170596/Sercom2MasterI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1822170596/Sercom2MasterI2C.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1822170596/Sercom2MasterI2C.o.d" -o ${OBJECTDIR}/_ext/1822170596/Sercom2MasterI2C.o ../src/hal/plib_auo/src/Sercom2MasterI2C.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1822170596/Sercom2MasterI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1822170596/ll_eic.o: ../src/hal/plib_auo/src/ll_eic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1822170596" 
	@${RM} ${OBJECTDIR}/_ext/1822170596/ll_eic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1822170596/ll_eic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1822170596/ll_eic.o.d" -o ${OBJECTDIR}/_ext/1822170596/ll_eic.o ../src/hal/plib_auo/src/ll_eic.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1822170596/ll_eic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1822170596/ll_pm.o: ../src/hal/plib_auo/src/ll_pm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1822170596" 
	@${RM} ${OBJECTDIR}/_ext/1822170596/ll_pm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1822170596/ll_pm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1822170596/ll_pm.o.d" -o ${OBJECTDIR}/_ext/1822170596/ll_pm.o ../src/hal/plib_auo/src/ll_pm.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1822170596/ll_pm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/EicDriver.o: ../src/hal/src/EicDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/EicDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/EicDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/EicDriver.o.d" -o ${OBJECTDIR}/_ext/408470894/EicDriver.o ../src/hal/src/EicDriver.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/EicDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/I2CMDriver.o: ../src/hal/src/I2CMDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/I2CMDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/I2CMDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/I2CMDriver.o.d" -o ${OBJECTDIR}/_ext/408470894/I2CMDriver.o ../src/hal/src/I2CMDriver.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/I2CMDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/PMDriver.o: ../src/hal/src/PMDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/PMDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/PMDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/PMDriver.o.d" -o ${OBJECTDIR}/_ext/408470894/PMDriver.o ../src/hal/src/PMDriver.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/PMDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/408470894/PwmDriver.o: ../src/hal/src/PwmDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/408470894" 
	@${RM} ${OBJECTDIR}/_ext/408470894/PwmDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/408470894/PwmDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/408470894/PwmDriver.o.d" -o ${OBJECTDIR}/_ext/408470894/PwmDriver.o ../src/hal/src/PwmDriver.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/408470894/PwmDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/SGM_C21N17A_BL_CONFIG" -I"../src/packs/ATSAMC21N17A_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src/hal/inc" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21n" ${PACK_COMMON_OPTIONS} 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/SGM_C21N17A_BL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../src/config/SGM_C21N17A_BL_CONFIG/ATSAMC21N17A.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g  -D__MPLAB_DEBUGGER_ICD4=1 -mprocessor=$(MP_PROCESSOR_OPTION) -mno-device-startup-code -o dist/${CND_CONF}/${IMAGE_TYPE}/SGM_C21N17A_BL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_ICD4=1,--defsym=_min_heap_size=512,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}/samc21n"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/SGM_C21N17A_BL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../src/config/SGM_C21N17A_BL_CONFIG/ATSAMC21N17A.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mno-device-startup-code -o dist/${CND_CONF}/${IMAGE_TYPE}/SGM_C21N17A_BL.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_SGM_C21N17A_BL_CONFIG=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}/samc21n"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/SGM_C21N17A_BL.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/SGM_C21N17A_BL_CONFIG
	${RM} -r dist/SGM_C21N17A_BL_CONFIG

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
