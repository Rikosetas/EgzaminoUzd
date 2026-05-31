#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string mazosiomisRaides(string zodis)
{
    for (char& raide : zodis)
    {
        raide = static_cast<char>(tolower(static_cast<unsigned char>(raide)));
    }

    return zodis;
}

bool arLeistinasUrlSimbolis(char simbolis)
{
    string leistini = ".:/?#[]@!$&'()*+,;=%-_~";
    return isalnum(static_cast<unsigned char>(simbolis)) || leistini.find(simbolis) != string::npos;
}

string nuvalytiUrl(string tekstas)
{
    while (!tekstas.empty() && !arLeistinasUrlSimbolis(tekstas.front()))
    {
        tekstas.erase(tekstas.begin());
    }

    while (!tekstas.empty() && !isalnum(static_cast<unsigned char>(tekstas.back())) && tekstas.back() != '/')
    {
        tekstas.pop_back();
    }

    return tekstas;
}

bool arUrl(string tekstas)
{
    tekstas = mazosiomisRaides(nuvalytiUrl(tekstas));

    if (tekstas.find("http://") == 0 || tekstas.find("https://") == 0 || tekstas.find("www.") == 0)
    {
        return tekstas.find('.') != string::npos;
    }

    if (tekstas.find('@') != string::npos || tekstas.find('.') == string::npos)
    {
        return false;
    }

    size_t paskutinisTaskas = tekstas.rfind('.');
    string galune = tekstas.substr(paskutinisTaskas + 1);
    set<string> galimosGalunes = { "lt", "com", "org", "net", "edu", "gov", "io", "dev", "eu", "info" };

    if (galune.length() < 2 || galune.length() > 6)
    {
        return false;
    }

    for (char simbolis : galune)
    {
        if (!isalpha(static_cast<unsigned char>(simbolis)))
        {
            return false;
        }
    }

    return galimosGalunes.find(galune) != galimosGalunes.end();
}

string gautiZodi(string tekstas)
{
    string zodis;

    for (char simbolis : tekstas)
    {
        if (isalnum(static_cast<unsigned char>(simbolis)))
        {
            zodis += static_cast<char>(tolower(static_cast<unsigned char>(simbolis)));
        }
    }

    return zodis;
}

void nuskaitytiTeksta(const string& failoVardas, map<string, int>& zodziuKiekiai,
    map<string, set<int>>& eilutes, vector<string>& urlAdresai)
{
    ifstream failas(failoVardas);
    string eilute;
    int eilutesNumeris = 0;

    while (getline(failas, eilute))
    {
        eilutesNumeris++;
        stringstream srautas(eilute);
        string dalis;

        while (srautas >> dalis)
        {
            if (arUrl(dalis))
            {
                urlAdresai.push_back(nuvalytiUrl(dalis));
                continue;
            }

            string zodis = gautiZodi(dalis);

            if (!zodis.empty())
            {
                zodziuKiekiai[zodis]++;
                eilutes[zodis].insert(eilutesNumeris);
            }
        }
    }
}

void isvestiZodziuKiekius(const string& failoVardas, const map<string, int>& zodziuKiekiai)
{
    ofstream rezultatai(failoVardas);

    rezultatai << left << setw(20) << "Zodis" << "Kiekis" << endl;
    rezultatai << "------------------------------" << endl;

    for (const auto& pora : zodziuKiekiai)
    {
        if (pora.second > 1)
        {
            rezultatai << left << setw(20) << pora.first << pora.second << endl;
        }
    }
}

void isvestiCrossReference(const string& failoVardas, const map<string, int>& zodziuKiekiai,
    const map<string, set<int>>& eilutes)
{
    ofstream rezultatai(failoVardas);

    rezultatai << left << setw(20) << "Zodis" << "Eilutes" << endl;
    rezultatai << "------------------------------------------------------------" << endl;

    for (const auto& pora : zodziuKiekiai)
    {
        if (pora.second > 1)
        {
            rezultatai << left << setw(20) << pora.first;

            for (int eilute : eilutes.at(pora.first))
            {
                rezultatai << eilute << " ";
            }

            rezultatai << endl;
        }
    }
}

void isvestiUrlAdresus(const string& failoVardas, const vector<string>& urlAdresai)
{
    ofstream rezultatai(failoVardas);

    rezultatai << "Rasti URL adresai:" << endl;
    rezultatai << "-----------------" << endl;

    for (const string& url : urlAdresai)
    {
        rezultatai << url << endl;
    }
}

int main()
{
    const string ivestiesFailas = "tekstas.txt";
    map<string, int> zodziuKiekiai;
    map<string, set<int>> eilutes;
    vector<string> urlAdresai;

    ifstream tikrinimas(ivestiesFailas);

    if (!tikrinimas)
    {
        cout << "Nepavyko atidaryti failo: " << ivestiesFailas << endl;
        return 1;
    }

    tikrinimas.close();

    nuskaitytiTeksta(ivestiesFailas, zodziuKiekiai, eilutes, urlAdresai);
    isvestiZodziuKiekius("zodziu_pasikartojimai.txt", zodziuKiekiai);
    isvestiCrossReference("cross_reference.txt", zodziuKiekiai, eilutes);
    isvestiUrlAdresus("url_adresai.txt", urlAdresai);

    cout << "Programa baige darba." << endl;
    cout << "Rezultatai irasyti i failus:" << endl;
    cout << "zodziu_pasikartojimai.txt" << endl;
    cout << "cross_reference.txt" << endl;
    cout << "url_adresai.txt" << endl;

    return 0;
}
