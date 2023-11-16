// C++ 23
#include <iostream>
#include <cxxopts.hpp>
#include <fmt/core.h>
#include <nbsp/NBioAPI.h>

// worst code possible, but its only for testing

int main(int argc, char* argv[]) {
    cxxopts::Options options("nbspcli", "A CLI for nitgen biometric devices");
    NBioAPI_HANDLE nbioApiHandle;
    NBioAPI_RETURN nbioApiReturn;
    NBioAPI_DEVICE_ID nbioApiDeviceId = NBioAPI_DEVICE_ID_AUTO;
    NBioAPI_FIR_HANDLE nbioApiFirHandle;
    NBioAPI_FIR_TEXTENCODE textFIR;

    options.add_options()
        ("i,init", "Initialize SDK");

    auto result = options.parse(argc, argv);

    if (result.count("init")) {
        nbioApiReturn = NBioAPI_Init(&nbioApiHandle);
        if (nbioApiReturn != NBioAPIERROR_NONE) {
            fmt::println("Failed to initialize SDK, Error code: {}\n", nbioApiReturn);
            return 1;
        }
        nbioApiReturn = NBioAPI_OpenDevice(nbioApiHandle, nbioApiDeviceId);
        if (nbioApiReturn != NBioAPIERROR_NONE) {
            fmt::println("Failed to open device, Error code: {}\n", nbioApiReturn);
            return 1;
        }
        nbioApiReturn = NBioAPI_Capture(nbioApiHandle, NBioAPI_FIR_PURPOSE_VERIFY, &nbioApiFirHandle, 10000, nullptr, nullptr);
        if (nbioApiReturn != NBioAPIERROR_NONE) {
            fmt::println("Failed to capture fingerprint, Error code: {}\n", nbioApiReturn);
            return 1;
        }

        fmt::println("Fingerprint captured successfully\n");
        fmt::println("Fingerprint data at address: {}\n", nbioApiFirHandle);

        nbioApiReturn = NBioAPI_GetTextFIRFromHandle(nbioApiHandle, nbioApiFirHandle, &textFIR, NBioAPI_FALSE);
        if (nbioApiReturn != NBioAPIERROR_NONE) {
            fmt::println("Failed to get fingerprint data, Error code: {}\n", nbioApiReturn);
            return 1;
        }
        fmt::println("Fingerprint hash: {}\n", textFIR.TextFIR);

    }

    return 0;
}