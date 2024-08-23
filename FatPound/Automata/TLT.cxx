module;

#include <algorithm>

module FatPound.Automata.TLT;

using std::vector, std::string, std::pair;

namespace fatpound::automata
{
    // TLT

    TLT::TLT(const CFG& cfg)
        :
        m_cfgrammar_(cfg.GetGrammar()),
        m_recursers_(m_cfgrammar_.size(), 0)
    {
        if (m_cfgrammar_.size() < 1)
        {
            throw std::runtime_error("There is no input!");
        }

        m_tree_ = new Node_(m_cfgrammar_[0].first);

        for (const auto& leaf_str : m_cfgrammar_[0].second)
        {
            m_tree_->leaves.push_back(new Node_(leaf_str));
        }

        CreateTree_(m_tree_);
    }
    TLT::TLT(const string& inputFilename)
        :
        TLT(CFG{ inputFilename })
    {

    }
    TLT::~TLT() noexcept
    {
        Clear_();
    }

    auto TLT::GetWords() const noexcept -> vector<string>
    {
        return m_results_;
    }

    void TLT::PrintWords() const noexcept
    {
        vector<string> finals;
        vector<string> repeaters;

        for (const auto& str : m_results_)
        {
            if (std::ranges::find(finals, str) == finals.cend())
            {
                finals.push_back(str);
            }
            else if (std::ranges::find(repeaters, str) == repeaters.cend())
            {
                repeaters.push_back(str);
            }
        }

        if (finals.size() > 0u)
        {
            for (const auto& str : finals)
            {
                std::cout << str << '\n';
            }
        }

        if (repeaters.size() > 0u)
        {
            std::cout << "\nRepeaters :\n\n";

            for (const auto& str : repeaters)
            {
                std::cout << str << '\n';
            }
        }

        std::cout << '\n';
    }

    bool TLT::IsTerminal_(const std::string& word) noexcept
    {
        return std::ranges::all_of(word, [](const auto& ch) noexcept -> bool { return std::islower(ch) not_eq 0; });
    }

    void TLT::CreateTree_(Node_* node)
    {
        m_results_.reserve(node->leaves.size());

        for (auto& leaf : node->leaves)
        {
            if (IsTerminal_(leaf->item))
            {
                m_results_.push_back(leaf->item);

                continue;
            }

            CreateInnerTree_(leaf);
        }
    }
    void TLT::CreateInnerTree_(Node_* node)
    {
        for (std::size_t i = 0u; i < node->item.size(); ++i)
        {
            const auto& ch = node->item[i];

            if (not std::isupper(ch))
            {
                continue;
            }

            const auto& cfg_it = std::ranges::find_if(m_cfgrammar_, [&](const auto& pair) { return pair.first[0] == ch; });

            string leftstr(node->item.cbegin(), node->item.cbegin() + i);
            string rightstr(node->item.cbegin() + i + 1, node->item.cend());

            const std::size_t index = cfg_it - m_cfgrammar_.cbegin();

            node->leaves.reserve(node->leaves.size() + cfg_it->second.size());

            for (const auto& cfgstr : cfg_it->second)
            {
                // string str = cfgstr;

                bool recursed = false;

                if (cfgstr.contains(ch))
                {
                    if (m_recursers_[index] >= s_recurse_limit_)
                    {
                        // const auto [first, last] = rn::remove_if(str, [](const auto& ch) { return std::isupper(ch); });
                        // 
                        // str.erase(first, last);

                        continue;
                    }

                    recursed = true;

                    ++m_recursers_[index];
                }

                const string& newstr = leftstr + cfgstr + rightstr;

                Node_* newnode = new Node_(newstr);

                node->leaves.push_back(newnode);

                if (recursed or (not IsTerminal_(newstr)))
                {
                    CreateInnerTree_(newnode);
                }
                else
                {
                    m_results_.push_back(newstr);
                }

                if (recursed)
                {
                    --m_recursers_[index];
                }
            }
        }
    }

    void TLT::Clear_() noexcept
    {
        if (m_tree_ == nullptr) [[unlikely]]
        {
            return;
        }

        std::deque<Node_*> nodes;

        nodes.push_back(m_tree_);

        while (nodes.size() > 0u)
        {
            Node_* node = nodes.back();

            nodes.pop_back();

            for (auto& leaf : node->leaves)
            {
                nodes.push_back(leaf);
            }

            delete node;
        }
    }


    // TLT::Node_

    TLT::Node_::Node_(const std::string& item)
        :
        item(item)
    {

    }
}