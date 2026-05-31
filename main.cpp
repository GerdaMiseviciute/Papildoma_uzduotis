#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
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
using std::left;
using std::setw;

bool hasDigit(const std::string& s) {
    return std::any_of(s.begin(), s.end(), [](unsigned char ch) { return std::isdigit(ch); });
}

string istrinti_zenklus(string z)
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

    z.clear();
    s.tempSubString(start, end - start).toUTF8String(z);
    return z;    
}
string didinti_pirma_raide(string z)
{
    icu::UnicodeString s = icu::UnicodeString::fromUTF8(z);
    UChar32 first = s.char32At(0);
    if (!s.isEmpty())
    {

        icu::UnicodeString firstStr(first);
        firstStr.toUpper(icu::Locale("lt"));

        s.replace(0, U16_LENGTH(first), firstStr);
    }

    z.clear();
    s.toUTF8String(z);

    return z;
}
int main()
{
    ifstream fd("tekstas.txt");
    ofstream fr("zodziai.txt");
    ofstream fr1("cross_reference_lentele.txt");
    map<string, int>skirtingi_zodziai;
    map<string, set<int>>zodziai_ir_eilutes;
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
            if(!istrinti_zenklus(zodis).empty())
            {
                skirtingi_zodziai[didinti_pirma_raide(istrinti_zenklus(zodis))]++;
                zodziai_ir_eilutes[didinti_pirma_raide(istrinti_zenklus(zodis))].insert(eilutes_sk);
            }
        }
        eilutes_sk++;
    }

    for(auto x: skirtingi_zodziai)
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
    return 0;
}