#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <numeric>
#include <random>
using namespace std;

vector<int> primeto100 = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
// strategy, singleton, observer

class GameStrategy{
public:
    vector<int> receivedNumbers;
    string name = "";
    virtual bool execStrategy() = 0;
};

class FiveEvenStrat : public GameStrategy{
public:
    FiveEvenStrat(){name ="Cinco números pares";}
    bool execStrategy(){
        int evens = 0;
        for (int i = 0; i < receivedNumbers.size(); i++){
            if ( receivedNumbers[i] % 2 == 0)
                evens++;
        }
        if (evens >= 5){
            for (auto i: receivedNumbers)
                std::cout << i << ", ";
            std::cout << "entonces el ganador es: " << name<< "\n";
            return true;
        }
        else
            return false;
    }
};

class FiveUnevenStrat : public GameStrategy{
public:
    FiveUnevenStrat(){name ="Cinco números impares";}
    bool execStrategy(){
        int unevens = 0;
        for (int i = 0; i < receivedNumbers.size(); i++){
            if ( receivedNumbers[i] % 2 != 0)
                unevens++;
        }
        if (unevens >= 5){
            for (auto i: receivedNumbers)
                std::cout << i << ", ";
            std::cout << "entonces el ganador es: " << name<< "\n";
            return true;

        }
        else
            return false;
    }
};

class OnePrimeStrat : public GameStrategy{
public:
    OnePrimeStrat(){name ="Un número primo";}
    bool execStrategy(){
        for (int i = 0; i < receivedNumbers.size(); i++){
            if (count(primeto100.begin(), primeto100.end(), receivedNumbers[i])){
                for (auto i: receivedNumbers)
                    std::cout << i << ", ";
                std::cout << "entonces el ganador es: " << name<< "\n";
                return true;
            }
        }
        return false;
    }
};

class ThreeMultipleTenStrat : public GameStrategy{
public:
    ThreeMultipleTenStrat(){name ="Tres números múltiplos de 10";}
    bool execStrategy(){
        int multiples = 0;
        for (int i = 0; i < receivedNumbers.size(); i++){
            if ( receivedNumbers[i] % 10 == 0)
                multiples++;
        }
        if (multiples >= 3){
            for (auto i: receivedNumbers)
                std::cout << i << ", ";
            std::cout << "entonces el ganador es: " << name<< "\n";

            return true;
        
        }
        else
            return false;
    }
};

class TwoMultipleTwentyFiveStrat : public GameStrategy{
public:
    TwoMultipleTwentyFiveStrat(){name ="Dos números múltiplos de 25";}
    bool execStrategy(){
        int multiples = 0;
        for (int i = 0; i < receivedNumbers.size(); i++){
            if ( receivedNumbers[i] % 25 == 0)
                multiples++;
        }
        if (multiples >= 2){
            for (auto i: receivedNumbers)
                std::cout << i << ", ";
            std::cout << "entonces el ganador es: " << name<< "\n";
            return true;
        }else
            return false;
    }
};

class Observer{
    public:
        virtual bool update(int value) = 0;
};

class GameStrategyObserver : public Observer{
    private:
        GameStrategy* strat;
    public:
        GameStrategyObserver(GameStrategy* _strat){
            strat = _strat;
        }
        bool update(int value) override {
            strat->receivedNumbers.push_back(value);
            return strat->execStrategy();
        }
};

// Subject
class GameSubject{
private:
    list<Observer*> observerList;
public:

    void registerObserver(Observer* _o){
        observerList.push_back(_o);
    }
    void removeObserver(){
        observerList.pop_back();
    }
    bool notifyObserver(int newRNGNumber){
        for (auto & i : observerList) {
            if (i->update(newRNGNumber) == true)
                return true;
        } 
        return false;
    }
};

//- SINGLETON PATTERN -//

// Application / Client
class Context{
private:
    Context(){};
    GameSubject CurrentSubject;

    vector<int> numberGenVector(int n){
        vector<int> numbers(n);
        iota(numbers.begin(), numbers.end(), 1);

        random_device rd;
        mt19937 g(rd());

        shuffle(numbers.begin(), numbers.end(), g);
        return numbers;
    }

public:
    Context(const Context&) = delete; 

    static Context& getInstance(){ 
        static Context Instance;
        return Instance;
    }

     void addPlayer(GameStrategy* strat){
        CurrentSubject.registerObserver(new GameStrategyObserver(strat));
    }

    void start(){
        vector<int> sequence = numberGenVector(100);
        while (!sequence.empty()){
            int current = sequence.back();
            sequence.pop_back();

            if (CurrentSubject.notifyObserver(current))
                break;
        }
        cout<< "Programa terminado.";
    }

};


int main(){
    Context& App = Context::getInstance();
    App.addPlayer(new FiveEvenStrat());
    App.addPlayer(new FiveUnevenStrat());
    App.addPlayer(new OnePrimeStrat());
    App.addPlayer(new ThreeMultipleTenStrat());
    App.addPlayer(new TwoMultipleTwentyFiveStrat());
    App.start();
}