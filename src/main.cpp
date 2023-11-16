#include <iostream>
#include <cxxopts.hpp>
#include <fmt/core.h>
#include <nbsp/NBioAPI.h>

int main(int argc, char* argv[]) {
    cxxopts::Options options("nbspcli", "A CLI for nitgen biometric devices");
    NBioAPI_HANDLE nbioApiHandle;
    NBioAPI_RETURN nbioApiReturn;
    NBioAPI_DEVICE_ID nbioApiDeviceId = NBioAPI_DEVICE_ID_AUTO;

    options.add_options()
        ("i,init", "Initialize SDK");

    auto result = options.parse(argc, argv);

    if (result.count("init")) {
        nbioApiReturn = NBioAPI_Init(&nbioApiHandle);
        if (nbioApiReturn != NBioAPIERROR_NONE) {
            fmt::print("Failed to initialize SDK, Error code: {}\n", nbioApiReturn);
            return 1;
        }
        nbioApiReturn = NBioAPI_OpenDevice(nbioApiHandle, nbioApiDeviceId);
        if (nbioApiReturn != NBioAPIERROR_NONE) {
            fmt::print("Failed to open device, Error code: {}\n", nbioApiReturn);
            return 1;
        }
        fmt::print("Device opened\n");
    }

    return 0;
}