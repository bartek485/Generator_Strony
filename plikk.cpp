#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

// Funkcja dziełaca string na częsci
vector<string> podziel(const string &str, char delimiter)
{
    vector<string> czesci;
    string czesc;
    istringstream tokenStream(str);
    while (getline(tokenStream, czesc, delimiter))
    {
        czesci.push_back(czesc);
    }
    return czesci;
}

// Funkcja pobierająca dane z pliku lub klawiatury
vector<string> pobierz_dane(bool z_pliku)
{
    vector<string> wlasciwosci;
    string line;

    if (z_pliku)
    {
        ifstream dane("dane.txt");
        if (!dane.is_open())
        {
            cerr << "Nie można otworzyć pliku dane.txt!" << endl;
            exit(1);
        }
        while (getline(dane, line))
        {
            wlasciwosci.push_back(line);
        }
        dane.close();
    }
    else
    {
        cout << "Wprowadź dane ręcznie:" << endl;
        string wprowadzone;
        cout << "Kolor tła strony (#rrggbb): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout << "Ścieżka do pliku graficznego tła strony (BRAK jeśli brak): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout << "Opcje tła strony (oddzielone średnikami, BRAK jeśli brak): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout << "Tytuł strony: ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout << "Rozmiar czcionki tytułu strony: ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout << "Kolor czcionki tytułu strony (#rrggbb): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout << "Liczba kolumn (1-4): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout << "Treść kolumn (oddzielone średnikami): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout << "Rozmiar czcionki w kolumnach (oddzielone średnikami): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout << "Kolor czcionki w kolumnach (#rrggbb, oddzielone średnikami): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout << "Kolor tła kolumn (#rrggbb, oddzielone średnikami): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout << "Ścieżki do plików graficznych teł kolumn (BRAK jeśli brak, oddzielone średnikami): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout << "Opcje tła kolumn (oddzielone średnikami, BRAK jeśli brak): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout << "Promień zaokrąglenia narożników kolumn (oddzielone średnikami): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout << "Kolor tła stopki (#rrggbb): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout << "Ścieżka do pliku graficznego tła stopki (BRAK jeśli brak): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout << "Opcje tła stopki (oddzielone średnikami, BRAK jeśli brak): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout << "Kolor czcionki w stopce (#rrggbb): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout << "Rozmiar czcionki w stopce: ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout << "Treść stopki: ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);
    }
    return wlasciwosci;
}

// Funkcja generująca stronę
void generuj_strone(const vector<string>& wlasciwosci, const string& nazwa_html, const string& nazwa_css)
{
    // Rozpakowanie danych
    string kolor_tla_strony = wlasciwosci[0];
    string sciezka_do_pliku_graficznego_tla_strony = wlasciwosci[1];
    string opcje_tla_strony = wlasciwosci[2];
    string tytul_strony = wlasciwosci[3];
    string rozmiar_czcionki_tytulu_strony = wlasciwosci[4];
    string kolor_czcionki_tytulu_strony = wlasciwosci[5];
    int liczba_kolumn = stoi(wlasciwosci[6]);
    vector<string> tresc_kolumn = podziel(wlasciwosci[7], ';');
    vector<string> rozmiar_czcionki_kolumn = podziel(wlasciwosci[8], ';');
    vector<string> kolor_czcionki_kolumn = podziel(wlasciwosci[9], ';');
    vector<string> kolor_tla_kolumn = podziel(wlasciwosci[10], ';');
    vector<string> sciezki_do_grafiki_kolumn = podziel(wlasciwosci[11], ';');
    vector<string> opcje_tla_kolumn = podziel(wlasciwosci[12], ';');
    vector<string> promien_zaokraglenia = podziel(wlasciwosci[13], ';');
    string kolor_tla_stopki = wlasciwosci[14];
    string sciezka_do_grafiki_stopki = wlasciwosci[15];
    string opcje_tla_stopki = wlasciwosci[16];
    string kolor_czcionki_stopki = wlasciwosci[17];
    string rozmiar_czcionki_stopki = wlasciwosci[18];
    string tresc_stopki = wlasciwosci[19];

    // Generowanie pliku CSS
    ofstream css_file(nazwa_css);
    if (!css_file.is_open())
    {
        cerr << "Nie można utworzyć pliku " << nazwa_css << "!" << endl;
        exit(1);
    }

    css_file << "body {\n";
    css_file << "    background-color: " << kolor_tla_strony << ";\n";
    if (sciezka_do_pliku_graficznego_tla_strony != "BRAK")
    {
        css_file << "    background-image: url('" << sciezka_do_pliku_graficznego_tla_strony << "');\n";
        css_file << "    " << opcje_tla_strony << ";\n";
    }
    css_file << "    margin: 0;\n"; // Reset marginesów
    css_file << "    padding: 0;\n"; // Reset paddingu
    css_file << "    font-family: Arial, sans-serif;\n"; // Ustawienie domyślnej czcionki
    css_file << "}\n\n";

    css_file << "h1 {\n";
    css_file << "    font-size: " << rozmiar_czcionki_tytulu_strony << ";\n";
    css_file << "    color: " << kolor_czcionki_tytulu_strony << ";\n";
    css_file << "    text-align: center;\n"; // Wyśrodkowanie tytułu
    css_file << "    margin: 20px 0;\n"; // Dodanie marginesu
    css_file << "}\n\n";

    css_file << ".main-content {\n";
    css_file << "    display: flex;\n"; // Użycie Flexboxa
    css_file << "    flex-direction: row;\n"; // Układ w poziomie
    css_file << "    justify-content: space-around;\n"; // Równomierne rozmieszczenie kolumn
    css_file << "    padding: 20px;\n"; // Padding wokół głównej zawartości
    css_file << "    flex-wrap: wrap;\n"; // Zawijanie kolumn w przypadku mniejszych ekranów
    css_file << "}\n\n";

    // Stylizacja poszczególnych kolumn
    for (int i = 0; i < liczba_kolumn; ++i)
    {
        css_file << ".col-" << i + 1 << " {\n";
        css_file << "    background-color: " << kolor_tla_kolumn[i] << ";\n";
        if (sciezki_do_grafiki_kolumn[i] != "BRAK") {
            css_file << "    background-image: url('" << sciezki_do_grafiki_kolumn[i] << "');\n";
            css_file << "    " << opcje_tla_kolumn[i] << ";\n";
        }
        css_file << "    font-size: " << rozmiar_czcionki_kolumn[i] << ";\n";
        css_file << "    color: " << kolor_czcionki_kolumn[i] << ";\n";
        css_file << "    border-radius: " << promien_zaokraglenia[i] << ";\n";
        css_file << "    padding: 15px;\n"; // Padding wewnątrz kolumn
        css_file << "    margin: 10px;\n"; // Margines wokół kolumn
        css_file << "    flex: 1; /* Kolumny rozciągają się równo */\n";
        css_file << "    min-width: 200px; /* Minimalna szerokość kolumny */\n";
        css_file << "    box-sizing: border-box;\n"; // Uwzględnienie paddingu i marginesów w szerokości
        css_file << "}\n\n";
    }

    // Stylizacja stopki
    css_file << ".footer {\n";
    css_file << "    background-color: " << kolor_tla_stopki << ";\n";
    if (sciezka_do_grafiki_stopki != "BRAK") {
        css_file << "    background-image: url('" << sciezka_do_grafiki_stopki << "');\n";
        css_file << "    " << opcje_tla_stopki << ";\n";
    }
    css_file << "    font-size: " << rozmiar_czcionki_stopki << ";\n";
    css_file << "    color: " << kolor_czcionki_stopki << ";\n";
    css_file << "    text-align: center;\n"; // Wyśrodkowanie tekstu stopki
    css_file << "    padding: 10px 0;\n"; // Padding wokół stopki
    css_file << "}\n";
    css_file.close();

    // Generowanie pliku HTML
    ofstream html_file(nazwa_html);
    if (!html_file.is_open())
    {
        cerr << "Nie można utworzyć pliku " << nazwa_html << "!" << endl;
        exit(1);
    }
    html_file << "<!DOCTYPE html>\n";
    html_file << "<html lang='pl'>\n";
    html_file << "<head>\n";
    html_file << "    <meta charset='UTF-8'>\n";
    html_file << "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
    html_file << "    <title>" << tytul_strony << "</title>\n";
    html_file << "    <link rel='stylesheet' href='" << nazwa_css << "'>\n";
    html_file << "</head>\n";
    html_file << "<body>\n";
    html_file << "    <h1>" << tytul_strony << "</h1>\n";
    html_file << "    <div class='main-content'>\n";
    for (int i = 0; i < liczba_kolumn; ++i)
    {
        html_file << "        <div class='col-" << i + 1 << "'>\n";
        if (sciezki_do_grafiki_kolumn[i] != "BRAK")
        {
            html_file << "            <img src='" << sciezki_do_grafiki_kolumn[i] << "' alt='Grafika kolumny " << i + 1 << "' style='max-width: 100%; border-radius: " << promien_zaokraglenia[i] << ";'>\n";
        }
        html_file << "            <p>" << tresc_kolumn[i] << "</p>\n";
        html_file << "        </div>\n";
    }
    html_file << "    </div>\n";
    html_file << "    <div class='footer'>\n";
    html_file << "        <p>" << tresc_stopki << "</p>\n";
    html_file << "    </div>\n";
    html_file << "</body>\n";
    html_file << "</html>\n";
    html_file.close();
}

int main()
{
    SetConsoleOutputCP(65001);
    bool z_pliku;
    string nazwa_html, nazwa_css;
    cout << "Czy chcesz pobrać dane z pliku (1) czy z klawiatury (0)? ";
    cin >> z_pliku;
    cin.ignore();  // aby zignorować znak nowej linii po cin

    cout << "Podaj nazwę pliku HTML (bez rozszerzenia): ";
    getline(cin, nazwa_html);
    nazwa_html += ".html";

    cout << "Podaj nazwę pliku CSS (bez rozszerzenia): ";
    getline(cin, nazwa_css);
    nazwa_css += ".css";

    vector<string> dane = pobierz_dane(z_pliku);

    // Sprawdzenie liczby linii
    if(dane.size() != 20)
    {
        cerr << "Plik danych powinien zawierać dokładnie 20 linii!" << endl;
        return 1;
    }

    generuj_strone(dane, nazwa_html, nazwa_css);

    cout << "Strona została wygenerowana w plikach: " << nazwa_html << " oraz " << nazwa_css << endl;
    return 0;
}
