#include "main.h"
// funkcja potrzebna do wyboru w funkcji 
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// LISTY DLA GRACZY
/**
 * @brief Dodaje gracza do listy cyklicznej
 *
 * @param gracze pole, kt�re ma by� dodane
 * @param lista cykliczna z graczami
 *
 * @return List� cykliczn� z dodanym graczem
 *
 * Funkcja dodaj_gracza_do_listy() sprawdza, czy lista cykliczna z graczami jest pusta. Je�li lista jest pusta (NULL), to ustawiamy gracza jako jedyny element listy.
 * Gracz wskazuje na sam siebie, poniewa� jest jedynym elementem listy.
 * Funkcja szuka ostatniego elementu w li�cie, przechodz�c przez kolejne elementy a� do momentu,
 * gdy "next" elementu nie wskazuje na pocz�tek listy (czyli gracze).
 * Po znalezieniu ostatniego elementu, ustawiamy jego wska�nik "next" na nowo dodanego gracza.
 * Ustawiamy wska�nik "next" nowo dodanego gracza na pocz�tek listy.
 * Zwracamy pocz�tek listy (pierwszy element).
 */
Gracz* dodaj_gracza_do_listy(Gracz* gracze, Gracz* lista) {
    if (lista == NULL) {
        gracze->next = gracze;
        return gracze;
    }

    Gracz* ostatni = lista;
    while (ostatni->next != lista) {
        ostatni = ostatni->next;
    }
    ostatni->next = gracze;
    gracze->next = lista;
    return lista;
}

/**
 * @brief Usuwa gracza z listy cyklicznej
 *
 * @param lista cykliczna z graczami
 * @param gracz, kt�ry ma by� usuni�ty
 *
 * Funkcja usun_gracza() sprawdza, czy lista jest pusta. Je�li tak, to nie ma �adnego gracza do usuni�cia, wi�c funkcja ko�czy si�.
 * Je�li pierwszy element listy (*lista) jest r�wny usuni�temu graczowi, to mamy do czynienia z usuwaniem pierwszego elementu.
 * Wtedy znajdujemy ostatni element listy, przemieszczaj�c si� przez kolejne elementy, a� wska�nik "next" ostatniego elementu wskazuje na pierwszy element listy (*lista).
 * Je�li ostatni element r�wnie� wskazuje na pierwszy element, to oznacza, �e lista zawiera�a tylko jeden element, i po usuni�ciu tego elementu lista staje si� pusta.
 * W przeciwnym przypadku przesuwamy wska�nik *lista na drugi element, a wska�nik "next" ostatniego elementu aktualizujemy, aby wskazywa� na nowy pierwszy element.
 * Je�li pierwszy element listy (*lista) nie jest r�wny usuni�temu graczowi, to musimy przeszuka� list�, aby znale�� poprzednika usuwanego elementu.
 * Przesuwamy si� przez kolejne elementy, a� wska�nik "next" obecnego elementu wskazuje na *lista (czyli dojedziemy do ko�ca listy) lub wska�nik "next" obecnego elementu jest r�wny
 * usuni�temu graczowi. Je�li znajdziemy poprzednika, to aktualizujemy jego wska�nik "next", aby omija� usuwanego gracza.
 * Na ko�cu, po usuni�ciu gracza z listy, zwalniamy pami�� zajmowan� przez usuni�tego gracza, u�ywaj�c funkcji free(usuniety).
 */
void usun_gracza(Gracz** lista, Gracz* usuniety) {
    if (*lista == NULL) {
        return;  // Lista jest pusta, nie ma nic do usuni�cia
    }

    if (*lista == usuniety) {
        // Usu� pierwszy element z listy
        Gracz* last_player = (*lista)->next;
        while (last_player->next != *lista) {
            last_player = last_player->next;
        }
        if (last_player == *lista) {
            *lista = NULL;  // Lista zawiera�a tylko jeden element
        }
        else {
            *lista = (*lista)->next;
            last_player->next = *lista;
        }
    }
    else {
        // Przeszukaj list�, aby znale�� poprzednik usuwanego elementu
        Gracz* obecne = *lista;
        while (obecne->next != *lista && obecne->next != usuniety) {
            obecne = obecne->next;
        }
        if (obecne->next == usuniety) {
            // Usu� gracza z listy
            obecne->next = usuniety->next;
        }
    }
    free(usuniety);  // Zwolnij pami�� zajmowan� przez usuni�tego gracza
}

// LISTY DLA PYTAN
/**
 * @brief Dodaje pytanie do listy cyklicznej
 *
 * @param nowe_pytanie wska�nik do pytania, kt�re ma by� dodane do listy
 * @param lista wska�nik do listy pytani
 *
 * Funkcja dodaj_pytanie_do_listy() sprawdza, czy lista jest pusta. Je�li tak, to nowe_pytanie staje si� jedynym elementem listy,
 * a jego wska�nik "next" wskazuje na samo siebie. Nast�pnie zwracamy wska�nik nowe_pytanie jako nowy pocz�tek listy.
 * Je�li lista nie jest pusta, przeszukujemy list�, aby znale�� ostatni element. Przesuwamy si� przez kolejne elementy,
 * a� wska�nik "next" ostatniego elementu wskazuje na pocz�tek listy (*lista). Nast�pnie ustawiamy wska�nik "next" ostatniego elementu
 * na nowe_pytanie, a wska�nik "next" nowe_pytanie ustawiamy na pocz�tek listy (*lista). Na ko�cu zwracamy wska�nik *lista jako nowy pocz�tek listy.
 */
Pytanie* dodaj_pytanie_do_listy(Pytanie* nowe_pytanie, Pytanie* lista) {
    if (lista == NULL) {
        nowe_pytanie->next = nowe_pytanie;
        return nowe_pytanie;
    }
    Pytanie* ostatni = lista->next;
    while (ostatni->next != lista) {
        ostatni = ostatni->next;
    }
    ostatni->next = nowe_pytanie;
    nowe_pytanie->next = lista;

    return lista;
}

/**
 * @brief Dodaje pytania z pliku do listy cyklicznej
 *
 * @param lista wska�nik do listy pytani
 * @param nazwa_pliku nazwa pliku zawieraj�cego pytania do dodania
 *
 * Funkcja dodaj_pytanie() otwiera plik o podanej nazwie i wczytuje kolejne linie jako pytania do dodania do listy.
 * Je�li nie uda si� otworzy� pliku, funkcja wypisuje odpowiedni komunikat i zwraca oryginaln� list� bez �adnych zmian.
 * W p�tli wczytuje linie pliku, a nast�pnie tworzy nowy element listy Pytanie i inicjalizuje go warto�ciami z wczytanej linii.
 * Warto�� pola "tresc" jest kopiowana bez pierwszego znaku '*', kt�ry jest pomijany.
 * Nast�pnie, w zale�no�ci od pierwszego znaku wczytanej linii, funkcja okre�la, kt�ra odpowied� jest poprawna i ustawia odpowiednie
 * pola w strukturze Pytanie. Po utworzeniu nowego pytania, dodaje je do listy za pomoc� funkcji dodaj_pytanie_do_listy().
 * Po przetworzeniu wszystkich linii w pliku, funkcja zamyka plik i zwraca zaktualizowan� list�.
 */
Pytanie* dodaj_pytanie(Pytanie* lista, char* nazwa_pliku) {
    FILE* plik_pytan;
    if (fopen_s(&plik_pytan, nazwa_pliku, "r") != 0) {
        printf("B��d podczas otwierania pliku: %s\n", nazwa_pliku);
        return lista;  // Zwracamy oryginaln� list�, je�li nie uda�o si� otworzy� pliku
    }

    char linia[MAX_LEN];
    while (fgets(linia, MAX_LEN, plik_pytan) != NULL) {
        // Nowe pytanie
        Pytanie* nowe_pytanie = (Pytanie*)malloc(sizeof(Pytanie));
        strcpy_s(nowe_pytanie->tresc, sizeof(nowe_pytanie->tresc), linia);  // Pomijamy znak '*' na pocz�tku
        nowe_pytanie->poprawna_odpowiedz = 0;

        // Dodaj odpowiedzi
        for (int i = 0; i < MAX_ANSWER; i++) {
            fgets(linia, MAX_LEN, plik_pytan);
            if (linia[0] == '*')
            {
                strcpy_s(nowe_pytanie->odpowiedzi[i], sizeof(nowe_pytanie->odpowiedzi[i]), linia + 1);
                nowe_pytanie->poprawna_odpowiedz = i;  // Indeks poprawnej odpowiedzi
            }
            else
                strcpy_s(nowe_pytanie->odpowiedzi[i], sizeof(nowe_pytanie->odpowiedzi[i]), linia);
        }
        lista = dodaj_pytanie_do_listy(nowe_pytanie, lista);  // Dodaj nowe pytanie do listy
    }
    fclose(plik_pytan);
    return lista;  // Zwracamy zaktualizowan� list�
}

/**
 * @brief Wybiera losowe pytanie z listy cyklicznej
 *
 * @param lista_pytan wska�nik do listy pyta�
 * @return wska�nik do wybranego pytania
 *
 * Funkcja wylosuj_pytanie() inicjalizuje generator liczb losowych za pomoc� srand(time(NULL)).
 * Nast�pnie generuje losow� liczb� w zakresie od 0 do 49 (random_number).
 * Je�li lista_pytan nie jest pusta, funkcja przechodzi przez list� pyta� losow� liczb� razy, przesuwaj�c si�
 * przez kolejne elementy przy pomocy wska�nika "next".
 * Na ko�cu zwraca wska�nik do wybranego pytania.
 */
Pytanie* wylosuj_pytanie(Pytanie* lista_pytan) {
    srand(time(NULL));
    // Losowanie liczby
    int random_number;
    // Przechodzenie przez list� pyta� wylosowan� liczb� razy
    if (lista_pytan != NULL)
    {
        random_number = 1 + rand() % 9;
        for (int i = 0; i < random_number; i++) {
            lista_pytan = lista_pytan->next;
        }
    }
    return lista_pytan;
}

/**
 * @brief Usuwa ca�� list� cykliczn� pyta�
 *
 * @param lista_pytan wska�nik do listy pyta� do usuni�cia
 *
 * Funkcja usun_liste_pytan() sprawdza, czy lista_pytan jest pusta. Je�li tak, to nie ma �adnych pyta� do usuni�cia,
 * wi�c funkcja ko�czy si�. W przeciwnym przypadku, funkcja przechodzi przez list� pyta�, zaczynaj�c od wska�nika lista_pytan,
 * i zwalnia pami�� zajmowan� przez ka�de pytanie. W ka�dym kroku p�tli, funkcja zachowuje referencj� do nast�pnego pytania
 * (nastepne_pytanie), zwalnia pami�� aktualnego pytania (aktualne_pytanie), a nast�pnie przesuwa wska�nik na nast�pne pytanie.
 * P�tla wykonuje si�, dop�ki aktualne_pytanie nie jest r�wne lista_pytan, co oznacza, �e przeszlismy przez ca�� list�.
 * Na koniec, opcjonalnie mo�na ustawi� wska�nik lista_pytan na NULL, aby jawnie wskaza�, �e lista jest pusta.
 */
void usun_liste_pytan(Pytanie* lista_pytan) {
    if (lista_pytan == NULL) {
        return;  // Lista jest pusta, nie ma nic do usuni�cia
    }

    Pytanie* aktualne_pytanie = lista_pytan;
    Pytanie* nastepne_pytanie;

    do {
        nastepne_pytanie = aktualne_pytanie->next;  // Zachowujemy referencj� do nast�pnego pytania
        free(aktualne_pytanie);  // Zwolnienie pami�ci aktualnego pytania
        aktualne_pytanie = nastepne_pytanie;  // Przesuni�cie wska�nika na nast�pne pytanie
    } while (aktualne_pytanie != lista_pytan);

    lista_pytan = NULL;  // Ustawienie wska�nika na list� pyta� na NULL (opcjonalne)
}

/**
 * @brief Usuwa pytanie z listy cyklicznej
 *
 * @param lista_pytan wska�nik do listy pyta�
 * @param pytanie_usuniete wska�nik do pytania, kt�re ma by� usuni�te
 *
 * Funkcja usun_pytanie() sprawdza, czy lista_pytan jest pusta. Je�li tak, to nie ma nic do usuni�cia, wi�c funkcja ko�czy si�.
 * Je�li lista_pytan wskazuje na pytanie_usuniete, to mamy do czynienia z usuwaniem pierwszego elementu.
 * W takim przypadku ustawiamy wska�nik lista_pytan na nast�pny element, aby usun�� pierwszy element z listy.
 * Je�li lista_pytan nie wskazuje na pytanie_usuniete, musimy przeszuka� list�, aby znale�� poprzednika pytanie_usuniete.
 * Przechodzimy przez kolejne elementy, a� wska�nik "next" obecnego elementu wskazuje na pytanie_usuniete lub osi�gniemy koniec listy.
 * Je�li znajdziemy poprzednika, to aktualizujemy jego wska�nik "next", aby omija� pytanie_usuniete.
 * Na ko�cu, po usuni�ciu pytania z listy, zwalniamy pami�� zajmowan� przez pytanie_usuniete, u�ywaj�c funkcji free(pytanie_usuniete).
 */
void usun_pytanie(Pytanie* lista_pytan, Pytanie* pytanie_usuniete) {
    if (lista_pytan == NULL) {
        return;  // Lista jest pusta, nie ma nic do usuni�cia
    }
    if (lista_pytan == pytanie_usuniete) {
        // Usu� pierwszy element z listy
        lista_pytan = lista_pytan->next;
    }
    else {
        // Przeszukaj list�, aby znale�� poprzednik usuwanego elementu
        Pytanie* obecne = lista_pytan;
        while (obecne->next != NULL && obecne->next != pytanie_usuniete) {
            obecne = obecne->next;
        }
        if (obecne->next == pytanie_usuniete) {
            // Usu� pytanie z listy
            obecne->next = pytanie_usuniete->next;
        }
    }
    free(pytanie_usuniete);  // Zwolnij pami�� zajmowan� przez usuni�te pytanie
}

/**
 * @brief Dodaje pytanie do pliku
 *
 * @param nazwa_pliku nazwa pliku, do kt�rego ma by� dodane pytanie
 *
 * Funkcja add_question_to_file() otwiera plik o podanej nazwie w trybie "a" (dopisywanie).
 * Je�li nie uda si� otworzy� pliku, funkcja wy�wietla komunikat o b��dzie i ko�czy dzia�anie.
 * Nast�pnie u�ytkownik jest proszony o wprowadzenie tre�ci pytania i odpowiedzi.
 * Tre�� pytania jest wczytywana za pomoc� fgets() do tablicy tresc_pytania.
 * Odpowiedzi s� wprowadzane w p�tli, gdzie u�ytkownik jest proszony o podanie odpowiedzi i s� one wczytywane do tablicy odpowiedzi.
 * Na koniec, tre�� pytania oraz odpowiedzi s� zapisywane do pliku za pomoc� fprintf().
 * Plik jest zamykany za pomoc� fclose().
 */
void add_question_to_file(char* nazwa_pliku) {
    FILE* plik_pytan;
    if (fopen_s(&plik_pytan, nazwa_pliku, "a") != 0) {
        printf("B��d podczas otwierania pliku: %s\n", nazwa_pliku);
        return;
    }

    char tresc_pytania[MAX_LEN];
    char odpowiedzi[MAX_ANSWER][MAX_LEN];

    printf("Podaj tre�� pytania: ");
    clearInputBuffer();
    fgets(tresc_pytania, MAX_LEN, stdin);

    printf("Podaj odpowiedzi (odpowied� poprawna poprzedzona znakiem '*', np. *Warszawa):\n");
    for (int i = 0; i < MAX_ANSWER; i++) {
        printf("Odpowied� %d: ", i + 1);
        fgets(odpowiedzi[i], MAX_LEN, stdin);
    }

    fprintf(plik_pytan, "%s", tresc_pytania);
    for (int i = 0; i < MAX_ANSWER; i++) {
        fprintf(plik_pytan, "%s", odpowiedzi[i]);
    }

    fclose(plik_pytan);
}

// GRA
// zwyk�a gra, bez mno�nika, bez czasu
/**
 * @brief Funkcja odpowiada za rozgrywk� w grze
 *
 * @param player wska�nik do obiektu gracza
 * @param questions wska�nik do listy pyta�
 * @param wybor warto�� okre�laj�ca rodzaj wyboru
 *
 * Funkcja zagraj() inicjalizuje zmienn� answer, kt�ra przechowuje numer odpowiedzi gracza, oraz zmienn� score, kt�ra przechowuje
 * aktualny wynik gracza. Nast�pnie wywo�uje funkcj� wylosuj_pytanie(), aby wybra� losowe pytanie z listy. Wy�wietla tre�� pytania
 * oraz mo�liwe odpowiedzi. Gracz wybiera numer odpowiedzi, korzystaj�c z funkcji wybierz_opcje(), a nast�pnie por�wnuje go z
 * indeksem poprawnej odpowiedzi w strukturze pytania. Je�li odpowied� jest poprawna, zwi�ksza wynik gracza i wy�wietla informacj�
 * o poprawnej odpowiedzi. W przeciwnym przypadku wy�wietla informacj� o b��dnej odpowiedzi. Na ko�cu wywo�uje funkcj� usun_pytanie()
 * w celu usuni�cia wykorzystanego pytania z listy.
 */
void zagraj(Gracz* player, Pytanie* questions, int wybor) {
    int answer;
    unsigned int score = 0;
    Pytanie* current_question;
    current_question = wylosuj_pytanie(questions);
    printf("%s", current_question->tresc);
    for (int i = 0; i < 4; i++) {
        printf("%d. %s", i + 1, current_question->odpowiedzi[i]);
    }
    printf("Podaj numer odpowiedzi: \n");

    answer = wybierz_opcje(wybor);
    if (answer - 1 == current_question->poprawna_odpowiedz) {
        player->score += 1;
        printf("Odpowied� poprawna!\nNaci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
    }
    else {
        player->multiplier = 1;
        printf("Odpowied� b��dna!\nNaci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
    }
    usun_pytanie(questions, current_question);
}

// gra z mno�nikiem, bez czasu
/**
 * @brief Funkcja odpowiedzialna za rozgrywk� w trybie mno�nika
 *
 * @param player wska�nik do struktury gracza
 * @param questions wska�nik do listy pyta�
 * @param wybor wyb�r opcji
 *
 * Funkcja zagraj_mnoznik() rozpoczyna gr� w trybie mno�nika dla danego gracza.
 * Losuje jedno pytanie z listy pyta�, u�ywaj�c funkcji wylosuj_pytanie().
 * Nast�pnie wy�wietla tre�� pytania oraz odpowiedzi dla gracza.
 * Gracz podaje numer odpowiedzi poprzez funkcj� wybierz_opcje(wybor).
 * Je�li udzieli poprawnej odpowiedzi, zwi�ksza swoje punkty o warto�� mno�nika (player->multiplier),
 * a nast�pnie zwi�ksza mno�nik o 1 (je�li mno�nik jest mniejszy od 3).
 * Je�li udzieli b��dnej odpowiedzi, mno�nik zostaje zresetowany do warto�ci 1.
 * Na ko�cu usuwa wykorzystane pytanie z listy pyta�, u�ywaj�c funkcji usun_pytanie(&questions, current_question).
 */
void zagraj_mnoznik(Gracz* player, Pytanie* questions, int wybor) {
    int answer;
    unsigned int score = 0;
    Pytanie* current_question;
    current_question = wylosuj_pytanie(questions);
    printf("%s", current_question->tresc);
    for (int i = 0; i < 4; i++) {
        printf("%d. %s", i + 1, current_question->odpowiedzi[i]);
    }
    printf("Podaj numer odpowiedzi: \n");

    answer = wybierz_opcje(wybor);
    if (answer - 1 == current_question->poprawna_odpowiedz) {
        if (player->multiplier < 5) {
            player->score += player->multiplier;
            player->multiplier++;
        }
        else {
            player->score += player->multiplier;
        }
        printf("Odpowied� poprawna!\nNaci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
    }
    else {
        player->multiplier = 1;
        printf("Odpowied� b��dna!\nNaci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
    }
    usun_pytanie(questions, current_question);
}

// gra z mno�nikiem i czasem
/**
 * @brief Funkcja realizuj�ca gr� z ograniczonym czasem na udzielenie odpowiedzi na pytanie
 *
 * @param player wska�nik do obiektu gracza
 * @param questions wska�nik do listy pyta�
 * @param wybor wyb�r opcji w grze
 *
 * Funkcja zagraj_czas() przygotowuje pytanie do wy�wietlenia poprzez wylosowanie pytania z listy
 * i inicjalizacj� czasu pocz�tkowego. Nast�pnie wy�wietla tre�� pytania oraz mo�liwe odpowiedzi.
 * Gracz ma 10 sekund na udzielenie odpowiedzi. Podczas oczekiwania na odpowied� wy�wietla up�ywaj�cy czas.
 * Je�li gracz udzieli odpowiedzi przed up�ywem 10 sekund, sprawdza poprawno�� odpowiedzi i aktualizuje wynik i mno�nik gracza.
 * Po zako�czeniu pytania usuwa je z listy.
 */
void zagraj_czas(Gracz* player, Pytanie* questions, int wybor) {
    int answer;
    Pytanie* current_question;
    current_question = wylosuj_pytanie(questions);
    printf("%s", current_question->tresc);
    for (int i = 0; i < 4; i++) {
        printf("%d. %s", i + 1, current_question->odpowiedzi[i]);
    }
    printf("Podaj numer odpowiedzi: \n");

    time_t startTime = time(0); // Pocz�tkowy czas dla pytania
    time_t lastDisplayedTime = startTime;
    int allowAnswer = 0; // Flaga, czy umo�liwiono odpowied�

    while (1) {
        time_t currentTime = time(0);
        double timeElapsed = difftime(currentTime, startTime);

        if (currentTime > lastDisplayedTime && timeElapsed < 10) {
            printf("%.0f... ", timeElapsed);
            fflush(stdout); // Wymuszenie natychmiastowego wy�wietlenia tekstu
            lastDisplayedTime = currentTime;
        }

        if (timeElapsed >= 10 && !allowAnswer) {
            player->multiplier = 1;
            printf("Min�o 10 sekund.\n");
            break;
        }

        if (kbhit() && (timeElapsed < 10 || allowAnswer)) { // Sprawdzanie czy klawisz zosta� naci�ni�ty
            answer = wybierz_opcje(wybor);
            time_t endTime = time(0); // Ko�cowy czas dla pytania
            double timeTaken = difftime(endTime, startTime); // Czas w sekundach
            if (answer - 1 == current_question->poprawna_odpowiedz) {
                player->score += player->multiplier;

                // Obliczenie mno�nika na podstawie czasu odpowiedzi
                if (timeTaken < 5) {
                    player->multiplier += 1;
                }
                else if (timeTaken >= 5 && timeTaken < 10) {
                    player->multiplier += 0.5;
                }
                printf("Odpowied� poprawna!\n");
            }
            else {
                player->multiplier = 1;
                printf("Odpowied� b��dna!\n");
            }
            break;
        }

        if (timeElapsed >= 10 && !allowAnswer) {
            // Sprawdzanie czy up�yn�o ju� 10 sekund, aby zako�czy� pytanie
            break;
        }

        // Czekaj 1 sekund�
        Sleep(1);
        fflush(stdout); // Wymuszenie natychmiastowego wy�wietlenia tekstu
    }

    printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
    usun_pytanie(questions, current_question);
}

/**
 * @brief Wy�wietla pytania dla graczy z listy cyklicznej
 *
 * @param player wska�nik do gracza, od kt�rego rozpoczyna si� wy�wietlanie
 * @param lista wska�nik do listy pyta�
 * @param no_gracze liczba graczy
 * @param wybor wyb�r odpowiedzi przez gracza
 * @param no_pytan liczba wszystkich pyta�
 * @param tryb tryb gry (1 - standardowy, 2 - z mno�nikiem, 3 - z ograniczonym czasem)
 *
 * Funkcja pokaz_pytania() wy�wietla pytania dla graczy z listy cyklicznej.
 * Przechodzi przez list� graczy, rozpoczynaj�c od gracza wskazywanego przez parametr "player".
 * Dla ka�dego gracza wy�wietla pytania i wywo�uje odpowiedni� funkcj� do gry w zale�no�ci od trybu.
 * Po zako�czeniu gry dla ka�dego pytania, przechodzi do nast�pnego gracza.
 * Po ka�dym pytaniu oczekuje na naci�ni�cie dowolnego klawisza przez u�ytkownika i czy�ci ekran.
 */
void pokaz_pytania(Gracz* player, Pytanie* lista, int no_gracze, int wybor, unsigned int no_pytan, int tryb)
{
    if (lista != NULL)
    {
        int no_q = (no_pytan / 3) * no_gracze;
        Gracz* current_player = player;
        for (int i = 0; i < no_q; i++)
        {
            printf("Gracz %s, wynik %.2lf, mno�nik %.2lf\nPytanie %d: ", current_player->nickname, current_player->score, current_player->multiplier, i + 1);

            switch (tryb)
            {
            case 1:
                zagraj(current_player, lista, wybor);
                break;
            case 2:
                zagraj_mnoznik(current_player, lista, wybor);
                break;
            case 3:
                zagraj_czas(current_player, lista, wybor);
                break;
            }

            current_player = current_player->next;
            getch();
            system("cls");
        }
    }
    else
        printf("B��d! Nie wczytano pliku.");
}

/**
 * @brief Wybiera opcj� z podanego zakresu
 *
 * @param wybor warto�� wyboru, kt�ra okre�la zakres opcji do wyboru
 * @return wybrana opcja
 *
 * Funkcja wybierz_opcje() przyjmuje warto�� wyboru (wybor) i w zale�no�ci od tego wyboru
 * ustala zakres opcji do wyboru. Nast�pnie pobiera liczb� od u�ytkownika i sprawdza, czy
 * wprowadzona liczba mie�ci si� w zakresie opcji. Je�li tak, zwraca wybran� opcj�.
 * W przypadku niepoprawnego wprowadzenia liczby, wy�wietla b��d i prosi u�ytkownika
 * o wprowadzenie poprawnej liczby. Funkcja kontynuuje pobieranie danych od u�ytkownika,
 * dop�ki nie zostanie wprowadzona poprawna liczba opcji.
 */
int wybierz_opcje(int wybor) {
    int choice = 0;
    int ile;
    int input = 0;
    do {
        if (wybor == 0) {
            ile = 2;
            printf("\nPodaj liczb� od 1 do %d:\n", ile);
            scanf_s("%d", &input);

            if (input >= 1 && input <= ile) {
                choice = input;
            }
            else {
                printf("\nB��d. Wprowad� poprawn� liczb� od 1 do %d.\n", ile);
                clearInputBuffer(); // Wyczy�� bufor wej�ciowy
            }
        }
        else if (wybor == 1) {
            ile = 11;
            printf("\nPodaj liczbe od 1 do %d:\n", ile);
            scanf_s("%d", &input);

            if (input >= 1 && input <= ile) {
                choice = input;
            }
            else {
                printf("\nB��d. Wprowad� poprawn� liczb� od 1 do %d.\n", ile);
                clearInputBuffer(); // Wyczy�� bufor wej�ciowy
            }
        }
        else if (wybor == 2) {
            ile = 4;
            printf("\nPodaj liczb� od 1 do %d:\n", ile);
            scanf_s("%d", &input);

            if (input >= 1 && input <= ile) {
                choice = input;
            }
            else {
                printf("\nB��d. Wprowad� poprawn� liczb� od 1 do %d.\n", ile);
                clearInputBuffer(); // Wyczy�� bufor wej�ciowy
            }
        }
    } while (choice < 1 || choice > ile);

    return choice;
}

/**
 * @brief Zapisuje najlepszy wynik gracza do pliku
 *
 * @param player wska�nik do struktury Gracz
 *
 * Funkcja najlepszy_wynik() otwiera plik "najlepszy_wynik.txt" w trybie odczytu.
 * Je�li plik nie istnieje, tworzy go w trybie zapisu.
 * Je�li plik istnieje, odczytuje z niego dotychczasowy najlepszy wynik.
 * Je�li wynik gracza nie jest lepszy od dotychczasowego najlepszego wyniku, funkcja ko�czy si�.
 * W przeciwnym przypadku otwiera plik w trybie zapisu i zapisuje nowy najlepszy wynik oraz nazw� gracza.
 * Na koniec zamyka plik i wy�wietla informacj� o zapisaniu najlepszego wyniku.
 */
void najlepszy_wynik(Gracz* player) {
    FILE* file;
    char filename[] = "najlepszy_wynik.txt";
    int najlepszy_wynik = 0;

    // Otwarcie pliku w trybie do odczytu
    if (fopen_s(&file, filename, "r") != 0) {
        // Plik nie istnieje, wi�c tworzymy nowy
        if (fopen_s(&file, filename, "w") != 0) {
            printf("B��d podczas tworzenia pliku.\n");
            return;
        }
    }
    else {
        // Plik istnieje, wi�c odczytujemy najlepszy wynik
        fscanf_s(file, "%d", &najlepszy_wynik);
        fclose(file);

        // Sprawdzamy, czy wynik jest lepszy od ju� zapisanego
        if (player->score <= najlepszy_wynik) {
            printf("Tw�j wynik nie jest lepszy od najlepszego wyniku.\n");
            return;
        }

        // Otwarcie pliku w trybie do zapisu (nadpisanie poprzednich danych)
        if (fopen_s(&file, filename, "w") != 0) {
            printf("B��d podczas zapisywania do pliku.\n");
            return;
        }
    }

    // Zapisanie nowego najlepszego wyniku do pliku
    fprintf(file, "%.2lf ", player->score);
    fprintf(file, "%s\n", player->nickname);

    fclose(file);
    printf("Tw�j wynik zosta� zapisany jako najlepszy wynik!\n");
}

/**
 * @brief Wybiera tryb gry
 *
 * @return numer wybranego trybu
 *
 * Funkcja wybierz_tryb() wy�wietla u�ytkownikowi opcje wyboru trybu gry: NORMALNY, MNO�NIK, MNO�NIK+CZAS.
 * U�ytkownik podaje numer trybu od 1 do 3, a funkcja sprawdza poprawno�� wprowadzonej warto�ci.
 * Je�li podany numer jest spoza zakresu 1-3, u�ytkownik jest proszony o ponowne wprowadzenie warto�ci.
 * Na koniec funkcja zwraca wybrany numer trybu.
 */
int wybierz_tryb()
{
    int mode;
    printf("Wybierz tryb gry:\n");
    printf("1. NORMALNY\n");
    printf("2. MNO�NIK\n");
    printf("3. MNO�NIK+CZAS\n");

    do {
        printf("Podaj numer trybu od 1 do 3: ");
        scanf_s("%d", &mode);
    } while (mode < 1 || mode > 3);

    return mode;
}

/**
 * @brief Wy�wietla wyniki z ostatniej rundy
 *
 * @param player wska�nik do aktualnego gracza
 * @param lista wska�nik do listy graczy
 * @param no_gracze liczba graczy
 *
 * Funkcja pokaz_wyniki() wy�wietla wyniki z ostatniej rundy.
 * Najpierw inicjalizuje zmienn� best na warto�� pocz�tkow�.
 * Nast�pnie przechodzi przez list� graczy, wy�wietlaj�c nazw� gracza i jego wynik.
 * Je�li wynik gracza jest wi�kszy od dotychczasowego najlepszego wyniku (best), aktualizuje warto�� best i resetuje flag� remisu.
 * Je�li wynik gracza jest r�wny dotychczasowemu najlepszemu wynikowi (best), ustawia flag� remisu na 1.
 * Po przej�ciu przez wszystkich graczy, sprawdza czy wyst�pi� remis.
 * Je�li tak, wy�wietla odpowiedni komunikat.
 * Je�li nie, przechodzi ponownie przez list� graczy, aby znale�� gracza z najlepszym wynikiem.
 * Wy�wietla informacj� o zwyci�zcy i wywo�uje funkcj� najlepszy_wynik() dla tego gracza.
 * Na ko�cu oczekuje na naci�ni�cie dowolnego klawisza i czy�ci ekran.
 */
void pokaz_wyniki(Gracz* player, Gracz* lista, int no_gracze)
{
    double best = 0; // Inicjalizacja best na pocz�tkow� warto��
    int isDraw = 0; // Flaga oznaczaj�ca remis
    printf("Wyniki z ostatniej rundy:\n");
    player = lista;
    do {
        printf("Gracz: %s, Wynik: %.2lf\n", player->nickname, player->score);
        if (player->score > best) {
            best = player->score;
            isDraw = 0;  // Resetowanie flagi remisu
        }
        else if (player->score == best) {
            isDraw = 1;  // Ustawienie flagi remisu
        }
        player = player->next;
    } while (player != lista);

    if (isDraw) {
        printf("\nRemis! Brak zwyci�zcy.\n");
    }
    else {
        // Ponownie przechodzimy przez list�, aby znale�� gracza z najlepszym wynikiem
        player = lista;
        while (player->score != best) {
            player = player->next;
        }
        printf("\nGracz %s, zwyci�y�!\nGRATULACJE!\n", player->nickname);
        najlepszy_wynik(player);
    }

    getch();
    system("cls");
}

/**
 * @brief Rozpoczyna gr�
 *
 * @param no_pytan liczba pyta� na gracza
 * @param wybor opcja wyboru
 * @param no_gracze liczba graczy
 * @param plik_latwe nazwa pliku z pytaniami �atwymi
 * @param plik_srednie nazwa pliku z pytaniami �rednimi
 * @param plik_trudne nazwa pliku z pytaniami trudnymi
 *
 * Funkcja gra() inicjalizuje gr�. Pocz�tkowo pobiera liczb� graczy od u�ytkownika i tworzy list� graczy.
 * Nast�pnie pobiera liczb� pyta� na gracza, przy czym u�ytkownik musi wybra� warto�� spo�r�d 6, 9, 12, 15 lub 18.
 * Tworzy listy pyta� dla r�nych poziom�w trudno�ci i wybiera tryb gry.
 * Wy�wietla pytania dla ka�dego gracza i na ka�dy poziom trudno�ci.
 * Na koniec wy�wietla wyniki, usuwa listy graczy i pyta�, a nast�pnie ko�czy gr�.
 */
void gra(unsigned int no_pytan, int wybor, int no_gracze, char plik_latwe[], char plik_srednie[], char plik_trudne[])
{
    printf("Podaj liczb� graczy.\n");
    wybor = 2;
    no_gracze = wybierz_opcje(wybor);
    system("cls");

    Gracz* gracze = NULL;
    Gracz* lista = NULL;

    for (int i = 0; i < no_gracze; i++) {
        Gracz* nowy_gracz = (Gracz*)malloc(sizeof(Gracz));
        printf("Podaj imi� gracza %d: ", i + 1);
        scanf_s("%s", nowy_gracz->nickname, MAX_NICK);
        nowy_gracz->score = 0;
        nowy_gracz->multiplier = 1;

        if (gracze == NULL) {
            gracze = nowy_gracz;
            lista = nowy_gracz;
            nowy_gracz->next = nowy_gracz;
        }
        else {
            gracze->next = nowy_gracz;
            nowy_gracz->next = lista;
            gracze = nowy_gracz;
        }
    }
    printf("Podaj liczb� pyta� na gracza 6, 9, 12, 15 lub 18\n");
    do {
        printf("Wybierz spo�r�d 6, 9, 12, 15, 18: ");
        if (scanf_s("%u", &no_pytan) != 1 || getchar() != '\n' || (no_pytan != 6 && no_pytan != 9 && no_pytan != 12 && no_pytan != 15 && no_pytan != 18)) {
            printf("Nieprawid�owy wyb�r. Spr�buj ponownie.\n");
            while (getchar() != '\n'); // Wyczy�� bufor wej�cia
        }
    } while (no_pytan != 6 && no_pytan != 9 && no_pytan != 12 && no_pytan != 15 && no_pytan != 18);

    system("cls");
    Gracz* current_player = lista;
    Pytanie* latwe = NULL;
    Pytanie* srednie = NULL;
    Pytanie* trudne = NULL;

    latwe = dodaj_pytanie(latwe, plik_latwe);
    srednie = dodaj_pytanie(srednie, plik_srednie);
    trudne = dodaj_pytanie(trudne, plik_trudne);

    int tryb = wybierz_tryb(); // Wyb�r trybu gry

    system("cls");

    pokaz_pytania(current_player, latwe, no_gracze, wybor, no_pytan, tryb);
    pokaz_pytania(current_player, srednie, no_gracze, wybor, no_pytan, tryb);
    pokaz_pytania(current_player, trudne, no_gracze, wybor, no_pytan, tryb);
    pokaz_wyniki(current_player, lista, no_gracze, wybor);

    Gracz* temp = lista;
    do {
        current_player = temp->next;
        free(temp);
        temp = current_player;
    } while (current_player != lista);

    usun_liste_pytan(latwe);
    usun_liste_pytan(srednie);
    usun_liste_pytan(trudne);
}

int main() {
    setlocale(LC_ALL, "Polish");
    srand(time(NULL));
    while (1)
    {
        int wybor = 2;
        printf("\t\t\tEkran G��wny!\n");
        printf("\t\t\tWybierz: \n\t\t1. aby rozpocz�� gr�, \n\t\t2. aby zobaczy� najlepsze wyniki, \n\t\t3. aby doda� pytania,\n\t\t4. aby zako�czy�.\n");
        int choice = 0;
        choice = wybierz_opcje(wybor);
        switch (choice)
        {
        case 1: // gra
        {
            system("cls");
            wybor = 1;
            printf("Wybierz kategori� pyta�:\n1. WIEDZA OG�LNA\n2. HISTORIA\n3. GEOGRAFIA\n4. SPORT\n5. GRY\n6. NAUKA I TECHNOLOGIA\n7. PRZYRODA\n8. MOTORYZACJA\n9. KINO\n10. POZOSTA�E\n\n11. Wyjd�\n");
            choice = wybierz_opcje(wybor);
            int no_gracze = 0;
            unsigned int no_pytan = 0;
            switch (choice)
            {
            case 1: // WIEDZA OGOLNA 1
            {
                system("cls");
                printf("Wybra�e� kategori� WIEDZA OG�LNA!\n\n"); // pliki 1
                char* plik_latwe = "pytania/pytania1_latwe.txt";
                char* plik_srednie = "pytania/pytania1_srednie.txt";
                char* plik_trudne = "pytania/pytania1_trudne.txt";
                printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                getch();
                system("cls");
                gra(no_pytan, wybor, no_gracze, plik_latwe, plik_srednie, plik_trudne);
                break;
            }
            case 2: // HISTORIA 2 
            {
                system("cls");
                printf("Wybra�e� kategori� HISTORIA!\n\n"); // pliki 2
                char* plik_latwe = "pytania/pytania2_latwe.txt";
                char* plik_srednie = "pytania/pytania2_srednie.txt";
                char* plik_trudne = "pytania/pytania2_trudne.txt";
                printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                getch();
                system("cls");
                gra(no_pytan, wybor, no_gracze, plik_latwe, plik_srednie, plik_trudne);
                break;
            }
            case 3: // GEOGRAFIA 3
            {
                system("cls");
                printf("Wybra�e� kategori� GEOGRAFIA!\n\n"); // pliki 3
                char* plik_latwe = "pytania/pytania3_latwe.txt";
                char* plik_srednie = "pytania/pytania3_srednie.txt";
                char* plik_trudne = "pytania/pytania3_trudne.txt";
                printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                getch();
                system("cls");
                gra(no_pytan, wybor, no_gracze, plik_latwe, plik_srednie, plik_trudne);
                break;
            }
            case 4: // SPORT 4
            {
                system("cls");
                printf("Wybra�e� kategori� SPORT!\n\n"); // pliki 4
                char* plik_latwe = "pytania/pytania4_latwe.txt";
                char* plik_srednie = "pytania/pytania4_srednie.txt";
                char* plik_trudne = "pytania/pytania4_trudne.txt";
                printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                getch();
                system("cls");
                gra(no_pytan, wybor, no_gracze, plik_latwe, plik_srednie, plik_trudne);
                break;
            }
            case 5: // GRY
            {
                system("cls");
                printf("Wybra�e� kategori� GRY!\n\n"); // pliki 5
                char* plik_latwe = "pytania/pytania5_latwe.txt";
                char* plik_srednie = "pytania/pytania5_srednie.txt";
                char* plik_trudne = "pytania/pytania5_trudne.txt";
                printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                getch();
                system("cls");
                gra(no_pytan, wybor, no_gracze, plik_latwe, plik_srednie, plik_trudne);
                break;
            }
            case 6: // NAUKA I TECHNOLOGIA
            {
                system("cls");
                printf("Wybra�e� kategori� NAUKA I TECHNOLOGIA!\n\n"); // pliki 6
                char* plik_latwe = "pytania/pytania6_latwe.txt";
                char* plik_srednie = "pytania/pytania6_srednie.txt";
                char* plik_trudne = "pytania/pytania6_trudne.txt";
                printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                getch();
                system("cls");
                gra(no_pytan, wybor, no_gracze, plik_latwe, plik_srednie, plik_trudne);
                break;
            }
            case 7: // PRZYRODA
            {
                system("cls");
                printf("Wybra�e� kategori� PRZYRODA!\n\n"); // pliki 7
                char* plik_latwe = "pytania/pytania7_latwe.txt";
                char* plik_srednie = "pytania/pytania7_srednie.txt";
                char* plik_trudne = "pytania/pytania7_trudne.txt";
                printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                getch();
                system("cls");
                gra(no_pytan, wybor, no_gracze, plik_latwe, plik_srednie, plik_trudne);
                break;
            }
            case 8: // MOTORYZACJA
            {
                system("cls");
                printf("Wybra�e� kategori� MOTORYZACJA!\n\n"); // pliki 8
                char* plik_latwe = "pytania/pytania8_latwe.txt";
                char* plik_srednie = "pytania/pytania8_srednie.txt";
                char* plik_trudne = "pytania/pytania8_trudne.txt";
                printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                getch();
                system("cls");
                gra(no_pytan, wybor, no_gracze, plik_latwe, plik_srednie, plik_trudne);
                break;
            }
            case 9: // KINO
            {
                system("cls");
                printf("Wybra�e� kategori� KINO!\n\n"); // pliki 9
                char* plik_latwe = "pytania/pytania9_latwe.txt";
                char* plik_srednie = "pytania/pytania9_srednie.txt";
                char* plik_trudne = "pytania/pytania9_trudne.txt";
                printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                getch();
                system("cls");
                gra(no_pytan, wybor, no_gracze, plik_latwe, plik_srednie, plik_trudne);
                break;
            }
            case 10: // POZOSTA�E
            {
                system("cls");
                printf("Wybra�e� kategori� POZOSTA�E!\n\n"); // pliki 10
                char* plik_latwe = "pytania/pytania10_latwe.txt";
                char* plik_srednie = "pytania/pytania10_srednie.txt";
                char* plik_trudne = "pytania/pytania10_trudne.txt";
                printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                getch();
                system("cls");
                gra(no_pytan, wybor, no_gracze, plik_latwe, plik_srednie, plik_trudne);
                break;
            }
            case 11:
            {
                system("cls");
                continue;
            }
            }
            break;
        }
        case 2: // najlepsze wyniki
        {
            FILE* file;
            errno_t err = fopen_s(&file, "najlepszy_wynik.txt", "r");
            if (err != 0) {
                printf("Nie mo�na otworzy� pliku.\n");
                break; // Przerwanie tylko aktualnego case, kontynuacja dzia�ania
            }

            char best_nick[MAX_NICK];
            double najlepszy_wynik;
            fscanf_s(file, "%lf %99s", &najlepszy_wynik, best_nick, MAX_NICK);
            fclose(file);

            printf("Najlepszy wynik: %.2lf, osiagn�� gracz o nicku: %s\n", najlepszy_wynik, best_nick);
            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
            getch();
            system("cls");
            break;
        }

        case 3: // dodawanie pyta�
        {
            system("cls");
            while (1) {
                printf("Wybierz kategori�, do kt�rej chcesz doda� pytanie:\n1. WIEDZA OG�LNA\n2. HISTORIA\n3. GEOGRAFIA\n4. SPORT\n5. GRY\n6. NAUKA I TECHNOLOGIA\n7. PRZYRODA\n8. MOTORYZACJA\n9. KINO\n10. POZOSTA�E\n\n11. Wyjd�\n");
                wybor = 1;
                choice = wybierz_opcje(wybor);
                switch (choice) {
                case 1:
                    system("cls");
                    while (1) {
                        printf("Wybierz zestaw trudno�ci pyta�, do kt�rego chcesz doda� pytanie:\n1. �ATWY\n2. �REDNI\n3. TRUDNE\n\n4. Wyjd�\n");
                        wybor = 2;
                        choice = wybierz_opcje(wybor);
                        switch (choice) {
                        case 1:
                            add_question_to_file("pytania/pytania1_latwe.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 2:
                            add_question_to_file("pytania/pytania1_srednie.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 3:
                            add_question_to_file("pytania/pytania1_trudne.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 4:
                            system("cls");
                            break;
                        default:
                            printf("Nieprawidlowy poziomu trudnosci.\n");
                            continue;
                        }
                        break;
                    }
                    continue;
                case 2:
                    system("cls");
                    while (1) {
                        printf("Wybierz zestaw trudno�ci pyta�, do kt�rego chcesz doda� pytanie:\n1. �ATWY\n2. �REDNI\n3. TRUDNE\n\n4. Wyjd�\n");
                        wybor = 2;
                        choice = wybierz_opcje(wybor);
                        switch (choice) {
                        case 1:
                            add_question_to_file("pytania/pytania2_latwe.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 2:
                            add_question_to_file("pytania/pytania2_srednie.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 3:
                            add_question_to_file("pytania/pytania2_trudne.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 4:
                            system("cls");
                            break;
                        default:
                            printf("Nieprawidlowy poziomu trudnosci.\n");
                            continue;
                        }
                        break;
                    }
                    continue;
                case 3:
                    system("cls");
                    while (1) {
                        printf("Wybierz zestaw trudno�ci pyta�, do kt�rego chcesz doda� pytanie:\n1. �ATWY\n2. �REDNI\n3. TRUDNE\n\n4. Wyjd�\n");
                        wybor = 2;
                        choice = wybierz_opcje(wybor);
                        switch (choice) {
                        case 1:
                            add_question_to_file("pytania/pytania3_latwe.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 2:
                            add_question_to_file("pytania/pytania3_srednie.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 3:
                            add_question_to_file("pytania/pytania3_trudne.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 4:
                            system("cls");
                            break;
                        default:
                            printf("Nieprawidlowy poziomu trudnosci.\n");
                            continue;
                        }
                        break;
                    }
                    continue;
                case 4:
                    system("cls");
                    while (1) {
                        printf("Wybierz zestaw trudno�ci pyta�, do kt�rego chcesz doda� pytanie:\n1. �ATWY\n2. �REDNI\n3. TRUDNE\n\n4. Wyjd�\n");
                        wybor = 2;
                        choice = wybierz_opcje(wybor);
                        switch (choice) {
                        case 1:
                            add_question_to_file("pytania/pytania4_latwe.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 2:
                            add_question_to_file("pytania/pytania4_srednie.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 3:
                            add_question_to_file("pytania/pytania4_trudne.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 4:
                            system("cls");
                            break;
                        default:
                            printf("Nieprawidlowy poziomu trudnosci.\n");
                            continue;
                        }
                        break;
                    }
                    continue;
                case 5:
                    system("cls");
                    while (1) {
                        printf("Wybierz zestaw trudno�ci pyta�, do kt�rego chcesz doda� pytanie:\n1. �ATWY\n2. �REDNI\n3. TRUDNE\n\n4. Wyjd�\n");
                        wybor = 2;
                        choice = wybierz_opcje(wybor);
                        switch (choice) {
                        case 1:
                            add_question_to_file("pytania/pytania5_latwe.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 2:
                            add_question_to_file("pytania/pytania5_srednie.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 3:
                            add_question_to_file("pytania/pytania5_trudne.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 4:
                            system("cls");
                            break;
                        default:
                            printf("Nieprawidlowy poziomu trudnosci.\n");
                            continue;
                        }
                        break;
                    }
                    continue;
                case 6:
                    system("cls");
                    while (1) {
                        printf("Wybierz zestaw trudno�ci pyta�, do kt�rego chcesz doda� pytanie:\n1. �ATWY\n2. �REDNI\n3. TRUDNE\n\n4. Wyjd�\n");
                        wybor = 2;
                        choice = wybierz_opcje(wybor);
                        switch (choice) {
                        case 1:
                            add_question_to_file("pytania/pytania6_latwe.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 2:
                            add_question_to_file("pytania/pytania6_srednie.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 3:
                            add_question_to_file("pytania/pytania6_trudne.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 4:
                            system("cls");
                            break;
                        default:
                            printf("Nieprawidlowy poziomu trudnosci.\n");
                            continue;
                        }
                        break;
                    }
                    continue;
                case 7:
                    system("cls");
                    while (1) {
                        printf("Wybierz zestaw trudno�ci pyta�, do kt�rego chcesz doda� pytanie:\n1. �ATWY\n2. �REDNI\n3. TRUDNE\n\n4. Wyjd�\n");
                        wybor = 2;
                        choice = wybierz_opcje(wybor);
                        switch (choice) {
                        case 1:
                            add_question_to_file("pytania/pytania7_latwe.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 2:
                            add_question_to_file("pytania/pytania7_srednie.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 3:
                            add_question_to_file("pytania/pytania7_trudne.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 4:
                            system("cls");
                            break;
                        default:
                            printf("Nieprawidlowy poziomu trudnosci.\n");
                            continue;
                        }
                        break;
                    }
                    continue;
                case 8:
                    system("cls");
                    while (1) {
                        printf("Wybierz zestaw trudno�ci pyta�, do kt�rego chcesz doda� pytanie:\n1. �ATWY\n2. �REDNI\n3. TRUDNE\n\n4. Wyjd�\n");
                        wybor = 2;
                        choice = wybierz_opcje(wybor);
                        switch (choice) {
                        case 1:
                            add_question_to_file("pytania/pytania8_latwe.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 2:
                            add_question_to_file("pytania/pytania8_srednie.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 3:
                            add_question_to_file("pytania/pytania8_trudne.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 4:
                            system("cls");
                            break;
                        default:
                            printf("Nieprawidlowy poziomu trudnosci.\n");
                            continue;
                        }
                        break;
                    }
                    continue;
                case 9:
                    system("cls");
                    while (1) {
                        printf("Wybierz zestaw trudno�ci pyta�, do kt�rego chcesz doda� pytanie:\n1. �ATWY\n2. �REDNI\n3. TRUDNE\n\n4. Wyjd�\n");
                        wybor = 2;
                        choice = wybierz_opcje(wybor);
                        switch (choice) {
                        case 1:
                            add_question_to_file("pytania/pytania9_latwe.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 2:
                            add_question_to_file("pytania/pytania9_srednie.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 3:
                            add_question_to_file("pytania/pytania9_trudne.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 4:
                            system("cls");
                            break;
                        default:
                            printf("Nieprawidlowy poziomu trudnosci.\n");
                            continue;
                        }
                        break;
                    }
                    continue;
                case 10:
                    system("cls");
                    while (1) {
                        printf("Wybierz zestaw trudno�ci pyta�, do kt�rego chcesz doda� pytanie:\n1. �ATWY\n2. �REDNI\n3. TRUDNE\n\n4. Wyjd�\n");
                        wybor = 2;
                        choice = wybierz_opcje(wybor);
                        switch (choice) {
                        case 1:
                            add_question_to_file("pytania/pytania10_latwe.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 2:
                            add_question_to_file("pytania/pytania10_srednie.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 3:
                            add_question_to_file("pytania/pytania10_trudne.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naci�nij DOWOLNY KLAWISZ, by przej�� dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 4:
                            system("cls");
                            break;
                        default:
                            printf("Nieprawidlowy poziomu trudnosci.\n");
                            continue;
                        }
                        break;
                    }
                    continue;
                case 11:
                    system("cls");
                    break;

                default:
                    printf("Nieprawid�owy wyb�r kategorii.\n");
                    continue;
                }
                break;
            }
            continue;
        }

        case 4: // KONIEC
        {
            printf("Koniec gry :(\n\n\n");
            exit(0);
        }

        default:
        {
            printf("Nieprawid�owy wyb�r.\n");
            continue;
        }
        }
    }
    return 0;
}