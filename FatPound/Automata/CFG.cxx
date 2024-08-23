module;

#include <algorithm>

module FatPound.Automata.CFG;

using std::vector, std::string, std::pair;

namespace fatpound::automata
{
    CFG::CFG(const string& inputFilename)
    {
        std::ifstream inputFile(inputFilename);

        if (not inputFile.is_open())
        {
            throw std::runtime_error("Input file cannot be opened for [InputtingCFG]!");
        }

        vector<char> alphabet;

        ReadFirstLine_(inputFile, alphabet);
        ReadSecondLine_(inputFile, alphabet);
    }

    auto CFG::GetGrammar() const noexcept -> decltype(m_grammar_)
    {
        return m_grammar_;
    }
    
    void CFG::ReadFirstLine_(std::ifstream& inputFile, vector<char>& alphabet)
    {
        // düzelt
        {
            string str;

            std::getline(inputFile, str);

            {
                std::stringstream ss;

                ss << str;

                char ch;

                while (ss >> ch)
                {
                    alphabet.push_back(ch);
                }
            }
        }

        std::ranges::sort(alphabet);

        auto it = std::ranges::unique(alphabet);

        alphabet.erase(it.begin(), it.end());
    }
    void CFG::ReadSecondLine_(std::ifstream& inputFile, vector<char>& alphabet)
    {
        string str;

        while (std::getline(inputFile, str, s_language_seperator_))
        {
            {
                const auto& it = std::ranges::remove_if(str, [](const auto& ch) noexcept -> bool { return std::isspace(ch) not_eq 0; });

                str.erase(it.begin(), it.end());
            }

            const auto& index = str.find(s_language_content_seperator_);

            if (index not_eq string::npos)
            {
                string word(str.cbegin(), str.cbegin() + index);

                str.erase(0, index + std::strlen(s_language_content_seperator_));

                vector<string> leaves;

                std::istringstream iss(str);

                string tempstr;

                while (std::getline(iss, tempstr, s_language_word_seperator_))
                {
                    if (std::ranges::find(leaves, tempstr) == leaves.cend())
                    {
                        for (const auto& ch : tempstr)
                        {
                            if (std::islower(ch) && std::ranges::find(alphabet, ch) == alphabet.cend())
                            {
                                throw std::runtime_error("The letter " + string{ ch } + " is not in the alphabet!");
                            }
                        }

                        leaves.push_back(tempstr);
                    }
                }

                m_grammar_.emplace_back(std::move(word), std::move(leaves));
            }
        }
    }
}