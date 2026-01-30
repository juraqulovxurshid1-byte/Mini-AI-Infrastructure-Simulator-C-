#include<iostream>
#include<vector>
#include<stdexcept>    //for invalid_argument
#include<string>
#include<memory>       //for unique_ptr

int main() {
    std::vector<std::unique_ptr<Resources::Storage>> storageDevices;
    storageDevices.push_back(std::make_unique<Resources::DiskStorage>());
    storageDevices.push_back(std::make_unique<Resources::MemoryStorage>());

    for (auto& device : storageDevices) {
        device->read();
        device->write();
    }

    Resources::Storage* s = new Resources::DiskStorage();
    delete s;

    auto model1 = std::make_unique<AIInfra::GPU>("Unknown", 1);
    auto model2 = std::make_unique<AIInfra::GPU>("Nvidia RTX 3060", 6);

    model1->showInfo();
    std::cout << std::endl;
    model2->showInfo();
    std::cout << std::endl;

    try {
        auto model3 = std::make_unique<AIInfra::GPU>("ACM", -2);
        model3->showInfo();
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    AIInfra::GPUManager manager;
    manager.addGPU(std::move(model1));
    manager.addGPU(std::move(model2));
    manager.showAll();

    std::cout << "Total GPUs: " << AIInfra::GPU::getTotalGPUs() << std::endl;

    AIInfra::Model MyModel("VisionNet",0.80);
    AIInfra::GPU trainingGpu("Nvidia RTX 4090", 24);
    AIInfra::ModelTrainer trainer1;
    trainer1.trainModel(trainingGpu);

    AIInfra::Model model("ResNet",90.2);
    AIInfra::ModelInspector::inspect(model);
   
    AIInfra::Model m;
    try {
		m.setAccuracy(0.92);
		m.setAccuracy(1.5); // This will throw an exception
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
	std::cout << "Accuracy: " << m.getAccuracy() << "%" << std::endl;

    if (!AIInfra::trySetAccuracy(m, 1.2)) {
        std::cout << "Invalid accuracy value.\n";
    }

    if (AIInfra::trySetAccuracy(m, 0.85)) {
		std::cout << "Accuracy updated" << std::endl;
    }

	std::cout << "Accuracy: " << m.getAccuracy() << "%" << std::endl;

    Resources::Cluster cluster;

    cluster.addResource(std::make_unique<AIInfra::GPU>());
    cluster.addResource(std::make_unique<Resources::TPU>());

    cluster.runAll();
};
