module;

export module FatPound.Automata.CFG;

import std;

using std::vector, std::string, std::pair;

export namespace fatpound::automata
{
    class CFG final
    {
    public:
        // The input file should be in the following format:
        //
        // 1st line: The languages' acceptable letters seperated by spaces (they must be common)
        // 2nd line: The languages are sepeareted by commas and are defined by their names followed by an arrow which is like this "-->"
        // and followed by the symbols of the language(terminals and non - terminals) seperated by a pipe character '|'
        // The seperators can be changed. See static constexprs below
        //
        // Example:
        // a b  c   d e
        // S --> aa | bX | aXX, X --> ab | b
        //
        explicit CFG(const string& inputFilename);
        
        explicit CFG() = delete;
        explicit CFG(const CFG& src) = delete;
        explicit CFG(CFG&& src) = delete;

        CFG& operator = (const CFG& src) = delete;
        CFG& operator = (CFG&& src) = delete;
        ~CFG() noexcept = default;


    protected:


    private:
        void ReadFirstLine_(std::ifstream& inputFile, vector<char>& alphabet);
        void ReadSecondLine_(std::ifstream& inputFile, vector<char>& alphabet);


    private:
        vector<pair<string, vector<string>>> m_grammar_;

        static constexpr auto s_language_seperator_         = ',';
        static constexpr auto s_language_word_seperator_    = '|';
        static constexpr auto s_language_content_seperator_ = "-->";


    /*            */
    //  fatpound* //
    /*            */


    public:
        auto GetGrammar() const noexcept -> decltype(m_grammar_);


    protected:


    private:
    };
}

module : private;