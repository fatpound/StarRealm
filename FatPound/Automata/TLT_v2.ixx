module;

export module FatPound.Automata.TLT_v2;

import FatPound.Automata.CFG;

import std;

using std::vector, std::string, std::pair;

export namespace fatpound::automata
{
    class TLT_v2 final
    {
    public:
        explicit TLT_v2(const CFG& cfgs);
        explicit TLT_v2(const string& inputFilename);

        explicit TLT_v2() = delete;
        explicit TLT_v2(const TLT_v2& src) = delete;
        explicit TLT_v2(TLT_v2&& src) = delete;

        TLT_v2& operator = (const TLT_v2& src) = delete;
        TLT_v2& operator = (TLT_v2&& src) = delete;
        ~TLT_v2() noexcept;


    public:
        auto GetWords() const noexcept -> vector<pair<string, bool>>;

        void PrintWords() const noexcept;


    protected:


    private:
        struct Node_ final
        {
            Node_(const pair<string, vector<string>>& tree);
            Node_(const string& str);

            vector<Node_*> leaves_;

            string item_;
        };


    private:
        auto GenerateResults_(string init_str = "", std::size_t index = 0u, std::size_t recursed = 0u) const -> vector<pair<string, bool>>;

        bool IsTerminal_(const string& str) const;

        void Clear_() noexcept;


    private:
        vector<pair<string, bool>> m_results_;

        vector<Node_*> m_trees_;

        static constexpr auto s_recurse_limit_ = 1u;
    };
}

module : private;