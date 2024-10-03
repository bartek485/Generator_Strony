#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <windows.h> // Zaimportowanie potrzebnych bibliotek

using namespace std;

// Funkcja dzieląca string na przy użyciu ogranicznika
vector<string> podziel(const string &str, char ogranicznik)
{
    vector<string> czesci; // Zmienna do przechowywania podzielonych części
    string czesc; // Zmienna do przechowywania bieżącej części
    istringstream czescStream(str); // Zmienna do wyodrębniania potrzebnego tekstu
    while(getline(czescStream, czesc, ogranicznik)) // Dzieli string na części
    {
        czesci.push_back(czesc); // Dodaje część do wektora
    }
    return czesci; // Zwraca wektor z częściami
}

// Funkcja pobierająca dane z pliku lub klawiatury
vector<string> pobierz_dane(bool z_pliku)
{
    vector<string> wlasciwosci; // Zmienna do przechowywania właściwości
    string linijka; // Zmienna do przechowywania bieżącej linii

    if(z_pliku) // Jeśli dane mają być pobrane z pliku
    {
        ifstream dane("dane.txt"); // Otwiera plik "dane.txt"
        if(!dane.is_open()) // Jeśli plik nie został poprawnie otwarty
        {
            cerr<<"Nie można otworzyć pliku dane.txt!"<<endl; // Wyświetla komunikat o błędzie
            exit(1); // Zamyka program z kodem błędu
        }
        while(getline(dane, linijka)) // Odczytuje każdą linijkę tekstu z pliku
        {
            wlasciwosci.push_back(linijka); // Dodaje linijkę do wektora
        }
        dane.close(); // Zamyka plik
    }
    else // Jeśli dane mają być pobrane z klawiatury
    {
        cout<<"Wprowadź dane ręcznie:"<<endl; // Komunikat do użytkownika
        string wprowadzone; // Zmienna do przechowywania wprowadzonego tekstu
        cout<<"Kolor tła strony (#rrggbb): "; // Prośba o kolor tła
        getline(cin, wprowadzone); // Odczytuje linię z wejścia
        wlasciwosci.push_back(wprowadzone); // Dodaje kolor tła do wektora

        // Powtarza powyższe kroki dla kolejnych właściwości
        cout<<"Ścieżka do pliku graficznego tła strony (BRAK jeśli brak): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout<<"Opcje tła strony (oddzielone średnikami, BRAK jeśli brak): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout<<"Tytuł strony: ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout<<"Rozmiar czcionki tytułu strony: ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout<<"Kolor czcionki tytułu strony (#rrggbb): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout<<"Liczba kolumn (1-4): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout<<"Treść kolumn (oddzielone średnikami): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout<<"Rozmiar czcionki w kolumnach (oddzielone średnikami): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout<<"Kolor czcionki w kolumnach (#rrggbb, oddzielone średnikami): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout<<"Kolor tła kolumn (#rrggbb, oddzielone średnikami): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout<<"Ścieżki do plików graficznych teł kolumn (BRAK jeśli brak, oddzielone średnikami): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout<<"Opcje tła kolumn (oddzielone średnikami, BRAK jeśli brak): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout<<"Promień zaokrąglenia narożników kolumn (oddzielone średnikami): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout<<"Kolor tła stopki (#rrggbb): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout<<"Ścieżka do pliku graficznego tła stopki (BRAK jeśli brak): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout<<"Opcje tła stopki (oddzielone średnikami, BRAK jeśli brak): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout<<"Kolor czcionki w stopce (#rrggbb): ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout<<"Rozmiar czcionki w stopce: ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);

        cout<<"Treść stopki: ";
        getline(cin, wprowadzone);
        wlasciwosci.push_back(wprowadzone);
    }
    return wlasciwosci; // Zwraca wektor z właściwościami
}

// Funkcja generująca stronę HTML oraz CSS na podstawie danych
void generuj_strone(const vector<string>& wlasciwosci, const string& nazwa_html, const string& nazwa_css)
{
    // Rozpakowanie danych z wektora
    string kolor_tla_strony = wlasciwosci[0];
    string sciezka_do_pliku_graficznego_tla_strony = wlasciwosci[1];
    string opcje_tla_strony = wlasciwosci[2];
    string tytul_strony = wlasciwosci[3];
    string rozmiar_czcionki_tytulu_strony = wlasciwosci[4];
    string kolor_czcionki_tytulu_strony = wlasciwosci[5];
    int liczba_kolumn = stoi(wlasciwosci[6]); // Przekształca string na int
    vector<string> tresc_kolumn = podziel(wlasciwosci[7], ';'); // Dzieli treść kolumn
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
    ofstream plik_css(nazwa_css); // Otwiera plik CSS do zapisu
    if(!plik_css.is_open()) // Jeśli plik nie został otwarty
    {
        cerr<<"Nie można utworzyć pliku "<<nazwa_css<<"!"<<endl; // Wyświetla komunikat o błędzie
        exit(1); // Zamyka program z kodem błędu
    }

    // Ustawienia dla ciała strony
    plik_css<<"body {\n";
    plik_css<<"    background-color: "<<kolor_tla_strony<<";\n"; // Kolor tła
    if(sciezka_do_pliku_graficznego_tla_strony!="BRAK") // Jeśli podano ścieżkę do tła graficznego
    {
        plik_css<<"    background-image: url('"<<sciezka_do_pliku_graficznego_tla_strony<<"');\n"; // Ustawia tło graficzne
        plik_css<<"    "<<opcje_tla_strony<<";\n"; // Dodaje opcje tła
    }
    plik_css<<"    margin: 0;\n"; // Resetuje marginesy
    plik_css<<"    padding: 0;\n"; // Resetuje padding
    plik_css<<"    font-family: Arial, sans-serif;\n"; // Ustawia domyślną czcionkę
    plik_css<<"}\n\n";

    // Ustawienia dla tytułu
    plik_css<<"h1 {\n";
    plik_css<<"    font-size: " << rozmiar_czcionki_tytulu_strony << ";\n"; // Ustawia rozmiar czcionki tytułu
    plik_css<<"    color: " << kolor_czcionki_tytulu_strony << ";\n"; // Ustawia kolor czcionki tytułu
    plik_css<<"    text-align: center;\n"; // Wyśrodkowuje tytuł
    plik_css<<"    margin: 20px 0;\n"; // Dodaje margines
    plik_css<<"}\n\n";

    // Ustawienia dla głównej zawartości
    plik_css<<".main-content {\n";
    plik_css<<"    display: flex;\n"; // Używa Flexboxa (narzędzia potrzebnego do ustawienia kolumn w poziomie)
    plik_css<<"    flex-direction: row;\n"; // Ustawia kierunek na poziomy
    plik_css<<"    justify-content: space-around;\n"; // Równomierne rozmieszcza kolumny
    plik_css<<"    padding: 20px;\n"; // Padding wokół głównej zawartości
    plik_css<<"    flex-wrap: wrap;\n"; // Zawija kolumn w przypadku mniejszych ekranów
    plik_css<<"}\n\n";

    // Stylizacja poszczególnych kolumn
    for(int i=0;i<liczba_kolumn;++i) // Iteracja przez każdą kolumnę
    {
        plik_css<<".col-"<<i+1<<" {\n"; // Klasa dla danej kolumny
        plik_css<<"    background-color: "<<kolor_tla_kolumn[i]<<";\n"; // Kolor tła kolumny
        if(sciezki_do_grafiki_kolumn[i]!="BRAK") // Jeśłi podano ścieżkę do tła graficznego kolumny
        {
            plik_css<<"    background-image: url('"<<sciezki_do_grafiki_kolumn[i]<<"');\n"; // Ustawia tło graficzne kolumny
            plik_css<<"    "<<opcje_tla_kolumn[i]<<";\n"; // Dodaje opcje tła kolumny
        }
        plik_css<<"    font-size: "<<rozmiar_czcionki_kolumn[i]<<";\n"; // Ustawia rozmiar czcionki w kolumnie
        plik_css<<"    color: " << kolor_czcionki_kolumn[i] << ";\n"; // Ustawia kolor czcionki w kolumnie
        plik_css<<"    border-radius: " << promien_zaokraglenia[i] << ";\n"; // Ustawia promień zaokrąglenia narożników
        plik_css<<"    padding: 15px;\n"; // Padding wewnątrz kolumny
        plik_css<<"    margin: 10px;\n"; // Margines wokół kolumny
        plik_css<<"    flex: 1; /* Kolumny rozciągają się równo */\n"; // Umożliwia równomierne rozciąganie kolumn
        plik_css<<"    min-width: 200px; /* Minimalna szerokość kolumny */\n"; // Ustawia minimalną szerokość kolumny
        plik_css<<"    box-sizing: border-box;\n"; // Uwzględnia padding i marginesy w szerokości
        plik_css<<"}\n\n";
    }

    // Stylizacja stopki
    plik_css<<".footer {\n";
    plik_css<<"    background-color: "<<kolor_tla_stopki<<";\n"; // Kolor tła stopki
    if(sciezka_do_grafiki_stopki!="BRAK") // Jeśli podano ścieżkę do tła graficznego stopki
    {
        plik_css<<"    background-image: url('"<<sciezka_do_grafiki_stopki<<"');\n"; // Ustawia tło graficzne stopki
        plik_css<<"    "<<opcje_tla_stopki<<";\n"; // Dodaje opcje tła stopki
    }
    plik_css<<"    font-size: "<<rozmiar_czcionki_stopki<<";\n"; // Ustawia rozmiar czcionki w stopce
    plik_css<<"    color: "<<kolor_czcionki_stopki<<";\n"; // Ustawia kolor czcionki w stopce
    plik_css<<"    text-align: center;\n"; // Wyśrodkowuje tekst w stopce
    plik_css<<"    padding: 10px 0;\n"; // Padding wokół stopki
    plik_css<<"}\n"; // Zamyka deklarację CSS
    plik_css.close(); // Zamyka plik CSS

    // Generowanie pliku HTML
    ofstream pilk_html(nazwa_html); // Otwiera plik HTML do zapisu
    if(!pilk_html.is_open()) // Jeśli plik nie został otwarty
    {
        cerr<<"Nie można utworzyć pliku "<<nazwa_html<<"!"<<endl; // Wyświetla komunikat o błędzie
        exit(1); // Zamyka program z kodem błędu
    }
    pilk_html<<"<!DOCTYPE html>\n"; // Deklaracja typu dokumentu
    pilk_html<<"<html lang='pl'>\n"; // Otwiera tag HTML z określeniem języka
    pilk_html<<"<head>\n"; // Otwiera sekcję head
    pilk_html<<"    <meta charset='UTF-8'>\n"; // Ustawia kodowanie znaków
    pilk_html<<"    <meta name='viewport' content='width=device-width, initial-scale=1.0'>\n"; // Ustawia viewport dla responsywności
    pilk_html<<"    <title>" << tytul_strony << "</title>\n"; // Ustawia tytuł strony
    pilk_html<<"    <link rel='stylesheet' href='"<<nazwa_css<<"'>\n"; // Linkuje do pliku CSS
    pilk_html<<"</head>\n"; // Zamyka sekcję head
    pilk_html<<"<body>\n"; // Otwiera sekcję body
    pilk_html<<"    <h1>"<<tytul_strony<<"</h1>\n"; // Dodaje tytuł strony
    pilk_html<<"    <div class='main-content'>\n"; // Otwiera główną sekcję zawartości
    for(int i=0;i<liczba_kolumn;++i) // Iteracja przez każdą kolumnę
    {
        pilk_html<<"        <div class='col-"<<i+1<<"'>\n"; // Otwiera div dla danej kolumny
        if(sciezki_do_grafiki_kolumn[i]!="BRAK") // Jeśli podano ścieżkę do grafiki kolumny
        {
            pilk_html<<"            <img src='"<<sciezki_do_grafiki_kolumn[i]<<"' alt='Grafika kolumny "<<i+1<<"' style='max-width: 100%; border-radius: "<<promien_zaokraglenia[i]<<";'>\n"; // Dodaje obrazek z danymi stylami
        }
        pilk_html<<"            <p>"<<tresc_kolumn[i]<<"</p>\n"; // Dodaje treść kolumny
        pilk_html<<"        </div>\n"; // Zamyka div dla danej kolumny
    }
    pilk_html<<"    </div>\n"; // Zamyka główną sekcję zawartości
    pilk_html<<"    <div class='footer'>\n"; // Otwiera sekcję stopki
    pilk_html<<"        <p>" << tresc_stopki << "</p>\n"; // Dodaje treść stopki
    pilk_html<<"    </div>\n"; // Zamyka sekcję stopki
    pilk_html<<"</body>\n"; // Zamyka sekcję body
    pilk_html<<"</html>\n"; // Zamyka tag HTML
    pilk_html.close(); // Zamyka plik HTML
}

int main()
{
    SetConsoleOutputCP(CP_UTF8); // Ustawia kodowanie wyjścia na UTF-8 (Windows)

    bool z_pliku;
    string nazwa_html, nazwa_css;
    cout<<"Witamy w generatorze strony!"<<endl;
    cout<<"Czy chcesz pobrać dane z pliku (1) czy z klawiatury (0)? ";
    cin>>z_pliku;
    cin.ignore();  // aby zignorować znak nowej linii po cin

    cout<<"Podaj nazwę pliku HTML (bez rozszerzenia): ";
    getline(cin, nazwa_html);
    nazwa_html += ".html";

    cout<<"Podaj nazwę pliku CSS (bez rozszerzenia): ";
    getline(cin, nazwa_css);
    nazwa_css += ".css";

    vector<string> dane = pobierz_dane(z_pliku);

    // Sprawdzenie liczby linijek w pliku
    if(dane.size()!=20) // Jeśli liczba linijek tekstu nie jest równa oczekiwanej
    {
        cerr<<"Plik danych powinien zawierać dokładnie 20 linijek!"<<endl; // Wyświetla komunikat o błędzie
        return 1;
    }

    generuj_strone(dane, nazwa_html, nazwa_css);

    cout<<"Strona została wygenerowana w plikach: "<<nazwa_html<<" oraz "<<nazwa_css<<endl;
    return 0;
}
