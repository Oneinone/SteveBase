#include <codecvt>
#include "CValveFileFormat.hpp"

#include "../XorStr/XorStr.h"

using namespace std;
using namespace nlohmann;

void JsonInjectionHelper(json& j, const json& j_Inject) {
    try {
        for (auto it = j_Inject.begin(); it != j_Inject.end(); ++it) {
            if (!j.count(it.key())) {
                j[it.key()] = it.value();
                continue;
            }
            if (it.value().is_object()) {
                JsonInjectionHelper(j[it.key()], it.value());
                continue;
            }
            j[it.key()] = it.value();
        }
    } catch (...) {
    }
}

Valve::ValveFileFormat::KeyValue::KeyValue(const string& key, const string& value) : m_Key(key), m_Value(value) {
}

Valve::ValveFileFormat::KeyValue::KeyValue(std::tuple<string, string>&& data)
    : m_Key(std::get<0>(data)), m_Value(std::get<1>(data)) {
}

const string& Valve::ValveFileFormat::KeyValue::Key() const {
    return m_Key;
}

const string& Valve::ValveFileFormat::KeyValue::Value() const {
    return m_Value;
}

Valve::ValveFileFormat::Node::Node(const string& name) : m_Name(name) {
}

void Valve::ValveFileFormat::Node::AddChild(Node&& child) {
    m_cChilds.push_back(std::move(child));
}

void Valve::ValveFileFormat::Node::AddProperty(KeyValue&& prop) {
    m_cProperties.push_back(std::move(prop));
}

void Valve::ValveFileFormat::Node::AddProperty(std::tuple<string, string>&& data) {
    m_cProperties.emplace_back(std::move(data));
}

const vector<Valve::ValveFileFormat::Node>& Valve::ValveFileFormat::Node::GetChildren() const {
    return m_cChilds;
}

const vector<Valve::ValveFileFormat::KeyValue>& Valve::ValveFileFormat::Node::GetProperties() const {
    return m_cProperties;
}

const string& Valve::ValveFileFormat::Node::Name() const {
    return m_Name;
}

json Valve::ValveFileFormat::Node::ToJson() const {
    json j;
    for (auto& child : m_cChilds) {
        if (j.count(child.Name())) {
            JsonInjectionHelper(j[child.Name()], child.ToJson());
        } else {
            j[child.Name()] = child.ToJson();
        }
    }
    for (auto& prop : m_cProperties)
        j[prop.Key()] = prop.Value();
    return j;
}

unique_ptr<Valve::ValveFileFormat::Node> Valve::ValveFileFormat::Parser::Parse(const string& path, EFileEncoding enc) {
    if (!LoadFile(path, enc))
        return nullptr;

    auto node = ParseNode(GetLine());
    if (node.GetChildren().size() == 0 && node.GetProperties().size() == 0)
        return nullptr;

    m_ss.clear();
    return make_unique<Node>(std::move(node));
}

unique_ptr<Valve::ValveFileFormat::Node> Valve::ValveFileFormat::Parser::ParseString(const string &str, EFileEncoding enc) {
    m_ss << str;
    auto node = ParseNode(GetLine());
    if (node.GetChildren().size() == 0 && node.GetProperties().size() == 0)
        return nullptr;

    m_ss.clear();
    return make_unique<Node>(std::move(node));
}

string Valve::ValveFileFormat::Parser::GetLine() {
    if (!m_ss.good())
        return "";

    string line;
    getline(m_ss, line);
    if (line[line.length()] == '\n')
        line.pop_back();
    return line;
}

string Valve::ValveFileFormat::Parser::wstring_to_string(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;
    return converter.to_bytes(wstr);
}

vector<size_t> Valve::ValveFileFormat::Parser::GetQuotePositions(const string& line) {
    vector<size_t> cPositions;
    auto           bEscape = false;
    for (size_t i = 0; i < line.size(); ++i) {
        auto c = line[i];
        if (c == '\\') {
            bEscape = bEscape ? false : true;
            continue;
        }
        if (c == '"' && !bEscape)
            cPositions.push_back(i);
        bEscape = false;
    }
    return cPositions;
}

bool Valve::ValveFileFormat::Parser::IsNode(const string& line) {
    return GetQuotePositions(line).size() == 2;
}

bool Valve::ValveFileFormat::Parser::IsProperty(const string& line) {
    return GetQuotePositions(line).size() == 4;
}

string Valve::ValveFileFormat::Parser::ExtractNodeName(const string& line) {
    auto cPos = GetQuotePositions(line);
    if (cPos.size() != 2)
        return line;
    return line.substr(cPos[0] + 1, cPos[1] - cPos[0] - 1);
}

std::tuple<string, string> Valve::ValveFileFormat::Parser::ExtractKeyValue(const string& line) {
    auto cPos = GetQuotePositions(line);
    if (cPos.size() != 4)
        return std::make_tuple(text("Error"), line);
    auto key = line.substr(cPos[0] + 1, cPos[1] - cPos[0] - 1);
    auto val = line.substr(cPos[2] + 1, cPos[3] - cPos[2] - 1);
    return make_tuple(key, val);
}

Valve::ValveFileFormat::Node Valve::ValveFileFormat::Parser::ParseNode(const string& line) {
    if (!m_ss.good())
        return { text("Error") };

    Node node(ExtractNodeName(line));
    GetLine();
    while (m_ss.good()) {
        auto strLine = GetLine();
        if (IsNode(strLine))
            node.AddChild(ParseNode(strLine));
        else if (IsProperty(strLine))
            node.AddProperty(ExtractKeyValue(strLine));
        else if (strLine.find('}') != string::npos)
            return node;
    }

    return node;
}

bool Valve::ValveFileFormat::Parser::LoadFile(const string& path, EFileEncoding enc) {
    std::wifstream FileStream(path);
    if (!FileStream || !FileStream.good()) {
        // tfm::printf(XorStr("[!] Could not open file '%s'"), path);
        return false;
    }

    switch (enc) {
        case ENC_UTF8:
        FileStream.imbue(std::locale(FileStream.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
        break;
        case ENC_UTF16_LE:
        FileStream.imbue(
            std::locale(FileStream.getloc(), new std::codecvt_utf16<wchar_t, 0x10FFFF, std::little_endian>));
        break;
        case ENC_UTF16_BE:
        FileStream.imbue(std::locale(FileStream.getloc(), new std::codecvt_utf16<wchar_t, 0x10FFFF>));
        break;
        default:
        case ENC_UTF16_CONSUME:
        FileStream.imbue(
            std::locale(FileStream.getloc(), new std::codecvt_utf16<wchar_t, 0x10FFFF, std::consume_header>));
        break;
    }

    std::wstring wstrBuffer((std::istreambuf_iterator<wchar_t>(FileStream)), std::istreambuf_iterator<wchar_t>());
    m_ss << wstring_to_string(wstrBuffer);
    return true;
}
