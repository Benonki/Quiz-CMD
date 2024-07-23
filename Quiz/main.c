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
 * @param gracze pole, które ma byæ dodane
 * @param lista cykliczna z graczami
 *
 * @return Listê cykliczn¹ z dodanym graczem
 *
 * Funkcja dodaj_gracza_do_listy() sprawdza, czy lista cykliczna z graczami jest pusta. Jeœli lista jest pusta (NULL), to ustawiamy gracza jako jedyny element listy.
 * Gracz wskazuje na sam siebie, poniewa¿ jest jedynym elementem listy.
 * Funkcja szuka ostatniego elementu w liœcie, przechodz¹c przez kolejne elementy a¿ do momentu,
 * gdy "next" elementu nie wskazuje na pocz¹tek listy (czyli gracze).
 * Po znalezieniu ostatniego elementu, ustawiamy jego wskaŸnik "next" na nowo dodanego gracza.
 * Ustawiamy wskaŸnik "next" nowo dodanego gracza na pocz¹tek listy.
 * Zwracamy pocz¹tek listy (pierwszy element).
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
 * @param gracz, który ma byæ usuniêty
 *
 * Funkcja usun_gracza() sprawdza, czy lista jest pusta. Jeœli tak, to nie ma ¿adnego gracza do usuniêcia, wiêc funkcja koñczy siê.
 * Jeœli pierwszy element listy (*lista) jest równy usuniêtemu graczowi, to mamy do czynienia z usuwaniem pierwszego elementu.
 * Wtedy znajdujemy ostatni element listy, przemieszczaj¹c siê przez kolejne elementy, a¿ wskaŸnik "next" ostatniego elementu wskazuje na pierwszy element listy (*lista).
 * Jeœli ostatni element równie¿ wskazuje na pierwszy element, to oznacza, ¿e lista zawiera³a tylko jeden element, i po usuniêciu tego elementu lista staje siê pusta.
 * W przeciwnym przypadku przesuwamy wskaŸnik *lista na drugi element, a wskaŸnik "next" ostatniego elementu aktualizujemy, aby wskazywa³ na nowy pierwszy element.
 * Jeœli pierwszy element listy (*lista) nie jest równy usuniêtemu graczowi, to musimy przeszukaæ listê, aby znaleŸæ poprzednika usuwanego elementu.
 * Przesuwamy siê przez kolejne elementy, a¿ wskaŸnik "next" obecnego elementu wskazuje na *lista (czyli dojedziemy do koñca listy) lub wskaŸnik "next" obecnego elementu jest równy
 * usuniêtemu graczowi. Jeœli znajdziemy poprzednika, to aktualizujemy jego wskaŸnik "next", aby omija³ usuwanego gracza.
 * Na koñcu, po usuniêciu gracza z listy, zwalniamy pamiêæ zajmowan¹ przez usuniêtego gracza, u¿ywaj¹c funkcji free(usuniety).
 */
void usun_gracza(Gracz** lista, Gracz* usuniety) {
    if (*lista == NULL) {
        return;  // Lista jest pusta, nie ma nic do usuniêcia
    }

    if (*lista == usuniety) {
        // Usuñ pierwszy element z listy
        Gracz* last_player = (*lista)->next;
        while (last_player->next != *lista) {
            last_player = last_player->next;
        }
        if (last_player == *lista) {
            *lista = NULL;  // Lista zawiera³a tylko jeden element
        }
        else {
            *lista = (*lista)->next;
            last_player->next = *lista;
        }
    }
    else {
        // Przeszukaj listê, aby znaleŸæ poprzednik usuwanego elementu
        Gracz* obecne = *lista;
        while (obecne->next != *lista && obecne->next != usuniety) {
            obecne = obecne->next;
        }
        if (obecne->next == usuniety) {
            // Usuñ gracza z listy
            obecne->next = usuniety->next;
        }
    }
    free(usuniety);  // Zwolnij pamiêæ zajmowan¹ przez usuniêtego gracza
}

// LISTY DLA PYTAN
/**
 * @brief Dodaje pytanie do listy cyklicznej
 *
 * @param nowe_pytanie wskaŸnik do pytania, które ma byæ dodane do listy
 * @param lista wskaŸnik do listy pytani
 *
 * Funkcja dodaj_pytanie_do_listy() sprawdza, czy lista jest pusta. Jeœli tak, to nowe_pytanie staje siê jedynym elementem listy,
 * a jego wskaŸnik "next" wskazuje na samo siebie. Nastêpnie zwracamy wskaŸnik nowe_pytanie jako nowy pocz¹tek listy.
 * Jeœli lista nie jest pusta, przeszukujemy listê, aby znaleŸæ ostatni element. Przesuwamy siê przez kolejne elementy,
 * a¿ wskaŸnik "next" ostatniego elementu wskazuje na pocz¹tek listy (*lista). Nastêpnie ustawiamy wskaŸnik "next" ostatniego elementu
 * na nowe_pytanie, a wskaŸnik "next" nowe_pytanie ustawiamy na pocz¹tek listy (*lista). Na koñcu zwracamy wskaŸnik *lista jako nowy pocz¹tek listy.
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
 * @param lista wskaŸnik do listy pytani
 * @param nazwa_pliku nazwa pliku zawieraj¹cego pytania do dodania
 *
 * Funkcja dodaj_pytanie() otwiera plik o podanej nazwie i wczytuje kolejne linie jako pytania do dodania do listy.
 * Jeœli nie uda siê otworzyæ pliku, funkcja wypisuje odpowiedni komunikat i zwraca oryginaln¹ listê bez ¿adnych zmian.
 * W pêtli wczytuje linie pliku, a nastêpnie tworzy nowy element listy Pytanie i inicjalizuje go wartoœciami z wczytanej linii.
 * Wartoœæ pola "tresc" jest kopiowana bez pierwszego znaku '*', który jest pomijany.
 * Nastêpnie, w zale¿noœci od pierwszego znaku wczytanej linii, funkcja okreœla, która odpowiedŸ jest poprawna i ustawia odpowiednie
 * pola w strukturze Pytanie. Po utworzeniu nowego pytania, dodaje je do listy za pomoc¹ funkcji dodaj_pytanie_do_listy().
 * Po przetworzeniu wszystkich linii w pliku, funkcja zamyka plik i zwraca zaktualizowan¹ listê.
 */
Pytanie* dodaj_pytanie(Pytanie* lista, char* nazwa_pliku) {
    FILE* plik_pytan;
    if (fopen_s(&plik_pytan, nazwa_pliku, "r") != 0) {
        printf("B³¹d podczas otwierania pliku: %s\n", nazwa_pliku);
        return lista;  // Zwracamy oryginaln¹ listê, jeœli nie uda³o siê otworzyæ pliku
    }

    char linia[MAX_LEN];
    while (fgets(linia, MAX_LEN, plik_pytan) != NULL) {
        // Nowe pytanie
        Pytanie* nowe_pytanie = (Pytanie*)malloc(sizeof(Pytanie));
        strcpy_s(nowe_pytanie->tresc, sizeof(nowe_pytanie->tresc), linia);  // Pomijamy znak '*' na pocz¹tku
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
    return lista;  // Zwracamy zaktualizowan¹ listê
}

/**
 * @brief Wybiera losowe pytanie z listy cyklicznej
 *
 * @param lista_pytan wskaŸnik do listy pytañ
 * @return wskaŸnik do wybranego pytania
 *
 * Funkcja wylosuj_pytanie() inicjalizuje generator liczb losowych za pomoc¹ srand(time(NULL)).
 * Nastêpnie generuje losow¹ liczbê w zakresie od 0 do 49 (random_number).
 * Jeœli lista_pytan nie jest pusta, funkcja przechodzi przez listê pytañ losow¹ liczbê razy, przesuwaj¹c siê
 * przez kolejne elementy przy pomocy wskaŸnika "next".
 * Na koñcu zwraca wskaŸnik do wybranego pytania.
 */
Pytanie* wylosuj_pytanie(Pytanie* lista_pytan) {
    srand(time(NULL));
    // Losowanie liczby
    int random_number;
    // Przechodzenie przez listê pytañ wylosowan¹ liczbê razy
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
 * @brief Usuwa ca³¹ listê cykliczn¹ pytañ
 *
 * @param lista_pytan wskaŸnik do listy pytañ do usuniêcia
 *
 * Funkcja usun_liste_pytan() sprawdza, czy lista_pytan jest pusta. Jeœli tak, to nie ma ¿adnych pytañ do usuniêcia,
 * wiêc funkcja koñczy siê. W przeciwnym przypadku, funkcja przechodzi przez listê pytañ, zaczynaj¹c od wskaŸnika lista_pytan,
 * i zwalnia pamiêæ zajmowan¹ przez ka¿de pytanie. W ka¿dym kroku pêtli, funkcja zachowuje referencjê do nastêpnego pytania
 * (nastepne_pytanie), zwalnia pamiêæ aktualnego pytania (aktualne_pytanie), a nastêpnie przesuwa wskaŸnik na nastêpne pytanie.
 * Pêtla wykonuje siê, dopóki aktualne_pytanie nie jest równe lista_pytan, co oznacza, ¿e przeszlismy przez ca³¹ listê.
 * Na koniec, opcjonalnie mo¿na ustawiæ wskaŸnik lista_pytan na NULL, aby jawnie wskazaæ, ¿e lista jest pusta.
 */
void usun_liste_pytan(Pytanie* lista_pytan) {
    if (lista_pytan == NULL) {
        return;  // Lista jest pusta, nie ma nic do usuniêcia
    }

    Pytanie* aktualne_pytanie = lista_pytan;
    Pytanie* nastepne_pytanie;

    do {
        nastepne_pytanie = aktualne_pytanie->next;  // Zachowujemy referencjê do nastêpnego pytania
        free(aktualne_pytanie);  // Zwolnienie pamiêci aktualnego pytania
        aktualne_pytanie = nastepne_pytanie;  // Przesuniêcie wskaŸnika na nastêpne pytanie
    } while (aktualne_pytanie != lista_pytan);

    lista_pytan = NULL;  // Ustawienie wskaŸnika na listê pytañ na NULL (opcjonalne)
}

/**
 * @brief Usuwa pytanie z listy cyklicznej
 *
 * @param lista_pytan wskaŸnik do listy pytañ
 * @param pytanie_usuniete wskaŸnik do pytania, które ma byæ usuniête
 *
 * Funkcja usun_pytanie() sprawdza, czy lista_pytan jest pusta. Jeœli tak, to nie ma nic do usuniêcia, wiêc funkcja koñczy siê.
 * Jeœli lista_pytan wskazuje na pytanie_usuniete, to mamy do czynienia z usuwaniem pierwszego elementu.
 * W takim przypadku ustawiamy wskaŸnik lista_pytan na nastêpny element, aby usun¹æ pierwszy element z listy.
 * Jeœli lista_pytan nie wskazuje na pytanie_usuniete, musimy przeszukaæ listê, aby znaleŸæ poprzednika pytanie_usuniete.
 * Przechodzimy przez kolejne elementy, a¿ wskaŸnik "next" obecnego elementu wskazuje na pytanie_usuniete lub osi¹gniemy koniec listy.
 * Jeœli znajdziemy poprzednika, to aktualizujemy jego wskaŸnik "next", aby omija³ pytanie_usuniete.
 * Na koñcu, po usuniêciu pytania z listy, zwalniamy pamiêæ zajmowan¹ przez pytanie_usuniete, u¿ywaj¹c funkcji free(pytanie_usuniete).
 */
void usun_pytanie(Pytanie* lista_pytan, Pytanie* pytanie_usuniete) {
    if (lista_pytan == NULL) {
        return;  // Lista jest pusta, nie ma nic do usuniêcia
    }
    if (lista_pytan == pytanie_usuniete) {
        // Usuñ pierwszy element z listy
        lista_pytan = lista_pytan->next;
    }
    else {
        // Przeszukaj listê, aby znaleŸæ poprzednik usuwanego elementu
        Pytanie* obecne = lista_pytan;
        while (obecne->next != NULL && obecne->next != pytanie_usuniete) {
            obecne = obecne->next;
        }
        if (obecne->next == pytanie_usuniete) {
            // Usuñ pytanie z listy
            obecne->next = pytanie_usuniete->next;
        }
    }
    free(pytanie_usuniete);  // Zwolnij pamiêæ zajmowan¹ przez usuniête pytanie
}

/**
 * @brief Dodaje pytanie do pliku
 *
 * @param nazwa_pliku nazwa pliku, do którego ma byæ dodane pytanie
 *
 * Funkcja add_question_to_file() otwiera plik o podanej nazwie w trybie "a" (dopisywanie).
 * Jeœli nie uda siê otworzyæ pliku, funkcja wyœwietla komunikat o b³êdzie i koñczy dzia³anie.
 * Nastêpnie u¿ytkownik jest proszony o wprowadzenie treœci pytania i odpowiedzi.
 * Treœæ pytania jest wczytywana za pomoc¹ fgets() do tablicy tresc_pytania.
 * Odpowiedzi s¹ wprowadzane w pêtli, gdzie u¿ytkownik jest proszony o podanie odpowiedzi i s¹ one wczytywane do tablicy odpowiedzi.
 * Na koniec, treœæ pytania oraz odpowiedzi s¹ zapisywane do pliku za pomoc¹ fprintf().
 * Plik jest zamykany za pomoc¹ fclose().
 */
void add_question_to_file(char* nazwa_pliku) {
    FILE* plik_pytan;
    if (fopen_s(&plik_pytan, nazwa_pliku, "a") != 0) {
        printf("B³¹d podczas otwierania pliku: %s\n", nazwa_pliku);
        return;
    }

    char tresc_pytania[MAX_LEN];
    char odpowiedzi[MAX_ANSWER][MAX_LEN];

    printf("Podaj treœæ pytania: ");
    clearInputBuffer();
    fgets(tresc_pytania, MAX_LEN, stdin);

    printf("Podaj odpowiedzi (odpowiedŸ poprawna poprzedzona znakiem '*', np. *Warszawa):\n");
    for (int i = 0; i < MAX_ANSWER; i++) {
        printf("OdpowiedŸ %d: ", i + 1);
        fgets(odpowiedzi[i], MAX_LEN, stdin);
    }

    fprintf(plik_pytan, "%s", tresc_pytania);
    for (int i = 0; i < MAX_ANSWER; i++) {
        fprintf(plik_pytan, "%s", odpowiedzi[i]);
    }

    fclose(plik_pytan);
}

// GRA
// zwyk³a gra, bez mno¿nika, bez czasu
/**
 * @brief Funkcja odpowiada za rozgrywkê w grze
 *
 * @param player wskaŸnik do obiektu gracza
 * @param questions wskaŸnik do listy pytañ
 * @param wybor wartoœæ okreœlaj¹ca rodzaj wyboru
 *
 * Funkcja zagraj() inicjalizuje zmienn¹ answer, która przechowuje numer odpowiedzi gracza, oraz zmienn¹ score, która przechowuje
 * aktualny wynik gracza. Nastêpnie wywo³uje funkcjê wylosuj_pytanie(), aby wybraæ losowe pytanie z listy. Wyœwietla treœæ pytania
 * oraz mo¿liwe odpowiedzi. Gracz wybiera numer odpowiedzi, korzystaj¹c z funkcji wybierz_opcje(), a nastêpnie porównuje go z
 * indeksem poprawnej odpowiedzi w strukturze pytania. Jeœli odpowiedŸ jest poprawna, zwiêksza wynik gracza i wyœwietla informacjê
 * o poprawnej odpowiedzi. W przeciwnym przypadku wyœwietla informacjê o b³êdnej odpowiedzi. Na koñcu wywo³uje funkcjê usun_pytanie()
 * w celu usuniêcia wykorzystanego pytania z listy.
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
        printf("OdpowiedŸ poprawna!\nNaciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
    }
    else {
        player->multiplier = 1;
        printf("OdpowiedŸ b³êdna!\nNaciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
    }
    usun_pytanie(questions, current_question);
}

// gra z mno¿nikiem, bez czasu
/**
 * @brief Funkcja odpowiedzialna za rozgrywkê w trybie mno¿nika
 *
 * @param player wskaŸnik do struktury gracza
 * @param questions wskaŸnik do listy pytañ
 * @param wybor wybór opcji
 *
 * Funkcja zagraj_mnoznik() rozpoczyna grê w trybie mno¿nika dla danego gracza.
 * Losuje jedno pytanie z listy pytañ, u¿ywaj¹c funkcji wylosuj_pytanie().
 * Nastêpnie wyœwietla treœæ pytania oraz odpowiedzi dla gracza.
 * Gracz podaje numer odpowiedzi poprzez funkcjê wybierz_opcje(wybor).
 * Jeœli udzieli poprawnej odpowiedzi, zwiêksza swoje punkty o wartoœæ mno¿nika (player->multiplier),
 * a nastêpnie zwiêksza mno¿nik o 1 (jeœli mno¿nik jest mniejszy od 3).
 * Jeœli udzieli b³êdnej odpowiedzi, mno¿nik zostaje zresetowany do wartoœci 1.
 * Na koñcu usuwa wykorzystane pytanie z listy pytañ, u¿ywaj¹c funkcji usun_pytanie(&questions, current_question).
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
        printf("OdpowiedŸ poprawna!\nNaciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
    }
    else {
        player->multiplier = 1;
        printf("OdpowiedŸ b³êdna!\nNaciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
    }
    usun_pytanie(questions, current_question);
}

// gra z mno¿nikiem i czasem
/**
 * @brief Funkcja realizuj¹ca grê z ograniczonym czasem na udzielenie odpowiedzi na pytanie
 *
 * @param player wskaŸnik do obiektu gracza
 * @param questions wskaŸnik do listy pytañ
 * @param wybor wybór opcji w grze
 *
 * Funkcja zagraj_czas() przygotowuje pytanie do wyœwietlenia poprzez wylosowanie pytania z listy
 * i inicjalizacjê czasu pocz¹tkowego. Nastêpnie wyœwietla treœæ pytania oraz mo¿liwe odpowiedzi.
 * Gracz ma 10 sekund na udzielenie odpowiedzi. Podczas oczekiwania na odpowiedŸ wyœwietla up³ywaj¹cy czas.
 * Jeœli gracz udzieli odpowiedzi przed up³ywem 10 sekund, sprawdza poprawnoœæ odpowiedzi i aktualizuje wynik i mno¿nik gracza.
 * Po zakoñczeniu pytania usuwa je z listy.
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

    time_t startTime = time(0); // Pocz¹tkowy czas dla pytania
    time_t lastDisplayedTime = startTime;
    int allowAnswer = 0; // Flaga, czy umo¿liwiono odpowiedŸ

    while (1) {
        time_t currentTime = time(0);
        double timeElapsed = difftime(currentTime, startTime);

        if (currentTime > lastDisplayedTime && timeElapsed < 10) {
            printf("%.0f... ", timeElapsed);
            fflush(stdout); // Wymuszenie natychmiastowego wyœwietlenia tekstu
            lastDisplayedTime = currentTime;
        }

        if (timeElapsed >= 10 && !allowAnswer) {
            player->multiplier = 1;
            printf("Minê³o 10 sekund.\n");
            break;
        }

        if (kbhit() && (timeElapsed < 10 || allowAnswer)) { // Sprawdzanie czy klawisz zosta³ naciœniêty
            answer = wybierz_opcje(wybor);
            time_t endTime = time(0); // Koñcowy czas dla pytania
            double timeTaken = difftime(endTime, startTime); // Czas w sekundach
            if (answer - 1 == current_question->poprawna_odpowiedz) {
                player->score += player->multiplier;

                // Obliczenie mno¿nika na podstawie czasu odpowiedzi
                if (timeTaken < 5) {
                    player->multiplier += 1;
                }
                else if (timeTaken >= 5 && timeTaken < 10) {
                    player->multiplier += 0.5;
                }
                printf("OdpowiedŸ poprawna!\n");
            }
            else {
                player->multiplier = 1;
                printf("OdpowiedŸ b³êdna!\n");
            }
            break;
        }

        if (timeElapsed >= 10 && !allowAnswer) {
            // Sprawdzanie czy up³ynê³o ju¿ 10 sekund, aby zakoñczyæ pytanie
            break;
        }

        // Czekaj 1 sekundê
        Sleep(1);
        fflush(stdout); // Wymuszenie natychmiastowego wyœwietlenia tekstu
    }

    printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
    usun_pytanie(questions, current_question);
}

/**
 * @brief Wyœwietla pytania dla graczy z listy cyklicznej
 *
 * @param player wskaŸnik do gracza, od którego rozpoczyna siê wyœwietlanie
 * @param lista wskaŸnik do listy pytañ
 * @param no_gracze liczba graczy
 * @param wybor wybór odpowiedzi przez gracza
 * @param no_pytan liczba wszystkich pytañ
 * @param tryb tryb gry (1 - standardowy, 2 - z mno¿nikiem, 3 - z ograniczonym czasem)
 *
 * Funkcja pokaz_pytania() wyœwietla pytania dla graczy z listy cyklicznej.
 * Przechodzi przez listê graczy, rozpoczynaj¹c od gracza wskazywanego przez parametr "player".
 * Dla ka¿dego gracza wyœwietla pytania i wywo³uje odpowiedni¹ funkcjê do gry w zale¿noœci od trybu.
 * Po zakoñczeniu gry dla ka¿dego pytania, przechodzi do nastêpnego gracza.
 * Po ka¿dym pytaniu oczekuje na naciœniêcie dowolnego klawisza przez u¿ytkownika i czyœci ekran.
 */
void pokaz_pytania(Gracz* player, Pytanie* lista, int no_gracze, int wybor, unsigned int no_pytan, int tryb)
{
    if (lista != NULL)
    {
        int no_q = (no_pytan / 3) * no_gracze;
        Gracz* current_player = player;
        for (int i = 0; i < no_q; i++)
        {
            printf("Gracz %s, wynik %.2lf, mno¿nik %.2lf\nPytanie %d: ", current_player->nickname, current_player->score, current_player->multiplier, i + 1);

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
        printf("B³¹d! Nie wczytano pliku.");
}

/**
 * @brief Wybiera opcjê z podanego zakresu
 *
 * @param wybor wartoœæ wyboru, która okreœla zakres opcji do wyboru
 * @return wybrana opcja
 *
 * Funkcja wybierz_opcje() przyjmuje wartoœæ wyboru (wybor) i w zale¿noœci od tego wyboru
 * ustala zakres opcji do wyboru. Nastêpnie pobiera liczbê od u¿ytkownika i sprawdza, czy
 * wprowadzona liczba mieœci siê w zakresie opcji. Jeœli tak, zwraca wybran¹ opcjê.
 * W przypadku niepoprawnego wprowadzenia liczby, wyœwietla b³¹d i prosi u¿ytkownika
 * o wprowadzenie poprawnej liczby. Funkcja kontynuuje pobieranie danych od u¿ytkownika,
 * dopóki nie zostanie wprowadzona poprawna liczba opcji.
 */
int wybierz_opcje(int wybor) {
    int choice = 0;
    int ile;
    int input = 0;
    do {
        if (wybor == 0) {
            ile = 2;
            printf("\nPodaj liczbê od 1 do %d:\n", ile);
            scanf_s("%d", &input);

            if (input >= 1 && input <= ile) {
                choice = input;
            }
            else {
                printf("\nB³¹d. WprowadŸ poprawn¹ liczbê od 1 do %d.\n", ile);
                clearInputBuffer(); // Wyczyœæ bufor wejœciowy
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
                printf("\nB³¹d. WprowadŸ poprawn¹ liczbê od 1 do %d.\n", ile);
                clearInputBuffer(); // Wyczyœæ bufor wejœciowy
            }
        }
        else if (wybor == 2) {
            ile = 4;
            printf("\nPodaj liczbê od 1 do %d:\n", ile);
            scanf_s("%d", &input);

            if (input >= 1 && input <= ile) {
                choice = input;
            }
            else {
                printf("\nB³¹d. WprowadŸ poprawn¹ liczbê od 1 do %d.\n", ile);
                clearInputBuffer(); // Wyczyœæ bufor wejœciowy
            }
        }
    } while (choice < 1 || choice > ile);

    return choice;
}

/**
 * @brief Zapisuje najlepszy wynik gracza do pliku
 *
 * @param player wskaŸnik do struktury Gracz
 *
 * Funkcja najlepszy_wynik() otwiera plik "najlepszy_wynik.txt" w trybie odczytu.
 * Jeœli plik nie istnieje, tworzy go w trybie zapisu.
 * Jeœli plik istnieje, odczytuje z niego dotychczasowy najlepszy wynik.
 * Jeœli wynik gracza nie jest lepszy od dotychczasowego najlepszego wyniku, funkcja koñczy siê.
 * W przeciwnym przypadku otwiera plik w trybie zapisu i zapisuje nowy najlepszy wynik oraz nazwê gracza.
 * Na koniec zamyka plik i wyœwietla informacjê o zapisaniu najlepszego wyniku.
 */
void najlepszy_wynik(Gracz* player) {
    FILE* file;
    char filename[] = "najlepszy_wynik.txt";
    int najlepszy_wynik = 0;

    // Otwarcie pliku w trybie do odczytu
    if (fopen_s(&file, filename, "r") != 0) {
        // Plik nie istnieje, wiêc tworzymy nowy
        if (fopen_s(&file, filename, "w") != 0) {
            printf("B³¹d podczas tworzenia pliku.\n");
            return;
        }
    }
    else {
        // Plik istnieje, wiêc odczytujemy najlepszy wynik
        fscanf_s(file, "%d", &najlepszy_wynik);
        fclose(file);

        // Sprawdzamy, czy wynik jest lepszy od ju¿ zapisanego
        if (player->score <= najlepszy_wynik) {
            printf("Twój wynik nie jest lepszy od najlepszego wyniku.\n");
            return;
        }

        // Otwarcie pliku w trybie do zapisu (nadpisanie poprzednich danych)
        if (fopen_s(&file, filename, "w") != 0) {
            printf("B³¹d podczas zapisywania do pliku.\n");
            return;
        }
    }

    // Zapisanie nowego najlepszego wyniku do pliku
    fprintf(file, "%.2lf ", player->score);
    fprintf(file, "%s\n", player->nickname);

    fclose(file);
    printf("Twój wynik zosta³ zapisany jako najlepszy wynik!\n");
}

/**
 * @brief Wybiera tryb gry
 *
 * @return numer wybranego trybu
 *
 * Funkcja wybierz_tryb() wyœwietla u¿ytkownikowi opcje wyboru trybu gry: NORMALNY, MNO¯NIK, MNO¯NIK+CZAS.
 * U¿ytkownik podaje numer trybu od 1 do 3, a funkcja sprawdza poprawnoœæ wprowadzonej wartoœci.
 * Jeœli podany numer jest spoza zakresu 1-3, u¿ytkownik jest proszony o ponowne wprowadzenie wartoœci.
 * Na koniec funkcja zwraca wybrany numer trybu.
 */
int wybierz_tryb()
{
    int mode;
    printf("Wybierz tryb gry:\n");
    printf("1. NORMALNY\n");
    printf("2. MNO¯NIK\n");
    printf("3. MNO¯NIK+CZAS\n");

    do {
        printf("Podaj numer trybu od 1 do 3: ");
        scanf_s("%d", &mode);
    } while (mode < 1 || mode > 3);

    return mode;
}

/**
 * @brief Wyœwietla wyniki z ostatniej rundy
 *
 * @param player wskaŸnik do aktualnego gracza
 * @param lista wskaŸnik do listy graczy
 * @param no_gracze liczba graczy
 *
 * Funkcja pokaz_wyniki() wyœwietla wyniki z ostatniej rundy.
 * Najpierw inicjalizuje zmienn¹ best na wartoœæ pocz¹tkow¹.
 * Nastêpnie przechodzi przez listê graczy, wyœwietlaj¹c nazwê gracza i jego wynik.
 * Jeœli wynik gracza jest wiêkszy od dotychczasowego najlepszego wyniku (best), aktualizuje wartoœæ best i resetuje flagê remisu.
 * Jeœli wynik gracza jest równy dotychczasowemu najlepszemu wynikowi (best), ustawia flagê remisu na 1.
 * Po przejœciu przez wszystkich graczy, sprawdza czy wyst¹pi³ remis.
 * Jeœli tak, wyœwietla odpowiedni komunikat.
 * Jeœli nie, przechodzi ponownie przez listê graczy, aby znaleŸæ gracza z najlepszym wynikiem.
 * Wyœwietla informacjê o zwyciêzcy i wywo³uje funkcjê najlepszy_wynik() dla tego gracza.
 * Na koñcu oczekuje na naciœniêcie dowolnego klawisza i czyœci ekran.
 */
void pokaz_wyniki(Gracz* player, Gracz* lista, int no_gracze)
{
    double best = 0; // Inicjalizacja best na pocz¹tkow¹ wartoœæ
    int isDraw = 0; // Flaga oznaczaj¹ca remis
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
        printf("\nRemis! Brak zwyciêzcy.\n");
    }
    else {
        // Ponownie przechodzimy przez listê, aby znaleŸæ gracza z najlepszym wynikiem
        player = lista;
        while (player->score != best) {
            player = player->next;
        }
        printf("\nGracz %s, zwyciê¿y³!\nGRATULACJE!\n", player->nickname);
        najlepszy_wynik(player);
    }

    getch();
    system("cls");
}

/**
 * @brief Rozpoczyna grê
 *
 * @param no_pytan liczba pytañ na gracza
 * @param wybor opcja wyboru
 * @param no_gracze liczba graczy
 * @param plik_latwe nazwa pliku z pytaniami ³atwymi
 * @param plik_srednie nazwa pliku z pytaniami œrednimi
 * @param plik_trudne nazwa pliku z pytaniami trudnymi
 *
 * Funkcja gra() inicjalizuje grê. Pocz¹tkowo pobiera liczbê graczy od u¿ytkownika i tworzy listê graczy.
 * Nastêpnie pobiera liczbê pytañ na gracza, przy czym u¿ytkownik musi wybraæ wartoœæ spoœród 6, 9, 12, 15 lub 18.
 * Tworzy listy pytañ dla ró¿nych poziomów trudnoœci i wybiera tryb gry.
 * Wyœwietla pytania dla ka¿dego gracza i na ka¿dy poziom trudnoœci.
 * Na koniec wyœwietla wyniki, usuwa listy graczy i pytañ, a nastêpnie koñczy grê.
 */
void gra(unsigned int no_pytan, int wybor, int no_gracze, char plik_latwe[], char plik_srednie[], char plik_trudne[])
{
    printf("Podaj liczbê graczy.\n");
    wybor = 2;
    no_gracze = wybierz_opcje(wybor);
    system("cls");

    Gracz* gracze = NULL;
    Gracz* lista = NULL;

    for (int i = 0; i < no_gracze; i++) {
        Gracz* nowy_gracz = (Gracz*)malloc(sizeof(Gracz));
        printf("Podaj imiê gracza %d: ", i + 1);
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
    printf("Podaj liczbê pytañ na gracza 6, 9, 12, 15 lub 18\n");
    do {
        printf("Wybierz spoœród 6, 9, 12, 15, 18: ");
        if (scanf_s("%u", &no_pytan) != 1 || getchar() != '\n' || (no_pytan != 6 && no_pytan != 9 && no_pytan != 12 && no_pytan != 15 && no_pytan != 18)) {
            printf("Nieprawid³owy wybór. Spróbuj ponownie.\n");
            while (getchar() != '\n'); // Wyczyœæ bufor wejœcia
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

    int tryb = wybierz_tryb(); // Wybór trybu gry

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
        printf("\t\t\tEkran G³ówny!\n");
        printf("\t\t\tWybierz: \n\t\t1. aby rozpocz¹æ grê, \n\t\t2. aby zobaczyæ najlepsze wyniki, \n\t\t3. aby dodaæ pytania,\n\t\t4. aby zakoñczyæ.\n");
        int choice = 0;
        choice = wybierz_opcje(wybor);
        switch (choice)
        {
        case 1: // gra
        {
            system("cls");
            wybor = 1;
            printf("Wybierz kategoriê pytañ:\n1. WIEDZA OGÓLNA\n2. HISTORIA\n3. GEOGRAFIA\n4. SPORT\n5. GRY\n6. NAUKA I TECHNOLOGIA\n7. PRZYRODA\n8. MOTORYZACJA\n9. KINO\n10. POZOSTA£E\n\n11. WyjdŸ\n");
            choice = wybierz_opcje(wybor);
            int no_gracze = 0;
            unsigned int no_pytan = 0;
            switch (choice)
            {
            case 1: // WIEDZA OGOLNA 1
            {
                system("cls");
                printf("Wybra³eœ kategoriê WIEDZA OGÓLNA!\n\n"); // pliki 1
                char* plik_latwe = "pytania/pytania1_latwe.txt";
                char* plik_srednie = "pytania/pytania1_srednie.txt";
                char* plik_trudne = "pytania/pytania1_trudne.txt";
                printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                getch();
                system("cls");
                gra(no_pytan, wybor, no_gracze, plik_latwe, plik_srednie, plik_trudne);
                break;
            }
            case 2: // HISTORIA 2 
            {
                system("cls");
                printf("Wybra³eœ kategoriê HISTORIA!\n\n"); // pliki 2
                char* plik_latwe = "pytania/pytania2_latwe.txt";
                char* plik_srednie = "pytania/pytania2_srednie.txt";
                char* plik_trudne = "pytania/pytania2_trudne.txt";
                printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                getch();
                system("cls");
                gra(no_pytan, wybor, no_gracze, plik_latwe, plik_srednie, plik_trudne);
                break;
            }
            case 3: // GEOGRAFIA 3
            {
                system("cls");
                printf("Wybra³eœ kategoriê GEOGRAFIA!\n\n"); // pliki 3
                char* plik_latwe = "pytania/pytania3_latwe.txt";
                char* plik_srednie = "pytania/pytania3_srednie.txt";
                char* plik_trudne = "pytania/pytania3_trudne.txt";
                printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                getch();
                system("cls");
                gra(no_pytan, wybor, no_gracze, plik_latwe, plik_srednie, plik_trudne);
                break;
            }
            case 4: // SPORT 4
            {
                system("cls");
                printf("Wybra³eœ kategoriê SPORT!\n\n"); // pliki 4
                char* plik_latwe = "pytania/pytania4_latwe.txt";
                char* plik_srednie = "pytania/pytania4_srednie.txt";
                char* plik_trudne = "pytania/pytania4_trudne.txt";
                printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                getch();
                system("cls");
                gra(no_pytan, wybor, no_gracze, plik_latwe, plik_srednie, plik_trudne);
                break;
            }
            case 5: // GRY
            {
                system("cls");
                printf("Wybra³eœ kategoriê GRY!\n\n"); // pliki 5
                char* plik_latwe = "pytania/pytania5_latwe.txt";
                char* plik_srednie = "pytania/pytania5_srednie.txt";
                char* plik_trudne = "pytania/pytania5_trudne.txt";
                printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                getch();
                system("cls");
                gra(no_pytan, wybor, no_gracze, plik_latwe, plik_srednie, plik_trudne);
                break;
            }
            case 6: // NAUKA I TECHNOLOGIA
            {
                system("cls");
                printf("Wybra³eœ kategoriê NAUKA I TECHNOLOGIA!\n\n"); // pliki 6
                char* plik_latwe = "pytania/pytania6_latwe.txt";
                char* plik_srednie = "pytania/pytania6_srednie.txt";
                char* plik_trudne = "pytania/pytania6_trudne.txt";
                printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                getch();
                system("cls");
                gra(no_pytan, wybor, no_gracze, plik_latwe, plik_srednie, plik_trudne);
                break;
            }
            case 7: // PRZYRODA
            {
                system("cls");
                printf("Wybra³eœ kategoriê PRZYRODA!\n\n"); // pliki 7
                char* plik_latwe = "pytania/pytania7_latwe.txt";
                char* plik_srednie = "pytania/pytania7_srednie.txt";
                char* plik_trudne = "pytania/pytania7_trudne.txt";
                printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                getch();
                system("cls");
                gra(no_pytan, wybor, no_gracze, plik_latwe, plik_srednie, plik_trudne);
                break;
            }
            case 8: // MOTORYZACJA
            {
                system("cls");
                printf("Wybra³eœ kategoriê MOTORYZACJA!\n\n"); // pliki 8
                char* plik_latwe = "pytania/pytania8_latwe.txt";
                char* plik_srednie = "pytania/pytania8_srednie.txt";
                char* plik_trudne = "pytania/pytania8_trudne.txt";
                printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                getch();
                system("cls");
                gra(no_pytan, wybor, no_gracze, plik_latwe, plik_srednie, plik_trudne);
                break;
            }
            case 9: // KINO
            {
                system("cls");
                printf("Wybra³eœ kategoriê KINO!\n\n"); // pliki 9
                char* plik_latwe = "pytania/pytania9_latwe.txt";
                char* plik_srednie = "pytania/pytania9_srednie.txt";
                char* plik_trudne = "pytania/pytania9_trudne.txt";
                printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                getch();
                system("cls");
                gra(no_pytan, wybor, no_gracze, plik_latwe, plik_srednie, plik_trudne);
                break;
            }
            case 10: // POZOSTA£E
            {
                system("cls");
                printf("Wybra³eœ kategoriê POZOSTA£E!\n\n"); // pliki 10
                char* plik_latwe = "pytania/pytania10_latwe.txt";
                char* plik_srednie = "pytania/pytania10_srednie.txt";
                char* plik_trudne = "pytania/pytania10_trudne.txt";
                printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
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
                printf("Nie mo¿na otworzyæ pliku.\n");
                break; // Przerwanie tylko aktualnego case, kontynuacja dzia³ania
            }

            char best_nick[MAX_NICK];
            double najlepszy_wynik;
            fscanf_s(file, "%lf %99s", &najlepszy_wynik, best_nick, MAX_NICK);
            fclose(file);

            printf("Najlepszy wynik: %.2lf, osiagn¹³ gracz o nicku: %s\n", najlepszy_wynik, best_nick);
            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
            getch();
            system("cls");
            break;
        }

        case 3: // dodawanie pytañ
        {
            system("cls");
            while (1) {
                printf("Wybierz kategoriê, do której chcesz dodaæ pytanie:\n1. WIEDZA OGÓLNA\n2. HISTORIA\n3. GEOGRAFIA\n4. SPORT\n5. GRY\n6. NAUKA I TECHNOLOGIA\n7. PRZYRODA\n8. MOTORYZACJA\n9. KINO\n10. POZOSTA£E\n\n11. WyjdŸ\n");
                wybor = 1;
                choice = wybierz_opcje(wybor);
                switch (choice) {
                case 1:
                    system("cls");
                    while (1) {
                        printf("Wybierz zestaw trudnoœci pytañ, do którego chcesz dodaæ pytanie:\n1. £ATWY\n2. ŒREDNI\n3. TRUDNE\n\n4. WyjdŸ\n");
                        wybor = 2;
                        choice = wybierz_opcje(wybor);
                        switch (choice) {
                        case 1:
                            add_question_to_file("pytania/pytania1_latwe.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 2:
                            add_question_to_file("pytania/pytania1_srednie.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 3:
                            add_question_to_file("pytania/pytania1_trudne.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
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
                        printf("Wybierz zestaw trudnoœci pytañ, do którego chcesz dodaæ pytanie:\n1. £ATWY\n2. ŒREDNI\n3. TRUDNE\n\n4. WyjdŸ\n");
                        wybor = 2;
                        choice = wybierz_opcje(wybor);
                        switch (choice) {
                        case 1:
                            add_question_to_file("pytania/pytania2_latwe.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 2:
                            add_question_to_file("pytania/pytania2_srednie.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 3:
                            add_question_to_file("pytania/pytania2_trudne.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
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
                        printf("Wybierz zestaw trudnoœci pytañ, do którego chcesz dodaæ pytanie:\n1. £ATWY\n2. ŒREDNI\n3. TRUDNE\n\n4. WyjdŸ\n");
                        wybor = 2;
                        choice = wybierz_opcje(wybor);
                        switch (choice) {
                        case 1:
                            add_question_to_file("pytania/pytania3_latwe.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 2:
                            add_question_to_file("pytania/pytania3_srednie.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 3:
                            add_question_to_file("pytania/pytania3_trudne.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
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
                        printf("Wybierz zestaw trudnoœci pytañ, do którego chcesz dodaæ pytanie:\n1. £ATWY\n2. ŒREDNI\n3. TRUDNE\n\n4. WyjdŸ\n");
                        wybor = 2;
                        choice = wybierz_opcje(wybor);
                        switch (choice) {
                        case 1:
                            add_question_to_file("pytania/pytania4_latwe.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 2:
                            add_question_to_file("pytania/pytania4_srednie.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 3:
                            add_question_to_file("pytania/pytania4_trudne.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
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
                        printf("Wybierz zestaw trudnoœci pytañ, do którego chcesz dodaæ pytanie:\n1. £ATWY\n2. ŒREDNI\n3. TRUDNE\n\n4. WyjdŸ\n");
                        wybor = 2;
                        choice = wybierz_opcje(wybor);
                        switch (choice) {
                        case 1:
                            add_question_to_file("pytania/pytania5_latwe.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 2:
                            add_question_to_file("pytania/pytania5_srednie.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 3:
                            add_question_to_file("pytania/pytania5_trudne.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
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
                        printf("Wybierz zestaw trudnoœci pytañ, do którego chcesz dodaæ pytanie:\n1. £ATWY\n2. ŒREDNI\n3. TRUDNE\n\n4. WyjdŸ\n");
                        wybor = 2;
                        choice = wybierz_opcje(wybor);
                        switch (choice) {
                        case 1:
                            add_question_to_file("pytania/pytania6_latwe.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 2:
                            add_question_to_file("pytania/pytania6_srednie.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 3:
                            add_question_to_file("pytania/pytania6_trudne.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
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
                        printf("Wybierz zestaw trudnoœci pytañ, do którego chcesz dodaæ pytanie:\n1. £ATWY\n2. ŒREDNI\n3. TRUDNE\n\n4. WyjdŸ\n");
                        wybor = 2;
                        choice = wybierz_opcje(wybor);
                        switch (choice) {
                        case 1:
                            add_question_to_file("pytania/pytania7_latwe.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 2:
                            add_question_to_file("pytania/pytania7_srednie.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 3:
                            add_question_to_file("pytania/pytania7_trudne.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
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
                        printf("Wybierz zestaw trudnoœci pytañ, do którego chcesz dodaæ pytanie:\n1. £ATWY\n2. ŒREDNI\n3. TRUDNE\n\n4. WyjdŸ\n");
                        wybor = 2;
                        choice = wybierz_opcje(wybor);
                        switch (choice) {
                        case 1:
                            add_question_to_file("pytania/pytania8_latwe.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 2:
                            add_question_to_file("pytania/pytania8_srednie.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 3:
                            add_question_to_file("pytania/pytania8_trudne.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
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
                        printf("Wybierz zestaw trudnoœci pytañ, do którego chcesz dodaæ pytanie:\n1. £ATWY\n2. ŒREDNI\n3. TRUDNE\n\n4. WyjdŸ\n");
                        wybor = 2;
                        choice = wybierz_opcje(wybor);
                        switch (choice) {
                        case 1:
                            add_question_to_file("pytania/pytania9_latwe.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 2:
                            add_question_to_file("pytania/pytania9_srednie.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 3:
                            add_question_to_file("pytania/pytania9_trudne.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
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
                        printf("Wybierz zestaw trudnoœci pytañ, do którego chcesz dodaæ pytanie:\n1. £ATWY\n2. ŒREDNI\n3. TRUDNE\n\n4. WyjdŸ\n");
                        wybor = 2;
                        choice = wybierz_opcje(wybor);
                        switch (choice) {
                        case 1:
                            add_question_to_file("pytania/pytania10_latwe.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 2:
                            add_question_to_file("pytania/pytania10_srednie.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
                            getch();
                            system("cls");
                            continue;
                        case 3:
                            add_question_to_file("pytania/pytania10_trudne.txt");
                            system("cls");
                            printf("Dodano pytanie!\n\n");
                            printf("Naciœnij DOWOLNY KLAWISZ, by przejœæ dalej\n");
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
                    printf("Nieprawid³owy wybór kategorii.\n");
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
            printf("Nieprawid³owy wybór.\n");
            continue;
        }
        }
    }
    return 0;
}