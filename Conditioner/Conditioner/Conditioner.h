#include <vector>
#include <string>

class Conditioner {
public:
    Conditioner();
    Conditioner(std::string brand, std::string model, double weight, int temperature, std::string mode, int year); // конструктор с параметрами

    void setBrand(const std::string& brand);
    void setModel(const std::string& model);
    void setWeight(double weight);
    void setTemperature(int temperature);
    void setMode(const std::string& mode);
    void setYear(int year);

    std::string getBrand() const;
    std::string getModel() const;
    double getWeight() const;
    int getTemperature() const;
    std::string getMode() const;
    int getYear() const;

    void adjust(const std::string& newMode, int newTemperature = -1);
    double averageTemperatureChange() const;

    void serialize() const;
    void serialize(const std::string& filename) const;
    void deserialize();
    void deserialize(const std::string& filename);

    void printInfo() const;

private:
    std::string brand_;
    std::string model_;
    double weight_;
    int temperature_;
    std::string mode_;
    int year_;
    std::vector<int> temperatureHistory_;
};