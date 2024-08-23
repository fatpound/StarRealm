module;

export module FatPound.Automata.TLT;

import FatPound.Automata.CFG;

import std;

using std::vector, std::string, std::pair;

export namespace fatpound::automata
{
    class TLT final
    {
    public:
        explicit TLT(const CFG& cfgs);
        explicit TLT(const string& inputFilename);

        explicit TLT() = delete;
        explicit TLT(const TLT& src) = delete;
        explicit TLT(TLT&& src) = delete;

        TLT& operator = (const TLT& src) = delete;
        TLT& operator = (TLT&& src) = delete;
        ~TLT() noexcept;


    public:
        auto GetWords() const noexcept -> vector<string>;

        void PrintWords() const noexcept;


    protected:


    private:
        struct Node_ final
        {
            Node_(const string& item);

            vector<Node_*> leaves;

            string item;
        };


    private:
        static bool IsTerminal_(const string& word) noexcept;


    private:
        void CreateTree_(Node_* node);
        void CreateInnerTree_(Node_* node);

        void Clear_() noexcept;


    private:
        const vector<pair<string, vector<string>>>& m_cfgrammar_;

        vector<string> m_results_;

        vector<std::size_t> m_recursers_;

        Node_* m_tree_ = nullptr;

        static constexpr auto s_recurse_limit_ = 1u;
    };
}

module : private;