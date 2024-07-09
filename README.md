# Discrete-Event Simulation of Restaurant

This project aims to create a simulation of a Shawarma restaurant, focusing on replicating its operations. The main goal is to obtain the average queue length and average employee time utilization for efficiency estimation reasons based on specified properties of the restaurant.

## Restaurant model

The simulation is build in accordance to the following model.

![SimulationDiagram](https://github.com/nett-things/simulation-techniques/assets/112755339/a4c42c2b-47b7-48fa-afe6-a62780c3fbdd)

The simulation includes stands that provide sliced chicken and beef for wraps. In the simulation, customers arrive at regular intervals. They randomly choose between beef or chicken wraps. The customers are then placed in separate queues based on their choice. The simulation also includes employees responsible for making the wraps. They serve customers based on availability and the meat available in the respective queues. Each wrap requires 1 unit of meat. The time taken to serve a customer is predetermined.

The in-depth description of the simulation is specified in `project_description.pdf`. This simulation is configured for the following strategies described in the PDF:

| Meat slicing strategy  | Wrapping service strateg | Simulation method | Parameters |
| :---: | :---: | :---: | :---: |
| P1  | S1  | MT1 | D2 |

## Usage

The simulation is operated by class `Restaurant`, which is also aliased as `Simulation` for clarity.  Creating a new simulation is done by simply creating a new instance of this class and specifying `max_time`. 

``` C++
Simulation sim(10000);
```

If we want to collect data every time advance, it can be enabled by setting true to `sampleAverageEveryTimeAdvance()`. In addition, logging for every step can be turned on by `setMode(Simulation::STEP_BY_STEP)`.

``` C++
sim.sampleAverageEveryTimeAdvance(true);
sim.setMode(Simulation::STEP_BY_STEP);
```

To run the simulation, call `execute()`.

``` C++
sim.execute();
```

After the simulation finishes running, the final results can be printed out.

``` C++
sim.printResults();
```

Obtained example results:

```
Average customer waiting time:          0.946026
Average storage time of chicken meat:   0.126601
Average storage time of beef meat:      0.529915
Average storage time of all meat:       0.328258
Average chicken wrap queue length:      0.687541
Average beef wrap queue length:         0.625644
Average queue length:                   0.656592
Average utilization of employee time:   54.336%
```

Alternatively these results can be also obtained by calling the following methods.

``` C++
double getAverageWaitingTime() const;
double getAverageChickenStorageTime() const;
double getAverageBeefStorageTime() const;
double getAverageMeatStorageTime() const;
double getAverageChickenQueueLength() const;
double getAverageBeefQueueLength() const;
double getAverageQueueLength() const;
double getAverageEmployeeTimeUtilization() const;
```

If the average data every time advance is enabled, the dataset containing these average values at each time advance can be obtained in a form of a vector of struct `Data`.

``` C++
vector<Data> getAverageDataSet();

...

struct Data {
  double simulation_time;
  double average_waiting_time;
  double average_chicken_storage_time;
  double average_beef_storage_time;
  double average_meat_storage_time;
  double average_chicken_queue_length;
  double average_beef_queue_length;
  double average_queue_length;
  double average_employee_time_utilization;
};
```

Such dataset can be used to extract the data to a file for further analysis (sucha as plotting through external scripts).

``` C++
fstream data_out("output\\avg_data.txt", fstream::out);

if(data_out.is_open())
  for(auto& i : sim.getAverageDataSet())
    data_out << i.simulation_time << "\t" << i.average_waiting_time << "\t" << i.average_meat_storage_time << "\t" << i.average_queue_length << "\t" << i.average_employee_time_utilization << endl;

data_out.close(); 
```

## Steady State

![avg_waiting_time](https://github.com/nett-things/simulation-techniques/assets/112755339/54f26cfc-31a0-4911-b867-2e830e575f43)
![avg_employee_util](https://github.com/nett-things/simulation-techniques/assets/112755339/740bd2c0-dccc-45a6-8f13-96eccbe74960)

As it can be observed from the averages plotted against the simulation time, the simulation reaches the steady face around simulation time of `5000s`. After this time, the averages cease spontaneously fluctuating and start oscillating around the same level.
