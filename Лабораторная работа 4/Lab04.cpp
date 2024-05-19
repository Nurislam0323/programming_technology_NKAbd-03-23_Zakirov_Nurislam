#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>


struct Car {
    int id;
    std::string make;
    std::string model;
    int year;
    std::string owner;
};


class CarDatabase {
private:
    std::vector<Car> cars;
    std::string filename;

    void loadFromFile() {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Unable to open file " << filename << std::endl;
            return;
        }
        cars.clear();
        std::string line;
        while (getline(file, line)) {
            std::istringstream ss(line);
            Car car;
            ss >> car.id >> car.make >> car.model >> car.year;
            ss.ignore();
            getline(ss, car.owner);
            cars.push_back(car);
        }
        file.close();
    }

    void saveToFile() {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Unable to open file " << filename << std::endl;
            return;
        }
        for (const auto& car : cars) {
            file << car.id << " " << car.make << " " << car.model << " " << car.year << " " << car.owner << "\n";
        }
        file.close();
    }

public:
    CarDatabase(const std::string& file) : filename(file) {
        loadFromFile();
    }

    void addCar(const Car& car) {
        cars.push_back(car);
        saveToFile();
    }

    void editCar(int id, const Car& updatedCar) {
        for (auto& car : cars) {
            if (car.id == id) {
                car = updatedCar;
                saveToFile();
                return;
            }
        }
        std::cerr << "Car with ID " << id << " not found." << std::endl;
    }

    void deleteCar(int id) {
        auto it = std::remove_if(cars.begin(), cars.end(), [id](const Car& car) { return car.id == id; });
        if (it != cars.end()) {
            cars.erase(it, cars.end());
            saveToFile();
        }
        else {
            std::cerr << "Car with ID " << id << " not found." << std::endl;
        }
    }

    void searchCar(int id) const {
        for (const auto& car : cars) {
            if (car.id == id) {
                std::cout << "ID: " << car.id << ", Make: " << car.make << ", Model: " << car.model
                    << ", Year: " << car.year << ", Owner: " << car.owner << std::endl;
                return;
            }
        }
        std::cerr << "Car with ID " << id << " not found." << std::endl;
    }

    void displayAll() const {
        for (const auto& car : cars) {
            std::cout << "ID: " << car.id << ", Make: " << car.make << ", Model: " << car.model
                << ", Year: " << car.year << ", Owner: " << car.owner << std::endl;
        }
    }
};

int main() {
    CarDatabase db("cars.txt");

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Car\n";
        std::cout << "2. Edit Car\n";
        std::cout << "3. Delete Car\n";
        std::cout << "4. Search Car\n";
        std::cout << "5. Display All Cars\n";
        std::cout << "6. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        if (choice == 6) break;

        switch (choice) {
        case 1: {
            Car car;
            std::cout << "Enter ID: "; std::cin >> car.id;
            std::cout << "Enter Make: "; std::cin >> car.make;
            std::cout << "Enter Model: "; std::cin >> car.model;
            std::cout << "Enter Year: "; std::cin >> car.year;
            std::cin.ignore();
            std::cout << "Enter Owner: "; std::getline(std::cin, car.owner);
            db.addCar(car);
            break;
        }
        case 2: {
            int id;
            std::cout << "Enter ID of the car to edit: "; std::cin >> id;
            Car car;
            std::cout << "Enter new Make: "; std::cin >> car.make;
            std::cout << "Enter new Model: "; std::cin >> car.model;
            std::cout << "Enter new Year: "; std::cin >> car.year;
            std::cin.ignore();
            std::cout << "Enter new Owner: "; std::getline(std::cin, car.owner);
            car.id = id;
            db.editCar(id, car);
            break;
        }
        case 3: {
            int id;
            std::cout << "Enter ID of the car to delete: "; std::cin >> id;
            db.deleteCar(id);
            break;
        }
        case 4: {
            int id;
            std::cout << "Enter ID of the car to search: "; std::cin >> id;
            db.searchCar(id);
            break;
        }
        case 5:
            db.displayAll();
            break;
        default:
            std::cerr << "Invalid option, please try again.\n";
        }
    }

    return 0;
}
