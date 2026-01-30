namespace Resources{
    class Storage {
    public:
        virtual void read() = 0;
        virtual void write() = 0;
        virtual ~Storage() {};
    };

    class DiskStorage :public Storage {
        void read() override { std::cout << "Reading data from the disk...\n"; }
        void write() override { std::cout << "Writing data to the disk...\n"; }
        ~DiskStorage() { std::cout << "Storage deleted from the disk.\n"; }
    };

    class MemoryStorage :public Storage {
        void read() override { std::cout << "Reading data from the memory...\n"; }
        void write()override { std::cout << "Writing data to the memory...\n\n"; }
        ~MemoryStorage() { std::cout << "Storage deleted from the memory.\n"; }
    };

    class ComputeResource {
    public:
        virtual void compute() = 0;
        virtual ~ComputeResource() {};
    };

    class TPU :public ComputeResource {
    public:
        void compute() override { std::cout << "TPU is performing the computation...\n"; }
    };

    class Cluster {
    private:
        std::vector<std::unique_ptr<ComputeResource>> resources;
    public:
        void addResource(std::unique_ptr<ComputeResource> r) {
            resources.push_back(std::move(r));
        }

        void runAll() {
            for (auto& r : resources) {
                r->compute();
            }
        }
    };
}
