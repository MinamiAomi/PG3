#include <iostream>
#include <list>
#include <iomanip>

int main() {

    std::list<const char*> yamanoteLineStations = {
        "Tokyo",
        "Kanda",
        "Akihabara",
        "Okachimachi",
        "Ueno",
        "Uguisudani",
        "Nippori",
        /*"Nishi-Nippori",*/
        "Tabata",
        "Komagome",
        "Sugamo",
        "Otsuka",
        "Ikebukuro",
        "Mejiro",
        "Takadanobaba",
        "Shin-Okubo",
        "Shinjuku",
        "Yoyogi",
        "Harajuku",
        "Shibuya",
        "Ebisu",
        "Meguro",
        "Gotanda",
        "Osaki",
        "Shinagawa",
        /*"TakanawaGateway",*/
        "Tamachi",
        "Hamamatsucho",
        "Shimbashi",
        "Yurakucho"
    };

    auto PrintYamanoteLineStations = [&yamanoteLineStations](int year) {
        std::cout << "-------------------------------------------------" << std::endl;
        std::cout << "List of Yamanote Line Stations in " << year << "\n";
        for (int i = 1; auto & station : yamanoteLineStations) {
            std::cout << "JY " << std::setw(2) << std::setfill('0') << i << " : " << station << "\n";
            i++;
        }
        std::cout << "-------------------------------------------------" << std::endl;
    };

    PrintYamanoteLineStations(1970);

    // 田端の前に西日暮里を追加
    auto tabataIterator = std::find(yamanoteLineStations.begin(), yamanoteLineStations.end(), "Tabata");
    yamanoteLineStations.insert(tabataIterator, "Nishi-Nippori");

    PrintYamanoteLineStations(2019);

    // 田町の前に高輪ゲートウェイを追加
    auto tamachiIterator = std::find(yamanoteLineStations.begin(), yamanoteLineStations.end(), "Tamachi");
    yamanoteLineStations.insert(tamachiIterator, "TakanawaGateway");

    PrintYamanoteLineStations(2022);


    std::cout << std::endl << "このプログラムは終了しました。" << std::endl;

    (void)std::getchar();
    return 0;
}