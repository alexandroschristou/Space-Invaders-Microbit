# NOTE: This file is generated by yotta: changes will be overwritten!

cmake_minimum_required(VERSION 2.8.11)

enable_testing()

# add a dummy target for all autogenerated tests, so we can build them all
# even though they are EXCLUDE_FROMALL'd, if you use custom CMakeLists you can
# add a dependency of this target on your test programs, by adding:
# add_dependencies(all_tests your_test_name)
add_custom_target(all_tests)


# always use the CMAKE_MODULE_PATH-provided .cmake files, even when including
# from system directories:
cmake_policy(SET CMP0017 OLD)

# toolchain file for bbc-microbit-classic-gcc
set(CMAKE_TOOLCHAIN_FILE "/home/alexandros/Desktop/microbit-samples/build/bbc-microbit-classic-gcc/toolchain.cmake")

# provide function for post-processing executables
function (yotta_postprocess_target target_type_ target_name_)
    if(COMMAND yotta_apply_target_rules)
        yotta_apply_target_rules(${target_type_} ${target_name_})
    endif()

    # For backwards compatibility, support YOTTA_POSTPROCESS_COMMAND.
    if(DEFINED YOTTA_POSTPROCESS_COMMAND AND ${target_type_} STREQUAL "EXECUTABLE")
        #message(AUTHOR_WARNING "This target defines a YOTTA_POSTPROCESS_COMMAND for which support has been deprecated. Please define a CMake function yotta_apply_target_rules(build_object_type build_object) instead.")
        string(REPLACE YOTTA_CURRENT_EXE_NAME "${target_name_}" LOCAL_POSTPROCESS_COMMAND "${YOTTA_POSTPROCESS_COMMAND}")
        separate_arguments(LOCAL_POSTPROCESS_COMMAND_SEPARATED UNIX_COMMAND ${LOCAL_POSTPROCESS_COMMAND})
        add_custom_command(
            TARGET ${target_name_}
            POST_BUILD
            COMMAND ${LOCAL_POSTPROCESS_COMMAND_SEPARATED}
        )
    endif()
endfunction()

# set target-defined definitions
set(YOTTA_BUILD_YEAR "2020") # UTC year
set(YOTTA_BUILD_MONTH "1") # UTC month 1-12
set(YOTTA_BUILD_DAY "9") # UTC day 1-31
set(YOTTA_BUILD_HOUR "12") # UTC hour 0-24
set(YOTTA_BUILD_MINUTE "34") # UTC minute 0-59
set(YOTTA_BUILD_SECOND "46") # UTC second 0-61
set(YOTTA_BUILD_UUID "3fbb093f-7770-4862-9a40-8ac056697afc") # unique random UUID for each build
set(YOTTA_BUILD_VCS_ID "c3b02564fd8082f3bf80472e679aa2f9b707c7c2") # git or mercurial hash
set(YOTTA_BUILD_VCS_CLEAN "0") # evaluates true if the version control system was clean, otherwise false
set(YOTTA_BUILD_VCS_DESCRIPTION "v2.1.1") # git describe or mercurial equivalent
set(TARGET BBC_MICROBIT_CLASSIC_GCC)
set(TARGET_LIKE_BBC_MICROBIT_CLASSIC_GCC TRUE)
set(YOTTA_BUILD_INFO_HEADER "/home/alexandros/Desktop/microbit-samples/build/bbc-microbit-classic-gcc/yotta_build_info.h")
set(TARGET_LIKE_BBC_MICROBIT_CLASSIC_GCC TRUE)
set(TARGET_LIKE_NRF51822 TRUE)
set(TARGET_LIKE_NRF TRUE)
set(TARGET_LIKE_NORDIC TRUE)
set(TARGET_LIKE_CORTEX_M0 TRUE)
set(TARGET_LIKE_ARMV6_M TRUE)
set(TARGET_LIKE_MBED_CLASSIC TRUE)
set(TARGET_LIKE_MICROBIT TRUE)
set(TARGET_LIKE_MBED_GCC TRUE)
set(TARGET_LIKE_MBED TRUE)
set(TARGET_LIKE_ARM TRUE)
set(TARGET_LIKE_GCC TRUE)
set(YOTTA_CFG TRUE)
set(YOTTA_CFG_MINAR TRUE)
set(YOTTA_CFG_MINAR_INITIAL_EVENT_POOL_SIZE 50)
set(YOTTA_CFG_MINAR_ADDITIONAL_EVENT_POOLS_SIZE 100)
set(YOTTA_CFG_ARCH TRUE)
set(YOTTA_CFG_ARCH_ARM TRUE)
set(YOTTA_CFG_MBED TRUE)
set(YOTTA_CONFIG_MERGED_JSON_FILE "/home/alexandros/Desktop/microbit-samples/build/bbc-microbit-classic-gcc/yotta_config.json")


project(microbit-samples)

# Definitions provided by the target configuration info:
if(NOT DEFINED YOTTA_FORCE_INCLUDE_FLAG)
    # backwards-compatibility hack for ARMCC only: Do not add new compilers here!
    if("${CMAKE_C_COMPILER_ID}" STREQUAL "ARMCC")
        set(YOTTA_FORCE_INCLUDE_FLAG "--preinclude")
    else()
        set(YOTTA_FORCE_INCLUDE_FLAG "-include")
    endif()
endif()
add_definitions("${YOTTA_FORCE_INCLUDE_FLAG} \"/home/alexandros/Desktop/microbit-samples/build/bbc-microbit-classic-gcc/yotta_config.h\"")

# include root directories of all components we depend on (directly and
# indirectly, including ourself)
include_directories("/home/alexandros/Desktop/microbit-samples")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/microbit")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/microbit-dal")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/mbed-classic")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/ble")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/ble-nrf51822")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk")


# recurse into dependencies that aren't built elsewhere
add_subdirectory(
   "/home/alexandros/Desktop/microbit-samples/build/bbc-microbit-classic-gcc/ym/microbit"
   "${CMAKE_BINARY_DIR}/ym/microbit"
)



# And others (typically CMSIS implementations) need to export non-system header
# files. Please don't use this facility. Please. It's much, much better to fix
# implementations that import these headers to import them using the full path.
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/microbit/inc")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/microbit-dal/inc/core")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/microbit-dal/inc/types")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/microbit-dal/inc/drivers")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/microbit-dal/inc/bluetooth")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/microbit-dal/inc/platform")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/mbed-classic/api")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/mbed-classic/hal")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/mbed-classic/targets/hal")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/mbed-classic/targets/cmsis")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/ble-nrf51822/source/btle")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/ble-nrf51822/source/btle/custom")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/ble-nrf51822/source/common")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/ble/ble_radio_notification")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/ble/ble_services/ble_dfu")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/ble/common")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/ble/device_manager")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/ble/device_manager/config")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/ble/peer_manager")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/device")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/drivers_nrf/ble_flash")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/drivers_nrf/delay")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/drivers_nrf/hal")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/drivers_nrf/pstorage")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/drivers_nrf/pstorage/config")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/libraries/bootloader_dfu")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/libraries/bootloader_dfu/hci_transport")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/libraries/crc16")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/libraries/hci")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/libraries/scheduler")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/libraries/timer")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/libraries/util")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/libraries/fds")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/libraries/fstorage")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/libraries/experimental_section_vars")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/softdevice/common/softdevice_handler")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/softdevice/s130/headers")
include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/nrf51-sdk/source/nordic_sdk/components/toolchain")


# modules with custom CMake build systems may append to the
# YOTTA_GLOBAL_INCLUDE_DIRS property to add compile-time-determined include
# directories:
get_property(GLOBAL_INCLUDE_DIRS GLOBAL PROPERTY YOTTA_GLOBAL_INCLUDE_DIRS)
include_directories(${GLOBAL_INCLUDE_DIRS})

# Provide versions of all the components we depend on, the corresponding
# preprocessor definitions are generated in yotta_config.h
set(YOTTA_MICROBIT_VERSION_STRING "2.1.1")
set(YOTTA_MICROBIT_VERSION_MAJOR 2)
set(YOTTA_MICROBIT_VERSION_MINOR 1)
set(YOTTA_MICROBIT_VERSION_PATCH 1)
set(YOTTA_MICROBIT_SAMPLES_VERSION_STRING "2.1.1")
set(YOTTA_MICROBIT_SAMPLES_VERSION_MAJOR 2)
set(YOTTA_MICROBIT_SAMPLES_VERSION_MINOR 1)
set(YOTTA_MICROBIT_SAMPLES_VERSION_PATCH 1)

# provide the name of the current module so that it's available to custom CMake
# even if custom CMake does weird things with project()
set(YOTTA_MODULE_NAME microbit-samples)

# recurse into subdirectories for this component, using the two-argument
# add_subdirectory because the directories referred to here exist in the source
# tree, not the working directory
add_subdirectory(
    "/home/alexandros/Desktop/microbit-samples/build/bbc-microbit-classic-gcc/source"
    "${CMAKE_BINARY_DIR}/./source"
)

# make YOTTA_MODULE_NAME available as a preprocessor symbol when
# compiling this module:
target_compile_definitions(microbit-samples PRIVATE "-DYOTTA_MODULE_NAME=microbit-samples")

# include .cmake files provided by the target:
