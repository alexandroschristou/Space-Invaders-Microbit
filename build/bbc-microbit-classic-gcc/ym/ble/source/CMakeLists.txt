# NOTE: This file is generated by yotta: changes will be overwritten!

cmake_minimum_required(VERSION 2.8.11)

include_directories("/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/source")


set(YOTTA_AUTO_BLE_CPP_FILES
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/source/services/UARTService.cpp"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/source/services/DFUService.cpp"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/source/BLE.cpp"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/source/DiscoveredCharacteristic.cpp"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/source/GapScanningParams.cpp"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/source/services/URIBeaconConfigService.cpp"
)
# force dependency on the config header for cpp files, which CMake otherwise wouldn't track:
set_property(SOURCE ${YOTTA_AUTO_BLE_CPP_FILES} PROPERTY OBJECT_DEPENDS "/home/alexandros/Desktop/microbit-samples/build/bbc-microbit-classic-gcc/yotta_config.h")
set(YOTTA_AUTO_BLE_HEADER_FILES
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/BLE.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/UUID.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/services/UARTService.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/ServiceDiscovery.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/services/DeviceInformationService.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/BLEProtocol.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/GattAttribute.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/GapEvents.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/services/BatteryService.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/Gap.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/GattCallbackParamTypes.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/GattService.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/DiscoveredService.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/SecurityManager.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/services/iBeacon.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/GattServer.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/CallChainOfFunctionPointersWithContext.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/GattServerEvents.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/blecommon.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/DiscoveredCharacteristicDescriptor.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/BLEInstanceBase.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/deprecate.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/SafeBool.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/services/DFUService.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/GapScanningParams.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/CharacteristicDescriptorDiscovery.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/services/EddystoneConfigService.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/DiscoveredCharacteristic.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/services/EddystoneService.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/services/URIBeaconConfigService.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/GattClient.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/GapAdvertisingData.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/services/LinkLossService.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/services/HealthThermometerService.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/FunctionPointerWithContext.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/services/HeartRateService.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/GapAdvertisingParams.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/services/EnvironmentalService.h"
    "/home/alexandros/Desktop/microbit-samples/yotta_modules/ble/ble/GattCharacteristic.h"
)
# force dependency on the config header for header files, which CMake otherwise wouldn't track:
set_property(SOURCE ${YOTTA_AUTO_BLE_HEADER_FILES} PROPERTY OBJECT_DEPENDS "/home/alexandros/Desktop/microbit-samples/build/bbc-microbit-classic-gcc/yotta_config.h")


add_library(ble
    ${YOTTA_AUTO_BLE_CPP_FILES}
    ${YOTTA_AUTO_BLE_HEADER_FILES}
)

yotta_postprocess_target(LIBRARY ble)



target_link_libraries(ble
    ble-nrf51822
    mbed-classic
)

