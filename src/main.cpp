#include <iostream>
#include <cxxopts.hpp>
#include <fmt/core.h>
#include <nbsp/NBioAPI.h>

int main(int argc, char* argv[]) {
    cxxopts::Options options("nbspcli", "A CLI for nitgen biometric devices");
    NBioAPI_HANDLE nbioApiHandle;
    NBioAPI_RETURN nbioApiReturn;
    NBioAPI_DEVICE_ID nbioApiDeviceId;
    
    options.add_options()
        ("i,init", "Initialize SDK")
        ("e,enroll", "Execute enroll function and return a hash")
        ;

    auto result = options.parse(argc, argv);

    if (result.count("init")) {
        nbioApiReturn = NBioAPI_Init(&nbioApiHandle);
        if (nbioApiReturn != NBioAPIERROR_NONE) {
            fmt::print("Failed to initialize SDK, Error code: {}", nbioApiReturn);
            return 1;
        }
        fmt::print("Initialized handle\n");
        return 0;
    }

    if (result.count("enroll")) {
        nbioApiDeviceId = NBioAPI_DEVICE_ID_AUTO;
        nbioApiReturn = NBioAPI_OpenDevice(nbioApiHandle, nbioApiDeviceId);
        if (nbioApiReturn != NBioAPIERROR_NONE) {
            fmt::print("Device failed to open\n");
            return 1;
        }
        fmt::print("Device opened\n");
        return 0;
    }

    return 0;
}
