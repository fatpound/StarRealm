/*            */
//  fatpound* //
/*            */

// StarRealm

#include <FatWin32_.hpp>

import StarRealm;

import std;

int APIENTRY wWinMain(
    [[maybe_unused]] _In_     HINSTANCE hInst,
    [[maybe_unused]] _In_opt_ HINSTANCE hPrevInst,
    [[maybe_unused]] _In_     LPWSTR    lpCmdLine,
    [[maybe_unused]] _In_     int       nShowCmd
    )
{
    try
    {
        return starrealm::Game{}.Go();
    }
    catch (const std::exception& ex)
    {
        const std::string str = ex.what();

        const int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), nullptr, 0);

        std::wstring wstr(static_cast<std::uint64_t>(sizeNeeded), 0);

        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), wstr.data(), sizeNeeded);

        MessageBox(nullptr, wstr.c_str(), L"Error!", MB_OK | MB_ICONERROR);
    }
    catch (...)
    {
        MessageBox(nullptr, L"Non-STD Exception was thrown!", L"Error...", MB_OK | MB_ICONERROR);
    }

    return -1;
}