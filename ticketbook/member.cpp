#include<iostream>
#include<fstream>
using namespace std;
#include"header.h"
int Admin::no_movie=0;
Language::Language(){}
Language::Language(string n): name(n){}
string Language::getName() { return name; }

Movie::Movie() {}
Movie::Movie(string n, Language lang) : name(n), language(lang) {}
string Movie::getName() { return name; }
Language Movie::getLanguage() { return language; }

Showtime::Showtime() {}
Showtime::Showtime(string t, Movie m) : time(t), movie(m) {}
string Showtime::getTime() { return time; }
Movie Showtime::getMovie() { return movie; }

Screen::Screen() : numShowtimes(0) {}
Screen& Screen::getInstance() {
    static Screen instance;
    return instance;
}
void Screen::addShowtime(Showtime showtime) {
        if (numShowtimes < MAX_SHOWTIMES) {
            showtimes[numShowtimes] = showtime;
            numShowtimes++;
        }
    }
void Screen::displayLanguages() {
        cout << "Available languages:" << endl;
        for (int i = 0; i < numShowtimes; i++) {
            bool found = false;
            for (int j = 0; j < i; j++) {
                if (showtimes[i].getMovie().getLanguage().getName() == showtimes[j].getMovie().getLanguage().getName()) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << showtimes[i].getMovie().getLanguage().getName() << endl;
            }
        }
    }
void Screen::displayMoviesByLanguage(string language) {
        cout << "Movies available in " << language << ":" << endl;
        for (int i = 0; i < numShowtimes; i++) {
            if (showtimes[i].getMovie().getLanguage().getName() == language) {
                cout << showtimes[i].getMovie().getName() << endl;
            }
        }
    }
void Screen::displayMovies() {
    cout << "Available movies:" << endl;
    for (int i = 0; i < numShowtimes; i++) {
        bool found = false;
        for (int j = 0; j < i; j++) {
            if (showtimes[i].getMovie().getName() == showtimes[j].getMovie().getName()) {
                found = true;
                break;
            }
        }
        if (!found) {
            cout << showtimes[i].getMovie().getName() << endl;
        }
    }
}


void User::setUsername(string name) {
        username = name;
    }
void User::setPassword(string pass) {
        password = pass;
    }
bool User::login(string name, string pass) {
        return (name == username && pass == password);
    }

void Movie::getdetails()
{
    cout << "Enter the movie title: ";
    cin >> name;
    string languageName;
    cout << "Enter the language of the movie: ";
    cin >> languageName;
    language.setname(languageName);
}
void Admin::addMovie() {
        static int i=0;

        ofstream f;
        f.open("movies.dat", ios::app|ios::binary);
        cout << "Enter the number of movies to add: ";
        cin >> n;
        no_movie+=n;
        // create movie object
        for (int j = 0; j < n; j++) {
            m[i].getdetails();
        f.write((char*)&m[i++], sizeof(Movie));
    }
    // add showtime details for the movie
    //use dsowtime class in movie similar to languaGE
    /*string showtime;
    cout << "Enter showtime (e.g. 13:30): ";
    cin >> showtime;
    Showtime showtimeObj(showtime, movie);

    // add showtime to screen
    screen.addShowtime(showtimeObj);
*/
    cout << "Movie added successfully!" << endl;
   }


void Admin::removeMovie() {
    cout << "Removing movie from screen" << endl;
    string movieTitle;
    cout << "Enter the movie title: ";
    cin >> movieTitle;
    string showtime;
    cout << "Enter showtime (e.g. 13:30): ";
    cin >> showtime;


    for (int i = 0; i < screen.numShowtimes; i++) {
        if (screen.showtimes[i].getTime() == showtime && screen.showtimes[i].getMovie().getName() == movieTitle) {
            for (int j = i + 1; j < screen.numShowtimes; j++) {
                screen.showtimes[j-1] = screen.showtimes[j];
            }
            screen.numShowtimes--;
            cout << "Movie removed successfully!" << endl;
            return;
        }
    }

    cout << "Movie not found!" << endl;
   }


Ticket::Ticket(int num_seats) {
      this->num_seats = num_seats;
      this->revenue = 0;
      available_seats = new int[num_seats];
      for (int i = 0; i < num_seats; i++) {
        available_seats[i] = i + 1;
      }
    }

Ticket::~Ticket() {
      delete[] available_seats;
    }

void Ticket:: book(int num_tickets) {
  if (num_tickets > num_seats) {
    cout << "Error: Not enough seats available." << endl;
    return;
  }
  if (num_tickets > num_seats - revenue) {
    cout << "Error: Only " << num_seats - revenue << " seats available." << endl;
    return;
  }

  cout << "Please enter the seat numbers you wish to book:" << endl;
  int seat_number;
  for (int i = 0; i < num_tickets; i++) {
    bool seat_available = false;
    while (!seat_available) {
      cin >> seat_number;
      seat_available = false;
      for (int j = 0; j < num_seats; j++) {
        if (available_seats[j] == seat_number) {
          available_seats[j] = available_seats[num_seats-1];
          num_seats--;
          revenue++;
          seat_available = true;
          cout << "Seat number " << seat_number << " booked." << endl;
          break;
        }
      }
      if (!seat_available) {
        cout << "Seat number " << seat_number << " is already booked. Please choose another seat." << endl;
      }
    }
  }
}

void Ticket::display() {
      cout << "Number of available seats: " << num_seats << endl;
    }

void Ticket::calculate_amount_regular() {
      int amount_booked = revenue * 100;
      cout << "Amount booked: $" << amount_booked << endl;
    }
void Ticket::calculate_amount_vip(){
      int amount_booked = revenue * 200;
      cout << "Amount booked: $" << amount_booked << endl;
    }


void Customer::displayLanguages() {
screen.displayLanguages();
}
void Customer::displayMoviesByLanguage(string language) {
screen.displayMoviesByLanguage(language);
}
void Customer::bookRegularTicket() {
        // Display available movies
        cout << "Available movies:" << endl;
        screen.displayMovies();

        // Get movie name from customer
        string movieName;
        cout << "Enter movie name: ";
        cin.ignore();
        getline(cin, movieName);

        // Get showtime from customer
        string showtime;
        cout << "Enter showtime (e.g. 13:30): ";
        cin >> showtime;

        // Check if showtime is valid
        bool showtimeExists = false;
        for (int i = 0; i < screen.numShowtimes; i++) {
            if (screen.showtimes[i].getMovie().getName() == movieName && screen.showtimes[i].getTime() == showtime) {
                showtimeExists = true;
                break;
            }
        }

        if (showtimeExists)
            {
                int num;

           Ticket ticket(10);
           ticket.display();
           cout<<"ENTER THE NUMBER OF TICKETS";
           cin>>num;
           ticket.book(num);
           ticket.display();

           ticket.calculate_amount_regular();
            cout << "Regular ticket booked for " << movieName << " at " << showtime << endl;
        } else {
            cout << "Invalid movie name or showtime." << endl;
        }
    }

void Customer::bookVipTicket() {
        // Display available movies
        cout << "Available movies:" << endl;
        screen.displayMovies();

        // Get movie name from customer
        string movieName;
        cout << "Enter movie name: ";
        cin.ignore();
        getline(cin, movieName);
        string showtime;
        cout << "Enter showtime (e.g. 13:30): ";
        cin >> showtime;

        // Check if showtime is valid
        bool showtimeExists = false;
        for (int i = 0; i < screen.numShowtimes; i++) {
            if (screen.showtimes[i].getMovie().getName() == movieName && screen.showtimes[i].getTime() == showtime) {
                showtimeExists = true;
                break;
            }
        }

        if (showtimeExists) {
            int num;
           Ticket ticket(10);
           ticket.display();
           cout<<"ENTER THE NUMBER OF TICKETS";
           cin>>num;
           ticket.book(num);
           ticket.display();
           ticket.calculate_amount_regular();
            cout << "VIP ticket booked for " << movieName << " at " << showtime << endl;
        } else {
            cout << "Invalid movie name or showtime." << endl;
        }
    }
void Customer::book_tickets(){
    char bchoice;
    cout<<"\ntwo types of tickets: \n1.REGULAR TICKET(price:100)\n2.VIP TICKET(price:200)\n ";
    cout<<"WHAT TICKET YOU WOULD LIKE TO BOOK(TYPE 'V' OR 'v' FOR VIP TICKETS OR 'R' OR 'r' REGULAR)";
    cin>>bchoice;
    Customer customerInstance;
        if(bchoice=='R'|| bchoice=='r')
        {
            customerInstance.bookRegularTicket();
        }
        if(bchoice=='V'|| bchoice=='v')
        {
            customerInstance.bookVipTicket();
        }

}
void Admin::display_all()
{
        screen.displayMovies();
        screen.displayLanguages();
}
