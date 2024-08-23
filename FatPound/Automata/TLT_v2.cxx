module;

module FatPound.Automata.TLT_v2;

using std::vector, std::string, std::pair;

namespace fatpound::automata
{
    TLT_v2::TLT_v2(const CFG& cfg)
    {
        {
            const auto& cfgrammar = cfg.GetGrammar();

            m_trees_.reserve(cfgrammar.size());

            for (const auto& tree : cfgrammar)
            {
                m_trees_.push_back(new Node_(tree));
            }
        }

        m_results_ = GenerateResults_("", 0u, 0u);
    }
    TLT_v2::TLT_v2(const string& inputFilename)
        :
        TLT_v2(CFG{ inputFilename })
    {

    }
    TLT_v2::~TLT_v2() noexcept
    {
        Clear_();
    }

    auto TLT_v2::GetWords() const noexcept -> vector<pair<string, bool>>
    {
        return m_results_;
    }

    void TLT_v2::PrintWords() const noexcept
    {
        for (const auto& item : m_results_)
        {
            if (item.second == true)
            {
                std::cout << item.first << '\n';
            }
        }
    }

    auto TLT_v2::GenerateResults_(string init_str, std::size_t index, std::size_t recursed) const -> vector<pair<string, bool>>
    {
        vector<pair<string, bool>> strings;

        for (const auto& node : m_trees_[index]->leaves_)
        {
            vector<pair<string, bool>> tempstrings;

            tempstrings.emplace_back(init_str, false);

            for (const auto& ch : node->item_)
            {
                vector<pair<string, bool>> newTempStrings;

                for (const auto& strPair : tempstrings)
                {
                    string& str = newTempStrings.emplace_back(strPair).first;

                    const auto insertedindex = newTempStrings.size() - 1;

                    const auto it = std::find_if(m_trees_.cbegin() + index, m_trees_.cend(), [&](const auto& tree) -> bool { return ch == tree->item_[0]; });

                    if (it == m_trees_.cend())
                    {
                        str += ch;
                    }
                    else
                    {
                        const auto tree_index = static_cast<std::size_t>(it - m_trees_.cbegin());
                        const auto will_recurse = ((tree_index == index) ? 1 : 0);

                        if (recursed < s_recurse_limit_)
                        {
                            // const auto size = tempstrings.size();

                            // bool deleted = false;

                            string tempstr = strPair.first;

                            if (tempstr == "")
                            {
                                continue;
                            }

                            const auto vec = GenerateResults_(tempstr, tree_index, recursed + will_recurse);

                            for (const auto& pair : vec)
                            {
                                newTempStrings.emplace_back(pair);
                            }

                            newTempStrings.erase(newTempStrings.begin() + insertedindex);
                        }
                        else
                        {
                            str += ch;
                        }
                    }
                }

                tempstrings = std::move(newTempStrings);
            }

            for (const auto& strPair : tempstrings)
            {
                strings.emplace_back(strPair.first, IsTerminal_(strPair.first));
            }
        }

        return strings;
    }

    bool TLT_v2::IsTerminal_(const string& str) const
    {
        for (const auto& tree : m_trees_)
        {
            if (std::any_of(str.cbegin(), str.cend(), [&](const auto& ch) -> bool { return ch == (tree->item_[0]); }))
            {
                return false;
            }
        }

        return true;
    }

    void TLT_v2::Clear_() noexcept
    {
        std::deque<Node_*> nodes;

        for (auto& tree : m_trees_)
        {
            if (tree != nullptr)
            {
                nodes.push_back(tree);
            }
            else
            {
                continue;
            }

            while (nodes.size() > 0)
            {
                Node_* node = nodes.back();

                nodes.pop_back();

                for (auto& leaf : node->leaves_)
                {
                    nodes.push_back(leaf);
                }

                delete node;
            }
        }
    }


    // TLT_v2::Node_

    TLT_v2::Node_::Node_(const pair<string, vector<string>>& tree)
        :
        item_(tree.first)
    {
        leaves_.reserve(tree.second.size());

        for (const auto& str : tree.second)
        {
            leaves_.push_back(new Node_(str));
        }
    }
    TLT_v2::Node_::Node_(const string& str)
        :
        item_(str)
    {

    }
}