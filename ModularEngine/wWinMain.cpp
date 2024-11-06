/*            */
//  fatpound* //
/*            */

// StarRealm

#include <FatWin32_.hpp>

import StarRealm;

import std;

using std::literals::chrono_literals::operator ""ms;

int APIENTRY wWinMain(
        [[maybe_unused]] _In_     HINSTANCE hInst,
        [[maybe_unused]] _In_opt_ HINSTANCE hPrevInst,
        [[maybe_unused]] _In_     LPWSTR    lpCmdLine,
        [[maybe_unused]] _In_     int       nShowCmd
    )
{
    try
    {
#if IN_DEBUG
        constexpr auto gameCount = 4;
#else
        constexpr auto gameCount = 1;
#endif // IN_DEBUG

        std::vector<std::unique_ptr<starrealm::Game>> games;

        games.reserve(gameCount);

        for (auto i = 0; i < gameCount; ++i)
        {
            games.push_back(std::make_unique<starrealm::Game>());
        }

        while (not games.empty())
        {
            std::erase_if(games, [](auto& pGame) noexcept -> bool { return pGame->IsFinished(); });

            std::this_thread::sleep_for(100ms);
        }

        return 0;
    }
    catch (const std::exception& ex)
    {
        const std::string str = ex.what();

        const auto sizeNeeded = ::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), nullptr, 0);

        std::wstring wstr(static_cast<std::uint64_t>(sizeNeeded), 0);

        ::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), wstr.data(), sizeNeeded);

        ::MessageBox(nullptr, wstr.c_str(), L"Error!", MB_OK | MB_ICONERROR);
    }
    catch (...)
    {
        ::MessageBox(nullptr, L"Non-STD Exception was thrown!", L"Error...", MB_OK | MB_ICONERROR);
    }

    return -1;
}