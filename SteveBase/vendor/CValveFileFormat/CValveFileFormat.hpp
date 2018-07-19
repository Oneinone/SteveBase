#pragma once

#include <string>
#include <memory>
#include <tuple>
#include <vector>
#include <fstream>
#include <sstream>

#include "../nlohmann/json.hpp"

namespace Valve {
    namespace ValveFileFormat {
        using namespace std;

        class KeyValue {
        public:
            KeyValue(const string& key, const string& value);
            KeyValue(tuple<string, string>&& data);
            const string& Key() const;
            const string& Value() const;

        private:
            string m_Key;
            string m_Value;
        };

        class Node {
        public:
            Node(const string& name);
            void AddChild(Node&& child);
            void AddProperty(KeyValue&& prop);
            void AddProperty(tuple<string, string>&& data);
            const vector<Node>&     GetChildren() const;
            const vector<KeyValue>& GetProperties() const;
            const string&           Name() const;
            nlohmann::json                    ToJson() const;

        private:
            string           m_Name;
            vector<Node>     m_cChilds;
            vector<KeyValue> m_cProperties;
        };

        class Parser {
        public:
            enum EFileEncoding {
                ENC_UTF8 = 0,
                ENC_UTF16_LE,
                ENC_UTF16_BE,
                ENC_UTF16_CONSUME,
                ENC_MAX
            };

        public:
            Parser() = default;
            unique_ptr<Node> Parse(const string& path, EFileEncoding enc = ENC_UTF16_CONSUME);
            unique_ptr<Node> ParseString(const string& str, EFileEncoding enc = ENC_UTF16_CONSUME);

        private:
            string GetLine();
            Node ParseNode(const string& line);
            bool LoadFile(const string& path, EFileEncoding enc = ENC_UTF16_CONSUME);

        private:
            static string wstring_to_string(const std::wstring& wstr);
            static vector<size_t> GetQuotePositions(const string& line);
            static bool IsNode(const string& line);
            static bool IsProperty(const string& line);
            static string ExtractNodeName(const string& line);
            static std::tuple<string, string> ExtractKeyValue(const string& line);

        private:
            std::stringstream m_ss;
        };

    } // namespace ValveFileFormat
} // namespace Valve