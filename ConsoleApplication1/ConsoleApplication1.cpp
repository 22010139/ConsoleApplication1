#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

class Tariff {
protected:
    string name;
    double price;
    int clients;

public:
    Tariff(string name, double price, int clients) {
        this->name = name;
        this->price = price;
        this->clients = clients;
    }

    virtual void getInfo() = 0;

    double getPrice() {
        return price;
    }

    int getClients() {
        return clients;
    }
};

class UnlimitedTariff : public Tariff {
private:
    int speed;

public:
    UnlimitedTariff(string name, double price, int clients, int speed) : Tariff(name, price, clients) {
        this->speed = speed;
    }

    virtual void getInfo() {
        cout << "Тариф \"" << name << "\"  скорость- " << speed << " Mb/s, оплата пользователя - " << price << " рублей, клиентов -  " << clients << endl;
    }
};

class LimitedTariff : public Tariff {
private:
    int traffic;

public:
    LimitedTariff(string name, double price, int clients, int traffic) : Tariff(name, price, clients) {
        this->traffic = traffic;
    }

    virtual void getInfo() {
        cout << "Тариф \"" << name << "\" трафик - " << traffic << " Gb, оплата пользователя - " << price << " рублей, клиентов - " << clients << endl;
    }
};

Tariff* parseTariff() {
    string type, name;
    double price;
    int clients, limit;

    cout << "Введите тип тарифа (\"unlimited\" или \"limited\"): ";
    cin >> type;
    cout << "Введите название тарифа: ";
    cin >> name;
    cout << "Введите цену тарифа: ";
    cin >> price;
    cout << "Введите количество клиентов: ";
    cin >> clients;

    if (type == "unlimited") {
        int speed;
        cout << "Введите скорость тарифа: ";
        cin >> speed;
        return new UnlimitedTariff(name, price, clients, speed);
    }
    else if (type == "limited") {
        int traffic;
        cout << "Введите лимит трафика: ";
        cin >> traffic;
        return new LimitedTariff(name, price, clients, traffic);
    }
    else {
        cout << "Некорректный тип тарифа" << endl;
        return nullptr;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<Tariff*> tariffs;
    tariffs.push_back(new UnlimitedTariff("Плюс", 1000, 500, 100));
    tariffs.push_back(new LimitedTariff("Семейный", 500, 1010, 20));
    tariffs.push_back(new UnlimitedTariff("Дачный", 750, 215, 50));
    tariffs.push_back(new LimitedTariff("Рабочий", 630, 800, 30));
    tariffs.push_back(new LimitedTariff("Детский", 240, 340, 15));

    while (true) {
        cout << "1 - Добавить тариф\n2 - Вывести информацию\n3 - Выход\n";
        int choice;
        cin >> choice;
        if (choice == 1) {
            Tariff* newTariff = parseTariff();
            if (newTariff != nullptr) {
                tariffs.push_back(newTariff);
            }
        }
        else if (choice == 2) {
            int totalClients = 0;
            for (auto tariff : tariffs) {
                tariff->getInfo();
                totalClients += tariff->getClients();
            }
            cout << "Количество клиентов: " << totalClients << endl;

            sort(tariffs.begin(), tariffs.end(), [](Tariff* t1, Tariff* t2) {
                return t1->getPrice() < t2->getPrice();
                });

            cout << "\nСортировка по размеру абоненской платы:\n" << endl;
            for (auto tariff : tariffs) {
                tariff->getInfo();
            }

            double minPrice, maxPrice;
            cout << "Введите минимальную и максимальную цену:\n" << endl;
            std::cin >> minPrice;
            std::cin >> maxPrice;

            while (minPrice < 0 || maxPrice < 0 || minPrice >= maxPrice) {
                cout << "Некорректные значения! Попробуйте еще раз: ";
                std::cin >> minPrice;
                std::cin >> maxPrice;
            }

            cout << "Выбранная пользователем оплата от " << minPrice << " до " << maxPrice << " рублей:\n" << endl;
            for (auto tariff : tariffs) {
                if (tariff->getPrice() >= minPrice && tariff->getPrice() <= maxPrice) {
                    tariff->getInfo();
                }
            }
        }
        else if (choice == 3) {
            break;
        }
    }

    for (auto tariff : tariffs) {
        delete tariff;
    }

    return 0;
}