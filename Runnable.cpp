#include<iostream>
using namespace std;

/*
Potrebno je kreirati aplikaciju za dijeljenje znanja putem razmjene članaka među korisnicima.

Izdvojene su sljedeće funkcionalnosti:
- Administrator sistema je zadužen za upravljanje korisničkim nalozima (Ime, Prezime, Email, DatumRegistracije, KorisnickoIme, Lozinka).
- Svaki članak (Naslov, Sadrzaj, Datum, Satnica, BrojPregleda) može sadržavati više tagova, ali pripada samo jednoj oblasti.
- Članke mogu dodavati svi registrovani korisnici.
- Korisnici aplikacije također mogu ostaviti komentar (Tekst, Datum, Popularnost) na određeni članak.
*/

enum TipKorisnika { Administrator, Guest };

class Vrijeme {
	int _sati;
	int _minute;
	int _sekunde;
public:
	Vrijeme(int sati = 0, int minute = 0, int sekunde = 0) {
		_sati = sati;
		_minute = minute;
		_sekunde = sekunde;
	}
	void Info(bool puniFormat = true) {
		cout << _sati << ":" << _minute;
		if (puniFormat)
			cout << ":" << _sekunde;
		cout << endl;
	}
	Vrijeme Add(Vrijeme zaDodati) {
		Vrijeme novoVrijeme(this->_sati, this->_minute, this->_sekunde);
		novoVrijeme._sekunde += zaDodati._sekunde;
		while (novoVrijeme._sekunde >= 60) {
			novoVrijeme._sekunde -= 60;
			novoVrijeme._minute++;
		}
		novoVrijeme._minute += zaDodati._minute;
		while (novoVrijeme._minute >= 60) {
			novoVrijeme._minute -= 60;
			novoVrijeme._sati++;
		}
		return novoVrijeme;
	}
	int convertToSec(Vrijeme convertThis) {
		return convertThis._sekunde + convertThis._minute * 60 + convertThis._sati * 3600;
	}
	int CompareTo(Vrijeme checkThis) {
		int paramSec = convertToSec(checkThis);
		int thisSec = convertToSec(*this);
		if (thisSec == paramSec)
			return 0;
		if (thisSec < paramSec)
			return 1;
		return -1;
	}
};
class Datum {
	int _dan;
	int _mjesec;
	int _godina;
public:
	Datum(int dan = 0, int mjesec = 0, int godina = 0) {
		_dan = dan; _mjesec = mjesec; _godina = godina;
	}
	void Info() {
		cout << _dan << "." << _mjesec << "." << _godina << ".";
	}
};
class Korisnik
{
public:
	char _ime[30];
	char _korisnickoIme[20];
	char* _lozinka;
	TipKorisnika _tipKorisnika;
	Korisnik(char userName[20], char * password, TipKorisnika userRole = Guest, char ime[30] = "noName") {
		strcpy_s(_ime, 30, ime);
		strncpy_s(_korisnickoIme, 20, userName, _TRUNCATE);
		_lozinka = new char[strlen(password) + 1];
		strncpy_s(_lozinka, strlen(password) + 1, password, _TRUNCATE);
		_tipKorisnika = userRole;
	}
	~Korisnik() {
		delete[] _lozinka;
		_lozinka = nullptr;
	}
	void Info() {
		_sleep(1000);
		system("cls");
		cout << "\t :: USER INFO :: " << endl;
		cout << "Ime:\t\t " << _ime << endl;
		cout << "Username:\t " << _korisnickoIme << endl;
		cout << "Password:\t " << _lozinka << endl;
		cout << "Tip korisnika:\t " << ((int(_tipKorisnika)) ? "Guest" : "Administrator") << endl;
		cout << "\t :: END OF PRINT :: " << endl;
	}
	void shortInfo() {
		cout << _ime << " (" << _korisnickoIme << ") [" << ((int(_tipKorisnika)) ? "Guest" : "Administrator") << "]" << endl;
	}
};
class Komentar
{
	char* _tekst;
	Datum _datum;
	Vrijeme _satnica;
	int _popularnost;
	Korisnik * _autor;
public:
	Komentar(char * userComment, Datum date, Vrijeme timestamp, Korisnik& author, int popularity = 0) {
		_tekst = new char[strlen(userComment) + 1];
		strncpy_s(_tekst, strlen(userComment) + 1, userComment, _TRUNCATE);
		_datum = date; _satnica = timestamp; _popularnost = popularity;
		_autor = new Korisnik(author._korisnickoIme, author._lozinka, author._tipKorisnika, author._ime);
	}
	~Komentar() {
		delete[] _tekst;
		_tekst = nullptr;
	}
	void Info() {
		system("cls"); _sleep(1000);
		_autor->shortInfo();
		cout << "KOMENTAR: " << endl << "\t" << _tekst << endl;
		cout << "Datum: "; _datum.Info(); cout << " "; _satnica.Info();
		cout << "\tPopularnost: " << _popularnost << endl;
	}
	void changePop(int newPopVal) {
		_popularnost = newPopVal;
	}
};
class Clanak {
	char _naslov[150];
	char* _sadrzaj;
	Datum _datum;
	Vrijeme _satnica;
	int _brojPregleda;
	char* _tagovi[10];
	char _oblast[100];
	Korisnik* _autor;
	Komentar* _komentari;
public:
	Clanak(char header[150], char * articleCont, Datum date, Vrijeme timestamp, char category[100], 
		Korisnik &author, Komentar &comment, char) {
		strncpy_s(_naslov, 150, header, _TRUNCATE);
	}
	//Funkciju za dodavanje tagova za članak

	/*Funkciju za promjenu sadržaja i vremena promjene članka. Kao verifikaciju dozvole potrebno 
	je proslijediti korisničko ime autora članka.
	Samo kreator članka ima permisije da mijenja njegov sadržaj.
	*/

	//Funkciju za dodavanje komentara

	//Funkciju Info

};

int main()
{
	Vrijeme trenutno(10, 40, 12);
	Vrijeme custom(1, 20, 23);
	trenutno.Info();
	Vrijeme novo = trenutno.Add(custom);
	novo.Info();
	cout << "Rezultat poredjenja: " << novo.CompareTo(trenutno) << endl;
	Korisnik alem("bosco", "superTajnaLozinka");
	alem.Info();
	Datum danas(20, 10, 2017);
	Komentar noviComm("Odlicno", danas, trenutno, alem);
	noviComm.Info();
	return 0;
}


