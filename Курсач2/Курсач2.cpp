#include <iostream>
#include <Windows.h> //манипуляции с консолью
#include <vector> //библиотека векторов
#include <string> //библиотека строкового типа
#include <iomanip> //манипуляции ввода-вывода
#include <string> //библиотека для строкового типа данных
using namespace std;

//Задание 1.1
class Sotrudnik { //базовый класс: сотрудник
private:
    string FIO;
    unsigned int ZP = 0;
    string dolzhnost;

public:
    void setFIO(string fio_1)
    { //инициализация ФИО
        FIO = fio_1;
    }
    string getFIO() const
    {
        return FIO;
    }

    void setZP(unsigned int zp_1)
    { //инициализация зарплаты
        ZP = zp_1;
    }
    unsigned int getZP() const
    {
        return ZP;
    }
    void setDolzhnost(string dolzhnost1)
    { //инициализация должности
        dolzhnost = dolzhnost1;
    }
    string getDolzhnost()
    {
        return dolzhnost;
    }

    void info(Sotrudnik sotrudnik)
    { //вывод базовой информации о сотруднике компании
        cout << "Должность: " << sotrudnik.getDolzhnost() << "\nФИО: " << sotrudnik.getFIO() << "\nЗарплата: " << sotrudnik.getZP() << endl;
    }
};

class Direktor : virtual public Sotrudnik { //класс: директор
private:
    vector<Sotrudnik> Podchinennie;

public:
    void setPodchinennie(vector<Sotrudnik> podchinennie)
    { //инициализация вектора, содержащего подчиненных директора
        Podchinennie = podchinennie;
    }
    vector<Sotrudnik> getPodchinennie()
    {
        return Podchinennie;
    }
    void uvolnenie(Direktor& direktor, vector<Sotrudnik>& podchinennie, string FIO)
    { //Метод увольнения старых сотрудников
        int counter = 0, size = podchinennie.size();
        for (int i = 0; i < size; i++) {
            if (podchinennie[i].getFIO() == FIO) {
                cout << podchinennie[i].getDolzhnost() << " " << FIO << " был уволен." << endl << endl;
                podchinennie.erase(podchinennie.begin() + i);
                direktor.setPodchinennie(podchinennie);
                break;
            }
            else counter++;
        }
        if (counter == size)  cout << "Такого сотрудника не существует!" << endl << endl;
    }
    void prinyatie(Sotrudnik& sotrudnik, Direktor& direktor, vector<Sotrudnik>& podchinennie, string dolzhnost)
    { //Метод принятия новых сотрудников
        podchinennie = direktor.getPodchinennie();
        sotrudnik.setDolzhnost(dolzhnost);
        podchinennie.insert(podchinennie.end(), sotrudnik);
        direktor.setPodchinennie(podchinennie);
        cout << sotrudnik.getFIO() << " был принят на должность " << sotrudnik.getDolzhnost() << "." << endl;
    }
};

class SisAdmin : public Sotrudnik { //класс системный администратор
private:
    vector<string> Oborudovanie;

public:
    void setOborudovanie(vector<string> oborudovanie)
    { //инициализация оборудования, которым управляет системный администратор
        Oborudovanie = oborudovanie;
    }
    vector<string> getOborudovanie()
    {
        return Oborudovanie;
    }
};

class Secretary : virtual public Sotrudnik { //класс секретарь
public:
    void SpisokSotrudnikov(vector<Sotrudnik> spisok, Direktor direktor)
    { //Метод, выводящий список подчиненных директора
        spisok = direktor.getPodchinennie();
        cout << "\nПодчиненные директора " << direktor.getFIO() << ":" << endl;
        cout << left << setw(40) << "Должность" << setw(40) << "ФИО" << setw(40) << "Зарплата" << endl;
        for (int i = 0; i < spisok.size(); i++) {
            cout << left << setw(40) << spisok[i].getDolzhnost() << setw(40) << spisok[i].getFIO() << setw(40) << spisok[i].getZP() << endl;
        }
    }
    void SpisokOborudovaniya(vector<string> oborudovanie, SisAdmin sisadmin)
    { //Метод, выводящий список оборудования, которым распоряжается сис.админ
        oborudovanie = sisadmin.getOborudovanie();
        cout << "\nСписок оборудования системного администратора:\n";
        for (int i = 0; i < oborudovanie.size(); i++) {
            cout << i + 1 << ") " << oborudovanie[i] << ";" << endl;
        }
    }
};

//Задание 1.2
class HR_Manager : public Direktor, public Secretary { //класс системный администратор (стажер)
private:
    vector<string> kandidati;

public:
    void set_kandidati(vector<string> kandidati1)
    { //инициализация списка стажеров
        kandidati = kandidati1;
    }
    vector<string> get_kandidati()
    {
        return kandidati;
    }
};

class Buhgalter : public Sotrudnik { //класс бухгалтер
private:
    vector<int> Dnevnaya_Stavka;

public:
    void setStavka(vector<int> stavka)
    { //инициализация тарифной ставки сотрудников
        Dnevnaya_Stavka = stavka;
    }
    vector<int> getStavka()
    {
        return Dnevnaya_Stavka;
    }
    void raschetZP(vector<int> stavka, Direktor& direktor, vector<Sotrudnik>& podchinennie)
    { //Метод перерасчета заработной платы сотрудников
        cout << "\nПерерасчет зарплаты сотрудников: ";
        direktor.setZP(stavka[0] * 23);
        cout << "\n\tЗарплата директора: " << direktor.getZP() << endl;
        for (int i = 0; i < podchinennie.size(); i++) {
            if (podchinennie[i].getDolzhnost() == "Бухгалтер") {
                podchinennie[i].setZP(stavka[1] * 23);
                cout << "\tЗарплата бухгалтера " << podchinennie[i].getFIO() << ": " << podchinennie[i].getZP() << endl;
            }
            else if (podchinennie[i].getDolzhnost() == "Секретарь") {
                podchinennie[i].setZP(stavka[2] * 23);
                cout << "\tЗарплата секретаря " << podchinennie[i].getFIO() << ": " << podchinennie[i].getZP() << endl;
            }
            else if (podchinennie[i].getDolzhnost() == "Системный администратор") {
                podchinennie[i].setZP(stavka[3] * 23);
                cout << "\tЗарплата системного администратора " << podchinennie[i].getFIO() << ": " << podchinennie[i].getZP() << endl;
            }
            else if (podchinennie[i].getDolzhnost() == "HR-менеджер") {
                podchinennie[i].setZP(stavka[4] * 23);
                cout << "\tЗарплата HR-менеджера " << podchinennie[i].getFIO() << ": " << podchinennie[i].getZP() << endl;
            }
        }
    }
};

class Initials : virtual public Sotrudnik {
private:
    string initials;
public:
    string init(string FIO, vector <Sotrudnik> podchinennie) { //Получение инициалов сотрудника
        int counter = 0;
        for (int j = 0; j < podchinennie.size(); j++) {
            if (FIO == podchinennie[j].getFIO()) {
                int i;
                for (i = 0; FIO[i] != ' '; i++)
                {
                    initials.insert(initials.end(), FIO[i]);
                }
                initials.push_back(' ');
                initials.push_back(FIO[i + 1]);
                initials.push_back('.');
                for (i++; FIO[i] != ' '; i++);
                initials.push_back(' ');
                initials.push_back(FIO[i + 1]);
                initials.push_back('.');
                return initials;
            }
            else {
                counter++;
            }
        }
        if (counter == podchinennie.size())
            return "Такого сотрудника не существует!\n";
    }
};

class Viplati : virtual public Sotrudnik {
public:
    unsigned int Viplata(string FIO, vector <Sotrudnik> podchinennie) {
        int counter = 0;
        for (int j = 0; j < podchinennie.size(); j++) {
            if (FIO == podchinennie[j].getFIO()) {
                cout << "Ежемесячные выплаты работнику " << FIO << ": " << podchinennie[j].getZP() << endl;
                return podchinennie[j].getZP();
            }
            else {
                counter++;
            }
        }
        if (counter == podchinennie.size()) {
            cout << "Такого сотрудника не существует!\n";
            return 0;
        }
    }
};

class INFO_Sotrudnik : public Initials, public Viplati {
public:
    void info_sotr(string FIO, vector <Sotrudnik> podchinennie) {
        cout << "Информация о сотруднике:\n";
        int counter = 0;
        for (int j = 0; j < podchinennie.size(); j++) {
            if (FIO == podchinennie[j].getFIO()) {
                cout << "Фамилия, имя, отчество сотрудника (инициалы): ";
                cout << init(FIO, podchinennie) << endl;
                Viplata(FIO, podchinennie);
            }
            else {
                counter++;
            }
        }
        if (counter == podchinennie.size()) {
            cout << "Такого сотрудника не существует!\n";
        }
    }
};

int main()
{
    SetConsoleCP(1251); //Ввод на русском языке
    setlocale(0, ""); //Вывод на русском языке
    vector<string> dolzhnost, oborudovanie, kandidati;
    vector<Sotrudnik> podchinennie;

    //Создание сотрудника-директора
    Direktor direktor;
    direktor.setDolzhnost("Директор");
    direktor.setFIO("Иванов Иван Иванович");
    direktor.setZP(100000);

    //Создание сотрудника-бухгалтера
    Buhgalter buhgalter;
    buhgalter.setDolzhnost("Бухгалтер");
    buhgalter.setFIO("Петров Петр Петрович");
    buhgalter.setZP(66000);

    //Создание сотрудника-секретаря
    Secretary secretary;
    secretary.setDolzhnost("Секретарь");
    secretary.setFIO("Васильев Василий Васильевич");
    secretary.setZP(46000);

    //Создание сотрудника-системного администратора
    SisAdmin sisadmin;
    sisadmin.setDolzhnost("Системный администратор");
    sisadmin.setFIO("Зайцев Артем Викторович");
    sisadmin.setZP(40000);
    oborudovanie = { "компьютер", "ноутбук", "мышь", "клавиатура", "сервер" };
    sisadmin.setOborudovanie(oborudovanie);

    //Задание 1.2. Создание HR-менеджера
    HR_Manager hr;
    hr.setDolzhnost("HR-менеджер");
    hr.setFIO("Волков Павел Викторович");
    hr.setZP(50000);
    kandidati = { "Хунгуреев Артем Викторович", "Агеева Александра Матвеевна", "Гусева София Тимофеевна", "Дорофеев Андрей Демидович" };
    hr.set_kandidati(kandidati);

    //заполнение вектора сотрудников для директора
    podchinennie = { buhgalter, secretary, sisadmin, hr };
    direktor.setPodchinennie(podchinennie);

    vector<string> Dnevnaya_Stavka = { "Директор: 4000 руб/день", "Бухгалтер: 2800 руб/день", "Секретарь: 2000 руб/день", "Системный администратор: 1700 руб/день", "HR: 2200 руб/день" };
    vector<int> Stavka = { 4000, 2800, 2000, 1700, 2200 };
    buhgalter.setStavka(Stavka);

    //Задание 1.2
    Initials initials;
    Viplati viplati;
    INFO_Sotrudnik info;
    info.info_sotr("Волков Павел Викторович", podchinennie);

    //Создание пользовательского интерфейса для удобства использования программы
    char flag_dolzhnost;
    cout << "Должности: \n1) Директор;\n2) Бухгалтер;\n3) Секретарь;\n4) Системный администратор;\n5) HR-менеджер;\n6) Выход.\n";
    cout << "Выберите должность, чтобы вывести доступные команды, связанные с ней: ";
    cin >> flag_dolzhnost;
    while (flag_dolzhnost != '6') {
        switch (flag_dolzhnost) {
        case '1': {
            system("cls");
            cout << "Директор" << endl;
            char flag_commands_direktor;
            cout << "1) Вывести ФИО директора;\n"
                << "2) Вывести зарплату директора;\n"
                << "3) Уволить работника;\n"
                << "4) Принять на работу\n"
                << "5) Отмена.\n";
            cout << "Введите команду: ";
            cin >> flag_commands_direktor;
            while (flag_commands_direktor != '5') {
                switch (flag_commands_direktor) {
                case '1': { //Вывод ФИО директора
                    system("cls");
                    cout << "Директор" << endl;
                    cout << "ФИО директора: " << direktor.getFIO() << endl;
                    break;
                }
                case '2': { //Вывод зарплаты директора
                    system("cls");
                    cout << "Директор" << endl;
                    cout << "Зарплата директора: " << direktor.getZP() << endl;
                    break;
                }
                case '3': { //Увольнение сотрудника
                    system("cls");
                    string FIO;
                    cout << "Директор" << endl;
                    secretary.SpisokSotrudnikov(podchinennie, direktor);
                    cout << "\nВведите ФИО сотрудника, которого нужно уволить: ";
                    cin.ignore();
                    getline(cin, FIO);
                    direktor.uvolnenie(direktor, podchinennie, FIO);
                    break;
                }
                case '4': { //Принятие на работу
                    system("cls");
                    cout << "Директор" << endl;
                    string FIO_Sotrudnik;
                    unsigned int ZP_Sotrudnik;
                    int c = 0;
                    Sotrudnik sotrudnik;
                    cout << "Введите ФИО будущего сотрудника: ";
                    cin.ignore();
                    getline(cin, FIO_Sotrudnik); //следующие строки написаны для проверки ввода ФИО
                    for (int i = 0; i < FIO_Sotrudnik.length(); i++) {
                        if (((int)FIO_Sotrudnik[i] >= -32 && (int)FIO_Sotrudnik[i] <= -1) || ((int)FIO_Sotrudnik[i] >= -64 && (int)FIO_Sotrudnik[i] <= -33)) continue;
                        else if ((int)FIO_Sotrudnik[i] == 32) {
                            if ((int)FIO_Sotrudnik[i+1] >= -64 && (int)FIO_Sotrudnik[i+1] <= -33) continue;
                            else c++;
                        }
                        else c++;
                    }
                    if (c == 0) {
                        sotrudnik.setFIO(FIO_Sotrudnik);
                        cout << "Введите зарплату будущего сотрудника: ";
                        cin >> ZP_Sotrudnik;
                        sotrudnik.setZP(ZP_Sotrudnik);
                        char flag_prinyatie;
                        cout << "Выберите должность, на которую требуется сотрудник: " << endl;
                        cout << "1) Бухгалтер;\n"
                            << "2) Секретарь;\n"
                            << "3) Системный администратор;\n"
                            << "4) Завершение.\n";
                        cout << "Введите команду: ";
                        cin >> flag_prinyatie;
                        system("cls");
                        cout << "Директор" << endl;
                        while (flag_prinyatie != '4') {
                            switch (flag_prinyatie) {
                            case '1': {
                                direktor.prinyatie(sotrudnik, direktor, podchinennie, "Бухгалтер");
                                break;
                            }
                            case '2': {
                                direktor.prinyatie(sotrudnik, direktor, podchinennie, "Секретарь");
                                break;
                            }
                            case '3': {
                                direktor.prinyatie(sotrudnik, direktor, podchinennie, "Системный администратор");
                                break;
                            }
                            default: {
                                cout << "Неизвестная команда!";
                                break;
                            }
                            }
                            break;
                        }
                    }
                    else cout << "Ввод имени осуществлен неверно!\n";
                    break;
                }
                default: {
                    system("cls");
                    cout << "Директор" << endl;
                    cout << "Неверная команда!\n";
                    break;
                }
                }
                cout << "1) Вывести ФИО директора;\n"
                    << "2) Вывести зарплату директора;\n"
                    << "3) Уволить работника;\n"
                    << "4) Принять на работу\n"
                    << "5) Отмена.\n";
                cout << "Введите команду: ";
                cin >> flag_commands_direktor;
            }
            system("cls");
            cout << "Выход к выбору должности.\n";
            break;
        }
        case '2': {
            system("cls");
            cout << "Бухгалтер" << endl;
            char flag_commands_buhgalter;
            cout << "1) Вывести ФИО бухгалтера;\n"
                << "2) Вывести зарплату бухгалтера;\n"
                << "3) Рассчитать з/п работникам, исходя из ставки;\n"
                << "4) Отмена.\n";
            cout << "Введите команду: ";
            cin >> flag_commands_buhgalter;
            while (flag_commands_buhgalter != '4') {
                switch (flag_commands_buhgalter) {
                case '1': {
                    system("cls");
                    cout << "Бухгалтер" << endl;
                    cout << "ФИО бухгалтера: " << buhgalter.getFIO() << endl;
                    break;
                } //Вывод ФИО бухгалтера
                case '2': {
                    system("cls");
                    cout << "Бухгалтер" << endl;
                    cout << "Зарплата бухгалтера: " << buhgalter.getZP() << endl;
                    break;
                } //Вывод зарплаты бухгалтера
                case '3': { //Рассчет з/п, исходя из ставки
                    system("cls");
                    cout << "Бухгалтер" << endl;
                    cout << "Дневная ставка:" << endl;
                    for (int i = 0; i < Dnevnaya_Stavka.size(); i++) {
                        cout << '\t' << Dnevnaya_Stavka[i] << endl;
                    }
                    buhgalter.raschetZP(Stavka, direktor, podchinennie);
                    direktor.setPodchinennie(podchinennie);
                    break;
                }
                default: {
                    system("cls");
                    cout << "Бухгалтер" << endl;
                    cout << "Неверная команда!\n";
                    break;
                }
                }
                cout << "1) Вывести ФИО бухгалтера;\n"
                    << "2) Вывести зарплату бухгалтера;\n"
                    << "3) Рассчитать з/п работникам, исходя из ставки;\n"
                    << "4) Отмена.\n";
                cout << "Введите команду: ";
                cin >> flag_commands_buhgalter;
            }
            system("cls");
            cout << "Выход к выбору должности\n";
            break;
        }
        case '3': {
            system("cls");
            cout << "Секретарь" << endl;
            char flag_commands_secretary;
            cout << "1) Вывести ФИО секретаря;\n"
                << "2) Вывести зарплату секретаря;\n"
                << "3) Вывести список сотрудников для директора;\n"
                << "4) Вывести таблицей список оборудования для системного администратора;\n"
                << "5) Отмена.\n";
            cout << "Введите команду: ";
            cin >> flag_commands_secretary;
            while (flag_commands_secretary != '5') {
                switch (flag_commands_secretary) {
                case '1': {
                    system("cls");
                    cout << "Секретарь" << endl;
                    cout << "ФИО секретаря: " << secretary.getFIO() << endl;
                    break;
                } //Вывод ФИО бухгалтера
                case '2': {
                    system("cls");
                    cout << "Секретарь" << endl;
                    cout << "Зарплата секретаря: " << secretary.getZP() << endl;
                    break;
                } //Вывод зарплаты бухгалтера
                case '3': {
                    system("cls");
                    cout << "Секретарь" << endl;
                    secretary.SpisokSotrudnikov(podchinennie, direktor);
                    cout << endl;
                    break;
                }
                case '4': {
                    system("cls");
                    cout << "Секретарь" << endl;
                    secretary.SpisokOborudovaniya(oborudovanie, sisadmin);
                    cout << endl;
                    break;
                }
                default: {
                    system("cls");
                    cout << "Секретарь" << endl;
                    cout << "Неверная команда!";
                    break;
                }
                }
                cout << "1) Вывести ФИО секретаря;\n"
                    << "2) Вывести зарплату секретаря;\n"
                    << "3) Вывести список сотрудников для директора;\n"
                    << "4) Вывести таблицей список оборудования для системного администратора;\n"
                    << "5) Отмена.\n";
                cout << "Введите команду: ";
                cin >> flag_commands_secretary;
            }
            system("cls");
            cout << "Выход к выбору должности\n";
            break;
        }
        case '4': {
            system("cls");
            cout << "Системный администратор" << endl;
            char flag_commands_sisadmin;
            cout << "1) Вывести ФИО системного администратора;\n"
                << "2) Вывести зарплату системного администратора;\n"
                << "3) Отмена.\n";
            cout << "Введите команду: ";
            cin >> flag_commands_sisadmin;
            system("cls");
            cout << "Системный администратор" << endl;
            while (flag_commands_sisadmin != '3') {
                switch (flag_commands_sisadmin) {
                case '1': {
                    system("cls");
                    cout << "Системный администратор" << endl;
                    cout << "ФИО системного администратора: " << sisadmin.getFIO() << endl;
                    break;
                } //Вывод ФИО
                case '2': {
                    system("cls");
                    cout << "Системный администратор" << endl;
                    cout << "Зарплата системного администратора: " << sisadmin.getZP() << endl;
                    break;
                } //Вывод зарплаты
                default: {
                    system("cls");
                    cout << "Системный администратор" << endl;
                    cout << "Неверная команда!\n";
                    break;
                }
                }
                cout << "1) Вывести ФИО системного администратора;\n"
                    << "2) Вывести зарплату системного администратора;\n"
                    << "3) Отмена.\n";
                cout << "Введите команду: ";
                cin >> flag_commands_sisadmin;
            }
            system("cls");
            cout << "Выход к выбору должности\n";
            break;
        }
        case '5': {
            system("cls");
            cout << "HR-менеджер" << endl;
            char flag_hr;
            cout << "1) Вывести ФИО HR-менеджера;\n"
                << "2) Вывести зарплату HR-менеджера;\n"
                << "3) Принять стажера на работу;\n"
                << "4) Вывести список сотрудников;\n"
                << "5) Отмена;\n";
            cout << "Введите команду: ";
            cin >> flag_hr;
            while (flag_hr != '5') {
                switch (flag_hr) {
                case '1': {
                    system("cls");
                    cout << "HR-менеджер" << endl;
                    cout << "ФИО HR-менеджера: " << hr.getFIO() << endl;
                    break;
                }
                case '2': {
                    system("cls");
                    cout << "HR-менеджер" << endl;
                    cout << "Зарплата HR-менеджера: " << hr.getZP() << endl;
                    break;
                }
                case '3': { //Принятие на работу
                    system("cls");
                    cout << "HR-менеджер" << endl;
                    cout << "Выберите стажера, которого нужно принять на работу: " << endl;
                    cout << "1) Хунгуреев Артем Викторович;\n2) Агеева Александра Матвеевна;\n3) Гусева София Тимофеевна;\n4) Дорофеев Андрей Демидович;\n5) Отмена.\n";
                    char flag_kandidati;
                    cout << "Введите команду: ";
                    cin >> flag_kandidati;
                    while (flag_kandidati != '5') {
                        switch (flag_kandidati) {
                        case '1': {
                            system("cls");
                            cout << "HR-менеджер\n";
                            int counter = 0;

                            for (int i = 0; i < podchinennie.size(); i++) {
                                if (podchinennie[i].getFIO() == "Хунгуреев Артем Викторович") counter++;
                                else continue;
                            }

                            if (counter == 0) {
                                cout << "Выберите должность, на которую будет принят стажер: \n";
                                cout << "1) Бухгалтер;\n2) Секретарь;\n3) Системный администратор;\n4) HR-менеджер;\n5) Отмена.\n";
                                char flag_kandidati_dolzhnost;
                                cout << "Введите команду: ";
                                cin >> flag_kandidati_dolzhnost;
                                while (flag_kandidati_dolzhnost != '5') {
                                    switch (flag_kandidati_dolzhnost) {
                                    case '1': {
                                        system("cls");
                                        Buhgalter buhgalter1;
                                        buhgalter1.setFIO("Хунгуреев Артем Викторович");
                                        buhgalter1.setZP(10);
                                        direktor.prinyatie(buhgalter1, direktor, podchinennie, "Бухгалтер");
                                        break;
                                    }
                                    case '2': {
                                        system("cls");
                                        Secretary secretary1;
                                        secretary1.setFIO("Хунгуреев Артем Викторович");
                                        secretary1.setZP(10);
                                        direktor.prinyatie(secretary1, direktor, podchinennie, "Секретарь");
                                        break;
                                    }
                                    case '3': {
                                        system("cls");
                                        SisAdmin sisadmin1;
                                        sisadmin1.setFIO("Хунгуреев Артем Викторович");
                                        sisadmin1.setZP(10);
                                        direktor.prinyatie(sisadmin1, direktor, podchinennie, "Системный администратор");
                                        break;
                                    }
                                    case '4': {
                                        system("cls");
                                        HR_Manager hr1;
                                        hr1.setFIO("Хунгуреев Артем Викторович");
                                        hr1.setZP(10);
                                        direktor.prinyatie(hr1, direktor, podchinennie, "HR-менеджер");
                                        break;
                                    }
                                    default: {
                                        system("cls");
                                        cout << "HR-менеджер" << endl;
                                        cout << "Неверная команда!\n";
                                        break;
                                    }
                                    }
                                    break;
                                }
                            }
                            else {
                                system("cls");
                                cout << "HR-менеджер\n";
                                cout << "Стажер Хунгуреев Артем Викторович уже принят на работу!" << endl;
                            }
                            break;
                        }
                        case '2': {
                            system("cls");
                            cout << "HR-менеджер\n";
                            int counter = 0;

                            for (int i = 0; i < podchinennie.size(); i++) {
                                if (podchinennie[i].getFIO() == "Агеева Александра Матвеевна") counter++;
                                else continue;
                            }

                            if (counter == 0) {
                                cout << "Выберите должность, на которую будет принят стажер: \n";
                                cout << "1) Бухгалтер;\n2) Секретарь;\n3) Системный администратор;\n4) HR-менеджер;\n5) Отмена.\n";
                                char flag_kandidati_dolzhnost;
                                cout << "Введите команду: ";
                                cin >> flag_kandidati_dolzhnost;
                                while (flag_kandidati_dolzhnost != '5') {
                                    switch (flag_kandidati_dolzhnost) {
                                    case '1': {
                                        system("cls");
                                        Buhgalter buhgalter1;
                                        buhgalter1.setFIO("Агеева Александра Матвеевна");
                                        buhgalter1.setZP(10);
                                        direktor.prinyatie(buhgalter1, direktor, podchinennie, "Бухгалтер");
                                        break;
                                    }
                                    case '2': {
                                        system("cls");
                                        Secretary secretary1;
                                        secretary1.setFIO("Агеева Александра Матвеевна");
                                        secretary1.setZP(10);
                                        direktor.prinyatie(secretary1, direktor, podchinennie, "Секретарь");
                                        break;
                                    }
                                    case '3': {
                                        system("cls");
                                        SisAdmin sisadmin1;
                                        sisadmin1.setFIO("Агеева Александра Матвеевна");
                                        sisadmin1.setZP(10);
                                        direktor.prinyatie(sisadmin1, direktor, podchinennie, "Системный администратор");
                                        break;
                                    }
                                    case '4': {
                                        system("cls");
                                        HR_Manager hr1;
                                        hr1.setFIO("Агеева Александра Матвеевна");
                                        hr1.setZP(10);
                                        direktor.prinyatie(hr1, direktor, podchinennie, "HR-менеджер");
                                        break;
                                    }
                                    default: {
                                        system("cls");
                                        cout << "HR-менеджер" << endl;
                                        cout << "Неверная команда!\n";
                                        break;
                                    }
                                    }
                                    break;
                                }
                            }
                            else {
                                system("cls");
                                cout << "HR-менеджер\n";
                                cout << "Стажер Агеева Александра Матвеевна уже принят на работу!" << endl;
                            }
                            break;
                        }
                        case '3': {
                            system("cls");
                            cout << "HR-менеджер:\n";
                            int counter = 0;

                            for (int i = 0; i < podchinennie.size(); i++) {
                                if (podchinennie[i].getFIO() == "Гусева София Тимофеевна") counter++;
                                else continue;
                            }


                            if (counter == 0) {
                                cout << "Выберите должность, на которую будет принят стажер: \n";
                                cout << "1) Бухгалтер;\n2) Секретарь;\n3) Системный администратор;\n4) HR-менеджер;\n5) Отмена.\n";
                                int flag_kandidati_dolzhnost;
                                cout << "Введите команду: ";
                                cin >> flag_kandidati_dolzhnost;
                                while (flag_kandidati_dolzhnost != '5') {
                                    switch (flag_kandidati_dolzhnost) {
                                    case '1': {
                                        system("cls");
                                        Buhgalter buhgalter1;
                                        buhgalter1.setFIO("Гусева София Тимофеевна");
                                        buhgalter1.setZP(10);
                                        direktor.prinyatie(buhgalter1, direktor, podchinennie, "Бухгалтер");
                                        break;
                                    }
                                    case '2': {
                                        system("cls");
                                        Secretary secretary1;
                                        secretary1.setFIO("Гусева София Тимофеевна");
                                        secretary1.setZP(10);
                                        direktor.prinyatie(secretary1, direktor, podchinennie, "Секретарь");
                                        break;
                                    }
                                    case '3': {
                                        system("cls");
                                        SisAdmin sisadmin1;
                                        sisadmin1.setFIO("Гусева София Тимофеевна");
                                        sisadmin1.setZP(10);
                                        direktor.prinyatie(sisadmin1, direktor, podchinennie, "Системный администратор");
                                        break;
                                    }
                                    case '4': {
                                        system("cls");
                                        HR_Manager hr1;
                                        hr1.setFIO("Гусева София Тимофеевна");
                                        hr1.setZP(10);
                                        direktor.prinyatie(hr1, direktor, podchinennie, "HR-менеджер");
                                        break;
                                    }
                                    default: {
                                        system("cls");
                                        cout << "HR-менеджер" << endl;
                                        cout << "Неверная команда!\n";
                                        break;
                                    }
                                    }
                                    break;
                                }
                            }
                            else {
                                system("cls");
                                cout << "HR-менеджер\n";
                                cout << "Стажер Гусева София Тимофеевна уже принят на работу!" << endl;
                            }
                            break;
                        }
                        case '4': {
                            system("cls");
                            cout << "HR-менеджер:\n";
                            int counter = 0;

                            for (int i = 0; i < podchinennie.size(); i++) {
                                if (podchinennie[i].getFIO() == "Дорофеев Андрей Демидович") counter++;
                                else continue;
                            }

                            if (counter == 0) {
                                cout << "Выберите должность, на которую будет принят стажер: \n";
                                cout << "1) Бухгалтер;\n2) Секретарь;\n3) Системный администратор;\n4) HR-менеджер;\n5) Отмена.\n";
                                int flag_kandidati_dolzhnost;
                                cout << "Введите команду: ";
                                cin >> flag_kandidati_dolzhnost;
                                while (flag_kandidati_dolzhnost != '5') {
                                    switch (flag_kandidati_dolzhnost) {
                                    case '1': {
                                        system("cls");
                                        Buhgalter buhgalter1;
                                        buhgalter1.setFIO("Дорофеев Андрей Демидович");
                                        buhgalter1.setZP(10);
                                        direktor.prinyatie(buhgalter1, direktor, podchinennie, "Бухгалтер");
                                        break;
                                    }
                                    case '2': {
                                        system("cls");
                                        Secretary secretary1;
                                        secretary1.setFIO("Дорофеев Андрей Демидович");
                                        secretary1.setZP(10);
                                        direktor.prinyatie(secretary1, direktor, podchinennie, "Секретарь");
                                        break;
                                    }
                                    case '3': {
                                        system("cls");
                                        SisAdmin sisadmin1;
                                        sisadmin1.setFIO("Дорофеев Андрей Демидович");
                                        sisadmin1.setZP(10);
                                        direktor.prinyatie(sisadmin1, direktor, podchinennie, "Системный администратор");
                                        break;
                                    }
                                    case '4': {
                                        system("cls");
                                        HR_Manager hr1;
                                        hr1.setFIO("Дорофеев Андрей Демидович");
                                        hr1.setZP(10);
                                        direktor.prinyatie(hr1, direktor, podchinennie, "HR-менеджер");
                                        break;
                                    }
                                    default: {
                                        system("cls");
                                        cout << "HR-менеджер" << endl;
                                        cout << "Неверная команда!\n";
                                        break;
                                    }
                                    }
                                    break;
                                }
                            }
                            else {
                                system("cls");
                                cout << "HR-менеджер\n";
                                cout << "Стажер Дорофеев Андрей Демидович уже принят на работу!" << endl;
                            }
                            break;
                        }
                        default: {
                            system("cls");
                            cout << "HR-менеджер\n";
                            cout << "Неверная команда!\n";
                            break;
                        }
                        }
                        break;
                    }
                    system("pause");
                    system("cls");
                    cout << "HR-менеджер\n";
                    break;
                }
                case '4': { //Вывод списка сотрудников
                    system("cls");
                    cout << "HR-менеджер\n";
                    secretary.SpisokSotrudnikov(podchinennie, direktor);
                    cout << endl;
                    break;
                }
                default: {
                    system("cls");
                    cout << "HR-менеджер\n";
                    cout << "Неверная команда!\n";
                    break;
                }
                }
                cout << "1) Вывести ФИО HR-менеджера;\n"
                    << "2) Вывести зарплату HR-менеджера;\n"
                    << "3) Принять стажера на работу;\n"
                    << "4) Вывести список сотрудников;\n"
                    << "5) Отмена;\n";
                cout << "Введите команду: ";
                cin >> flag_hr;
            }
            system("cls");
            cout << "Выход к выбору должности\n";
            break;
        }
        default: {
            system("cls");
            cout << "Неверная команда!\n";
            break;
        }
        }
        cout << "Должности: \n1) Директор;\n2) Бухгалтер;\n3) Секретарь;\n4) Системный администратор;\n5) HR-менеджер;\n6) Выход.\n";
        cout << "Выберите должность: ";
        cin >> flag_dolzhnost;
    }
    cout << "Выход. Завершение программы.";
    return 0;
}