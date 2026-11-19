#include <iostream>
#include <string>
#include <vector>

class TariffPlan {
protected:
    int id;
    std::string name;
    double baseFee;

public:
    TariffPlan(int id = 0, const std::string& name = "None", double baseFee = 0.0)
        : id(id), name(name), baseFee(baseFee) {}

    virtual ~TariffPlan() = default;

    int getId() const { return id; }
    void setId(int newId) { id = newId; }

    std::string getName() const { return name; }
    void setName(const std::string& newName) { name = newName; }

    double getBaseFee() const { return baseFee; }
    void setBaseFee(double newFee) { baseFee = (newFee >= 0) ? newFee : 0.0; }

    virtual double calculateMonthlyCost() const = 0;

    virtual void printInfo() const {
        std::cout << "ID: " << id << " | Name: " << name << " | Base fee: " << baseFee;
    }
};

class MobileTariff : virtual public TariffPlan {
protected:
    int minutes;
    int gigabytes;
    int sms;

public:
    MobileTariff(int id, const std::string& name, double baseFee, int minutes, int gigabytes, int sms)
        : TariffPlan(id, name, baseFee), minutes(minutes), gigabytes(gigabytes), sms(sms) {}

    ~MobileTariff() override = default;

    int getMinutes() const { return minutes; }
    void setMinutes(int newMinutes) { minutes = newMinutes; }

    int getGigabytes() const { return gigabytes; }
    void setGigabytes(int newGb) { gigabytes = newGb; }

    int getSms() const { return sms; }
    void setSms(int newSms) { sms = newSms; }

    double calculateMonthlyCost() const override {
        return baseFee + (gigabytes * 0.25) + (minutes * 0.01);
    }

    void printInfo() const override {
        TariffPlan::printInfo();
        std::cout << " | Total: " << calculateMonthlyCost()
                  << " | Min: " << minutes << ", GB: " << gigabytes << ", SMS: " << sms << '\n';
    }
};

class InternetTariff : virtual public TariffPlan {
protected:
    int speedMbps;
    bool hasStaticIp;

public:
    InternetTariff(int id, const std::string& name, double baseFee, int speedMbps, bool hasStaticIp)
        : TariffPlan(id, name, baseFee), speedMbps(speedMbps), hasStaticIp(hasStaticIp) {}

    ~InternetTariff() override = default;

    int getSpeedMbps() const { return speedMbps; }
    void setSpeedMbps(int newSpeed) { speedMbps = newSpeed; }

    bool getHasStaticIp() const { return hasStaticIp; }
    void setHasStaticIp(bool staticIp) { hasStaticIp = staticIp; }

    double calculateMonthlyCost() const override {
        double staticIpFee = hasStaticIp ? 5.0 : 0.0;
        return baseFee + (speedMbps * 0.05) + staticIpFee;
    }

    void printInfo() const override {
        TariffPlan::printInfo();
        std::cout << " | Total: " << calculateMonthlyCost()
                  << " | Speed: " << speedMbps << " Mbps, Static IP: " << (hasStaticIp ? "Yes" : "No") << '\n';
    }
};

class ComboTariff : public MobileTariff, public InternetTariff {
private:
    double discountPercent;

public:
    ComboTariff(int id, const std::string& name, double baseFee,
                int minutes, int gigabytes, int sms,
                int speedMbps, bool hasStaticIp, double discountPercent)
        : TariffPlan(id, name, baseFee),
          MobileTariff(id, name, baseFee, minutes, gigabytes, sms),
          InternetTariff(id, name, baseFee, speedMbps, hasStaticIp),
          discountPercent(discountPercent) {}

    ~ComboTariff() override = default;

    double getDiscountPercent() const { return discountPercent; }
    void setDiscountPercent(double newDiscount) {
        discountPercent = (newDiscount >= 0 && newDiscount <= 100) ? newDiscount : 0.0;
    }

    double calculateMonthlyCost() const override {
        double mobilePart = (gigabytes * 0.25) + (minutes * 0.01);
        double internetPart = (speedMbps * 0.05) + (hasStaticIp ? 5.0 : 0.0);
        double total = baseFee + mobilePart + internetPart;
        return total * (1.0 - discountPercent / 100.0);
    }

    void printInfo() const override {
        TariffPlan::printInfo();
        std::cout << " | Total: " << calculateMonthlyCost()
                  << " | Min: " << minutes << ", GB: " << gigabytes << ", SMS: " << sms
                  << ", Speed: " << speedMbps << " Mbps, Static IP: " << (hasStaticIp ? "Yes" : "No")
                  << ", Discount: " << discountPercent << "%\n";
    }
};

int main() {
    std::vector<TariffPlan*> tariffs;

    tariffs.push_back(new MobileTariff(101, "Unlimited+", 25.0, 500, 30, 100));
    tariffs.push_back(new InternetTariff(202, "Fiber 200", 30.0, 200, true));
    tariffs.push_back(new ComboTariff(303, "All Inclusive MAX", 45.0, 1000, 50, 200, 300, true, 15.0));

    std::cout << "Tariff plans:\n";
    for (size_t i = 0; i < tariffs.size(); ++i) {
        tariffs[i]->printInfo();
    }

    std::cout << "\nUpdating combo tariff:\n";
    ComboTariff* combo = dynamic_cast<ComboTariff*>(tariffs[2]);
    if (combo != nullptr) {
        combo->setDiscountPercent(25.0);
        combo->setSpeedMbps(500);
        combo->printInfo();
    }

    for (TariffPlan* ptr : tariffs) {
        delete ptr;
    }
    tariffs.clear();

    return 0;
}