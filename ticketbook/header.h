#include<iostream>
using namespace std;
const int MAX_LANGUAGES = 5;
const int MAX_MOVIES = 10;
const int MAX_SHOWTIMES = 20;

class Language {
private:
    string name;
public:
    Language();
    void setname (string n){name=n;};
    string getName();
};
class Movie {
private:
    string name;
    Language language;
public:
    Movie();
    Movie(string n, Language lang);
    string getName();
    Language getLanguage();
    void getdetails();
};
class Showtime {
private:
    string time;
    Movie movie;
public:
    Showtime();
    Showtime(string t, Movie m);
    string getTime();
    Movie getMovie();
};
class Screen {
public:
    Showtime showtimes[MAX_SHOWTIMES];
    int numShowtimes;
    friend class Customer;

    Screen();
    static Screen& getInstance();
    void addShowtime(Showtime showtime);
    void displayLanguages();
    void displayMoviesByLanguage(string language);
    void displayMovies();
};
class User {
protected:
    string username;
    string password;
public:
    void setUsername(string name);
    void setPassword(string pass);
    virtual bool login(string name, string pass);
};
class Admin : public User {
private:
    static int no_movie;
    Movie m[100];
    Language language;
    Screen& screen = Screen::getInstance();
public:
    //Admin(){no_movie=0;}
    //void updatenumberofmovies(int n){no_movie+=n;}
    int getnummovies(){return no_movie;}
    void addMovie();
    void removeMovie();
    void display_all();


};

class Ticket {
  private:
    int num_seats;
    int revenue;
    int* available_seats;

  public:
    Ticket(int num_seats);
    ~Ticket();
    void book(int num_tickets);
    void display();
    void calculate_amount_regular();
    void calculate_amount_vip();
};

class Customer : public User {
private:
Screen& screen = Screen::getInstance();
public:
void displayLanguages();
void displayMoviesByLanguage(string language);
friend class Ticket;
void bookRegularTicket();
void bookVipTicket();
void book_tickets();
};

