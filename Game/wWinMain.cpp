/*******************************************************************************/
/*                                                                             */
/*                 :::::::                                                     */
/*               :+:    :+:            ::                                      */
/*              +:+            :+     +#                                       */
/*             +#+            +#pL+++##+##++:          :::::::        :::      */
/*            +#+         ++#+##+++ uﬂ#+             :+:    :+:     :+:        */
/*           #+#     #+#     #+      ##                   +:+     +:++         */
/*   wWinMain.########      ##                          +#+      +#+  +:+      */
/*                                                    +#+      +#+#    #+#+    */
/*                                                  #+#         #+#   #+#      */
/*   By: fatpound                                 ########:#      ##.tr        */
/*                                                                             */
/*   Created: --/--/---- ??:??:??                                              */
/*   Updated: 21/01/2025 01:23:26                                              */
/*                                                                             */
/*******************************************************************************/

//           //
// fatpound* //
//           //

#include <FatNamespaces.hpp>
#include <FatWin32.hpp>

import FatPound;
import StarRealm;

import std;

int APIENTRY wWinMain(
    [[maybe_unused]] _In_     HINSTANCE hInst,
    [[maybe_unused]] _In_opt_ HINSTANCE hPrevInst,
    [[maybe_unused]] _In_     LPWSTR    lpCmdLine,
    [[maybe_unused]] _In_     int       nShowCmd)
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
            std::erase_if(games, [](auto& pGame) noexcept -> bool { return pGame->IsOver(); });
            
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        return 0;
    }
    catch (const std::exception& ex)
    {
        ::MessageBox(nullptr, FATSPACE_UTIL::ToWString(ex.what()).c_str(), L"Error!", MB_OK | MB_ICONERROR);
    }
    catch (...)
    {
        ::MessageBox(nullptr, L"Non-STD Exception was thrown!", L"Error...", MB_OK | MB_ICONERROR);
    }

    return -1;
}