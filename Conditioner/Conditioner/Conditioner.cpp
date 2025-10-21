#include "Conditioner.h"
#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
#include <algorithm>

Conditioner::Conditioner() : Conditioner("", "", 0, 25, "авто", 2023) {}

Conditioner::Conditioner(std::string brand, std::string model, double weight, int temperature, std::string mode, int year)
    : brand_(brand), model_(model), weight_(weight), temperature_(temperature), mode_(mode), year_(year) {
    temperatureHistory_.push_back(temperature);
}

void Conditioner::setBrand(const std::string& brand) { brand_ = brand; }
void Conditioner::setModel(const std::string& model) { model_ = model; }
void Conditioner::setWeight(double weight) { weight_ = weight; }
void Conditioner::setTemperature(int temperature) {
    temperature_ = temperature;
    temperatureHistory_.push_back(temperature);
}
void Conditioner::setMode(const std::string& mode) { mode_ = mode; }
void Conditioner::setYear(int year) { year_ = year; }

std::string Conditioner::getBrand() const { return brand_; }
std::string Conditioner::getModel() const { return model_; }
double Conditioner::getWeight() const { return weight_; }
int Conditioner::getTemperature() const { return temperature_; }
std::string Conditioner::getMode() const { return mode_; }
int Conditioner::getYear() const { return year_; }

void Conditioner::adjust(const std::string& newMode, int newTemperature) {
    mode_ = newMode;
    if (newMode == "охлаждение" && newTemperature != -1) {
        setTemperature(newTemperature);
    }
}

double Conditioner::averageTemperatureChange() const {
    if (temperatureHistory_.size() < 2) return 0;
    std::vector<int> differences;
    std::adjacent_difference(temperatureHistory_.begin(), temperatureHistory_.end(), std::back_inserter(differences));
    return std::accumulate(differences.begin() + 1, differences.end(), 0.0,
        [](double sum, int diff) { return sum + std::abs(diff); }) / (differences.size() - 1);
}

void Conditioner::serialize() const {
    serialize("conditioner.txt");
}

void Conditioner::serialize(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << brand_ << '\n' << model_ << '\n' << weight_ << '\n'
            << temperature_ << '\n' << mode_ << '\n' << year_ << '\n';
        file.close();
    }
}

void Conditioner::deserialize() {
    deserialize("conditioner.txt");
}

void Conditioner::deserialize(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::getline(file, brand_);
        std::getline(file, model_);
        file >> weight_ >> temperature_;
        file.ignore();
        std::getline(file, mode_);
        file >> year_;
        file.close();
    }
}

void Conditioner::printInfo() const {
    std::cout << brand_ << " " << model_ << " : ";
    std::cout << "Температура: " << temperature_ << "°C, ";
    std::cout << "Режим: " << mode_ << ", ";
    std::cout << "Среднее изменение температуры: " << averageTemperatureChange() << "°C" << std::endl;
}