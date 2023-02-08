#include <iostream>
// BUAT BIKIN FILE TXT
#include <fstream>
// BUAT BIKIN ARRAY
#include <vector>
// BUAT DAPETIN WAKTU-TANGGAL
#include <ctime>
// TO EDITING STRING
#include <string>
// FOR CHECK SPACING
#include <cctype>
// BUAT BIKIN STRING TANPA SPASI
#include <algorithm>
// BUAT VALIDASI
#include <regex>

#include <windows.h>

/*
 *
 * KELOMPOK 5
 * RESERVASI LAPANGAN FUTSAL (FUTSIN)
 * 1. Akwan Cakra Tajimalela (2209098)
 * 2. Dhowy Anja Alhusna (2210013)
 * 3. Nauval Gymnasti (2200418)
 * 4. Billdan Satriana Roseandree (2200482)
 *
 * PEMBAGIAN TUGAS
 * AKWAN CAKRA:
 * SEMUA USER
 *
 * BILLDAN:
 * CRUD PERLENGKAPAN
 *
 * NAUVAL:
 * CRUD LAPANGAN
 *
 * ANJA:
 * AUTHENTIKASI
 *
 */

using namespace std;
// INITIALIZE DECLARATION
bool isLogin = false;
// ID FOR USE IN ALL CODE
int idAccount;

// MENDISPLAY LIST LAPANGAN YANG TERDAPAT DI CLASS LAPANGAN
// LAPANGAN {ID, NAMA, HARGA, VISIBILITY}
// TOOL {ID, NAMA, HARGA, MINIMAL, STOK, VISIBILITY}
// TRANSAKSI {ID, ID AKUN, LAPANGAN, PERLENGKAPAN, JUMLAH, DURASI, 1/2 (BERHASIL/ SELESAI), KEMBALIAN, JAM MULAI, JAM SELESAI, TANGGAL, BULAN,TAHUN}
vector<vector<string>> Account = {{"1", "akwan", "akwan@mail.com", "akwan", "2"}, {"2", "billdan", "billdan@mail.com", "billdan", "1"}, {"3", "gymnasty", "gymnasty@mail.com", "gymnasty", "2"}}, Lapangans = {{"1", "Lapangan Hitam", "20000", "1"}, {"2", "Lapangan Normal", "25000", "1"}, {"3", "Lapangan Medium", "30000", "1"}}, Tools = {{"1", "Cone", "10000", "5", "100", "1"}, {"2", "Rompi", "10000", "5", "100", "1"}, {"3", "Bola", "4000", "1", "12", "1"}};
vector<vector<string>> Transactions = {{"1", "1", "1", "0", "0", "2", "1", "5000", "12:00", "14:30", "11", "12", "2022"}, {"2", "2", "1", "0", "0", "14", "1", "5000", "07:00", "21:00", "10", "12", "2022"}, {"3", "1", "1", "0", "0", "1", "1", "5000", "14:30", "15:30", "13", "12", "2022"}};

struct Calendar
{
    string month[12] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
    string year[20] = {"2022", "2023", "2024", "2025", "2026", "2027", "2028", "2029", "2030", "2031", "2032", "2033", "2034", "2035", "2036", "2037", "2038", "2039", "2040", "2041"};
    float waktuAll[15] = {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21};
};

// INISIALISASI AGAR DAPAT DIGUNAKAN DIBAWAH
void Login();
void Register();
int AdminMainMenu();
int MainMenu();
void TambahLapangan();
void UbahLapangan();
void HapusLapangan();
void TambahTool();
void UbahTool();
void HapusTool();
void ListTransaksi();
void AdminTransaksi();
void AdminLapangan();
void AdminTool();
void CreateSewa();
void getDetailLapangan(int idLapangan);
void PrintTransaction(int idAccount, int idTransaction);

int jamBuka = 14;
Calendar calendar;

// MAU BIKIN CURRENCY FORMAT
string currencyFormatter(int price) // 10000
{
    string strHarga = to_string(price);
    if (strHarga.length() == 4)
    {
        strHarga.insert(1, ".");
    }
    else if (strHarga.length() == 5)
    {
        strHarga.insert(2, ".");
    }
    else if (strHarga.length() == 6)
    {
        strHarga.insert(3, ".");
    }
    else if (strHarga.length() == 7)
    {
        strHarga.insert(1, ".");
        strHarga.insert(5, ".");
    }
    else if (strHarga.length() == 8)
    {
        strHarga.insert(2, ".");
        strHarga.insert(5, ".");
    }

    return strHarga;
}

// FOR MAKING INFO OUTLINE
void autoLiner(string message, int height, int width)
{
    char sym1 = 218; // ┌
    char sym2 = 196; // ─
    char sym3 = 191; // ┐
    char sym4 = 179; // │
    char sym5 = 192; // └
    char sym6 = 217; // ┘

    int msg = message.size();
    int length = (width / 2) - (msg / 2);

    int stat = 0;
    if (height == 3)
    {
        stat = (height / 3);
    }
    else
    {
        stat = (height / 3) + 1;
    }

    cout << sym1;
    for (int i = 0; i < width; i++)
    {
        cout << sym2;
    }
    cout << sym3;
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        cout << sym4;
        if (i != stat)
        {
            for (int j = 0; j < width; j++)
            {
                cout << " ";
            }
        }
        else
        {
            for (int j = 0; j < length; j++)
            {
                cout << " ";
            }
            cout << message;
            if (msg % 2 != 0)
            {
                length -= 1;
            }
            for (int j = 0; j < length; j++)
            {
                cout << " ";
            }
            length += 1;
        }
        cout << sym4;
        if (i != height - 1)
        {
            cout << endl;
        }
    }
    cout << endl;
    cout << sym5;
    for (int i = 0; i < width; i++)
    {
        cout << sym2;
    }
    cout << sym6;
    cout << endl;
}

// FOR MAKING LINE FOR SEPARATOR
void oneLine(int width)
{
    char sym = 196; // ─

    for (int i = 0; i < width + 1; i++)
    {
        cout << sym;
    }
}

// FOR MAKING LINE WITH TEXT FOR SEPARATOR
void oneLineText(string message, int width)
{
    char sym = 196; // ─
    int msg = message.size();
    int widhtAuto = (width / 2) - (msg / 2);

    for (int i = 0; i < widhtAuto; i++)
    {
        cout << sym;
    }
    cout << message;
    for (int i = 0; i < widhtAuto + 1; i++)
    {
        cout << sym;
    }
}

// CHECK IF LAPANGAN EXIST
bool GetLapangan(int lap)
{
    for (int i = 0; i < Lapangans.size(); i++)
    {
        if (stoi(Lapangans[i][0]) == lap && stoi(Lapangans[i][3]) == 1)
        {
            return true;
        }
    }
    return false;
}

// CHECK IF TRANSACTION EXIST
bool GetTransaction(int idTransaction)
{
    for (int i = 0; i < Transactions.size(); i++)
    {
        if (stoi(Transactions[i][0]) == idTransaction && stoi(Transactions[i][1]) == idAccount)
        {
            return true;
        }
    }
    return false;
}

// CHECK IF TOOL EXIST
bool GetTool(int tool)
{
    for (int i = 0; i < Tools.size(); i++)
    {
        if (stoi(Tools[i][0]) == tool && stoi(Tools[i][5]) == 1)
        {
            return true;
        }
    }
    return false;
}

// GETTING USERNAME
string GetUsername()
{
    for (int i = 0; i < Account.size(); i++)
    {
        if (stoi(Account[i][0]) == idAccount)
        {
            return Account[i][1];
        }
    }
}

// CHECK IF EMAIL EXIST
bool GetEmail(string email)
{
    for (int i = 0; i < Account.size(); i++)
    {
        if (Account[i][2] == email)
        {
            return true;
        }
    }
}

// CHECK IF STRING IS ADMIN
bool isAdmin()
{
    int exist = 0;
    for (int i = 0; i < Account.size(); i++)
    {
        if (stoi(Account[i][0]) == idAccount && stoi(Account[i][4]) == 1)
        {
            exist++;
            return true;
        }
    }
    if (exist == 1)
    {
        return false;
    }
}

// CHECK IF STRING IS NUMBER
bool isNumber(string number)
{
    regex regex_number("((\\b[0-9]+)?\\.)?[0-9]+\\b");
    bool isNumber = regex_match(number, regex_number);

    if (isNumber)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// CHECK IF THE DATE IS CLEAR
bool isOccupiedDate(int idLapangan, string tanggal, string bulan, string tahun)
{
    int waktuMain = 0;
    for (int i = 0; i < Transactions.size(); i++)
    {
        if (stoi(Transactions[i][2]) == idLapangan && Transactions[i][10] == tanggal && Transactions[i][11] == bulan && Transactions[i][12] == tahun)
        {
            waktuMain += stoi(Transactions[i][5]);
        }
    }
    if (waktuMain == 14)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// CHANGING TEXT COLOR
void changeColor(int desiredColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);
}

/*
 * FUNGSI UNTUK USER
 * BUKA 14 JAM DARI JAM 7 - 21
 * 07:00 - 21:00
 */

// UNTUK MEMBUAT TAB PADA KALENDER
void GetTab(int &tab, int &sumDay, int &newTab, string &text, int tahun, int bulan)
{
    int astTab;
    // GETTING TAB IN EVERY YEAR
    for (int j = 0; j < 20; j++)
    {
        sumDay = 31;
        newTab = 7 - ((sumDay + tab) - (((sumDay + tab) / 7) * 7));
        tab = newTab;
        if (j == 0)
        {
            tab = 5;
        }
        if (bulan == 1 && tahun == stoi(calendar.year[j]))
        {
            text = "JANUARI " + to_string(tahun);
            break;
        }
        if (j == 0)
        {
            tab = newTab;
        }

        sumDay = 28;
        tab = 7 - newTab;
        newTab = 7 - ((sumDay + tab) - (((sumDay + tab) / 7) * 7));
        if (bulan == 2 && tahun % 4 != 0 && tahun == stoi(calendar.year[j]))
        {
            text = "FEBRUARI " + to_string(tahun);
            break;
        }

        if (stoi(calendar.year[j]) % 4 == 0)
        {
            sumDay = 29;
            tab = 7 - newTab;
            newTab = 7 - ((sumDay + tab) - (((sumDay + tab) / 7) * 7));
        }
        if (bulan == 2 && tahun % 4 == 0 && tahun == stoi(calendar.year[j]))
        {
            text = "FEBRUARI " + to_string(tahun);
            break;
        }

        sumDay = 31;
        tab = 7 - newTab;
        newTab = 7 - ((sumDay + tab) - (((sumDay + tab) / 7) * 7));
        if (bulan == 3 && tahun == stoi(calendar.year[j]))
        {
            text = "MARET " + to_string(tahun);
            break;
        }

        sumDay = 30;
        tab = 7 - newTab;
        newTab = 7 - ((sumDay + tab) - (((sumDay + tab) / 7) * 7));
        if (bulan == 4 && tahun == stoi(calendar.year[j]))
        {
            text = "APRIL " + to_string(tahun);
            break;
        }

        sumDay = 31;
        tab = 7 - newTab;
        newTab = 7 - ((sumDay + tab) - (((sumDay + tab) / 7) * 7));
        if (bulan == 5 && tahun == stoi(calendar.year[j]))
        {
            text = "MEI " + to_string(tahun);
            break;
        }

        sumDay = 30;
        tab = 7 - newTab;
        newTab = 7 - ((sumDay + tab) - (((sumDay + tab) / 7) * 7));
        if (bulan == 6 && tahun == stoi(calendar.year[j]))
        {
            text = "JUNI " + to_string(tahun);
            break;
        }

        sumDay = 31;
        tab = 7 - newTab;
        newTab = 7 - ((sumDay + tab) - (((sumDay + tab) / 7) * 7));
        if (bulan == 7 && tahun == stoi(calendar.year[j]))
        {
            text = "JULI " + to_string(tahun);
            break;
        }

        sumDay = 31;
        tab = 7 - newTab;
        newTab = 7 - ((sumDay + tab) - (((sumDay + tab) / 7) * 7));
        if (bulan == 8 && tahun == stoi(calendar.year[j]))
        {
            text = "AGUSTUS " + to_string(tahun);
            break;
        }

        sumDay = 30;
        tab = 7 - newTab;
        newTab = 7 - ((sumDay + tab) - (((sumDay + tab) / 7) * 7));
        if (bulan == 9 && tahun == stoi(calendar.year[j]))
        {
            text = "SEPTEMBER " + to_string(tahun);
            break;
        }

        sumDay = 31;
        tab = 7 - newTab;
        newTab = 7 - ((sumDay + tab) - (((sumDay + tab) / 7) * 7));
        if (bulan == 10 && tahun == stoi(calendar.year[j]))
        {
            text = "OKTOBER " + to_string(tahun);
            break;
        }

        sumDay = 30;
        tab = 7 - newTab;
        newTab = 7 - ((sumDay + tab) - (((sumDay + tab) / 7) * 7));
        if (bulan == 11 && tahun == stoi(calendar.year[j]))
        {
            text = "NOVEMBER " + to_string(tahun);
            break;
        }

        sumDay = 31;
        tab = 7 - newTab;
        newTab = 7 - ((sumDay + tab) - (((sumDay + tab) / 7) * 7));
        if (bulan == 12 && tahun == stoi(calendar.year[j]))
        {
            text = "DESEMBER " + to_string(tahun);
            break;
        }
    }
}

// GET JADWAL CALENDAR
void GetCalendar(int lap, int bulan = 1, int tahun = 2022, int mode = 2)
{
    // 14 OREN
    // 13 UNGU
    // 12 MERAH
    // 11 CYAN
    // 10 HIJAU MUDA
    // 9 BIRU MUDA
    // 8 ABU
    // 7 PUTIH
    // 6 KUNING
    // 241 ITU SIMBOL KOTAK
    char plus = 241;
    int main = 0, sumDay = 0, tab = 5, newTab = 0, num = 0, once = 0;
    int getDay = 0, lastTab = 0;
    string text = "ERROR";

    GetTab(tab, sumDay, newTab, text, tahun, bulan);
    oneLineText(text, 50);
    cout << endl;
    cout << "S\tS\tR\tK\tJ\tS\tM" << endl;

    for (int i = 1; i <= sumDay + tab; i++)
    {
        if (i <= tab && tab != 7)
        {
            cout << " "
                 << "\t";
        }
        else if (i > tab)
        {
            for (int j = 0; j < Transactions.size(); j++)
            {
                if (mode == 1)
                {
                    if (stoi(Transactions[j][10]) == (i - tab) && stoi(Transactions[j][11]) == bulan && stoi(Transactions[j][12]) == tahun && stoi(Transactions[j][2]) == lap)
                    {
                        main += stoi(Transactions[j][5]);
                    }

                    if (j == Transactions.size() - 1)
                    {
                        if (main > 13)
                        {
                            changeColor(8);
                        }
                        else if (main >= 11 && main <= 13)
                        {
                            changeColor(12);
                        }
                        else if (main >= 6 && main <= 10)
                        {
                            changeColor(6);
                        }
                        else if (main >= 1 && main <= 5)
                        {
                            changeColor(13);
                        }
                        else
                        {
                            changeColor(7);
                        }

                        if (i % 7 == 0)
                        {
                            cout << (i - tab) << "\n";
                        }
                        else
                        {
                            cout << (i - tab) << "\t";
                        }
                    }
                }
                else if (mode == 2 && stoi(Transactions[j][1]) == idAccount)
                {
                    if (stoi(Transactions[j][10]) == (i - tab) && stoi(Transactions[j][11]) == bulan && stoi(Transactions[j][12]) == tahun)
                    {
                        main += stoi(Transactions[j][5]);
                    }

                    if (j == Transactions.size() - 1)
                    {
                        if (main > 0)
                        {
                            changeColor(13);
                        }
                        else
                        {
                            changeColor(7);
                        }

                        if (i % 7 == 0)
                        {
                            cout << (i - tab) << "\n";
                        }
                        else
                        {
                            cout << (i - tab) << "\t";
                        }
                    }
                }

                if (j == Transactions.size() - 1)
                {
                    main = 0;
                }
                changeColor(7);
            }
        }
    }
    if (mode == 1)
    {
        cout << endl;
        oneLineText("INFO", 50);
        cout << endl;
        changeColor(8);
        cout << (char)254u;
        changeColor(7);
        cout << ": Tidak ada waktu tersisa" << endl;
        changeColor(12);
        cout << (char)254u;
        changeColor(7);
        cout << ": Hanya tersisa " << plus << "1-2 Jam" << endl;
        changeColor(6);
        cout << (char)254u;
        changeColor(7);
        cout << ": Tersisa " << plus << "8-4 Jam" << endl;
        changeColor(13);
        cout << (char)254u;
        changeColor(7);
        cout << ": Tersisa " << plus << "13-9 Jam" << endl;
        cout << (char)254u;
        cout << ": Kosong " << endl;
        oneLine(50);
        cout << endl;
    }
    else
    {
        cout << endl;
        oneLineText("INFO", 50);
        cout << endl;
        cout << (char)254u;
        cout << ": Tidak ada jadwal" << endl;
        changeColor(13);
        cout << (char)254u;
        changeColor(7);
        cout << ": Terdapat jadwal " << endl;
        oneLine(50);
        cout << endl;
    }
}

// GET JAM BERMAIN
// TRANSAKSI {ID, ID AKUN, LAPANGAN, PERLENGKAPAN, JUMLAH, DURASI, 1/2 (BERHASIL/ SELESAI), JAM MULAI, JAM SELESAI, KEMBALIAN, TANGGAL, BULAN,TAHUN}
bool GetWaktu(int idLapangan, int dur, string tanggal, string bulan, string tahun, string waktuAwal)
{
    int waktu, sub1, sub2, sub3, sub4, sub5, sub6, sub7, sub8;
    bool exist;
    string time, timeEnd;
    sub5 = stoi(waktuAwal.substr(0, 2));
    sub6 = stoi(waktuAwal.substr(3, 4));
    sub7 = sub5 + dur;
    sub8 = sub6;

    for (int i = 0; i < Transactions.size(); i++)
    {
        exist = true;
        if (stoi(Transactions[i][2]) == idLapangan && Transactions[i][10] == tanggal && Transactions[i][11] == bulan && Transactions[i][12] == tahun)
        {
            exist = false;
            time = Transactions[i][8];
            timeEnd = Transactions[i][9];

            sub1 = stoi(time.substr(0, 2));
            sub2 = stoi(time.substr(3, 4));
            sub3 = stoi(timeEnd.substr(0, 2));
            sub4 = stoi(timeEnd.substr(3, 4));

            if (sub5 < 7 || sub7 > 21)
            {
                return false;
            }
            else
            {
                // if (i == Transactions.size() - 1)
                // {
                if (sub5 >= sub1)
                {
                    if (sub5 >= sub1 && sub6 >= sub2 && sub5 < sub3 && (sub6 <= sub4 || sub6 >= sub4) || sub5 <= sub3 && sub6 < sub4)
                    {
                        return false;
                    }
                    else
                    {
                        return true;
                    }
                }
                else if (sub7 <= sub1)
                {
                    if (sub5 <= sub1 && (sub6 >= sub2 || sub6 <= sub2) && sub7 >= sub1 && sub8 > sub4)
                    {
                        return false;
                    }
                    else
                    {
                        return true;
                    }
                }
                else
                {
                    return false;
                    // }
                }
            }
        }
    }

    if (sub5 < 7 || sub7 > 21)
    {
        return false;
    }
    else if (exist)
    {
        return true;
    }
}

void GetJam(int idLapangan, int dur, string tanggal, string bulan, string tahun, string &waktuAwal)
{
    int waktu, sub1, sub2, sub3, sub4;
    string time;
    cout << "Waktu awal bermain yang tersedia\t: " << endl;
    for (int i = 0; i < Transactions.size(); i++)
    {
        // TRANSAKSI {ID, ID AKUN, LAPANGAN, PERLENGKAPAN, JUMLAH, DURASI, 1/2 (BERHASIL/ SELESAI), KEMBALIAN, JAM MULAI, JAM SELESAI, TANGGAL, BULAN,TAHUN}
        for (int j = 0; j < 15; j++)
        {
            if (stoi(Transactions[i][2]) == idLapangan && Transactions[i][10] == tanggal && Transactions[i][11] == bulan && Transactions[i][12] == tahun)
            {
                time = Transactions[i][8];
                sub1 = stoi(time.substr(0, 2));
                sub2 = stoi(time.substr(3, 4));
                sub3 = sub1 + stoi(Transactions[i][5]);

                if (calendar.waktuAll[j] <= sub3 && calendar.waktuAll[j] >= sub1)
                {
                    if (sub2 == 0)
                    {
                        calendar.waktuAll[j] = 0;
                    }
                    else if (sub2 == 10)
                    {
                        calendar.waktuAll[j] = 0.1;
                    }
                    else if (sub2 == 20)
                    {
                        calendar.waktuAll[j] = 0.2;
                    }
                    else if (sub2 == 30)
                    {
                        calendar.waktuAll[j] = 0.3;
                    }
                    else if (sub2 == 40)
                    {
                        calendar.waktuAll[j] = 0.4;
                    }
                    else if (sub2 == 50)
                    {
                        calendar.waktuAll[j] = 0.5;
                    }

                    for (int k = j; k <= dur; k++)
                    {
                        calendar.waktuAll[k] = 0;
                    }
                }
            }
        }
    }

    int num = 0;
    for (int i = 0; i < 15; i++)
    {
        num++;
        if (calendar.waktuAll[i] == (float)0)
        {
            cout << "[" << num << "] " << i + 7 << ":00 Terisi" << endl;
        }
        else if (calendar.waktuAll[i] == (float)0.1)
        {
            cout << "[" << num << "] " << i + 7 << ":10 Terisi" << endl;
        }
        else if (calendar.waktuAll[i] == (float)0.2)
        {
            cout << "[" << num << "] " << i + 7 << ":20 Terisi" << endl;
        }
        else if (calendar.waktuAll[i] == (float)0.3)
        {
            cout << "[" << num << "] " << i + 7 << ":30 Terisi" << endl;
        }
        else if (calendar.waktuAll[i] == (float)0.4)
        {
            cout << "[" << num << "] " << i + 7 << ":40 Terisi" << endl;
        }
        else if (calendar.waktuAll[i] == (float)0.5)
        {
            cout << "[" << num << "] " << i + 7 << ":50 Terisi" << endl;
        }
        else
        {
            cout << "[" << num << "] " << calendar.waktuAll[i] << ":00" << endl;
        }
    }

    do
    {
        cout << "Pilih waktu waktu awal co(15:30 atau 12.00)\t: ";
        cin >> waktuAwal;
        if (!GetWaktu(idLapangan, dur, tanggal, bulan, tahun, waktuAwal))
        {
            cout << "Waktu telah terisi!" << endl;
        }
    } while (GetWaktu(idLapangan, dur, tanggal, bulan, tahun, waktuAwal) != true);
    cout << "Waktu telah dibooking!" << endl;
    system("pause");
}

// MENDISPLAY LIST LAPANGAN YANG TERDAPAT DI CLASS LAPANGAN
void ListLapangan()
{
    autoLiner("DAFTAR LAPANGAN", 3, 50);
    int num = 0;
    for (int i = 0; i < Lapangans.size(); i++)
    {
        if (stoi(Lapangans[i][3]) == 1)
        {
            num++;
            cout << "[" << num << "] " << Lapangans[i][1] << "\t-\tID: " << Lapangans[i][0]
                 << "\nRp. " << currencyFormatter(stoi(Lapangans[i][2])) << "/Jam" << endl;
        }
    }
    if (num == 0)
    {
        cout << "Tidak ada data lapangan!" << endl;
    }
}

// MENDISPLAY LIST LAPANGAN YANG TERDAPAT DI CLASS LAPANGAN YANG TELAH DIHAPUS
void ListDeletedLapangan()
{
    autoLiner("DAFTAR LAPANGAN DIHAPUS", 3, 50);
    int num = 0;
    for (int i = 0; i < Lapangans.size(); i++)
    {
        if (stoi(Lapangans[i][3]) != 1)
        {
            num++;
            cout << "[" << num << "] " << Lapangans[i][1] << " - ID: " << Lapangans[i][0]
                 << "\nRp. " << currencyFormatter(stoi(Lapangans[i][2])) << "/Jam" << endl;
        }
    }
    if (num == 0)
    {
        cout << "Belum ada data lapangan yang dihapus!" << endl;
    }
}

// MEMBUAT LIST PERLENGKAPAN DARI CLASS TOOLS
void ListTool()
{
    int num = 0;
    autoLiner("DAFTAR PERLENGKAPAN", 3, 50);
    for (int i = 0; i < Tools.size(); i++)
    {
        if (stoi(Tools[i][5]) == 1)
        {
            num++;
            cout << "[" << num << "] " << Tools[i][1] << "\t-\tID: " << Tools[i][0] << "\nRp. "
                 << currencyFormatter(stoi(Tools[i][2])) << "\t/" << Tools[i][3] << "pcs" << endl;
        }
    }
    if (num == 0)
    {
        cout << "Tidak ada data lapangan!" << endl;
    }
}

// MEMBUAT LIST PERLENGKAPAN DARI CLASS TOOLS YANG TELAH DIHAPUS
void ListDeletedTool()
{
    int num = 0;
    autoLiner("DAFTAR PERLENGKAPAN", 3, 50);
    for (int i = 0; i < Tools.size(); i++)
    {
        if (stoi(Tools[i][5]) == 2)
        {
            num++;
            cout << "[" << num << "] " << Tools[i][1] << "\t-\tID: " << Tools[i][0] << "\nRp. "
                 << currencyFormatter(stoi(Tools[i][2])) << "\t/" << Tools[i][3] << "pcs" << endl;
        }
    }
    if (num == 0)
    {
        cout << "Tidak ada data lapangan dihapus!" << endl;
    }
}

// MENGAMBIL INPUTAN LAPANGAN YANG USER MAU
void getLap(int lap, string &dur, string tanggal, string bulan, string tahun, string &waktuAwal)
{
    for (int i = 0; i < Lapangans.size(); i++)
    {
        if (stoi(Lapangans[i][0]) == lap)
        {
            system("CLS");
            getDetailLapangan(lap);
            do
            {
                cout << "Maksimal bermain 24 Jam " << endl;
                cout << "Durasi bermain (jam): ";
                cin >> dur;
                if (!isNumber(dur))
                {
                    cout << "Hanya menerima angka!" << endl;
                }
                else if (stoi(dur) <= 0 || stoi(dur) >= 24)
                {
                    cout << "Inputan tidak sesuai, kurang dari 0 jam atau lebih dari 24 jam!" << endl;
                }
            } while (isNumber(dur) != true || stoi(dur) <= 0 || stoi(dur) >= 24);
            break;
        }
    }

    system("CLS");
    GetJam(lap, stoi(dur), tanggal, bulan, tahun, waktuAwal);
}

// MENDAPATKAN DETIL LAPANGAN
void getDetailLapangan(int idLapangan)
{
    autoLiner("DETIL LAPANGAN", 3, 50);
    for (int i = 0; i < Lapangans.size(); i++)
    {
        if (stoi(Lapangans[i][0]) == idLapangan)
        {
            cout << "Nama\t: " << Lapangans[i][1] << endl;
            cout << "Harga\t: Rp" << currencyFormatter(stoi(Lapangans[i][2])) << " /Jam" << endl;
        }
    }
    oneLine(50);
    cout << endl;
}

// MENDISPLAY DETIL TRANSAKSI YANG TELAH DILAKUKAN
// KEMBALIAN
void getDetail(string lap, string tool, string jmlTool, string dur, string tanggal, string bulan, string tahun, string waktuMulai)
{
    int totalTools = 0, totalAll, sub1, sub2, sub3, sub4;
    string pay, uang, kembalian, waktuSelesai;
    for (int i = 0; i < Lapangans.size(); i++)
    {
        if (stoi(Lapangans[i][0]) == stoi(lap))
        {
            sub1 = stoi(waktuMulai.substr(0, 2));
            sub2 = stoi(waktuMulai.substr(3, 4));
            sub3 = sub1 + stoi(dur);
            sub4 = sub2;
            waktuSelesai = to_string(sub3) + ":" + to_string(sub4);

            system("CLS");
            autoLiner("DETIL TRANSAKSI", 3, 50);
            cout << Lapangans[i][1] << endl;
            cout << "Rp. " << currencyFormatter(stoi(Lapangans[i][2])) << "/Jam\n";
            // cout << Lapangans[i]->desc << "\n\n";
            cout << "INFO :" << endl;
            cout << "Belum termasuk perlengkapan " << endl;
            cout << "Tanggal bermain\t: " << tanggal << "/" << bulan << "/" << tahun << endl;
            cout << "Waktu mulai\t: " << sub1 << ":" << sub2 << " - " << sub3 << ":" << sub4 << endl;
            cout << "Durasi bermain\t: " << dur << " Jam" << endl;
            cout << "Perlengkapan\t: " << endl;
            if (tool != "0")
            {
                for (int j = 0; j < Tools.size(); j++)
                {
                    int num = 1;
                    if (stoi(Tools[j][0]) == stoi(tool))
                    {
                        totalTools += stoi(Tools[i][2]) * stoi(jmlTool);
                        cout << num << ". " << Tools[j][1] << " - " << currencyFormatter(stoi(Tools[i][2])) << " x " << jmlTool << endl;
                        num++;
                    }
                }
            }
            else
            {
                cout << "Tidak menyewa perlengkapan tambahan" << endl;
            }
            cout << endl;
            totalAll = totalTools + (stoi(Lapangans[i][2]) * stoi(dur));
            oneLineText("TOTAL HARGA", 50);
            cout << "\nLapangan\t: "
                 << "Rp. " << currencyFormatter(stoi(Lapangans[i][2])) << " x " << dur << " Jam" << endl;
            if (tool != "0")
            {
                cout << "Perlengkapan\t: "
                     << "Rp. " << currencyFormatter(totalTools) << endl;
            }
            cout << "Total harga\t: "
                 << "Rp. " << currencyFormatter(totalAll) << endl;
            oneLine(50);
            cout << "\nKetik '1' untuk membayar!" << endl;
            cout << "Ketik '0' untuk kembali dan membatalkan transaksi!" << endl;
            do
            {
                cin >> pay;
                if (!isNumber(pay))
                {
                    cout << "Hanya menerima angka!" << endl;
                }
                else if (pay == "0")
                {
                    CreateSewa();
                }
                else if (stoi(pay) != 1)
                {
                    cout << "Inputan tidak sesuai!" << endl;
                }
            } while (isNumber(pay) != true || pay != "0" && pay != "1");

            system("CLS");
            oneLine(50);
            cout << "\nKetik '0' untuk membatalkan transaksi!" << endl;
            cout << "Total harga\t: "
                 << "Rp. " << currencyFormatter(totalAll) << endl;
            do
            {
                cout << "Masukan jumlah uang\t: ";
                cin >> uang;
                if (uang == "0")
                {
                    CreateSewa();
                }
                else if (!isNumber(uang))
                {
                    cout << "Hanya menerima angka!" << endl;
                }
                else if (stoi(uang) < totalAll)
                {
                    cout << "Uang yang dibayarkan belum mencukupi!" << endl;
                }
            } while (isNumber(uang) != true || stoi(uang) < totalAll);

            system("CLS");
            kembalian = to_string(stoi(uang) - totalAll);
            oneLineText("PEMBAYARAN", 50);
            cout << "\nUang dibayarkan\t: Rp" << currencyFormatter(stoi(uang)) << endl;
            cout << "Total harga\t: Rp" << currencyFormatter(totalAll) << endl;
            oneLine(50);
            cout << "\nKembalian\t: Rp" << currencyFormatter(stoi(kembalian)) << endl;
            Transactions.push_back({to_string(Transactions.size() + 1), to_string(idAccount), lap, tool, jmlTool, dur, "1", kembalian, waktuMulai, waktuSelesai, tanggal, bulan, tahun});
            cout << endl;
            system("pause");
            system("CLS");
            oneLineText("TRANSAKSI", 50);
            cout << "\nPembayaran berhasil dilakukan!" << endl;
            // PrintTransaction(lap, tool, Tools, dur, Lapangans, totalTools, totalAll);
        }
    }
}

// MENAMPILKAN DAFTAR TRANSAKSI
// TRANSAKSI {ID, ID AKUN, LAPANGAN, PERLENGKAPAN, JUMLAH, DURASI, 1/2 (BERHASIL/ SELESAI), KEMBALIAN, JAM MULAI, JAM SELESAI, TANGGAL, BULAN,TAHUN}
void GetListTransaction(int idAccount)
{
    int tr = 0, totalLap = 0, totalTool = 0, num = 0, sub1, sub2, sub3, sub4;
    string transaksi;
    system("CLS");
    autoLiner("DAFTAR TRANSAKSI", 3, 50);
    for (int i = 0; i < Transactions.size(); i++)
    {
        if (stoi(Transactions[i][1]) == idAccount)
        {
            tr++;
            string text = "TRANSAKSI ";
            oneLineText(text + to_string(tr), 50);
            cout << "\nTransaksi\t: " << tr << "\nID\t\t: " << Transactions[i][0] << endl;
            for (int a = 0; a < Lapangans.size(); a++)
            {
                if (stoi(Lapangans[a][0]) == stoi(Transactions[i][2]))
                {
                    totalLap = stoi(Lapangans[a][2]) * stoi(Transactions[i][5]);
                    cout << Lapangans[a][1] << "\t: Rp" << currencyFormatter(stoi(Lapangans[a][2])) << " /Jam" << endl;
                }
            }
            cout << "Tanggal bermain\t: " << Transactions[i][10] << "/" << Transactions[i][11] << "/" << Transactions[i][12] << endl;
            cout << "Waktu mulai\t: " << Transactions[i][8] << " - " << Transactions[i][9] << endl;
            cout << "Durasi bermain\t: " << Transactions[i][5] << " Jam" << endl;
            cout << "Perlengkapan\t: " << endl;
            if (Transactions[i][3] != "0")
            {
                for (int b = 0; b < Tools.size(); b++)
                {
                    if (stoi(Tools[b][0]) == stoi(Transactions[i][3]))
                    {
                        num++;
                        totalTool = stoi(Tools[b][2]) * stoi(Transactions[i][4]);
                        cout << num << ". " << Tools[b][1] << " x" << Transactions[i][4] << " - " << currencyFormatter(stoi(Tools[b][2]) * stoi(Transactions[i][4])) << endl;
                    }
                }
            }
            else
            {
                cout << "Tidak menyewa perlengkapan tambahan" << endl;
            }
            oneLineText("TOTAL HARGA", 50);
            cout << "\nLapangan\t: "
                 << "Rp. " << currencyFormatter(totalLap) << endl;
            if (Transactions[i][3] != "0")
            {
                cout << "Perlengkapan\t: "
                     << "Rp. " << currencyFormatter(totalTool) << endl;
            }
            cout << "Uang dibayarkan\t: "
                 << "Rp. " << currencyFormatter(stoi(Transactions[i][7]) + totalLap + totalTool) << endl;
            cout << "Total harga\t: "
                 << "Rp. " << currencyFormatter(totalLap + totalTool) << endl;
            oneLine(50);
            cout << "\nKembalian\t: "
                 << "Rp. " << currencyFormatter(stoi(Transactions[i][7])) << endl;
            oneLine(50);
            cout << "\n\n\n";
        }
    }

    if (tr == 0 && isAdmin())
    {
        cout << "Belum ada data transaksi!" << endl;
    }
    else if (tr == 0)
    {
        cout << "Anda belum memiliki transaksi!" << endl;
    }
    else
    {
        cout << "Apakah anda ingin mencetak transaksi?" << endl;
        cout << "Ketik '0' untuk keluar" << endl;
        do
        {
            cout << "Masukan ID\t: ";
            cin >> transaksi;
            if (transaksi == "0")
            {
                MainMenu();
            }
            else if (!isNumber(transaksi))
            {
                cout << "Hanya menerima angka!" << endl;
            }
            else if (!GetTransaction(stoi(transaksi)))
            {
                cout << "Data transaksi tidak ada!" << endl;
            }
            else
            {
                PrintTransaction(idAccount, stoi(transaksi));
            }
        } while (isNumber(transaksi) != true || GetTransaction(stoi(transaksi)) != true);
    }
}

// PRINT TRANSACTION
void PrintTransaction(int idAccount, int idTransaction)
{
    int tr = 0, totalLap = 0, totalTool = 0, num = 0, sub1, sub2, sub3, sub4;
    system("CLS");
    cout << "Print transaksi" << endl;
    for (int i = 0; i < Transactions.size(); i++)
    {
        if (stoi(Transactions[i][1]) == idAccount && stoi(Transactions[i][0]) == idTransaction)
        {
            tr++;
            string text = "TRANSAKSI ";
            ofstream myfile;
            myfile.open("myTransaction.txt", ios::app);
            myfile << "===================== DAFTAR TRANSAKSI =====================" << endl;
            myfile << "\nTransaksi\t\t: " << tr << endl;
            for (int a = 0; a < Lapangans.size(); a++)
            {
                if (stoi(Lapangans[a][0]) == stoi(Transactions[i][2]))
                {
                    totalLap = stoi(Lapangans[a][2]) * stoi(Transactions[i][5]);
                    myfile << Lapangans[a][1] << "\t: Rp" << currencyFormatter(stoi(Lapangans[a][2])) << " /Jam" << endl;
                }
            }
            myfile << "Tanggal bermain\t: " << Transactions[i][10] << "/" << Transactions[i][11] << "/" << Transactions[i][12] << endl;
            myfile << "Waktu mulai\t\t: " << Transactions[i][8] << " - " << Transactions[i][9] << endl;
            myfile << "Durasi bermain\t: " << Transactions[i][5] << " Jam" << endl;
            myfile << "Perlengkapan\t: " << endl;
            if (Transactions[i][3] != "0")
            {
                for (int b = 0; b < Tools.size(); b++)
                {
                    if (stoi(Tools[b][0]) == stoi(Transactions[i][3]))
                    {
                        num++;
                        totalTool = stoi(Tools[b][2]) * stoi(Transactions[i][4]);
                        myfile << num << ". " << Tools[b][1] << " x" << Transactions[i][4] << " - " << currencyFormatter(stoi(Tools[b][2]) * stoi(Transactions[i][4])) << endl;
                    }
                }
            }
            else
            {
                myfile << "Tidak menyewa perlengkapan tambahan" << endl;
            }
            myfile << endl;
            myfile << "======================== TOTAL HARGA =======================" << endl;
            myfile << "\nLapangan\t\t: "
                   << "Rp. " << currencyFormatter(totalLap) << endl;
            if (Transactions[i][3] != "0")
            {
                myfile << "Perlengkapan\t: "
                       << "Rp. " << currencyFormatter(totalTool) << endl;
            }
            myfile << "Uang dibayarkan\t: "
                   << "Rp. " << currencyFormatter(stoi(Transactions[i][7]) + totalLap + totalTool) << endl;
            myfile << "Total harga\t\t: "
                   << "Rp. " << currencyFormatter(totalLap + totalTool) << endl;
            myfile << "=============================================================" << endl;
            myfile << "\nKembalian\t\t: "
                   << "Rp. " << currencyFormatter(stoi(Transactions[i][7])) << endl;
            myfile << "=============================================================" << endl;
            myfile << "\n\n\n";
            myfile.close();
        }
    }
}

// MENAMPILKAN DAFTAR TRANSAKSI
// LAPANGAN {ID, NAMA, HARGA, VISIBILITY}
// TRANSAKSI {ID, ID AKUN, LAPANGAN, PERLENGKAPAN, JUMLAH, DURASI, 1/2 (BERHASIL/ SELESAI), JAM MULAI, JAM SELESAI, KEMBALIAN, TANGGAL, BULAN, TAHUN}
void ListTransaksi()
{
    int tr = 0, totalLap = 0, totalTool = 0, num = 0;
    system("CLS");
    autoLiner("DAFTAR TRANSAKSI", 3, 50);
    for (int i = 0; i < Transactions.size(); i++)
    {
        tr++;
        string text = "TRANSAKSI ";
        oneLineText(text + to_string(tr), 50);
        for (int a = 0; a < Account.size(); a++)
        {
            if (stoi(Account[a][0]) == stoi(Transactions[i][1]))
            {
                cout << "\nNama\t: " << Account[a][1] << endl;
            }
        }
        oneLine(50);
        cout << endl;
        for (int a = 0; a < Lapangans.size(); a++)
        {
            if (stoi(Lapangans[a][0]) == stoi(Transactions[i][2]))
            {
                totalLap = stoi(Lapangans[a][2]) * stoi(Transactions[i][5]);
                cout << Lapangans[a][1] << "\t: Rp" << currencyFormatter(stoi(Lapangans[a][2])) << " /Jam" << endl;
            }
        }
        cout << "Tanggal bermain\t: " << Transactions[i][10] << "/" << Transactions[i][11] << "/" << Transactions[i][12] << endl;
        cout << "Waktu mulai\t: " << Transactions[i][8] << " - " << Transactions[i][9] << endl;
        cout << "Durasi bermain\t: " << Transactions[i][5] << " Jam" << endl;
        cout << "Perlengkapan\t: " << endl;
        if (Transactions[i][3] != "0")
        {
            for (int b = 0; b < Tools.size(); b++)
            {
                if (stoi(Tools[b][0]) == stoi(Transactions[i][3]))
                {
                    num++;
                    totalTool = stoi(Tools[b][2]) * stoi(Transactions[i][4]);
                    cout << num << ". " << Tools[b][1] << " x" << stoi(Transactions[i][4]) << " - " << currencyFormatter(stoi(Tools[b][2]) * stoi(Transactions[i][4])) << endl;
                }
            }
        }
        else
        {
            cout << "Tidak menyewa perlengkapan tambahan" << endl;
        }
        oneLineText("TOTAL HARGA", 50);
        cout << "\nLapangan\t: "
             << "Rp. " << currencyFormatter(totalLap) << endl;
        if (Transactions[i][3] != "0")
        {
            cout << "Perlengkapan\t: "
                 << "Rp. " << currencyFormatter(totalTool) << endl;
        }
        cout << "Uang dibayarkan\t: "
             << "Rp. " << currencyFormatter(stoi(Transactions[i][7]) + totalLap + totalTool) << endl;
        cout << "Total harga\t: "
             << "Rp. " << currencyFormatter(totalLap + totalTool) << endl;
        oneLine(50);
        cout << "\nKembalian\t: "
             << "Rp. " << currencyFormatter(stoi(Transactions[i][7])) << endl;
        oneLine(50);
        cout << "\n\n\n";
    }

    if (tr == 0)
    {
        cout << "Belum ada data transaksi!" << endl;
    }
}

/*
 *
 * MEMBUAT SEWA LAPANGAN USER
 *
 */
bool skip;
string lap, tool, jmlTool, timed, waktuMulai, waktuSelesai, tanggal, bulan, tahun;
void CreateSewa()
{
    string choice;
    // GETTING TAHUN
    time_t ttime = time(0);
    tm *local_time = localtime(&ttime);
    tahun = to_string(1900 + local_time->tm_year);
    bulan = to_string(1 + local_time->tm_mon);

    // PANDUAN SEWA
    system("CLS");
    autoLiner("PANDUAN SEWA", 3, 50);
    cout << "1. Anda diharuskan memilih ID dari salah satu lapangan" << endl;
    cout << "2. Anda diharuskan memilih bulan yang nantinya anda akan sewa pada bulan tersebut" << endl;
    cout << "3. Anda diharuskan memilih tanggal anda akan bermain" << endl;
    cout << "4. Anda diharuskan memilih durasi bermain anda" << endl;
    cout << "5. Anda diharuskan memilih jam mulai bermain anda" << endl;
    cout << "6. Anda diberikan pilihan untuk dapat meminjam perlengkapan tambahan" << endl;
    cout << "7. Jika anda meminjam maka selanjutnya anda akan diminta jumlah yang akan anda pinjam" << endl;
    cout << "8. Setelah itu semua anda diharuskan membayar pembayaran anda" << endl;
    cout << "9. Setelah membayar anda akan mendapatkan bukti pembayaran" << endl;
    cout << "10. Anda bermain pada waktu yang telah anda tentukan" << endl;
    cout << "11. Anda mengembalikan perlengkapan dan menyelesaikan penyewaan lapangan" << endl;
    oneLine(50);
    cout << "\nKetik '1' untuk lanjut dan '0' untuk kembali!" << endl;
    do
    {
        oneLine(50);
        cout << "\nPilih" << endl;
        cin >> lap;
        if (!isNumber(lap))
        {
            cout << "Hanya menerima angka!" << endl;
        }
        else if (lap == "0")
        {
            MainMenu();
        }
    } while (isNumber(lap) != true || lap != "0" && lap != "1");
    lap.clear();

    system("CLS");
    // MENDAPATKAN ID LAPANGAN
    ListLapangan();
    do
    {
        oneLine(50);
        cout << "\nPilih ID lapangan" << endl;
        cin >> lap;
        if (!isNumber(lap))
        {
            cout << "Hanya menerima angka!" << endl;
        }
        else if (!GetLapangan(stoi(lap)))
        {
            cout << "Data lapangan tidak tersedia untuk ID tersebut!" << endl;
        }
    } while (isNumber(lap) != true || GetLapangan(stoi(lap)) != true);

    system("CLS");
    getDetailLapangan(stoi(lap));
    do
    {
        cout << "Apakah anda ingin mengganti bulan?" << endl;
        cout << "[1] Ya" << endl;
        cout << "[2] Tidak (gunakan bulan sekarang)" << endl;
        cin >> choice;
        if (!isNumber(choice))
        {
            cout << "Hanya menerima angka!" << endl;
        }
        else if (choice != "1" && choice != "2")
        {
            cout << "Inputan tidak sesuai!" << endl;
        }
    } while (isNumber(choice) != true || choice != "1" && choice != "2");

    if (choice == "1")
    {
        oneLineText("PILIH BULAN", 50);
        cout << endl;
        for (int i = 0; i < 12; i++)
        {
            cout << "[" << i + 1 << "] " << calendar.month[i] << endl;
        }
        do
        {
            cout << "Masukan bulan\t: ";
            cin >> bulan;
            if (!isNumber(bulan))
            {
                cout << "Hanya menerima angka!" << endl;
            }
            else if (stoi(bulan) < 1 || stoi(bulan) > 12)
            {
                cout << "Bulan tidak valid!" << endl;
            }
        } while (isNumber(bulan) != true || stoi(bulan) < 1 || stoi(bulan) > 12);
    }

    system("CLS");
    getDetailLapangan(stoi(lap));
    do
    {
        cout << "Apakah anda ingin mengganti tahun?" << endl;
        cout << "[1] Ya" << endl;
        cout << "[2] Tidak (gunakan tahun sekarang)" << endl;
        cin >> choice;
        if (!isNumber(choice))
        {
            cout << "Hanya menerima angka!" << endl;
        }
        else if (choice != "1" && choice != "2")
        {
            cout << "Inputan tidak sesuai!" << endl;
        }
    } while (isNumber(choice) != true || choice != "1" && choice != "2");

    if (choice == "1")
    {
        system("CLS");
        oneLineText("PILIH TAHUN", 50);
        cout << endl;
        for (int i = 0; i < 10; i++)
        {
            cout << "[" << i + 1 << "] " << calendar.year[i] << "\t\t";
            for (int j = i + 10; j < 20; j++)
            {
                cout << "[" << j + 1 << "] " << calendar.year[j] << endl;
                break;
            }
        }

        do
        {
            cout << "Pilih tahun\t(co: 2022, 2023, 2024, dll): ";
            cin >> tahun;
            if (!isNumber(tahun))
            {
                cout << "Hanya menerima angka!" << endl;
            }
            else if (stoi(tahun) < 2022 || stoi(tahun) > 2041)
            {
                cout << "Masukan tahun yang benar!" << endl;
            }
        } while (isNumber(tahun) != true || stoi(tahun) < 2022 || stoi(tahun) > 2041);
    }

    system("CLS");
    GetCalendar(stoi(lap), stoi(bulan), stoi(tahun), 1);
    do
    {
        cout << "Masukan tanggal bermain\t: ";
        cin >> tanggal;
        if (!isNumber(tanggal))
        {
            cout << "Hanya menerima angka!" << endl;
        }
        else if (stoi(tanggal) < 1 || stoi(tanggal) > 31)
        {
            cout << "Masukan tanggal yang benar!" << endl;
        }
        else if (!isOccupiedDate(stoi(lap), tanggal, bulan, tahun))
        {
            cout << "Tanggal tersebut sudah penuh!" << endl;
        }
    } while (isOccupiedDate(stoi(lap), tanggal, bulan, tahun) != true || isNumber(tanggal) != true || stoi(tanggal) < 1 || stoi(tanggal) > 31);

    system("CLS");
    getLap(stoi(lap), timed, tanggal, bulan, tahun, waktuMulai);

    system("CLS");
    ListTool();
    do
    {
        oneLine(50);
        cout << "\nPilih ID perlengkapan atau '0' untuk tidak meminjam perlengkapan" << endl;
        cout << "ID\t: ";
        cin >> tool;
        if (tool == "0")
        {
            skip = true;
            break;
        }
        else if (!GetTool(stoi(tool)))
        {
            tool = "0";
            cout << "Data perlengkapan tidak tersedia untuk ID tersebut!" << endl;
        }
        else
        {
            do
            {
                oneLine(50);
                cout << "\nMasukan jumlah yang ingin disewa\t: ";
                cin >> jmlTool;
                if (isNumber(jmlTool) && stoi(jmlTool) > stoi(Tools[stoi(tool) - 1][4]))
                {
                    cout << "Jumlah barang yang disewa melebihi stok kami" << endl;
                }
                else if (stoi(jmlTool) < 1)
                {
                    cout << "Inputan tidak sesuai!" << endl;
                }
                else if (!isNumber(jmlTool))
                {
                    cout << "Hanya menerima angka!" << endl;
                }
            } while (isNumber(jmlTool) != true || stoi(jmlTool) < 1 || stoi(jmlTool) > stoi(Tools[stoi(tool) - 1][4]));
        }
    } while (GetTool(stoi(tool)) != true);

    system("CLS");
    getDetail(lap, tool, jmlTool, timed, tanggal, bulan, tahun, waktuMulai);
}

// SHOW JADWAL THAT USER HAS
void ShowCalendar()
{
    string choice, bulan, tahun;

    time_t ttime = time(0);
    tm *local_time = localtime(&ttime);
    tahun = to_string(1900 + local_time->tm_year);
    bulan = to_string(1 + local_time->tm_mon);

    system("CLS");
    autoLiner("JADWAL SAYA", 3, 50);
    cout << "Masukan bulan\t: " << endl;
    cout << "[1] Gunakan bulan sekarang " << calendar.month[stoi(bulan) - 1] << endl;
    cout << "[2] Pilih bulan manual" << endl;
    cout << "[0] Kembali" << endl;
    do
    {
        cin >> choice;
        if (!isNumber(choice))
        {
            cout << "Hanya menerima angka!" << endl;
        }
        else if (choice == "0")
        {
            MainMenu();
        }
        else if (stoi(choice) < 1 || stoi(choice) > 2)
        {
            cout << "Inputan tidak sesuai!" << endl;
        }
    } while (isNumber(choice) != true || stoi(choice) < 1 || stoi(choice) > 2);

    if (choice == "2")
    {
        system("CLS");
        oneLineText("PILIH BULAN", 50);
        cout << endl;
        for (int i = 0; i < 12; i++)
        {
            cout << "[" << i + 1 << "] " << calendar.month[i] << endl;
        }
        do
        {
            cout << "Masukan bulan\t: ";
            cin >> bulan;
            if (!isNumber(bulan))
            {
                cout << "Hanya menerima angka!" << endl;
            }
            else if (stoi(bulan) < 1 || stoi(bulan) > 12)
            {
                cout << "Bulan tidak valid!" << endl;
            }
        } while (isNumber(bulan) != true || stoi(bulan) < 1 || stoi(bulan) > 12);
    }

    system("CLS");
    oneLineText("TAHUN", 50);
    cout << "\nMasukan tahun\t: " << endl;
    cout << "[1] Gunakan tahun sekarang " << tahun << endl;
    cout << "[2] Pilih tahun manual" << endl;
    cout << "[0] Kembali" << endl;
    do
    {
        cin >> choice;
        if (!isNumber(choice))
        {
            cout << "Hanya menerima angka!" << endl;
        }
        else if (choice == "0")
        {
            MainMenu();
        }
        else if (stoi(choice) < 1 || stoi(choice) > 2)
        {
            cout << "Inputan tidak sesuai!" << endl;
        }
    } while (isNumber(choice) != true || stoi(choice) < 1 || stoi(choice) > 2);

    if (choice == "2")
    {
        system("CLS");
        oneLineText("PILIH TAHUN", 50);
        cout << endl;
        for (int i = 0; i < 10; i++)
        {
            cout << "[" << i + 1 << "] " << calendar.year[i] << "\t\t";
            for (int j = i + 10; j < 20; j++)
            {
                cout << "[" << j + 1 << "] " << calendar.year[j] << endl;
                break;
            }
        }
        do
        {
            cout << "Pilih tahun\t(co: 2022, 2023, 2024, dll): ";
            cin >> tahun;
            if (!isNumber(tahun))
            {
                cout << "Hanya menerima angka!" << endl;
            }
            else if (stoi(tahun) < 2022 || stoi(tahun) > 2041)
            {
                cout << "Masukan tahun yang benar!" << endl;
            }
        } while (isNumber(tahun) != true || stoi(tahun) < 2022 || stoi(tahun) > 2041);
    }

    system("CLS");
    GetCalendar(0, stoi(bulan), stoi(tahun), 2);
    system("pause");
    ShowCalendar();
}

// MENU UNTUK USER
int MainMenu()
{
    int choice;

    system("CLS");
    if (isAdmin())
    {
        AdminMainMenu();
    }
    cout << "Halo " << GetUsername() << "! Selamat datang kembali!" << endl;
    autoLiner("PILIH MENU", 3, 50);
    cout << "[1] Sewa lapangan\n"
         << "[2] Riwayat sewa\n"
         << "[3] Jadwal sewa\n"
         << "[4] Logout\n"
         << "[5] Exit\n";
    oneLine(50);
    cout << "\nPilih Menu\t: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        CreateSewa();
        system("pause");
        break;
    case 2:
        GetListTransaction(idAccount);
        system("pause");
        break;
    case 3:
        ShowCalendar();
        system("pause");
        break;
    case 4:
        isLogin = false;
        idAccount = ' ';
        cout << "Anda berhasil logout!" << endl;
        system("pause");
        Login();
        break;
    case 5:
        system("pause");
        exit(0);
        break;
    default:
        cout << "Pilihan tidak ada" << endl;
        system("pause");
        break;
    }
    return MainMenu();
}

// ADMIN
// MENU STIAP MENU
void AdminMenuLapangan(int &menu)
{
    system("CLS");
    autoLiner("MENU LAPANGAN", 3, 50);
    cout << "[1] Daftar Lapangan" << endl;
    cout << "[2] Tambah Lapangan" << endl;
    cout << "[3] Ubah Lapangan" << endl;
    cout << "[4] Hapus Lapangan" << endl;
    cout << "[5] Lihat Lapangan Dihapus" << endl;
    cout << "[0] Kembali" << endl
         << endl;
    do
    {
        cin >> menu;
        if (!isNumber(to_string(menu)))
        {
            cout << "Hanya menerima angka!" << endl;
        }
    } while (isNumber(to_string(menu)) != true);
}

// SHOW MENU LAPANGAN
void AdminLapangan()
{
    int menu;
    AdminMenuLapangan(menu);
    switch (menu)
    {
    case 1:
        system("CLS");
        ListLapangan();
        break;
    case 2:
        system("CLS");
        TambahLapangan();
        break;
    case 3:
        system("CLS");
        UbahLapangan();
        break;
    case 4:
        system("CLS");
        HapusLapangan();
        break;
    case 5:
        system("CLS");
        ListDeletedLapangan();
        break;
    case 0:
        AdminMainMenu();
        break;

    default:
        cout << "Inputan tidak sesuai!" << endl;
        break;
    }

    system("pause");
    AdminLapangan();
}
// ADMIN
// MENU PADA PERLENGKAPAN
void AdminMenuTool(int &menu)
{
    system("CLS");
    autoLiner("MENU PERLENGKAPAN", 3, 50);
    cout << "[1] Daftar Perlengkapan" << endl;
    cout << "[2] Tambah Perlengkapan" << endl;
    cout << "[3] Ubah Perlengkapan" << endl;
    cout << "[4] Hapus Perlengkapan" << endl;
    cout << "[5] Lihat Perlengkapan Dihapus" << endl;
    cout << "[0] Kembali" << endl
         << endl;
    do
    {
        cin >> menu;
        if (!isNumber(to_string(menu)))
        {
            cout << "Hanya menerima angka!" << endl;
        }
    } while (isNumber(to_string(menu)) != true);
}

// SHOW MENU TOOL
void AdminTool()
{
    int menu;
    AdminMenuTool(menu);
    switch (menu)
    {
    case 1:
        system("CLS");
        ListTool();
        system("pause");
        AdminTool();
        break;
    case 2:
        system("CLS");
        TambahTool();
        break;
    case 3:
        system("CLS");
        UbahTool();
        break;
    case 5:
        system("CLS");
        ListDeletedTool();
        break;
    case 4:
        system("CLS");
        HapusTool();
        break;
    case 0:
        AdminMainMenu();
        break;

    default:
        cout << "Inputan tidak sesuai!" << endl;
        break;
    }

    system("pause");
    AdminTool();
}

// TAMBAH LAPANGAN ADMIN
void TambahLapangan()
{
    string nama, harga, choice;
    autoLiner("TAMBAH LAPANGAN", 3, 50);
    cout << "Ketik '0' untuk kembali!" << endl;
    cout << "Masukan nama\t: ";
    do
    {
        cin.ignore();
        getline(cin, nama);

        if (nama == "0")
        {
            AdminLapangan();
        }

        if (nama.size() < 5)
        {
            cout << "Nama lapangan minimal 8 karakter!" << endl;
        }
    } while (nama.size() < 5);

    cout << "Masukan harga\t: ";
    do
    {
        cin >> harga;
        if (!isNumber(harga))
        {
            cout << "Hanya menerima angka!" << endl;
        }
    } while (isNumber(harga) != true);

    system("CLS");
    cout << "Nama\t: " << nama << endl;
    cout << "Harga\t: Rp" << currencyFormatter(stoi(harga)) << endl;
    cout << "Apakah data sudah benar?" << endl;
    cout << "[1] Ya" << endl;
    cout << "[2] Tidak" << endl;
    cout << "[0] Kembali ke Main menu" << endl;
    do
    {
        cin >> choice;
        if (!isNumber(choice))
        {
            cout << "Hanya menerima angka!" << endl;
        }
    } while (isNumber(choice) != true);

    switch (stoi(choice))
    {
    case 1:
        Lapangans.push_back({to_string(Lapangans.size() + 1), nama, harga, "1"});
        cout << "Data berhasil ditambahkan!" << endl;
        break;
    case 2:
        TambahLapangan();
        break;
    case 0:
        AdminLapangan();
        break;
    default:
        cout << "Inputan tidak sesuai!" << endl;
        break;
    }
}

// UBAH LAPANGAN ADMIN
void UbahLapangan()
{
    string lap, next, nama, harga, namaAwal, hargaAwal;
    int check = 0;
    system("CLS");
    cout << "Ketik '0' untuk kembali!" << endl;
    cout << "ID tersedia\t: ";
    for (int i = 0; i < Lapangans.size(); i++)
    {
        if (i + 1 == Lapangans.size())
        {
            cout << Lapangans[i][0];
        }
        else
        {
            cout << Lapangans[i][0] << ", ";
        }
    }
    cout << endl;
    cout << "Masukan ID lapangan\t: ";
    do
    {
        cin >> lap;
        if (!isNumber(lap))
        {
            cout << "Hanya menerima angka!" << endl;
        }
    } while (isNumber(lap) != true);

    system("CLS");
    for (int i = 0; i < Lapangans.size(); i++)
    {
        if (stoi(Lapangans[i][0]) == stoi(lap))
        {
            check++;
            lap = to_string(i);
            namaAwal = Lapangans[i][1];
            hargaAwal = Lapangans[i][2];
            cout << "Nama\t: " << namaAwal << endl;
            cout << "Harga\t: Rp" << currencyFormatter(stoi(hargaAwal)) << endl;
        }
    }
    if (check == 0)
    {
        AdminLapangan();
    }
    cout << "Apakah ingin melanjutkan dengan data ini?\n[1] Ya\n[2] Tidak\n[3] Kembali Kembali ke Main Menu\n";
    do
    {
        cin >> next;
        if (!isNumber(next))
        {
            cout << "Hanya menerima angka!" << endl;
        }
    } while (isNumber(next) != true);

    switch (stoi(next))
    {
    case 1:
        system("CLS");
        autoLiner("MASUKAN DATA", 3, 50);
        cout << "Nama Awal\t: " << namaAwal << endl;
        cout << "Nama\t: ";
        do
        {
            cin.ignore();
            getline(cin, nama);
            if (nama.size() < 5)
            {
                cout << "Nama tidak boleh kurang dari 5 karatker!" << endl;
            }
        } while (nama.size() < 5);

        cout << "Harga Awal\t: Rp" << currencyFormatter(stoi(hargaAwal)) << endl;
        cout << "Harga\t: ";
        do
        {
            cin >> harga;
            if (!isNumber(harga))
            {
                cout << "Hanya menerima angka!" << endl;
            }
        } while (isNumber(harga) != true);

        system("CLS");
        cout << "Nama\t: " << namaAwal << " -> " << nama << endl;
        cout << "Harga\t: Rp" << currencyFormatter(stoi(hargaAwal)) << " -> Rp" << currencyFormatter(stoi(harga)) << endl;
        cout << "Apakah data sudah benar?" << endl;
        cout << "[1] Ya" << endl;
        cout << "[2] Tidak" << endl;
        cout << "[0] Kembali ke Main menu" << endl;
        do
        {
            cin >> next;
            if (!isNumber(next))
            {
                cout << "Hanya menerima angka!" << endl;
            }
        } while (isNumber(next) != true);
        switch (stoi(next))
        {
        case 1:
            Lapangans[stoi(lap)][1] = nama;
            Lapangans[stoi(lap)][2] = harga;
            cout << "Data berhasil diubah!" << endl;
            break;
        case 2:
            UbahLapangan();
            break;
        case 3:
            AdminLapangan();
            break;

        default:
            cout << "Inputan tidak sesuai!" << endl;
            break;
        }
        break;
    case 2:
        UbahLapangan();
        break;
    case 3:
        AdminMainMenu();
        break;

    default:
        cout << "Inputan tidak sesuai!" << endl;
        break;
    }
}

// HAPUS LAPANGAN ADMIN
void HapusLapangan()
{
    string lap, next;
    int check;
    system("CLS");
    cout << "Ketik '0' untuk kembali!" << endl;
    cout << "ID tersedia\t: ";
    for (int i = 0; i < Lapangans.size(); i++)
    {
        if (i + 1 == Lapangans.size())
        {
            cout << Lapangans[i][0];
        }
        else
        {
            cout << Lapangans[i][0] << ", ";
        }
    }
    cout << endl;
    cout << "Masukan ID lapangan\t: ";
    do
    {
        cin >> lap;
        if (!isNumber(lap))
        {
            cout << "Hanya menerima angka!" << endl;
        }
    } while (isNumber(lap) != true);

    system("CLS");
    for (int i = 0; i < Lapangans.size(); i++)
    {
        if (stoi(Lapangans[i][0]) == stoi(lap))
        {
            check++;
            lap = to_string(i);
            cout << "Nama\t: " << Lapangans[i][1] << endl;
            cout << "Harga\t: Rp" << currencyFormatter(stoi(Lapangans[i][2])) << endl;
        }
    }
    if (check == 0)
    {
        AdminLapangan();
    }
    cout << "Apakah ingin hapus data ini?\n[1] Ya\n[2] Tidak\n[3] Kembali\n";
    do
    {
        cin >> next;
        if (!isNumber(next))
        {
            cout << "Hanya menerima angka!" << endl;
        }
    } while (isNumber(next) != true);

    switch (stoi(next))
    {
    case 1:
        Lapangans[stoi(lap)][3] = "2";
        cout << "Data berhasil dihapus!" << endl;
        break;
    case 2:
        HapusLapangan();
        break;
    case 3:
        AdminLapangan();
        break;

    default:
        cout << "Inputan tidak sesuai!" << endl;
        break;
    }
}

// TAMBAH PERLENGKAPAN ADMIN
void TambahTool()
{
    string nama, harga, min, stok, choice;
    autoLiner("TAMBAH PERLENGKAPAN", 3, 50);
    cout << "Ketik '0' untuk kembali!" << endl;
    cout << "Masukan nama\t: ";
    do
    {
        cin.ignore();
        getline(cin, nama);
        if (nama == "0")
        {
            AdminTool();
        }
        else if (nama.size() < 5)
        {
            cout << "Nama perlengkapan minimal 8 karakter!" << endl;
        }
    } while (nama.size() < 5);

    cout << "Masukan harga\t: ";
    do
    {
        cin >> harga;
        if (!isNumber(harga))
        {
            cout << "Hanya menerima angka!" << endl;
        }
    } while (isNumber(harga) != true);

    cout << "Masukan minimal sewa\t: ";
    do
    {
        cin >> min;
        if (!isNumber(min))
        {
            cout << "Hanya menerima angka!" << endl;
        }
    } while (isNumber(min) != true);

    cout << "Masukan stok\t: ";
    do
    {
        cin >> stok;
        if (!isNumber(stok))
        {
            cout << "Hanya menerima angka!" << endl;
        }
    } while (isNumber(stok) != true);

    system("CLS");
    cout << "================== RINGKASAN ==================" << endl;
    cout << "Nama\t: " << nama << endl;
    cout << "Harga\t: " << currencyFormatter(stoi(harga)) << endl;
    cout << "Minimal sewa\t: " << min << endl;
    cout << "Stok\t: " << stok << endl;
    cout << "Apakah data sudah benar?" << endl;
    cout << "[1] Ya" << endl;
    cout << "[2] Tidak" << endl;
    cout << "[0] Kembali ke Main menu" << endl;
    do
    {
        cin >> choice;
        if (!isNumber(choice))
        {
            cout << "Hanya menerima angka!" << endl;
        }
    } while (isNumber(choice) != true);

    switch (stoi(choice))
    {
    case 1:
        Tools.push_back({to_string(Tools.size() + 1), nama, harga, min, stok});
        cout << "Data berhasil ditambahkan!" << endl;
        break;
    case 2:
        TambahTool();
        break;
    case 0:
        AdminMainMenu();
        break;
    default:
        cout << "Inputan tidak sesuai!" << endl;
        break;
    }
}

// UBAH PERLENGKAPAN ADMIN
void UbahTool()
{
    // TOOL {ID, NAMA, HARGA, MINIMAL, STOK}
    string lap, next, nama, harga, min, stok, namaAwal, hargaAwal, minAwal, stokAwal;
    int check = 0;
    system("CLS");
    cout << "Ketik '0' untuk kembali!" << endl;
    cout << "ID tersedia\t: ";
    for (int i = 0; i < Tools.size(); i++)
    {
        if (i + 1 == Tools.size())
        {
            cout << Tools[i][0];
        }
        else
        {
            cout << Tools[i][0] << ", ";
        }
    }
    cout << endl;
    cout << "Masukan ID perlengkapan\t: ";
    do
    {
        cin >> lap;
        if (!isNumber(lap))
        {
            cout << "Hanya menerima angka!" << endl;
        }
    } while (isNumber(lap) != true);

    system("CLS");
    for (int i = 0; i < Tools.size(); i++)
    {
        if (stoi(Tools[i][0]) == stoi(lap))
        {
            check++;
            lap = to_string(i);
            namaAwal = Tools[i][1];
            hargaAwal = Tools[i][2];
            minAwal = Tools[i][3];
            stokAwal = Tools[i][4];
            cout << "Nama\t: " << namaAwal << endl;
            cout << "Harga\t: Rp" << currencyFormatter(stoi(hargaAwal)) << endl;
            cout << "Minimal sewa\t: " << minAwal << endl;
            cout << "Stok\t: " << stokAwal << endl;
        }
    }
    if (check == 0)
    {
        AdminTool();
    }
    cout << "Apakah ingin melanjutkan dengan data ini?\n[1] Ya\n[2] Tidak\n[3] Kembali Kembali ke Main Menu\n";
    do
    {
        cin >> next;
        if (!isNumber(next))
        {
            cout << "Hanya menerima angka!" << endl;
        }
    } while (isNumber(next) != true);
    switch (stoi(next))
    {
    case 1:
        system("CLS");
        autoLiner("MASUKAN DATA", 3, 50);
        cout << "Nama Awal\t: " << namaAwal << endl;
        cout << "Nama\t: ";
        do
        {
            cin.ignore();
            getline(cin, nama);
            if (nama.size() < 5)
            {
                cout << "Nama tidak boleh kurang dari 5 karatker!" << endl;
            }
        } while (nama.size() < 5);

        cout << "Harga Awal\t: Rp" << currencyFormatter(stoi(hargaAwal)) << endl;
        cout << "Harga\t: ";
        do
        {
            // cin.ignore();
            // getline(cin, harga);
            cin >> harga;
            if (!isNumber(harga))
            {
                cout << "Hanya menerima angka!" << endl;
            }
        } while (isNumber(harga) != true);

        cout << "Minimal sewa Awal\t: " << minAwal << "pc/s" << endl;
        cout << "Minimal sewa\t: ";
        do
        {
            // cin.ignore();
            // getline(cin, min);
            cin >> min;
            if (!isNumber(min))
            {
                cout << "Hanya menerima angka!" << endl;
            }
        } while (isNumber(min) != true);

        cout << "Stok Awal\t: " << stokAwal << "pc/s" << endl;
        cout << "Stok\t: ";
        do
        {
            // cin.ignore();
            // getline(cin, stok);
            cin >> stok;
            if (!isNumber(stok))
            {
                cout << "Hanya menerima angka!" << endl;
            }
        } while (isNumber(stok) != true);

        system("CLS");
        cout << "Nama\t: " << namaAwal << " -> " << nama << endl;
        cout << "Harga\t: Rp" << currencyFormatter(stoi(hargaAwal)) << " -> Rp" << currencyFormatter(stoi(harga)) << endl;
        cout << "Minimal sewa\t: " << minAwal << " -> " << min << endl;
        cout << "Stok\t: " << stokAwal << " pc/s"
             << " -> " << stok << " pc/s" << endl;
        cout << "Apakah data sudah benar?" << endl;
        cout << "[1] Ya" << endl;
        cout << "[2] Tidak" << endl;
        cout << "[0] Kembali ke Main menu" << endl;
        do
        {
            // cin >> next;
            cin.ignore();
            getline(cin, next);
            if (!isNumber(next))
            {
                cout << "Hanya menerima angka!" << endl;
            }
        } while (isNumber(next) != true);

        switch (stoi(next))
        {
        case 1:
            Tools[stoi(lap)][1] = nama;
            Tools[stoi(lap)][2] = harga;
            Tools[stoi(lap)][3] = min;
            Tools[stoi(lap)][4] = stok;
            cout << "Data berhasil diubah!" << endl;
            break;
        case 2:
            UbahTool();
            break;
        case 3:
            AdminTool();
            break;

        default:
            cout << "Inputan tidak sesuai!" << endl;
            break;
        }
        break;
    case 2:
        UbahTool();
        break;
    case 3:
        AdminMainMenu();
        break;

    default:
        cout << "Inputan tidak sesuai!" << endl;
        break;
    }
}

// HAPUS PERLENGKAPAN ADMIN
void HapusTool()
{
    string lap, next;
    int check;
    system("CLS");
    cout << "Ketik '0' untuk kembali!" << endl;
    cout << "ID tersedia\t: ";
    for (int i = 0; i < Tools.size(); i++)
    {
        if (i + 1 == Tools.size())
        {
            cout << Tools[i][0];
        }
        else
        {
            cout << Tools[i][0] << ", ";
        }
    }
    cout << endl;
    cout << "Masukan ID perlengkapan\t: ";
    do
    {
        cin >> lap;
        if (!isNumber(lap))
        {
            cout << "Hanya menerima angka!" << endl;
        }
    } while (isNumber(lap) != true);

    system("CLS");
    for (int i = 0; i < Tools.size(); i++)
    {
        if (stoi(Tools[i][0]) == stoi(lap))
        {
            check++;
            lap = to_string(i);
            cout << "Nama\t: " << Tools[i][1] << endl;
            cout << "Harga\t: Rp" << currencyFormatter(stoi(Tools[i][2])) << endl;
        }
    }
    if (check == 0)
    {
        AdminTool();
    }
    cout << "Apakah ingin hapus data ini?\n[1] Ya\n[2] Tidak\n[3] Kembali\n";
    do
    {
        cin >> next;
        if (!isNumber(next))
        {
            cout << "Hanya menerima angka!" << endl;
        }
    } while (isNumber(next) != true);

    switch (stoi(next))
    {
    case 1:
        Tools[stoi(lap)][5] = "2";
        cout << "Data berhasil dihapus!" << endl;
        break;
    case 2:
        HapusTool();
        break;
    case 3:
        AdminTool();
        break;

    default:
        cout << "Inputan tidak sesuai!" << endl;
        break;
    }
}

// MENU FOR ADMIN
int AdminMainMenu()
{
    int choice, menu = 0;

    system("CLS");
    if (!isAdmin())
    {
        MainMenu();
    }
    cout << "Halo " << GetUsername() << "! Selamat datang kembali!" << endl;
    autoLiner("PILIH MENU", 3, 50);
    cout << "[1] Data Lapangan\n"
         << "[2] Data Perlengkapan\n"
         << "[3] Daftar Transaksi\n"
         << "[4] Logout\n"
         << "[5] Exit\n";
    oneLine(50);
    cout << "\nPilih Menu\t: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        system("CLS");
        AdminLapangan();
        system("pause");
        break;
    case 2:
        system("CLS");
        AdminTool();
        system("pause");
        break;
    case 3:
        ListTransaksi();
        system("pause");
        break;
    case 4:
        isLogin = false;
        idAccount = ' ';
        cout << "Anda berhasil logout!" << endl;
        system("pause");
        Login();
        break;
    case 5:
        system("pause");
        exit(0);
        break;
    default:
        cout << "Pilihan tidak ada" << endl;
        system("pause");
        break;
    }
    return AdminMainMenu();
}

// MENDAPATKAN AKUN
int GetAccount(string username, string password)
{
    for (int i = 0; i < Account.size(); i++)
    {
        if (username == Account[i][1] && password == Account[i][3])
        {
            idAccount = stoi(Account[i][0]);
            return 1;
        }
        else if (i + 1 == Account.size())
        {
            if (username == "" || password == "")
            {
                return 3;
            }
            else if (username != Account[i][1] || password != Account[i][3])
            {
                return 2;
            }
        }
    }
}

// LOGIN SEBELUM MASUK KE PROGRAM
void Login()
{
    int ResultGA = 0, a = 5;
    string username = "", password = "";

    do
    {
        if (a > 1)
        {
            system("CLS");
            autoLiner("LOGIN", 3, 50);
            cout << "Silahkan login terlebih dahulu" << endl;
            cout << "Username\t: ";
            // cin.ignore();
            // getline(cin, username);
            cin >> username;
            cout << "Password\t: ";
            // cin.ignore();
            // getline(cin, password);
            cin >> password;
            ResultGA = GetAccount(username, password);

            if (ResultGA == 1)
            {
                isLogin = true;
                cout << endl;
                cout << "Login sukses!" << endl;
                system("pause");
                if (isAdmin())
                {
                    AdminMainMenu();
                }
                else
                {
                    MainMenu();
                }
                break;
            }
            else if (ResultGA == 2)
            {
                cout << "Username atau Password anda salah!" << endl;
                cout << "Kesempatan anda tersisa " << a - 1 << " kali lagi" << endl;
                system("pause");
            }
            else if (ResultGA == 3)
            {
                cout << "Username atau Password tidak boleh kosong!" << endl;
                cout << "Kesempatan anda tersisa " << a - 1 << " kali lagi" << endl;
                system("pause");
            }
        }
        else
        {
            system("CLS");
            cout << "Anda telah 5 kali gagal, coba lain kali" << endl;
            system("pause");
        }
        a--;
    } while (a != 0);
}

// REGISTER JIKA TIDAK ADA AKUN
void Register()
{
    string id = to_string(Account.size() + 1), username = "", email = "", password = "", confpassword = "";
    bool all;

    // do
    // {
    system("CLS");
    autoLiner("REGISTRASI", 3, 50);
    oneLineText("INFO", 50);
    cout << "\n1. Username tidak boleh mengandung spasi\t" << endl;
    cout << "2. E-mail tidak boleh sama\t\t\t" << endl;
    cout << "3. Password minimal 8 karakter\t\t"
         << endl;
    oneLine(50);
    cout << "\nMasukan username\t: ";
    cin.ignore();
    getline(cin, username);
    // DELETING WHITESPACE
    username.erase(remove_if(username.begin(), username.end(), ::isspace),
                   username.end());

    do
    {
        cout << "Masukan e-mail\t\t: ";
        cin >> email;
        if (GetEmail(email))
        {
            cout << "E-mail sudah digunakan!" << endl;
        }
    } while (GetEmail(email) != false);

    int confirmed = 0;
    do
    {
        confirmed = 0;
        cout << "Masukan password\t: ";
        cin >> password;
        if (password.length() < 8)
        {
            confirmed++;
            cout << "Password tidak boleh kurang dari 8 karakter!" << endl;
        }
    } while (confirmed > 0);

    do
    {
        confirmed = 0;
        cout << "Masukan konfirmasi password\t: ";
        cin >> confpassword;
        if (password != confpassword)
        {
            confirmed++;
            cout << "Password dengan konfirmasi password tidak cocok!" << endl;
        }
    } while (confirmed > 0);

    // } while (all != false);
    Account.push_back({id, username, email, password, "2"});
    cout << endl;
    cout << "Anda berhasil registrasi!" << endl;
    system("pause");
    Login();
}

// FUNGSI UTAMA
int main()
{
    // MEMBUAT DATA DARI CLASS TOOLS
    string lanjut;

    system("CLS");
    autoLiner("APLIKASI FUTSIN", 3, 50);
    cout << "[1] Login\n[2] Register\n[3] Exit" << endl;
    do
    {
        cin >> lanjut;
        if (!isNumber(lanjut))
        {
            cout << "Hanya menerima angka!" << endl;
        }
        else if (stoi(lanjut) < 1 || stoi(lanjut) > 3)
        {
            cout << "Inputan tidak sesuai!" << endl;
        }
    } while (isNumber(lanjut) != true || stoi(lanjut) < 1 || stoi(lanjut) > 3);

    switch (stoi(lanjut))
    {
    case 1:
        if (!isLogin)
        {
            Login();
        }
        break;
    case 2:
        Register();
        break;
    case 3:
        cout << "Selamat tinggal!" << endl;
        exit(0);
        break;

    default:
        cout << "Input tidak sesuai!" << endl;
        break;
    }

    system("pause");
    return 0;
}