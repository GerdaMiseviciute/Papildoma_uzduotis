#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <iomanip>
#include <map>
#include <algorithm>
#include <cctype>
#include <unicode/unistr.h>
#include <unicode/brkiter.h>
#include <unicode/locid.h>
#include <unicode/uchar.h>

using std::ofstream;
using std::ifstream;
using std::string;
using std::map;
using std::istringstream;
using std::cout;
using std::endl;
using std::set;
using std::vector;
using std::left;
using std::setw;

bool hasDigit(const string& s) {
    return std::any_of(s.begin(), s.end(), [](unsigned char ch) { return std::isdigit(ch); });
}

string pirmi_keturi_simboliai(const string& s)
{
    if(s.length()>4)
        return s.substr(0, 4);
    return s;
}

string po_paskutinio_tasko(const string& s)
{
    size_t pos=s.rfind('.');
    if(pos!=std::string::npos && pos+1<s.length())
        return s.substr(pos+1);
    return "";
}

string mazosios_raides(const string& s)
{
    string rez=s;
    for(char& c : rez)
    {
        c = tolower(static_cast<unsigned char>(c));
    }
    return rez;
}

string istrinti_zenklus(const string& z)
{
    icu::UnicodeString s = icu::UnicodeString::fromUTF8(z);
    if (s.isEmpty() || hasDigit(z))
        return "";

    int32_t start = 0;
    int32_t end = s.length();

    while(start < end && !u_isalpha(s.char32At(start)))
        start++;
    while(end > start && !u_isalpha(s.char32At(end - 1)))
        end--;

    string out;
    s.tempSubString(start, end - start).toUTF8String(out);
    return out;    
}
string didinti_pirma_raide(const string& z)
{
    icu::UnicodeString s = icu::UnicodeString::fromUTF8(z);
    UChar32 first = s.char32At(0);
    if (!s.isEmpty())
    {

        icu::UnicodeString firstStr(first);
        firstStr.toUpper(icu::Locale("lt"));

        s.replace(0, U16_LENGTH(first), firstStr);
    }

    string out;
    s.toUTF8String(out);

    return out;
}
int main()
{
    ifstream fd("tekstas.txt");
    ifstream fd1("domenai.txt");
    ofstream fr("zodziai.txt");
    ofstream fr1("cross_reference_lentele.txt");
    ofstream ff("url.txt");
    vector<string>domenai;
    string domenas;
    while(fd1>>domenas)
        domenai.push_back(domenas);
    map<string, int>skirtingi_zodziai;
    map<string, set<int>>zodziai_ir_eilutes;
    set<string>urls;
    string eilute;
    int eilutes_sk=1;
    while(getline(fd, eilute))
    {
        if(eilute.back()=='.')
            eilute.pop_back();
        istringstream zodziai(eilute);
        string zodis;
        while(zodziai>>zodis)
        {   
            bool sutapo=false;
            for(int i=0; i<domenai.size(); i++)
            {
                if(mazosios_raides(domenai[i])==po_paskutinio_tasko(zodis))
                {
                    urls.insert(zodis);
                    sutapo=true;
                    break;
                }
            }
            if(sutapo)
                continue;
            else if(pirmi_keturi_simboliai(zodis)=="http")
                urls.insert(zodis);
            else if(!istrinti_zenklus(zodis).empty())
            {
                skirtingi_zodziai[didinti_pirma_raide(istrinti_zenklus(zodis))]++;
                zodziai_ir_eilutes[didinti_pirma_raide(istrinti_zenklus(zodis))].insert(eilutes_sk);
            }
        }
        eilutes_sk++;
    }

    for(auto x : skirtingi_zodziai)
    {
        if(x.second>1)
            fr<<x.first<<" "<<x.second<<endl;
    }

    for(auto x : zodziai_ir_eilutes)
    {
        if(x.second.size()>1)
        {
            fr1<<x.first<<": ";
            bool pirmas = true;
            for(auto y : x.second)
            {
                if(!pirmas)
                    fr1<<", ";
                fr1<<y;
                pirmas=false;
            }
            fr1<<endl;
        }
    }

    for(auto x : urls)
    {
        ff<<x<<endl;
    }
    return 0;
}