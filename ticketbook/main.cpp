#include <iostream>
#include <string>
using namespace std;

class Movie;
class Showtime;
class Screen;
class User;
class Admin;
class Customer;
class Language;

const int MAX_LANGUAGES = 5;
const int MAX_MOVIES = 10;
const int MAX_SHOWTIMES = 20;

class Language {
private:
    string name;
public:
    Language() {}
    Language(string n) : name(n) {}
    string getName() { return name; }
};

class Movie {
private:
    string name;
    Language language;
public:
    Movie() {}
    Movie(string n, Language lang) : name(n), language(lang) {}
    string getName() { return name; }
    Language getLanguage() { return language; }
};

class Showtime {
private:
    string time;
    Movie movie;
public:
    Showtime() {}
    Showtime(string t, Movie m) : time(t), movie(m) {}
    string getTime() { return time; }
    Movie getMovie() { return movie; }
};

class Screen {
public:
    Showtime showtimes[MAX_SHOWTIMES];
    int numShowtimes;

    Screen() : numShowtimes(0) {}

    static Screen& getInstance() {
        static Screen instance;
        return instance;
    }

    void addShowtime(Showtime showtime) {
        if (numShowtimes < MAX_SHOWTIMES) {
            showtimes[numShowtimes] = showtime;
            numShowtimes++;
        }
    }

    void displayLanguages() {
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

    void displayMoviesByLanguage(string language) {
        cout << "Movies available in " << language << ":" << endl;
        for (int i = 0; i < numShowtimes; i++) {
            if (showtimes[i].getMovie().getLanguage().getName() == language) {
                cout << showtimes[i].getMovie().getName() << endl;
            }
        }
    }

    void displayMovies() {
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
};

class User {
protected:
    string username;
    string password;
public:
    void setUsername(string name) {
        username = name;
    }

    void setPassword(string pass) {
        password = pass;
    }

    virtual bool login(string name, string pass) {
        return (name == username && pass == password);
    }
};

class Admin : public User {
private:
    Language language;
    Screen& screen = Screen::getInstance();
public:
    void addMovie() {
        cout << "Adding movie to screen" << endl;

        string movieTitle;
        cout << "Enter the movie title: ";
        cin >> movieTitle;

        string languageName;
        cout << "Enter the language of the movie: ";
        cin >> languageName;
        language = Language(languageName);

        Movie movie(movieTitle, language);

        string showtime;
        cout << "Enter showtime (e.g. 13:30): ";
        cin >> showtime;
        Showtime showtimeObj(showtime, movie);

        screen.addShowtime(showtimeObj);

        cout << "Movie added successfully!" << endl;
    }

    void removeMovie() {
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
                    screen.showtimes[j - 1] = screen.showtimes[j];
                }
                screen.numShowtimes--;
                cout << "Movie removed successfully!" << endl;
                return;
            }
        }

        cout << "Movie not found!" << endl;
    }
};

class Ticket {
private:
    int num_seats;
    int revenue;
    int* available_seats;

public:
    Ticket(int num_seats) {
        this->num_seats = num_seats;
        this->revenue = 0;
        available_seats = new int[num_seats];
        for (int i = 0; i < num_seats; i++) {
            available_seats[i] = i + 1;
        }
    }

    ~Ticket() {
        delete[] available_seats;
    }

    void book(int num_tickets) {
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
                        available_seats[j] = available_seats[num_seats - 1];
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

    void display() {
        cout << "Number of available seats: " << num_seats << endl;
    }

    void calculate_amount_booked() {
        int amount_booked = revenue * 100;
        cout << "Amount booked: $" << amount_booked << endl;
    }
};

class Customer : public User {
private:
    Screen& screen = Screen::getInstance();
public:
    void displayLanguages() {
        screen.displayLanguages();
    }

    void displayMoviesByLanguage(string language) {
        screen.displayMoviesByLanguage(language);
    }

    friend class Ticket;

    void bookRegularTicket() {
        cout << "Available movies:" << endl;
        screen.displayMovies();

        string movieName;
        cout << "Enter movie name: ";
        cin.ignore();
        getline(cin, movieName);

        string showtime;
        cout << "Enter showtime (e.g. 13:30): ";
        cin >> showtime;

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
            cout << "Enter the number of tickets: ";
            cin >> num;
            ticket.book(num);
            ticket.display();
            ticket.calculate_amount_booked();
            cout << "Regular ticket booked for " << movieName << " at " << showtime << endl;
        } else {
            cout << "Invalid movie name or showtime." << endl;
        }
    }

    void bookVipTicket() {
        cout << "Available movies:" << endl;
        screen.displayMovies();

        string movieName;
        cout << "Enter movie name: ";
        cin.ignore();
        getline(cin, movieName);

        string showtime;
        cout << "Enter showtime (e.g. 13:30): ";
        cin >> showtime;

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
            cout << "Enter the number of tickets: ";
            cin >> num;
            ticket.book(num);
            ticket.display();
            cout << "VIP ticket booked for " << movieName << " at " << showtime << endl;
        } else {
            cout << "Invalid movie name or showtime." << endl;
        }
    }
};

void runApplication() {
    char choice;
    Admin admin;
    admin.setUsername("admin");
    admin.setPassword("admin");
    string name, pass;
    int ch;
    char ach;

    cout << "Enter admin username: ";
    cin >> name;
    cout << "Enter admin password: ";
    cin >> pass;

    if (admin.login(name, pass)) {
        do {
            cout << "\nEnter your choice: \n1. Add movie\n2. Delete movie\n3. Display movies\n";
            cin >> ch;
            switch (ch) {
                case 1:
                    admin.addMovie();
                    break;
                case 2:
                    admin.removeMovie();
                    break;
                case 3:
                    Screen::getInstance().displayMovies();
                    break;
                default:
                    cout << "Invalid choice!" << endl;
                    break;
            }
            cout << "\nDo you want to perform admin tasks again (y/n)? ";
            cin >> ach;
        } while (ach == 'y' || ach == 'Y');

        Customer customer;
        customer.setUsername("customer");
        customer.setPassword("customer");

        cout << "Enter customer username: ";
        cin >> name;
        cout << "Enter customer password: ";
        cin >> pass;

        if (customer.login(name, pass)) {
            customer.displayLanguages();

            string language;
            cout << "Enter language: ";
            cin >> language;
            customer.displayMoviesByLanguage(language);

            cout << "What ticket would you like to book? (Type 'V' or 'v' for VIP tickets or 'R' or 'r' for regular): ";
            cin >> choice;

            if (choice == 'R' || choice == 'r') {
                customer.bookRegularTicket();
            } else if (choice == 'V' || choice == 'v') {
                customer.bookVipTicket();
            } else {
                cout << "Invalid choice!" << endl;
            }
        } else {
            cout << "Invalid customer login details." << endl;
        }
    } else {
        cout << "Invalid admin login details." << endl;
    }
}

int main() {
    
    runApplication();
    return 0;
}

