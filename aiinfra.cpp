namespace AIInfra {
    class GPU : public Resources :: ComputeResource {
        static int TotalGPUs;
    private:
        std::string name;
        int memoryGB;
        double frequencyGHz;
    public:
        GPU() : name("unknown"), memoryGB(1), frequencyGHz(1) { TotalGPUs++; }

        GPU(const std::string& n, const int m)
            : name(n), memoryGB(m), frequencyGHz(1)
        {
            if (m <= 0) throw std::invalid_argument("Memory can't be negative");
            TotalGPUs++;
        }

        std::string getName() const { return name; }
        int getMemoryGB() const { return memoryGB; }
        double getFrequencyGHz() const { return frequencyGHz; }

        void setFrequencyGHz(double f) {
            if (f <= 0)
                throw std::invalid_argument("Frequency can't be negative");
            frequencyGHz = f;
        }

        void showInfo() const {
            std::cout << "Name: " << name
                << "\nMemoryGB: " << memoryGB
                << "\nFrequencyGHz: " << frequencyGHz << std::endl;
        }

        static int getTotalGPUs() { return TotalGPUs; }

        void compute() override { std::cout << "GPU " << name << " is performing the computation...\n"; }

        ~GPU() { TotalGPUs--; }
    };

    int GPU::TotalGPUs = 0;


    class GPUManager {
    private:
        std::vector<std::unique_ptr<GPU>> gpus;
    public:
        void addGPU(std::unique_ptr<GPU> gpu) { gpus.push_back(std::move(gpu)); }
        void showAll() const {
            for (const auto& g : gpus) g->showInfo();
        }
    };

    class Model {
    private:
        std::string name;
        double accuracy = 0.0;
        friend class ModelInspector;
    public:
		Model() :name("unknown"), accuracy(0.0) {};

        Model(const std::string& n,const double a) :name(n), accuracy(a) {};
        
        void setAccuracy(double a) {
            if (a < 0.0 || a>1.0)
                throw std::invalid_argument("Accuracy must be between 0 and 100");
			accuracy = a;
        }

        double getAccuracy() const { return accuracy; };
    };

    bool trySetAccuracy(Model& m, double a) {
        if (a < 0.0 || a>1.0) return false;
        m.setAccuracy(a);
        return true;
    }

    class ModelTrainer {
    public:
        void trainModel(Resources::ComputeResource& resource) {
            resource.compute();
            std::cout << "Training model..." << std::endl;
        }
    };

    class ModelInspector {
    public:
        static void inspect(Model& m) {
            std::cout << "Model name: " << m.name << '\n';
			std::cout << "Model accuracy: " << m.accuracy << "%\n";
        };
    };
}
