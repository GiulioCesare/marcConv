################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ControlField.cpp \
../src/DataField.cpp \
../src/DocOfflineExport.cpp \
../src/Embedded.cpp \
../src/Leader.cpp \
../src/MarcRecord.cpp \
../src/MarcStreamReader.cpp \
../src/MarcStreamWriter.cpp \
../src/ReadMarcExample.cpp \
../src/Subfield.cpp \
../src/marcConv.cpp 

OBJS += \
./src/ControlField.o \
./src/DataField.o \
./src/DocOfflineExport.o \
./src/Embedded.o \
./src/Leader.o \
./src/MarcRecord.o \
./src/MarcStreamReader.o \
./src/MarcStreamWriter.o \
./src/ReadMarcExample.o \
./src/Subfield.o \
./src/marcConv.o 

CPP_DEPS += \
./src/ControlField.d \
./src/DataField.d \
./src/DocOfflineExport.d \
./src/Embedded.d \
./src/Leader.d \
./src/MarcRecord.d \
./src/MarcStreamReader.d \
./src/MarcStreamWriter.d \
./src/ReadMarcExample.d \
./src/Subfield.d \
./src/marcConv.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/argentino/workspace/cdt/marcConv/include" -I"/home/argentino/workspace/cdt/marcConv/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


